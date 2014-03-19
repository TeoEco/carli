#ifndef CARLI_Q_VALUE_H
#define CARLI_Q_VALUE_H

#include "utility/memory_pool.h"
#include "utility/linked_list.h"

#include "value.h"

#include <cfloat>
#include <limits>
#include <memory>

namespace Carli {

  class Q_Value;
  class Q_Value : public Zeni::Pool_Allocator<Q_Value>, public std::enable_shared_from_this<Q_Value> {
    Q_Value(const Q_Value &) = delete;
    Q_Value & operator=(const Q_Value &) = delete;

  public:
    typedef Zeni::Linked_List<Q_Value> List;
    typedef List::iterator iterator;
    enum class Type : char {SPLIT, UNSPLIT, FRINGE};

    Q_Value(const double &q_value_, const Type &type_, const size_t &depth_)
     : depth(depth_),
     type(type_),
     value(q_value_),
     eligible(this)
    {
    }

    Q_Value & operator=(const double &q_value_) {
      value = q_value_;
      return *this;
    }

    size_t last_episode_fired = std::numeric_limits<size_t>::max();
    size_t last_step_fired = std::numeric_limits<size_t>::max();
    size_t pseudoepisode_count = 0;

    size_t depth;
    size_t update_count = 0;

    Type type;

    bool eligibility_init = false;
    double eligibility = -1.0;
    double credit = 1.0;
  //  double weight = 1.0;

    double value;
    Value cabe; ///< Cumulative Absolute Bellman Error
    Value mabe; ///< Mean Absolute Bellman Error (cabe / update_count)

  #ifdef WHITESON_ADAPTIVE_TILE
    double minbe = DBL_MAX; ///< Minimum Bellman Error experienced
  #endif

    double t0; ///< temp "register"

    List eligible;

    static size_t eligible_offset() {
      union {
        const List Q_Value:: * m;
        const char * c;
      } u;

      u.c = nullptr;
      u.m = &Q_Value::eligible;
      return u.c - static_cast<char *>(nullptr);
    }
  };

}

#endif
