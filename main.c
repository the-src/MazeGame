#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>

#define HEIGHT 18
#define WIDTH 18

int PlayerPositionRow, PlayerPositionColumn; // Player position
int MonsterPositionRow, MonsterPositionColumn; // Monster position
int ExitPositionRow, ExitPositionColumn;
int DistanceMonsterPlayer, DistanceMonsterExit;

bool PlayerPositionHasChanged;


unsigned char maze[WIDTH][HEIGHT] = {{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}, //0
                                     {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'}, //1
                                     {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'}, //2
                                     {'#', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', '#'}, //3
                                     {'#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'}, //4
                                     {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'}, //5
                                     {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'}, //6
                                     {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'}, //7
                                     {'#', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'}, //8
                                     {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'}, //9
                                     {'#', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'}, //10
                                     {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'}, //11
                                     {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', '#'}, //12
                                     {'#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'}, //13
                                     {'#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'}, //14
                                     {'#', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'}, //15
                                     {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'}, //16
                                     {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} //17
};


int action() {
    int input;
    input = getch(); // Get input for movement
    return input;
}

void grid() {
    int i, j;
    for (i = 0; i < WIDTH; i++) {
        for (j = 0; j < HEIGHT; j++) {
            switch (maze[i][j]) {
                case '#':
                    printf("\u2588"); // Prints a block
                    break;
                case ' ':
                    printf("\u00a0"); // Prints a space
                    break;
                case 'P':
                    printf("\u263a"); // Prints the player
                    break;
                case 'M':
                    printf("\u1d25"); // Prints the monster
                    break;
                case 'E':
                    printf("\u2591"); // Prints the exit
                    break;
            }
        }
        printf("\n");
    }
}

void playerMove(int posRow, int posColumn) {
    PlayerPositionHasChanged = false;

    // When Caps Lock is on, the player also can move up and down
    switch (action()) {
        case 87:
        case 119: // W
            if (maze[posRow - 1][posColumn] != '#') {
                maze[posRow][posColumn] = ' ';
                maze[posRow - 1][posColumn] = 'P';
                PlayerPositionRow--;
                PlayerPositionHasChanged = true;
            }
            break;
        case 65:
        case 97: // A
            if (maze[posRow][posColumn - 1] != '#') {
                maze[posRow][posColumn] = ' ';
                maze[posRow][posColumn - 1] = 'P';
                PlayerPositionColumn--;
                PlayerPositionHasChanged = true;
            }
            break;
        case 83:
        case 115: // S
            if (maze[posRow + 1][posColumn] != '#') {
                maze[posRow][posColumn] = ' ';
                maze[posRow + 1][posColumn] = 'P';
                PlayerPositionRow++;
                PlayerPositionHasChanged = true;
            }
            break;
        case 68:
        case 100: // D
            if (maze[posRow][posColumn + 1] != '#') {
                maze[posRow][posColumn] = ' ';
                maze[posRow][posColumn + 1] = 'P';
                PlayerPositionColumn++;
                PlayerPositionHasChanged = true;
            }
            break;
    }
}

void EasyMonsterMove(int posRow, int posColumn) {
    if (PlayerPositionHasChanged == false) {
        return;
    }

    int move = rand() % 4;

    switch (move) {
        case 0: // W
            if (maze[posRow - 1][posColumn] != '#') {
                maze[posRow][posColumn] = ' ';
                maze[posRow - 1][posColumn] = 'M';
                MonsterPositionRow--;
            } else {
                EasyMonsterMove(posRow, posColumn);
            }
            break;
        case 1: // A
            if (maze[posRow][posColumn - 1] != '#') {
                maze[posRow][posColumn] = ' ';
                maze[posRow][posColumn - 1] = 'M';
                MonsterPositionColumn--;
            } else {
                EasyMonsterMove(posRow, posColumn);
            }
            break;
        case 2: // S
            if (maze[posRow + 1][posColumn] != '#') {
                maze[posRow][posColumn] = ' ';
                maze[posRow + 1][posColumn] = 'M';
                MonsterPositionRow++;
            } else {
                EasyMonsterMove(posRow, posColumn);
            }
            break;
        case 3: // D
            if (maze[posRow][posColumn + 1] != '#') {
                maze[posRow][posColumn] = ' ';
                maze[posRow][posColumn + 1] = 'M';
                MonsterPositionColumn++;
            } else {
                EasyMonsterMove(posRow, posColumn);
            }
            break;
    }
}

void setInitialPlayerPosition() {
    int i, j;
    bool validCell = false;

    while (!validCell) {
        i = rand() % (WIDTH - 2) + 1;
        j = rand() % (HEIGHT - 2) + 1;
        if (maze[i][j] == ' ') {
            validCell = true;
            maze[i][j] = 'P';
            PlayerPositionRow = i;
            PlayerPositionColumn = j;
            break;
        }
    }
}

void setInitialMonsterPosition() {
    int k, l, p;
    while (1) {
        k = rand() % (WIDTH - 2) + 1; // 1 to 16
        p = rand() % 16 + 17; // 16 to 32
        l = p - k;

        MonsterPositionRow = PlayerPositionRow + k;
        MonsterPositionColumn = abs(PlayerPositionColumn - l);

        if (maze[MonsterPositionRow][MonsterPositionColumn] == ' ') {
            DistanceMonsterPlayer = abs(PlayerPositionRow - MonsterPositionRow) + abs(PlayerPositionColumn - MonsterPositionColumn);
            DistanceMonsterExit = abs(ExitPositionRow - MonsterPositionRow) + abs(ExitPositionColumn - MonsterPositionColumn);
            if (DistanceMonsterPlayer > 16 && DistanceMonsterExit > 16) {
                continue;
            }
            maze[MonsterPositionRow][MonsterPositionColumn] = 'M';
            break;
        }
    }
}

void setInitialExitPosition() {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (maze[i][j] == 'E') {
                ExitPositionRow = i;
                ExitPositionColumn = j;
            }
        }
    }
}

int main() {
    system("chcp 65001"); // Set console encoding to UTF-8
    system("cls");
    srand(time(NULL)); // Seed the random number generator
    setInitialExitPosition(); // Set the exit position
    setInitialPlayerPosition(); // Set the player position
    setInitialMonsterPosition(); // Set the monster position
    grid(); // Print the grid
    while (1) {
        playerMove(PlayerPositionRow, PlayerPositionColumn);
        EasyMonsterMove(MonsterPositionRow, MonsterPositionColumn);
        system("cls");
        grid();
        printf("%d %d", DistanceMonsterExit, DistanceMonsterPlayer);
        if (!DistanceMonsterPlayer) {
            system("cls");
            printf("You lost!\n");
            getchar();
            break;
        }
        if (PlayerPositionRow == ExitPositionRow && PlayerPositionColumn == ExitPositionColumn) {
            system("cls");
            printf("You won!\n");
            getchar();
            break;
        }
    }
    return 0;
}

