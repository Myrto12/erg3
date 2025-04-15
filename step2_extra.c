#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define words 20000 //to keimeno poy epejergazomaste exei 16057 lekseis
#define characters 50 // h megalyterh agglikh leksh exei 45 grammata





int get_choice(void);
void text_input(char text[words][characters+1]); 
void vocabulary_input(char vocabulary[words][characters+1]);
void text_processing(char text[words][characters+1], char vocabulary[words][characters+1]);
void text_statistics(char text[words][characters+1]);
void add_to_vocabulary(char vocabulary[words][characters+1], char string[characters+1]);
void array_in_lower_case(char array[words][characters+1]);





int main(){
    static char text[words][characters+1];  
    static char vocabulary[words][characters+1];
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
            if(vocabulary[0][0]=='\0'){
                printf("There is no vocabulary, can't process the text. Please load vocabulary\n");
                break;
            }
            else{
                text_processing(text,vocabulary);
            }
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
    char line[characters+1];
    char filename[characters+1];
    printf("Enter filename(filename.txt)\n");
    scanf(" %s",&filename);
    FILE *fptr;
    fptr = fopen(filename,"r");
    if(fptr==NULL){
        printf("The file was not found or cannot be opened\n");
        fclose(fptr);
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
    array_in_lower_case(text);
}

void vocabulary_input(char vocabulary[words][characters+1]){
    char dict_file[characters+1];
    printf("Enter dictionary file(filename.txt)\n");
    scanf(" %s",&dict_file);
    FILE *fptr;
    fptr = fopen(dict_file, "r");
    if (fptr ==NULL){
        printf("The file %s was not found or cannot be opened\n",dict_file);
        return;
    }
    else{
        printf("A dictionary was successfully loaded.\n");
    }
    int count=0;
    while(fgets(vocabulary[count],(characters+1),fptr)){count++;}
    fclose(fptr);
    array_in_lower_case(vocabulary);
}

void text_processing(char text[words][characters+1], char vocabulary[words][characters+1]){
    int i=0;
    int j=0;
    int choice = 0;
    int go_to_main_menu = 0;
    int compare = 0;
    char string[characters+1];
    while(go_to_main_menu!=1){
        while(text[i][0]!='\0'){
            strcpy(string,text[i]);
            if (go_to_main_menu==1){break;}
            while(vocabulary[j][0]!='\0'){
                compare = strcmp(string,vocabulary[j]);
                j++;
                if(compare==0){break;}
            }
            if(compare!=0){
                printf("The word %s was not found in the dictionary\nChoose option\n1 : add the word\n2 : continue text processing without adding the word\n3 : back to main menu\n", string);
                scanf(" %d",&choice);
                switch (choice){
                    case 1:
                    add_to_vocabulary(vocabulary,string);
                    printf("word added\n");
                    break;
                    case 2:
                    break;
                    case 3:
                    go_to_main_menu =1;
                    break;
                }
                i++;
                break; 
            }
          
            
          
        }

    }
    
}

void text_statistics(char text[words][characters+1]){
    int words_counter = -1;
    int character_counter = 0;
    int number_of_spaces = 0;
    int characters_with_spaces = 0;
    char stats_file[characters+1];
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
    printf("The statistics will be saved at the file..(enter filename.txt)\n");
    scanf(" %s",&stats_file);
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

void add_to_vocabulary(char vocabulary[words][characters+1], char string[characters+1]){
    int i=0;
    while(vocabulary[i][0]!='\0'){i++;}
    strcpy(vocabulary[i],string);
    printf("%s\n",vocabulary[i]);

    FILE *voc_ptr;
    voc_ptr = fopen("dictionary.txt","a");
    fprintf(voc_ptr,"\n%s\n",string);
    fclose(voc_ptr);
}

void array_in_lower_case(char array[words][characters+1]){
    int i,j;
    for(i=0; i<words; i++){
        for(j=0; j<characters+1; j++){
            array[i][j] = tolower(array[i][j]);
        }
    }
}

