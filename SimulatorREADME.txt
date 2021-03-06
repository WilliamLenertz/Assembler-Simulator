			!!!!!!READ ME FIRST!!!!!


Creators:

William Lenertz
Chao Zhou



Project 1 part 2: Simulator


			***Introduction***

Name: It’s_RISC

Welcome to our simulator, also known as It’s_RISC.

This is a very simple program that simulates the UST 3400 machine (Rip Van saWinkle). Before using this simulator, please read the following instructions for proper use

We do believe our simulator works for all assembly code input.



			 ***CONTENTS***

1.)Simulator.c:
- This file contains the code used to create It’s_RISC (the simulator).
- Please do not modify any of the contents in this file

2.)Makefile
- Use this to compile the Simulator.c file.
- when “make” is input into the command line, this will compile the Simulator.c file and output an executable file called “Simulator” and another file called “Simulator.o”

3.)README.txt
- This is the file you are reading right now. It provides the instructions, rules, and other information about the simulator before use.





			***Background***


It’s_RISC is designed to simulate the UST-3400 system. Please read background on assembly language for the UST-3400 before beginning to use this system. This includes what opcodes are allowed and how each type of instruction is formatted (R-type, I-type, J-type and O-type). This way, the machine code you input is correct for the UST-3400 machine.




			***Rules***

1.) Registers:
- As you should already know, the UST-3400 uses 8 registers (0-7). Please do not attempt to use more than 8 registers

2.) Memory
- This simulator has allocated enough memory for 512 32-bit inputs. Please do not exceed this memory ceiling.





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

2.) A Simulator.o file will appear as well as an executable file called “Simulator”


3.)Running the program

- The program needs a machine code file input from the command line as well as an output file. After creating your machine code file (possibly using the The_Big_Black_Box_That_Rocks!!! assembler), you can run it with the following command:

****************
./Simulator machineCodeName.txt outputFileName.txt
****************
- Obviously, use your own text file names in the command


4.)While It’s_RISC is running, it will output the machine state after each instruction is executed. This includes the current PC (program counter), contents of memory and the contents of each register.

- After completion (and if your assembly code/machine code was correct), a final number of instructions will be printed. This will tell you how many instructions were executed during the simulation


5.)After running the program, another file will appear. This will be the second text file you input into the command line. It will contain all of the machine state information that was printed to the screen as well as the final count of instructions executed

6.)When you are done with the simulator, you may run the following command to remove the executable “Simulator” file as well as the “Simulator.o” file:

****************
$make clean
****************

