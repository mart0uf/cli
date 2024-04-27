# About the project.
The idea of creating a CLI(Command Line Interface) has been in my mind for a long time, since I started studying embedded systems. And very often, in order to debug some things, it was necessary to rebuild the project, connect the programmer and program the microcontroller, and so on every time. At some point, I wanted to have a tool that allowed me to execute simple commands. The very first version was raw and only handled letters and the 'Enter' key. At some point, I started to make mistakes and had to rewrite the entire team. That's how I came up with the idea to start processing other keyboard keys as well. In the end, this turned out to be a fairly handy tool for controlling and executing commands for the microcontroller. To write the functionality, I took the Terminal from Linux as an example. So I tried to be as much like him as possible.

# Features 
1. Processing of incoming commands and arguments.
2. Support for the history of previously launched commands.
3. When you press the Tab key, autocomplete occurs. CLI completes as much of the name as possible.
4. The cursor can now be moved with arrows on the keyboard.
5. Implemented handling of deletion using the 'Backspace' key and the 'Delete' key.
6. If the command crashes and returns a value other than zero, the CLI will report it.
7. The `console.h` header file contains the commands needed to configure the terminal in the design.
8. The CLI can be easily ported to any system, you just need to change the functions of sending and receiving a symbol.

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
