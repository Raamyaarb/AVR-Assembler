#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Instruction
{
    char label[50];
    char opcode[50];
    char opnd1[50];
    char opnd2[50];
};

struct optabb
{
    char op[50];
};

char symbol[50];
char value[50];
char mnemonic[50];
int length;
struct optabb opt[80];

int parse()
{
    FILE *fpp = fopen("optab.txt", "r");
    int i = 0;

    while (fscanf(fpp, "%49s", opt[i].op) == 1)
    {
        // printf("%s\n", opt[i].op);
        i++;
    }

    fclose(fpp);
    return i;
}

int checkOpcode(char array[50], int w)
{
    int found = 0;
    while (w--)
    {
        if (strcmp(opt[w].op, array) == 0)
            return 1;
    }
    return 0;
}

int searchSymtab(struct Instruction *inst)
{
    FILE *fp4 = fopen("symtab.txt", "r");
    int found = 0;

    while (fscanf(fp4, "%s\t%s", symbol, value) == 2)
    {
        if (strcmp(inst->label, symbol) == 0)
        {
            found = 1;
            break;
        }
    }

    fclose(fp4);
    return found;
}

int searchOptab(struct Instruction *inst)
{
    FILE *fp5 = fopen("optab.txt", "r");
    int found = 0;

    while (fscanf(fp5, "%49s", mnemonic) == 1)
    {
        if (strcmp(mnemonic, inst->opcode) == 0)
        {
            found = 1;
            break;
        }
    }

    fclose(fp5);
    return found;
}

void pass1()
{
    int locctr = 0;
    char line[100];
    FILE *fp1 = fopen("input3.txt", "r");

    if (fp1 == NULL)
    {
        perror("Error opening input.txt");
        exit(EXIT_FAILURE);
    }

    FILE *fp2 = fopen("symtab.txt", "w");
    if (fp2 == NULL)
    {
        perror("Error opening symtab.txt");
        exit(EXIT_FAILURE);
    }

    FILE *fp3 = fopen("intermediate.txt", "w");
    if (fp3 == NULL)
    {
        perror("Error opening intermediate.txt");
        exit(EXIT_FAILURE);
    }

    int optlen = parse();
    struct Instruction inst;

    while (fgets(line, sizeof(line), fp1) != NULL)
    {
        char array[4][50]; // Array to hold the parsed values
        int len = sscanf(line, "%s %s %s %s", array[0], array[1], array[2], array[3]);
        // printf("%s\t%s\t%s\t%s\n", array[0], array[1], array[2], array[3]);
        printf("%d\n", len);
        strcpy(inst.label, " ");
        strcpy(inst.opcode, " ");
        strcpy(inst.opnd1, " ");
        strcpy(inst.opnd2, " ");
        if (len == 1)
        {
            strcpy(inst.opcode, array[0]);
        }
        else if (len == 2)
        {
            strcpy(inst.opcode, array[0]);
            strcpy(inst.opnd1, array[1]);
        }
        else if (len == 3)
        {
            char str[50];
            strcpy(str, array[0]);
            // printf("%s\t%s", str, array[0]);
            if (checkOpcode(str, optlen))
            {
                strcpy(inst.opcode, array[0]);
                strcpy(inst.opnd1, array[1]);
                strcpy(inst.opnd2, array[2]);
            }
            else
            {
                strcpy(inst.label, array[0]);
                strcpy(inst.opcode, array[1]);
                strcpy(inst.opnd1, array[2]);
                strcpy(inst.opnd2, " ");
            }
        }
        else if (len == 4)
        {
            strcpy(inst.label, array[0]);
            strcpy(inst.opcode, array[1]);
            strcpy(inst.opnd1, array[2]);
            strcpy(inst.opnd2, array[3]);
        }

        if (strcmp(inst.opcode, ".EXIT") == 0)
            break;
        if (strcmp(inst.opcode, ".ORG") == 0)
        {
            unsigned int start = strtol(inst.opnd1, NULL, 16);
            locctr = start;
            fprintf(fp3, "%x\t%s\t%s\t%s\t%s\n", locctr, inst.label, inst.opcode, inst.opnd1, inst.opnd2);
            continue;
        }

        if (!(strcmp(inst.label, " ") == 0) || !(strcmp(inst.opcode, " ") == 0) || !(strcmp(inst.opnd1, " ") == 0) || !(strcmp(inst.opnd2, " ") == 0))
        {
            fprintf(fp3, "%x\t%s\t%s\t%s\t%s\n", locctr, inst.label, inst.opcode, inst.opnd1, inst.opnd2);

            if (strcmp(inst.label, " ") != 0)
            {
                if (!searchSymtab(&inst))
                {
                    fprintf(fp2, "%x\t%s\n", locctr, inst.label);
                }
                else
                {
                    printf("Duplicate symbol:%s\n", inst.label);
                }
            }

            if (searchOptab(&inst))
            {
                if ((strcmp(inst.opcode, "LDS") == 0) || (strcmp(inst.opcode, "STS") == 0) || (strcmp(inst.opcode, "JMP") == 0))
                    locctr = locctr + 4;
                else
                    locctr += 2;
            }
            else if (strcmp(inst.opcode, "BYTE.") == 0)
            {
                unsigned int result = strtol(inst.opnd1, NULL, 10);
                // unsigned int r=strtol(result,NULL,16);
                locctr += (result / 2);
            }
            else if (strcmp(inst.opcode, ".DB") == 0)
            {
                locctr += 2;
            }
            else if (strcmp(inst.opcode, ".DW") == 0)
            {
                unsigned int result1 = strtol(inst.opnd1, NULL, 10);
                // unsigned int r=strtol(result1,NULL,16);
                printf("HEXX::%x\n", result1);
                locctr += (2 * result1);
            }
            else
            {
                printf("Error: Invalid opcode:%s\n", inst.opcode);
            }
        }
    }

    fprintf(fp3, "\t%s\t%s\t%s\t%s\n", inst.label, inst.opcode, inst.opnd1, inst.opnd2);
    length = locctr;
    FILE *fpp = fopen("length.txt", "w");
    fprintf(fpp, "%x\n", length);
    fclose(fpp);
    printf("Length of the code is %x bytes\n", length);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}

int main()
{
    pass1();
    return 0;
}
