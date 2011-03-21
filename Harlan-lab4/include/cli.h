#ifndef __CLI_H
#define __CLI_H

/*
	Initialize the command line interface and all dependencies.
 */
extern void init_cli(void);

/*
	Infinite CLI program loop.
 */
extern void cli_loop(void);

/*
	Strip quotes off a string.

	Returns 0, success.
	Returns 1, format error.
 */
extern int cli_strip_quotes(char **args);


/*
	Strips a decimal number from a string.

	Returns 0, success.
	Returns 1, format error.
 */
extern int cli_strip_decimal_number(char **args);

/*
	Strip a word out of a string.

	Return 0, more args after the word.
	Return 1, no more args after the word.
 */
extern int cli_strip_word(char **args);

/*
	Strip spaces from the beginning of a string.
 */
extern void cli_strip_spaces(char **args);

/*
	Sets the cli prompt to the first 255 bits of text
	plus a  null terminator.
 */
extern void cli_set_prompt(const char *text);

#endif