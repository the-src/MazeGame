/*
 Yusuf Saraçlıoğlu
 Date: 2022-04-30
 Intro to C Programming EHB 110E
 CRN:25333 Homework #1
 This code only works in Windows runtime environment. And CMD recommended while running this code.
 You can compile this code with Clion, Code::Blocks, Visual Studio, etc.
 Also you can compile in the following way:
 gcc main.c -o main.exe
 */

/* Known problems:
 In hard mode, when monster crosses a wall program crashes, but when it is in easy mode, it works fine.
 I tried to resolve this problem but it didn't work.
*/

// Advices for playing: Play in fulscreen in CMD. Enjoy!


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>

// Some declarations and initializations for the game
#define HEIGHT 18
#define WIDTH 18

static int PlayerPositionRow, PlayerPositionColumn; // Player position
static int MonsterPositionRow, MonsterPositionColumn; // Monster position
int ExitPositionRow, ExitPositionColumn;
int DistanceMonsterPlayer, DistancePlayerExit, DistanceMonsterPlayerOld;

void EasyMode(), HardMode();

bool PlayerPositionHasChanged;

// This is the maze
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

void Menu() {
    // This function prints the menu and asks the user to choose an option to play hard or easy mode
    printf("                                                                                                                                                                            \n"
           "                                                                                                                                                                            \n"
           "           .              __.....__                __  __   ___                             __.....__                                   __  __   ___         __.....__      \n"
           "         .'|          .-''         '.             |  |/  `.'   `.                       .-''         '.               .--./)           |  |/  `.'   `.   .-''         '.    \n"
           "     .| <  |         /     .-''\"'-.  `.           |   .-.  .-.   '                     /     .-''\"'-.  `.            /.''\\\\            |   .-.  .-.   ' /     .-''\"'-.  `.  \n"
           "   .' |_ | |        /     /________\\   \\          |  |  |  |  |  |    __              /     /________\\   \\          | |  | |      __   |  |  |  |  |  |/     /________\\   \\ \n"
           " .'     || | .'''-. |                  |          |  |  |  |  |  | .:--.'.  .--------.|                  |           \\`-' /    .:--.'. |  |  |  |  |  ||                  | \n"
           "'--.  .-'| |/.'''. \\\\    .-------------'          |  |  |  |  |  |/ |   \\ | |____    |\\    .-------------'           /(\"'`    / |   \\ ||  |  |  |  |  |\\    .-------------' \n"
           "   |  |  |  /    | | \\    '-.____...---.          |  |  |  |  |  |`\" __ | |     /   /  \\    '-.____...---.           \\ '---.  `\" __ | ||  |  |  |  |  | \\    '-.____...---. \n"
           "   |  |  | |     | |  `.             .'           |__|  |__|  |__| .'.''| |   .'   /    `.             .'             /'\"\"'.\\  .'.''| ||__|  |__|  |__|  `.             .'  \n"
           "   |  '.'| |     | |    `''-...... -'                             / /   | |_ /    /___    `''-...... -'              ||     ||/ /   | |_                   `''-...... -'    \n"
           "   |   / | '.    | '.                                             \\ \\._,\\ '/|         |                              \\'. __// \\ \\._,\\ '/                                    \n"
           "   `'-'  '---'   '---'                                             `--'  `\" |_________|                               `'---'   `--'  `\"                                     ");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\tCoded by Yusuf Saraclioglu");
    printf("\n\n\t\t\t\t\t\t\t\t\tSelect an option:\n\n\t\t\t\t\t\t\t\t\t1. Start Game (Press any key except Q :) )\n\t\t\t\t\t\t\t\t\t2. Exit (Press Q)\n\n\t\t\t\t\t\t\t\t\t\t");
    char input = getch();
    if (input == 'Q' || input == 'q') {
        exit(0);
    } else {
        mode:
        system("cls");
        printf("Select MODE to play:\n1. Easy Mode (Press 1)\n2. Hard Mode (Press 2)");
        char mode = getch();
        if (mode == '1') {
            system("cls");
            EasyMode();
        } else if (mode == '2') {
            system("cls");
            HardMode();
        } else {
            goto mode;
        }
    }
}

void grid() {
    // This function prints the maze
    // For a better visualization, I used ASCII art and unicode characters
    int i, j;
    maze[8][1] = 'E';
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

int checkWin_Lose() {
    // This function checks if the player has won or lost looking at the maze positions of the player, monster and exit
    if (PlayerPositionRow == ExitPositionRow && PlayerPositionColumn == ExitPositionColumn) {
        system("cls");
        printf("\n\n\\ \\   /           \\ \\        /           | \n"
               " \\   / _ \\  |   |  \\ \\  \\   / _ \\  __ \\  | \n"
               "    | (   | |   |   \\ \\  \\ / (   | |   |_| \n"
               "   _|\\___/ \\__,_|    \\_/\\_/ \\___/ _|  _|_) \n");
        system("pause");
        system("cls");
        printf("Do you want to play again? (Y/N)\n");
        char input = getch();
        if (input == 'Y' || input == 'y') {
            system("cls");
            maze[MonsterPositionRow][MonsterPositionColumn] = ' ';
            maze[PlayerPositionRow][PlayerPositionColumn] = ' ';
            Menu();
        } else {
            exit(0);
        }
    } else if (PlayerPositionRow == MonsterPositionRow && PlayerPositionColumn == MonsterPositionColumn) {
        system("cls");
        printf("\n\n\\ \\   /            |                |   | \n"
               " \\   / _ \\  |   |  |      _ \\   __| __| | \n"
               "    | (   | |   |  |     (   |\\__ \\ |  _| \n"
               "   _|\\___/ \\__,_| _____|\\___/ ____/\\__|_) \n");
        system("pause");
        system("cls");
        printf("Do you want to play again? (Y/N)\n");
        char input = getch();
        if (input == 'Y' || input == 'y') {
            system("cls");
            maze[MonsterPositionRow][MonsterPositionColumn] = ' ';
            maze[PlayerPositionRow][PlayerPositionColumn] = ' ';
            Menu();
        } else {
            exit(0);
        }
    } else {
        return 0;
    }
}


void MonsterCatchPlayer() {
    // I get some unexpected results when monster and player are in the same position, so I put this function to make monster and player positions same
    PlayerPositionRow = MonsterPositionRow;
    PlayerPositionColumn = MonsterPositionColumn;
}

int action() {
    int input;
    input = getch(); // Get input for movement, W, A, S, D only
    return input;
}

void playerMove(int posRow, int posColumn) {
    PlayerPositionHasChanged = false; // This variable is used to check if the player has moved or not, if not, the monster will not move

    // When Caps Lock is on, the player also can move up and down
    switch (action()) {
        case 87:
        case 119: // W
            if (maze[posRow - 1][posColumn] != '#') {
                maze[posRow][posColumn] = ' ';
                if (maze[posRow - 1][posColumn] == 'M') {
                    MonsterCatchPlayer(); // If the player moves to the same position as the monster, the monster will catch the player
                    break;
                }
                maze[posRow - 1][posColumn] = 'P';
                PlayerPositionRow--;
                PlayerPositionHasChanged = true;
            }
            break;
        case 65:
        case 97: // A
            if (maze[posRow][posColumn - 1] != '#') {
                maze[posRow][posColumn] = ' ';
                if (maze[posRow][posColumn - 1] == 'M') {
                    MonsterCatchPlayer(); // If the player moves to the same position as the monster, the monster will catch the player
                    break;
                }
                maze[posRow][posColumn - 1] = 'P';
                PlayerPositionColumn--;
                PlayerPositionHasChanged = true;
            }
            break;
        case 83:
        case 115: // S
            if (maze[posRow + 1][posColumn] != '#') {
                maze[posRow][posColumn] = ' ';
                if (maze[posRow + 1][posColumn] == 'M') {
                    MonsterCatchPlayer(); // If the player moves to the same position as the monster, the monster will catch the player
                    break;
                }
                maze[posRow + 1][posColumn] = 'P';
                PlayerPositionRow++;
                PlayerPositionHasChanged = true;
            }
            break;
        case 68:
        case 100: // D
            if (maze[posRow][posColumn + 1] != '#') {
                maze[posRow][posColumn] = ' ';
                if (maze[posRow][posColumn + 1] == 'M') {
                    MonsterCatchPlayer(); // If the player moves to the same position as the monster, the monster will catch the player
                    break;
                }
                maze[posRow][posColumn + 1] = 'P';
                PlayerPositionColumn++;
                PlayerPositionHasChanged = true;
            }
            break;
    }
}

// This function is used to move the monster in easy mode
void EasyMonsterMove(int posRow, int posColumn) {
    if (PlayerPositionHasChanged == false) {
        return;
    }
    int move = rand() % 4 + 1; // Randomly choose a direction to move
    switch (move) {
        case 1: // W
            if (maze[posRow - 1][posColumn] != '#') {
                maze[posRow][posColumn] = ' ';
                if (maze[posRow - 1][posColumn] == 'P') {
                    MonsterCatchPlayer();
                    break;
                }
                maze[posRow - 1][posColumn] = 'M';
                MonsterPositionRow--;
            } else {
                EasyMonsterMove(posRow, posColumn);
            }
            break;
        case 2: // A
            if (maze[posRow][posColumn - 1] != '#') {
                maze[posRow][posColumn] = ' ';
                if (maze[posRow][posColumn - 1] == 'P') {
                    MonsterCatchPlayer();
                    break;
                }
                maze[posRow][posColumn - 1] = 'M';
                MonsterPositionColumn--;
            } else {
                EasyMonsterMove(posRow, posColumn);
            }
            break;
        case 3: // S
            if (maze[posRow + 1][posColumn] != '#') {
                maze[posRow][posColumn] = ' ';
                if (maze[posRow + 1][posColumn] == 'P') {
                    MonsterCatchPlayer();
                    break;
                }
                maze[posRow + 1][posColumn] = 'M';
                MonsterPositionRow++;
            } else {
                EasyMonsterMove(posRow, posColumn);
            }
            break;
        case 4: // D
            if (maze[posRow][posColumn + 1] != '#') {
                maze[posRow][posColumn] = ' ';
                if (maze[posRow][posColumn + 1] == 'P') {
                    MonsterCatchPlayer();
                    break;
                }
                maze[posRow][posColumn + 1] = 'M';
                MonsterPositionColumn++;
            } else {
                EasyMonsterMove(posRow, posColumn);
            }
            break;
    }
}

// This function is used to move the monster in hard mode
// In hard mode the distance between the player and the monster must decrease
// The monster will move in a random direction until it reaches the player
void HardMonsterMove(int posRow, int posColumn) {
    if (PlayerPositionHasChanged == false) {
        return;
    }

    int move = rand() % 4 + 1; // Randomly choose a direction to move
    DistanceMonsterPlayerOld = abs(posRow - PlayerPositionRow) + abs(posColumn -
                                                                     PlayerPositionColumn); // Calculate previous the distance between the monster and the player

    move:
    switch (move) {
        case 1: // W
            if (maze[posRow - 1][posColumn] != '#') {
                DistanceMonsterPlayer = abs((posRow - 1) - PlayerPositionRow) + abs(posColumn -
                                                                                    PlayerPositionColumn); // Calculate the distance between the monster and the player
                if (DistanceMonsterPlayer < DistanceMonsterPlayerOld) {
                    maze[posRow][posColumn] = ' ';
                    if (maze[posRow - 1][posColumn] == 'P') {
                        MonsterCatchPlayer();
                        break;
                    }
                    maze[posRow - 1][posColumn] = 'M';
                    MonsterPositionRow--;
                    break;
                }
            }
        case 2: // A
            if (maze[posRow][posColumn - 1] != '#') {
                DistanceMonsterPlayer = abs(posRow - PlayerPositionRow) + abs((posColumn - 1) -
                                                                              PlayerPositionColumn); // Calculate the distance between the monster and the player
                if (DistanceMonsterPlayer < DistanceMonsterPlayerOld) {
                    maze[posRow][posColumn] = ' ';
                    if (maze[posRow][posColumn - 1] == 'P') {
                        MonsterCatchPlayer();
                        break;
                    }
                    maze[posRow][posColumn - 1] = 'M';
                    MonsterPositionColumn--;
                    break;
                }
            }
        case 3: // S
            if (maze[posRow + 1][posColumn] != '#') {
                DistanceMonsterPlayer = abs((posRow + 1) - PlayerPositionRow) + abs(posColumn -
                                                                                    PlayerPositionColumn); // Calculate the distance between the monster and the player
                if (DistanceMonsterPlayer < DistanceMonsterPlayerOld) {
                    maze[posRow][posColumn] = ' ';
                    if (maze[posRow + 1][posColumn] == 'P') {
                        MonsterCatchPlayer();
                        break;
                    }
                    maze[posRow + 1][posColumn] = 'M';
                    MonsterPositionRow++;
                    break;
                }
            }
        case 4: // D
            if (maze[posRow][posColumn + 1] != '#') {
                DistanceMonsterPlayer = abs(posRow - PlayerPositionRow) + abs((posColumn + 1) -
                                                                              PlayerPositionColumn); // Calculate the distance between the monster and the player
                if (DistanceMonsterPlayer < DistanceMonsterPlayerOld) {
                    maze[posRow][posColumn] = ' ';
                    if (maze[posRow][posColumn + 1] == 'P') {
                        MonsterCatchPlayer();
                        break;
                    }
                    maze[posRow][posColumn + 1] = 'M';
                    MonsterPositionColumn++;
                    break;
                }
            }
        default:
            goto move;
    }
}

void setInitialPlayerPosition() {
    int i, j;
    bool validCell = false;

    maze[PlayerPositionRow][PlayerPositionColumn] = ' '; // Remove the player from the current position for playing the game again

    do {
        i = rand() % (WIDTH - 2) + 1;
        j = rand() % (HEIGHT - 2) + 1;
        DistancePlayerExit = abs(i - ExitPositionRow) + abs(j - ExitPositionColumn);

        if (maze[i][j] == ' ') {
            if (DistancePlayerExit > 16) {
                maze[i][j] = 'P';
                PlayerPositionRow = i;
                PlayerPositionColumn = j;
                validCell = true;
                break;
            }
        }
    } while (!validCell);
}

void setInitialMonsterPosition() {
    int i, j;
    bool validCell = false;

    maze[MonsterPositionRow][MonsterPositionColumn] = ' '; // Remove the monster from the current position for playing the game again

    do {
        i = rand() % (WIDTH - 2) + 1;
        j = rand() % (HEIGHT - 2) + 1;
        DistanceMonsterPlayer = abs(PlayerPositionRow - i) + abs(PlayerPositionColumn -
                                                                 j); // Calculate the distance between the monster and the player

        if (maze[i][j] == ' ') {
            if (DistanceMonsterPlayer > 16) {
                maze[i][j] = 'M';
                MonsterPositionRow = i;
                MonsterPositionColumn = j;
                validCell = true;
                break;
            }
        }
    } while (!validCell);
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

void EasyMode() {
    setInitialExitPosition(); // Set the exit position
    setInitialPlayerPosition(); // Set the player position
    setInitialMonsterPosition(); // Set the monster position
    grid();
    while (1) {
        playerMove(PlayerPositionRow, PlayerPositionColumn);
        EasyMonsterMove(MonsterPositionRow, MonsterPositionColumn);
        system("cls");
        grid();
        checkWin_Lose();
    }
}

void HardMode() {
    setInitialExitPosition(); // Set the exit position
    setInitialPlayerPosition(); // Set the player position
    setInitialMonsterPosition(); // Set the monster position
    grid();
    while (1) {
        playerMove(PlayerPositionRow, PlayerPositionColumn);
        HardMonsterMove(MonsterPositionRow, MonsterPositionColumn);
        system("cls");
        grid();
        checkWin_Lose();
    }
}


int main() {
    system("chcp 65001"); // Set console encoding to UTF-8
    system("cls");
    srand(time(NULL)); // Seed the random number generator
    Menu();
    return 0;
}