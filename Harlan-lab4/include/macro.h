#ifndef __MACRO_H
#define __MACRO_H

#define MACRO_MAX 3

#define MACRO0 0
#define MACRO1 1
#define MACRO2 2

/*
	Initialize the macro module.
 */
extern void init_macro(void);

/*
	Set a specified macro.
 */
extern void macro_set(int n, const char *macro);

/*
	Execute a specified macro.
 */
extern void macro_execute(int n);

#endif