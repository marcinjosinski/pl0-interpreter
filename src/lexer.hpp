#ifndef PL0_LEXER_HPP
#define PL0_LEXER_HPP

#include "token.hpp"
#include "utils.hpp"
#include <algorithm>
#include <map>

namespace pl0::lexer {

class lexer {
public:
  lexer(std::string buffer) noexcept
      : buffer_{std::move(buffer)}, cursor_{buffer_.c_str()},
        end_{cursor_ + buffer_.length()} {
    std::transform(buffer_.begin(), buffer_.end(), buffer_.begin(), ::tolower);
  }

  token current_token;
  void match(token_type type);
  token get_next_token();
  char peek(int n = 1) const noexcept;

private:
  std::string buffer_;
  const char *cursor_;
  const char *end_;
  token scan_token_();
  token scan_identifier_() noexcept;
  token scan_integer_() noexcept;
  void advance_(int n = 1) noexcept;
  void skip_whitespaces_() noexcept;
};
} // namespace pl0::lexer

#endif