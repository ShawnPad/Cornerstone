/* 
 * File:   main.cpp
 * Author: spadilla
 *
 * Created on October 30, 2018, 5:25 PM
 */

#include <cstdlib>
#include <iostream>
using namespace std;
const char alpha[] = {"abcdefghijklmnopqrstuvwxyz"};
const char bigAlpha[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

char e(char a, int b) {
    int index = 0;
    bool big = false;
    for (int i = 0; i < 26; i++) {
        if (a == alpha[i]) {
            index = i;
            break;
        }
    }
    if (index == 0) {
        for (int i = 0; i < 26; i++) {
            if (a == bigAlpha[i]) {
                index = i;
                big = true;
                break;
            }
        }
    }
    if (a==' ') {
        return ' ';
    }
    index += b;
    index %= 26;
    if (big) {
        return bigAlpha[index];
    } else {
        return alpha[index];
    }
}

char d(char a, int b) {
    int index = 0;
    bool big = false;
    for (int i = 0; i < 26; i++) {
        if (a == alpha[i]) {
            index = i;
            break;
        }
    }
    if (index == 0) {
        for (int i = 0; i < 26; i++) {
            if (a == bigAlpha[i]) {
                index = i;
                big = true;
                break;
            }
        }
    }
    if (a == ' ') {
        return ' ';
    }
    index -= b;
    index %= 26;
    if (index < 0) {
        index += 26;
    }
    if (big) {
        return bigAlpha[index];
    } else {
        return alpha[index];
    }
}

int main(int argc, char** argv) {
    int key;
    do {
        cout << "Key:";
        cin>>key;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            continue;
        } else {
            break;
        }
    } while (true);
    srand(key);
    string type;
    do {
        cout << "Encrypt or Decrypt? (E,D) ";
        cin>>type;
    } while (type.compare("E") != 0 && type.compare("D") != 0 && type.compare("e") != 0 && type.compare("d") != 0);
    bool type2;
    if (type.compare("E") == 0 || type.compare("e") == 0) {
        type2 = true;
        cout << "Message to encrypt: ";
    } else {
        type2 = false;
        cout << "Message to decrypt: ";
    }
    string str;
    cin.ignore();
    getline(cin, str);
    int length = str.length();
    int code[length];
    for (int i = 0; i < length; i++) {
        code[i] = rand() % 10 + 1;
    }
    string str2;
    if (type2) {
        for (int i = 0; i < str.length(); i++) {
            str2 += e(str[i], code[i]);
        }
    } else {
        for (int i = 0; i < str.length(); i++) {
            str2 += d(str[i], code[i]);
        }
    }
    for (int i = 0; i < length; i++) {
        cout << code[i];
    }
    cout << endl;
    for (int i = 0; i < length; i++) {
        cout << str2[i];
    }
    return 0;
}

