#include<iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;

int back[7] = {21,13,8,5,3,2,1};
int numnum = 30;
int legal = 29;

int min_fb(){
    int index = -1;
    int remain = numnum;
    for(int i = 0; i < 7; i++){
        if(remain >= back[i]){
            remain -= back[i];
            index = i;
        }
    }
    int key = back[index];
    return key;
}

int is_ideal(int player){
    int key = min_fb();
    if (key == player){
        return 1;
    }
    else{
        return 0;
    }
}

int is_fb(){
    for(int i = 0; i < 7; i++){
        if(numnum == back[i]){
            return 1;
        }
    }
    return 0;
}

int random_legal(){
    srand(time(NULL));
    int x = rand();
    if(x < 0){
        x = -x;
    }
    int magic = (x % legal) + 1;
    if(magic > 5){
        magic %= 5;
        
        if(magic == 0)
        	magic = x % 5 + 1;
    }
    return magic;
}

int init(){
	numnum = 30;
	legal = 29;
}

int AI_move(int player){
	if (player > legal){
		cout << "illegal move, try again\n";
		return -1;
	}
    int good = is_ideal(player);
    legal = 2 * player;
    numnum -= player;

    int best = -1;
    if(numnum <= legal){
        best = numnum;
    }
    else{
        if(good || is_fb()){
            best = random_legal();
            cout << "hi\n";
            cout << legal << '\n';
        }
        else{
            best = min_fb();
        }
    }
    legal = 2 * best;
    numnum -= best;
    return best;
}
