/*
*******************************************************************************
@file	function.c
@brief	Define simple functions for the CLI. 
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
#include "function.h"

/**
* @brief 	Command: Print in console all function.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
* @param  	argc Number of arguments passed to the function.
* @param 	argv[] Array of argument values.
* @return 	`int` Function success or error code.
* @retval 	(0) if success.
* @retval   Error code (!0) if error.
*/
int cli_function_help(cli_t *cli, int argc, char* argv[]) {
	cli_printf(cli, "CLI version: v%d.%d\r\n", CLI_VERSION_MAJOR, CLI_VERSION_MINOR);
	cli_printf(cli, "Data compiling: %s %s\r\n", __DATE__, __TIME__);
	cli_printf(cli, "Type 'help' to see this list commands.\r\n");
	cli_printf(cli, "List command:\r\n");
	for (int index = 0; index < CLI_MAX_COUNT_COMMAND; index++) {
		if (cli->Commands[index].Function != NULL) {
			cli_printf(cli, "\t%s - %s\r\n", cli->Commands[index].Name, cli->Commands[index].Help);
		}
	}
	return EXIT_SUCCESS;
}

/**
* @brief 	Command: Clear console CLI.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
* @param  	argc Number of arguments passed to the function.
* @param 	argv[] Array of argument values.
* @return 	`int` Function success or error code.
* @retval 	(0) if success.
* @retval   Error code (!0) if error.
*/
int cli_function_clear(cli_t *cli, int argc, char* argv[]) {
	cli_printf(cli, CONSOLE_CLEAR_TERMINAL);
	return EXIT_SUCCESS;
}
