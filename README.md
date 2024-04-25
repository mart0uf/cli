# About the project.
The idea of creating a CLI(Command Line Interface) has been in my mind for a long time, since I started studying embedded systems. And very often, in order to debug some things, it was necessary to rebuild the project, connect the programmer and program the microcontroller, and so on every time. At some point, I wanted to have a tool that allowed me to execute simple commands. The very first version was raw and only handled letters and the 'Enter' key. At some point, I started to make mistakes and had to rewrite the entire team. That's how I came up with the idea to start processing other keyboard keys as well. In the end, this turned out to be a fairly handy tool for controlling and executing commands for the microcontroller. To write the functionality, I took the Terminal from Linux as an example. So I tried to be as much like him as possible.

# Features 
1. Processing of incoming commands and arguments.
2. Support for the history of previously launched commands.
3. When you press the Tab key, autocomplete occurs. CLI completes as much of the name as possible.
4. The cursor can now be moved with arrows on the keyboard.
5. Implemented handling of deletion using the 'Backspace' key and the 'Delete' key.
6. If the command crashes and returns a value other than zero, the CLI will report it.
7. The console.h header file contains the commands needed to configure the terminal in the design.
8. The CLI can be easily ported to any system, you just need to change the functions of sending and receiving a symbol.


