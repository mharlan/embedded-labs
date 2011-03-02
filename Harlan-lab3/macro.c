#include "macro.h"
#include "uart.h"

#include <stdlib.h>
#include <string.h>

#define MACRO_SIZE_MAX 128

static char * macros[MACRO_MAX];

/*
	Set a specified macro.
 */
void macro_set(int n, const char *macro)
{
	size_t macro_len;

	if(n < 0 || n >= MACRO_MAX) {
		return;
	}

	//clear the old macro
	if(macros[n] != NULL) {
		free(macros[n]);
	}

	macro_len = strlen(macro) + 2;
	if(macro_len > MACRO_SIZE_MAX) {
		macro_len = MACRO_SIZE_MAX;
	}

	macros[n] = malloc(sizeof(*macros[n]) * macro_len);
	if(!macros[n]) {
		return;
	}

	memcpy(macros[n], macro, macro_len - 2);
	macros[n][macro_len-2] = '\n';
	macros[n][macro_len-1] = '\0';
}

/*
	Execute a specified macro.
 */
void macro_execute(int n)
{
	char *c;
	int macro_len;
	int i;

	if(n < 0 || n >= MACRO_MAX) {
		return;
	}

	c = macros[n];
	macro_len = strlen(c);

	for(i = 0; i < macro_len; ++i) {
		uart_dummy_receive(*c);
		++c;
	}
}