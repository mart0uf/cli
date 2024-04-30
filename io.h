/*
*******************************************************************************
@file	io.h
@brief	A header file that contains definitions of the functions of reading and writing a character.
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

#ifndef CLI_IO_H_
#define CLI_IO_H_

/**
* @brief    Writes a character ch to CLI.
* @param  	ch Number of arguments passed to the function.
*/
extern int __io_cli_putchar(int ch) __attribute__((weak));

/**
* @brief    Reads the next character from the CLI.
* @return 	`int` A symbol read as an unsigned char and converted to an int.
*/
extern int __io_cli_getchar(void) __attribute__((weak));

#endif /* CLI_IO_H_ */
