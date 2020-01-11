

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

//Helper functions Main function at bottom
int random(int min, int max) {
    return rand() % (max - min + 1) + min; //create random number from min to max
}

void potion(int& playerHP) {
    cout << "You gain 15HP!" << endl;
    playerHP += 15; //increase player hp +15
}

void nailBomb(int& monsterHP) {
    cout << "The Monster takes 10dmg!" << endl;
    monsterHP -= 10; //decrease monster hp -10
}

void bigShield() {
    cout << "You take no damage this turn!" << endl;
}

void giantSword(int& bonus) {
    cout << "You gain +2dmg on future attacks this round!" << endl;
    bonus += 2; // increase bonus damage by +2
}

void info(string Name, int& playerHP, int& bonus) { //UI give player info for next turn
    cout << Name << " has " << playerHP << "HP and will deal +" << bonus << " bonus damage this turn." << endl;
}

void bag(int* inv, string* items) {
    cout << "Bag:" << endl; //show items and amount 
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << " [" << inv[i] << "]" << items[i] << endl;
    }
}

void generateMonster(int& monsterHP, int& goldDrop) { //give monster random health and gold drop
    monsterHP = random(30, 50);
    goldDrop = random(5, 100);
}

void generateBoss(int& monsterHP, int& goldDrop) { //give boss random health and gold drop
    monsterHP = random(100, 1000);
    goldDrop = random(1000, 10000);
}

void attack(int& a, int* damage) {
    a -= random(damage[0], damage[1]); //attack random damage within range
}

void attack(int& a, int* damage, int bonus) {
    int b = random(damage[0], damage[1]) + bonus; //attack random damage within range +bonus damage
    a -= b;
    cout << "You did " << b << " damage!" << endl;
}

bool retreat() {
    return random(1, 100) < 70; //returns true 70% of the time
}

bool befriend(int& bf, string monsterName) {
    if (bf == -1) {
        cout << " You can't befriend a boss!"; 
        return false;
    } else {
        bf += random(1, 3); //add 1-3 to friendship value
        if (bf < 10) { //if friendship value  is greater than or equal to 10 you befriend monster
            cout << "You attempted to befriend " << monsterName << "!" << endl;
        } else {
            cout << "You have befriended: " << monsterName << "!" << endl;
            cout << monsterName << " gives you some gold and runs away." << endl;
            return true;
        }
    }
    return false;
}

void clear() {
    cout << endl << endl << endl << endl << endl << endl; //ui cleaning
}

//
//
// Main function
//
//
int main(int argc, char** argv) {
    srand(time(0));
    //Player
    int playerHP = 20;
    int bf = 0;
    int playerDamage = 6;
    string items[] = {"Potion", "Nail Bomb", "Bigger Shield", "Giant Sword"};
    int inv[] = {1, 1, 1, 1}; //# items in inventory
    int gold = 0;
    int armor = 0;
    int damage[] = {1, 100};
    int bonus = 0;
    string Name;
    //Monster
    int monsterHP, goldDrop;
    int monsterDamage[] = {1, 5};
    string monsterName = "";
    string monsternames[] = {"Jeremy The Gremlin", "Vlad The Vamp", "Sam The Slime", "Dave The Devil", "Paul The Poltergeist"};
    char play;
    cout << "Welcome Player to an Adventure where you kill the same monster and boss." << endl;
    cout << "All so you can upgrade your character to kill them more times!" << endl;
    cout << "What is your name?" << endl;
    getline(cin, Name); //get player name
    do {
        int op;
        cout << "1 Fight Monster" << endl;
        cout << "2 General Merchant" << endl;
        cout << "3 Armor Shop" << endl;
        cin>> op;
        int count = 0;
        bool quit = false;
        switch (op) {
            case 1: //attack case 
                count++;//generate a monster or boss
                monsterName = monsternames[random(0, 4)];
                if (count % 5 == 0 && count != 0) {
                    generateBoss(monsterHP, goldDrop);
                    cout << "You encounter " << monsterName << " a boss monster!" << endl;
                } else {
                    generateMonster(monsterHP, goldDrop);
                    cout << "You encounter " << monsterName << " a low level monster!" << endl;
                }
                //option loop ie attack befriend flee or use item
                do {
                    bool atk = true;
                    info(Name, playerHP, bonus);
                    bag(inv, items);
                    cout << "Press Enter to Continue" << endl;
                    cin.ignore();
                    getchar();
                    clear();
                    int op2;
                    cout << "1 Attack" << endl;
                    cout << "2 Befriend" << endl;
                    cout << "3 Flee" << endl;
                    cout << "4 Bag" << endl;
                    cin >> op2;
                    clear();
                    switch (op2) {
                        case 1: //attack case
                            attack(monsterHP, damage, bonus); 
                            if(monsterHP<=0){
                                atk = false; //if monster dead do not attack again
                                cout<<"You killed "<< monsterName<<" "<<goldDrop<<"g dropped!"<<endl;
                                gold+=goldDrop;
                            }
                            break;
                        case 2: //befriend case
                            if (befriend(bf, monsterName)) {
                                quit = true; //leave option loop
                                atk = false; //if monster friend do not attack
                            }
                            break;
                        case 3: //flee case
                            if (retreat()) {
                                cout << "You point at a cloud, confusing " << monsterName << "!" << endl;
                                cout << "You are able to escape!" << endl;
                                atk = false; //if successful retreat do not attack
                                quit = true; //leave option loop
                            } else {
                                cout << "Your escape plan failed." << endl;
                                //you don't escape and monster attacks
                            }
                            break;
                        case 4: // item case
                            int op3;
                            bag(inv, items);
                            do { //loop to check valid user input
                                cin.clear();
                                cout << "Use which item?" << endl;
                                cin>>op3;
                                if (inv[op3] > 0) {
                                    inv[op3-1]--; //remove item from inventory
                                    break;
                                } else {
                                    cout << "You don't have any!" << endl;
                                }
                            } while (true);
                            cout << "You use: " << items[op3 - 1] << endl;
                            //use item
                            switch (op3) {
                                case 1:
                                    potion(playerHP);
                                    break;
                                case 2:
                                    nailBomb(monsterHP);
                                    break;
                                case 3:
                                    bigShield();
                                    atk = false; //stops next monster attack
                                    break;
                                case 4:
                                    giantSword(bonus);
                                    break;
                            }
                            break;
                    }
                    if (atk) {
                        cout << monsterName<<" attacks you!" << endl;
                        attack(playerHP, monsterDamage); //monster attacks player
                    }
                } while (monsterHP > 0 && !quit && playerHP > 0);
                break;
            case 2: //general store
                cout << "Welcome to the General Store! What would you like to buy traveler?" << endl;
                cout << "Gold: " << gold << endl;
                cout << "Potion 10g | Nail Bomb 50g | Bigger Shield 100g | Giant Sword 500g" << endl;
                bag(inv, items);
                int ch1;
                cin >> ch1;
                //checks which option chosen, if player has enough gold and gives item to player
                if (ch1 == 1 && gold > 10) {
                    inv[0]++;
                } else
                    if (ch1 == 2 && gold > 50) {
                    inv[1]++;
                } else
                    if (ch1 == 3 && gold > 100) {
                    inv[2]++;
                } else
                    if (ch1 == 4 && gold > 500) {
                    inv[3]++;
                } else
                    if (ch1 == 1 && gold > 10) {
                    inv[0]++;
                } else {
                    cout << "You poor!" << endl;
                }
                break;
            case 3: //Power up shop
                cout << "Welcome traveler. We sell the finest weapons and armor!" << endl;
                cout << "Gold: " << gold << endl;
                cout << "1 The Append Sword(500g) +2 Bonus damage" << endl;
                cout << "2 The Append Armor(1000g) -1 Monster Damage" << endl;
                int ch2;
                cin>>ch2;
                //checks which option chosen, if player has enough gold and gives player powerup
                if (ch2 == 1 && gold > 500) {
                    gold -= 500;
                    bonus += 2;
                } else
                    if (ch2 == 2 && gold > 1000) {
                    gold -= 1000;
                    monsterDamage[0]--;
                    monsterDamage[1]--;
                } else {
                    cout << "You poor!" << endl;
                }
                break;
        }
        if (playerHP <= 0) { // if player hp 0 or lower player has died
            cout << "You died.... Play again? (y,n)" << endl;
        } else {
            cout << "Return to town or quit game? (y,n)" << endl;
        }
        cin>>play;
    } while (play == 'y'); // check if player wants to play again
    return 0;
}