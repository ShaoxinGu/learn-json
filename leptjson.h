#ifndef LEPTJSON_H__
#define LEPTJSON_H__

#include <stddef.h>	/* size_t */

/* 表示解析类型的枚举 */
typedef enum { LEPT_UNDEFINED, LEPT_NULL, LEPT_TRUE, LEPT_FALSE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT }lept_type;


typedef struct lept_value lept_value;	/* 解析结果数据，包含解析类型和对应数据 */
typedef struct lept_member lept_member;	/* 解析对象，包含一个lept_value和键的字符串 */

struct lept_value {
	union {
		struct { lept_member* m; size_t size; };/* object */
		struct { lept_value* e; size_t size; }; /* array */
		struct { char* s; size_t len; };		/* string */
		double n;								/* number */
	};
	lept_type type;
};

struct lept_member {
	char* k; size_t klen;   /* member key string, key string length */
	lept_value v;           /* member value */
};

enum
{
	LEPT_PARSE_OK = 0,
	LEPT_PARSE_EXPECT_VALUE,
	LEPT_PARSE_INVALID_VALUE,
	LEPT_PARSE_ROOT_NOT_SINGULAR,
	LEPT_PARSE_NUMBER_TOO_BIG,
	LEPT_PARSE_MISS_QUOTATION_MARK,
	LEPT_PARSE_INVALID_STRING_ESCAPE,
	LEPT_PARSE_INVALID_STRING_CHAR,
	LEPT_PARSE_INVALID_UNICODE_HEX,
	LEPT_PARSE_INVALID_UNICODE_SURROGATE,
	LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET
};

#define lept_init(v)		do { (v)->type = LEPT_UNDEFINED; } while(0)

int lept_parse(lept_value* v, const char* json);

void lept_free(lept_value* v);

lept_type lept_get_type(const lept_value* v);

void lept_set_null(lept_value* v);

int lept_get_boolean(const lept_value* v);
void lept_set_boolean(lept_value* v, int b);

double lept_get_number(const lept_value* v);
void lept_set_number(lept_value* v, double n);

const char* lept_get_string(const lept_value* v);
size_t lept_get_string_length(const lept_value* v);
void lept_set_string(lept_value* v, const char* s, size_t len);

size_t lept_get_array_size(const lept_value* v);
lept_value* lept_get_array_element(const lept_value* v, size_t index);

#endif /* LEPTJSON_H__ */