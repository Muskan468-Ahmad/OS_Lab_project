# OS_Lab_project
## Custom Terminal Project in C Language

### Introduction
THE MYSH PROJECT INVOLVES THE DEVELOPMENT OF A CUSTOM TERMINAL
SHELL WRITTEN IN C. THE GOAL IS TO CREATE A LIGHTWEIGHT AND SIMPLE
TERMINAL THAT SIMULATES THE BEHAVIOR OF COMMON UNIX/LINUX
SHELLS. THE TERMINAL SUPPORTS EXECUTING EXTERNAL COMMANDS,
BUILT-IN COMMANDS LIKE CD AND EXIT, INPUT/OUTPUT REDIRECTION, AND
PIPING. IT IS A FOUNDATIONAL TOOL FOR LEARNING ABOUT PROCESS
CONTROL, SYSTEM CALLS, AND BASIC SHELL FUNCTIONALITIES IN
OPERATING SYSTEMS.

### Features
THE CUSTOM TERMINAL, MYSH, IMPLEMENTS SEVERAL FEATURES TYPICAL OF A
LINUX SHELL. THE FUNCTIONALITIES INCLUDE:
BUILT-IN COMMANDS:
EXIT: EXITS THE SHELL PROGRAM, TERMINATING THE USER SESSION.
CD <DIRECTORY>: CHANGES THE CURRENT WORKING DIRECTORY TO THE
SPECIFIED DIRECTORY. THIS COMMAND MIMICS THE FUNCTIONALITY OF THE CD
COMMAND IN BASH.
#### EXTERNAL COMMAND EXECUTION
THE SHELL SUPPORTS RUNNING ANY EXTERNAL COMMAND AVAILABLE IN THE
SYSTEM'S PATH, SUCH AS LS, PWD, CAT, AND MORE. THESE COMMANDS ARE
EXECUTED IN CHILD PROCESSES CREATED BY FORK(), AND THEIR OUTPUT IS
DISPLAYED IN THE TERMINAL.
#### INPUT AND OUTPUT REDIRECTION
OUTPUT REDIRECTION (>): THE SHELL ALLOWS THE OUTPUT OF A COMMAND TO
BE REDIRECTED INTO A FILE, OVERWRITING THE EXISTING FILE IF IT EXISTS.
INPUT REDIRECTION (<): THE SHELL ALSO ALLOWS READING FROM A FILE TO
PROVIDE INPUT TO COMMANDS.
#### PIPING
THE SHELL SUPPORTS PIPING, WHERE THE OUTPUT OF ONE COMMAND IS USED
AS THE INPUT FOR THE NEXT. THIS IS ACHIEVED BY CONNECTING COMMANDS
THROUGH PIPES (|).
#### PROCESS MANAGEMENT
THE TERMINAL ALLOWS COMMANDS TO BE EXECUTED IN THE BACKGROUND
USING &. THIS PREVENTS THE TERMINAL FROM WAITING FOR THE PROCESS TO
FINISH BEFORE ACCEPTING NEW COMMANDS.

### DESIGN AND IMPLEMENTATION
#### Main Loop
THE MAIN LOOP READS USER INPUT, PARSES THE COMMAND,
AND DETERMINES THE TYPE OF COMMAND (WHETHER IT'S
BUILT-IN, EXTERNAL, INVOLVES REDIRECTION, OR USES
PIPING).

### Command Execution:
When a command is entered, the executeCommand function is responsible for parsing and executing it.

### Redirection Handling:
Redirection (>, <) is implemented by modifying the file descriptors using dup2().

### Background Execution:
Background execution is implemented by checking for the & symbol at the end of a command
If a command ends with &, the shell executes it in the background without waiting for the process to finish.

### EXAMPLES OF COMMANDS:

![image](https://github.com/user-attachments/assets/3738827c-c0a4-4e15-aab0-f9d444b16262)

### Applications:
Highlight practical applications of building a shell:
•	Learning Purpose: Understand process control, system calls, and inter-process communication.
•	Foundation for Advanced Shells: Build more complex tools like task automation or custom scripting environments.
### Conclusion:
The mysh project is a basic shell implementation that demonstrates core features of a terminal, including command execution, built-in commands, redirection, piping, and background processes. While it lacks some of the advanced features of a full Linux shell, it provides a solid foundation for understanding how shells operate at a system level. Further improvements can be made to add more functionality, robustness, and user-friendly features.







