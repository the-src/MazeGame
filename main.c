#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>

#define HEIGHT 18
#define WIDTH 18

int PlayerPositionX, PlayerPositionY; // Player position
int MonsterPositionX, MonsterPositionY; // Monster position
int ExitPositionX, ExitPositionY;

bool PlayerPositionHasChanged;


unsigned char maze[HEIGHT][WIDTH] = {{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}, //0
                                     {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'}, //1
                                     {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'}, //2
                                     {'#', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'}, //3
                                     {'#', 'M', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'}, //4
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
                                     {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'P', ' ', ' ', ' ', '#'}, //16
                                     {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} //17
};


int action() {
    int input;
    input = getch(); // Get input for movement
    return input;
}

void grid() {
    int i, j;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
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

void playerMove(int posX, int posY) {
    switch (action()) {
        case 87:
        case 119: // W
            if (maze[posX - 1][posY] != '#') {
                maze[posX][posY] = ' ';
                maze[posX - 1][posY] = 'P';
                PlayerPositionX--;
                PlayerPositionHasChanged = true;
            } else {
                PlayerPositionHasChanged = false;
            }
            break;
        case 65:
        case 97: // A
            if (maze[posX][posY - 1] != '#') {
                maze[posX][posY] = ' ';
                maze[posX][posY - 1] = 'P';
                PlayerPositionY--;
                PlayerPositionHasChanged = true;
            } else {
                PlayerPositionHasChanged = false;
            }
            break;
        case 83:
        case 115: // S
            if (maze[posX + 1][posY] != '#') {
                maze[posX][posY] = ' ';
                maze[posX + 1][posY] = 'P';
                PlayerPositionX++;
                PlayerPositionHasChanged = true;
            } else {
                PlayerPositionHasChanged = false;
            }
            break;
        case 68:
        case 100: // D
            if (maze[posX][posY + 1] != '#') {
                maze[posX][posY] = ' ';
                maze[posX][posY + 1] = 'P';
                PlayerPositionY++;
                PlayerPositionHasChanged = true;
            } else {
                PlayerPositionHasChanged = false;
            }
            break;
        default:
            PlayerPositionHasChanged = false;
            break;
    }
}

void EasyMonsterMove(int posX, int posY) {
    if (PlayerPositionHasChanged == false) {
        return;
    }

    int move = rand() % 4;

    switch (move) {
        case 0:
            if (maze[posX - 1][posY] != '#') {
                maze[posX][posY] = ' ';
                maze[posX - 1][posY] = 'M';
                MonsterPositionX--;
            } else {
                EasyMonsterMove(posX, posY);
            }
            break;
        case 1:
            if (maze[posX][posY - 1] != '#') {
                maze[posX][posY] = ' ';
                maze[posX][posY - 1] = 'M';
                MonsterPositionY--;
            } else {
                EasyMonsterMove(posX, posY);
            }
            break;
        case 2:
            if (maze[posX + 1][posY] != '#') {
                maze[posX][posY] = ' ';
                maze[posX + 1][posY] = 'M';
                MonsterPositionX++;
            } else {
                EasyMonsterMove(posX, posY);
            }
            break;
        case 3:
            if (maze[posX][posY + 1] != '#') {
                maze[posX][posY] = ' ';
                maze[posX][posY + 1] = 'M';
                MonsterPositionY++;
            } else {
                EasyMonsterMove(posX, posY);
            }
            break;
    }
}


void setInitialPlayerPosition() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (maze[i][j] == 'P') {
                PlayerPositionX = i;
                PlayerPositionY = j;
            }
        }
    }
}

void setInitialMonsterPosition() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            while (maze[i][j] != '#' || maze[i][j] != 'P' || maze[i][j] != 'E') {
                

            }
        }
    }
}

void setInitialExitPosition() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (maze[i][j] == 'E') {
                ExitPositionX = i;
                ExitPositionY = j;
            }
        }
    }
}


int main() {
    system("chcp 65001"); // Set console encoding to UTF-8
    system("cls");
    srand(time(NULL)); // Seed the random number generator
    grid();
    setInitialPlayerPosition(); // Set the player position
    setInitialMonsterPosition(); // Set the monster position
    setInitialExitPosition(); // Set the exit position
    while (1) {
        playerMove(PlayerPositionX, PlayerPositionY);
        EasyMonsterMove(MonsterPositionX, MonsterPositionY);
        system("cls");
        grid();
        if (PlayerPositionX == MonsterPositionX && PlayerPositionY == MonsterPositionY) {
            system("cls");
            printf("You lost!\n");
            getchar();
            break;
        }
        if (PlayerPositionX == ExitPositionX && PlayerPositionY == ExitPositionY) {
            system("cls");
            printf("You won!\n");
            getchar();
            break;
        }
    }
    return 0;
}

