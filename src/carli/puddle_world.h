#ifndef PUDDLE_WORLD_H
#define PUDDLE_WORLD_H

#include "agent.h"
#include "environment.h"

#include <algorithm>
#include <array>
#include <cfloat>
#include <list>
#include <stdexcept>

namespace Puddle_World {

  class Feature;
  class Feature : public ::Feature<Feature> {
    Feature & operator=(const Feature &);

  public:
    enum Axis {X, Y};

    Feature()
     : ::Feature<Feature>(true)
    {
    }

    Feature(const Axis &axis_, const double &bound_lower_, const double &bound_higher_, const size_t &depth_)
     : ::Feature<Feature>(true),
     axis(axis_),
     bound_lower(bound_lower_),
     bound_higher(bound_higher_),
     depth(depth_)
    {
    }

    int compare_pi(const Feature &rhs) const {
      return depth != rhs.depth ? (depth < rhs.depth ? -1 : 1) :
             axis != rhs.axis ? axis - rhs.axis :
             bound_lower != rhs.bound_lower ? (bound_lower < rhs.bound_lower ? -1 : 1) :
             (bound_higher == rhs.bound_higher ? 0 : bound_higher < rhs.bound_higher ? -1 : 1);
    }

    bool precedes(const Feature &rhs) const {
      const auto mdpt = midpt();
      return axis == rhs.axis && (rhs.bound_lower == mdpt || rhs.bound_higher == mdpt);
    }

    double midpt() const {
      return (bound_lower + bound_higher) / 2.0;
    }

    Feature * clone() const {
      return new Feature(axis, bound_lower, bound_higher, depth);
    }

    void print_impl(std::ostream &os) const {
      os << (axis == X ? 'x' : 'y') << '(' << bound_lower << ',' << bound_higher << ':' << depth << ')';
    }

    Axis axis;
    double bound_lower; ///< inclusive
    double bound_higher; ///< exclusive

    size_t depth; ///< 0 indicates unsplit
  };

  typedef Feature feature_type;

  class Move;
  typedef Action<Move, Move> action_type;

  class Move : public action_type {
  public:
    enum Direction {NORTH, SOUTH, EAST, WEST};

    Move(const Direction &direction_ = NORTH)
     : direction(direction_)
    {
    }

    Move * clone() const {
      return new Move(direction);
    }

    int compare(const Move &rhs) const {
      return direction - rhs.direction;
    }

    void print_impl(std::ostream &os) const {
      os << "move(";

      switch(direction) {
        case NORTH: os << "north"; break;
        case SOUTH: os << "south"; break;
        case EAST:  os << "east";  break;
        case WEST:  os << "west";  break;
        default: abort();
      }

      os << ')';
    }

    Direction direction;
  };

  class Environment : public ::Environment<action_type> {
  public:
    typedef std::pair<double, double> double_pair;

    Environment()
     : m_init_x(0.15, 0.45),
     m_init_y(0.15, 0.45),
     m_goal_dynamic(false),
     m_step_count(0),
     m_random_start(false)
    {
      m_horizontal_puddles.push_back({{0.1, 0.45, 0.75, 0.1}});
      m_vertical_puddles.push_back({{0.45, 0.4, 0.8, 0.1}});

      Environment::init_impl();
    }

    const double_pair & get_position() const {return m_position;}
    const double & get_value(const Feature::Axis &index) const {return *(&m_position.first + index);}
    bool is_random_start() const {return m_random_start;}

    void set_position(const double_pair &position_) {m_position = position_;}
    void set_random_start(const bool &random_start_) {
      m_random_start = random_start_;

      if(m_random_start) {
        m_init_x = double_pair(0.0, 1.0);
        m_init_y = double_pair(0.0, 1.0);
      }
      else {
        m_init_x = double_pair(0.15, 0.45);
        m_init_y = double_pair(0.15, 0.45);
      }
    }

    bool goal_reached() const {
      if(m_goal_dynamic)
        return m_goal_x.first <= m_position.first  && m_position.first  < m_goal_x.second &&
               m_goal_y.first <= m_position.second && m_position.second < m_goal_y.second;
      else
        return m_position.first + m_position.second > 1.9;
    }

  private:
    typedef std::array<double, 4> Puddle;

    void init_impl() {
      do {
        m_position.first = m_init_x.first + m_random_init.frand_lt() * (m_init_x.second - m_init_x.first);
        m_position.second = m_init_y.first + m_random_init.frand_lt() * (m_init_y.second - m_init_y.first);
      } while(goal_reached());

      m_random_motion = Zeni::Random(m_random_init.rand());
    }

    void alter_impl() {
      /// Too extreme
//       m_horizontal_puddles.at(0)[1] = 0.3;
//       m_vertical_puddles.at(0)[2] = 0.6;
//       m_horizontal_puddles.push_back({{0.6, 0.75, 0.5, 0.1}});
//       m_goal_dynamic = true;
//       m_goal_x = std::make_pair(0.4, 0.5);
//       m_goal_y = std::make_pair(0.7, 0.8);

      m_goal_dynamic = true;
      m_goal_x = std::make_pair(0.7, 0.8);
      m_goal_y = std::make_pair(0.9, 1.0);
    }

    reward_type transition_impl(const action_type &action) {
      const double shift = m_random_motion.frand_gaussian() * 0.01;
      const double step_size = shift + 0.05;

      switch(dynamic_cast<const Move &>(action).direction) {
        case Move::NORTH: m_position.second += step_size; break;
        case Move::SOUTH: m_position.second -= step_size; break;
        case Move::EAST:  m_position.first  += step_size; break;
        case Move::WEST:  m_position.first  -= step_size; break;
        default: abort();
      }

      if(m_position.first < 0.0)
        m_position.first = 0.0;
      else if(m_position.first >= 1.0)
        m_position.first = 1.0 - DBL_EPSILON;
      if(m_position.second < 0.0)
        m_position.second = 0.0;
      else if(m_position.second >= 1.0)
        m_position.second = 1.0 - DBL_EPSILON;

      ++m_step_count;

      double reward = -1.0;

      std::for_each(m_horizontal_puddles.begin(), m_horizontal_puddles.end(), [this,&reward](const Puddle &puddle) {
        reward -= 400.0 * horizontal_puddle_reward(puddle[0], puddle[1], puddle[2], puddle[3]);
      });
      std::for_each(m_vertical_puddles.begin(), m_vertical_puddles.end(), [this,&reward](const Puddle &puddle) {
        reward -= 400.0 * vertical_puddle_reward(puddle[0], puddle[1], puddle[2], puddle[3]);
      });

      return reward;
    }

    double horizontal_puddle_reward(const double &left, const double &right, const double &y, const double &radius) const {
      double dist;

      if(m_position.first < left)
        dist = pythagoras(m_position.first - left, m_position.second - y);
      else if(m_position.first < right)
        dist = std::abs(m_position.second - y);
      else
        dist = pythagoras(m_position.first - right, m_position.second - y);

      return std::max(0.0, radius - dist);
    }

    double vertical_puddle_reward(const double &x, const double &bottom, const double &top, const double &radius) const {
      double dist;

      if(m_position.second < bottom)
        dist = pythagoras(m_position.first - x, m_position.second - bottom);
      else if(m_position.second < top)
        dist = std::abs(m_position.first - x);
      else
        dist = pythagoras(m_position.first - x, m_position.second - top);

      return std::max(0.0, radius - dist);
    }

    template <typename TYPE>
    TYPE pythagoras(const TYPE &lhs, const TYPE &rhs) const {
      return sqrt(squared(lhs) + squared(rhs));
    }

    template <typename TYPE>
    TYPE squared(const TYPE &value) const {
      return value * value;
    }

    void print_impl(std::ostream &os) const {
      os << "Puddle World:" << std::endl;
      os << " (" << m_position.first << ", " << m_position.second << ')' << std::endl;
    }

    Zeni::Random m_random_init;
    Zeni::Random m_random_motion;

    double_pair m_position;

    double_pair m_init_x;
    double_pair m_init_y;
    
    bool m_goal_dynamic;
    double_pair m_goal_x;
    double_pair m_goal_y;

    size_t m_step_count;
    bool m_random_start;

    std::vector<Puddle> m_horizontal_puddles;
    std::vector<Puddle> m_vertical_puddles;
  };

  class Agent : public ::Agent<feature_type, action_type> {
  public:
    typedef std::pair<double, double> point_type;
    typedef std::pair<point_type, point_type> line_segment_type;

    Agent(const std::shared_ptr<environment_type> &env)
     : ::Agent<feature_type, action_type>(env)
    {
      set_credit_assignment(INV_LOG_UPDATE_COUNT);
      set_discount_rate(1.0);
      set_learning_rate(0.3);
      set_on_policy(false);
      set_epsilon(0.1);
      set_pseudoepisode_threshold(10);
      m_features_complete = false;
    }

    void print_value_function_grid(std::ostream &os) const {
      std::set<line_segment_type> line_segments;
      std::for_each(m_value_function.begin(), m_value_function.end(), [this,&os,&line_segments](decltype(*m_value_function.begin()) &value) {
        os << *value.first << ":" << std::endl;
        const auto line_segments2 = this->generate_value_function_grid_sets(value.second);
        this->merge_value_function_grid_sets(line_segments, line_segments2);
        this->print_value_function_grid_set(os, line_segments2);
      });
      os << "all:" << std::endl;
      print_value_function_grid_set(os, line_segments);
    }

    void print_update_count_grid(std::ostream &os) const {
      std::map<line_segment_type, size_t> update_counts;
      std::for_each(m_value_function.begin(), m_value_function.end(), [this,&os,&update_counts](decltype(*m_value_function.begin()) &value) {
        os << *value.first << ":" << std::endl;
        const auto update_counts2 = this->generate_update_count_maps(value.second);
        this->merge_update_count_maps(update_counts, update_counts2);
        this->print_update_count_map(os, update_counts2);
      });
      os << "all:" << std::endl;
      print_update_count_map(os, update_counts);
    }

    void print_policy(std::ostream &os, const size_t &granularity) {
      auto env = std::dynamic_pointer_cast<Environment>(get_env());
      const auto position = env->get_position();

      for(size_t y = granularity; y != 0lu; --y) {
        for(size_t x = 0lu; x != granularity; ++x) {
          env->set_position(Environment::double_pair((x + 0.5) / granularity, (y - 0.5) / granularity));
          regenerate_lists();
          auto action = choose_greedy();
          switch(dynamic_cast<const Move &>(*action).direction) {
            case Move::NORTH: os << 'N'; break;
            case Move::SOUTH: os << 'S'; break;
            case Move::EAST:  os << 'E'; break;
            case Move::WEST:  os << 'W'; break;
            default: abort();
          }
        }
        os << std::endl;
      }

      env->set_position(position);
      regenerate_lists();
    }

  private:
    std::set<line_segment_type> generate_value_function_grid_sets(const feature_trie_type * const &trie, const line_segment_type &extents = line_segment_type(point_type(), point_type(1.0, 1.0))) const {
      std::set<line_segment_type> line_segments;
      if(trie) {
        std::for_each(trie->begin(trie), trie->end(trie), [this,&line_segments,&extents](const feature_trie_type &trie2) {
          auto new_extents = extents;
          const auto &key = trie2.get_key();
          if(key->axis == Feature::X) {
            new_extents.first.first = key->bound_lower;
            new_extents.second.first = key->bound_higher;
          }
          else {
            new_extents.first.second = key->bound_lower;
            new_extents.second.second = key->bound_higher;
          }

          if(new_extents.first.first != extents.first.first)
            line_segments.insert(std::make_pair(std::make_pair(new_extents.first.first, new_extents.first.second), std::make_pair(new_extents.first.first, new_extents.second.second)));
          if(new_extents.first.second != extents.first.second)
            line_segments.insert(std::make_pair(std::make_pair(new_extents.first.first, new_extents.first.second), std::make_pair(new_extents.second.first, new_extents.first.second)));
          if(new_extents.second.first != extents.second.first)
            line_segments.insert(std::make_pair(std::make_pair(new_extents.second.first, new_extents.first.second), std::make_pair(new_extents.second.first, new_extents.second.second)));
          if(new_extents.second.second != extents.second.second)
            line_segments.insert(std::make_pair(std::make_pair(new_extents.first.first, new_extents.second.second), std::make_pair(new_extents.second.first, new_extents.second.second)));

          if(trie2.get_deeper()) {
            const auto line_segments2 = this->generate_value_function_grid_sets(trie2.get_deeper(), new_extents);
            this->merge_value_function_grid_sets(line_segments, line_segments2);
          }
        });
      }
      return line_segments;
    }

    std::map<line_segment_type, size_t> generate_update_count_maps(const feature_trie_type * const &trie, const line_segment_type &extents = line_segment_type(point_type(), point_type(1.0, 1.0)), const size_t &update_count = 0) const {
      std::map<line_segment_type, size_t> update_counts;
      if(trie) {
        std::for_each(trie->begin(trie), trie->end(trie), [this,&update_counts,&extents,&update_count](const feature_trie_type &trie2) {
          auto new_extents = extents;
          const auto &key = trie2.get_key();
          if(key->axis == Feature::X) {
            new_extents.first.first = key->bound_lower;
            new_extents.second.first = key->bound_higher;
          }
          else {
            new_extents.first.second = key->bound_lower;
            new_extents.second.second = key->bound_higher;
          }

          const auto update_count2 = update_count + (trie2.get() ? trie2->update_count : 0);

          update_counts[new_extents] = update_count2;

          if(trie2.get_deeper()) {
            const auto update_counts2 = this->generate_update_count_maps(trie2.get_deeper(), new_extents, update_count2);
            this->merge_update_count_maps(update_counts, update_counts2);
          }
        });
      }
      return update_counts;
    }

    void print_value_function_grid_set(std::ostream &os, const std::set<line_segment_type> &line_segments) const {
      std::for_each(line_segments.begin(), line_segments.end(), [&os](const line_segment_type &line_segment) {
        os << line_segment.first.first << ',' << line_segment.first.second << '/' << line_segment.second.first << ',' << line_segment.second.second << std::endl;
      });
    }

    void print_update_count_map(std::ostream &os, const std::map<line_segment_type, size_t> &update_counts) const {
      std::for_each(update_counts.begin(), update_counts.end(), [&os](const std::pair<line_segment_type, size_t> &rect) {
        os << rect.first.first.first << ',' << rect.first.first.second << '/' << rect.first.second.first << ',' << rect.first.second.second << '=' << rect.second << std::endl;
      });
    }

    void merge_value_function_grid_sets(std::set<line_segment_type> &combination, const std::set<line_segment_type> &additions) const {
      std::for_each(additions.begin(), additions.end(), [&combination](const line_segment_type &line_segment) {
        combination.insert(line_segment);
      });
    }

    void merge_update_count_maps(std::map<line_segment_type, size_t> &combination, const std::map<line_segment_type, size_t> &additions) const {
      std::for_each(additions.begin(), additions.end(), [&combination](const std::pair<line_segment_type, size_t> &rect) {
        combination[rect.first] += rect.second;
      });
    }

    void generate_features() {
      auto env = std::dynamic_pointer_cast<const Environment>(get_env());

      assert(!m_features);

      Feature::List * x_tail = &(new Feature(Feature::X, 0.0, 1.0, 0))->features;
      x_tail = x_tail->insert_in_order<feature_type::List::compare_default>(m_features, false);
      Feature::List * y_tail = &(new Feature(Feature::Y, 0.0, 1.0, 0))->features;
      y_tail = y_tail->insert_in_order<feature_type::List::compare_default>(m_features, false);

      std::array<feature_trie, 4> tries = {{get_trie(Move(Move::NORTH)),
                                            get_trie(Move(Move::SOUTH)),
                                            get_trie(Move(Move::EAST)),
                                            get_trie(Move(Move::WEST))}};

      for(;;) {
        Feature::List * x_tail_next = nullptr;
        Feature::List * y_tail_next = nullptr;

        std::for_each(tries.begin(), tries.end(), [this,&env,&x_tail,&y_tail,&x_tail_next,&y_tail_next](feature_trie &trie) {
          if(generate_feature_ranged(env, trie, x_tail, x_tail_next))
            return;
          if(generate_feature_ranged(env, trie, y_tail, y_tail_next))
            return;
        });

        if(x_tail_next)
          x_tail = x_tail_next;
        if(y_tail_next)
          y_tail = y_tail_next;

        if(!x_tail_next && !y_tail_next)
          break;
      }
    }

    bool generate_feature_ranged(const std::shared_ptr<const Environment> &env, feature_trie &trie, const Feature::List * const &tail, Feature::List * &tail_next) {
      auto match = std::find_if(trie->begin(trie), trie->end(trie), [&tail](const feature_trie_type &trie)->bool {return trie.get_key()->compare(**tail) == 0;});

      if(match && (!match->get() || match->get()->type != Q_Value::FRINGE)) {
        auto feature = match->get_key();
        const auto midpt = feature->midpt();
        if(env->get_value(feature->axis) < midpt)
          tail_next = &(new Feature(feature->axis, feature->bound_lower, midpt, feature->depth + 1))->features;
        else
          tail_next = &(new Feature(feature->axis, midpt, feature->bound_higher, feature->depth + 1))->features;
        tail_next = tail_next->insert_in_order<feature_type::List::compare_default>(m_features, false);
        trie = match->get_deeper();
        return true;
      }

      return false;
    }

    void generate_candidates() {
      auto env = std::dynamic_pointer_cast<const Environment>(get_env());

      assert(!m_candidates);

      (new Move(Move::NORTH))->candidates.insert_before(m_candidates);
      (new Move(Move::SOUTH))->candidates.insert_before(m_candidates);
      (new Move(Move::EAST))->candidates.insert_before(m_candidates);
      (new Move(Move::WEST))->candidates.insert_before(m_candidates);
    }

    void update() {
      auto env = std::dynamic_pointer_cast<const Environment>(get_env());

      m_metastate = env->goal_reached() ? SUCCESS : NON_TERMINAL;
    }
  };

}

#endif
