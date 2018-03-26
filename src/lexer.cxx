#include <iostream>

#include "lexer.hpp"
namespace pl0::lexer {

namespace {

using namespace pl0::lexer;
using namespace std::literals::string_view_literals;

std::map<std::string_view, token, std::less<>> reserved_keywords = {
    {"odd"sv, token{token_type::odd, "odd"}},
    {"if"sv, token{token_type::if_cond, "if"}},
    {"then"sv, token{token_type::if_then, "then"}},
    {"while"sv, token{token_type::while_cond, "while"}},
    {"begin"sv, token{token_type::begin, "begin"}},
    {"end"sv, token{token_type::end, "end"}},
    {"call"sv, token{token_type::call, "call"}},
    {"const"sv, token{token_type::constant, "const"}},
    {"var"sv, token{token_type::var, "var"}},
    {"procedure"sv, token{token_type::procedure, "procedure"}},
    {"do"sv, token{token_type::while_do, "do"}}};

} // namespace

char lexer::peek(int n) const noexcept {
  return *(cursor_ + n);
}

token lexer::scan_identifier_() noexcept {
  auto start_ident = cursor_++;

  while (cursor_ != end_ && (std::isalnum(*cursor_) || *cursor_ == '_'))
    advance_();

  std::string_view result{start_ident, static_cast<std::size_t>(std::distance(
                                           start_ident, cursor_))};

  if (reserved_keywords.find(result) != reserved_keywords.end())
    return reserved_keywords[result];
  else
    return token{token_type::identifier, result};
}

token lexer::scan_integer_() noexcept {
  auto start_int = cursor_;

  while (std::isdigit(*cursor_))
    advance_();
  return token{
      token_type::integer,
      std::string_view{start_int, static_cast<std::size_t>(
                                      std::distance(start_int, cursor_))}};
}

void lexer::advance_(int n) noexcept { std::advance(cursor_, n); }

token lexer::get_next_token() {
  current_token = scan_token_();
  return current_token;
}

void lexer::match(token_type type) {
  std::cout << current_token << "\n";
  if (current_token.get_type() == type) {
    current_token = scan_token_();
  } else {
    throw pl0::utils::error{"Match fail. Add here more info about tokens?"};
  }
}

token lexer::scan_token_() {

  skip_whitespaces_();

  if (cursor_ >= end_)
    return token{token_type::eof, 0};

  if (std::isalpha(*cursor_))
    return scan_identifier_();

  switch (*cursor_) {
  case '!':
    advance_();
    return token{token_type::write, "!"};
  case '<':
    advance_();
    if(*cursor_ == '=') {
      advance_();
      return token{token_type::less_equal, "<="};
    }
    return token{token_type::less, "<"};
  case ',':
    advance_();
    return token{token_type::comma, ","};
  case '>':
    advance_();
    if(*cursor_ == '=') {
      advance_();
      return token{token_type::greater_equal, ">="};
    }
    return token{token_type::greater, ">"};
  case '=':
    advance_();
    return token{token_type::equal, "="};
  case ';':
    advance_();
    return token{token_type::semicolon, ";"};
  case '#':
    advance_();
    return token{token_type::not_equal, "#"};
  case '?':
    advance_();
    return token{token_type::read, "?"};
  case ':': {
    if(peek() == '=') {
      advance_(2);
      return token{token_type::assign, ":="};
    }
    break;
  }
  case '(':
    advance_();
    return token{token_type::lparen, "("};
  case ')':
    advance_();
    return token{token_type::rparen, ")"};
  case '/':
    advance_();
    return token{token_type::div, "/"};
  case '*':
    advance_();
    return token{token_type::mul, "*"};
  case '+':
    advance_();
    return token{token_type::plus, "+"};
  case '-':
    advance_();
    return token{token_type::minus, "-"};
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    return scan_integer_();
  }
  throw pl0::utils::error{"Unknown token."};
}

void lexer::skip_whitespaces_() noexcept {
  for (;;) {
    if (*cursor_ != ' ' && *cursor_ != '\n' && *cursor_ != '\t')
      break;
    advance_();
  }
}

} // namespace pl0::lexer
