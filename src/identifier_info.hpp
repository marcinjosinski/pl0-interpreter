#ifndef PL0_IDENTIFIER_INFO_HPP
#define PL0_IDENTIFIER_INFO_HPP

#include <string_view>
#include <memory>

namespace pl0::identifier_info {

enum class ident_type { variable, procedure, constant };

class identifier_info {
public:
  identifier_info(std::string_view name, ident_type t)
     : name_{std::move(name)}, type_{t} {}

  std::string_view get_name() const noexcept { return name_; }
  bool is(ident_type t) const noexcept { return type_ == t; }

  virtual ~identifier_info() = default;

private:
  ident_type type_;
  std::string_view name_;
};

// symbols

class variable_symbol : public identifier_info {
public:
  variable_symbol(std::string_view name, int value)
      : identifier_info{name, ident_type::variable}, value_{value} {}
  int get_value() const { return value_; }
  void set_value(int value) { value_ = value; }

private:
  int value_;
};

class procedure_symbol : public identifier_info {
public:
  procedure_symbol(std::string_view name, int level)
      : identifier_info{name, ident_type::procedure}, level_{level} {}
  int get_level() const { return level_; }

private:
  int level_;
};
} // namespace pl0::identifier_info

using identifier_info_ptr = std::unique_ptr<pl0::identifier_info::identifier_info>;


#endif