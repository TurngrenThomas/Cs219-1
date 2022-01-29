#include <stdio.h>
#include <stdlib.h>  // for atoi
#include <cstring>   // for strlen
#include <algorithm> // for remove

struct _ADD_SETTINGS {
    int spaces = 0;
    int spaces_i = 0;
    char num_1[100];
    char num_2[100];

    void reset() {
        spaces = 0;
        spaces_i = 0;
        memset(&(num_1), 0, 100);
        memset(&(num_2), 0, 100);
    }

} Add_Settings;

enum CONTROL_CODES{
    READ=0,
    ADD,
    SUB,
    MULT,
    DIV
};

void removeSpaces(char* s) {
    *std::remove(s, s + strlen(s), ' ') = 0;
    *std::remove(s, s + strlen(s), '\n') = 0;
}

int is_instruction(char c, int count) {   
    if (c == 'A' && count == 0) {
        return 1;
    }
    if (c == 'D' && count == 1) {
        return 1;
    }
    if (c == 'D' && count == 2) {
        return 1;
    }

    return 0;
}

int main() {
    FILE *f;
    char file_chars[100];
    int i=0, count = 0, control_code = 0;

    f=fopen("ADDME.txt","r");
    if (f==NULL){
        printf("file doesnt exist?!\n");
        return 1;
    }

    while (fscanf(f, "%c", &file_chars[i]) != EOF) {
        //printf("%c",file_chars[i]);

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
                Add_Settings.num_1[Add_Settings.spaces_i++] = file_chars[i];
            }
            if (Add_Settings.spaces == 2) {
                Add_Settings.num_2[Add_Settings.spaces_i++] = file_chars[i];
            }
            if (Add_Settings.spaces == 3) {   
                int num1=0;
                int num2=0;

                control_code = READ;

                removeSpaces(Add_Settings.num_1);
                removeSpaces(Add_Settings.num_2);

                strncpy(Add_Settings.num_1, Add_Settings.num_1+2, strlen(Add_Settings.num_1));
                strncpy(Add_Settings.num_2, Add_Settings.num_2+2, strlen(Add_Settings.num_2));

                sscanf(Add_Settings.num_1, "%d", &num1);
                sscanf(Add_Settings.num_2, "%d", &num2);

                printf("(Number 1: %d:) + ", num1);
                printf("(Number 2: %d) = ", num2);
                printf("%d | Hex: %x\n", num1 + num2, num1 + num2);

                Add_Settings.reset();
            }

            if (file_chars[i] == ' ' || file_chars[i] == '\n') {
                Add_Settings.spaces++;
                Add_Settings.spaces_i = 0;
            }
        }
        i++;
    }



   // Add_Settings.num_1[strlen(Add_Settings.num_1)+1] = '\0';

    fclose(f);

    return 0;
}
