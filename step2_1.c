//up1119397 ΘΕΟΔΩΡΑΚΟΠΟΥΛΟΣ ΧΡΗΣΤΟΣ
#include <stdio.h>
#include <string.h>
#define WORDS 10000
#define MAXCHARS 45   //h megalyterh agglikh leksh exei 45 grammata symfona me to leksiko ths oxfordhs

int selectOperation(void);
void start(void);
void importText(char text[MAXCHARS+1][WORDS]);
void importDictionary();
void editMode();
void computeStats(char text[MAXCHARS+1][WORDS]);
void removeSpaces(char word[MAXCHARS+1]);

int main(int argc, char**argv){
    int exit = 0;
    char text[MAXCHARS+1][WORDS];

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
    printf("       LAB 3 step 2_1\n\n");
    printf("Please select Existing Operations\n1. Eisagogh Keimenou\n2. Eisagogh leksilogiou\n3. Epeksergasia keimenou/apothikeush leksikou\n4. Ypologismos statistikon tou keimenou\n5. eksodos\n");
}
int selectOperation(void){
    int input;
    printf("\n\nPlease select an operation (type '0' for operation list): ");
    scanf("%d", &input);
    while (getchar() != '\n'); // katharizo to input buffer
    return input;
}

void importText(char text[MAXCHARS+1][WORDS]){
    char word[MAXCHARS+1];
    printf("\nEisodos lekseon (grapse 'telos' gia termatismo): \n");
    
    for (int i=0; i<WORDS; i++){
        scanf("%45s", word);
        if (strcmp(word, "telos")==0) {break;}
        else {
            strcpy(text[i], word);} 
    }
}

void importDictionary(){
    printf("\nimportDictionary\n");
}

void editMode(){
    printf("\neditMode\n");
}

void computeStats(char text[MAXCHARS+1][WORDS]){
    int letterSum = 0, wordSum=0, charAndSpaceSum=0,wordLen=0,i=0;
    int histogramStats[MAXCHARS] = {0};

    //lekseis-grammata
    do {
        wordLen= strlen(text[i]);
        if (wordLen ==0){i++; continue;}
        else {letterSum+=wordLen; wordSum++; i++; histogramStats[wordLen]++;}
    } 
    while (wordLen != 0);
    printf("\nLetters: %d\n Words: %d\n", letterSum, wordSum);

    charAndSpaceSum = letterSum + (wordSum - 1);
    printf("synolikoi xarakthres(me kena): %d\n\n", charAndSpaceSum);

    //istogramma
    printf("Istogramma lekseon/xarakthron:");
    for (int j=1; j<MAXCHARS; j++){
        printf("\n%d: ", j);
        for (int k=0;k<histogramStats[j]; k++){printf("#");}
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