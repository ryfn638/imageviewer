#ifndef intTypes
#define intTypes

#define lambda(return_type, args, body)                                        \
  ({ return_type __fn__ args body __fn__; })

// just for lambdas only
#define RETURN return;

typedef unsigned long long uint64_t;
typedef signed long long int64_t;

typedef unsigned int uint32_t;
typedef signed int int32_t;

typedef unsigned char uint8_t;
typedef signed char int8_t;
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef enumTypes
#define enumTypes
typedef enum { FALSE = 0, TRUE = 1 } tlBool;

#define __bool_true_false_are_defined 1

#endif
