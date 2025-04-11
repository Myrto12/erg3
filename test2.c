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
    return choice;
}

void text_input(void){
    printf("text_input\n");
}

void vocabulary_input(void){
    FILE *fptr;
    fptr = fopen("Top1000EnglishWords.txt", "r");
    if (fptr ==NULL){
        printf("The file 'Top1000EnglishWords.txt' was not found or cannot be opened.\n");
        fclose(fptr);
        return;
    }
    char vocabulary[1000][20];
    char array[100000];
    int count=0;
    while(fgets(vocabulary[count],2,fptr)){
        strcpy(vocabulary[count], fgets(vocabulary[count],21,fptr));
        count+1;

    }
    int i=0;
    for(i=0; i<1000; i++){
        printf("%s\n", vocabulary[i]);
    }
    fclose(fptr);
}

void text_processing(void){
    printf("text_processing\n");
}

void text_statistics(void){
    printf("text_statistics\n");
}

