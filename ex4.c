/******************
Name: Roei Wald
ID: 211589791
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>


#define PYRAMID_SIZE 5
#define HALF 0.5
#define BOARD_SIZE 20
#define BOARD_LIMIT 3
#define ASCII 128
#define WORD_MAX 16
#define CROSSWORD_MAX 30
#define SLOTS_MAX 100

typedef struct Slot {
    int row;
    int colmn;
    int length;
    char direction;
    int occupation;
}Slot;

typedef struct Word {
    char letters[WORD_MAX];
    int length;
    int occupation;
} Word;

void task1RobotPaths();
int moveRobot(int x, int y);
void task2HumanPyramid();
void printTotalWeights (float weightArr[PYRAMID_SIZE][PYRAMID_SIZE]);
float computeWeight (float weightArr[PYRAMID_SIZE][PYRAMID_SIZE], int y, int x);
void task3ParenthesisValidator();
int findOpener();
int findCloser (char opener);
char specificCloser (char opener);

void task4QueensBattle();
int queen(int y, int x, int d, int rowTrack[BOARD_SIZE], int columnTrack[BOARD_SIZE], int areaTrack[ASCII], \
          char givenBoard[BOARD_SIZE][BOARD_SIZE], char printBoard[BOARD_SIZE][BOARD_SIZE]);
int check (int y, int x, int rowTrack[BOARD_SIZE], int columnTrack[BOARD_SIZE], int areaTrack[ASCII], \
          char givenBoard[BOARD_SIZE][BOARD_SIZE], char printBoard[BOARD_SIZE][BOARD_SIZE] );
int checkDiagonal(int y, int x , char printBoard[BOARD_SIZE][BOARD_SIZE]);
void mark (int y, int x, int rowTrack[BOARD_SIZE], int columnTrack[BOARD_SIZE], int areaTrack[ASCII], \
          char givenBoard[BOARD_SIZE][BOARD_SIZE], char printBoard[BOARD_SIZE][BOARD_SIZE]);
void unmark (int y, int x, int rowTrack[BOARD_SIZE], int columnTrack[BOARD_SIZE], int areaTrack[ASCII], \
          char givenBoard[BOARD_SIZE][BOARD_SIZE], char printBoard[BOARD_SIZE][BOARD_SIZE]);
void task5CrosswordGenerator();
int singWordToSlot (int slotIndex, Slot slotArray[SLOTS_MAX], int wordIndex, Word wordArray[SLOTS_MAX],\
    char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX], int slotNum, int wordNum);
void reInsert (int slotIndex, Slot slotArray[SLOTS_MAX], int wordIndex, Word wordArray[SLOTS_MAX],\
    char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX], int slotsNum, int counter);
void removeInsert (int slotIndex, Slot slotArray[SLOTS_MAX], int wordIndex, Word wordArray[SLOTS_MAX],\
    char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX], int counter);
void removeH (Slot slot, Word word, char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX],\
    int row, int colmn, int counter);
void removeV (Slot slot, Word word, char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX],\
    int row, int colmn, int counter);
void insert (int slotIndex, Slot slotArray[SLOTS_MAX], int wordIndex, Word wordArray[SLOTS_MAX],\
    char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX], int counter);
void insertH (Slot slot, Word word,  char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX],\
    int row, int colmn, int counter);
void insertV (Slot slot, Word word, char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX],\
    int row, int colmn, int counter);
int checkPreviuseInsert (Slot slot, Word word, char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX]);
int checkH (Slot slot, Word word, int counter, int row, int colmn, char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX]);
int checkV (Slot slot, Word word, int counter, int row, int colmn, char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX]);
int validPlace (Slot slot, Word word, char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX]);




int main()
{
    int task = -1;
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task))
        {
            switch (task)
            {
                case 6:
                    printf("Goodbye!\n");
                break;
                /* Compute the total number of distinct paths the robot can take
                   to return to its home (0,0) from a given starting position. */
                case 1:
                    task1RobotPaths();
                break;
                case 2:
                    task2HumanPyramid();
                break;
                case 3:
                    task3ParenthesisValidator();
                break;
                case 4:
                    task4QueensBattle();
                break;
                case 5:
                    task5CrosswordGenerator();
                break;
                default:
                    printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
}
// FUNCS FOR CASE 2:
// * Func that do case 1
void task1RobotPaths()
{
    // Define the starting point.
    int y, x;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf("%d %d", &y, &x);
    // If the given numbers are negative the total number of paths is 0. And we save the recursive calculation
    if (x<0 || y<0)
        printf("The total number of paths the robot can take to reach home is: 0\n");
    else
        // Print the total number of paths calling the recursion function.
        printf("The total number of paths the robot can take to reach home is: %d\n", moveRobot(x, y));

}
// Recursive func that compute the total number of paths
int moveRobot(int y, int x) {
// Stop conditions:
    // return 1 if it gets to home (0,0) - success
    if (x==0 && y==0) return 1;
    // return 0 if it gets out of boundaries
    if (x<0 || y<0) return 0;
    // Sum the recursive funcs one go down second left.
    return moveRobot(y-1, x) + moveRobot(y, x-1);
}
// FUNCS FOR CASE 2:
// * The func that do case 2
void task2HumanPyramid() {
    // Set an array on array (5*5) that will contain the weights of every cheerleader in every level
    float weightArr[PYRAMID_SIZE][PYRAMID_SIZE] = {0};
    printf("Please enter the weights of the cheerleaders:\n");
    // loop that will scan number as the size of the line (1 to the first, 2 to the second...
        for (int i = 0; i < PYRAMID_SIZE; i++) {
            for (int j = 0; j <= i; j++) {
                scanf("%f", &weightArr[i][j]);
                if (weightArr[i][j]<0) {
                    printf("Negative weights are not supported.\n");
                    return;
                }
            }
        }
    printTotalWeights(weightArr);
}
// Func that will print the total weight supported by each cheerleader in the pyramid.
void printTotalWeights (float weightArr[PYRAMID_SIZE][PYRAMID_SIZE]) {
    printf("The total weight on each cheerleader is:\n");
    /* loop that run as the pyramid and print the cumulative weight of the cheerleader.
       1 print to the first line
       2 prints to the second and so on */
    for (int y = 0; y < PYRAMID_SIZE; y++) {
        for (int x = 0; x <= y; x++) {
            // print the result that we get from the recursive func
            printf("%.2f\t", computeWeight(weightArr, y, x));
        }
        printf("\n");
    }
}
// Recursive func to compute the cumulative weight and return the result.
float computeWeight(float weightArr[PYRAMID_SIZE][PYRAMID_SIZE], int y, int x) {
    // If we get out of the pyramid boundaries we want to add 0
    if (y<0 || x<0 || y<x)
        return 0;
    /*
    Sum the weight of the cheerleader and the half of the total weight of the two cheerleaders above her.
    the two above in the array is the one above and the one above and to the left
    */
    float above = HALF * (computeWeight(weightArr, y-1, x) + computeWeight(weightArr, y-1, x-1));
    return above + weightArr[y][x];
}
// Main func for case 3 - get the input and return if balanced or not.
void task3ParenthesisValidator()
{
    // Clean the buffer
    scanf("%*[^ \n]");
    scanf("%*c");
    printf("Please enter a term for validation:\n");
    // If the helper func that check the validaition is return correct - success
    if (findOpener())
        printf("The parentheses are balanced correctly.\n");
    // If found incorrect validation - not balanced
    else
        printf("The parentheses are not balanced correctly.\n");
    // clean the buffer before moving to the next case

}
// Func that looking for opener parentheses. and check if the input is correct
int findOpener() {
    char item;
    // first take the inpute from the user then take the item from the buffer
    scanf("%c", &item);
    // If it is a closer parentheses - not balanced
    if (item == ')' || item == ']' || item == '}' || item == '>') {
        // delete! printf("found closer while looking for opener\n");
        scanf("%*[^\n]");
        return 0;
    }
    // If we get till the end - correct
    if (item == '\n') {
        return 1;
    }
    // If we found an opener parentheses - we call a func that looking for it closer
    if (item == '[' || item == '(' || item == '{' || item == '<'){
        // delete! printf("found opener %c start looking for closer\n", item);
        // if the openers will complete - move on to find new one
        if(findCloser(item)) {
            // delete! printf("retun from find closer - start looking for new opener\n");
            return findOpener();
        }
        // if the opener didnt close or get to not balanced situation - 0
        else
            return 0;
    }
    // continue to check if not all above
    return findOpener();
    }
// func that find the closer - take the opener with it
int findCloser (char opener) {
    char item;
    // take new item from the buffer
    scanf("%c", &item);
    // if the item match to it closer - continue to check
    if (item == specificCloser(opener)) {
        // delete! printf("found closer %c\n", item);
        return 1;
    }
    // else if the item is closer that we didn't look for - not ballanced
    else if (item == ')' || item == ']' || item == '}' || item == '>') {
        // delete! printf("found opener %c while checking for closer\n", item);
        scanf("%*[^\n]");
        return 0;
    }
    // if we get to the end while looking for a closer - not balanced
    if (item == '\n') {
        // delete! printf("got to the end with not closed parenth\n", item);
        return 0;
    }
    // if it finds new opener while looking for closer - start looking for closer to the new one
    if (item == '(' || item == '[' || item == '{' || item == '<') {
        // if the find closer to the new parenth will be not ballanced - 0 (incomplete)
        // delete! printf("found new opener %c start looking for closer\n", item);
        if (!findCloser(item))
            return 0;
    }
    // keep looking for a closer to the origin one
    return findCloser(opener);

}
// func that return the closer to a specific opener
char specificCloser (char opener) {
    if (opener == '(')
        return ')';
    if (opener == '[')
        return ']';
    if (opener == '{')
        return '}';
    if (opener == '<')
        return '>';
    return '\0';
}

void task4QueensBattle() {
    // dimension
    int dimension;
    // the board the user will give
    char givenBoard[BOARD_SIZE][BOARD_SIZE]={0};
    // the board I will print
    char printBoard[BOARD_SIZE][BOARD_SIZE]={0};
    // An array that will track if there is queen in the row
    int rowTrack[BOARD_SIZE]={0};
    // An array that will track if there is queen in the column
    int columnTrack[BOARD_SIZE]={0};
    // An array that will track if there is queen in the area (by adding 1 to the location that is the number in ASCII
    int areaTrack[ASCII]={0};
    printf("Please enter the board dimensions:\n");
    scanf("%d", &dimension);
    printf("Please enter a %d*%d puzzle board:\n",dimension , dimension);
    // take the user input
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++)
            scanf(" %c", &givenBoard[i][j]);
    }
    if (dimension < 0 || (dimension > 1 && dimension < BOARD_LIMIT))
        printf("This puzzle cannot be solved.\n");
    //if the func queen that solve the board succeed it will print the board that was modify with queens
    else if (queen(0,0,dimension, rowTrack, columnTrack, areaTrack, givenBoard, printBoard)) {
        printf("Solution:\n");
        for (int i=0; i<dimension;i++){
            for (int j=0; j<dimension;j++){
                // if it has queen in the location
                if (printBoard[i][j] == 'X')
                    printf("%c ", printBoard[i][j]);
                else
                    printf("* ");
            }
            printf("\n");
        }
    }
    // cant be solved
    else
    printf("This puzzle cannot be solved.\n");
}
// the func that try to solve the board
int queen(int y, int x, int dimension, int rowTrack[BOARD_SIZE], int columnTrack[BOARD_SIZE], int areaTrack[ASCII], \
          char givenBoard[BOARD_SIZE][BOARD_SIZE], char printBoard[BOARD_SIZE][BOARD_SIZE]) {
    // Success (stop condition)
    if (y==dimension && columnTrack[y-1]==1)
        return 1;
    // the program tried all combination with no success (exceed out of the dimension) - fail
    else if(x==dimension)
        return 0;
    // if the check for the location is good, put queen, mark it in the trackers and move to the start of the next row
    if (check(y,x,rowTrack,columnTrack, areaTrack, givenBoard, printBoard)) {
        mark(y, x, rowTrack, columnTrack, areaTrack, givenBoard, printBoard);
        // if the next row cant have queen in it, unmark the trackers and put queen in the former row next column
        if (!(queen(y+1, 0, dimension, rowTrack, columnTrack, areaTrack, givenBoard, printBoard))) {
            unmark(y, x, rowTrack, columnTrack, areaTrack, givenBoard, printBoard);
            return queen(y, x+1, dimension, rowTrack, columnTrack, areaTrack, givenBoard, printBoard);
        }
    }
    // if cant put queen in the location - move to the nearby location
    else
        return (queen(y, x+1, dimension, rowTrack, columnTrack, areaTrack, givenBoard, printBoard));
    return 1;
}
// func that check if it can take queen
int check (int y, int x, int rowTrack[BOARD_SIZE], int columnTrack[BOARD_SIZE], int areaTrack[ASCII], \
          char givenBoard[BOARD_SIZE][BOARD_SIZE], char printBoard[BOARD_SIZE][BOARD_SIZE] ) {
    int currentAre = givenBoard[y][x];
    /*
     check what is inside the accord location in the trackers and check the nearby diagonals
     1 - clear
     0 - cant put there
     if there is 1 in the tracer or 'X' in the diagoals - 0
    */
    return (!rowTrack[y] && !columnTrack[x] && !areaTrack[currentAre] && checkDiagonal(y, x, printBoard));
}
// check if there is queen in the diagonals
int checkDiagonal(int y, int x , char printBoard[BOARD_SIZE][BOARD_SIZE]) {
    if(printBoard[y+1][x+1] == 'X' || \
        printBoard[y+1][x-1] == 'X'|| \
        printBoard[y-1][x-1] == 'X'|| \
        printBoard[y-1][x+1] == 'X'){
        // if there is queen
        return 0;
        }
    else
        // clear
        return 1;

}
// func that put queen in the print board and update the trackers
void mark (int y, int x, int rowTrack[BOARD_SIZE], int columnTrack[BOARD_SIZE], int areaTrack[ASCII], \
          char givenBoard[BOARD_SIZE][BOARD_SIZE], char printBoard[BOARD_SIZE][BOARD_SIZE]) {
    // put queen
    printBoard[y][x] = 'X';
    // update row
    rowTrack[y] = 1;
    // update columns
    columnTrack[x] = 1;
    int currentArea = givenBoard[y][x];
    // update area (locatin is the numeral value in ASCII)
    areaTrack[currentArea] = 1;
}
//func that unmark if the next row couldnt take queen
void unmark (int y, int x, int rowTrack[BOARD_SIZE], int columnTrack[BOARD_SIZE], int areaTrack[ASCII], \
          char givenBoard[BOARD_SIZE][BOARD_SIZE], char printBoard[BOARD_SIZE][BOARD_SIZE]) {
    // update row
    rowTrack[y] = 0;
    // update columns
    columnTrack[x] = 0;
    int currentArea = givenBoard[y][x];
    // update the area
    areaTrack[currentArea] = 0;
    // change the queen to '*'
    printBoard[y][x] = '*';
}


void task5CrosswordGenerator() {
    char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX] = {0};
    int dimension;

    printf("Please enter the dimensions of the crossword grid:\n");
    scanf("%d", &dimension);
    int slotsNum;
    printf("Please enter the number of slots in the crossword:\n");
    scanf("%d", &slotsNum);
    Slot slotArray[SLOTS_MAX];
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
    for (int i = 0; i < slotsNum; i++) {
        scanf("%d %d %d %c",\
            &slotArray[i].row, &slotArray[i].colmn, &slotArray[i].length, &slotArray[i].direction);
        slotArray[i].occupation = -1;
    }
    int wordsNum;
    printf("Please enter the number of words in the dictionary:\n");
    scanf("%d", &wordsNum);
    while (wordsNum < slotsNum) {
        printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", slotsNum);
        scanf("%d", &wordsNum);
    }
    Word wordArray[SLOTS_MAX];
    printf("Please enter the words for the dictionary:\n");
    for (int i = 0; i < wordsNum; i++) {
        scanf("%s", wordArray[i].letters);
        wordArray[i].length = strlen(wordArray[i].letters);
        wordArray[i].occupation = 0;
    }
    if (singWordToSlot(0, slotArray, 0, wordArray, crosswordBoard, slotsNum, wordsNum)) {
        for (int i = 0; i < dimension; i++) {
            printf("| ");
            for (int j = 0; j < dimension; j++) {
                if (crosswordBoard[i][j] == '\0')
                    printf("# ");
                else
                    printf("%c ", crosswordBoard[i][j]);
                printf("| ");
            }
            printf("\n");
        }
    }
    else
        printf("This crossword cannot be solved.\n");
}

int singWordToSlot (int slotIndex, Slot slotArray[SLOTS_MAX], int wordIndex, Word wordArray[SLOTS_MAX],\
    char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX], int slotNum, int wordNum) {
    if (slotIndex == slotNum)
        return 1;

    if (wordIndex == wordNum)
        return 0;

    if (validPlace(slotArray[slotIndex], wordArray[wordIndex], crosswordBoard)) {
        insert(slotIndex, slotArray, wordIndex, wordArray, crosswordBoard, 0);
        if (singWordToSlot(slotIndex+1, slotArray, 0, wordArray, crosswordBoard, slotNum, wordNum))
            return 1;
        removeInsert(slotIndex, slotArray, wordIndex, wordArray, crosswordBoard, 0);
        reInsert(slotIndex, slotArray, wordIndex, wordArray, crosswordBoard, slotNum, 0);
    }
    return singWordToSlot(slotIndex, slotArray, wordIndex + 1, wordArray, crosswordBoard, slotNum, wordNum);
}

int validPlace (Slot slot, Word word, char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX]) {

    // delete! printf("check for %s\n", word.letters);
    if (slot.length != word.length) {
        // delete! printf("Wrong word length.\n");
        return 0;
    }
    if (word.occupation) {
        // delete! printf("Used word\n");
        return 0;
    }
    if (!checkPreviuseInsert(slot, word, crosswordBoard)) {
        // delete! printf("Dont much the other previude words\n");
        return 0;
    }
    return 1;
}

int checkPreviuseInsert (Slot slot, Word word, char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX]) {
    if (slot.direction == 'H')
        return checkH(slot, word, 0, slot.row, slot.colmn, crosswordBoard);
    else
        return checkV(slot, word, 0, slot.row, slot.colmn, crosswordBoard);
}

int checkH (Slot slot, Word word, int counter, int row, int colmn, char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX]) {
    // delete! printf("Checking for words in the horizion: %s\n", word.letters);
    if (counter == word.length)
        return 1;
    if (crosswordBoard[row][colmn] == '\0')
        return checkH(slot, word, counter + 1, row, colmn + 1, crosswordBoard);
    if (word.letters[counter] != crosswordBoard[row][colmn])
        // delete! printf("Wrong much %c in (%d,%d)\n", crosswordBoard[row][colmn], row, colmn);
        return 0;
    return checkH(slot, word, counter + 1, row, colmn + 1, crosswordBoard);
}

int checkV (Slot slot, Word word, int counter, int row, int colmn, char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX]) {
    // delete! printf("Checking for words in the vertical: %s\n", word.letters);
    if (counter == word.length)
        return 1;
    if (crosswordBoard[row][colmn] == '\0')
        return checkV(slot, word, counter + 1, row + 1, colmn, crosswordBoard);
    if (word.letters[counter] != crosswordBoard[row][colmn])
        return 0;
    return checkV(slot, word, counter + 1, row + 1, colmn, crosswordBoard);
}

void insert (int slotIndex, Slot slotArray[SLOTS_MAX], int wordIndex, Word wordArray[SLOTS_MAX],\
    char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX], int counter) {
    // delete! printf("insert %s\n", wordArray[wordIndex].letters);
    if (slotArray[slotIndex].direction == 'H')
        insertH(slotArray[slotIndex], wordArray[wordIndex], crosswordBoard,\
            slotArray[slotIndex].row, slotArray[slotIndex].colmn, counter);
    else
        insertV(slotArray[slotIndex], wordArray[wordIndex], crosswordBoard,\
            slotArray[slotIndex].row, slotArray[slotIndex].colmn, counter);
    wordArray[wordIndex].occupation = 1;
    slotArray[slotIndex].occupation = wordIndex;
}

void insertH (Slot slot, Word word,  char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX],\
    int row, int colmn, int counter) {
    if (counter == word.length) {
        return;
    }
    crosswordBoard[row][colmn] = word.letters[counter];
    insertH(slot, word, crosswordBoard, row, colmn + 1, counter + 1);
}

void insertV (Slot slot, Word word, char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX],\
    int row, int colmn, int counter) {
    if (counter == word.length) {
        return;
    }
    crosswordBoard[row][colmn] = word.letters[counter];
    insertV(slot, word, crosswordBoard, row + 1, colmn, counter + 1);
}

void removeInsert (int slotIndex, Slot slotArray[SLOTS_MAX], int wordIndex, Word wordArray[SLOTS_MAX],\
    char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX], int counter) {
    // delete! printf("remove %s length: %d\n", wordArray[wordIndex].letters, wordArray[wordIndex].length);
    if (slotArray[slotIndex].direction == 'H')
        removeH(slotArray[slotIndex], wordArray[wordIndex], crosswordBoard,\
            slotArray[slotIndex].row, slotArray[slotIndex].colmn, counter);
    else
        removeV(slotArray[slotIndex], wordArray[wordIndex], crosswordBoard,\
            slotArray[slotIndex].row, slotArray[slotIndex].colmn, counter);
    wordArray[wordIndex].occupation = 0;
    slotArray[slotIndex].occupation = -1;
}

void removeH (Slot slot, Word word, char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX],\
    int row, int colmn, int counter) {
    if (counter == word.length) {
        return;
    }
    crosswordBoard[row][colmn] = '\0';
    removeH(slot, word, crosswordBoard, row, colmn + 1, counter + 1);
}

void removeV (Slot slot, Word word, char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX],\
    int row, int colmn, int counter) {
    if (counter == word.length) {
        return;
    }
    crosswordBoard[row][colmn] = '\0';
    removeH(slot, word, crosswordBoard, row + 1, colmn, counter + 1);
}

void reInsert (int slotIndex, Slot slotArray[SLOTS_MAX], int wordIndex, Word wordArray[SLOTS_MAX],\
    char crosswordBoard[CROSSWORD_MAX][CROSSWORD_MAX], int slotsNum, int counter) {
    if (counter == slotIndex)
        return;
    if (slotArray[counter].occupation >= 0)
        insert(counter, slotArray, slotArray[counter].occupation, wordArray, crosswordBoard, 0);
    reInsert(slotIndex, slotArray, wordIndex, wordArray, crosswordBoard, slotsNum, counter + 1);
}

