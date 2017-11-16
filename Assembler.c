//
//  main.c
//  assembler
//
//  Created by William Lenertz and Chao Zhou on 2/20/17.
//  Copyright © 2017 William Lenertz, Chao Zhou. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



//function prototype declaration
int passOne(FILE *f, FILE *out);
int passTwo(FILE *f, FILE *output);
int isOpcode(char * item);
int isValidLabel(char * item);
int checkLabel(char *label);
int rTypeAssembly(char * input[5]);
int iTypeAssembly(char * input[5]);
int jTypeAssembly(char * input[5], int pc);
int oTypeAssembly(char * input[5]);
int otherType(char *input[5]);





//Global Lists
char *opList[8][3] = {{"add","000","r"} , {"nand","001","r"} , {"lw","010", "i"} ,{"sw","011","i"} , {"beq","100","i"} ,
    {"jalr","101","j"} , {"halt","110","o"} , {"noop","111","o"}};

char *regList[8] = {"000","001","010","011","100","101","110","111"};

char *labelTable[200] = {NULL};



//PC iterator

int pc = 0;
int firstPass = 0;


//File that will contain machine code
FILE *finalOut;


//Main Function
int main(int argc, char * argv[]) {
    
    
    FILE *f;
    FILE *middleFile;

    f = fopen(argv[1], "r");
    middleFile = fopen("./intermediateFile.txt", "w+");
    
    finalOut = fopen(argv[2], "w");
    
    
    passOne(f,middleFile);
    fclose(f);
    
    
    passTwo(middleFile, finalOut);
    fclose(middleFile);
    fclose(finalOut);
    
    
    return 0;
}////////////////END: main() Method





int passOne(FILE *f, FILE *out){
    
    int size = 256;
    char *token = NULL;
    char line[size];
    
    int lineIndex = 0;
    int labelIndex = 0;
    
    int i = 0;
    
    //Read from input file
    while (fgets(line, size, f)) {
        char *lineArray[5] = {NULL};
        if((token = strtok(line, " \n")) != NULL){
            
            
            
            
            do {
                if (i>4) {
                    break;
                }
                
                lineArray[i] = token;
                char * label = strdup(token);
                
                if (i == 0){
                    if ((isOpcode(token)) ==  -1) {
                        if ((isValidLabel(token)) == 1){
                            labelTable[lineIndex] = label;
                        }
                        else{
                            exit(0);
                        }
                    }
                }
                
                
                i++;
                
                
                
                
                
                
            } while ((token = strtok(NULL, " \n")));
            
            
            
            
            //Write to Intermediate File
            //No labels written
            int q;
            for (q = 0; q<5; q++) {
                
                if (lineArray[q] != NULL) {
                    if (q == 0 && (checkLabel(lineArray[q])) == -1) {
                        fputs(lineArray[q], out);
                        fputs(" ", out);
                        
                    }
                    else if (q > 0){
                        fputs(lineArray[q], out);
                        fputs(" ",out);
                    }
                }
            }
            fputs(" \n",out);
            
            
        }
        
        firstPass++;
        i = 0;
        labelIndex++;
        lineIndex ++;
    }
    
    
    
    return 0;
}///////////END: passOne() method



int passTwo(FILE *f, FILE *output){
    
    
    rewind(f);
    
    int size = 100;
    char *token = NULL;
    char line[size];
    
    int lineIndex = 0;
    int labelIndex = 0;
    
    int i = 0;
    
    //Reade from intermediate file
    while (fgets(line, size, f)) {
        char *lineArray[5] = {NULL};
        if((token = strtok(line, " \n")) != NULL){
            
            do {
                if (i>4) {
                    break;
                }
                
                lineArray[i] = token;
                
                i++;
                
                
                
            } while ((token = strtok(NULL, " ")));
            
            
            //Check opcode and go to correct function
            if (lineArray[0] != NULL) {
                int checkOp = isOpcode(lineArray[0]);
                
                if (checkOp == -1) {
                    otherType(lineArray);
                }else {
                    if (strcmp(lineArray[0],"add") == 0 || strcmp(lineArray[0],"nand") == 0) {
                        rTypeAssembly(lineArray);
                    }else if (strcmp(lineArray[0],"lw") == 0 || strcmp(lineArray[0],"sw") == 0
                              || strcmp(lineArray[0],"beq") == 0){
                        iTypeAssembly(lineArray);
                        
                    }
                    else if ((strcmp(lineArray[0],"halt\n")) == 0 ||(strcmp(lineArray[0],"halt")) == 0 || (strcmp(lineArray[0],"noop")) == 0){
                        oTypeAssembly(lineArray);
                        
                    }else if (strcmp(lineArray[0],"jalr") == 0){
                        jTypeAssembly(lineArray, pc);
                        
                    }else{
                        printf("Invalid Opcode: %s: Not Listed\n",lineArray[0]);
                        exit(0);
                    }
                    
                    
                }
                
            }
            
            pc++;
            
            
            
            
        }
        
        
        i = 0;
        labelIndex++;
        lineIndex ++;
    }
    
    return 0;
}///////////END: passTwo() method



//Check for opcode.
//Returns opcode index or -1
int isOpcode(char * item){
    int check = -1;
    
    
    
    int i;
    for (i = 0; i<8; i++) {
        if (strcmp(item,opList[i][0]) == 0 || item == opList[i][0]) {
            check = i;
            return check;
        }
    }
    
    return check;
}//////////END: isOpcode() method



//Error checks all labels
int isValidLabel(char * item){
    
    int check = 1;
    int len = strlen(item);
    if (len > 6 || len < 1) {
        printf("Invalid Label: %s : Label must be between 1 and 6 characters\n", item);
        exit(0);
    }
    
    int val;
    //if label starts with 0
    if ((isdigit(item[0]))) {
        printf("Invalid Label: %s : Cannot begin with a number\n", item);
        exit(0);
    }
    //if label starts with 1-9
    else if ((val = atoi(&item[0]))) {
        printf("Invalid Label: %s : Cannot begin with a number\n", item);
        exit(0);
    }
    else{
        int j;
        for (j = 0; j < len; j++) {
            if (!isalnum(item[j])) {
                printf("Invalid Label: %s : Can only contain numbers and letters\n", item);
                exit(0);
            }
        }
    }
    
    //repeat label error
    int k;
    for (k = 0; k<20; k++) {
        if (labelTable[k] != NULL && (strcmp(item, labelTable[k])) == 0) {
            printf("Repeat Label Error: %s\n", item);
            exit(0);
        }
    }
    
    return check;
}///////////END: isValidLabel() method


//Checks if label is in labelTable
//Returns index of label or -1
int checkLabel(char *label){
    
    int check = -1;
    char * justLabel;
    
    int i = 0;
    while (i < 200) {
        if (labelTable[i] != NULL && label != NULL) {
            
            justLabel = strtok(label, "\n");
            
            if (strcmp(label, labelTable[i]) == 0) {
                check = i;
            }
        }
        i++;
    }
    
    return check;
    
}


int rTypeAssembly(char * input[5]){
    
    char result[256];
    
    
    char *opcode = input[0];
    char *binOp = NULL;
    if ((strcmp(opcode, "add")) == 0) {
        binOp = "000";
    }else if ((strcmp(opcode, "nand")) == 0){
        binOp = "001";
    }
    
    char *destReg = input[1];
    if (destReg == NULL) {
        printf("destRegister: %s\n",destReg);
        printf("1.)Invalid Register at address: %d\n",pc);
        exit(0);
    }
    
    char *regA = input[2];
    if (regA == NULL) {
        printf("RegisterA: %s\n",regA);
        printf("Invalid A Register at address: %d\n",pc);
        exit(0);
    }
    char *regB = input[3];
    if (regB == NULL) {
        printf("Invalid B Register at address: %d\n",pc);
        exit(0);
    }
    
    int destIndex;
    int aIndex;
    int bIndex;
    
    if ((strcmp(destReg, "0")) == 0) {
        destIndex = 0;
    }else if((destIndex = atoi(destReg))){
        destIndex = atoi(destReg);
    }else{
        printf("destRegister: %s\n",destReg);
        printf("2.)Invalid Register at address: %d\n",pc);
        exit(0);
    }
    
    if ((strcmp(regA, "0")) == 0) {
        aIndex = 0;
    }else if ((aIndex = atoi(regA))){
        aIndex = atoi(regA);
    }else{
        printf("3.)Invalid Register at address: %d\n",pc);
        exit(0);
    }
    
    if ((strcmp(regB, "0")) == 0) {
        bIndex = 0;
    }else if ((bIndex = atoi(regB))){
        bIndex = atoi(regB);
    }else{
        printf("4.)Invalid Register at address: %d\n",pc);
        exit(0);
    }
    
    char *binDest = regList[destIndex];
    char *binA = regList[aIndex];
    char *binB = regList[bIndex];
    
    
    sprintf(result,"0000000%s%s%s0000000000000%s",binOp,binA,binB,binDest);
    fprintf(finalOut, "%ld\n",strtol(result, NULL, 2));
    printf("%ld\n",strtol(result, NULL, 2));
    
    return 0;
}




int iTypeAssembly(char * input[5]){
    
    char *opcode = input[0];
    int intOp = isOpcode(opcode);
    
    
    char * destR, *source, *offset = NULL;
    
    int intDest = -1, intSource = -1, intOffset = -1;
    
    int i;
    for (i = 1; i<4; i++) {
        if (i == 1) {
            destR = input[i];
            if (destR == NULL) {
                printf("Invalid Register at address: %d\n",pc);
                exit(0);
            }
            if ((strcmp(destR, "0")) == 0) {
                intDest = 0;
            }
            else if ((intDest = atoi(destR))) {
                if (intDest < 0 || intDest > 7) {
                    printf("Error at line %d: Destination register out of range\n",pc);
                    printf("Destination Register: %d\n",intDest);
                    exit(0);
                }
            }else{
                printf("Invalid assembly Instruction at line: %d\n", pc);
                printf("Cannot assemble instruction: %s \n", destR);
                printf("Term must be a register between 0 and 7\n\n");
                exit(0);
            }
            
            
        }else if (i == 2) {
            source = input[i];
            if ((checkLabel(source)) != -1) {
                intSource = checkLabel(source);
                
            }
            else if ((strcmp(source, "0")) == 0){
                intSource = 0;
            }else if ((intSource = atoi(source))){
                if (intSource < 0 || intSource > 7) {
                    printf("Error at line %d: Source register out of range\n",pc);
                    printf("Source Register: %d\n",intSource);
                    exit(0);
                }else{
                    intSource = atoi(source);
                }
            }else{
                printf("Error at line %d: Invalid source register\n",pc);
                printf("Source Register:||%s||\n",source);
                
                exit(0);
            }
        }
        
        else if (i == 3) {
            offset = input[i];
            if((checkLabel(offset)) != -1){
                intOffset = checkLabel(offset);
                
                
            }else if ((strcmp(offset, "0")) == 0){
                intOffset = 0;
            }
            else if ((intOffset = atoi(offset))){
                if (intOffset < -32768 || intOffset > 32768 ) {
                    printf("Error at line %d: Offset Is too large/small\n",pc);
                    exit(0);
                }
            }else{
                printf("Error at line %d: Invalid offset\n",pc);
                printf("Invalid Offset||%s||\n",offset);
                exit(0);
            }
        }
    }
    
    
    //BIT-SHIFTING HERE
    int result1;
    int offset2;
    
    if (intOp == 4 && (checkLabel(offset)) >= 0) {
        offset2 = (intOffset-(pc+1));
        offset2 = ((0xFFFF)&offset2);
        result1 = (((intOp<<22)) + ((intDest<<19)) + ((intSource<<16)) + offset2);
        printf("%d\n",result1);
        fprintf(finalOut, "%d\n",result1);
        
    }else{
        result1 = (((intOp<<22)) + ((intDest<<19)) + ((intSource<<16)) + ((0xFFFF)&intOffset));
        printf("%d\n",result1);
        fprintf(finalOut, "%d\n",result1);
    }
    
    
    
    
    return 0;
}



int jTypeAssembly(char * input[5], int pc){
    
    char *opcode = input[0];
    int intOp = isOpcode(opcode);
    char *regA = input[1];
    if (regA == NULL) {
        printf("Invalid J-Type Instruction: NULL register\n");
        exit(0);
    }
    int intA = atoi(regA);
    
    char *regB = input[2];
    if (regB == NULL) {
        printf("Invalid J-Type Instruction: NULL register\n");
        exit(0);
    }
    int intB = atoi(regB);
    
    
    
    int result1 = (((intOp<<22)) + ((intA<<19)) + ((intB<<16)));
    
    fprintf(finalOut, "%d\n",result1);
    printf("%d\n",result1);
    
    
    
    
    return 0;
}


int oTypeAssembly(char * input[5]){
    
    char *opcode = input[0];
    char *machineCode;
    char intMachine;
    
    
    
    if ((strcmp(opcode, "halt")) == 0 || (strcmp(opcode, "halt\n")) == 0){
        machineCode = opList[6][1];
    } else if ((strcmp(opcode, "noop")) == 0){
        machineCode = opList[7][1];
    }else{
        printf("Invalid O-Type instruction at address: %d\n",pc);
        exit(0);
    }
    
    intMachine = atoi(machineCode);
    
    char result[256];
    sprintf(result,"0000000%hhd0000000000000000000000\n",intMachine);
    long intResult = strtol(result, NULL, 2);
    fprintf(finalOut, "%ld\n",intResult);
    printf("%ld\n",strtol(result, NULL, 2));
    
    
    return 0;
}


//Assembly Directives
//Should only be .fill
int otherType(char *input[5]){
    
    
    
    char *immediate = input[1];
    if (immediate == NULL) {
        printf("Invalid OTHER-Type Instruction\n");
        printf("Line Address: %d\n",pc);
        printf("Need Value after .fill\n");
        exit(0);
    }
    int imVal = -1;
    
    if (immediate == NULL) {
        return 0;
    }
    
    if((imVal = checkLabel(immediate)) != -1){
        imVal = checkLabel(immediate);
        
    }else if ((strcmp(immediate,"0")) == 0) {
        imVal = 0;
        
        
    }else if((atoi(immediate))){
        imVal = atoi(immediate);
    }else{
        printf("Invalid assembly Instruction at line: %d\n", pc);
        printf("Cannot assemble instruction: %s\n", immediate);
        exit(0);
    }
    
    fprintf(finalOut, "%d\n",imVal);
    
    printf("%d\n",imVal);
    
    
    return 0;
}



