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
