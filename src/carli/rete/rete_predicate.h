#ifndef RETE_PREDICATE_H
#define RETE_PREDICATE_H

#include "rete_node.h"

namespace Rete {

  class Rete_Predicate : public Rete_Node {
    Rete_Predicate(const Rete_Predicate &);
    Rete_Predicate & operator=(const Rete_Predicate &);

    friend void bind_to_predicate(const Rete_Predicate_Ptr &predicate, const Rete_Node_Ptr &out);

  public:
    enum Predicate {EQ, NEQ, GT, GTE, LT, LTE};

    Rete_Predicate(const Predicate &predicate_, const WME_Token_Index lhs_index_, const WME_Token_Index rhs_index_);
    Rete_Predicate(const Predicate &predicate_, const WME_Token_Index lhs_index_, const Symbol_Ptr_C &rhs_);

    void destroy(Filters &filters, const Rete_Node_Ptr &output);

    void insert_wme_token(const WME_Token_Ptr_C &wme_token, const Rete_Node_Ptr_C &from);
    void remove_wme_token(const WME_Token_Ptr_C &wme_token, const Rete_Node_Ptr_C &from);

    void pass_tokens(const Rete_Node_Ptr &output);

    bool operator==(const Rete_Node &rhs) const;

    static Rete_Predicate_Ptr find_existing(const Predicate &predicate, const WME_Token_Index &lhs_index, const WME_Token_Index &rhs_index, const Rete_Node_Ptr &out);
    static Rete_Predicate_Ptr find_existing(const Predicate &predicate, const WME_Token_Index &lhs_index, const Symbol_Ptr_C &rhs, const Rete_Node_Ptr &out);

  private:
    bool test_predicate(const Symbol_Ptr_C &lhs, const Symbol_Ptr_C &rhs) const;

    Predicate m_predicate;
    WME_Token_Index m_lhs_index;
    WME_Token_Index m_rhs_index;
    Symbol_Ptr_C m_rhs;
    std::weak_ptr<Rete_Node> input;
    std::list<WME_Token_Ptr_C, Zeni::Pool_Allocator<WME_Token_Ptr_C>> tokens;
  };

  void bind_to_predicate(const Rete_Predicate_Ptr &predicate, const Rete_Node_Ptr &out);

}

#endif
