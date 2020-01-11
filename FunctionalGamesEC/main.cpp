/* 
 * File:   main.cpp
 * Author: spadilla
 *
 * Created on October 25, 2018, 1:45 PM
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

int dice(int a) {
    int n = 0;
    for (int i = 0; i < a; i++) {
        n += rand() % 6 + 1;
    }
    return n;
}

int game(int a) {//initialize board
    int board[16];
    int length = (sizeof (board) / sizeof (*board));
    for (int i = 0; i < length; i++) {
        board[i] = 0;
    }
    int player = 0;
    for (int i = 0; i < 100000; i++) {
        int roll = dice(a);
        player += roll;
        if (player > length) {
            player = 0;
        } else if (player != 0) {
            board[player]++;
        }
    }
    cout << "|Start|";
    for (int i = 1; i < length; i++) {
        cout << board[i] << "|";
    }
    int first = board[0];
    int second = -1;
    int findex = 0;
    int sindex = 0;
    for (int i = 1; i < length; i++) {
        if (first < board[i]) {
            first = board[i];
            findex = i;
        }
    }
    for (int i = 1; i < length; i++) {
        if (findex == i) {
        } else if (second < board[i]) {
            second = board[i];
            sindex = i;
        }
    }
    cout << endl << "Great spot: " << findex << " | Good spot: " << sindex << endl << endl;
}

int main(int argc, char** argv) {
    srand(time(0));
    cout << "One Die" << endl;
    game(1); //1 die
    cout << "Two Dice" << endl;
    game(2); //2 dice
    return 0;
}

