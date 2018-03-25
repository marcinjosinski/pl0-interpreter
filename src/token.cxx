#include "token.hpp"
#include "utils.hpp"
#include <string>

namespace pl0::lexer {
namespace {
constexpr const char *token_type_names[]{
    "odd",        "equal",         "not_equal",   "less_equal", "less",
    "greater",    "greater_equal", "integer",     "real",       "plus",
    "minus",      "mul",           "div",         "lparen",     "rparen",
    "identifier", "eof",           "unary minus", "unary plus", "program",
    "id",         "empty",         "assign",      "write",      "if cond",
    "if then",    "while cond",    "while do",    "begin",      "end",
    "semicolon",  "call",          "read",        "const",      "var",
    "procedure",  "comma"};
}

bool token::is_one_of(std::initializer_list<token_type> ilist) const noexcept {
  for (const auto &tok_type : ilist)
    if (is(tok_type))
      return true;

  return false;
}

bool token::is(token_type type) const noexcept { return get_type() == type; }

bool token::is_one_of(token_type t1, token_type t2) const noexcept {
  return is(t1) || is(t2);
}

std::string_view token::get_lexeme() const noexcept { return lexeme_; }

token_type token::get_type() const noexcept { return type_; }

std::string token::get_name() const {
  return token_type_names[static_cast<int>(get_type())];
}

int token::get_integer() const {
  if (is(token_type::integer))
    return std::atoi(std::string{get_lexeme()}.c_str());
  else
    throw utils::error{"Cannot cast token lexeme to int"};
}

std::ostream &operator<<(std::ostream &os, const token &tok) {
  std::ostringstream sstr;
  sstr << "token{type:" << tok.get_name() << ", lexeme:\'" << tok.get_lexeme()
       << "\'}";
  return os << sstr.str();
}

} // namespace pl0::lexer
