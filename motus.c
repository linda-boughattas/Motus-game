#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

#define MAX_PLAYERS 3
#define MAX_ROUNDS 10
#define MAX_WORD_LENGTH 20

int Number_PLAYERS, MAX_TRIALS;
int level, length;
bool end=false;
char* selectedWord = NULL;
char **board;

int GetNumberOfPlayers();
void GetPlayersNames();
int ChooseLevel();
int EnterRounds();
char* GetRandomWord();
void ResetBoard();
//void PrintBoard();
void PrintColoredBoard();
void GetWord();
bool CalculateScore();
void Winner();
int EndGame();
int EndGame2();
struct player
{
    char name[20];
    int score;
};
typedef struct player PLAYER;


int main() 
{
    while(1){
        printf(" ███╗░░░███╗░█████╗░████████╗██╗░░░██╗░██████╗\n");
        printf(" ████╗░████║██╔══██╗╚══██╔══╝██║░░░██║██╔════╝\n");
        printf(" ██╔████╔██║██║░░██║░░░██║░░░██║░░░██║╚█████╗░\n");
        printf(" ██║╚██╔╝██║██║░░██║░░░██║░░░██║░░░██║░╚═══██╗\n");
        printf(" ██║░╚═╝░██║╚█████╔╝░░░██║░░░╚██████╔╝██████╔╝\n");
        printf(" ╚═╝░░░░░╚═╝░╚════╝░░░░╚═╝░░░░╚═════╝░╚═════╝░\n");

        putchar('\n');
        Number_PLAYERS=GetNumberOfPlayers();
        MAX_TRIALS=2*Number_PLAYERS;
        PLAYER* PlayerName;
        PlayerName=(PLAYER*)malloc(Number_PLAYERS*sizeof(PLAYER));
        if(!PlayerName)exit(-2);
        GetPlayersNames(Number_PLAYERS,PlayerName);
        level=ChooseLevel();
        int c=0,round;
        round=EnterRounds();
        while(c<round){
            selectedWord=GetRandomWord(level);
            length=strlen(selectedWord)-1;
            board = (char **)malloc(MAX_TRIALS * sizeof(char *));
            if (board == NULL) {
                printf("Memory allocation failed.\n");
                exit(-1);
            }
            for (int i = 0; i < MAX_TRIALS; i++) {
                board[i] = (char *)malloc(length * sizeof(char));
                if (board[i] == NULL) {
                    printf("Memory allocation failed.\n");
                    exit(1);
                }
            }
            ResetBoard(board,length);
            printf("\n\n------ 𝗟𝗲𝘁 𝗧𝗵𝗲 𝗚𝗮𝗺𝗲 𝗕𝗲𝗴𝗶𝗻𝘀------");
            printf("\n\nThe word is composed of %d letters",length);
            bool test=false;
            for(int i=0, j=0; i<MAX_TRIALS; j++ ,i++){
                printf("\n\n%s's turn: ", PlayerName[j].name);
                GetWord(board, length, i);
                printf("\n");
                test=CalculateScore(board, selectedWord, PlayerName, i, j);
                PrintColoredBoard(board, selectedWord, length);
                printf("Name\t|\tScore");
                for(int k=0; k<Number_PLAYERS; k++){
                    printf("\n%s\t|\t%d ", PlayerName[k].name, PlayerName[k].score);
                }
                if(test==true){
                    printf("\n\n-----❀ꗥ～ꗥ❀ 𝗪𝗶𝗻𝗻𝗲𝗿 ❀ꗥ～ꗥ❀-----\n");
                    printf("\tis %s with a score %d",PlayerName[j].name,PlayerName[j].score);
                    break;
                }
                if(j==Number_PLAYERS-1){
                    j=-1;
                }
            }
            if(test==false){
                printf("\n\nThe right answer is: %s",selectedWord);
                Winner(PlayerName, PlayerName[0].score, PlayerName[0].name);
            }
            int number;
            c++;
            if(c==round){
                number=EndGame2();
                if(number==2){
                    end=true;
                    break;
                }
            }
            else{
                number=EndGame();
                if(number==3){
                    end=true;
                    break;
                }
                if(number==2){
                    c=round;
                }
            }
        }
        if(end==true){
            break;
        }
    }
}

int GetNumberOfPlayers(){
    for (int i=2; i<=MAX_PLAYERS; i++) 
    {
        printf("\t%d players ",i);
    }

    printf("\nSelect number of players: ");
    while (1)
    {
        if (scanf("%d", &Number_PLAYERS) != 1)
        {
            while (getchar() != '\n')
            ;
            printf("\nPlease enter a valid number of players: ");
        }
        else if (Number_PLAYERS <= MAX_PLAYERS && Number_PLAYERS >= 2)
        break;
        
        else
        printf("\nPlease enter a number of players between 2 and %d: ", MAX_PLAYERS);
    }
    return Number_PLAYERS;
}

void GetPlayersNames(int Number_PLAYERS, PLAYER* p){
    printf("\nEnter players names\n");
    for (int i = 0; i < Number_PLAYERS; i++) {
        printf("   Player n°%d: ", i + 1);
        scanf(" %19[^\n]", p[i].name);
        p[i].score=0;
        
    }
}

int ChooseLevel(){
    printf("\n \t1. Easy \t2. Medium \t3. Hard\n");
    printf("\nChoose the difficulty of the game: ");
    while (1)
    {
        if (scanf("%d", &level ) != 1)
        {
            while (getchar() != '\n')
            ;
            printf("\nPlease enter the number of the chosen level: ");
        }
        else if (level  <= 3 && level >= 1 )
        break;
        
        else
        printf("\nPlease choose between the levels indicated: ");
    }
    printf("\n");
    return level;
}

int EnterRounds(){
    int round;
    printf("Enter number of rounds you desire to play: ");
    while (1)
    {
        if (scanf("%d", &round ) != 1)
        {
            while (getchar() != '\n')
            ;
            printf("\nPlease enter an integer that indicates the number of rounds: ");
        }
        else if (round  <= MAX_ROUNDS && round >= 1 )
        break;
        else
        printf("\nRounds can not surpass %d  ",MAX_ROUNDS);
    }
    printf("\n");
    return round;
}

char* GetRandomWord(int level) {
    const char* levelFiles[] = {
        "C:\\Users\\LENOVO\\Documents\\Motus\\1_easy.txt",
        "C:\\Users\\LENOVO\\Documents\\Motus\\2_medium.txt",
        "C:\\Users\\LENOVO\\Documents\\Motus\\3_hard.txt"
    };
    const int numWords[] = {1094, 1439, 655};

    FILE* file = fopen(levelFiles[level-1], "r");
    if (file == NULL) {
        printf("Error: Could not open the level file.\n");
        return NULL;
    }

    char word[MAX_WORD_LENGTH];
    //rewind(file);
    int randomWordIndex=rand()%numWords[level-1];
    int currentWordIndex=0;

    while (currentWordIndex <= randomWordIndex && fgets(word, MAX_WORD_LENGTH, file) != NULL) {
        if (currentWordIndex == randomWordIndex){
            selectedWord = strdup(word);
            break;
        }
        currentWordIndex++;
    }

    fclose(file);
    return selectedWord;
}

void ResetBoard(char **board, int length){
    for (int i = 0; i < MAX_TRIALS; i++) {
        for (int j = 0; j < length; j++) {
            board[i][j] = ' ';
        }
    }
}

/*void PrintBoard(char **board, int length){
    for(int i=0 ; i<MAX_TRIALS ; i++)
    {
        for(int j=0 ; j<length-1 ;j++)
        {
            printf(" %c |", board[i][j]);
        }
        printf(" %c ", board[i][length-1]);
        printf("\n");
        if(i==MAX_TRIALS-1)
        break;
        for(int j=0 ; j<length-1 ;j++)
        {
            printf("---|");
        }
        printf("---\n");
    }
    printf("\n");
}*/

void PrintColoredBoard(char** board, char* selectedWord, int length){
    for(int i=0 ; i<MAX_TRIALS ; i++)
    {
        for(int j=0 ; j<length-1 ;j++)
        {
            if(board[i][j]==selectedWord[j]){
                printf("\033[0;32m");
                printf(" %c ", board[i][j]);
                printf("\x1b[0m");
                printf("|");
            }
            else if (strchr(selectedWord, board[i][j])){
                printf("\x1b[33m");
                printf(" %c ", board[i][j]);
                printf("\x1b[0m");
                printf("|");
            }
            else{
                printf("\x1b[31m");
                printf(" %c ", board[i][j]);
                printf("\x1b[0m");
                printf("|");
            }
        }
        if(board[i][length-1]==selectedWord[length-1]){
                printf("\033[0;32m");
                printf(" %c ", board[i][length-1]);
                printf("\x1b[0m");
            }
            else if (strchr(selectedWord, board[i][length-1])){
                printf("\x1b[33m");
                printf(" %c ", board[i][length-1]);
                printf("\x1b[0m");
            }
            else{
                printf("\x1b[31m");
                printf(" %c ", board[i][length-1]);
                printf("\x1b[0m");
            }
        printf("\n");
        if(i==MAX_TRIALS-1)
        break;
        for(int j=0 ; j<length-1 ;j++)
        {
            printf("---|");
        }
        printf("---\n");
    }
    printf("\n");
}

void GetWord(char** board, int length, int i) {
    char word[length + 1];
    int j=0;

    while(1) {

        while (1) {
            if (scanf(" %c", &word[j]) != 1) {
                while (getchar() != '\n')
                printf("\nPlease enter an alphabet: ");
            } 
            else if(isalpha(word[j])) {
                word[j] = tolower(word[j]);
                board[i][j] = word[j];
                break;
            }
        }
        j++;
        if (j >= length) {
            while (getchar() != '\n');
            break;
        }
    }
}

bool CalculateScore(char**board, char*selectedWord, PLAYER* p, int i, int j){
    bool test=true;
    for(int k=0 ; k<length ;k++)
    {
        if(board[i][k]==selectedWord[k]){
            p[j].score+=10;
        }
        else if (strchr(selectedWord, board[i][k])){
            p[j].score+=5;
            test=false;
        }
        else{
            test=false;
        }
    }
    return(test);
}

void Winner(PLAYER* p, int max, char winner[20]){
    int n=0;
    for(int i=0; i<Number_PLAYERS; i++){
        if(max<=p[i].score){
            max=p[i].score;
            winner=p[i].name;
            n++;
        }
    }
    //printf("\n %d",n);
    if(n==1){
        printf("\n\n-----❀ꗥ～ꗥ❀ 𝗪𝗶𝗻𝗻𝗲𝗿 ❀ꗥ～ꗥ❀-----\n");
        printf("\tis %s with a score %d",winner,max);
    }
    else if (n>1){
        printf("\n\n-----❀ꗥ～ꗥ❀ 𝗪𝗶𝗻𝗻𝗲𝗿𝘀 ❀ꗥ～ꗥ❀-----\n");
        printf("            are ");
        for(int i=0; i<Number_PLAYERS-1; i++){
            if(max==p[i].score){
                printf("%s & ",p[i].name);
            }
        }
        if(max==p[Number_PLAYERS-1].score){
                printf(" %s",p[Number_PLAYERS-1].name);
            }
        printf("\n               with a score %d",max);
    }
}

int EndGame(){
    int number;
    printf("\n\nWould you like to: ");
    printf("\n \t1. Continue \t2. Replay \t3. End Game\n");
    while (1)
    {
        if (scanf("%d", &number ) != 1)
        {
            while (getchar() != '\n')
            ;
            printf("\nPlease enter a number between 1 and 3: ");
        }
        else if (number  <= 3 && number >= 1 )
        break;
        
        else
        printf("\nPlease choose between option 1 and 3: ");
    }
    printf("\n");
    return number;
}

int EndGame2(){
    int number;
    printf("\n\nWould you like to: ");
    printf("\n \t1. Replay \t2. End Game\n");
    while (1)
    {
        if (scanf("%d", &number ) != 1)
        {
            while (getchar() != '\n')
            ;
            printf("\nPlease enter a number between 1 and 3: ");
        }
        else if (number  <= 2 && number >= 1 )
        break;
        
        else
        printf("\nPlease choose between option 1 and 2: ");
    }
    printf("\n");
    return number;
}