#include <stdio.h>
#include <stdlib.h>  // for atoi
#include <cstring>   // for strlen
#include <algorithm> // for remove

struct _ADD_SETTINGS {
    int spaces = 0;
    int spaces_i = 0;
    int spaces_i2 = 0; // quick fix
    int num1=0;
    int num2=0;
    char num_1[100];
    char num_2[100];

    void reset() {
        spaces = 0;
        spaces_i = 0;
        spaces_i2 = 0;
        num1 = 0;
        num2 = 0;
        memset(&(num_1), ' ', strlen(num_1));
        memset(&(num_2), ' ', strlen(num_2));
    }

} Add_Settings;

enum CONTROL_CODES{
    READ=0,
    ADD=1,
    SUB,
    MULT,
    DIV
};

void removeSpaces(char* s) {
    *std::remove(s, s + strlen(s), ' ') = 0;
    *std::remove(s, s + strlen(s), '\n') = 0;
}

int is_instruction(char c, int count) {   

    if (c == 'A' && count == 0) 
        return 1;
    if (c == 'D' && count == 1) 
        return 1;
    if (c == 'D' && count == 2) 
        return 1;

    return 0;
}

void INS_ADD() {
    
    printf("BNum1: %s   ", Add_Settings.num_1);
    printf("BNum2: %s\n", Add_Settings.num_2);
    removeSpaces(Add_Settings.num_1); // Sanitize
    removeSpaces(Add_Settings.num_2);
    strncpy(Add_Settings.num_1, Add_Settings.num_1+2, strlen(Add_Settings.num_1));
    strncpy(Add_Settings.num_2, Add_Settings.num_2+2, strlen(Add_Settings.num_2));
    sscanf(Add_Settings.num_1, "%x", &Add_Settings.num1);
    sscanf(Add_Settings.num_2, "%x", &Add_Settings.num2);

    printf("ANum1: %s   ", Add_Settings.num_1);
    printf("ANum2: %s\n", Add_Settings.num_2);

    printf("(Number 1: %d) + ", Add_Settings.num1);
    printf("(Number 2: %d) = ", Add_Settings.num2);
    printf("%d | Hex: %x\n", Add_Settings.num1 + Add_Settings.num2, Add_Settings.num1 + Add_Settings.num2);
    
    Add_Settings.reset();
}

int main() {
    FILE *f;
    char file_chars[100];
    int i=0, count = 0, control_code = READ;

    f=fopen("Programming-Project-1.txt","r");
    if (f==NULL){
        printf("file doesnt exist?!\n");
        return 1;
    }

    int fCode = fscanf(f, "%c", &file_chars[i]);
    while (fCode != EOF) {
        if (control_code == READ) {
            if (is_instruction(file_chars[i], count)) {
                count++;
                if (count == 3) {
                   control_code = ADD;
                   count=0;
                }
            } else {
                count = 0;
            }
        } else if (control_code == ADD) {
            if (Add_Settings.spaces == 1) {
                printf("B: Add_Settings[%d] = %c\n", Add_Settings.spaces_i, Add_Settings.num_1[Add_Settings.spaces_i]);
                Add_Settings.num_1[Add_Settings.spaces_i++] = file_chars[i];
                printf("A: Add_Settings[%d] = %c\n", Add_Settings.spaces_i, Add_Settings.num_1[Add_Settings.spaces_i-1]);
                printf("1 Char: %c\n", file_chars[i]);
                printf("FILE I: %c\n", file_chars[i]);
            }

            if (Add_Settings.spaces == 2) {
                if (file_chars[i] == '\n' || file_chars[i] == ' ') {
                    // Quick Fix
                    control_code = READ;
                    INS_ADD();
                    printf("===================================================================\n\n");
                } else {
                    Add_Settings.num_2[Add_Settings.spaces_i2++] = file_chars[i];
                }
            }

            if (file_chars[i] == ' ' || file_chars[i] == '\n' || fCode == EOF) {
                Add_Settings.spaces++;
            }
        }

        i++;
        fCode = fscanf(f, "%c", &file_chars[i]);
    }

    fclose(f);
    printf("END\n");
    return 0;
}
