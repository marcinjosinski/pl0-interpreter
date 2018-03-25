#ifndef PL0_TOKEN_HPP
#define PL0_TOKEN_HPP
#include <initializer_list>
#include <sstream>
#include <string>
#include <string_view>

namespace pl0::lexer {
enum class token_type {
  equal,
  not_equal,
  less_equal,
  less,
  greater,
  greater_equal,
  odd,
  integer,
  real,
  plus,
  minus,
  mul,
  div,
  lparen,
  rparen,
  identifier,
  eof,
  unary_minus,
  unary_plus,
  program,
  id,
  empty,
  assign,
  write,
  if_cond,
  if_then,
  while_cond,
  while_do,
  begin,
  end,
  semicolon,
  call,
  read,
  constant,
  var,
  procedure,
  comma,
};

class token {
public:
  explicit token(token_type type, std::string_view lexeme) noexcept
      : type_{type}, lexeme_{std::move(lexeme)} {}

  token() = default;
  token(const token &) = default;
  token &operator=(const token &) = default;
  token(token &&) noexcept = default;
  token &operator=(token &&) noexcept = default;

  [[nodiscard]] bool is(token_type type) const noexcept;

  [[nodiscard]] bool is_one_of(token_type t1, token_type t2) const noexcept;
  [[nodiscard]] bool is_one_of(std::initializer_list<token_type> ilist) const
      noexcept;

  template <typename... Ts>
  [[nodiscard]] bool is_one_of(token_type t1, token_type t2, Ts... ts) const
      noexcept {
    static_assert((std::is_same_v<token_type, Ts> && ...),
                  "Invalid token type.");
    return is(t1) || is_one_of(t2, ts...);
  }

  std::string_view get_lexeme() const noexcept;
  token_type get_type() const noexcept;

  std::string get_name() const;
  int get_integer() const;

private:
  token_type type_;
  std::string_view lexeme_;
};

std::ostream &operator<<(std::ostream &, const token &);

} // namespace pl0::lexer

#endif