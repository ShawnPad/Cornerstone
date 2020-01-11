/* 
 * File:   main.cpp
 * Author: spadilla
 *
 * Created on October 23, 2018, 7:51 PM
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

const int B = 0; //empty
const int S = 1; //silver coin
const int G = 2; //gold coin
const int P = 3; //player
void printBoard(int a[], int size); //print game board to console
int dice(); //roll a die
int game(int win);

int main(int argc, char** argv) {
    srand(time(0));
    //if you win first try the jailor will play race to 3
    int win = 0;
    int loss = 0;
    //welcome
    cout << "Welcome to The Ploy of the Jailor" << endl << endl;
    //extra credit race to 3
    while (win < 3 && loss < 3) {
        int out = game(win); //play game and save output ie 3 if you lose first
        //1 if you win 0 if you lose
        if (out == 3) {
            break; //if you lose first you lose the game w/o race to 3
        } else if (out) {
            win++;
        } else {
            loss++;
        }
        cout << "Wins: " << win << " |Losses: " << loss << endl;
    }
    if (win == 3) {
        cout << "You Escaped!" << endl;
    }
    if (loss == 3) {
        cout << "You Died." << endl;
    }
    return 0;
}

int game(int win) {
    int board[16];
    //initialize board
    int boardLength = (sizeof (board) / sizeof (*board));
    for (int i = 0; i < boardLength; i++) {
        board[i] = B;
    }
    //place player at start
    board[0] = P;
    //place silver coin
    int sc = rand() % 15 + 1;
    board[sc] = S;
    cout << "The jailor placed silver coin on space: " << sc << endl;
    int gc1 = 0;
    int gc2 = 0;
    //get user input for gold coin placement
    do {
        cout << "What spaces do you want to place your two gold coins on?(1-15)" << endl;
        cin>>gc1;
        cin.ignore();
        cin>>gc2;
        //anti cheat
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Invalid" << endl;
            continue;
        }
        //anti cheat
        if ((gc1 <= 0 || gc1 >= 16) || (gc2 <= 0 || gc2 >= 16)) {
            cout << "You can't trick the jailor! Choose an number from 1 to 15!" << endl;
        }
        //extra credit hard mode if you cheat
        if (gc1 == sc || gc2 == sc) {
            cout << "The Jailor is angry that you put your coin on his!" << endl;
            cout << "You now only get one gold coin and the jailer gets two silver coins!" << endl;
            int sc2;
            do {
                sc2 = rand() % 15 + 1;
                if (sc2 != sc) {
                    board[sc2] = S;
                    cout << "The jailor placed another silver coin on space: " << sc2 << endl;
                }
            } while (sc2 == sc);
            do {
                cout << "What space do you want to place your gold coin on?(1-15)" << endl;
                cin>>gc1;
                gc2 = 0;
                //anti cheat
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore();
                    cout << "Invalid" << endl;
                    continue;
                }
            } while (gc1 <= 0 || gc1 >= 16 || gc1 == sc || gc1 == sc2);
            break;
        }
    } while ((gc1 <= 0 || gc1 >= 16) || (gc2 <= 0 || gc2 >= 16) || gc1 == sc || gc2 == sc);
    //place gold coins
    board[gc1] = G;
    if (gc2 != 0) {
        board[gc2] = G;
    }
    //game start
    int game = 1;
    int autoPlay = 0; //AutoPlay boolean
    int acounter = 0; //AutoPlay iteration counter
    cin.ignore();
    do {
        printBoard(board, boardLength);
        if (!autoPlay) {
            cout << "Press enter to roll, enter any other character to auto play." << endl;
            if (cin.get() == '\n') {
            } else {
                autoPlay = 1;
            }
        } else {
            acounter++;
            cout << "AutoPlay: " << acounter << endl;
        }
        int roll = dice();
        cout << "**You rolled: " << roll << "**" << endl;
        //Where is the player?
        int indexP = 0;
        for (int i = 0; i < boardLength; i++) {
            if (board[i] == P) {
                indexP = i;
            }
        }
        //pass go!
        if (indexP + roll > 15) {
            board[indexP] = B;
            board[0] = P;
            cout << "Passed end, return to Start." << endl;
        } else if (board[indexP + roll] == G) {
            //touch gold win!
            board[indexP] = B;
            board[indexP + roll] = G + P;
            game = 0;
            printBoard(board, boardLength);
            cout << "You won this round!" << endl;
            if (win == 0) {
                cout << "The jailor is lonely and wants to play race to 3! Play again." << endl << endl;
            }
            return 1;
        } else if (board[indexP + roll] == S) {
            //touch silver lose :(
            game = 0;
            board[indexP] = B;
            board[indexP + roll] = S + P;
            printBoard(board, boardLength);
            if (win == 0) {
                cout << "You Died." << endl;
                break;
            } else {
                cout << "You lost this round." << endl;
            }
            return 0;
        } else {
            //Move player
            board[indexP] = B;
            board[indexP + roll] = P;
        }
    } while (game);
    return 3;
}

int dice() {
    return rand() % 6 + 1;
}

void printBoard(int a[], int size) {
    cout << "------------------------------" << endl;
    cout << "Board: " << endl;
    for (int i = 0; i < size; i++) {
        if (a[i] == S) {
            cout << "S|";
        }
        if (a[i] == G) {
            cout << "G|";
        }
        if (a[i] == S + P) {
            cout << "SP|";
        }
        if (a[i] == G + P) {
            cout << "GP|";
        }
        if (i == 0) {
            if (a[i] == P) {
                cout << "|StartP|";
            } else {
                cout << "|Start|";
            }
        } else if (a[i] == P) {
            cout << "P|";
        } else if (a[i] == B) {
            cout << "#|";
        }
    }
    cout << endl;
    cout << "------------------------------" << endl;
}
