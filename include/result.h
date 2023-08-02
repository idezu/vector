#ifndef LIBARGS_RESULT_H
#define LIBARGS_RESULT_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct String_t
	{
		char * data;
		size_t lenght;
	} string;

struct Error_t
	{
		char *message;
		char *file;
		int line;
	};

enum ResultType
{
	RESULT_OK,
	RESULT_ERROR
};

#define ResultDEF(T) \
	typedef struct Result_t_##T { \
		union { \
			T value; \
			struct Error_t error; \
		}; \
		enum ResultType type; \
	} Result##T

#define Result(T) Result##T

ResultDEF(int);
ResultDEF(float);
ResultDEF(double);
ResultDEF(char);
ResultDEF(bool);
ResultDEF(string);

typedef struct Result_t_void 
	{
		struct Error_t error;
		enum ResultType type;
	} Resultvoid;

typedef struct Result_t
	{
		union
			{
				void* value;
				struct Error_t error;
			};
		enum ResultType type;
	} Result;

#endif // LIBARGS_RESULT_H