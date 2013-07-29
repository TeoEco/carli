#ifndef RETE_NODE_H
#define RETE_NODE_H

#include "wme_token.h"

#include <algorithm>
#include <cassert>
#include <functional>
#include <list>

namespace Rete {

  class Rete_Action;
  class Rete_Existential;
  class Rete_Existential_Join;
  class Rete_Filter;
  class Rete_Join;
  class Rete_Negation;
  class Rete_Negation_Join;
  class Rete_Node;
  class Rete_Predicate;

  typedef std::shared_ptr<const Rete_Action> Rete_Action_Ptr_C;
  typedef std::shared_ptr<const Rete_Existential> Rete_Existential_Ptr_C;
  typedef std::shared_ptr<const Rete_Existential_Join> Rete_Existential_Join_Ptr_C;
  typedef std::shared_ptr<const Rete_Filter> Rete_Filter_Ptr_C;
  typedef std::shared_ptr<const Rete_Join> Rete_Join_Ptr_C;
  typedef std::shared_ptr<const Rete_Negation> Rete_Negation_Ptr_C;
  typedef std::shared_ptr<const Rete_Negation_Join> Rete_Negation_Join_Ptr_C;
  typedef std::shared_ptr<const Rete_Node> Rete_Node_Ptr_C;
  typedef std::shared_ptr<const Rete_Predicate> Rete_Predicate_Ptr_C;

  typedef std::shared_ptr<Rete_Action> Rete_Action_Ptr;
  typedef std::shared_ptr<Rete_Existential> Rete_Existential_Ptr;
  typedef std::shared_ptr<Rete_Existential_Join> Rete_Existential_Join_Ptr;
  typedef std::shared_ptr<Rete_Filter> Rete_Filter_Ptr;
  typedef std::shared_ptr<Rete_Join> Rete_Join_Ptr;
  typedef std::shared_ptr<Rete_Negation> Rete_Negation_Ptr;
  typedef std::shared_ptr<Rete_Negation_Join> Rete_Negation_Join_Ptr;
  typedef std::shared_ptr<Rete_Node> Rete_Node_Ptr;
  typedef std::shared_ptr<Rete_Predicate> Rete_Predicate_Ptr;

  class Rete_Node : public std::enable_shared_from_this<Rete_Node>, public Zeni::Pool_Allocator<Rete_Existential_Join> {
    Rete_Node(const Rete_Node &);
    Rete_Node & operator=(const Rete_Node &);

    friend void bind_to_action(const Rete_Action_Ptr &action, const Rete_Node_Ptr &out);
    friend void bind_to_existential(const Rete_Existential_Ptr &existential, const Rete_Node_Ptr &out);
    friend void bind_to_existential_join(const Rete_Existential_Join_Ptr &existential_join, const Rete_Node_Ptr &out0, const Rete_Node_Ptr &out1);
    friend void bind_to_join(const Rete_Join_Ptr &join, const Rete_Node_Ptr &out0, const Rete_Node_Ptr &out1);
    friend void bind_to_negation(const Rete_Negation_Ptr &negation, const Rete_Node_Ptr &out);
    friend void bind_to_negation_join(const Rete_Negation_Join_Ptr &negation_join, const Rete_Node_Ptr &out0, const Rete_Node_Ptr &out1);
    friend void bind_to_predicate(const Rete_Predicate_Ptr &predicate, const Rete_Node_Ptr &out);

  public:
    Rete_Node() {}
    virtual ~Rete_Node() {}

    virtual void destroy(std::unordered_set<Rete_Filter_Ptr> &filters, const Rete_Node_Ptr &output) = 0;

    std::shared_ptr<const Rete_Node> shared() const {
      return shared_from_this();
    }
    std::shared_ptr<Rete_Node> shared() {
      return shared_from_this();
    }

    const std::list<Rete_Node_Ptr> & get_outputs() const {
      return outputs;
    }

    virtual void insert_wme_token(const WME_Token_Ptr_C &wme_token, const Rete_Node_Ptr_C &from) = 0;
    virtual void remove_wme_token(const WME_Token_Ptr_C &wme_token, const Rete_Node_Ptr_C &from) = 0;

    virtual void pass_tokens(const Rete_Node_Ptr &output) = 0;

    virtual bool operator==(const Rete_Node &rhs) const = 0;

  protected:
    void erase_output(const Rete_Node_Ptr &output) {
      outputs.erase(std::find(outputs.begin(), outputs.end(), output));
    }

    template<typename CONTAINER>
    typename CONTAINER::iterator find(CONTAINER &tokens, const WME_Token_Ptr_C &token) {
      return tokens.find(token);
//      return std::find(tokens.begin(), tokens.end(), token);
    }

    template<typename CONTAINER>
    typename CONTAINER::iterator find_deref(CONTAINER &tokens, const WME_Token_Ptr_C &token) {
      return tokens.find(token);
//      return std::find_if(tokens.begin(), tokens.end(), [&token](const WME_Token_Ptr_C &tok){return *tok == *token;});
    }

    std::list<Rete_Node_Ptr> outputs;
  };

}

#endif
