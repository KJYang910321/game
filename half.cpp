#include<iostream>
#include<random>
using namespace std;

int rounds = 0;
int last = 0;

int normal_AI(int round){
    if(round == 0){
        return 25;
    }
    else{
        int choice = (25 + last)/2;
        return choice;
    }
}

int smart_AI(int round){
    if(round == 0){
        return 12;
    }
    else{
        int miss = rand() % 4;
        int choice = (12 + last + miss)/2;
        return choice;
    }
}

int random_AI(int round){
    if (rand() % 2 == 0){
        int choice = rand() % 51;
        return choice;
    }
    else{
        int choice = (25 + last)/2;
        return choice;
    }
}

int score_board[5] = {0};

int main(){
    while(1){
        int score[5] = {0};
        score[0] = normal_AI(rounds);
        score[1] = smart_AI(rounds);
        score[2] = random_AI(rounds);
        score[3] = 0;
        cin >> score[4];
        
        int sum = 0;
        for(int i = 0; i < 5; i++){
            sum += score[i];
        }
        int aver = sum / 5;
        int mini = 100;
        int win = -1;
        for(int i = 0; i < 5; i++){
            cout << "p" << i << "choice" << score[i] <<'\n';
            score[i] -= aver;
            if(score[i] < 0){
                score[i] = -score[i];
            }
            if(score[i] <= mini){
                mini = score[i];
                win = i;
            }
        }

        score_board[win] ++;
        if(score_board[win] >= 5){
            cout << "champion is " << win;
            break;
        }

        cout << "round "<< rounds << "average is " << aver << '\n';
        if(win != 4){
            cout << "AI " << win << "wins" << '\n'; 
        }
        else{
            cout << "player wins" << '\n';
        }
        rounds ++;
        last = aver;
    }
}