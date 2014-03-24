#ifndef RETE_NEGATION_JOIN_H
#define RETE_NEGATION_JOIN_H

#include "rete_node.h"

namespace Rete {

  class RETE_LINKAGE Rete_Negation_Join : public Rete_Node {
    Rete_Negation_Join(const Rete_Negation_Join &);
    Rete_Negation_Join & operator=(const Rete_Negation_Join &);

    friend void bind_to_negation_join(const Rete_Negation_Join_Ptr &join, const Rete_Node_Ptr &out0, const Rete_Node_Ptr &out1);

  public:
    Rete_Negation_Join(WME_Bindings bindings_);

    void destroy(Filters &filters, const Rete_Node_Ptr &output);

    Rete_Node_Ptr_C parent() const {return input0->shared();}
    Rete_Node_Ptr parent() {return input0->shared();}

    void insert_wme_token(const WME_Token_Ptr_C &wme_token, const Rete_Node * const &from);
    bool remove_wme_token(const WME_Token_Ptr_C &wme_token, const Rete_Node * const &from);

    bool operator==(const Rete_Node &rhs) const;

    static Rete_Negation_Join_Ptr find_existing(const WME_Bindings &bindings, const Rete_Node_Ptr &out0, const Rete_Node_Ptr &out1);

    void output_name(std::ostream &os) const;

  private:
    void join_tokens(std::pair<WME_Token_Ptr_C, size_t> &lhs, const WME_Token_Ptr_C &rhs);
    void unjoin_tokens(std::pair<WME_Token_Ptr_C, size_t> &lhs, const WME_Token_Ptr_C &rhs);

    void disconnect(const Rete_Node * const &from);

    void pass_tokens(const Rete_Node_Ptr &output);
    void unpass_tokens(const Rete_Node_Ptr &output);

    WME_Bindings bindings;
    Rete_Node * input0 = nullptr;
    Rete_Node * input1 = nullptr;
    std::list<std::pair<WME_Token_Ptr_C, size_t>, Zeni::Pool_Allocator<std::pair<WME_Token_Ptr_C, size_t>>> input0_tokens;
    std::list<WME_Token_Ptr_C, Zeni::Pool_Allocator<WME_Token_Ptr_C>> input1_tokens;

    struct {
      bool connected0 : 1;
      bool connected1 : 1;
    } data = {true, false};
  };

  RETE_LINKAGE void bind_to_negation_join(const Rete_Negation_Join_Ptr &join, const Rete_Node_Ptr &out0, const Rete_Node_Ptr &out1);

}

#endif
