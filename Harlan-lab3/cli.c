#include "cli.h"
#include "LED.h"
#include "uart.h"
#include "info.h"

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
static void cli_command_echo(char *text);
static void cli_command_display(char *text);
static void cli_command_hex(char *text);

void init_cli(void)
{
	//initialize the hardware
	init_leds();
	init_uart();
	init_info();

	strcpy(cli_prompt, CLI_PROMPT);
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

static void cli_process_command(char *command)
{
	char *token_end;

	//strip spaces and tabs
	while(isspace(*command)) {
		++command;
	}

	token_end = command;
	while(isgraph(*token_end) && *token_end != '\t') {	//bug with isgraph, returns true on \t, and it shouldn't
		token_end++;
	}

	if(token_end != command) {
		*token_end = '\0';

		++token_end;
		if(strcmp(command, "info") == 0) {
			cli_command_info();
		}
		else if(strcmp(command, "?") == 0) {
			cli_command_question();
		}
		else if(strcmp(command, "echo") == 0) {
			cli_command_echo(token_end);
		}
		else if(strcmp(command, "display") == 0) {
			cli_command_display(token_end);
		}
		else if(strcmp(command, "set") == 0) {
			
		}
		else if(strcmp(command, "hex") == 0) {
			cli_command_hex(token_end);
		}
		else if(strcmp(command, "set") == 0) {
			
		}
		else if(strcmp(command, "switch") == 0) {
			
		}
		else if(strcmp(command, "port") == 0) {
			
		}
		else if(strcmp(command, "timer") == 0) {
			
		}
		else if(strcmp(command, "uart0") == 0) {
			
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

	uart_printf("info\n");
	uart_printf(" -Displays various system information.\n");

	uart_printf("?\n");
	uart_printf(" -Displays a menu of CLI commands.\n");
}

static void cli_command_info(void)
{
	info_display();
}

static void cli_command_echo(char *text)
{
	char *end;

	//strip spaces and tabs
	while(isspace(*text)) {
		++text;
	}

	if(*text != '"') {
		uart_printf("1 Incorrect format, echo [\"text\"]\n");
		return;
	}
	text++;

	end = strchr(text, '"');
	if(end == NULL) {
		uart_printf("2 Incorrect format, echo [\"text\"]\n");
		return;
	}
	*end = '\0';

	uart_printf("%s\n", text);
}

static void cli_command_display(char *text)
{
	char *end;

	//strip spaces and tabs
	while(isspace(*text)) {
		++text;
	}

	if(*text != '"') {
		uart_printf("1 Incorrect format, display [\"text\"]\n");
		return;
	}
	text++;

	end = strchr(text, '"');
	if(end == NULL) {
		uart_printf("2 Incorrect format, display [\"text\"]\n");
		return;
	}
	*end = '\0';

	led_display_text(text);
}

static void cli_command_hex(char *text)
{
	char *end;
	int value;

	//strip spaces and tabs
	while(isspace(*text)) {
		++text;
	}

	end = text;
	while(isdigit(*end)) {
		++end;
	}
	*end = '\0';

	//is there a number at all
	if(text == end) {
		uart_printf("1 Incorrect format, hex [decimal number]\n");
		return;
	}

	//convert string to int
	value = atoi(text);
	if(value == 0) {
		uart_printf("2 Incorrect format, hex [decimal number]\n");
		return;
	}

	led_display_int_hex(value);
}

