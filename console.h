/*
*******************************************************************************
@file	console.h
@brief	Header file for comfortable use of the console. Includes changing
        styles, colors, and commands to clean up the console and string.
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
#ifndef CLI_CONSOLE_H_
#define CLI_CONSOLE_H_

/** Font styles. **/
#define CONSOLE_NORMAL           "\033[0m"
#define CONSOLE_BOLD             "\033[1m"
#define CONSOLE_FADED            "\033[2m"
#define CONSOLE_ITALIC           "\033[3m"
#define CONSOLE_UNDERLINE        "\033[4m"
#define CONSOLE_BLINK            "\033[5m"
#define CONSOLE_DOUBLE_UNDERLINE "\033[9m"

/* Set Console background color */
#define CONSOLE_BACKGROUND_COLOR_BLACK  "\033[40m"
#define CONSOLE_BACKGROUND_COLOR_RED    "\033[41m"
#define CONSOLE_BACKGROUND_COLOR_GREEN  "\033[42m"
#define CONSOLE_BACKGROUND_COLOR_YELLOW "\033[43m"
#define CONSOLE_BACKGROUND_COLOR_BLUE   "\033[44m"
#define CONSOLE_BACKGROUND_COLOR_PURPLE "\033[45m"
#define CONSOLE_BACKGROUND_COLOR_CYAN   "\033[46m"
#define CONSOLE_BACKGROUND_COLOR_WHITE  "\033[47m"

/* Set Console color */
#define CONSOLE_COLOR_RED    "\033[91m"
#define CONSOLE_COLOR_STD    "\033[39m"
#define CONSOLE_COLOR_GREEN  "\033[92m"
#define CONSOLE_COLOR_BULE   "\033[94m"

/* Cleaning  */
#define CONSOLE_CLEAR_TERMINAL   "\033c"
#define CONSOLE_CLEAR_STRING     "\033[K"

/** Input **/

/*

URL: https://www.cs.cmu.edu/~pattis/15-1XX/common/handouts/ascii.html

Dec  Char                           Dec  Char     Dec  Char     Dec  Char
---------                           ---------     ---------     ----------
  0  NUL (null)                      32  SPACE     64  @         96  `
  1  SOH (start of heading)          33  !         65  A         97  a
  2  STX (start of text)             34  "         66  B         98  b
  3  ETX (end of text)               35  #         67  C         99  c
  4  EOT (end of transmission)       36  $         68  D        100  d
  5  ENQ (enquiry)                   37  %         69  E        101  e
  6  ACK (acknowledge)               38  &         70  F        102  f
  7  BEL (bell)                      39  '         71  G        103  g
  8  BS  (backspace)                 40  (         72  H        104  h
  9  TAB (horizontal tab)            41  )         73  I        105  i
 10  LF  (NL line feed, new line)    42  *         74  J        106  j
 11  VT  (vertical tab)              43  +         75  K        107  k
 12  FF  (NP form feed, new page)    44  ,         76  L        108  l
 13  CR  (carriage return)           45  -         77  M        109  m
 14  SO  (shift out)                 46  .         78  N        110  n
 15  SI  (shift in)                  47  /         79  O        111  o
 16  DLE (data link escape)          48  0         80  P        112  p
 17  DC1 (device control 1)          49  1         81  Q        113  q
 18  DC2 (device control 2)          50  2         82  R        114  r
 19  DC3 (device control 3)          51  3         83  S        115  s
 20  DC4 (device control 4)          52  4         84  T        116  t
 21  NAK (negative acknowledge)      53  5         85  U        117  u
 22  SYN (synchronous idle)          54  6         86  V        118  v
 23  ETB (end of trans. block)       55  7         87  W        119  w
 24  CAN (cancel)                    56  8         88  X        120  x
 25  EM  (end of medium)             57  9         89  Y        121  y
 26  SUB (substitute)                58  :         90  Z        122  z
 27  ESC (escape)                    59  ;         91  [        123  {
 28  FS  (file separator)            60  <         92  \        124  |
 29  GS  (group separator)           61  =         93  ]        125  }
 30  RS  (record separator)          62  >         94  ^        126  ~
 31  US  (unit separator)            63  ?         95  _        127  DEL

 */


/* ASCII character codes */
/*
*  @brief Symbols that are used for CLI processing. 
*/
enum keyboard {
	Key_BS = 8,
	Key_TAB = 9,

	Key_VT= 11,

	Key_CR = 13,

	Key_ESC = 27,

	Key_SPACE = 32,  /* ' ' */

	Key_3 = 51,  /* '3' */

	Key_A = 65,  /* 'A' */
	Key_B = 66,  /* 'B' */
	Key_C = 67,  /* 'C' */
	Key_D = 68,  /* 'D' */

	Key_CONTROL = 91, /* '[' control characters */

	Key_Tilda = 126,  /* '~' */
	Key_DEL = 127
};

#endif /* CLI_CONSOLE_H_ */
