#ifndef ___LEXER_H___
#define ___LEXER_H___
#include <stdint.h>
#include <sys/types.h>

typedef struct lexer Lexer;
typedef struct token Token;

typedef void* (*state_fn)(Lexer*);
typedef void* (*emit_tk)(Token);

struct lexer 
{
    const char *source;
    size_t current;
    size_t start;
    size_t line;
    size_t column;
};

struct token
{
    const char *start;
    size_t length;
    size_t line;
    size_t column;
};

#endif
