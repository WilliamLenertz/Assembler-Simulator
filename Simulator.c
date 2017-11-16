//
//  Simulator.c
//  Simulator
//
//  Created by William Lenertz on 3/6/17.
//  Copyright © 2017 William Lenertz/Chao Zhou. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>




//Function Prototypes
int init_Registers();
int init_Memory();
int convertNum(int num);
int machineCycler(int pc);
int print_State(int pc);
int printFinalStats(int numInstr);


int registerFile[8];
int numMemory;
int dataMem[512];


//Input File
FILE *f;
//Output File
//This will have our data after each cycle and other stats
FILE *out;


int main(int argc, const char * argv[]) {
    
    
    init_Registers();
    init_Memory();
    
    
    f = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    
    
    //Initialize registers and memory.
    
    init_Registers();
    init_Memory();
    
    
    //Populate instruction Memory with all machine code
    //Machine code addressed by index in array
    int size = 32;
    char line[size];
    int i = 0;
    char *lineCopy;
    int instruction;
    numMemory = 0;
    while (fgets(line, size, f)) {
        lineCopy = strdup(line);
        instruction = (int)strtol(lineCopy, NULL, 10);
        dataMem[numMemory] = instruction;
        numMemory++;
    }
    
    //close input file
    fclose(f);
    
    
    //Begin simulation
    
    int initPC = 0;
    
    
    //Begin cycling through machine code
    machineCycler(initPC);
    
    //close output file
    fclose(out);
    
    return 0;
}

//Heart of simulator. Loops through code until halt is reached.
//Increments pc based on opcode.
//Reads instruction at pc
int machineCycler(int pc){
    int numInstr = 0;
    
    
    
    int opcode = 0;
    int instruction;
    
    int a,b,c;
    
    int offset; //for lw, sw and beq sign extension
    
    
    while (opcode != 6) {
        
        print_State(pc);
        numInstr++;
        
        
        
        instruction = dataMem[pc];
        
        opcode = (instruction>>22);
        
        switch (opcode) {
            case 0://add
                a = (instruction>>19)&7;
                b = (instruction>>16)&7;
                c = (instruction&7);
                
                registerFile[c] = registerFile[a] + registerFile[b];
                
                pc++;
                
                break;
            case 1://nand
                a = (instruction>>19)&7;
                b = (instruction>>16)&7;
                c = (instruction&7);
                
                registerFile[c] = (~(registerFile[a] & registerFile[b]));
                
                
                pc++;
                break;
            case 2://lw
                a = (instruction>>19)&7;
                b = (instruction>>16)&7;
                c = (instruction&0xFFFF);
                
                offset = convertNum(c);
                
                registerFile[a] = dataMem[registerFile[b] + offset];
                
                pc++;
                
                break;
            case 3://sw
                a = (instruction>>19)&7;
                b = (instruction>>16)&7;
                c = (instruction&0xFFFF);
                
                offset = convertNum(c);
                
                
                dataMem[registerFile[b] + offset] = registerFile[a];
                numMemory++;
                
                pc++;
                
                break;
            case 4://beq
                a = (instruction>>19)&7;
                b = (instruction>>16)&7;
                c = (instruction&0xFFFF);
                
                offset = convertNum(c);
                
                if (registerFile[a] == registerFile[b]) {
                    pc = (pc+1) + offset;
                }
                else{
                    pc++;
                }
                
                break;
            case 5://jalr
                a = (instruction>>19)&7;
                b = (instruction>>16)&7;
                
                if (registerFile[a] == registerFile[b]) {
                    pc++;
                }else{
                    registerFile[a] = pc+1;
                    pc = registerFile[b];
                }
                
                break;
            case 6://halt
                printf("System Halted\n");
                printFinalStats(numInstr);
                exit(0);
                
                
                
            case 7://noop
                a = (instruction>>19)&7;
                
                pc++;
    
                break;
            default:
                printf("System Terminated: Halt not reached\n");
                printFinalStats(numInstr);
                break;
        }
    }
    
    
    
    return 0;
}





//sign extend.
int convertNum(int num){
    // convert a 16-bit number into a 32-bit integer
    //accounts for negatives by padding with 1's
    if (num & (1<<15) ){
        num -= (1<<16);
    }
    return(num);
}



//initialize registers to 0
int init_Registers(){
    
    for (int i = 0; i<8; i++) {
        registerFile[i] = 0;
    }
    
    return 0;
}

//initialize memory to 0
int init_Memory(){
    
    for (int i = 0; i<200; i++) {
        dataMem[i] = 0;
    }
    
    return 0;
}


//print current state of memory and registers
int print_State(int pc){
    printf("@@@\nstate:\n");
    fprintf(out, "@@@\nstate:\n");
    
    printf("    PC: %d\n\n",pc);
    fprintf(out,"    PC: %d\n\n",pc);
    printf("    Memory:\n");
    fprintf(out,"    Memory:\n");
    
    int j = 0;
    for (j = 0; j<numMemory; j++) {
        printf("        mem[%d]=%d\n",j,dataMem[j]);
        fprintf(out, "        mem[%d]=%d\n",j,dataMem[j]);
    }
    printf("\n");
    fprintf(out, "\n");
    
    int i = 0;
    printf("    Registers\n");
    for (i = 0; i<8; i++){
        printf("        Register[%d]=%d\n",i,registerFile[i]);
        fprintf(out, "        Register[%d]=%d\n",i,registerFile[i]);
    }
    
    printf("End State\n\n");
    fprintf(out,"\nEnd State\n\n");
    
    return 0;
}


//print final stats after execution.
int printFinalStats(int numInstr){
    
    
    printf("INSTRUCTIONS: %d\n\n", numInstr);
    fprintf(out, "INSTRUCTIONS: %d\n\n", numInstr);
    
    return 0;
}

