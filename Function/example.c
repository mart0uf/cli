/*
*******************************************************************************
@file	example.c
@brief	Examples of commands for the CLI.
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

#include "example.h"
#include <stdlib.h>

static int test_buffer[8];

/**
* @brief 	Command: Example function in CLI init.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
*/
int cli_example_init(cli_t *cli) {
	cli_add(cli, "example", cli_function_example, "Example command");
	cli_add(cli, "read_buffer", cli_function_read_buffer, "Read from test buffer");
	cli_add(cli, "write_buffer", cli_function_write_buffer, "Write to test buffer");
	return 0;
}

/**
* @brief 	Command: Example function in CLI. Read from test buffer.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
* @param  	argc Number of arguments passed to the function.
* @param 	argv[] Array of argument values.
* @return 	`int` Function success or error code.
* @retval 	(0) if success.
* @retval   Error code (!0) if error.
*/
int cli_function_read_buffer(cli_t *cli, int argc, char *argv[]) {
	/* Default */
	int start_address = 0;
	int count = 1;


	/* Parse */
	for (int i = 0; i < argc; i++) {
		if ((!strcmp(argv[i], "-h")) | (!strcmp(argv[i], "--help"))) {

			goto label_help;
		}

		if ((!strcmp(argv[i], "-c")) | (!strcmp(argv[i], "--count"))) {
			if (i > argc - 1) {
				cli_printf(cli, "Need more argument for -c (--count)\r\n");
				return EXIT_FAILURE;
			}
			count = (int)(strtol(argv[i + 1], NULL, 10));
		}

		if ((!strcmp(argv[i], "-a")) | (!strcmp(argv[i], "--all"))) {
			start_address = 0;
			count = 8;
			goto label_read;
		}
	}

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			start_address = (int)(strtol(argv[i + 1], NULL, 10));
			if (start_address + count > 8) {
				cli_printf(cli, "Invalid buffer address. Value must be [0 .. 7] and '--count' [8 .. 1]\r\n");
				return EXIT_FAILURE;
			}
			goto label_read;
		}
	}

label_help:
	cli_printf(cli, "Usage: %s [ADDRESS]\r\n", argv[0]);
	cli_printf(cli, "Value [ADDRESS] is must [0 .. 7]\r\n");
	cli_printf(cli, "Examples: %s 3 -c 2\r\n", argv[0]);
	cli_printf(cli, "Option: \r\n");
	cli_printf(cli, "\t-h, --help        print information about function\r\n");
	cli_printf(cli, "\t-c, --count       Number of items to read from the buffer.\r\n");
	cli_printf(cli, "\t-a, --all         Read all items from the buffer.\r\n");
	return EXIT_SUCCESS;

label_read:
	for (int i = 0; i < count; i++) {
		int index = start_address + i;
		cli_printf(cli, "buffer[%d]=0x%.4x\r\n", index, test_buffer[index]);
	}
	return EXIT_SUCCESS;
}

/**
* @brief 	Command: Example function in CLI. Write to test buffer.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
* @param  	argc Number of arguments passed to the function.
* @param 	argv[] Array of argument values.
* @return 	`int` Function success or error code.
* @retval 	(0) if success.
* @retval   Error code (!0) if error.
*/
int cli_function_write_buffer(cli_t *cli, int argc, char *argv[]) {
	/* Default */
	int start_address = 0;
	int index_address = 0;

	/* Parse */
	for (int i = 0; i < argc; i++) {
		if ((!strcmp(argv[i], "-h")) | (!strcmp(argv[i], "--help"))) {
			goto label_help;
		}

		if ((!strcmp(argv[i], "-c")) | (!strcmp(argv[i], "--clear"))) {
			goto label_clear;
		}
	}

	for (int i = 1; i < argc; i++) {
		start_address = (int) (strtol(argv[i], NULL, 10));
		if (start_address > 8) {
			cli_printf(cli,	"Invalid address. Value must be [0 .. 7]\r\n");
			return EXIT_FAILURE;
		}
		index_address = i;
		goto label_write;
	}

label_help:
	cli_printf(cli, "Usage: %s [ADDRESS] [VALUE_1] [VALUE_2]\r\n", argv[0]);
	cli_printf(cli, "Value [ADDRESS] is must [0 .. 7]\r\n");
	cli_printf(cli, "Examples: %s 3 \r\n", argv[0]);
	cli_printf(cli, "Option: \r\n");
	cli_printf(cli, "\t-h, --help        print information about function\r\n");
	cli_printf(cli, "\t-c, --clear       Clear the test buffer.\r\n");
	return EXIT_SUCCESS;

label_clear:
	for (int i = 0; i < 8; i++) {
		test_buffer[i] = 0;
	}
	return EXIT_SUCCESS;

label_write:
	int count = 0;
	for (int i = index_address; i < argc; i++) {
		if ((start_address + count) > 8 ){
			cli_printf(cli,	"Invalid value for address.\r\n");
			return EXIT_FAILURE;
		}
		if (argv[i][0] != '-') {
			test_buffer[start_address + count] = (int)(strtol(argv[i + 1], NULL, 10));
			count++;
		}
	}
	return EXIT_SUCCESS;
}



/**
* @brief 	Command: Example function in CLI. Print all argv.
* @param 	cli Is a pointer (`cli_t`) to the instance to be worked on.
* @param  	argc Number of arguments passed to the function.
* @param 	argv[] Array of argument values.
* @return 	`int` Function success or error code.
* @retval 	(0) if success.
* @retval   Error code (!0) if error.
*/
int cli_function_example(cli_t *cli, int argc, char* argv[]) {
	cli_printf(cli, "Example command\r\n");
	for (int i = 0; i < argc; i++) {
		cli_printf(cli, "\targv[%d] - '%s'\r\n", i, argv[i]);
	}
	return EXIT_SUCCESS;
}
