#ifndef PL0_UTILS_HPP
#define PL0_UTILS_HPP

namespace pl0::utils {
struct error {
  explicit error(const char *m) : func{m} {};
  const char *func;
};
} // namespace pl0::utils

#endif