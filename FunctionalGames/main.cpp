/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: spadilla
 *
 * Created on January 13, 2019, 4:52 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

/*
 * 
 */
void potion(int& playerHP) {
    cout << "You gain 15HP!" << endl;
    playerHP += 15;
}

void nailBomb(int& monsterHP) {
    cout << "The Monster takes 10dmg!" << endl;
    monsterHP -= 10;
}

void bigShield() {
    cout << "You take no damage this turn!" << endl;
}

void giantSword(int& bonus) {
    cout << "You gain +2dmg on future attacks this round!" << endl;
    bonus += 2;
}

void info(string Name, int& playerHP, int& bonus) {
    cout << Name << " Has " << playerHP << " and will deal +" << bonus << " this turn." << endl;
}

void bag(int* inv, string* items) {
    cout << "Bag:" << endl;
    for (int i = 0; i < sizeof (items), i++) {
        cout << i + 1 << " [" << inv[i] << "]" << items[i] << endl;
    }
}

void generateMonster(int& monsterHP, int& goldDrop) {
    monsterHP = random(30, 50);
    goldDrop = random(5, 100);
}

void generateBoss(int& monsterHP, int& goldDrop) {
    monsterHP = random(100, 1000);
    goldDrop = random(1000, 10000);
}

void attack(int& a, int[] damage) {
    a -= random(damage[0], damage[1]);
}

void attack(int& a, int[] damage, int bonus) {
    int b random(damage[0], damage[1]) + bonus;
    a -= b;
    cout << "You did " << b << "damage!" << endl;
}

bool retreat() {
    return random(1, 100) < 70;
}

bool befriend(int& bf) {
    if (bf == -1) {
        cout << " You can't befriend a boss!"
        return false;
    } else {
        bf += random(1, 3);
        if (bf < 10) {
            cout << "You attempted to befriend the monster!" << endl;
        } else {
            cout << "You have befriended: " << monsterName << "!" << end;
            cout << monsterName << " gives you some gold and runs away." << endl;
            return true;
        }
    }
    return false;
}

int random(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main(int argc, char** argv) {
    srand(0);
    //Player
    int playerHP = 20;
    int bf = 0;
    int playerDamage = 6;
    string[] items = {"Potion", "Nail Bomb", "Bigger Shield", "Giant Sword"};
    int[] inv = {1, 1, 1, 1};
    int gold = 0;
    int armor = 0;
    int[] damage = {1, 6};
    int bonus = 0;
    string Name;
    //Monster
    int monsterHP, goldDrop;
    int[] monsterDamage = {1, 5};
    string monsterName = "Shitstain";
    char play;
    cout << "Welcome Player"
    do {
        int op;
        cout << "1 Fight Monster" << endl;
        cout << "2 General Merchant" << endl;
        cout << "3 Armor Shop" << endl;
        cin>> op;
        int count = 0;
        switch (op) {
            case 1:
                count++;
                if (count % 5 == 0 & count != 0) {
                    generateMonster();
                } else {
                    generateBoss();
                }
                bool quit = false;
                do {
                    bool atk = true;
                    info(Name, playerHP, bonus);
                    bag(inv, items);
                    cout << "Press Enter to Continue";
                    cin.ignore();
                    int op2;
                    cout << "1 Attack" << endl;
                    cout << "2 Befriend" << endl;
                    cout << "3 Flee" << endl;
                    cout << "4 Bag" << endl;
                    cin << op2;
                    switch (op2) {
                        case 1:
                            attack(monsterHP, damage, bonus);
                            break;
                        case 2:
                            if (befriend(bf)) {
                                quit = true;
                            }
                            break;
                        case 3:
                            if (retreat()) {
                                cout << "You point at a cloud, confusing the monster!" << end;
                                cout << "You are able to escape!" << endl;
                                quit = true;
                            } else {
                                cout << "Your escape plan failed."
                            }
                            break;
                        case 4:
                            int op3;
                            bag(inv, items);
                            do {
                                cin.clear();
                                cout << "Use which item?" << endl;
                                if (inv[op3] > 0) {
                                    inv[op3]--;
                                    break;
                                } else {
                                    cout << "You don't have any!" << endl;
                                }
                            } while (true);
                            cout << "You use: " << items[op3];
                            switch (op3) {
                                case 1:
                                    potion(playerHP);
                                    break;
                                case 2:
                                    nailBomb(monsterHP);
                                    break;
                                case 3:
                                    bigShield();
                                    atk = false;
                                    break;
                                case 4:
                                    giantSword(bonus);
                                    break;
                            }
                            break;
                    }
                    if (atk) {
                        cout << "The monster attacks you!" << endl;
                        attack(playerHP, monsterDamage)
                    }
                } while (monsterHP > 0 || !quit || playerHP <= 0);
                break;
            case 2:
                break;
            case 3:
                break;
        }
        if (playerHP <= 0) {
            cout << "You died.... Play again? (y,n)"
        } else {
            cout << "Return to town or quit game? (y,n)"
        }
    } while (play = 'y');
    return 0;
}
