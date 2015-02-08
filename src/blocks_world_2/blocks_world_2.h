#ifndef BLOCKS_WORLD_2_H
#define BLOCKS_WORLD_2_H

#include "carli/agent.h"
#include "carli/environment.h"

#include <algorithm>
#include <list>
#include <stdexcept>

#if !defined(_WINDOWS)
#define BLOCKS_WORLD_2_LINKAGE
#elif !defined(BLOCKS_WORLD_2_INTERNAL)
#define BLOCKS_WORLD_2_LINKAGE __declspec(dllimport)
#else
#define BLOCKS_WORLD_2_LINKAGE __declspec(dllexport)
#endif

namespace Blocks_World_2 {

  using std::dynamic_pointer_cast;
  using std::endl;
  using std::ostream;

  typedef int64_t block_id;

  /** Stupid features:
    * BLOCK ^column C
    * BLOCK ^height H
    * SRC ^right-of DEST
    */

  class BLOCKS_WORLD_2_LINKAGE Move : public Carli::Action {
  public:
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

    Move(const Rete::Variable_Indices &variables, const Rete::WME_Token &token)
     : block(debuggable_cast<const Rete::Symbol_Constant_Int &>(*token[variables.find("block-name")->second]).value),
     dest(debuggable_cast<const Rete::Symbol_Constant_Int &>(*token[variables.find("dest-name")->second]).value)
    {
    }

    Move * clone() const {
      return new Move(block, dest);
    }

    int64_t compare(const Action &rhs) const {
      return compare(debuggable_cast<const Move &>(rhs));
    }

    int64_t compare(const Move &rhs) const {
      return block != rhs.block ? block - rhs.block : dest - rhs.dest;
    }

    void print_impl(ostream &os) const {
      os << "move(" << block << ',' << dest << ')';
    }

    block_id block;
    block_id dest;
  };

  class BLOCKS_WORLD_2_LINKAGE Environment : public Carli::Environment {
  public:
    Environment();

    typedef std::vector<block_id> Stack;
    typedef std::vector<Stack> Stacks;

    const Stacks & get_blocks() const {return m_blocks;}
    const Stacks & get_goal() const {return m_goal;}

    int64_t num_blocks() const {return m_num_blocks;}

  private:
    void init_impl();
    Stacks random_Stacks(const int64_t &num_blocks);

    reward_type transition_impl(const Carli::Action &action);

    void print_impl(ostream &os) const;

    const int64_t m_num_blocks = get_Option_Ranged<int64_t>(Options::get_global(), "num-blocks");

    Zeni::Random m_random;
    Stacks m_blocks;
    Stacks m_goal;
  };

  class BLOCKS_WORLD_2_LINKAGE Agent : public Carli::Agent {
  public:
    Agent(const std::shared_ptr<Carli::Environment> &env);
    ~Agent();

  private:
    void generate_rete();

    void generate_features();

    void update();

    Zeni::Random m_random;

    /*
     * Objects: workspace/goal
     *          stack
     *          block
     *          name
     *
     * Relations: stack ^matches goal-stack
     *            stack ^top block
     *            block ^matches-top stack
     */

    const Rete::Symbol_Constant_String_Ptr_C m_action_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("action"));
    const Rete::Symbol_Constant_String_Ptr_C m_block_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("block"));
    const Rete::Symbol_Constant_String_Ptr_C m_dest_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("dest"));
    const Rete::Symbol_Constant_String_Ptr_C m_clear_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("clear")); ///< Legacy
    const Rete::Symbol_Constant_String_Ptr_C m_in_place_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("in-place")); ///< Legacy
    const Rete::Symbol_Constant_String_Ptr_C m_name_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("name"));
    const Rete::Symbol_Constant_String_Ptr_C m_blocks_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("blocks"));
    const Rete::Symbol_Constant_String_Ptr_C m_discrepancy_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("discrepancy"));
    const Rete::Symbol_Constant_String_Ptr_C m_goal_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("goal"));
    const Rete::Symbol_Constant_String_Ptr_C m_stack_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("stack"));
    const Rete::Symbol_Constant_String_Ptr_C m_matches_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("matches"));
    const Rete::Symbol_Constant_String_Ptr_C m_top_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("top"));
    const Rete::Symbol_Constant_String_Ptr_C m_matches_top_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("matches-top"));
    const Rete::Symbol_Constant_String_Ptr_C m_true_value = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("true"));
    const Rete::Symbol_Constant_String_Ptr_C m_false_value = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("false"));
    const Rete::Symbol_Identifier_Ptr_C m_blocks_id = Rete::Symbol_Identifier_Ptr_C(new Rete::Symbol_Identifier("BLOCKS"));
    const Rete::Symbol_Identifier_Ptr_C m_goal_id = Rete::Symbol_Identifier_Ptr_C(new Rete::Symbol_Identifier("GOAL"));
    const Rete::Symbol_Identifier_Ptr_C m_table_id = Rete::Symbol_Identifier_Ptr_C(new Rete::Symbol_Identifier("TABLE"));
    const Rete::Symbol_Identifier_Ptr_C m_table_stack_id = Rete::Symbol_Identifier_Ptr_C(new Rete::Symbol_Identifier("|"));
    const Rete::Symbol_Constant_Int_Ptr_C m_table_name = Rete::Symbol_Constant_Int_Ptr_C(new Rete::Symbol_Constant_Int(0));
    std::list<Rete::WME_Ptr_C> m_wmes_prev;
  };

}

#endif
