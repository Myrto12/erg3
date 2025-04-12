//up1119397 ΘΕΟΔΩΡΑΚΟΠΟΥΛΟΣ ΧΡΗΣΤΟΣ
#include <stdio.h>
#include <string.h>
#define WORDS 5000
#define MAXCHARS 100   
#define textFile "keimeno.txt"

int selectOperation(void);
void start(void);
void importText(char text[WORDS][MAXCHARS+1]);
void importDictionary();
void editMode();
void computeStats(char text[WORDS][MAXCHARS+1]);
void removeSpaces(char word[MAXCHARS+1]);

int main(int argc, char**argv){
    int exit = 0;
    char text[WORDS][MAXCHARS+1];
    char dictionary[WORDS][MAXCHARS+1];
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
                editMode();
                break;
            case 4:
                computeStats(text);
                break;
            case 5:
                exit = 1;
                break;

        }
    } while (exit == 0);
    
    return 0;
}

void start(void){
    printf("       LAB 3 step 2_2\n\n");
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

    file = fopen("keimeno.txt", "r"); 
    if (file == NULL) {
        printf("\nThe file '%s' was not found or cannot be opened!\n", textFile);
        fclose(file);
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
    
    printf("The file '%s' has been successfully imported!", textFile);
}

void importDictionary(char dictionary[WORDS][MAXCHARS+1]){
    FILE *file;
    char word[MAXCHARS+1];
    int i=0;

    file = fopen("dictionary.txt", "r"); 
    if (file == NULL) {
        printf("\nThe file 'dictionary.txt' was not found or cannot be opened.\n");
        fclose(file);
        return;
    }
    while (fgets(word, MAXCHARS+1, file)){strcpy(dictionary[i], word);i++;}
    printf("\nThe file 'dictionary.txt' has been successfully set as the dictionary!\n");
    fclose(file);
}

void editMode(){
    printf("\neditMode\n");
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