#ifndef TETRIS_H
#define TETRIS_H

#include "carli/agent.h"
#include "carli/environment.h"

#include <array>
#include <stdexcept>

namespace Tetris {
  enum Tetromino_Supertype {TETS_SQUARE = 1,
                            TETS_LINE = 2,
                            TETS_T = 3,
                            TETS_L = 4,
                            TETS_J = 5,
                            TETS_S = 6,
                            TETS_Z = 7};

  enum Tetromino_Type {TET_SQUARE = 0x10,
                       TET_LINE_DOWN = 0x20, TET_LINE_RIGHT = 0x21,
                       TET_T = 0x30, TET_T_90 = 0x31, TET_T_180 = 0x32, TET_T_270 = 0x33,
                       TET_L = 0x40, TET_L_90 = 0x41, TET_L_180 = 0x42, TET_L_270 = 0x43,
                       TET_J = 0x50, TET_J_90 = 0x51, TET_J_180 = 0x52, TET_J_270 = 0x53,
                       TET_S = 0x60, TET_S_90 = 0x61,
                       TET_Z = 0x70, TET_Z_90 = 0x71};

  inline uint8_t num_types(const Tetromino_Supertype &supertype) {
    return supertype == TETS_SQUARE ? 1 : (supertype == TETS_LINE || supertype == TETS_S || supertype == TETS_Z) ? 2 : 4;
  }

  inline Tetromino_Type super_to_type(const Tetromino_Supertype &supertype, const uint8_t &index) {
    return Tetromino_Type((supertype << 4) | (index & 0x3));
  }

  inline Tetromino_Supertype type_to_super(const Tetromino_Type &type) {
    return Tetromino_Supertype(type >> 4);
  }
}

inline std::ostream & operator<<(std::ostream &os, const Tetris::Tetromino_Type &type);

namespace Tetris {

  using std::dynamic_pointer_cast;
  using std::endl;
  using std::ostream;

  class Feature;
  class Type;
  class Size;
  class Position;
  class Gaps;
  class Clears;
  class X_Odd;

  class Feature : public Carli::Feature {
  public:
    Feature() {}

    virtual Feature * clone() const = 0;

    int64_t compare_axis(const Carli::Feature &rhs) const {
      return compare_axis(debuggable_cast<const Feature &>(rhs));
    }

    virtual int64_t compare_axis(const Feature &rhs) const = 0;
    virtual int64_t compare_axis(const Type &rhs) const = 0;
    virtual int64_t compare_axis(const Size &rhs) const = 0;
    virtual int64_t compare_axis(const Position &rhs) const = 0;
    virtual int64_t compare_axis(const Gaps &rhs) const = 0;
    virtual int64_t compare_axis(const Clears &rhs) const = 0;
    virtual int64_t compare_axis(const X_Odd &rhs) const = 0;

    virtual Rete::WME_Token_Index wme_token_index() const = 0;
  };

  class Type : public Carli::Feature_Enumerated<Feature> {
  public:
    enum Axis : size_t {CURRENT = 1, NEXT = 2};

    Type(const Axis &axis_, const Tetromino_Type &type_)
     : Feature_Enumerated<Feature>(type_), axis(axis_)
    {
    }

    Type * clone() const {
      return new Type(axis, Tetromino_Type(value));
    }

    int64_t compare_axis(const Feature &rhs) const {
      return -rhs.compare_axis(*this);
    }
    int64_t compare_axis(const Type &rhs) const {
      return axis - rhs.axis;
    }
    int64_t compare_axis(const Size &) const {return -1;}
    int64_t compare_axis(const Position &) const {return -1;}
    int64_t compare_axis(const Gaps &) const {return -1;}
    int64_t compare_axis(const Clears &) const {return -1;}
    int64_t compare_axis(const X_Odd &) const {return -1;}

    Rete::WME_Token_Index wme_token_index() const {
      return Rete::WME_Token_Index(axis, 2);
    }

    void print(ostream &os) const {
      os << "type(" << (axis == CURRENT ? "current" : "next") << ':' << value << ')';
    }

    Axis axis;
  };

  class Size : public Carli::Feature_Ranged<Feature> {
  public:
    enum Axis : size_t {WIDTH = 3, HEIGHT = 4};

    Size(const Axis &axis_, const double &bound_lower_, const double &bound_upper_, const int64_t &depth_, const bool &upper_)
     : Feature_Ranged(Rete::WME_Token_Index(axis_, 2), bound_lower_, bound_upper_, depth_, upper_, true)
    {
    }

    Size * clone() const {
      return new Size(Axis(axis.first), bound_lower, bound_upper, depth, upper);
    }

    int64_t compare_axis(const Tetris::Feature &rhs) const {
      return -rhs.compare_axis(*this);
    }
    int64_t compare_axis(const Type &) const {return 1;}
    int64_t compare_axis(const Size &rhs) const {
      return Feature_Ranged_Data::compare_axis(rhs);
    }
    int64_t compare_axis(const Position &) const {return -1;}
    int64_t compare_axis(const Gaps &) const {return -1;}
    int64_t compare_axis(const Clears &) const {return -1;}
    int64_t compare_axis(const X_Odd &) const {return -1;}

    Rete::WME_Token_Index wme_token_index() const {
      return axis;
    }

    void print(ostream &os) const {
      switch(axis.first) {
        case WIDTH: os << "width"; break;
        case HEIGHT: os << "height"; break;
        default: abort();
      }

      os << '(' << bound_lower << ',' << bound_upper << ':' << depth << ')';
    }
  };

  class Position : public Carli::Feature_Ranged<Feature> {
  public:
    enum Axis : size_t {X = 5, Y = 6};

    Position(const Axis &axis_, const double &bound_lower_, const double &bound_upper_, const int64_t &depth_, const bool &upper_)
     : Feature_Ranged(Rete::WME_Token_Index(axis_, 2), bound_lower_, bound_upper_, depth_, upper_, true)
    {
    }

    Position * clone() const {
      return new Position(Axis(axis.first), bound_lower, bound_upper, depth, upper);
    }

    int64_t compare_axis(const Tetris::Feature &rhs) const {
      return -rhs.compare_axis(*this);
    }
    int64_t compare_axis(const Type &) const {return 1;}
    int64_t compare_axis(const Size &) const {return 1;}
    int64_t compare_axis(const Position &rhs) const {
      return Feature_Ranged_Data::compare_axis(rhs);
    }
    int64_t compare_axis(const Gaps &) const {return -1;}
    int64_t compare_axis(const Clears &) const {return -1;}
    int64_t compare_axis(const X_Odd &) const {return -1;}

    Rete::WME_Token_Index wme_token_index() const {
      return axis;
    }

    void print(ostream &os) const {
      switch(axis.first) {
        case X: os << 'x'; break;
        case Y: os << 'y'; break;
        default: abort();
      }

      os << '(' << bound_lower << ',' << bound_upper << ':' << depth << ')';
    }
  };

  class Gaps : public Carli::Feature_Ranged<Feature> {
  public:
    enum Axis : size_t {BENEATH = 7, CREATED = 8, DEPTH = 9};

    Gaps(const Axis &axis_, const double &bound_lower_, const double &bound_upper_, const int64_t &depth_, const bool &upper_)
     : Feature_Ranged(Rete::WME_Token_Index(axis_, 2), bound_lower_, bound_upper_, depth_, upper_, true)
    {
    }

    Gaps * clone() const {
      return new Gaps(Axis(axis.first), bound_lower, bound_upper, depth, upper);
    }

    int64_t compare_axis(const Tetris::Feature &rhs) const {
      return -rhs.compare_axis(*this);
    }
    int64_t compare_axis(const Type &) const {return 1;}
    int64_t compare_axis(const Size &) const {return 1;}
    int64_t compare_axis(const Position &) const {return 1;}
    int64_t compare_axis(const Gaps &rhs) const {
      return Feature_Ranged_Data::compare_axis(rhs);
    }
    int64_t compare_axis(const Clears &) const {return -1;}
    int64_t compare_axis(const X_Odd &) const {return -1;}

    Rete::WME_Token_Index wme_token_index() const {
      return axis;
    }

    void print(ostream &os) const {
      switch(axis.first) {
        case BENEATH: os << "gaps-beneath"; break;
        case CREATED: os << "gaps-created"; break;
        default: abort();
      }

      os << '(' << bound_lower << ',' << bound_upper << ':' << depth << ')';
    }
  };

  class Clears : public Carli::Feature_Ranged<Feature> {
  public:
    enum Axis : size_t {CLEARS = 10, ENABLES = 11, PROHIBITS = 12};

    Clears(const Axis &axis_, const double &bound_lower_, const double &bound_upper_, const int64_t &depth_, const bool &upper_)
     : Feature_Ranged(Rete::WME_Token_Index(axis_, 2), bound_lower_, bound_upper_, depth_, upper_, true)
    {
    }

    Clears * clone() const {
      return new Clears(Axis(axis.first), bound_lower, bound_upper, depth, upper);
    }

    int64_t compare_axis(const Tetris::Feature &rhs) const {
      return -rhs.compare_axis(*this);
    }
    int64_t compare_axis(const Type &) const {return 1;}
    int64_t compare_axis(const Size &) const {return 1;}
    int64_t compare_axis(const Position &) const {return 1;}
    int64_t compare_axis(const Gaps &) const {return 1;}
    int64_t compare_axis(const Clears &rhs) const {
      return Feature_Ranged_Data::compare_axis(rhs);
    }
    int64_t compare_axis(const X_Odd &) const {return -1;}

    Rete::WME_Token_Index wme_token_index() const {
      return axis;
    }

    void print(ostream &os) const {
      switch(axis.first) {
        case CLEARS: os << "clears"; break;
        case ENABLES: os << "enables-clearing"; break;
        case PROHIBITS: os << "prohibits-clearing"; break;
        default: abort();
      }

      os << '(' << bound_lower << ',' << bound_upper << ':' << depth << ')';
    }
  };

  class X_Odd : public Carli::Feature_Enumerated<Feature> {
  public:
    enum Axis : size_t {AXIS = 13};

    X_Odd(const bool &value_)
     : Feature_Enumerated<Feature>(value_)
    {
    }

    X_Odd * clone() const {
      return new X_Odd(value != 0);
    }

    int64_t compare_axis(const Feature &rhs) const {
      return -rhs.compare_axis(*this);
    }
    int64_t compare_axis(const Type &) const {return -1;}
    int64_t compare_axis(const Size &) const {return -1;}
    int64_t compare_axis(const Position &) const {return -1;}
    int64_t compare_axis(const Gaps &) const {return -1;}
    int64_t compare_axis(const Clears &) const {return -1;}
    int64_t compare_axis(const X_Odd &) const {
      return 0;
    }

    Rete::WME_Token_Index wme_token_index() const {
      return Rete::WME_Token_Index(AXIS, 2);
    }

    void print(ostream &os) const {
      os << "x-odd(" << (value ? "true" : "false") << ')';
    }
  };

  class Place : public Carli::Action {
  public:
    Place()
     : type(TET_SQUARE)
    {
    }

    Place(const std::pair<int16_t, int16_t> &position_, const Tetromino_Type &type_)
     : position(position_),
     type(type_)
    {
    }

    Place(const Rete::WME_Token &token)
     : position(int16_t(debuggable_cast<const Rete::Symbol_Constant_Int &>(*token[Rete::WME_Token_Index(Position::X, 2)]).value),
                int16_t(debuggable_cast<const Rete::Symbol_Constant_Int &>(*token[Rete::WME_Token_Index(Position::Y, 2)]).value)),
     type(Tetromino_Type(debuggable_cast<const Rete::Symbol_Constant_Int &>(*token[Rete::WME_Token_Index(Type::CURRENT, 2)]).value))
    {
    }

    Place * clone() const {
      return new Place(position, type);
    }

    int64_t compare(const Action &rhs) const {
      return compare(debuggable_cast<const Place &>(rhs));
    }

    int64_t compare(const Place &rhs) const {
      return position.first != rhs.position.first ? position.first - rhs.position.first :
             position.second != rhs.position.second ? position.second - rhs.position.second :
             type - rhs.type;
    }

    void print_impl(ostream &os) const {
      os << "place(" << position.first << ',' << position.second << ':' << type << ')';
    }

    std::pair<int16_t, int16_t> position;
    Tetromino_Type type;
  };

  class Environment : public Carli::Environment {
  public:
    enum class Outcome {OUTCOME_NULL, OUTCOME_ACHIEVED, OUTCOME_ENABLED, OUTCOME_PROHIBITED};

    struct Placement {
      Placement(const Tetromino_Type &type_,
                const std::pair<int16_t, int16_t> &size_,
                const std::pair<int16_t, int16_t> &position_,
                const int16_t &gaps_beneath_,
                const int16_t &gaps_created_,
                const int16_t &depth_to_gap_,
                const Outcome &outcome_1,
                const Outcome &outcome_2,
                const Outcome &outcome_3,
                const Outcome &outcome_4)
       : type(type_),
       size(size_),
       position(position_),
       gaps_beneath(gaps_beneath_),
       gaps_created(gaps_created_),
       depth_to_gap(depth_to_gap_),
       outcome({{Outcome::OUTCOME_NULL, outcome_1, outcome_2, outcome_3, outcome_4}})
      {
      }

      Tetromino_Type type;
      std::pair<int16_t, int16_t> size;
      std::pair<int16_t, int16_t> position;
      int16_t gaps_beneath;
      int16_t gaps_created;
      int16_t depth_to_gap;
      std::array<Outcome, 5> outcome;
    };
    typedef std::list<Placement, Zeni::Pool_Allocator<Placement>> Placements;

    const std::array<double, 5> score_line = {{0.0, 10.0, 20.0, 30.0, 40.0}}; ///< No risk-reward tradeoff
//    const std::array<double, 5> score_line = {{0.0, 10.0, 20.0, 40.0, 80.0}}; ///< Risk-reward tradeoff
    const double score_failure = 0.0;

    Environment();

    Environment(const Environment &rhs); ///< Non-conformant copy constructor ignores m_placements
    Environment & operator=(const Environment &rhs); ///< Non-conformant copy operator ignores m_placements

    Tetromino_Supertype get_current() const {return m_current;}
    Tetromino_Supertype get_next() const {return m_next;}

    const Placements & get_placements() const {return m_placements;}

  private:
    enum Result {PLACE_ILLEGAL, PLACE_GROUNDED, PLACE_UNGROUNDED};

    struct Tetromino : public std::array<std::pair<uint8_t, uint8_t>, 4> {
      uint8_t width;
      uint8_t height;
    };

    void init_impl();

    reward_type transition_impl(const Carli::Action &action);
    void place_Tetromino(const Tetromino &tet, const std::pair<int16_t, int16_t> &position);

    void print_impl(ostream &os) const;

    static Tetromino generate_Tetromino(const Tetromino_Type &type);
    uint8_t clear_lines(const std::pair<int16_t, int16_t> &position);

    int16_t gaps_beneath(const Tetromino &tet, const std::pair<int16_t, int16_t> &position) const;
    int16_t gaps_created(const Tetromino &tet, const std::pair<int16_t, int16_t> &position) const;
    int16_t depth_to_highest_gap() const;
    Outcome outcome(const uint8_t &lines_cleared, const Tetromino &tet, const std::pair<int16_t, int16_t> &position) const;

    Zeni::Random m_random_init;
    Zeni::Random m_random_selection;

    std::array<std::pair<std::array<bool, 10>, int16_t>, 20> m_grid;
    Tetromino_Supertype m_current;
    Tetromino_Supertype m_next;

    void generate_placements();
    Placements m_placements;

    bool m_lookahead = false;
  };

  class Agent : public Carli::Agent {
  public:
    Agent(const std::shared_ptr<Carli::Environment> &env);
    ~Agent();

  private:
    template<typename SUBFEATURE, typename AXIS>
    void generate_rete_continuous(const Carli::Node_Unsplit_Ptr &node_unsplit,
                                  const std::function<action_ptrsc(const Rete::WME_Token &token)> &get_action,
                                  const AXIS &axis,
                                  const double &lower_bound,
                                  const double &upper_bound);
    void generate_rete();

    void generate_features();

    void update();

    const Rete::Symbol_Variable_Ptr_C m_first_var = Rete::Symbol_Variable_Ptr_C(new Rete::Symbol_Variable(Rete::Symbol_Variable::First));
    const Rete::Symbol_Variable_Ptr_C m_third_var = Rete::Symbol_Variable_Ptr_C(new Rete::Symbol_Variable(Rete::Symbol_Variable::Third));

    const Rete::Symbol_Identifier_Ptr_C m_input_id = Rete::Symbol_Identifier_Ptr_C(new Rete::Symbol_Identifier("I1"));
    const Rete::Symbol_Constant_String_Ptr_C m_input_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("input"));
    const Rete::Symbol_Constant_String_Ptr_C m_action_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("action"));
    const Rete::Symbol_Constant_String_Ptr_C m_type_current_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("type-current"));
    const Rete::Symbol_Constant_String_Ptr_C m_type_next_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("type-next"));
    const Rete::Symbol_Constant_String_Ptr_C m_width_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("width"));
    const Rete::Symbol_Constant_String_Ptr_C m_height_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("height"));
    const Rete::Symbol_Constant_String_Ptr_C m_x_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("x"));
    const Rete::Symbol_Constant_String_Ptr_C m_y_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("y"));
    const Rete::Symbol_Constant_String_Ptr_C m_gaps_beneath_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("gaps-beneath"));
    const Rete::Symbol_Constant_String_Ptr_C m_gaps_created_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("gaps-created"));
    const Rete::Symbol_Constant_String_Ptr_C m_depth_to_gap_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("depth-to-gap")); ///< Depth to the highest gap
    const Rete::Symbol_Constant_String_Ptr_C m_clears_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("clears"));
    const Rete::Symbol_Constant_String_Ptr_C m_enables_clearing_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("enables-clearing"));
    const Rete::Symbol_Constant_String_Ptr_C m_prohibits_clearing_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("prohibits-clearing"));
    const Rete::Symbol_Constant_String_Ptr_C m_x_odd_attr = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("x-odd"));
    const Rete::Symbol_Constant_String_Ptr_C m_true_value = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("true"));
    const Rete::Symbol_Constant_String_Ptr_C m_false_value = Rete::Symbol_Constant_String_Ptr_C(new Rete::Symbol_Constant_String("false"));

    std::list<Rete::WME_Ptr_C> m_wmes_prev;
  };

}

std::ostream & operator<<(std::ostream &os, const Tetris::Tetromino_Type &type) {
  switch(type) {
    case Tetris::TET_SQUARE:     os << "O";     break;

    case Tetris::TET_LINE_DOWN:  os << "I";     break;
    case Tetris::TET_LINE_RIGHT: os << "I_90";  break;

    case Tetris::TET_T:          os << "T";     break;
    case Tetris::TET_T_90:       os << "T_90";  break;
    case Tetris::TET_T_180:      os << "T_180"; break;
    case Tetris::TET_T_270:      os << "T";     break;

    case Tetris::TET_L:          os << "L";     break;
    case Tetris::TET_L_90:       os << "L_90";  break;
    case Tetris::TET_L_180:      os << "L_180"; break;
    case Tetris::TET_L_270:      os << "L_270"; break;

    case Tetris::TET_J:          os << "J";     break;
    case Tetris::TET_J_90:       os << "J_90";  break;
    case Tetris::TET_J_180:      os << "J_180"; break;
    case Tetris::TET_J_270:      os << "J_270"; break;

    case Tetris::TET_S:          os << "S";     break;
    case Tetris::TET_S_90:       os << "S_90";  break;

    case Tetris::TET_Z:          os << "Z";     break;
    case Tetris::TET_Z_90:       os << "Z_90";  break;

    default: abort();
  }

  return os;
}

#endif