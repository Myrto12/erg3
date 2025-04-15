#include <stdio.h>
#include <string.h>

int get_choice(void);
void text_input(void);
void vocabulary_input(void);
void text_processing(void);
void text_statistics(void);


int main(){
    int exit =0;
    while(exit!=1){
        int choice = get_choice();
        switch(choice){
            case 1:
            text_input();
            break;
            case 2:
            vocabulary_input();
            break;
            case 3:
            text_processing();
            break;
            case 4:
            text_statistics();
            break;
            case 5:
            exit = 1;
            break;
            default:
            printf("Choose one of the options above\n");   
        }

    }
    
    getchar();
    return 0;
}


int get_choice(void){
    int choice;
    printf("1: input text\n2: input vocabulary\n3: text processing\n4: text statistics\n5: exit\n");
    scanf(" %d", &choice);
    while(getchar() != '\n');
    return choice;
}

void text_input(void){
    printf("text_input\n");
}

void vocabulary_input(void){
    printf("vocabulary_input\n");
}

void text_processing(void){
    printf("text_processing\n");
}

void text_statistics(void){
    printf("text_statistics\n");
}

