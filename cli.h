/*
*******************************************************************************
@file	cli.h
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

#ifndef CLI_H_
#define CLI_H_

/* Includes ---------------------------------------------------------------- */
#include <stdio.h>   /* For 'vsniprintf' and BUFSIZ */
#include <string.h>  /* For 'strlen' */
#include <stdarg.h>  /* For 'va_list' */

#include "opt.h"
#include "console.h"
/*---------------------------------------------------------------------------*/


/* Includes ---------------------------------------------------------------- */
/* *** Version <CLI_VERSION_MAJOR>.<CLI_VERSION_MINOR>*** */
#define CLI_VERSION_MAJOR 1
#define CLI_VERSION_MINOR 0
/*---------------------------------------------------------------------------*/


/* Typedef ------------------------------------------------------------------*/
/*
 * @brief	CLI handle Structure definition
 */
typedef struct cli_instance cli_t;

/*
 * @brief	Defining Options and Running Commands
 */
typedef struct {
	const char *Name;                      // Name function
	int (*Function)(cli_t *cli, int argc, char* argv[]); // Pointer to the implementation
	const char *Help;                      // Help information
} cli_command_t;

/*
 * @brief	Defining a Command List
 */
typedef struct {
	char Command[CLI_BUFFER_SIZE];     // Name function
} cli_command_history_t;

/*
 * @brief	CLI handle Structure definition
 */
struct cli_instance {
	int (*_io_putchar)(int ch);                      // Function transmit char
	int (*_io_getchar)(void);                        // Function receiver char
	char Buffer[CLI_BUFFER_SIZE];                    // Receive buffer
	int  Point;                                      // Cursor/pointer in Receive Buffer
	cli_command_t Commands[CLI_MAX_COUNT_COMMAND];   // All list command for shell
	cli_command_history_t History[CLI_SIZE_HISTORY]; // List history command
	int  HistoryPoint;                               // Cursor/pointer history command
	int  HistoryNewPoint;                            // Cursor/pointer new history command
};

/*
 * @brief	CLI Status structures definition
 */
typedef enum {
	CLI_OK = 0U,
	CLI_ERROR = !CLI_OK
} cli_error_t;
/*---------------------------------------------------------------------------*/


/* Instance Definition ----------------------------------------------------- */
extern cli_t cli0;
/*---------------------------------------------------------------------------*/


/* NOTE A description of the functions is provided in 'cli.c'. */
/* Function instances ------------------------------------------------------ */

extern int __cli_print_hello(cli_t *cli) __attribute__((weak));

int cli_init(cli_t *cli);
int cli_printf(cli_t *cli, const char* format, ...);
int cli_add(cli_t *cli, const char *name, int (*function)(cli_t *cli, int argc, char* argv[]), const char *help);
int cli_handler(cli_t *cli);

#if (CLI_ENABLE_DELETE_COMMAND == TRUE)
int cli_remove_id(cli_t *cli, int index);
int cli_remove_name(cli_t *cli, const char* name);
int cli_remove_ptr(cli_t *cli, int (*function)(cli_t *cli, int argc, char* argv[]));
#endif
/*---------------------------------------------------------------------------*/

#endif /* CLI_H_ */
