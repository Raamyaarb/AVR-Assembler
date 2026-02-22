#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct Instruction
{
    char locctr[50];
    char label[50];
    char opcode[50];
    char opnd1[50];
    char opnd2[50];
} instruction[40];

struct optab
{
    char op[40];
    char format[50];
    char value[50];
};

char symbol[50];
char value[50];
char mnemonic[50];
struct optab opt[80];

unsigned int fetchLength()
{
    char length[5];
    FILE *f1 = fopen("length.txt", "r");
    fscanf(f1, "%s", length);
    fclose(f1);
    return strtol(length, NULL, 16);
}

void printBin16(unsigned int num)
{
    for (int i = 15; i >= 0; i--)
    {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

void printBin12(unsigned int num)
{
    for (int i = 11; i >= 0; i--)
    {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0)
        {
            printf(" "); // Add space for better readability
        }
    }
    printf("\n");
}

void printBin8(unsigned int num)
{
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

void printBin7(unsigned int num)
{
    for (int i = 6; i >= 0; i--)
    {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

void printBin(int *binaryOutput)
{
    for (int xyz = 0; xyz < 16; xyz++)
    {
        printf("%d", binaryOutput[xyz]); // Print each binary digit
    }
    printf("\n"); // Add a newline character at the end
}

int *hexToBinary(unsigned int num)
{
    int *binary = malloc(17 * sizeof(int)); // For 16 bits + null terminator
    int i = 15;                             // Start from the last index

    // Iterate through each hex digit
    while (num)
    {
        int n = num % 16;

        // Convert hex digit to 4-bit binary
        for (int j = 0; j < 4; j++)
        {
            binary[i] = (n >> j) & 1;
            i--;
        }

        num = num / 16; // Move to the next hex digit
    }

    // Fill the remaining elements with 0
    while (i >= 0)
    {
        binary[i] = 0;
        i--;
    }

    return binary;
}

char *binaryArrayToString(int *binaryArray, int size)
{
    char *binaryString = malloc((size + 1) * sizeof(char)); // +1 for null terminator

    if (binaryString == NULL)
    {
        // Handle memory allocation failure
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++)
    {
        binaryString[i] = binaryArray[i] + '0'; // Convert binary digit to character
    }

    binaryString[size] = '\0'; // Null-terminate the string

    return binaryString;
}
int parse()
{
    FILE *fpp = fopen("optab2.txt", "r"); // Open the file "optab.txt" for reading
    int i = 0;                            // Initialize a counter variable

    // Read data from the file using fscanf until it fails to read three values
    while (fscanf(fpp, "%s %s %s", opt[i].op, opt[i].format, opt[i].value) == 3)
    {
        i++; // Increment the counter after successfully reading three values
    }
    fclose(fpp); // Close the file
    // printf("%d parse\n",i);
    return i; // Return the total number of records read from the file
}

int checkOpcode(char array[50], int w)
{
    while (w--)
    {
        if (strcmp(opt[w].op, array) == 0)
            return 1;
    }
    return 0;
}

int findOpt(struct Instruction *inst, int w)
{
    while (w--)
    {
        if (strcmp(opt[w].op, inst->opcode) == 0)
            return strtol(opt[w].format, NULL, 10);
    }
}

unsigned int findValue(struct Instruction *inst, int w)
{
    while (w--)
    {
        if (strcmp(opt[w].op, inst->opcode) == 0)
        {
            unsigned int v = (unsigned int)strtol(opt[w].value, NULL, 16);
            printf("findvalue %x", v);
            return v;
        }
    }
}

char *findValue1(struct Instruction *inst, int w)
{
    while (w--)
    {
        if (strcmp(opt[w].op, inst->opcode) == 0)
        {

            return opt[w].value;
        }
    }
}

char *getRegisterCode(char *temp)
{
    char *s = NULL;

    if (strcmp(temp, "R0") == 0)
        s = strdup("00000");
    else if (strcmp(temp, "R1") == 0)
        s = strdup("00001");
    else if (strcmp(temp, "R2") == 0)
        s = strdup("00010");
    else if (strcmp(temp, "R3") == 0)
        s = strdup("00011");
    else if (strcmp(temp, "R4") == 0)
        s = strdup("00100");
    else if (strcmp(temp, "R5") == 0)
        s = strdup("00101");
    else if (strcmp(temp, "R6") == 0)
        s = strdup("00110");
    else if (strcmp(temp, "R7") == 0)
        s = strdup("00111");
    else if (strcmp(temp, "R8") == 0)
        s = strdup("01000");
    else if (strcmp(temp, "R9") == 0)
        s = strdup("01001");
    else if (strcmp(temp, "R10") == 0)
        s = strdup("01010");
    else if (strcmp(temp, "R11") == 0)
        s = strdup("01011");
    else if (strcmp(temp, "R12") == 0)
        s = strdup("01100");
    else if (strcmp(temp, "R13") == 0)
        s = strdup("01101");
    else if (strcmp(temp, "R14") == 0)
        s = strdup("01110");
    else if (strcmp(temp, "R15") == 0)
        s = strdup("01111");
    else if (strcmp(temp, "R16") == 0)
        s = strdup("10000");
    else if (strcmp(temp, "R17") == 0)
        s = strdup("10001");
    else if (strcmp(temp, "R18") == 0)
        s = strdup("10010");
    else if (strcmp(temp, "R19") == 0)
        s = strdup("10011");
    else if (strcmp(temp, "R20") == 0)
        s = strdup("10100");
    else if (strcmp(temp, "R21") == 0)
        s = strdup("10101");
    else if (strcmp(temp, "R22") == 0)
        s = strdup("10110");
    else if (strcmp(temp, "R23") == 0)
        s = strdup("10111");
    else if (strcmp(temp, "R24") == 0)
        s = strdup("11000");
    else if (strcmp(temp, "R25") == 0)
        s = strdup("11001");
    else if (strcmp(temp, "R26") == 0)
        s = strdup("11010");
    else if (strcmp(temp, "R27") == 0)
        s = strdup("11011");
    else if (strcmp(temp, "R28") == 0)
        s = strdup("11100");
    else if (strcmp(temp, "R29") == 0)
        s = strdup("11101");
    else if (strcmp(temp, "R30") == 0)
        s = strdup("11110");
    else if (strcmp(temp, "R31") == 0)
        s = strdup("11111");

    return s;
}

int parseIntermidiate(int optlen)
{
    struct Instruction inst;
    struct Instruction inst_buffer;
    int i = 0;
    char line[100];
    FILE *fp1 = fopen("intermediate.txt", "r");
    while (fgets(line, sizeof(line), fp1) != NULL)
    {
        // char array[5][50];
        int len = sscanf(line, "%s %s %s %s %s", inst_buffer.locctr, inst_buffer.label, inst_buffer.opcode, inst_buffer.opnd1, inst_buffer.opnd2);
        strcpy(inst.label, "\0");
        strcpy(inst.opcode, "\0");
        strcpy(inst.opnd1, "\0");
        strcpy(inst.opnd2, "\0");
        if (len == 1)
        {
            strcpy(instruction[i].opcode, inst_buffer.locctr);
        }
        else if (len == 2)
        {
            strcpy(inst.locctr, inst_buffer.locctr);
            strcpy(inst.opcode, inst_buffer.label);
        }
        else if (len == 3)
        {
            strcpy(inst.locctr, inst_buffer.locctr);
            strcpy(inst.opcode, inst_buffer.label);
            strcpy(inst.opnd1, inst_buffer.opcode);
        }
        else if (len == 4)
        {
            char str[50];
            strcpy(str, inst_buffer.label);
            // printf("%s\t%s", str, inst_buffer.locctr);
            if (checkOpcode(str, optlen))
            {
                strcpy(inst.locctr, inst_buffer.locctr);
                strcpy(inst.opcode, inst_buffer.label);
                strcpy(inst.opnd1, inst_buffer.opcode);
                strcpy(inst.opnd2, inst_buffer.opnd1);
            }
            else
            {
                strcpy(inst.locctr, inst_buffer.locctr);
                strcpy(inst.label, inst_buffer.label);
                strcpy(inst.opcode, inst_buffer.opcode);
                strcpy(inst.opnd1, inst_buffer.opnd1);
                strcpy(inst.opnd2, " ");
            }
        }
        else if (len == 5)
        {
            strcpy(inst.locctr, inst_buffer.locctr);
            strcpy(inst.label, inst_buffer.label);
            strcpy(inst.opcode, inst_buffer.opcode);
            strcpy(inst.opnd1, inst_buffer.opnd1);
            strcpy(inst.opnd2, inst_buffer.opnd2);
        }
        instruction[i] = inst;
        i++;
        if (strcmp(inst.opcode, "END") == 0)
            break;
    }
    return i - 1;
}

int searchSymtab(struct Instruction *inst)
{
    FILE *fp5 = fopen("symtab.txt", "r");
    if (fp5 == NULL)
    {
        printf("Error Opening symtab.txt\n");
        return 0;
    }

    while (fscanf(fp5, "%s\t%s", value, symbol) == 2)
    {
        // printf("Comparing: %s with %s\n", symbol, inst->opnd1);
        if (strcmp(symbol, inst->opnd1) == 0)
        {
            fclose(fp5);
            return 1; // Symbol found
        }
    }

    fclose(fp5);
    return 0; // Symbol not found
}

unsigned int getSymvalue(struct Instruction *inst)
{
    FILE *fp5 = fopen("symtab.txt", "r");
    if (fp5 == NULL)
    {
        printf("Error Opening symtab.txt\n");
        return 0;
    }

    while (fscanf(fp5, "%s\t%s", value, symbol) == 2)
    {
        // printf("Comparing: %s with %s\n", symbol, inst->opnd1);
        if (strcmp(symbol, inst->opnd1) == 0)
        {
            unsigned int result = strtol(value, NULL, 16);
            fclose(fp5);
            return result; // Return the symbol value
        }
    }

    fclose(fp5);
    return 0; // Symbol not found
}

void pass2()
{

    FILE *fp2 = fopen("optab2.txt", "r");
    FILE *fp3 = fopen("output.txt", "w");
    if (fp2 == NULL)
        printf("Error Opening optab2.txt\n");
    if (fp3 == NULL)
        printf("Error Opening output.txt\n");
    int optlen = parse();
    int instlen = parseIntermidiate(optlen);
    // printf("%d - optlen ",optlen);
    for (int i = 0; i < instlen; i++)
    {
        if (strcmp(instruction[i].opcode, ".ORG") == 0)
        {
            printf("::%s\n", instruction[i].opcode);
            fprintf(fp3, "%s\t%s\t%s\t%s\t%s\n", instruction[i].locctr, instruction[i].label, instruction[i].opcode, instruction[i].opnd1, instruction[i].opnd2);
            continue;
        }
        if (strcmp(instruction[i].opcode, "BYTE.") == 0)
        {
            char arr[6];
            strcpy(arr, instruction[i].opnd1);
            unsigned int result = strtol(arr, NULL, 16);
            printf("Converted:::%x\n", result);
            fprintf(fp3, "%s\t%s\t%s\t%s\t%s\t%04x\n", instruction[i].locctr, instruction[i].label, instruction[i].opcode, instruction[i].opnd1, instruction[i].opnd2, result);
            continue;
        }
        if (strcmp(instruction[i].opcode, ".DB") == 0)
        {
            printf("%s\n", instruction[i].opcode);
            fprintf(fp3, "%s\t%s\t%s\t%s\t%s\n", instruction[i].locctr, instruction[i].label, instruction[i].opcode, instruction[i].opnd1, instruction[i].opnd2);
            continue;
        }
        if (strcmp(instruction[i].opcode, ".DW") == 0)
        {
          printf("%s\n",instruction[i].opcode);
          fprintf(fp3, "%s\t%s\t%s\t%s\t%s\n", instruction[i].locctr, instruction[i].label, instruction[i].opcode, instruction[i].opnd1, instruction[i].opnd2);
          continue;
        }
        printf("%s\t%s\t%s\t%s\t%s\n", instruction[i].locctr, instruction[i].label, instruction[i].opcode, instruction[i].opnd1, instruction[i].opnd2);
        if ((!strcmp(instruction[i].label, " ") == 0) || (!strcmp(instruction[i].opcode, " ") == 0) ||
            (!strcmp(instruction[i].opnd1, " ") == 0) || (!strcmp(instruction[i].opnd2, " ") == 0))
        {

            int fmt = findOpt(&instruction[i], optlen);
            printf("%d\n", fmt);
            unsigned int value = findValue(&instruction[i], (optlen - 1));
            // printf("value %x\n",value);
            int *binr = hexToBinary(value);
            // printBin(binr);

            if (fmt == 1)
            {
                char *result = getRegisterCode(instruction[i].opnd1);
                char *result1 = getRegisterCode(instruction[i].opnd2);
                char msb = result1[0];
                printf("%c\n", msb);
                for (int i = 0; i < 4; i++)
                {
                    result1[i] = result1[i + 1];
                }
                printf("%c\n", msb);
                result1[4] = msb;
                printf("%s\n", result1);
                char *concatenated = malloc(strlen(result) + strlen(result1) + 1);
                strcpy(concatenated, result);
                strcat(concatenated, result1);
                printf("%s\n", concatenated);
                int len2 = strlen(concatenated);
                printf("len2 %d\n", len2);
                for (int i = len2 - 1; i > 0; i--)
                {
                    concatenated[i] = concatenated[i - 1];
                }
                concatenated[0] = msb; // Set the first element to the original MSB
                printf("Result after left-shifting MSB: %s\n", concatenated);
                char *buffer = malloc(17);
                sprintf(buffer, "111111%s", concatenated);
                strcpy(concatenated, buffer);
                unsigned int concatenatedValue = strtol(concatenated, NULL, 2);
                printf("concatenatedValue %x\n", concatenatedValue);
                printf("opcode %s\n", instruction[i].opcode);
                unsigned int opcodeee = findValue(&instruction[i], 16);
                printf(" opcodeee %x\n", opcodeee);
                binr = hexToBinary(opcodeee);
                printBin(binr);
                int size = 16;
                char *binaryString = binaryArrayToString(binr, size);
                unsigned int opcodeeee = strtol(binaryString, NULL, 2);
                unsigned int objectcode = opcodeeee & concatenatedValue;
                printf("binary string %s\n", binaryString);
                fprintf(fp3, "%s\t%s\t%s\t%s\t%s\t%04x\n", instruction[i].locctr, instruction[i].label, instruction[i].opcode, instruction[i].opnd1, instruction[i].opnd2, objectcode);
            }
            else if (fmt == 3)
            {
                char *result = getRegisterCode(instruction[i].opnd1);
                printf("format3:::%s\n", result);
                for (int i = 0; i < 4; i++)
                {
                    result[i] = result[i + 1];
                }
                result[4] = '\0';
                char arr[4] = "\0";
                strcpy(arr, instruction[i].opnd2);
                // unsigned int opndd=strtol(arr,NULL,16);
                const char *hexPrefix = "0X";
                unsigned int opndd;
                if (strncmp(arr, hexPrefix, strlen(hexPrefix)) == 0)
                {
                    // Skip the "0X" prefix and convert the rest to an integer
                    opndd = (unsigned int)strtol(arr + strlen(hexPrefix), NULL, 16);
                    printf("Value after skipping prefix: %x\n", opndd);
                }
                binr = hexToBinary(opndd);
                printBin(binr);
                printf("\n");
                unsigned int last8bits = 0;
                for (int i = 8; i < 16; i++)
                {
                    last8bits |= binr[i] << (7 - (i - 8));
                }
                printBin8(last8bits); // Print the extracted last 8 bits
                printf("End of format3\n");
                last8bits |= ((result[0] - '0') << 7) | ((result[1] - '0') << 6) | ((result[2] - '0') << 5) | ((result[3] - '0') << 4);
                // Store the final 12-bit value in the variable finalValue
                unsigned int finalValue = last8bits;
                // Print the final result with a function that supports 12 bits
                printBin12(finalValue);
                printf("\n");
                printf("opcode %s\n", instruction[i].opcode);
                unsigned int opcodeee = findValue(&instruction[i], 16);
                printf(" opcodeee %x\n", opcodeee);
                binr = hexToBinary(opcodeee);
                printBin(binr);
                int size = 16;
                char *binaryString = binaryArrayToString(binr, size);
                unsigned int opcodeeee = strtol(binaryString, NULL, 2);
                int *binr1 = hexToBinary(finalValue);
                char *bs = binaryArrayToString(binr1, size);
                char finalValue1[17]; // Assuming a 16-bit value plus the null terminator
                printf("HII::");
                printf("%s\n", bs);
                printf("\n");
                for (int i = 0; i < 4; i++)
                {
                    bs[i] = '1';
                }
                printf("Modified bs: %s\n", bs);
                unsigned int r = strtol(bs, NULL, 2);
                unsigned int objectcode = opcodeeee & r;
                printf("binary string %s\n", binaryString);
                fprintf(fp3, "%s\t%s\t%s\t%s\t%s\t%04x\n", instruction[i].locctr, instruction[i].label, instruction[i].opcode, instruction[i].opnd1, instruction[i].opnd2, objectcode);
            }

            else if (fmt == 0)
            {
                char *result;
                if (strcmp(instruction[i].opnd1, "X") == 0)
                {
                    result = getRegisterCode(instruction[i].opnd2);
                }
                else
                {
                    result = getRegisterCode(instruction[i].opnd1);
                }

                char *buffer = malloc(17);
                sprintf(buffer, "1111111%s", result);
                strcpy(result, buffer);
                sprintf(buffer, "%s1111", result);
                strcpy(result, buffer);
                printf("opcode %s\n", instruction[i].opcode);
                unsigned int opcodeee = findValue(&instruction[i], 16);
                printf(" opcodeee %x\n", opcodeee);
                binr = hexToBinary(opcodeee);
                printBin(binr);
                int size = 16;
                char *binaryString = binaryArrayToString(binr, size);
                unsigned int opcodeeee = strtol(binaryString, NULL, 2);
                unsigned int r = strtol(result, NULL, 2);
                unsigned int objectcode = opcodeeee & r;
                printf("r=%x\n", r);
                printf("binary string %s\n", binaryString);
                fprintf(fp3, "%s\t%s\t%s\t%s\t%s\t%04x\n", instruction[i].locctr, instruction[i].label, instruction[i].opcode, instruction[i].opnd1, instruction[i].opnd2, objectcode);
            }
            else if (fmt == 5)
            {
                char *result;
                if (strncmp(instruction[i].opnd1, "0X", 2) == 0)
                {
                    result = getRegisterCode(instruction[i].opnd2);
                    printf("STS: %s\n", result);
                    char arr[4] = "\0";
                    strcpy(arr, instruction[i].opnd1);
                    const char *hexPrefix = "0X";
                    unsigned int opndd;
                    if (strncmp(arr, hexPrefix, strlen(hexPrefix)) == 0)
                    {
                        // Skip the "0X" prefix and convert the rest to an integer
                        opndd = (unsigned int)strtol(arr + strlen(hexPrefix), NULL, 16);
                        printf("Value after skipping prefix: %x\n", opndd);
                    }
                    binr = hexToBinary(opndd);
                    printBin(binr);

                    printf("\n");
                }
                else
                {
                    printf("---------------------\n");
                    result = getRegisterCode(instruction[i].opnd1);
                    printf("result %s\n", result);
                    char *buffer = malloc(17);
                    sprintf(buffer, "1111111%s1111", result);
                    printf("buffer %s\n", buffer);
                    char arr[4] = "\0";
                    strcpy(arr, instruction[i].opnd2);
                    const char *hexPrefix = "0X";
                    unsigned int opndd;
                    if (strncmp(arr, hexPrefix, strlen(hexPrefix)) == 0)
                    {
                        // Skip the "0X" prefix and convert the rest to an integer
                        opndd = (unsigned int)strtol(arr + strlen(hexPrefix), NULL, 16);
                        printf("Value after skipping prefix: %x\n", opndd);
                    }
                    binr = hexToBinary(opndd);
                    int size = 16;
                    char *binaryString = binaryArrayToString(binr, size);
                    strcat(buffer, binaryString);
                    printf("bufferrr %s\n", buffer);
                    unsigned int opcodeeee = 0;
                    for (int i = 0; i < 32; i++)
                    {
                        opcodeeee = opcodeeee * 2 + (buffer[i] - '0');
                    }
                    printf(" opcodeeee %x\n", opcodeeee);
                    char *opcodeee = findValue1(&instruction[i], 50);
                    printf(" opcodeee %s\n", opcodeee);
                    unsigned int result1 = 0;
                    for (int i = 0; opcodeee[i] != '\0'; i++)
                    {
                        result1 = result1 * 16 + (opcodeee[i] >= 'A' ? opcodeee[i] - 'A' + 10 : opcodeee[i] - '0');
                    }
                    printf("try 1 %x\n", result1);
                    unsigned int opcode = opcodeeee & result1;
                    printf("asdfghjkl %x\n", opcode);
                    fprintf(fp3, "%s\t\t%s\t%s\t%s\t%x\n", instruction[i].locctr, instruction[i].opcode, instruction[i].opnd1, instruction[i].opnd2, opcode);
                }
                printf("format5:::%s\n", result);
            }
            else if (fmt == 4)
            {
                if (searchSymtab(&instruction[i]))
                {
                    printf("Operand1: %s\n", instruction[i].opnd1);
                    unsigned int target = getSymvalue(&instruction[i]);
                    printf("Converted::::%x\n", target);
                    unsigned int pc = strtol(instruction[i + 1].locctr, NULL, 16);
                    printf("PC::%x\n", pc);
                    unsigned int disp = target - pc;
                    printf("DISP:::%x\n", disp);
                    binr = hexToBinary(disp);
                    printf("After conversion-----");
                    printBin(binr);
                    printf("\n");
                    unsigned int last7bits = 0;
                    for (int i = 9; i < 16; i++)
                    { // Start from index 9 to extract the last 7 bits
                        last7bits |= (binr[i] & 1) << (6 - (i - 9));
                    }
                    printBin7(last7bits);
                    printf("End of format 44444444:\n");
                    unsigned int result = (0b1111110000000 | last7bits) << 3 | 0b111;
                    // Print the result
                    printf("Result: ");
                    printBin16(result);
                    unsigned int opcodeee = findValue(&instruction[i], 16);
                    printf(" opcodeee %x\n", opcodeee);
                    binr = hexToBinary(opcodeee);
                    printBin(binr);
                    int size = 16;
                    char *binaryString = binaryArrayToString(binr, size);
                    unsigned int opcodeeee = strtol(binaryString, NULL, 2);
                    unsigned int objectcode = opcodeeee & result;
                    printf("binary string %s\n", binaryString);
                    fprintf(fp3, "%s\t%s\t%s\t%s\t%s\t%04x\n", instruction[i].locctr, instruction[i].label, instruction[i].opcode, instruction[i].opnd1, instruction[i].opnd2, objectcode);
                }
            }
        }
    }
}

int main()
{
    pass2();
    return 0;
}
