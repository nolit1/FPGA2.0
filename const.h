//
// Created by Евгений on 13/09/2018.
//

#ifndef FPGA_CONST_H
#define FPGA_CONST_H

#endif //FPGA_CONST_H

//команды Risk FPGA
#define ADD 0
#define ADDI 1
#define ADDU 2
#define SUB 3
#define SUBU 4
#define LW 5
#define SW 6
#define BEQ 7
#define J 8
#define JR 9
#define SLT 10

#define REG 16
#define MEMORY_SIZE 1000 //максимальное число элементов
#define MAX_COMMAND 100 //макс число команд
#define ADDRESS_SIZE 8

char *manualFile; //файл с адресами машины и инструкцией

//Структура команды
struct singleCommand {
    int command;
    int regA;
    int regB;
    int regC;
};
