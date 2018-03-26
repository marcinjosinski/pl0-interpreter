#ifndef PL0_SCOPE_HPP
#define PL0_SCOPE_HPP

#include <memory>
#include <string_view>
#include <unordered_map>

#include "identifier_info.hpp"
#include "utils.hpp"

namespace pl0::scope {

using symbol_table = std::unordered_map<std::string_view, ident_info_ptr>;

class scope {
public:
  scope &operator=(const scope &) = default;
  scope(const scope &) = default;
  scope(std::string_view name = "",
        std::shared_ptr<scope> enclosing_scope = nullptr)
      : name_{std::move(name)}, enclosing_scope_{std::move(enclosing_scope)},
        level_(enclosing_scope_ ? enclosing_scope_->level_ + 1 : 0) {}

  std::string_view get_scope_name() const { return name_; }

  std::shared_ptr<scope> get_enclosing_scope() { return enclosing_scope_; }

  void define(ident_info_ptr symbol) {
    auto result = memory_.emplace(symbol->get_name(), std::move(symbol));
    if (!result.second)
      throw utils::error{"Fail define symbol"};
  }

  identifier_info::ident_info *resolve(std::string_view name) {
    auto iter = memory_.find(name);
    if (iter == memory_.end()) {
      return enclosing_scope_ ? enclosing_scope_->resolve(name) : nullptr;
    }
    return iter->second.get();
  }

  int get_level() const { return level_; }

public:
  symbol_table memory_;
  std::string_view name_;
  std::shared_ptr<scope> enclosing_scope_;
  int level_;
};
} // namespace pl0::scope

#endif