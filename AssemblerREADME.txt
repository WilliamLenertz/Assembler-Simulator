			!!!!!!READ ME FIRST!!!!!


Creators:

William Lenertz
Chao Zhou



Project 1 part 1: Assembler


			***Introduction***

Name:The_Big_Black_Box_That_Rocks!!!

Welcome! to our assembler also known as The_Big_Black_Box_That_Rocks!!!.

This is a very advanced assembler (super primitive though) specifically designed for the UST-3400 machine (Rip Van saWinkle). Before using this assembler please read the following rules and instructions for proper use.

We do believe this assembler works for all cases except when tabs are used for white space.





			***Contents***

1.)Assembler.c:
- This file contains the code used to create the assembler.
- Please do not modify any of the contents in this file

2.)Makefile
- Use this to compile the Assembler.c file.
- when “make” is input into the command line, this will compile the Assembler.c file and output an executable file called “Assembler” and another file called “Assembler.o”

3.)README.txt
- This is the file you are reading right now. It provides the instructions, rules, and other information about the assembler before use.




			***Background***


The_Big_Black_Box_That_Rocks!!! is designed only for the UST-3400 system. Please read background on assembly language for the UST-3400 before beginning to use this system. This includes what opcodes are allowed and how each type of instruction is formatted (R-type, I-type, J-type and O-type).







			***Rules***



1.) White Space: DO NOT USE TABS!!!!!
- We creators of The_Big_Black_Box_That_Rocks!!! believe in SPACES ONLY!!!!
- The_Big_Black_Box_That_Rocks!!! only allows for spaces to indicate white space. Any use of tabs or other means of indicating white space will result in assembly error.
- When writing the assembly code, ensure that all white space between fields are SPACES and nothing else.

2.)Label Format:
- All labels must be no more than 6 characters long
- All labels may only contain letters and numbers
- No label may start with a number
- If a label does not follow this format, the assembler will exit.

3.) Assembly Code Length:
- The_Big_Black_Box_That_Rocks!!! will allow for no more than 200 lines of assembly code.

4.)R-type instructions:
- R-type instructions must have 3 numbers following the opcode. They may not be labels or missing entirely. They also must represent registers in the range of [0,7]. The following are examples of valid R-type instructions (one includes a valid label):
- Comments are allowed at the end of the instruction

*********************
add 2 1 3
start nand 0 7 1
*********************

5.) I-type Instructions:
- I-type instructions must have 2 numbers immediately after the opcode. They must represent registers in the range [0,7].
- The 3rd input after the opcode may either be a number between the range of [-32768,32768] or a label.
- Comments are allowed at the end of the instruction

6.) J-Type Instructions:
- J-type instructions only need 2 numbers after the opcode. These numbers must represent registers in the range of [0,7].
- Comments are allowed at the end of the instruction

7.) O-Type Instructions:
- O-Type instructions should not have anything after the opcode.
- Labels in front of the opcodes are allowed
- Comments are allowed at the end of the instruction

8.) Assembler Directives:
- The only assembler directive allowed by the assembler is .fill.
- .fill must have a number immediately following it.
- Comments are allowed at the end of each instruction








			***Instructions for Use***


(assumes assembly code is written)

1.) Compiling
- First, place the .zip file into the desired location. Then open it
- 3 files and 1 directory should appear after unzipping.
- In a linux machine, change the cd to point to the directory your .zip file.
- run the command “make” in your linux command line. 

****************
$make
****************

2.) An Assembler.o file will appear as well as an executable file called “Assembler”


3.)Running the program
- The program needs an assembly code file input from the command line as well as an output file. After creating your assembly code file, you can run it with the following command:

****************
./Assembler assemblyCodeName.txt machineCodeName.txt
****************
- Obviously, use your own text file names in the command


4.)If your assembly code file was formatted correctly, the corresponding machine code will be printed to the screen as well as outputted to the output file you typed into the command line

5.)After running the program, at most 2 files will be outputted. One will be the name of the output file you typed into the command line. The other one will be titled “intermediateFile.txt”

- The intermediateFile.txt is used only for the assembler. You may open it if you like, but it will contain a copy of your assembly code without any labels at the beginning.

- You do not need to worry about the intermediateFile.txt because when you type the command “make clean” the intermediateFile.txt will be removed. You can use the following command:

****************
$make clean
****************


6.)To view the following machine code or any errors encountered, please open the “machineCodeName.txt” file using the “less” command. Please note that the machine code will also be printed to the screen for your convenience.


