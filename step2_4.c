#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define WORDS 100000
#define MAXCHARS 300  
#define textFile "keimeno.txt"
#define dictionaryName "dictionary.txt"

int selectOperation(void);
void start(void);
void importText(char text[WORDS][MAXCHARS+1]);
void importDictionary();
void editMode(char text[WORDS][MAXCHARS+1], char dictionary[WORDS][MAXCHARS+1]);
void computeStats(char text[WORDS][MAXCHARS+1]);
void removeSpaces(char word[MAXCHARS+1]);
void printArray(char array[WORDS][MAXCHARS+1]);
int unknownWordChoice(char word[MAXCHARS+1]);
void makeLowercase(char text[WORDS][MAXCHARS+1]);
int findLastWordPosition(char array[WORDS][MAXCHARS+1]);

int main(int argc, char**argv){
    int exit = 0;
    static char text[WORDS][MAXCHARS+1];  //static giati exo stack overflow gia poly megala arxeia
    static char dictionary[WORDS][MAXCHARS+1];
    start();
    do{
        switch (selectOperation()){
            default:
                printf("\nNot a valid operation!\n");
                break;
            case 0:
                printf("\n1. Eisagogh Keimenou\n2. Eisagogh leksilogiou\n3. Epeksergasia keimenou/apothikeush leksikou\n4. Ypologismos statistikon tou keimenou\n5. eksodos\n");
                break;
            case 1:
                importText(text);
                break;
            case 2:
                importDictionary(dictionary);
                break;
            case 3:
                editMode(text, dictionary);
                break;
            case 4:
                computeStats(text);
                break;
            case 5:
                exit = 1;
                break;
            case 6:
                if (argc > 1 && strcmp(argv[1], "-debug") == 0){
                    printArray(text);
                    printArray(dictionary);
                }
                else{printf("\nNot a valid operation!\n");}
                break;
        }
    } while (exit == 0);
    
    return 0;
}

void start(void){
    printf("       LAB 3 step 2_4\n\n");
    printf("Please select Existing Operations\n1. Eisagogh Keimenou\n2. Eisagogh leksilogiou\n3. Epeksergasia keimenou/apothikeush leksikou\n4. Ypologismos statistikon tou keimenou\n5. eksodos\n");
}
int selectOperation(void){
    int input;
    printf("\n\nPlease select an operation (type '0' for operation list): ");
    scanf("%d", &input);
    while (getchar() != '\n'); // katharizo to input buffer
    return input;
}

void importText(char text[WORDS][MAXCHARS+1]){
    FILE *file;
    char line[MAXCHARS+1];
    int i=0;

    file = fopen(textFile, "r"); 
    if (file == NULL) {
        printf("\nThe file '%s' was not found or cannot be opened!\n", textFile);
        return;
    }
    
    while (fgets(line, MAXCHARS+1, file)) {
        char *ptr = strtok(line, " \t\n\r.,;:!?\"'()[]{}");
        while (ptr != NULL) {
            strcpy(text[i], ptr);
            i++;
            ptr = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
        }
    }

    fclose(file);
    printf("\nThe file '%s' has been successfully imported!\n", textFile);

}

void importDictionary(char dictionary[WORDS][MAXCHARS+1]){
    FILE *file;
    char word[MAXCHARS+1];
    int i=0;

    file = fopen(dictionaryName, "r"); 
    if (file == NULL) {
        printf("\nThe file '%s' was not found or cannot be opened.\n", dictionaryName);
        return;
    }
    while (fgets(word, MAXCHARS+1, file)){word[strcspn(word, "\n")] = 0 /*to ascii 0*/; strcpy(dictionary[i], word);i++;}
    printf("\nThe file '%s' has been successfully set as the dictionary!\n", dictionaryName);
    fclose(file);
}

void editMode(char text[WORDS][MAXCHARS+1], char dictionary[WORDS][MAXCHARS+1]){
    int i=0,j=0,choice=0,exit=0, wordExists=0;
    printf("\n------Edit Mode------\n");
    printf("\n\nParakalo perimenete (mporei na parei ligh ora)\n\n");

    FILE *file;
    file = fopen(dictionaryName, "a"); //prepei na to kano append kai sto leksiko
    if (file == NULL) {
        printf("Den brethike leksiko. Parakalo kante to prota import.\n");
        return;
    }
    
    makeLowercase(text);
    makeLowercase(dictionary);
    findLastWordPosition(dictionary);

    while(text[i][0] != '\0' && exit == 0){
        j=0;
        removeSpaces(text[i]);
        wordExists = 0;
        while (j<WORDS){
            if (strcmp(text[i], dictionary[j])==0) {wordExists = 1;j++;break;}
            else {j++;continue;}
        }
        if (wordExists == 0){                
            choice = unknownWordChoice(text[i]);
            if (choice == 1){
                strcpy(dictionary[findLastWordPosition(dictionary)], text[i]);
                fprintf(file, "\n%s", text[i]);///////////////////////////////////////////////////////////////////////////

            } 
            else if (choice ==2){}
            else if (choice ==3){exit =1; break;}
        }
        i++;   
        
    }
    fclose(file);

}

void computeStats(char text[WORDS][MAXCHARS+1]){
    int letterSum = 0, wordSum=0, charAndSpaceSum=0,wordLen=0,i=0,epilogh=0;
    int histogramStats[MAXCHARS] = {0};
    char fileName[100];
    printf("\n1: emfanise statistika\n2: apothikeuse statistika");
    printf("\nPlease select an operation: ");
    scanf("%d", &epilogh);
    //lekseis-grammata
    do {
        wordLen= strlen(text[i]);
        if (wordLen ==0){i++; continue;}
        else {letterSum+=wordLen; wordSum++; i++; histogramStats[wordLen]++;}
    } 
    while (wordLen != 0);
    charAndSpaceSum = letterSum + (wordSum - 1);
    
    switch(epilogh){
        default: printf("\nNot a valid operation!\n");break;
        
        case 1:
            printf("\nLetters: %d\n Words: %d\n", letterSum, wordSum);
            printf("Istogramma lekseon/xarakthron:");
            for (int j=1; j<MAXCHARS; j++){
                printf("\n%d: ", j);
                for (int k=0;k<histogramStats[j]; k++){printf("#");}
            }
            break;
        
        case 2:
            printf("\nDose onoma arxeiou statistikon (xoris extension): "); scanf("%s", fileName);
            strcat(fileName, ".txt");
            FILE *file = fopen(fileName, "w");
            fprintf(file, "\nLetters: %d\n Words: %d\n\nIstogramma lekseon/xarakthron:", letterSum, wordSum);
            for (int j=1; j<MAXCHARS; j++){
                fprintf(file, "\n%d: ", j);
                for (int k=0;k<histogramStats[j]; k++){fprintf(file, "#");}
            }
            fclose(file);
            printf("'%s' has been made successfully!", fileName);
            break;      
    }
    
}

void removeSpaces(char word[MAXCHARS+1]){
    char wordCopy[MAXCHARS+1];
    int j=0;
    strcpy(wordCopy, word);
    for (int i=0; i<MAXCHARS; i++){
        if (wordCopy[i] != ' '){word[j++]=wordCopy[i];}
    }
    word[j]='\0';
}

void printArray(char array[WORDS][MAXCHARS+1]){
    printf("\n\n");
    for (int i=0; i<WORDS; i++){
        for (int j=0; j<MAXCHARS+1; j++){
            printf("%c", array[i][j]);
        }
        printf("\n");
        
    }
}

void makeLowercase(char text[WORDS][MAXCHARS+1]){
    for (int i=0; i<WORDS; i++){
        for (int j=0; text[i][j] != '\0'; j++){
            text[i][j] = tolower(text[i][j]);
        }
    }
}

int unknownWordChoice(char word[MAXCHARS+1]){
    int choice;
    printf("\nBrethike agnosth leksh: '%s'\n", word);
    
    while(1){
        printf("\nEpilogh (pata 0 gia lista epilogon): ");
        scanf("%d", &choice);
        switch (choice){
            default: printf("\nDen yparxei auth h epilogh.\n");while (getchar() != '\n'); break;
            case 0: printf("\n1: prosthikh ths lekshs '%s' sto leksiko\n2: Agnohse to\n3. Eksodos apo leitourgia epeksergasias\n"); break;
            case 1: printf("\nH leksh '%s' prostethike sto leksiko!\n", word); return 1;
            case 2: printf("\nParablepsh ths lekshs '%s'..\n", word);return 2;
            case 3: printf("\nGinetai eksodos apo th leitourgia epeksergasias.."); return 3;
        }
    }
}

int findLastWordPosition(char array[WORDS][MAXCHARS+1]){
    int i=0;
    while(array[i++][0] != '\0');
    return i; //epistrefei thn epomenh apo thn teleutea thesh pou briskete leksh
}