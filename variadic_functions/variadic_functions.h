#ifndef VARIADIC_FUNCTIONS_H
#define VARIADIC_FUNCTIONS_H

#include <stdarg.h>

/**
 * struct printer - maps a format symbol to its print function
 * @symbol: the format specifier (c, i, f, s)
 * @print: pointer to the function that prints that type
 */
typedef struct printer
{
	char *symbol;
	void (*print)(va_list);
} printer_t;

int sum_them_all(const unsigned int n, ...);
void print_numbers(const char *separator, const unsigned int n, ...);
void print_strings(const char *separator, const unsigned int n, ...);
void print_all(const char * const format, ...);
void print_char(va_list args);
void print_int(va_list args);
void print_float(va_list args);
void print_string(va_list args);

#endif /* VARIADIC_FUNCTIONS_H */
