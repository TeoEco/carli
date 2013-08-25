#include "rete_negation_join.h"

#include "rete_existential.h"
#include "rete_negation.h"

namespace Rete {

  Rete_Negation_Join::Rete_Negation_Join(WME_Bindings bindings_) : bindings(bindings_) {}

  void Rete_Negation_Join::destroy(Filters &filters, const Rete_Node_Ptr &output) {
    erase_output(output);
    if(outputs.empty()) {
      auto i0 = input0;
      auto i1 = input1;
      i0->destroy(filters, shared());
      if(i0 != i1)
        i1->destroy(filters, shared());
    }
  }

  void Rete_Negation_Join::insert_wme_token(const WME_Token_Ptr_C &wme_token, const Rete_Node * const &from) {
    assert(from == input0 || from == input1);

    if(from == input0) {
      input0_tokens.emplace_back(wme_token, 0u);

      if(++input0_count == 1u && input0 != input1) {
        input1->insert_output(shared());
        input1->pass_tokens(shared());
      }
      else {
        for(const auto &other : input1_tokens)
          join_tokens(input0_tokens.back(), other);
      }

      if(input0_tokens.back().second == 0u) {
        for(auto &output : outputs)
          output->insert_wme_token(wme_token, this);
      }
    }
    if(from == input1) {
      input1_tokens.push_back(wme_token);

      for(auto &other : input0_tokens)
        join_tokens(other, wme_token);
    }
  }

  void Rete_Negation_Join::remove_wme_token(const WME_Token_Ptr_C &wme_token, const Rete_Node * const &from) {
    assert(from == input0 || from == input1);

    if(from == input0) {
      auto found = find_key(input0_tokens, wme_token);
      if(found != input0_tokens.end()) {
        if(found->second == 0u) {
          for(auto &output : outputs)
            output->remove_wme_token(wme_token, this);
        }
        input0_tokens.erase(found);

        if(--input0_count == 0u && input0 != input1) {
          input1->unpass_tokens(shared());
          input1->erase_output(shared());
        }
      }
    }
    if(from == input1) {
      auto found = find(input1_tokens, wme_token);
      if(found != input1_tokens.end()) {
        // TODO: Avoid looping through non-existent pairs?
        input1_tokens.erase(found);
        for(auto &other : input0_tokens)
          unjoin_tokens(other, wme_token);
      }
    }
  }

  bool Rete_Negation_Join::operator==(const Rete_Node &rhs) const {
    if(auto join = dynamic_cast<const Rete_Negation_Join *>(&rhs))
      return bindings == join->bindings && input0 == join->input0 && input1 == join->input1;
    return false;
  }

  Rete_Negation_Join_Ptr Rete_Negation_Join::find_existing(const WME_Bindings &bindings, const Rete_Node_Ptr &out0, const Rete_Node_Ptr &out1) {
    for(auto &o0 : out0->get_outputs()) {
      if(auto existing_negation_join = std::dynamic_pointer_cast<Rete_Negation_Join>(o0)) {
        if(std::find(out1->get_outputs().begin(), out1->get_outputs().end(), existing_negation_join) != out1->get_outputs().end()) {
          if(bindings == existing_negation_join->bindings)
            return existing_negation_join;
        }
      }
    }

    return nullptr;
  }

  void Rete_Negation_Join::join_tokens(std::pair<WME_Token_Ptr_C, size_t> &lhs, const WME_Token_Ptr_C &rhs) {
    for(auto &binding : bindings) {
      if(*(*lhs.first)[binding.first] != *(*rhs)[binding.second])
        return;
    }

    if(++lhs.second == 1) {
      for(auto &output : outputs)
        output->remove_wme_token(lhs.first, this);
    }
  }

  void Rete_Negation_Join::unjoin_tokens(std::pair<WME_Token_Ptr_C, size_t> &lhs, const WME_Token_Ptr_C &rhs) {
    for(auto &binding : bindings) {
      if(*(*lhs.first)[binding.first] != *(*rhs)[binding.second])
        return;
    }

    if(--lhs.second == 0) {
      for(auto &output : outputs)
        output->insert_wme_token(lhs.first, this);
    }
  }

  void Rete_Negation_Join::pass_tokens(const Rete_Node_Ptr &output) {
    if(is_iterating())
      return;
    for(auto &wme_token : input0_tokens) {
      if(!wme_token.second)
        output->insert_wme_token(wme_token.first, this);
    }
  }

  void Rete_Negation_Join::unpass_tokens(const Rete_Node_Ptr &output) {
    if(is_iterating())
      return;
    for(auto &wme_token : input0_tokens) {
      if(!wme_token.second)
        output->remove_wme_token(wme_token.first, this);
    }
  }

  void bind_to_negation_join(const Rete_Negation_Join_Ptr &join, const Rete_Node_Ptr &out0, const Rete_Node_Ptr &out1) {
    assert(join && !join->input0 && !join->input1);
    assert(!std::dynamic_pointer_cast<Rete_Existential>(out0));
    assert(!std::dynamic_pointer_cast<Rete_Negation>(out0));
    join->input0 = out0.get();
    join->input1 = out1.get();

    out0->insert_output(join);
    out0->pass_tokens(join);
    if(out0 != out1) {
      out1->insert_output(join);
      out1->pass_tokens(join);
    }
  }

}
