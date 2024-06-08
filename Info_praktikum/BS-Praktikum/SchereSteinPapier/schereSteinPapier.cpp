#include <iostream>
#include <vector>
#include <thread>
#include <semaphore>
#include <chrono>
#include <random>

using namespace std;

enum Ergebnis {
    Schere,
    Stein,
    Papier,
};

counting_semaphore<1> semP1(1);
counting_semaphore<1> semP2(1);
counting_semaphore<1> semR(0);



// ##########################################
// global variables
// ##########################################

int gameCount = 0;

int res1;
int res2;

int player1Count = 0;
int player2Count = 0;


// ##########################################
// Functions
// ##########################################

void player(int id);
void referee();
string resultString(int a);

void player(int id) 
{   
    random_device rd;                          
    mt19937 gen(rd());    
    uniform_int_distribution<> dis(0, 2);        // random number gnerator between 0 and 2
    while(gameCount < 50 && player1Count < 3 && player2Count < 3) {
        int res = dis(gen); 
        if(id==1) {
            semP1.acquire();
        } else {
            semP2.acquire();
        }

        if(id==1) {
            res1 = static_cast<Ergebnis>(res);
        } else {
            res2 = static_cast<Ergebnis>(res);
        }
        semR.release();
    }
}

void referee() 
{   
    semR.acquire();
    while(gameCount < 50 && player1Count < 3 && player2Count < 3) {
        if(res1 == res2) {}                                         // do nothing if equal
            else if(res1 == 0 && res2 == 2){                        // schere vs papier 
                player1Count++;
            } else if(res1 == 1 && res2 == 0) {                     // stein vs schere
                player1Count++;
            } else if(res1 == 2 && res2 == 1) {                     // papier vs stein
                player1Count++;
            } else {                                                // in every other case: player2 wins
                player2Count++;
            }
        gameCount++; 
        cout << resultString(res1) << " vs " << resultString(res2) << " | (" << player1Count << " : " << player2Count << ")" << endl;
        
        semP1.release();
        semP2.release();
    }
    if(player1Count >= 3) {
            cout << endl << "Player1 wins!" << endl << endl;
        } else if (player2Count >= 3) {
            cout << endl << "Player2 wins!" << endl << endl;
    }
}

string resultString(int a) {
    Ergebnis result = static_cast<Ergebnis>(a);

    switch (result) {
        case Schere:
            return "Schere";
            break;
        case Stein:
            return "Stein";
            break;
        case Papier:
            return "Papier";
            break;
        default:
            return "invalid";
            break;
    }
}

// ##########################################
// MAIN
// ##########################################

int main() 
{
    cout << endl << "Player1" << " vs " << "Player2" << " | (" << 0 << " : " << 0 << ")" << endl << "------------------------" << endl;
    thread player1 = thread(player, 1); 
    thread player2 = thread(player, 2); 
    thread refereeT = thread(referee);

    player1.join();
    player2.join();
    refereeT.join();

    return 0;
}