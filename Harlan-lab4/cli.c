#include "cli.h"
#include "LED.h"
#include "uart.h"
#include "info.h"
#include "macro.h"
#include "ports.h"
#include "timer.h"
#include "keyboard.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CLI_PROMPT      "> "
#define CLI_BUFFER_SIZE 256

#define ASCII_DEL 0x7F

static char cli_prompt[CLI_BUFFER_SIZE];

static void cli_process_command(const char *command);

/*
	Zero arguement CLI functions.
 */
static void cli_command_info(void);
static void cli_command_question(void);

/*
	Variable arguement CLI functions.

	Multiple arguements encoded as strings, separated by
	whitespace and quotes.
 */
static void cli_command_echo(char *args);
static void cli_command_display(char *args);
static void cli_command_hex(char *args);
static void cli_command_set(char *args);
static void cli_command_switch(char *args);
static void cli_command_port(char *args);
static void cli_command_timer(char *args);
static void cli_command_uart0(char *args);

void init_cli(void)
{
	//initialize the hardware
	init_leds();
	init_uart();
	init_info();
	init_keyboard();

	cli_set_prompt(CLI_PROMPT);
}

void cli_loop(void)
{
	char buffer[CLI_BUFFER_SIZE];
	char c;

	int buffer_pos;

	uart_printf("%s", cli_prompt);

	buffer_pos = 0;

	while(1) {
		//wait until a character is available
		while((c = uart_getchar()) == 0) { ; }

		//new line means end of the command
		if(c == '\n') {
			//only process a command if something was entered
			if(buffer_pos) {
				buffer[buffer_pos] = '\0';
				cli_process_command(buffer);
			}

			buffer_pos = 0;
			memset(buffer, 0, CLI_BUFFER_SIZE);

			uart_printf("%s", cli_prompt);
		}
		//there is more to come...
		else if(isgraph(c) || isspace(c)) {
			buffer[buffer_pos++] = c;
		}
		//
		else if(c == ASCII_DEL) {
			if(buffer_pos) {
				buffer_pos--;
				buffer[buffer_pos] = '\0';
			}
		}
		//ignore for now
		else {
			continue;
		}

		//is the command too long?
		if(buffer_pos >= CLI_BUFFER_SIZE) {
			uart_printf("\n--Error--, command is too long. Command ignored.\n");
			
			buffer_pos = 0;
			memset(buffer, 0, CLI_BUFFER_SIZE);

			uart_printf("%s", cli_prompt);
		}
	}
}

int cli_strip_quotes(char **args)
{
	char *c;

	c = *args;
	if(*c != '"') {
		return 1;
	}
	++c;

	c = strchr(c, '"');
	if(c == NULL) {
		return 1;
	}
	*c = '\0';

	*args = c;

	return 0;
}

int cli_strip_word(char **args) 
{
	char *c;

	c = *args;
	while(isalpha(*c)) {
		++c;
	}

	if(c == *args) {
		return 1;
	}
	*c = '\0';

	*args = c;

	return 0;
}

int cli_strip_decimal_number(char **args)
{
	char *c;

	c = *args;
	while(isdigit(*c)) {
		++c;
	}
	*c = '\0';

	//is there a number at all
	if(*args == c) {
		return 1;
	}
	*args = c;

	return 0;
}

void cli_strip_spaces(char **args)
{
	char *c;

	c = *args;
	while(isspace(*c)) {
		++c;
	}

	*args = c;
}

void cli_set_prompt(const char *text)
{
	size_t prompt_len;
	
	prompt_len = strlen(text) + 1;
	if(prompt_len >= CLI_BUFFER_SIZE) {
		prompt_len = CLI_BUFFER_SIZE;
	}
	
	memcpy(cli_prompt, text, prompt_len);
	cli_prompt[prompt_len-1] = '\0';
}

static void cli_process_command(char *command)
{
	char *args;

	//strip spaces and tabs
	cli_strip_spaces(&command);

	args = command;
	while(isgraph(*args) && *args != '\t') {	//bug with isgraph, returns true on \t and it shouldn't
		++args;
	}

	if(args != command) {
		*args = '\0';

		++args;
		if(strcmp(command, "info") == 0) {
			cli_command_info();
		}
		else if(strcmp(command, "?") == 0) {
			cli_command_question();
		}
		else if(strcmp(command, "echo") == 0) {
			cli_command_echo(args);
		}
		else if(strcmp(command, "display") == 0) {
			cli_command_display(args);
		}
		else if(strcmp(command, "set") == 0) {
			cli_command_set(args);
		}
		else if(strcmp(command, "hex") == 0) {
			cli_command_hex(args);
		}
		else if(strcmp(command, "switch") == 0) {
			cli_command_switch(args);
		}
		else if(strcmp(command, "port") == 0) {
			cli_command_port(args);
		}
		else if(strcmp(command, "timer") == 0) {
			cli_command_timer(args);
		}
		else if(strcmp(command, "uart0") == 0) {
			cli_command_uart0(args);
		}
		else if(strcmp(command, "scan") == 0) {
			keyboard_read(KEYBOARD_SCAN);
		}
		else if(strcmp(command, "type") == 0) {
			keyboard_read(KEYBOARD_TYPE);
		}
		else {
			uart_printf("--Command:%s, not found. Enter \"?\" to see a list of available commands.\n", command);
		}
	}
}

static void cli_command_question(void)
{
	uart_printf("\nAvailable Commands:\n\n");

	uart_printf("echo [\"text\"]\n");
	uart_printf(" -Echos text back to the serial port.\n");

	uart_printf("display [\"text\"]\n");
	uart_printf(" -Display text on the LEDs.\n");

	uart_printf("set prompt [\"text\"]\n");
	uart_printf(" -Set the CLI prompt to text.\n");

	uart_printf("hex [decimal number]\n");
	uart_printf(" -Display a decimal number in hex on the LEDs.\n");

	uart_printf("switch [0-2] [\"text\"]\n");
	uart_printf(" -Assigns the text macro to a button.\n");

	uart_printf("port [A-K]\n");
	uart_printf(" -Display the current state of the port.\n");

	uart_printf("timer [0-2]\n");
	uart_printf(" -Display the current state of the timer.\n");

	uart_printf("uart0 [speed [baudrate]] [parity [even|odd|none]] [bits [7|8]]\n");
	uart_printf(" -Set the uart0 settings.\n");

	uart_printf("scan\n");
	uart_printf(" -Displays scan codes from a PS/2 keyboard. Press a button to quit.\n");

	uart_printf("type\n");
	uart_printf(" -Displays scan codes from a PS/2 keyboard. Press a button or ESC to quit.\n");


	uart_printf("info\n");
	uart_printf(" -Displays various system information.\n");

	uart_printf("?\n");
	uart_printf(" -Displays a menu of CLI commands.\n");
}

static void cli_command_info(void)
{
	info_display();
}

static void cli_command_echo(char *args)
{
	char *token;

	cli_strip_spaces(&args);

	token = args;
	if(cli_strip_quotes(&args)) {
		uart_printf("Incorrect format, echo [\"text\"]\n");
		return;
	}

	uart_printf("%s\n", ++token);
}

static void cli_command_display(char *args)
{
	char *token;

	cli_strip_spaces(&args);

	token = args;
	if(cli_strip_quotes(&args)) {
		uart_printf("Incorrect format, display [\"text\"]\n");
		return;
	}

	led_display_text(++token);
}

static void cli_command_hex(char *args)
{
	char *token;
	int value;

	cli_strip_spaces(&args);

	token = args;
	if(cli_strip_decimal_number(&args)) {
		uart_printf("1 Incorrect format, hex [decimal number]\n");
		return;
	}

	value = atoi(token);
	led_display_int_hex(value);
}

static void cli_command_set(char *args)
{
	char *token;

	cli_strip_spaces(&args);

	token = args;
	if(cli_strip_word(&args)) {
		uart_printf("1 Incorrect format, set prompt [\"text\"]\n");
		return;
	}

	if(strcmp(token, "prompt") == 0) {
		++args;
		cli_strip_spaces(&args);

		token = args;
		if(cli_strip_quotes(&args)) {
			uart_printf("2 Incorrect format, set prompt [\"text\"]\n");
			return;
		}

		++token;
		cli_set_prompt(token);
	}
	else {
		uart_printf("3 Incorrect format, set prompt [\"text\"]\n");
		return;
	}
}

static void cli_command_switch(char *args)
{
	char *token;
	int value;

	cli_strip_spaces(&args);

	token = args;
	if(cli_strip_decimal_number(&args)) {
		uart_printf("1 Incorrect format, switch [n] [\"text\"]\n");
		return;
	}
	value = atoi(token);

	if(value < 0 || value >= MACRO_MAX) {
		uart_printf("2 Incorrect format, switch [n] [\"text\"]\n");
		return;
	}

	++args;
	cli_strip_spaces(&args);

	token = args;
	if(cli_strip_quotes(&args)) {
		uart_printf("3 Incorrect format, switch [n] [\"text\"]\n");
		return;
	}

	macro_set(value, ++token);
}

static void cli_command_port(char *args)
{
	char *token;

	cli_strip_spaces(&args);

	token = args;
	if(cli_strip_word(&args)) {
		uart_printf("Incorrect format, port [A-K]\n");
		return;
	}

	ports_print_config(token);
}

static void cli_command_timer(char *args)
{
	char *token;

	cli_strip_spaces(&args);

	token = args;
	if(cli_strip_decimal_number(&args)) {
		uart_printf("Incorrect format, timer [0-2]\n");
		return;
	}

	timers_print_config(token);
}

static void cli_command_uart0(char *args)
{
	char *token;
	int value;

	cli_strip_spaces(&args);

	token = args;
	if(cli_strip_word(&args)) {
		uart_printf("1 Incorrect format, uart0 [speed [baudrate]] [parity [even|odd|none]] [bits [7|8]]\n");
		return;
	}

	if(strcmp(token, "speed") == 0) {
		++args;
		
		cli_strip_spaces(&args);		
	
		token = args;
		if(cli_strip_decimal_number(&args)) {
			uart_printf("2 Incorrect format, uart0 [speed [baudrate]] [parity [even|odd|none]] [bits [7|8]]\n");
			return;
		}
		value = atoi(token);

		uart_set_baudrate(value);

		++args;
		cli_strip_spaces(&args);

		token = args;
		cli_strip_word(&args);
	}
	if(strcmp(token, "parity") == 0) {
		++args;

		cli_strip_spaces(&args);

		token = args;
		if(cli_strip_word(&args)) {
			uart_printf("3 Incorrect format, uart0 [speed [baudrate]] [parity [even|odd|none]] [bits [7|8]]\n");
			return;
		}

		uart_set_parity(token);

		++args;
		cli_strip_spaces(&args);

		token = args;
		cli_strip_word(&args);
	}
	if(strcmp(token, "bits") == 0) {
		++args;

		cli_strip_spaces(&args);

		token = args;
		if(cli_strip_decimal_number(&args)) {
			uart_printf("4 Incorrect format, uart0 [speed [baudrate]] [parity [even|odd|none]] [bits [7|8]]\n");
			return;
		}

		uart_set_bits(token);
	}
}