# CPU

This repository includes my CPU emulator, Assembler, and Disassembler. The processor has a standard set of commands such as push, pop, math commands (add, mul, ...), jump commands (call, jae), draw, out, and more. It also has RAM and video memory, so you can fill it and then display it, thus displaying pictures or even videos. The assembler translates a text file into bytecode, which the processor executes. The disassembler performs the reverse task.

## Table of Contents

- [Introduction](#introduction)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Commands](#commands)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The CPU emulator in this repository simulates the behavior of a processor that can execute a standard set of commands, has RAM and video memory, and can perform various tasks such as displaying pictures or videos. The Assembler and Disassembler tools are used to convert text files into bytecode and vice versa.

## Requirements

To use the CPU emulator, Assembler, and Disassembler in this repository, you need to have the following:

- C++ Compiler (GCC, Clang, or MSVC)
- SFML Library

## Installation

To install the CPU emulator, Assembler, and Disassembler, you can clone this repository using the following command:

```
git clone https://github.com/vorontsov-amd/CPU.git
```

Then, navigate to the `CPU` directory and compile the code using your preferred C++ compiler. You also need to install the SFML library and link it to your project.

## Usage

The CPU emulator, Assembler, and Disassembler in this repository can be used to write and execute assembly language programs. Here's an overview of the tools available in this repository:

- `Processor.cpp`: This file contains the implementation of the CPU emulator.
- `assembler.cpp`: This file contains the implementation of the Assembler tool.
- `disassembler.cpp`: This file contains the implementation of the Disassembler tool.

To use these tools, you need to write an assembly language program in a text file, assemble it using the Assembler tool, and then execute it using the CPU emulator. You can also disassemble the bytecode back into assembly language using the Disassembler tool.

## Commands
- push
  - push value        - push the number to stack
  - push [index]      - push the value from ram[index]
  - push registername - push the value from register 

- pop 
  - pop value         - pop the number from stack
  - pop [index]       - pops the value to ram[index]
  - pop registername  - pop the value from register 

- add  - add to numbers 
- sub  - subtract one number from another
- mul  - multiply two numbers
- div  - divide two numbers
- sqrt - extract the root of a number

- in - reads a number from the user and puts it on the stack

- out - print the last number in stack

- jump label - jump to the label
Take two numbers from stack: a, then b
- ja  - jump if a >  b 
- jae - jump if a >= b
- jb  - jump if a <  b
- jbe - jump if a <= b
- je  - jump if a == b
- jne - jump if a != b

- call FunctionName - call the function FunctionName    

- return - return from function to the main function

- HLT - ends the program

- scan
- draw
- stop


## Contributing

If you want to contribute to this project, feel free to submit a pull request.

## License

This project is licensed under the [MIT License](https://github.com/vorontsov-amd/CPU/blob/main/LICENSE).

