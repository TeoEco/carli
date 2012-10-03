#ifndef BLOCKS_WORLD_H
#define BLOCKS_WORLD_H

#include "environment.h"
#include "linked_list.h"

#include <algorithm>
#include <stdexcept>

namespace Blocks_World {
  
  typedef int block_id;

  struct On_Top;
  typedef Feature<On_Top> feature_type;

  struct In_Place : public feature_type {
    In_Place()
     : block(block_id())
    {
    }

    In_Place(const block_id &block_)
     : block(block_)
    {
    }

    void print(std::ostream &os) const {
      os << "in-place(" << block << ')';
    }

    block_id block;
  };

  struct On_Top : public feature_type {
    On_Top()
     : top(block_id()),
     bottom(block_id())
    {
    }

    On_Top(const block_id &top_, const block_id &bottom_)
     : top(top_),
     bottom(bottom_)
    {
    }

    void print(std::ostream &os) const {
      os << "on-top(" << top << ',' << bottom << ')';
    }

    block_id top;
    block_id bottom;
  };

  struct Move;
  typedef Action<Move> action_type;

  struct Move : public action_type {
    Move()
     : block(block_id()),
     dest(block_id())
    {
    }

    Move(const block_id &block_, const block_id &dest_)
     : block(block_),
     dest(dest_)
    {
    }

    void print(std::ostream &os) const {
      os << "move(" << block << ',' << dest << ')';
    }

    block_id block;
    block_id dest;
  };

  class Environment : public ::Environment<feature_type, action_type> {
  public:
    Environment() {
      Environment::init_impl();
      generate_lists();
    }

    ~Environment() {
      destroy_lists();
    }

  private:
    typedef std::list<block_id> Stack;
    typedef std::list<Stack> Stacks;

    void init_impl() {
      {
        m_blocks.push_front(Stack());
        Stack &stack = *m_blocks.begin();
        stack.push_front(2);
      }
      {
        m_blocks.push_front(Stack());
        Stack &stack = *m_blocks.begin();
        stack.push_front(1);
        stack.push_front(3);
      }
    }

    reward_type transition_impl(const action_type &action) {
      Stacks::iterator src = std::find_if(m_blocks.begin(), m_blocks.end(), [&action](Stack &stack)->bool {
        return !stack.empty() && *stack.begin() == static_cast<const Move &>(action).block;
      });
      Stacks::iterator dest = std::find_if(m_blocks.begin(), m_blocks.end(), [&action](Stack &stack)->bool {
        return !stack.empty() && *stack.begin() == static_cast<const Move &>(action).dest;
      });

      if(src == m_blocks.end())
        throw std::runtime_error("Attempt to move Block from under another Block.");
      if(dest == m_blocks.end())
        dest = m_blocks.insert(m_blocks.begin(), Stack());

      src->pop_front();
      dest->push_front(static_cast<const Move &>(action).block);

      if(src->empty())
        m_blocks.erase(src);

      if(m_blocks.size() == 1) {
        m_metastate = SUCCESS;
        block_id id = 0;
        std::for_each(m_blocks.begin()->begin(), m_blocks.begin()->end(), [this,&id](const block_id &id_) {
          if(++id != id_)
            m_metastate = NON_TERMINAL;
        });
      }
      else
        m_metastate = NON_TERMINAL;

      return reward_type(-1);
    }

    void print_impl(std::ostream &os) const {
      os << "Blocks World:" << std::endl;
      std::for_each(m_blocks.begin(), m_blocks.end(), [&os](const Stack &stack) {
        std::for_each(stack.rbegin(), stack.rend(), [&os](const block_id &id) {
          os << ' ' << id;
        });
        os << std::endl;
      });

      if(m_features) {
        std::for_each(m_features->features.begin(), m_features->features.end(), [&os](const feature_type &feature) {
          os << ' ' << feature;
        });
        os << std::endl;
      }

      if(m_candidates) {
        std::for_each(m_candidates->candidates.begin(), m_candidates->candidates.end(), [&os](const action_type &action) {
          os << ' ' << action;
        });
        os << std::endl;
      }
    }

    void generate_lists() {
      generate_features();
      generate_candidates();
    }

    void generate_features() {
      assert(!m_features);

      feature_type::iterator features;
      std::for_each(m_blocks.begin(), m_blocks.end(), [&features](const Stack &stack) {
        auto it = stack.begin();
        auto itn = ++stack.begin();
        auto iend = stack.end();

        while(itn != iend) {
          feature_type * on_top = new On_Top(*it, *itn);
          on_top->features.insert_before(features);
          features = &on_top->features;

          it = itn;
          ++itn;
        }

        block_id counter = 4;
        std::for_each(stack.rbegin(), stack.rend(), [&features,&counter](const block_id &id) {
          if(--counter == id) {
            feature_type * in_place = new In_Place(id);
            in_place->features.insert_before(features);
            features = &in_place->features;
          }
          else
            counter = 0;
        });
      });

      m_features = features.get();
    }

    void generate_candidates() {
      assert(!m_candidates);

      action_type::iterator candidates;
      std::for_each(m_blocks.begin(), m_blocks.end(), [&candidates,this](const Stack &stack_src) {
        if(stack_src.size() != 1) {
          action_type * move = new Move(*stack_src.begin(), 0);
          move->candidates.insert_before(candidates);
          candidates = &move->candidates;
        }

        std::for_each(m_blocks.begin(), m_blocks.end(), [&candidates,&stack_src](const Stack &stack_dest) {
          if(&stack_src == &stack_dest)
            return;

          action_type * move = new Move(*stack_src.begin(), *stack_dest.begin());
          move->candidates.insert_before(candidates);
          candidates = &move->candidates;
        });
      });

      m_candidates = candidates.get();
    }

    void destroy_lists() {
      if(m_features) {
        m_features->features.destroy();
        m_features = nullptr;
      }

      if(m_candidates) {
        m_candidates->candidates.destroy();
        m_candidates = nullptr;
      }
    }

    Stacks m_blocks;
  };

}

#endif
