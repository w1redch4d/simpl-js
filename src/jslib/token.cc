#include <string.h>
#include "token.h"

namespace jslib {
namespace internal {
#define T(name, string, precedence) #name,
const char* const Token::name_[NUM_TOKENS] = {TOKEN_LIST(T, T)};
#undef T

#define T(name, string, precedence) string,
const char* const Token::string_[NUM_TOKENS] = {TOKEN_LIST(T, T)};
#undef T

constexpr uint8_t length(const char* str) {
  return str ? static_cast<uint8_t>(strlen(str)) : 0;
}
#define T(name, string, precedence) length(string),
const uint8_t Token::string_length_[NUM_TOKENS] = {TOKEN_LIST(T, T)};
#undef T

#define T1(name, string, precedence) \
  ((Token::name == Token::IN) ? 0 : precedence),
#define T2(name, string, precedence) precedence,
// precedence_[0] for accept_IN == false, precedence_[1] for accept_IN = true.
const int8_t Token::precedence_[2][NUM_TOKENS] = {{TOKEN_LIST(T1, T1)},
                                                  {TOKEN_LIST(T2, T2)}};
#undef T2
#undef T1
}
}