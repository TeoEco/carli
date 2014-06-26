#ifndef MOUNTAIN_CAR_H
#define MOUNTAIN_CAR_H

#include "carli/agent.h"
#include "carli/environment.h"

#include <algorithm>
#include <array>
#include <cfloat>
#include <list>
#include <stdexcept>

namespace Mountain_Car {
  enum Direction : char {LEFT = 0, IDLE = 1, RIGHT = 2};
}

inline std::ostream & operator<<(std::ostream &os, const Mountain_Car::Direction &direction);

namespace Mountain_Car {

  using std::dynamic_pointer_cast;
  using std::endl;
  using std::make_pair;
  using std::map;
  using std::ostream;
  using std::pair;
  using std::set;
  using std::shared_ptr;

  class Feature;
  class Position;
  class Velocity;
  class Acceleration_Direction;

  class Feature : public Carli::Feature {
  public:
    Feature(const Rete::WME_Token_Index &axis_, const Rete::WME_Bindings &bindings_) : Carli::Feature(axis_, bindings_) {}

    virtual Feature * clone() const = 0;
  };

  class Position : public Carli::Feature_Ranged<Feature> {
  public:
    enum Index {index = 0};

    Position(const double &bound_lower_, const double &bound_upper_, const int64_t &depth_, const bool &upper_)
     : Feature_Ranged(Rete::WME_Token_Index(index, 2), Rete::WME_Bindings(), bound_lower_, bound_upper_, depth_, upper_, false)
    {
    }

    Position * clone() const {
      return new Position(bound_lower, bound_upper, depth, upper);
    }

    void print(ostream &os) const {
      os << "x(" << bound_lower << ',' << bound_upper << ':' << depth << ')';
    }
  };

  class Velocity : public Carli::Feature_Ranged<Feature> {
  public:
    enum Index {index = 1};

    Velocity(const double &bound_lower_, const double &bound_upper_, const int64_t &depth_, const bool &upper_)
     : Feature_Ranged(Rete::WME_Token_Index(index, 2), Rete::WME_Bindings(), bound_lower_, bound_upper_, depth_, upper_, false)
    {
    }

    Velocity * clone() const {
      return new Velocity(bound_lower, bound_upper, depth, upper);
    }

    void print(ostream &os) const {
      os << "x-dot(" << bound_lower << ',' << bound_upper << ':' << depth << ')';
    }
  };

  class Acceleration_Direction : public Carli::Feature_Enumerated<Feature> {
  public:
    enum Index {index = 2};

    Acceleration_Direction(const Direction &direction)
     : Feature_Enumerated<Feature>(Rete::WME_Token_Index(index, 2), Rete::WME_Bindings(), direction)
    {
    }

    Acceleration_Direction * clone() const {
      return new Acceleration_Direction(Direction(value));
    }

    int64_t get_depth() const {
      return 0;
    }

    int64_t compare_value(const Carli::Feature &) const {
      return 0;
    }

    void print(ostream &os) const {
      os << "acceleration(" << Direction(value) << ')';
    }
  };

  class Acceleration : public Carli::Action {
  public:
    Acceleration(const Direction &direction_ = IDLE)
     : direction(direction_)
    {
    }

    Acceleration(const Rete::WME_Token &token)
     : direction(Direction(debuggable_cast<const Rete::Symbol_Constant_Int &>(*token[Rete::WME_Token_Index(Acceleration_Direction::index, 2)]).value))
    {
    }

    Acceleration * clone() const {
      return new Acceleration(direction);
    }

    int64_t compare(const Action &rhs) const {
      return direction - debuggable_cast<const Acceleration &>(rhs).direction;
    }

    int64_t compare(const Acceleration &rhs) const {
      return direction - rhs.direction;
    }

    void print_impl(ostream &os) const {
      os << "acceleration(" << direction << ')';
    }

    Direction direction;
  };

  class Environment : public Carli::Environment {
    Environment(const Environment &);
    Environment & operator=(const Environment &);

  public:
    typedef pair<double, double> double_pair;

    Environment();

    const double & get_x() const {return m_x;}
    const double & get_x_dot() const {return m_x_dot;}
//    const double & get_value(const Feature_Axis &index) const {return *(&m_x + index);}
    bool is_random_start() const {return m_random_start;}
    bool is_reward_negative() const {return m_reward_negative;}

    void set_x(const double &x_) {m_x = x_;}
    void set_x_dot(const double &x_dot_) {m_x_dot = x_dot_;}

    bool success() const {
      return m_x >= m_goal_position;
    }

  private:
    void init_impl();

    void alter_impl();

    reward_type transition_impl(const Carli::Action &action);

    void print_impl(ostream &os) const;

    Zeni::Random m_random_init;

    double m_x = 0.0;
    double m_x_dot = 0.0;

    const double m_min_position = -1.2;
    const double m_max_position = 0.6;
    const double m_max_velocity = 0.07;
    const double m_goal_position = 0.5;

    double m_cart_force = 0.001;
    double m_grav_force = 0.0025;

    const bool m_random_start = get_Option_Ranged<bool>(Options::get_global(), "random-start");
    const bool m_reward_negative = get_Option_Ranged<bool>(Options::get_global(), "reward-negative");
  };

  class Agent : public Carli::Agent {
  public:
    Agent(const shared_ptr<Carli::Environment> &env);
    ~Agent();

    void print_policy(ostream &os, const size_t &granularity);

  private:
    void generate_cmac(const Rete::Rete_Node_Ptr &parent);

    void generate_rete(const Rete::Rete_Node_Ptr &parent);

    void generate_features();

    void update();

    const double m_min_x = -1.2;
    const double m_max_x = 0.6;
    const double m_min_x_dot = -0.07;
    const double m_max_x_dot = 0.07;

    const Rete::Symbol_Variable_Ptr_C m_first_var = Rete::Symbol_Variable_Ptr_C(new Rete::Symbol_Variable(Rete::Symbol_Variable::First));
    const Rete::Symbol_Variable_Ptr_C m_third_var = Rete::Symbol_Variable_Ptr_C(new Rete::Symbol_Variable(Rete::Symbol_Variable::Third));

    const Rete::Symbol_Constant_String_Ptr_C m_x_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("x"));
    const Rete::Symbol_Constant_String_Ptr_C m_x_dot_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("x-dot"));
    Rete::Symbol_Constant_Float_Ptr_C m_x_value = Rete::Symbol_Constant_Float_Ptr_C(new Rete::Symbol_Constant_Float(dynamic_pointer_cast<Environment>(get_env())->get_x()));
    Rete::Symbol_Constant_Float_Ptr_C m_x_dot_value = Rete::Symbol_Constant_Float_Ptr_C(new Rete::Symbol_Constant_Float(dynamic_pointer_cast<Environment>(get_env())->get_x_dot()));

    Rete::WME_Ptr m_x_wme;
    Rete::WME_Ptr m_x_dot_wme;

    std::array<std::shared_ptr<const Carli::Action>, 3> m_action = {{std::shared_ptr<const Carli::Action>(new Acceleration(LEFT)),
                                                                     std::shared_ptr<const Carli::Action>(new Acceleration(IDLE)),
                                                                     std::shared_ptr<const Carli::Action>(new Acceleration(RIGHT))}};
  };

}

std::ostream & operator<<(std::ostream &os, const Mountain_Car::Direction &direction) {
  switch(direction) {
    case Mountain_Car::LEFT:  os << "left";  break;
    case Mountain_Car::IDLE:  os << "idle";  break;
    case Mountain_Car::RIGHT: os << "right"; break;
    default: abort();
  }

  return os;
}

#endif
