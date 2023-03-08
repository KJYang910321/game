#include<iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;

// index of item / type of judge / type of auction
int arts[5][4][4];
int jewel[5][4][4];
int special[5][4][4];

int goals[3][5];
int auction_score;


int jumping(){
    srand(time(NULL));
    int plus = rand();
    plus %= 20;
    return plus;
}

double second(double first){
    srand(time(NULL));
    int x = rand();
    int index = x % 3;
    double weight[3] = {0.8, 1, 1.2};
    double value = (double)first * weight[index];
    return value; 
}

void create_art(int number, int price, double judge[4], double auction[4]){
    for(int j = 0; j < 4; j++){
        for(int a = 0; a < 4; a++){
            arts[number][j][a] = price * judge[j] * auction[a];
        }
    }
}

void create_jewel(int number, int price, double judge[4], double auction[4]){
    for(int j = 0; j < 4; j++){
        for(int a = 0; a < 4; a++){
            jewel[number][j][a] = price * judge[j] * auction[a];
        }
    }
}

void create_special(int number, int price, double judge[4], double auction[4]){
    for(int j = 0; j < 4; j++){
        for(int a = 0; a < 4; a++){
            special[number][j][a] = price * judge[j] * auction[a];
        }
    }
}

void show_price(int list[5][4][4]){
    for(int i = 0; i < 5; i++){
        cout << "number " << i << " : " << '\n';
        for(int j = 0; j < 4; j++){
            cout << "judge type " << j+1 << " : ";
            for(int a = 0; a < 4; a++){
                cout << list[i][j][a] << ", ";
            }
            cout << '\n';
        }
        cout << '\n';
    }
}

void build_up(){

	auction_score = 0;
    //set up database
    //arts one goal = 10000
    int art_one = 10000;
    double art_one_judge[4] = {1, 0.8, 0.6, 0.5};
    double art_one_auction[4] = {1, 0.5, 0.8, 0.8};
    art_one_auction[3] = second(0.8);
    create_art(0, art_one, art_one_judge, art_one_auction);
    goals[0][0] = 10000;

    //arts two goal = 6000
    int art_two = 6000;
    double art_two_judge[4] = {1.2, 1, 0.6, 0.5};
    double art_two_auction[4] = {1, 0.5, 1, 1};
    art_two_auction[3] = second(1);
    create_art(1, art_two, art_two_judge, art_two_auction);
    goals[0][1] = 6000;

    //arts three goal = 2000
    int art_three = 2000;
    double art_three_judge[4] = {0.1, 0.5, 1, 1};
    double art_three_auction[4] = {0.8, 0.5, 1, 1};
    art_three_auction[3] = second(1);
    create_art(2, art_three, art_three_judge, art_three_auction);
    goals[0][2] = 2000;

    //arts four goal = 1500
    int art_four = 1500;
    double art_four_judge[4] = {0.1, 0.5, 1, 0.8};
    double art_four_auction[4] = {0.8, 0.5, 1, 1};
    art_four_auction[3] = second(1);
    create_art(3, art_four, art_four_judge, art_four_auction);
    goals[0][3] = 1500;

    //arts five goal = 800
    int art_five = 800;
    double art_five_judge[4] = {0.1, 0.5, 1, 1};
    double art_five_auction[4] = {0.8, 0.5, 0.9, 0.9};
    art_five_auction[3] = second(0.9);
    create_art(4, art_five, art_five_judge, art_five_auction);
    goals[0][4] = 800;

    //jewel one goal = 3500
    int jewel_one = 3500;
    double jewel_one_judge[4] = {1, 1, 0.7, 0.5};
    double jewel_one_auction[4] = {1, 0.5, 1, 1};
    jewel_one_auction[3] = second(1);
    create_jewel(0, jewel_one, jewel_one_judge, jewel_one_auction);
    goals[1][0] = 3500;

    //jewel two goal = 2500
    int jewel_two = 2500;
    double jewel_two_judge[4] = {1.2, 1.1, 1, 0.8};
    double jewel_two_auction[4] = {1.1, 0.5, 1, 1};
    jewel_two_auction[3] = second(1);
    create_jewel(1, jewel_two, jewel_two_judge, jewel_two_auction);
    goals[1][1] = 2500;

    //jewel three goal = 4000
    int jewel_three = 4000;
    double jewel_three_judge[4] = {1, 1, 1, 1};
    double jewel_three_auction[4] = {1.1, 1.2, 0.8, 0.8};
    jewel_three_auction[3] = second(0.8);
    create_jewel(2, jewel_three, jewel_three_judge, jewel_three_auction);
    goals[1][2] = 4000;

    //jewel four goal = 500
    int jewel_four = 500;
    double jewel_four_judge[4] = {1, 1, 1, 1};
    double jewel_four_auction[4] = {0.7, 1.2, 0.7, 0.7};
    jewel_four_auction[3] = second(0.7);
    create_jewel(3, jewel_four, jewel_four_judge, jewel_four_auction);
    goals[1][3] = 500;

    //jewel five goal = 1000
    int jewel_five = 1000;
    double jewel_five_judge[4] = {1, 1, 1, 1};
    double jewel_five_auction[4] = {0.7, 1.2, 0.7, 0.7};
    jewel_five_auction[3] = second(0.7);
    create_jewel(4, jewel_five, jewel_five_judge, jewel_five_auction);
    goals[1][4] = 1000;
    //show_price(jewel);

    //special one goal = 1000
    int special_one = 1000;
    double special_one_judge[4] = {0.7, 0.7, 1, 0.5};
    double special_one_auction[4] = {0.5, 1, 0.5, 0.5};
    special_one_auction[3] = second(0.5);
    create_special(0, special_one, special_one_judge, special_one_auction);
    goals[2][0] = 1000;

    //special two goal = 5000
    int special_two = 5000;
    double special_two_judge[4] = {1.3, 1.2, 1.1, 0.6};
    double special_two_auction[4] = {1, 0.6, 1, 1};
    special_two_auction[3] = second(1);
    create_special(1, special_two, special_two_judge, special_two_auction);
    goals[2][1] = 5000;

    //special three goal = 8000
    int special_three = 8000;
    double special_three_judge[4] = {1, 1, 1, 1};
    double special_three_auction[4] = {1, 0.6, 1, 1};
    special_three_auction[3] = second(1);
    create_special(2, special_three, special_three_judge, special_three_auction);
    goals[2][2] = 8000;

    //special four goal = 8000
    int special_four = 7700;
    double special_four_judge[4] = {0.9, 0.9, 1.2, 0.9};
    double special_four_auction[4] = {0.6, 1, 0.6, 0.6};
    special_four_auction[3] = second(0.6);
    create_special(3, special_four, special_four_judge, special_four_auction);
    goals[2][3] = 7700;

    //special five goal = 9999
    int special_five = 9999;
    double special_five_judge[4] = {1, 1, 1, 1};
    double special_five_auction[4] = {1, 1, 1, 1};
    special_five_auction[3] = second(0.6);
    create_special(4, special_five, special_five_judge, special_five_auction);
    goals[2][4] = 9999;

    // cout << "arts pricing\n";
    // show_price(arts);
    // cout << "\n\n";

    // cout << "jewel pricing\n";
    // show_price(jewel);
    // cout << "\n\n";

    // cout << "special pricing\n";
    // show_price(special);
}
