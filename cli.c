/*
*******************************************************************************
@file	cli.c
@brief	The main Command Line Interpreter file. Contains the necessary
		functions to work.
*******************************************************************************
@attention

The MIT License

Copyright (c) 2024 Martouf (Kolegov A.A.)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************
*/

#include "cli.h"
#include "io.h"
#include "function.h"

#if CLI_USE_FULL_ASSERT == 1
#include <assert.h>
#define assert_cli(_e) assert(_e)
#else
#define assert_cli(_e) if (!(_e)) while(1) {};
#endif

#if (CLI_EXAMPLE_ENABLE == TRUE)
#include "Function/example.h"
#endif

/* Instance Definition ----------------------------------------------------- */
cli_t cli0;

/* Instances of static functions ------------------------------------------- */

static void cli_clear_buffer(cli_t *cli);
static int cli_utils_abs(int id);
static void cli_print_line(cli_t *cli);
static int cli_key_handler(cli_t *cli, char symbol);
static int cli_key_handler_backspace(cli_t *cli);
static int cli_key_handler_enter(cli_t *cli);
static int cli_key_handler_tab(cli_t *cli);
static int cli_key_handler_esc(cli_t *cli);
static int cli_key_handler_print_element(cli_t *cli, int inc);
static int cli_key_handler_set_point(cli_t *cli, int inc);
static int cli_key_handler_control_delete(cli_t *cli);
static int cli_history_add(cli_t *cli);
static int cli_run(cli_t *cli);

/*---------------------------------------------------------------------------*/
/**
* @brief	Initial configuration of the CLI and adding commands.
* @note 	The read and write functions are described in the `io.h` and
*       	`io.c` files. Alternatively, you can override.
*       	the `__io_cli_getchar` and `__io_cli_putchar` functions.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
* @retval 	`CLI_OK` (0) if success.
* @retval   `CLI_ERROR` (!0) if error.
*
*/
int cli_init(cli_t *cli) {
	assert_cli(cli != NULL && "CLI instance is incorrect!\n");
	cli_error_t status = CLI_OK;
	memset(cli, 0, sizeof(cli_t));
	cli->_io_getchar = __io_cli_getchar;
	cli->_io_putchar = __io_cli_putchar;

	/* Add default commands */
	status |= cli_add(cli, "help", cli_function_help, "Displays reference information about commands");
	status |= cli_add(cli, "clear", cli_function_clear, "Clear terminal");

#if (CLI_EXAMPLE_ENABLE == TRUE)
	cli_example_init(cli);
#endif

	if (status != CLI_ERROR) {
		status = CLI_OK;
	}

	/* Show Hello massage */
	__cli_print_hello(cli);
	cli_print_line(cli);

	return status;
}

/*---------------------------------------------------------------------------*/
/**
* @brief	Console Output Function.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
* @param	format Format string.
* @return	`int` Number of characters sent.
* @retval 	`int` (>0) if success.
* @retval   `CLI_ERROR` (!0) if error.
*/
int cli_printf(cli_t *cli, const char* format, ...) {
	va_list args;
	va_start(args, format);
	char temp[BUFSIZ];
	int nchar = vsniprintf(temp, sizeof(temp), format, args);
	va_end(args);

	if (nchar < 0) return CLI_ERROR;
	for (int i = 0; i < nchar; i++) {
		cli->_io_putchar(temp[i]);
	}
	return nchar;
}

/*---------------------------------------------------------------------------*/
/**
* @brief	Display a welcome message in the console.
* @note 	Can be overridden.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
*
*/
int __cli_print_hello(cli_t *cli) {
	return cli_printf(cli, "%s\rCommand Line Interpreter initialized\r\n", CONSOLE_CLEAR_STRING);
}

/*---------------------------------------------------------------------------*/
/**
* @brief	Function of adding a command to the CLI.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
* @param	name Function name.
* @param	function Pointer on Function.
* @param	help Minimal description of the function.
* @return	`int` The number of the command in the list.
* @retval 	`int` (>0) if success.
* @retval   `CLI_ERROR` (!0) if error.
*
*/
int cli_add(cli_t *cli, const char *name, int (*function)(cli_t *cli, int argc, char* argv[]), const char *help) {
	assert_cli(cli != NULL && "CLI instance is incorrect!\n");
	assert_cli(name != NULL && "Name function text is incorrect!\n");
	assert_cli(function != NULL && "Pointer to function is incorrect!\n");
	assert_cli(help != NULL && "Help text is incorrect!\n");
	int index = 0;
	for (index = 0; index < CLI_MAX_COUNT_COMMAND; index++) {
		if (cli->Commands[index].Function == NULL) {
			cli->Commands[index].Name = name;
			cli->Commands[index].Function = function;
			cli->Commands[index].Help = help;
			return index;
		}
	}
	cli_printf(cli, "Failed to add a function. Buffer is overcrowded. Change the value of CLI_MAX_COUNT_COMMAND in the 'opt.h' file.");
	return CLI_ERROR;
}

#if (CLI_ENABLE_DELETE_COMMAND == TRUE)
/*---------------------------------------------------------------------------*/
/**
* @brief	Remove a command from the list.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
* @param	index Command index.
* @retval 	`CLI_OK` (0) if success.
* @retval   `CLI_ERROR` (!0) if error.
*
*/
int cli_remove_id(cli_t *cli, int index) {
	assert_cli(cli != NULL && "CLI instance is incorrect!\n");
	if (cli->Commands[index].Name != NULL) {
		cli->Commands[index].Name = NULL;
		cli->Commands[index].Function = NULL;
		cli->Commands[index].Help = NULL;
		return CLI_OK;
	}
	return CLI_ERROR;
}
/*---------------------------------------------------------------------------*/
/**
* @brief	Remove a command from the list.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
* @param	name Command name.
* @retval 	`CLI_OK` (0) if success.
* @retval   `CLI_ERROR` (!0) if error.
*/
int cli_remove_name(cli_t *cli, const char* name) {
	assert_cli(cli != NULL && "CLI instance is incorrect!\n");
	for (int index = 0; index < CLI_MAX_COUNT_COMMAND; index++) {
		size_t length = strlen(cli->Commands[index].Name);
		if (!memcmp(cli->Commands[index].Name, name, length)) {
			return cli_remove_id(cli, index);
		}
	}
	return CLI_ERROR;
}

/*---------------------------------------------------------------------------*/
/**
* @brief	Remove a command from the list.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
* @param	function Pointer on Function.
* @retval 	`CLI_OK` (0) if success.
* @retval   `CLI_ERROR` (!0) if error.
*/
int cli_remove_ptr(cli_t *cli, int (*function)(cli_t *cli, int argc, char* argv[])) {
	assert_cli(cli != NULL && "CLI instance is incorrect!\n");
	for (int index = 0; index < CLI_MAX_COUNT_COMMAND; index++) {
		if (cli->Commands[index].Function == function) {
			return cli_remove_id(cli, index);
		}
	}
	return CLI_ERROR;
}
#endif
/*---------------------------------------------------------------------------*/
/**
* @brief	Command to clear the contents of the buffer.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
*
*/
static void cli_clear_buffer(cli_t *cli) {
	memset(cli->Buffer, 0, sizeof(cli->Buffer));
	cli->Point = 0;
}

/*---------------------------------------------------------------------------*/
/**
* @brief	Print the prefix and buffer content to the console.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
*
*/
static void cli_print_line(cli_t *cli) {
	cli_printf(cli, "\r%s%s%s", CONSOLE_CLEAR_STRING, CLI_PREFIX, cli->Buffer);
	for (int i = 0; i < strlen(cli->Buffer) - cli->Point; i++) {
		/* Print '\033[D' */
		cli_printf(cli, "%c%c%c", Key_ESC, Key_CONTROL, Key_D);
	}
}

/*---------------------------------------------------------------------------*/
/**
* @brief	The main handler of the Command Line Interpreter.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
*
*/
int cli_handler(cli_t *cli) {
	assert_cli(cli != NULL && "CLI instance is incorrect!\n");
	/* Basic Key Handler */
	char symbol = (char)cli->_io_getchar();
	switch (symbol) {
		case 0:
			break;
		case Key_CR:
			return cli_key_handler_enter(cli);
		case Key_DEL:
		case Key_BS:
			return cli_key_handler_backspace(cli);
		case Key_TAB:
			return cli_key_handler_tab(cli);
		case Key_ESC:
			return cli_key_handler_esc(cli);
		default:
			return cli_key_handler(cli, symbol);
	}
	return CLI_OK;
}

/*---------------------------------------------------------------------------*/
/**
* @brief	Handler for basic information keys.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
* @param	symbol The character to be processed.
*
*/
static int cli_key_handler(cli_t *cli, char symbol) {
	if ((symbol >= 0x20) & (symbol <= 0x7e)) {
		if (cli->Buffer[cli->Point]) {
			for (int i = strlen(cli->Buffer); i > cli->Point; i--) {
				cli->Buffer[i] = cli->Buffer[i-1];
			}
		}
		if (cli->Point >= CLI_BUFFER_SIZE - 1) {
			cli_printf(cli, "\r%sThe buffer is full.\r\n", CONSOLE_CLEAR_STRING);
		} else{
			cli->Buffer[cli->Point++] = symbol;
		}
		cli_print_line(cli);
	}
	return CLI_OK;
}

/*---------------------------------------------------------------------------*/
/**
* @brief	The handler removes the character on the left.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
*
*/
static int cli_key_handler_backspace(cli_t *cli) {
	if (cli->Point) {
		(cli->Point)--;
		for (int i = cli->Point; i < strlen(cli->Buffer); i++) {
			cli->Buffer[i] = cli->Buffer[i + 1];
		}
	}
	cli_print_line(cli);
	return CLI_OK;
}

/*---------------------------------------------------------------------------*/
/**
* @brief	Function for processing the Enter key.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
*
*/
static int cli_key_handler_enter(cli_t *cli) {
	cli_error_t res = CLI_OK;
	if (cli->Point) {
		res = cli_run(cli);
	} else {
		cli->_io_putchar((int)Key_VT);
	}
	cli_print_line(cli);
	return res;
}

/*---------------------------------------------------------------------------*/
/**
* @brief	Function to handle the launch of commands from the console.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
*
*/
static int cli_run(cli_t *cli) {
	/* Delete 'Key_Space' at the end of the command */
	while (cli->Buffer[cli->Point - 1] == Key_SPACE) {
		cli_key_handler_backspace(cli);
	}
	cli_printf(cli, "\r\n");
	/* Add list command running */
	cli_history_add(cli);
	/* Search function */
	for (int index = 0; index < CLI_MAX_COUNT_COMMAND; index++) {
		/* Find command */
		if (cli->Commands[index].Function == NULL) continue;
		size_t length = strlen(cli->Commands[index].Name);
		if (!memcmp(cli->Commands[index].Name, cli->Buffer, length)) {
			if ((cli->Buffer[length] != 0) && (cli->Buffer[length] != ' ')) {
				continue;
			}

			int argc = 1;
			/* Find count arguments */
			int len = strlen(cli->Buffer);
			for (int i = 0; i < len; i++) {
				if (cli->Buffer[i] == Key_SPACE) {
					argc++;
				}
			}
			/* Find arguments */
			char *argv[argc];
			int inc = 0;
			argv[inc++] = cli->Buffer;
			for (int i = 0; i < len; i++) {
				if (cli->Buffer[i] == Key_SPACE) {
					cli->Buffer[i] = 0;
					argv[inc++] = &(cli->Buffer[i + 1]);
				}
			}
			/* Run command */
			int ret = cli->Commands[index].Function(cli, argc, argv);
			/* If command return error */
			if (ret) {
				cli_printf(cli, "Function '%s' return %d [0x%.8x]\r\n",
						cli->Commands[index].Name,
						ret,
						ret);
			}
			goto label_exit_cmd;
		}
	}
	cli_printf(cli, "Command '%s' not found\r\n", cli->Buffer);
label_exit_cmd:
	cli_clear_buffer(cli);
	cli_printf(cli, "\r%s\r", CONSOLE_CLEAR_STRING);
	return 0;
}

/*---------------------------------------------------------------------------*/
/**
* @brief	Function for processing the Tab key.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
*
*/
static int cli_key_handler_tab(cli_t *cli) {
	/* Number of clear matches */
	int countmatch = 0;
	/* We are looking for the number of "clear" matches */
	for (int i = 0; i < CLI_MAX_COUNT_COMMAND; i++) {
		if ((!memcmp(cli->Commands[i].Name, cli->Buffer, cli->Point)) && (cli->Commands[i].Function != NULL)) {
			countmatch++;
		}
	}
	/* If there are no matches, exit */
	if (countmatch == 0) return CLI_OK;

	/* Number of matches with character completion */
	int match = 0;
	/* We do it as long as there are matches */
	do {
		match = 0;
		for (int i = 0; i < CLI_MAX_COUNT_COMMAND; i++) {
			if (cli->Commands[i].Function == NULL) continue;
			if (!(memcmp(cli->Commands[i].Name, cli->Buffer, cli->Point))) {
				if (!match) {
					/* If there is nothing to add */
					if (cli->Commands[i].Name[cli->Point] == 0) {
						break;
					}
					/* Add symbol */
					cli->Buffer[cli->Point] = cli->Commands[i].Name[cli->Point];
					cli->Point++;
				}
				match++;
			}
		}
	} while (countmatch == match);

	/* If there is more than one command, then write all possible commands */
	if (countmatch != 1) {
		/* Send Enter for a pleasant look */
		cli_printf(cli, "\r\n");
		if ((cli->Point)--) {
			cli->Buffer[cli->Point] = 0;
		}
		for (int i = 0; i < CLI_MAX_COUNT_COMMAND; i++) {
			if (!memcmp(cli->Commands[i].Name, cli->Buffer, cli->Point)) {
				/* Write all commands */
				cli_printf(cli, "   %s", cli->Commands[i].Name);
			}
		}
		/* Send Enter for a pleasant look */
		cli_printf(cli, "\r\n");
	} else {
		cli->Buffer[(cli->Point)++] = ' ';
	}
	/* Command output */
	cli_printf(cli, "\r%s%s", CLI_PREFIX, cli->Buffer);
	return CLI_OK;
}

/*---------------------------------------------------------------------------*/
/**
* @brief	Function for processing the Escape key.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
*
*/
static int cli_key_handler_esc(cli_t *cli) {
	char symbol = 0 ;
	do {
		symbol = (char)cli->_io_getchar();
	} while (!symbol);
	if (symbol == Key_CONTROL) {
		char symbol = 0;
		do {
			symbol = (char)cli->_io_getchar();
		} while(!symbol);

		switch (symbol) {
		case Key_A:
			/* Arrow Up */
			return cli_key_handler_print_element(cli, -1);
		case Key_B:
			/* Arrow Down */
			return cli_key_handler_print_element(cli, 1);
		case Key_D:
			/* Arrow Left */
			return cli_key_handler_set_point(cli, -1);
		case Key_C:
			/* Arrow Rigth */
			return cli_key_handler_set_point(cli, 1);
		case Key_3:
			char s = 0;
			do {
				s = (char) cli->_io_getchar();
			} while (!s);
			if (s == Key_Tilda) {
				/* Key Delete */
				return cli_key_handler_control_delete(cli);
			}
		default:
			break;
		}
	}
	return CLI_OK;
}

/*---------------------------------------------------------------------------*/
/**
* @brief	Function to add commands from the current buffer to the	list of 
*       	past running commands.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
*
*/
static int cli_history_add(cli_t *cli) {
	if (strcmp(cli->History[cli_utils_abs(cli->HistoryNewPoint - 1)].Command, cli->Buffer)) {
		strcpy(cli->History[cli->HistoryNewPoint].Command, cli->Buffer);
		cli->HistoryNewPoint = cli_utils_abs(++(cli->HistoryNewPoint));
		cli->History[cli->HistoryNewPoint].Command[0] = 0;
	}
	cli->HistoryPoint = cli->HistoryNewPoint;
	return CLI_OK;
}

/*---------------------------------------------------------------------------*/
/**
* @brief	Print element from history command.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
* @param	inc Step relative to the current position.
*
*/
static int cli_key_handler_print_element(cli_t *cli, int inc) {
	int temp = cli_utils_abs(cli->HistoryPoint + inc);
	if (cli->History[temp].Command[0] != 0) {
		cli->HistoryPoint = temp;
		cli->Point = strlen(cli->History[cli->HistoryPoint].Command);
		memcpy(cli->Buffer, cli->History[cli->HistoryPoint].Command, sizeof(cli->Buffer));
		cli_print_line(cli);
	}
	return CLI_OK;
}

/*---------------------------------------------------------------------------*/
/**
* @brief	A function that calculates a number modulo 'CLI_SIZE_HISTORY'. 
*       	Required to organize a circular buffer in the command history.
* @param	id Absolute number.
* @retval 	`int` [0 .. CLI_SIZE_HISTORY - 1].
*
*/
static int cli_utils_abs(int id) {
	if (id > CLI_SIZE_HISTORY - 1) {
		return (id - CLI_SIZE_HISTORY);
	}
	if (id < 0) {
		return (id + CLI_SIZE_HISTORY);
	}
	return id;
}

/*---------------------------------------------------------------------------*/
/**
* @brief	Function to set the cursor pointer in the console.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
* @param	inc An incrimination regarding an already active Point.
*
*/
static int cli_key_handler_set_point(cli_t *cli, int inc) {
	if (inc > 0) {
		/* inc Arrow Rigth */
		if (cli->Buffer[cli->Point]) {
			cli->Point++;
			cli_printf(cli, "%c%c%c", Key_ESC, Key_CONTROL, Key_C);
		}
	} else {
		/* inc Arrow Left */
		if (cli->Point) {
			cli->Point--;
			cli_printf(cli, "%c%c%c", Key_ESC, Key_CONTROL, Key_D);
		}
	}
	return CLI_OK;
}

/*---------------------------------------------------------------------------*/
/**
* @brief	The handler removes the character on the Right.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
*
*/
static int cli_key_handler_control_delete(cli_t *cli) {
	if (cli->Point) {
		for (int i = cli->Point; i < strlen(cli->Buffer); i++) {
			cli->Buffer[i] = cli->Buffer[i + 1];
		}
	}
	cli_print_line(cli);
	return CLI_OK;
}
