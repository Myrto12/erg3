#include <stdio.h>
#include <string.h>
#define words 1000
#define characters 50

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
    char text[words][characters];
    char word[50];
    char endword[50] = "end";
    int i;
    printf("Input text:\n");
    while(scanf(" %s",word), strcmp(word,endword)!=0){
        strcpy(text[i++],word);
    }
    int j;
    for(j=0; j<i; j++){
        printf("%s\n", text[j]);
    }
}

void vocabulary_input(void){
    FILE *fptr;
    fptr = fopen("dictionary.txt", "r");
    if (fptr ==NULL){
        printf("The file 'Top1000EnglishWords.txt' was not found or cannot be opened.\n");
        fclose(fptr);
        return;
    }
    char vocabulary[words][characters];
    int count=0;
    while(fgets(vocabulary[count],21,fptr)){count++;}

    
    int i=0;
    for(i=0; i<words; i++){
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

