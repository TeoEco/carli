#ifndef CARLI_ACTION_H
#define CARLI_ACTION_H

#include "utility/linked_list.h"
#include "utility/memory_pool.h"

#include <memory>
#include <sstream>

#include "linkage.h"

namespace Carli {

  class Action;
  
  typedef std::shared_ptr<const Action> Action_Ptr_C;

  typedef std::shared_ptr<Action> Action_Ptr;

  class CARLI_LINKAGE Action : public Zeni::Pool_Allocator<char> {
    Action(const Action &) = delete;
    Action & operator=(const Action &) = delete;

  public:
    Action() {}

    virtual ~Action() {}

    virtual Action * clone() const = 0;

    bool operator<(const Action &rhs) const {return compare(rhs) < 0;}
    bool operator<=(const Action &rhs) const {return compare(rhs) <= 0;}
    bool operator>(const Action &rhs) const {return compare(rhs) > 0;}
    bool operator>=(const Action &rhs) const {return compare(rhs) >= 0;}
    bool operator==(const Action &rhs) const {return compare(rhs) == 0;}
    bool operator!=(const Action &rhs) const {return compare(rhs) != 0;}

    void print(std::ostream &os) const {
      print_impl(os);
    }

    std::string to_string() const {
      std::ostringstream oss;
      print(oss);
      return oss.str();
    }

    virtual int64_t compare(const Action &rhs) const = 0;

    virtual void print_impl(std::ostream &os) const = 0;
  };
}

inline std::ostream & operator<<(std::ostream &os, const Carli::Action &action) {
  action.print(os);
  return os;
}

#endif
