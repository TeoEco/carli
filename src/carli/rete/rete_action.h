#ifndef RETE_ACTION_H
#define RETE_ACTION_H

#include "agenda.h"
#include "rete_node.h"

namespace Rete {

  class Rete_Action : public Rete_Node {
    Rete_Action(const Rete_Action &);
    Rete_Action & operator=(const Rete_Action &);

    friend void bind_to_action(const Rete_Action_Ptr &action, const Rete_Node_Ptr &out);
    friend class Rete_Action_to_Agenda;

  public:
    typedef std::function<void (const Rete_Action &rete_action, const WME_Token &wme_token)> Action;

    Rete_Action(Agenda &agenda_,
                const Action &action_ = [](const Rete_Action &, const WME_Token &){},
                const Action &retraction_ = [](const Rete_Action &, const WME_Token &){});

    ~Rete_Action();

    void destroy(Filters &filters, const Rete_Node_Ptr &output = Rete_Node_Ptr());

    Rete_Node_Ptr_C parent() const {return input->shared();}
    Rete_Node_Ptr parent() {return input->shared();}

    void insert_wme_token(const WME_Token_Ptr_C &wme_token, const Rete_Node * const &from);
    bool remove_wme_token(const WME_Token_Ptr_C &wme_token, const Rete_Node * const &from);

    void pass_tokens(const Rete_Node_Ptr &);
    void unpass_tokens(const Rete_Node_Ptr &);

    bool operator==(const Rete_Node &/*rhs*/) const;

    static Rete_Action_Ptr find_existing(const Action &/*action_*/, const Action &/*retraction_*/, const Rete_Node_Ptr &/*out*/);

    std::string generate_name() const;

    void set_action(const Action &action_) {
      action = action_;
    }

    void set_retraction(const Action &retraction_) {
      retraction = retraction_;
    }

  private:
    Rete_Node * input = nullptr;
    std::list<WME_Token_Ptr_C, Zeni::Pool_Allocator<WME_Token_Ptr_C>> input_tokens;
    Action action;
    Action retraction;
    Agenda &agenda;
  };

  void bind_to_action(const Rete_Action_Ptr &action, const Rete_Node_Ptr &out);

  class Rete_Action_to_Agenda {
    friend class Agenda;

    static const Rete_Action::Action & action(const Rete_Action &rete_action) {
      return rete_action.action;
    }

    static const Rete_Action::Action & retraction(const Rete_Action &rete_action) {
      return rete_action.retraction;
    }
  };

}

#endif
