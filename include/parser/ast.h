#ifndef ___AST_H___
#define ___AST_H___
#include <stdint.h>
#include <sys/types.h>

#include "cJSON/cJSON.h"

typedef struct parameter Parameter;
typedef struct builtin_fn SecondFn;
typedef struct builtin_fn FirstFn;
typedef struct location Location;
typedef struct function Function;
typedef struct binary Binary;
typedef struct common Common;
typedef struct file AstRoot;
typedef struct tuple Tuple;
typedef struct term Term;
typedef struct file File;
typedef struct call Call;
typedef struct var Var;
typedef struct let Let;
typedef struct _if If;

typedef struct _value Str;
typedef struct _value Int;
typedef struct _value Bool;

typedef Term (*evaluate_fn)(Term**);

void
json_iter(cJSON *json);

File*
ast_new(const char *name, const char *filename, size_t length);

enum term_tag
{ 
    IntTag,
    StrTag,
    CallTag,
    BinaryTag,
    FunctionTag,
    LetTag,
    IfTag,
    PrintTag,
    FirstTag,
    SecondTag,
    BoolTag,
    TupleTag,
    VarTag,

    Nothing,
}__attribute__((__packed__));

enum binary_op
{
    Add,
    Sub,
    Mul,
    Div,
    Rem,
    Eq,
    Neq,
    Lt,
    Gt,
    Lte,
    Gte,
    And,
    Or,
}__attribute__((__packed__));

struct location 
{
    size_t start;
    size_t end;
    char filename[];
};

struct _value
{  
    Location *location;
    char *kind;
    char *value;
};

struct term
{
    void *term;
    evaluate_fn eval;
    enum term_tag tag;
};

struct file
{
    Location *location;
    Term expression;
    char name[];
};

struct parameter
{
    Location *location;
    char *text;
};

struct var
{
    Location *location;
    char *text;
    char *kind;
};

struct function
{
    Location *location;
    Term value;
    char *kind;
    Parameter parameters[];
};

struct call
{
    Location *location;
    Term callee;
    char *kind;
    Term arguments[];
};

struct let
{
    Location *location;
    Term value;
    Term next;
    Parameter name;
    char *kind;
};

struct _if
{
    Location *location;
    Term condition;
    Term then;
    Term otherwise;
    char *kind;
};

struct binary
{
    Location *location;
    Term lhs;
    Term rhs;
    char *kind;
    enum binary_op op;
};

struct tuple
{
    Location *location;
    Term first;
    Term second;
    char *kind;
};

struct builtin_fn
{
    Location *location;
    Term value;
    char *kind;
};

#endif
