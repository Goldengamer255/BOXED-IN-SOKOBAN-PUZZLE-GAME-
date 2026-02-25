#include <stdio.h>

#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#define ROWS 10
#define COLS 10
#define SPACE 0
#define WALL 1
#define TARGET 2
#define BOX 3
#define BOX_ON_TARGET 4
#define PERSON 5
#define PERSON_ON_TARGET 6

void PrintRoom(int room[ROWS][COLS]) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (room[i][j] == SPACE) {
                printf(" ");
            }
            else if (room[i][j] == WALL) {
                printf("#");
            }
            else if (room[i][j] == TARGET) {
                printf("*");
            }
            else if (room[i][j] == BOX) {
                printf("O");
            }
            else if (room[i][j] == BOX_ON_TARGET) {
                printf("@");
            }
            else if (room[i][j] == PERSON) {
                printf("X");
            }
            else if (room[i][j] == PERSON_ON_TARGET) {
                printf("X");
            }
        }
        printf("\n"); 
    }
}

void InitialiseRoom(int room[ROWS][COLS], char *layout) {
    int i, j;
    int index = 0;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (layout[index] != '\0') {
                if (layout[index] == '0') {
                    room[i][j] = SPACE;
                }
                if (layout[index] == '1') {
                    room[i][j] = WALL;
                }
                if (layout[index] == '2') {
                    room[i][j] = TARGET;
                }
                if (layout[index] == '3') {
                    room[i][j] = BOX;
                }
                if (layout[index] == '4') {
                    room[i][j] = BOX_ON_TARGET;
                }
                if (layout[index] == '5') {
                    room[i][j] = PERSON;
                }
                if (layout[index] == '6') {
                    room[i][j] = PERSON_ON_TARGET;
                }
                index++;
            } else {
                room[i][j] = WALL;
            }
        }
    }
}

void LocatePerson(int room[ROWS][COLS], int *row, int *col) {
    int i,j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (room[i][j] != '\0')
                if (room[i][j] == PERSON || room[i][j] == PERSON_ON_TARGET) {
                    *row = i;
                    *col = j;
                    return;
                }
            }
        }
    }


// THIS IS TASK 10 FUNCTION
void UndoMove(int room[ROWS][COLS], char *allMoves) {
    int row, col;
    int index = strlen(allMoves);
    if (index < 2) {
        return;
    }
    char lastMove = allMoves[index - 2];
    char moveType = allMoves[index - 1];
    allMoves[index - 2] = '\0';
    
    LocatePerson(room, &row, &col);

    if (lastMove == 'w') {  // Undo move up
        if (moveType == '1') {  // If a box was pushed
            if (room[row][col] == PERSON) { // if person
                if (room[row-1][col] == BOX_ON_TARGET) { // if box in front is box on target
                    room[row-1][col] = TARGET;
                    room[row][col] = BOX;
                }
                else if (room[row-1][col] == BOX) { // if box in front is box on nothing
                    room[row-1][col] = SPACE;
                    room[row][col] = BOX;
                }
                if (room[row+1][col] == TARGET) { // if space behind is target
                    room[row+1][col] = PERSON_ON_TARGET;
                } else { // if space behind is not target
                    room[row+1][col] = PERSON;
                }
            } else if (room[row][col] == PERSON_ON_TARGET) { // if person is on target currently
                if (room[row-1][col] == BOX_ON_TARGET) { // if box in front is on target
                    room[row-1][col] = TARGET;
                    room[row][col] = BOX_ON_TARGET;
                } else if (room[row-1][col] == BOX) { // if box in front is not on target
                    room[row][col] = BOX_ON_TARGET;
                    room[row-1][col] = SPACE;
                }
                if (room[row+1][col] == TARGET) { // if space behind is target
                    room[row+1][col] = PERSON_ON_TARGET;
                } else { // if space behind is not target
                    room[row+1][col] = PERSON;
                }
            }
        } else if (moveType == '0') {
            if (room[row][col] == PERSON) {
                if (room[row+1][col] == TARGET) {
                    room[row+1][col] = PERSON_ON_TARGET;
                    room[row][col] = SPACE;
                } else {
                    room[row+1][col] = PERSON;
                    room[row][col] = SPACE;
                }
            } else if (room[row][col] == PERSON_ON_TARGET) {
                if (room[row+1][col] == TARGET) {
                    room[row+1][col] = PERSON_ON_TARGET;
                    room[row][col] = TARGET;
                } else {
                    room[row+1][col] = PERSON;
                    room[row][col] = TARGET;
                }
            }
        }
    } else if (lastMove == 's') {  // Undo move down
        if (moveType == '1') {  // If a box was pushed
            if (room[row][col] == PERSON) { // if person
                if (room[row+1][col] == BOX_ON_TARGET) { // if box in front is box on target
                    room[row+1][col] = TARGET;
                    room[row][col] = BOX;
                }
                else if (room[row+1][col] == BOX) { // if box in front is box on nothing
                    room[row+1][col] = SPACE;
                    room[row][col] = BOX;
                }
                if (room[row-1][col] == TARGET) { // if space behind is target
                    room[row-1][col] = PERSON_ON_TARGET;
                } else { // if space behind is not target
                    room[row-1][col] = PERSON;
                }
            } else if (room[row][col] == PERSON_ON_TARGET) { // if person is on target currently
                if (room[row+1][col] == BOX_ON_TARGET) { // if box in front is on target
                    room[row+1][col] = TARGET;
                    room[row][col] = BOX_ON_TARGET;
                } else if (room[row+1][col] == BOX) { // if box in front is not on target
                    room[row][col] = BOX_ON_TARGET;
                    room[row+1][col] = SPACE;
                }
                if (room[row-1][col] == TARGET) { // if space behind is target
                    room[row-1][col] = PERSON_ON_TARGET;
                } else { // if space behind is not target
                    room[row-1][col] = PERSON;
                }
            }
        } else if (moveType == '0') {
            if (room[row][col] == PERSON) {
                if (room[row-1][col] == TARGET) {
                    room[row-1][col] = PERSON_ON_TARGET;
                    room[row][col] = SPACE;
                } else {
                    room[row-1][col] = PERSON;
                    room[row][col] = SPACE;
                }
            } else if (room[row][col] == PERSON_ON_TARGET) {
                if (room[row-1][col] == TARGET) {
                    room[row-1][col] = PERSON_ON_TARGET;
                    room[row][col] = TARGET;
                } else {
                    room[row-1][col] = PERSON;
                    room[row][col] = TARGET;
                }
            }
        }
    } else if (lastMove == 'a') {  // Undo move left
        if (moveType == '1') {  // If a box was pushed
            if (room[row][col] == PERSON) { // if person
                if (room[row][col-1] == BOX_ON_TARGET) { // if box in front is box on target
                    room[row][col-1] = TARGET;
                    room[row][col] = BOX;
                }
                else if (room[row][col-1] == BOX) { // if box in front is box on nothing
                    room[row][col-1] = SPACE;
                    room[row][col] = BOX;
                }
                if (room[row][col+1] == TARGET) { // if space behind is target
                    room[row][col+1] = PERSON_ON_TARGET;
                } else { // if space behind is not target
                    room[row][col+1] = PERSON;
                }
            } else if (room[row][col] == PERSON_ON_TARGET) { // if person is on target currently
                if (room[row][col-1] == BOX_ON_TARGET) { // if box in front is on target
                    room[row][col-1] = TARGET;
                    room[row][col] = BOX_ON_TARGET;
                } else if (room[row][col-1] == BOX) { // if box in front is not on target
                    room[row][col] = BOX_ON_TARGET;
                    room[row][col-1] = SPACE;
                }
                if (room[row][col+1] == TARGET) { // if space behind is target
                    room[row][col+1] = PERSON_ON_TARGET;
                } else { // if space behind is not target
                    room[row][col+1] = PERSON;
                }
            }
        } else if (moveType == '0') {
            if (room[row][col] == PERSON) {
                if (room[row][col+1] == TARGET) {
                    room[row][col+1] = PERSON_ON_TARGET;
                    room[row][col] = SPACE;
                } else {
                    room[row][col+1] = PERSON;
                    room[row][col] = SPACE;
                }
            } else if (room[row][col] == PERSON_ON_TARGET) {
                if (room[row][col+1] == TARGET) {
                    room[row][col+1] = PERSON_ON_TARGET;
                    room[row][col] = TARGET;
                } else {
                    room[row][col+1] = PERSON;
                    room[row][col] = TARGET;
                }
            }
        }
    } else if (lastMove == 'd') {  // Undo move right
        if (moveType == '1') {  // If a box was pushed
            if (room[row][col] == PERSON) { // if person
                if (room[row][col+1] == BOX_ON_TARGET) { // if box in front is box on target
                    room[row][col+1] = TARGET;
                    room[row][col] = BOX;
                }
                else if (room[row][col+1] == BOX) { // if box in front is box on nothing
                    room[row][col+1] = SPACE;
                    room[row][col] = BOX;
                }
                if (room[row][col-1] == TARGET) { // if space behind is target
                    room[row][col-1] = PERSON_ON_TARGET;
                } else { // if space behind is not target
                    room[row][col-1] = PERSON;
                }
            } else if (room[row][col] == PERSON_ON_TARGET) { // if person is on target currently
                if (room[row][col+1] == BOX_ON_TARGET) { // if box in front is on target
                    room[row][col+1] = TARGET;
                    room[row][col] = BOX_ON_TARGET;
                } else if (room[row][col+1] == BOX) { // if box in front is not on target
                    room[row][col] = BOX_ON_TARGET;
                    room[row][col+1] = SPACE;
                }
                if (room[row][col-1] == TARGET) { // if space behind is target
                    room[row][col-1] = PERSON_ON_TARGET;
                } else { // if space behind is not target
                    room[row][col-1] = PERSON;
                }
            }
        } else if (moveType == '0') {
            if (room[row][col] == PERSON) {
                if (room[row][col-1] == TARGET) {
                    room[row][col-1] = PERSON_ON_TARGET;
                    room[row][col] = SPACE;
                } else {
                    room[row][col-1] = PERSON;
                    room[row][col] = SPACE;
                }
            } else if (room[row][col] == PERSON_ON_TARGET) {
                if (room[row][col-1] == TARGET) {
                    room[row][col-1] = PERSON_ON_TARGET;
                    room[row][col] = TARGET;
                } else {
                    room[row][col-1] = PERSON;
                    room[row][col] = TARGET;
                }
            }
        }
    } else { 
        return;
    }
}



// THIS IS TASK 8 FUNCTION!!!!!!!
void MakeMove(int room[ROWS][COLS], char move, char *allMoves) {
    int row, col;
    int index = strlen(allMoves);
    LocatePerson(room, &row, &col);
    // MOVE UP
    if (move == 'w') {
        if (room[row-1][col] == WALL || (room[row-2][col] == WALL && room[row-1][col] == BOX) || (room[row-2][col] == BOX && room[row-1][col] == BOX) || (room[row-2][col] == WALL && room[row-1][col] == BOX_ON_TARGET) || (room[row-2][col] == BOX_ON_TARGET && room[row-1][col] == BOX_ON_TARGET) || (room[row-2][col] == BOX_ON_TARGET && room[row-1][col] == BOX) || (room[row-2][col] == BOX && room[row-1][col] == BOX_ON_TARGET)) {
            return;
        }
        else if (room[row-1][col] == BOX) {
            if (room[row-2][col] == TARGET) {
                room[row-2][col] = BOX_ON_TARGET;
            }
            else {
                room[row-2][col] = BOX;
            }
            if (room[row][col] == PERSON_ON_TARGET) {
                room[row][col] = TARGET;
            } else {
                room[row][col] = SPACE;
            }
            room[row-1][col] = PERSON;
            allMoves[index++] = 'w';
            allMoves[index++] = '1';
            allMoves[index++] = '\0';
        }
        else if (room[row-1][col] == BOX_ON_TARGET) {
            if (room[row-2][col] == TARGET) {
                room[row-2][col] = BOX_ON_TARGET;
            }
            else {
                room[row-2][col] = BOX;
            }
            room[row-1][col] = PERSON_ON_TARGET;
            if (room[row][col] == PERSON_ON_TARGET) {
                room[row][col] = TARGET;
            } else {
                room[row][col] = SPACE;
            }
            allMoves[index++] = 'w';
            allMoves[index++] = '1';
            allMoves[index++] = '\0';
        }
        else {
            if (room[row-1][col] == TARGET) {
                room[row-1][col] = PERSON_ON_TARGET;
            }
            else {
                room[row-1][col] = PERSON;
            }
            if (room[row][col] == PERSON_ON_TARGET) {
                room[row][col] = TARGET;
            } else {
                room[row][col] = SPACE;
            }
            allMoves[index++] = 'w';
            allMoves[index++] = '0';
            allMoves[index++] = '\0';
        }
    }
    // MOVE DOWN
    else if (move == 's') {
        if (room[row+1][col] == WALL || (room[row+2][col] == WALL && room[row+1][col] == BOX) || (room[row+2][col] == BOX && room[row+1][col] == BOX) || (room[row+2][col] == WALL && room[row+1][col] == BOX_ON_TARGET) || (room[row+2][col] == BOX_ON_TARGET && room[row+1][col] == BOX_ON_TARGET) || (room[row+2][col] == BOX_ON_TARGET && room[row+1][col] == BOX) || (room[row+2][col] == BOX && room[row+1][col] == BOX_ON_TARGET)) {
            return;
        }
        else if (room[row+1][col] == BOX) {
            if (room[row+2][col] == TARGET) {
                room[row+2][col] = BOX_ON_TARGET;
            }
            else {
                room[row+2][col] = BOX;
            }
            if (room[row][col] == PERSON_ON_TARGET) {
                room[row][col] = TARGET;
            } else {
                room[row][col] = SPACE;
            }
            room[row+1][col] = PERSON;
            allMoves[index++] = 's';
            allMoves[index++] = '1';
            allMoves[index++] = '\0';
        }
        else if (room[row+1][col] == BOX_ON_TARGET) {
            if (room[row+2][col] == TARGET) {
                room[row+2][col] = BOX_ON_TARGET;
            }
            else {
                room[row+2][col] = BOX;
            }
            room[row+1][col] = PERSON_ON_TARGET;
            if (room[row][col] == PERSON_ON_TARGET) {
                room[row][col] = TARGET;
            } else {
                room[row][col] = SPACE;
            }
            allMoves[index++] = 's';
            allMoves[index++] = '1';
            allMoves[index++] = '\0';
        }
        else {
            if (room[row+1][col] == TARGET) {
                room[row+1][col] = PERSON_ON_TARGET;
            }
            else {
                room[row+1][col] = PERSON;
            }
            if (room[row][col] == PERSON_ON_TARGET) {
                room[row][col] = TARGET;
            } else {
                room[row][col] = SPACE;
            }
            allMoves[index++] = 's';
            allMoves[index++] = '0';
            allMoves[index++] = '\0';
        }
    }
    // MOVE LEFT
    else if (move == 'a') {
        if (room[row][col-1] == WALL || (room[row][col-2] == WALL && room[row][col-1] == BOX) || (room[row][col-2] == BOX && room[row][col-1] == BOX) || (room[row][col-2] == WALL && room[row][col-1] == BOX_ON_TARGET) || (room[row][col-2] == BOX_ON_TARGET && room[row][col-1] == BOX_ON_TARGET) || (room[row][col-2] == BOX_ON_TARGET && room[row][col-1] == BOX) || (room[row][col-2] == BOX && room[row][col-1] == BOX_ON_TARGET)) {
            return;
        }
        else if (room[row][col-1] == BOX) {
            if (room[row][col-2] == TARGET) {
                room[row][col-2] = BOX_ON_TARGET;
            }
            else {
                room[row][col-2] = BOX;
            }
            if (room[row][col] == PERSON_ON_TARGET) {
                room[row][col] = TARGET;
            } else {
                room[row][col] = SPACE;
            }
            room[row][col-1] = PERSON;
            allMoves[index++] = 'a';
            allMoves[index++] = '1';
            allMoves[index++] = '\0';
        }
        else if (room[row][col-1] == BOX_ON_TARGET) {
            if (room[row][col-2] == TARGET) {
                room[row][col-2] = BOX_ON_TARGET;
            }
            else {
                room[row][col-2] = BOX;
            }
            room[row][col-1] = PERSON_ON_TARGET;
            if (room[row][col] == PERSON_ON_TARGET) {
                room[row][col] = TARGET;
            } else {
                room[row][col] = SPACE;
            }
            allMoves[index++] = 'a';
            allMoves[index++] = '1';
            allMoves[index++] = '\0';
        }
        else {
            if (room[row][col-1] == TARGET) {
                room[row][col-1] = PERSON_ON_TARGET;
            }
            else {
                room[row][col-1] = PERSON;
            }
            if (room[row][col] == PERSON_ON_TARGET) {
                room[row][col] = TARGET;
            } else {
                room[row][col] = SPACE;
            }
            allMoves[index++] = 'a';
            allMoves[index++] = '0';
            allMoves[index++] = '\0';
        }
    }
    // MOVE RIGHT
    else if (move == 'd') {
        if (room[row][col+1] == WALL || (room[row][col+2] == WALL && room[row][col+1] == BOX) || (room[row][col+2] == BOX && room[row][col+1] == BOX) || (room[row][col+2] == WALL && room[row][col+1] == BOX_ON_TARGET) || (room[row][col+2] == BOX_ON_TARGET && room[row][col+1] == BOX_ON_TARGET) || (room[row][col+2] == BOX_ON_TARGET && room[row][col+1] == BOX) || (room[row][col+2] == BOX && room[row][col+1] == BOX_ON_TARGET)) {
            return;
        }
        else if (room[row][col+1] == BOX) {
            if (room[row][col+2] == TARGET) {
                room[row][col+2] = BOX_ON_TARGET;
            }
            else {
                room[row][col+2] = BOX;
            }
            if (room[row][col] == PERSON_ON_TARGET) {
                room[row][col] = TARGET;
            } else {
                room[row][col] = SPACE;
            }
            room[row][col+1] = PERSON;
            allMoves[index++] = 'd';
            allMoves[index++] = '1';
            allMoves[index++] = '\0';
        }
        else if (room[row][col+1] == BOX_ON_TARGET) {
            if (room[row][col+2] == TARGET) {
                room[row][col+2] = BOX_ON_TARGET;
            }
            else {
                room[row][col+2] = BOX;
            }
            room[row][col+1] = PERSON_ON_TARGET;
            if (room[row][col] == PERSON_ON_TARGET) {
                room[row][col] = TARGET;
            } else {
                room[row][col] = SPACE;
            }
            allMoves[index++] = 'd';
            allMoves[index++] = '1';
            allMoves[index++] = '\0';
        }
        else {
            if (room[row][col+1] == TARGET) {
                room[row][col+1] = PERSON_ON_TARGET;
            }
            else {
                room[row][col+1] = PERSON;
            }
            if (room[row][col] == PERSON_ON_TARGET) {
                room[row][col] = TARGET;
            } else {
                room[row][col] = SPACE;
            }
            allMoves[index++] = 'd';
            allMoves[index++] = '0';
            allMoves[index++] = '\0';
            }
        }
    else if (move == 'z') {
        UndoMove(room, allMoves);
    }
}
    
int main (void) { 
char layout[200] = "1111111111100000000110020000011002005001100200000110020000011002222201100300000110000000011111111111";
char moves[100] = {0};
int room[ROWS][COLS];
InitialiseRoom(room, layout);
MakeMove(room, 's', moves);
MakeMove(room, 's', moves);
MakeMove(room, 's', moves);
MakeMove(room, 'z', moves);
MakeMove(room, 'z', moves);
MakeMove(room, 'z', moves);
PrintRoom(room);
printf("Moves: %s", moves);
}

