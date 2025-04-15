#include <stdio.h>
#include <string.h>
#define words 20000 //to keimeno poy epejergazomaste exei 16057 lekseis
#define characters 50 // h megalyterh agglikh leksh exei 45 grammata
#define filename "keimeno.txt"
#define dict_file "dictionary.txt"
#define stats_file "statistics.txt"



int get_choice(void);
void text_input(char text[words][characters+1]); 
void vocabulary_input(char vocabulary[words][characters+1]);
void text_processing(void);
void text_statistics(char text[words][characters+1]);




int main(){
    static char text[words][characters+1];  
    static char vocabulary[words][characters+1];
    char word[characters+1];
    char endword[characters+1] = "telos";
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
    getchar();
    return 0;
}


int get_choice(void){
    int choice;
    printf("1: input text\n2: input vocabulary\n3: text processing\n4: text statistics\n5: exit\n");
    scanf(" %d", &choice);
    return choice;
}

void text_input(char text[words][characters+1]){
    char line[characters+1];
    FILE *fptr;
    fptr = fopen(filename,"r");
    if(fptr==NULL){
        printf("The file was not found or cannot be opened\n");
        return;
    }
    else{
        printf("The file %s was successfully opened\n",filename);
    }
    int text_words = 0;
    while(fgets(line,characters+1,fptr)){
        char* tok_ptr = strtok(line, " \t\n\r.,;:!?\"'()[]{}");
        while(tok_ptr!=NULL){
            strcpy(text[text_words], tok_ptr);
            tok_ptr = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
            text_words++;
        }
    }
    fclose(fptr);
}

void vocabulary_input(char vocabulary[words][characters+1]){
    FILE *fptr;
    fptr = fopen("dictionary.txt", "r");
    if (fptr ==NULL){
        printf("The file %s was not found or cannot be opened\n",dict_file);
        fclose(fptr);
        return;
    }
    else{
        printf("A dictionary was successfully loaded.\n");
    }
    int count=0;
    while(fgets(vocabulary[count],(characters+1),fptr)){count++;}
    fclose(fptr);
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
    printf("The statistics will be saved at the file %s\n\n",stats_file);
    FILE *stats_ptr;
    stats_ptr = fopen(stats_file, "w");
    fprintf(stats_ptr, "Statistics\nWords : %d\nCharacters : %d\nCharacters with spaces : %d\nHistogram(Number of characters/Words)\n",words_counter,character_counter,characters_with_spaces);
    for (i=1; i<characters+1; i++){
        for (j=0; j<words_counter; j++){
            if(strlen(text[j]) == i){
                histogram_counter+=1;
            }
        
        }
        fprintf(stats_ptr,"%d : ",i);
        for(k=0; k<histogram_counter; k++){
            fprintf(stats_ptr,"#");
        }
        fprintf(stats_ptr,"\n");
        histogram_counter = 0;
    }
    fclose(stats_ptr);

        
}



