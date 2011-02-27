#include "cli.h"
#include "LED.h"
#include "oscillator.h"
#include "uart.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CLI_PROMPT      "> "
#define CLI_BUFFER_SIZE 256

static char cli_prompt[CLI_BUFFER_SIZE];

static void cli_process_command(const char *command);
static void cli_display(char *text);
static void cli_question(void);

void init_cli(void)
{
	//initialize the hardware
	init_leds();
	init_uart();

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
			buffer[buffer_pos] = '\0';
			cli_process_command(buffer);

			buffer_pos = 0;
			uart_printf("%s", cli_prompt);
		}
		//there is more to come...
		else {
			buffer[buffer_pos++] = c;
		}

		//is the command too long?
		if(buffer_pos >= CLI_BUFFER_SIZE) {
			uart_printf("\n--Error--, command is too long. Command ignored.\n");
			buffer_pos = 0;

			uart_printf("%s", cli_prompt);
		}
	}
}

static void cli_process_command(char *command)
{
	char *token_end;

	token_end = command;

	while(isgraph(*token_end)) {
		token_end++;
	}

	if(token_end != command) {
		if(*token_end == '\0') {
			if(strcmp(command, "info") == 0) {
			
			}
			else if(strcmp(command, "?") == 0) {
				cli_question();
			}
			else {
				uart_printf("--Command:%s, not found. Enter \"?\" to see a list of available commands.\n");
			}
		}
		else {
			*token_end = '\0';

			if(strcmp(command, "echo") == 0) {
				
			}
			else if(strcmp(command, "display") == 0) {
				cli_display(++token_end);
			}
			else if(strcmp(command, "set") == 0) {
				
			}
			else if(strcmp(command, "hex") == 0) {
				
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
				uart_printf("--Command:%s, not found. Enter \"?\" to see a list of available commands.\n");
			}
		}
	}
}

static void cli_display(char *text)
{
	char *end;

	size_t token_len;

	if(*text != '"') {
		uart_printf("Incorrect format, display [\"text\"]\n");
		return;
	}
	text++;

	end = strchr(text, '"');
	if(*end != '"') {
		uart_printf("Incorrect format, display [\"text\"]\n");
		return;
	}
	*end = '\0';

	led_display_text(text);
}

static void cli_question(void)
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
