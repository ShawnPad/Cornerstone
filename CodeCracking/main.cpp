/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: spadilla
 *
 * Created on January 24, 2019, 1:05 PM
 */

#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

/*
 * 
 */
void checkloc(int g[], int code[], int& r, int& w, int length) {
    bool check[length]; //create bool array
    for (int i = 0; i < length; i++) {
        check[i] = false; //fill bool array with false
    }
    for (int i = 0; i < length; i++) {
        if (g[i] == code[i]) {// correct position 
            check[i] = true; //stop double counting if correct
            r++; //iterate number correct
        }
    }
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (check[i]) {//stop double counting
                break;
            }
            if (code[j] == g[i] && code[j] != g[j]) {//count incorrect pos
                check[i] = true;
                w++; //iterate number incorrect pos
                break; //stop double counting
            }
        }
    }
}

int main(int argc, char** argv) {
    char play;
    do {
        srand(24); //Seed random number
        int dif[] = {4, 5, 6}; //Number of digits per difficulty
        char d;
        int l;
        cout << "Difficulty level? (e,m,h)" << endl; //Ask user difficulty level
        cin>>d;
        switch (d) { //Set number of digits
            case 'e': l = dif[0];
                break;
            case 'm': l = dif[1];
                break;
            case 'h': l = dif[2];
                break;
            default: l = dif[2]; //Invalid input default hard mode lol
                cin.clear();
                cin.ignore();
        }
        int code[l];
        for (int i = 0; i < l; i++) {
            code[i] = rand() % 10; //Create random code each digit 0-9
        }
        //int code[] = {9, 3, 0, 0}; //to test given condition
        const int length = sizeof (code) / sizeof (code[0]); //get array length
        int g[length]; //player guess array
        bool win = false;
        int chances = 12; //number of chances player gets
        int sum = 0;
        for (int i = 0; i < length; i++) {
            sum += code[i]; //sum code
        }
        cout << "Sum of code: " << sum << endl; //give user hints
        cout << "Number of digits: " << length << endl;
        for (int i = chances; i > 0; i--) {//guess loop
            int w = 0; //wrong location
            int r = 0; //right location
            cout << "You have " << i << " guesses left!" << endl;
            cout << "Guess " << chances - i + 1 << ":";
            int temp = 0;
            cin >> temp;
            if (cin.fail()) {//Check if valid input
                cout << "Error!" << endl;
                cin.clear();
                cin.ignore();
                continue;
            }
            for (int i = 0; i < length; i++) {//Separate user answer into array
                if (i == 0) {//ie 9300 -> 9,3,0,0
                    g[length - i - 1] = temp % 10; //divide by zero condition
                } else {
                    g[length - i - 1] = temp / (int) pow(10, i) % 10;
                }
            }
            for (int i = 0; i < length; i++) {
                cout << g[i]; //tell user parsed guess
            }
            cout << endl;
            checkloc(g, code, r, w, length); //check logic
            cout << "Right #’s: Right Loc. – " << r << ", Wrong Loc. – " << w << endl;
            if (r == length) { //win condition
                cout << "You cracked the safe! You win!" << endl;
                win = true;
                break;
            }
        }
        if (!win) { //loss condition
            cout << "You failed to crack the safe..." << endl;
            cout << "The code was: " << endl;
            for (int i = 0; i < length; i++) {
                cout << code[i];
            }
        }
        cout << endl << "Play again? (y,n)" << endl; //play again condition
        cin>>play;
    } while (play == 'y');
    return 0;
}


