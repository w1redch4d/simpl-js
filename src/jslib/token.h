#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifndef JSLIB_TOKEN_H
#define JSLIB_TOKEN_H

#if defined(WIN32)
#if defined(JSLIB_SHARED_IMPLEMENTATION)
#define JSLIB_EXPORT __declspec(dllexport)
#define JSLIB_EXPORT_PRIVATE __declspec(dllexport)
#else
#define JSLIB_EXPORT __declspec(dllimport)
#define JSLIB_EXPORT_PRIVATE __declspec(dllimport)
#endif  // defined(JSLIB_SHARED_IMPLEMENTATION)
#else
#if defined(JSLIB_SHARED_IMPLEMENTATION)
#define JSLIB_EXPORT __attribute__((visibility("default")))
#define JSLIB_EXPORT_PRIVATE __attribute__((visibility("default")))
#else
#define JSLIB_EXPORT
#define JSLIB_EXPORT_PRIVATE
#endif  // defined(JSLIB_SHARED_IMPLEMENTATION)
#endif

namespace jslib {

namespace internal {
        
#define BIN_OPS_TOKEN_LIST(T, E)     \
    E(T, NULLISH, "??", 3)           \
    E(T, OR, "||", 4)                \
    E(T, AND, "&&", 5)               \
    E(T, BIT_OR, "|", 6)             \
    E(T, BIT_XOR, "^", 7)            \
    E(T, BIT_AND, "&", 8)            \
    E(T, SHL, "<<", 11)              \
    E(T, SAR, ">>", 11)              \
    E(T, SHR, ">>>", 11)             \
    E(T, MUL, "*", 13)               \
    E(T, DIV, "/", 13)               \
    E(T, MOD, "%", 13)               \
    E(T, EXP, "**", 14)              

#define UNARY_OPS_TOKEN_LIST(T, E) \
    E(T, ADD, "+", 0)                 \
    E(T, SUB, "-", 0)                 \


#define EXPAND_BINOP_ASSIGN_TOKEN(T, name, string, precedence) T(ASSIGN_##name, string "=", 2)

#define EXPAND_BINOP_TOKEN(T, name, string, precedence) T(name, string, precedence)

/*
T : Non-Keyword Tokens
K: Keyword Tokens
*/
#define TOKEN_LIST(T, K)                                                      \
                                                                              \
  /* BEGIN PropertyOrCall */                                                  \
  /* BEGIN Member */                                                          \
  /* BEGIN Template */                                                        \
  /* ES6 Template Literals */                                                 \
  T(TEMPLATE_SPAN, nullptr, 0)                                                \
  T(TEMPLATE_TAIL, nullptr, 0)                                                \
  /* END Template */                                                          \
                                                                              \
  /* Punctuators (ECMA-262, section 7.7, page 15). */                         \
  /* BEGIN Property */                                                        \
  T(PERIOD, ".", 0)                                                           \
  T(LBRACK, "[", 0)                                                           \
  /* END Property */                                                          \
  /* END Member */                                                            \
  T(QUESTION_PERIOD, "?.", 0)                                                 \
  T(LPAREN, "(", 0)                                                           \
  /* END PropertyOrCall */                                                    \
  T(RPAREN, ")", 0)                                                           \
  T(RBRACK, "]", 0)                                                           \
  T(LBRACE, "{", 0)                                                           \
  T(COLON, ":", 0)                                                            \
  T(ELLIPSIS, "...", 0)                                                       \
  T(CONDITIONAL, "?", 3)                                                      \
  /* BEGIN AutoSemicolon */                                                   \
  T(SEMICOLON, ";", 0)                                                        \
  T(RBRACE, "}", 0)                                                           \
  /* End of source indicator. */                                              \
  T(EOS, "EOS", 0)                                                            \
  /* END AutoSemicolon */                                                     \
                                                                              \
  /* BEGIN ArrowOrAssignmentOp */                                             \
  T(ARROW, "=>", 0)                                                           \
  /* BEGIN AssignmentOp */                                                    \
  /* IsAssignmentOp() relies on this block of enum values being */            \
  /* contiguous and sorted in the same order! */                              \
  T(INIT, "=init", 2) /* AST-use only. */                                     \
  T(ASSIGN, "=", 2)                                                           \
  BIN_OPS_TOKEN_LIST(T, EXPAND_BINOP_ASSIGN_TOKEN)                          \
  /* END AssignmentOp */                                                      \
  /* END ArrowOrAssignmentOp */                                               \
                                                                              \
  /* Binary operators sorted by precedence. */                                \
  /* IsBinaryOp() relies on this block of enum values */                      \
  /* being contiguous and sorted in the same order! */                        \
  T(COMMA, ",", 1)                                                            \
                                                                              \
  /* Unary operators, starting at ADD in UNARY_OPS_TOKEN_LIST  */             \
  /* IsUnaryOp() relies on this block of enum values */                       \
  /* being contiguous and sorted in the same order! */                        \
  UNARY_OPS_TOKEN_LIST(T, EXPAND_BINOP_TOKEN)                                 \
                                                                              \
  T(NOT, "!", 0)                                                              \
  T(BIT_NOT, "~", 0)                                                          \
  K(DELETE, "delete", 0)                                                      \
  K(TYPEOF, "typeof", 0)                                                      \
  K(VOID, "void", 0)                                                          \
                                                                              \
  /* BEGIN IsCountOp */                                                       \
  T(INC, "++", 0)                                                             \
  T(DEC, "--", 0)                                                             \
  /* END IsCountOp */                                                         \
  /* END IsUnaryOrCountOp */                                                  \
                                                                              \
  /* Compare operators sorted by precedence. */                               \
  /* IsCompareOp() relies on this block of enum values */                     \
  /* being contiguous and sorted in the same order! */                        \
  T(EQ, "==", 9)                                                              \
  T(EQ_STRICT, "===", 9)                                                      \
  T(NE, "!=", 9)                                                              \
  T(NE_STRICT, "!==", 9)                                                      \
  T(LT, "<", 10)                                                              \
  T(GT, ">", 10)                                                              \
  T(LTE, "<=", 10)                                                            \
  T(GTE, ">=", 10)                                                            \
  K(INSTANCEOF, "instanceof", 10)                                             \
  K(IN, "in", 10)                                                             \
                                                                              \
  /* Keywords (ECMA-262, section 7.5.2, page 13). */                          \
  K(BREAK, "break", 0)                                                        \
  K(CASE, "case", 0)                                                          \
  K(CATCH, "catch", 0)                                                        \
  K(CONTINUE, "continue", 0)                                                  \
  K(DEBUGGER, "debugger", 0)                                                  \
  K(DEFAULT, "default", 0)                                                    \
  /* DELETE */                                                                \
  K(DO, "do", 0)                                                              \
  K(ELSE, "else", 0)                                                          \
  K(FINALLY, "finally", 0)                                                    \
  K(FOR, "for", 0)                                                            \
  K(FUNCTION, "function", 0)                                                  \
  K(IF, "if", 0)                                                              \
  /* IN */                                                                    \
  /* INSTANCEOF */                                                            \
  K(NEW, "new", 0)                                                            \
  K(RETURN, "return", 0)                                                      \
  K(SWITCH, "switch", 0)                                                      \
  K(THROW, "throw", 0)                                                        \
  K(TRY, "try", 0)                                                            \
  /* TYPEOF */                                                                \
  K(VAR, "var", 0)                                                            \
  /* VOID */                                                                  \
  K(WHILE, "while", 0)                                                        \
  K(WITH, "with", 0)                                                          \
  K(THIS, "this", 0)                                                          \
                                                                              \
  /* Literals (ECMA-262, section 7.8, page 16). */                            \
  K(NULL_LITERAL, "null", 0)                                                  \
  K(TRUE_LITERAL, "true", 0)                                                  \
  K(FALSE_LITERAL, "false", 0)                                                \
  T(NUMBER, nullptr, 0)                                                       \
  T(SMI, nullptr, 0)                                                          \
  T(BIGINT, nullptr, 0)                                                       \
  T(STRING, nullptr, 0)                                                       \
                                                                              \
  /* BEGIN Callable */                                                        \
  K(SUPER, "super", 0)                                                        \
  /* BEGIN AnyIdentifier */                                                   \
  /* Identifiers (not keywords or future reserved words). */                  \
  /* TODO(rezvan): Add remaining contextual keywords (meta, target, as, from) \
   * to tokens. */                                                            \
  T(IDENTIFIER, nullptr, 0)                                                   \
  K(GET, "get", 0)                                                            \
  K(SET, "set", 0)                                                            \
  K(OF, "of", 0)                                                              \
  K(ASYNC, "async", 0)                                                        \
  /* `await` is a reserved word in module code only */                        \
  K(AWAIT, "await", 0)                                                        \
  K(YIELD, "yield", 0)                                                        \
  K(LET, "let", 0)                                                            \
  K(STATIC, "static", 0)                                                      \
  /* Future reserved words (ECMA-262, section 7.6.1.2). */                    \
  T(FUTURE_STRICT_RESERVED_WORD, nullptr, 0)                                  \
  T(ESCAPED_STRICT_RESERVED_WORD, nullptr, 0)                                 \
  /* END AnyIdentifier */                                                     \
  /* END Callable */                                                          \
  K(ENUM, "enum", 0)                                                          \
  K(CLASS, "class", 0)                                                        \
  K(CONST, "const", 0)                                                        \
  K(EXPORT, "export", 0)                                                      \
  K(EXTENDS, "extends", 0)                                                    \
  K(IMPORT, "import", 0)                                                      \
  T(PRIVATE_NAME, nullptr, 0)                                                 \
                                                                              \
  /* Illegal token - not able to scan. */                                     \
  T(ILLEGAL, "ILLEGAL", 0)                                                    \
  T(ESCAPED_KEYWORD, nullptr, 0)                                              \
                                                                              \
  /* Scanner-internal use only. */                                            \
  T(WHITESPACE, nullptr, 0)                                                   \
  T(UNINITIALIZED, nullptr, 0)                                                \
  T(REGEXP_LITERAL, nullptr, 0)


class JSLIB_EXPORT Token {
public:
#define T(name, string, precedence) name,
  enum Value : uint8_t { TOKEN_LIST(T, T) NUM_TOKENS };
#undef T
    static const char* Name(Value token) {
        return name_[token];
    }

    static const char* String(Value token) {
        return string_[token];
    }

    static const char* StringToName(char* string) {
        for (int i = 0; i < NUM_TOKENS; i++) {
            if (string_[i] == nullptr) {
                continue;
            }
            if(!strcmp(string_[i], string)) {
                return name_[i];
            }
        }
        return "No matching Tokens found";
    }
private:
static const char* const name_[NUM_TOKENS];
static const char* const string_[NUM_TOKENS];
static const uint8_t string_length_[NUM_TOKENS];
static const int8_t precedence_[2][NUM_TOKENS];
static const uint8_t token_flags[NUM_TOKENS];
};
}
}

#endif  // JSLIB_TOKEN_H