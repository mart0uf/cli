/*
*******************************************************************************
@file	opt.h
@brief	CLI configuration file.
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

#ifndef CLI_OPT_H_
#define CLI_OPT_H_

#ifndef TRUE
#  define TRUE		1U
#endif

#ifndef FALSE
#  define FALSE		0U
#endif

/*****************************************************************************/
/* Prefix reflected on the console screen */
#define CLI_PREFIX                ">"

/* Buffer size for commands and console */
#define CLI_BUFFER_SIZE            32

/* Maximum number of possible commands */
#define CLI_MAX_COUNT_COMMAND      8

/* Maximum number to write to the command run history.
 * Compilation will create a buffer with the size of
 *   (CLI_MAX_COUNT_COMMAND * CLI_BUFFER_SIZE)
 */
#define CLI_SIZE_HISTORY           8

/* Allow dynamic deletion of commands. */
#define CLI_ENABLE_DELETE_COMMAND  FALSE

/* Use the standard assert or light version. */
#define CLI_USE_FULL_ASSERT        FALSE

/* Use your sharing functions for the CLI. */
#define CLI_CUSTOM_IO              FALSe
#if (CLI_CUSTOM_IO == FALSE)
/* Ready-to-use solution for platforms. */
#define CLI_FOR_STM32_HAL          TRUE
#if (CLI_FOR_STM32_HAL == FLASE)
#define CLI_FOR_ZYNQ               FALSe
#endif
#endif

/* Enable example function. */
#define CLI_EXAMPLE_ENABLE         TRUE

/*****************************************************************************/
/* Checking that the parameters are correct. */
#if CLI_BUFFER_SIZE < 0 
#error "'CLI_BUFFER_SIZE' must be greater than 0!"
#endif

#if CLI_MAX_COUNT_COMMAND < 0 
#error "'CLI_MAX_COUNT_COMMAND' must be greater than 0!"
#endif

#if CLI_SIZE_HISTORY < 0 
#error "'CLI_SIZE_HISTORY' must be greater than 0!"
#endif

#if CLI_SIZE_HISTORY < 0
#error "'CLI_SIZE_HISTORY' must be greater than 0!"
#endif

#endif /* CLI_OPT_H_ */
