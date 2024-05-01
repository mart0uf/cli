# About the project.
The idea of creating a CLI(Command Line Interface) has been in my mind for a long time, since I started studying embedded systems. And very often, in order to debug some things, it was necessary to rebuild the project, connect the programmer and program the microcontroller, and so on every time. At some point, I wanted to have a tool that allowed me to execute simple commands. The very first version was raw and only handled letters and the 'Enter' key. At some point, I started to make mistakes and had to rewrite the entire team. That's how I came up with the idea to start processing other keyboard keys as well. In the end, this turned out to be a fairly handy tool for controlling and executing commands for the microcontroller. To write the functionality, I took the Terminal from Linux as an example. So I tried to be as much like him as possible.

# Features 
1. Processing of incoming commands and arguments.
   ![2024-04-30 10-22-59 (online-video-cutter com)(3)](https://github.com/mart0uf/cli/assets/104390290/1ef5d4a7-6507-4bf3-8e49-8135fc252278)
3. Support for the history of previously launched commands.
   ![2024-04-30 10-35-43 (online-video-cutter com)(1)](https://github.com/mart0uf/cli/assets/104390290/b817ff80-0e9e-4c5b-89c4-15e52a734ec7)
5. When you press the Tab key, autocomplete occurs. CLI completes as much of the name as possible.
   ![2024-04-30 10-22-59 (online-video-cutter com)(1)(1)](https://github.com/mart0uf/cli/assets/104390290/a9ac9742-e0c4-49b7-8fe1-c4f4a122bfd4)
6. The cursor can now be moved with arrows on the keyboard.
   ![2024-04-30 10-22-59 (online-video-cutter com)(2)(1)](https://github.com/mart0uf/cli/assets/104390290/c5c584d0-fbe2-4ef7-8f3d-8b75c39c4e1b)
8. Implemented handling of deletion using the 'Backspace' key and the 'Delete' key.
   ![2024-04-30 10-22-59 (online-video-cutter com)(1)](https://github.com/mart0uf/cli/assets/104390290/6290e580-3dfe-4445-b2ab-e678925b1f49)
10. If the command crashes and returns a value other than zero, the CLI will report it.
    ![2024-04-27 15-08-06 (online-video-cutter com) (online-video-cutter com)(3)(1)](https://github.com/mart0uf/cli/assets/104390290/28780123-7c50-451a-8652-bcae4445ba2d)
12. The `console.h` header file contains the commands needed to configure the terminal in the design.
13. The CLI can be easily ported to any system, you just need to change the functions of sending and receiving a symbol.

# Configuring the CLI
The main configuration of the CLI is done in the `opt.h` file.

- Parameter `CLI_PREFIX` - Prefix reflected on the console screen. The value must always be a string type.
- Parameter `CLI_BUFFER_SIZE` - Buffer size for commands and console. Adjust the buffer size to suit your needs. The value must always be an integer greater than 0.
- Parameter `CLI_MAX_COUNT_COMMAND` - Buffer size for commands and console. Adjust the buffer size to suit your needs. The value must always be an integer greater than 0.
- Parameter `CLI_SIZE_HISTORY` - Maximum number to write to the command run history. Adjust the buffer size to suit your needs. The value must always be an integer greater than 0. If you don't want to use the command history, it is recommended to set the value to 1 so as not to take up extra memory.
- Parameter `CLI_ENABLE_DELETE_COMMAND` - Allow dynamic deletion of commands. Use additional functions if you want to remove commands from the list during the execution of your program. The accepted value must be TRUE or FALSE.
- Parameter `CLI_USE_FULL_ASSERT` - Use the standard assert or light version for debugging CLI. The accepted value must be TRUE or FALSE.
- Parameter `CLI_CUSTOM_IO` - Use your sharing functions for the CLI. The accepted value must be TRUE or FALSE.
- Parameter `CLI_FOR_STM32_HAL` - Use an out-of-the-box HAL-based solution for STM32. The accepted value must be TRUE or FALSE.
- Parameter `CLI_FOR_ZYNQ` - Use an out-of-the-box for Zynq.
- Parameter `CLI_EXAMPLE_ENABLE` - Include sample functions for the CLI.

# Porting
You must set the `CLI_CUSTOM_IO` flag to `TRUE`. (In the `opt.h` file). For porting, you need to define the functions `__io_cli_putchar(int ch)` and `__io_cli_getchar(void)`. Example of CLI connection using CMSIS for STM32:
```c
/* This CMSIS is valid for STM32F1xx. */
#include "main.h"
#define CLI_UART USART1
int __io_cli_putchar(int ch) {
	while(1) {
		if (READ_BIT(CLI_UART->CR1, USART_CR1_TE)) {
			if ((CLI_UART->ISR & UART_FLAG_TXE)) {
				CLI_UART->TDR = ch;
				return 0;
			}
		}
	}
	return 0;

}

int __io_cli_getchar(void) {
	int ch = 0;
	if (READ_BIT(CLI_UART->CR1, USART_CR1_RE)) {
		if ((CLI_UART->ISR & USART_ISR_RXNE)) {
			ch = (int)CLI_UART->RDR;
		}
	}
	return ch;
}
```
# Use of ready-made solutions

## For STM32
It is necessary to set the `CLI_FOR_STM32_HAL` flag to `TRUE`, the `CLI_CUSTOM_IO` flag to `FALSE`  (In the `opt.h` file). In the `io.c` file, find the line:
```c
/* Parameter */	
#define CLI_UART huart1
```
Replace the handle `huart` (`UART_HandleTypeDef`) with the one you want.


## For Zynq
It is necessary to set the `CLI_FOR_ZYNQ` flag to `TRUE`, the `CLI_CUSTOM_IO` flag to `FALSE`  (In the `opt.h` file). In the 'io.c' file, find the line:
```c
/* Parameter */	
#include "xuartps_hw.h"
u32 BaseAddress = STDIN_BASEADDRESS;
```
Change `BaseAddress` the address to the one you want.

# Launching
```c
/* To get started, you need to call the function. */
cli_init(&cli0);

/* Define and add the features needed to work in the CLI. */
cli_add(&cli0, "example", cli_function_example, "Example command");
cli_add(&cli0, "read_buffer", cli_function_read_buffer, "Read from test buffer");
cli_add(&cli0, "write_buffer", cli_function_write_buffer, "Write to test buffer");

/* In the main loop, call the function. */
while(1) {
   cli_handler(&cli0);
}
```

# Additional Features
If you use the `CLI_ENABLE_DELETE_COMMAND` flag, you can remove functions from the CLI during the execution of commands. Functions can be deleted by ID (`cli_remove_id()`), name (`cli_remove_name()`), or function pointer (`cli_remove_ptr()`).

You can override the CLI write and read functions while the program is running. To do this, you need to assign these functions after initialization.
```c
cli_init(&cli0);
cli0._io_getchar = __io_getchar;
cli0._io_putchar = __io_putchar;
```

You can also initialize multiple CLI instances. To do this, you just need to declare them:
```c
cli_t cli1;
cli_init(&cli1);
...
```

# Programs on which the CLI runs
Command Line Interpreter was tested on `PuTTY` and `TeraTerm`. I can't guarantee stable performance in other programs. But I'd love for you to give me feedback.

# Next steps
I consider the further development of CLI in this context to be complete. What has now been implemented is quite enough for comfortable work. If there are any interesting development ideas, please let me know. If you find an error, please let us know.

