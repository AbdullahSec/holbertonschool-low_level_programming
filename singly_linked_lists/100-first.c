#include <stdio.h>

/**
 * first - prints a message before main is executed
 *
 * Description: uses the constructor attribute so the function runs
 * automatically before main
 */
__attribute__((constructor))
void first(void)
{
	printf("You're beat! and yet, you must allow,\n");
	printf("I bore my house upon my back!\n");
}
