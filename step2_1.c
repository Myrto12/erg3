#include <stdio.h>
#include <string.h>
#define words 1000
#define characters 50



int get_choice(void);
void text_input(char text[words][characters+1]);
void vocabulary_input(char vocabulary[words][characters+1]);
void text_processing(void);
void text_statistics(char text[words][characters+1]);



int main(){
    char text[words][characters+1];
    char word[characters+1];
    char endword[characters+1] = "telos";
    char vocabulary[words][characters+1];
    int exit =0;
    while(exit!=1){
        int choice = get_choice();
        switch(choice){
            case 1:
            text_input(text);
            break;
            case 2:
            vocabulary_input(vocabulary);
            break;
            case 3:
            text_processing();
            break;
            case 4:
            text_statistics(text);
            break;
            case 5:
            exit = 1;
            break;
            default:
            printf("\nChoose one of the options above\n");   
        }

    }
    return 0;
}


int get_choice(void){
    int choice;
    printf("1: input text\n2: input vocabulary\n3: text processing\n4: text statistics\n5: exit\n");
    scanf(" %d", &choice);
    while(getchar() != '\n');
    return choice;
}

void text_input(char text[words][characters+1]){
    char word[characters+1];
    char endword[characters+1] = "telos";
    char vocabulary[words][characters+1];
    int i=0;
    printf("Input text(type telos to finish):\n");
    while(scanf(" %50s",word), strcmp(word,endword)!=0){
        strcpy(text[i++],word);
    }
    printf("\n");
}

void vocabulary_input(char vocabulary[words][characters+1]){
   printf("vocabulary_input\n");
}

void text_processing(void){
    printf("text_processing\n");
}

void text_statistics(char text[words][characters+1]){
    int words_counter = -1;
    int character_counter = 0;
    int number_of_spaces = 0;
    int characters_with_spaces = 0;
    do{
        words_counter++;
        character_counter+=strlen(text[words_counter]);
    }
    while(strlen(text[words_counter]) != 0);
    number_of_spaces = words_counter-1;
    characters_with_spaces = character_counter + number_of_spaces;
    printf("Words : %d\nCharacters : %d\nCharacters with spaces : %d\n",words_counter,character_counter,characters_with_spaces);

    int i,j,k;
    int histogram_counter = 0;
    printf("\nHistogram(Number of characters/Words\n");
    for (i=1; i<characters+1; i++){
        for (j=0; j<words_counter; j++){
            if(strlen(text[j]) == i){
                histogram_counter+=1;
            }
        
        }
        printf("%d : ",i);
        for(k=0; k<histogram_counter; k++){
            printf("#");
        }
        printf("\n");
        histogram_counter = 0;
    }
    printf("\n");

        
}




