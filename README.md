### This version of a processor has the next commands: ###
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
