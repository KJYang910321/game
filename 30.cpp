#include<iostream>
#include<random>
using namespace std;

int points = 0;
int win = 0;

int handle_move(int player_move){
    int num = points - 1;

    //rational move
    if(num % 4 == 0 && win == 0){
        int move = rand() % 3 + 1;
        return move;
    }
    //irrational moves and Al wins
    else{
        if(win == 0){
            win = 1;
            int remain = (points - 1) % 4;
            int best = 4 - remain;
            return best;
        }
        else{
            int best = 4 - player_move;
            return best;
        }
    }
}

int main(){
    for(int i = 0; i < 20; i++){
        int my;
        cin >> my;
        points += my;
        cout << points << '\n';
        if (points >= 30){
            cout << "player_lose";
            break;
        }
        int reply = handle_move(my);
        points += reply;
        cout << points << '\n';
        if(points >= 30){
            cout << "player_win";
            break;
        }
    }
}