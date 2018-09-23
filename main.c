#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "const.h"

int countCommand = 0; //счет строк
int regMemory[REG];


//Перевод из двоичной в десятичную
int toDecimal(const char *inputNum) {
    int resultNum = 0;
    for (int i = 1; i < (int) strlen(inputNum); i++) {
        if (inputNum[i] == '1') {
            resultNum = (int) (resultNum + pow(2, strlen(inputNum) - 1 - i));
        }
    }
    if (inputNum[0] == '1') { //если отрицательное
        resultNum = resultNum * (-1);
    }
    return resultNum;
}


void parser(FILE *manualInput, struct singleCommand *command, int *fixMemory) {
    char inputCommand[64]; //Массив для считанной команды
    char address[ADDRESS_SIZE * 2]; //умножение, т.к. есть разделители ";"
    int line = 0;

    //Считываем первую строчку с данными для фиксированной памяти машины
    fgets(address, sizeof(address), manualInput);
    fixMemory[0] = atoi(strtok(address, ";"));
    for (int i = 1; i < ADDRESS_SIZE; i++) {
        fixMemory[i] = atoi(strtok(NULL, ";"));
    }

    //Начинаем считывать команды, которые начинаются со 2й строчки
    line++;
    while (!feof(manualInput)) {
        fgets(inputCommand, sizeof(inputCommand), manualInput);
        char *currentCommand = strtok(inputCommand, "("); //Взять из строки саму команду

        if (!strcmp(currentCommand, "endFile")) { //Если конец файла, то сохраняем количество строк
            countCommand = line;
        } else {

            if (!strcmp(currentCommand, "ADD")) {
                char *regA = strtok(NULL, ","); //записали первый регистр
                char *regB = strtok(NULL, ","); //записали второй регистр
                char *regC = strtok(NULL, ")"); //записали третий регистр

                command[line].command = ADD;
                command[line].regA = toDecimal(regA);
                command[line].regB = toDecimal(regB);
                command[line].regC = toDecimal(regC);

//                printf("\n------------\n");
//                printf("Line %d\n", line);
//                printf("Current Command: %s\n", currentCommand);
//                printf("RegA: %s\n", regA);
//                printf("RegB: %s\n", regB);
//                printf("RegC: %s\n", regC);
//                printf("Command Line Command: %d\n", command[line].command);
//                printf("Command Line RegA: %d\n", command[line].regA);
//                printf("Command Line RegB: %d\n", command[line].regB);
//                printf("Command Line RegC: %d\n", command[line].regC);

                line++;

            } else if (!strcmp(currentCommand, "ADDI")) {
                char *regA = strtok(NULL, ","); //записали первый регистр
                char *regB = strtok(NULL, ","); //записали второй регистр
                char *regC = strtok(NULL, ")"); //записали третий регистр
                command[line].command = ADDI;
                command[line].regA = toDecimal(regA);
                command[line].regB = toDecimal(regB);
                command[line].regC = toDecimal(regC);
                line++;

            } else if (!strcmp(currentCommand, "ADDU")) {
                char *regA = strtok(NULL, ","); //записали первый регистр
                char *regB = strtok(NULL, ","); //записали второй регистр
                char *regC = strtok(NULL, ")"); //записали третий регистр

                command[line].command = ADDU;
                command[line].regA = toDecimal(regA);
                command[line].regB = toDecimal(regB);
                command[line].regC = toDecimal(regC);
                line++;
            } else if (!strcmp(currentCommand, "SUB")) {
                char *regA = strtok(NULL, ","); //записали первый регистр
                char *regB = strtok(NULL, ","); //записали второй регистр
                char *regC = strtok(NULL, ")"); //записали третий регистр

                command[line].command = SUB;
                command[line].regA = toDecimal(regA);
                command[line].regB = toDecimal(regB);
                command[line].regC = toDecimal(regC);
                line++;
            } else if (!strcmp(currentCommand, "SUBU")) {
                char *regA = strtok(NULL, ","); //записали первый регистр
                char *regB = strtok(NULL, ","); //записали второй регистр
                char *regC = strtok(NULL, ")"); //записали третий регистр

                command[line].command = SUBU;
                command[line].regA = toDecimal(regA);
                command[line].regB = toDecimal(regB);
                command[line].regC = toDecimal(regC);
                line++;
            } else if (!strcmp(currentCommand, "LW")) {
                char *regA = strtok(NULL, ","); //записали первый регистр
                char *regC = strtok(NULL, ")"); //записали третий регистр

                command[line].command = LW;
                command[line].regA = toDecimal(regA);
                command[line].regC = toDecimal(regC);
                line++;
            } else if (!strcmp(currentCommand, "SW")) {
                char *regA = strtok(NULL, ","); //записали первый регистр
                char *regC = strtok(NULL, ")"); //записали третий регистр

                command[line].command = SW;
                command[line].regA = toDecimal(regA);
                command[line].regC = toDecimal(regC);
                line++;
            } else if (!strcmp(currentCommand, "BEQ")) {
                char *regA = strtok(NULL, ","); //записали первый регистр
                char *regB = strtok(NULL, ","); //записали второй регистр
                char *regC = strtok(NULL, ")"); //записали третий регистр

                command[line].command = BEQ;
                command[line].regA = toDecimal(regA);
                command[line].regB = toDecimal(regB);
                command[line].regC = toDecimal(regC);
                line++;
            } else if (!strcmp(currentCommand, "J")) {
                char *regC = strtok(NULL, ")"); //записали третий регистр

                command[line].command = J;
                command[line].regC = toDecimal(regC);
                line++;
            } else if (!strcmp(currentCommand, "JR")) {
                char *regB = strtok(NULL, ")"); //записали третий регистр

                command[line].command = JR;
                command[line].regB = toDecimal(regB);
                line++;
            } else if (!strcmp(currentCommand, "SLT")) {
                char *regA = strtok(NULL, ","); //записали первый регистр
                char *regB = strtok(NULL, ","); //записали второй регистр
                char *regC = strtok(NULL, ")"); //записали третий регистр

                command[line].command = SLT;
                command[line].regA = toDecimal(regA);
                command[line].regB = toDecimal(regB);
                command[line].regC = toDecimal(regC);
                line++;
            }

        }

    }
}

//Массив регистров
void initReg() {
    for (int i = 0; i < REG; i++) { //заполняем масив нулями
        regMemory[i] = 0;
        //printf("%d", regMemory[i]);
    }
}

/**Команда – действие*/
int risk(int counter, int currentCommand, int registerA, int registerB, int registerC,
         int *fixMemory, int *regMemory) {

    switch (currentCommand) {

        /**ADD, складываем значения ячеек B и C и кладем в A*/
        case ADD : {
            regMemory[registerA] = regMemory[registerB] + regMemory[registerC];
            counter++;
            break;
        }
            /**ADDI, складываем B и число C(отриц) и кладем в A*/
        case ADDI : {
            regMemory[registerA] = regMemory[registerB] + registerC;
            counter++;
            break;
        }
            /**ADDU, складываем B и число C(Без знака, убирает "-") и кладем в A*/
        case ADDU : {
            if (registerC < 0) {
                regMemory[registerA] = regMemory[registerB] - registerC;
            } else regMemory[registerA] = regMemory[registerB] + registerC;
            counter++;
            break;
        }
            /**SUB, вычитаем из значения ячейки B зн. ячейки C и кладем в A*/
        case SUB : {
            regMemory[registerA] = regMemory[registerB] - regMemory[registerC];
            counter++;
            break;
        }
            /**SUBU, вычитаем из значения ячейки B число C (Без знака, убирает "-") и кладем в A*/
        case SUBU : {
            if (registerC < 0) {
                regMemory[registerA] = regMemory[registerB] + registerC;
            } else regMemory[registerA] = regMemory[registerB] - registerC;
            counter++;
            break;
        }
            /**LW, в ячейку A выгружаем данные из фикс памяти из ячейки с индексом С*/
        case LW : {
            regMemory[registerA] = fixMemory[registerC];
            counter++;
            break;
        }
            /**SW, в ячейку фикс памяти с индексом "значение регистра с индексом С" загружаем данные из ячейки регистра A*/
        case SW : {
            fixMemory[regMemory[registerC]] = regMemory[registerA];
            counter++;
            break;
        }
            /**BEQ, если данные A и B равны, то перемещаемся на строку counter в C + 1, иначе +1*/
        case BEQ : {
            if (regMemory[registerA] == regMemory[registerB]) {
                counter = counter + 1 + registerC;
            } else {
                counter++;
            }
            break;
        }
            /**J, перемещаемся на строку counter + C */
        case J : {
            counter = counter + registerC;
            break;
        }
            /**JR, перемещаемся на строку значения регистра B */
        case JR : {
            counter = regMemory[registerB]; //переместиться в позицию значения в регистре B
            break;
        }
            /**SLT, Если значение регистра C меньше знач в B, то в регистр А записываем значение регистра С
             * иначе ничего не делаем
             * идем дальше*/
        case SLT : {
            if (regMemory[registerC] < regMemory[registerB]) {
                regMemory[registerA] = regMemory[registerC];
                counter++;
            } else {
                counter++;
            }
            break;
        }
        default:
            break;
    }
    return counter;
}

void debuggerToFile(int step, FILE *resultFile, int currentCommand, int registerA, int registerB, int registerC,
                    int *regMemory, int *fixMemory) {
    char *nameCommand = NULL;
    if (currentCommand == ADD) {
        nameCommand = "ADD";
    } else if (currentCommand == ADDI) {
        nameCommand = "ADDI";
    } else if (currentCommand == ADDU) {
        nameCommand = "ADDU";
    } else if (currentCommand == SUB) {
        nameCommand = "SUB";
    } else if (currentCommand == SUBU) {
        nameCommand = "SUBU";
    } else if (currentCommand == LW) {
        nameCommand = "LW";
    } else if (currentCommand == SW) {
        nameCommand = "SW";
    } else if (currentCommand == BEQ) {
        nameCommand = "BEQ";
    } else if (currentCommand == J) {
        nameCommand = "J";
    } else if (currentCommand == JR) {
        nameCommand = "JR";
    } else if (currentCommand == SLT) {
        nameCommand = "SLT";
    }
    fprintf(resultFile, "Шаг № %d \n", step);
    fprintf(resultFile, "%s(А: %d B: %d C: %d)\n", nameCommand, registerA, registerB, registerC);
    for (int i = 0; i < REG; i++) {
        fprintf(resultFile, "Регистр[%d] = %d \n", i, regMemory[i]);
    }
    fprintf(resultFile, "Данные в фиксированной памяти \n");
    for (int i = 0; i < ADDRESS_SIZE; i++) {
        fprintf(resultFile, "Адрес[%d] = %d \n", i, fixMemory[i]);
    }
}


void resultToFile(FILE *resultF, int *fixMemory) {
    fwrite("Регистры: \n", strlen("Регистры: \n"), 1, resultF);
    for (int i = 0; i < REG; i++) {
        fprintf(resultF, "Регистр[%d] = %d \n", i, regMemory[i]);
    }
    fprintf(resultF, "Фиксированная память \n");
    for (int i = 0; i < ADDRESS_SIZE; i++) {
        fprintf(resultF, "Адрес памяти[%d] = %d \n", i, fixMemory[i]);
    }
    fclose(resultF);
}

int debugStep() {
    int step;
    printf("======Идем дальше?======\n"
           "1 - Да, Другое – завершить работу программы\n"
           "Введите число:");
    scanf("%d", &step);
    return step;
}

void debugStepToConsol(int *fixMemory) {
    //вывод в консоль
    for (int i = 0; i < REG; i++) {
        printf("Регистр[%d] = %d \n", i, regMemory[i]);
    }
    for (int i = 0; i < ADDRESS_SIZE; i++) {
        printf("Адрес памяти[%d] = %d \n", i, fixMemory[i]);
    }
}

int main(int argv, char **argc) {
    argv = 4;
    manualFile = argc[1]; //файл с командами и инициализацией

    printf("%s \n", manualFile);

    /**Инизиализация регистров*/
    initReg();

    /**Инизиализация памяти*/
    //Количество байт = размер элемента * количество элементов
    int *fixMemory = malloc(sizeof(int) * MEMORY_SIZE);//выделяем место под фикс память
    struct singleCommand *command = malloc(sizeof(struct singleCommand) * MAX_COMMAND); //выделяем место под команды
    FILE *manualInput = fopen(manualFile, "rt"); //Открытие текстового файла manualFile
    // (Prog1 или Prog2, указывается в аргументах) с инструкцией на чтение

    /**Запускаем парсер входного файла*/
    parser(manualInput, command,
           fixMemory); //парсит инструкцию и записывает команды в command, данные машины в fixMemory

    /**Проходимся по строчкам и выполняем команды*/
    int counter = 0;
    char *resultDebugName = argc[3];
    FILE *resultDebug;
    resultDebug = fopen(resultDebugName, "wt");

    int stepCounter = 0;


    /**1 - выполнение программы, запись результата в result
     * 2 - просмотр работы программы по шагам
     * 3 - выполнение программы, запись результата в result, запись пошаговой работы в resultDbug*/
    if (!strcmp(argc[4], "1")) { //Выполнение работы машины, запись результата в result и resultDebug
        while (counter < countCommand) {
            counter = risk(counter, command[counter].command,
                           command[counter].regA, command[counter].regB, command[counter].regC,
                           fixMemory, regMemory);
        }
    } else {
        //по шагам
        if (!strcmp(argc[4], "2")) {
            while (counter < countCommand) {
                int a = debugStep();
                if (a == 1) {
                    counter = risk(counter, command[counter].command,
                                   command[counter].regA, command[counter].regB, command[counter].regC,
                                   fixMemory, regMemory);
                    debugStepToConsol(fixMemory);
                } else
                    (counter = countCommand);
            }
        } else
            if (!strcmp(argc[4], "3")) {
            while (counter < countCommand) {
                counter = risk(counter, command[counter].command,
                               command[counter].regA, command[counter].regB, command[counter].regC,
                               fixMemory, regMemory);
                debuggerToFile(stepCounter, resultDebug, command[counter].command, command[counter].regA,
                               command[counter].regB, command[counter].regC, regMemory, fixMemory);
                stepCounter++;
            }
        }
    }

    //вывод в консоль результата (просто для удобства, а так выводится в файл result)
    for (int i = 0; i < REG; i++) {
        printf("Регистр[%d] = %d \n", i, regMemory[i]);
    }
    for (int i = 0; i < ADDRESS_SIZE; i++) {
        printf("Адрес памяти[%d] = %d \n", i, fixMemory[i]);
    }

    /**Вывод результата работы машины в файл result.txt*/
    FILE *resultF = fopen(argc[2], "wt");
    resultToFile(resultF, fixMemory);


    free(fixMemory);
    free(command);
    fclose(manualInput);
    fclose(resultDebug);

    return 0;
}
