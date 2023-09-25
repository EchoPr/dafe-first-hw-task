#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <ctime>

using namespace std;

#define OK 100
#define NOT_OK 101
#define ERROR 102
#define END_GAME 103


struct GameField {
    vector<int> field;
    int chips_amount;

    GameField() {
        field.assign(3, 0);
        field[0] = 3;
        field[1] = 4;
        field[2] = 5;

        chips_amount = 12;
    }

    int take_chips(int row, int num) {
        if (row < 0 || row > 2 || field[row] < num)
            return NOT_OK;

        field[row] -= num;
        chips_amount -= num;
        return OK;
    }

    int get_chip(int row) {
        return field[row];
    }
};

GameField game_field;

bool game_stop() {
    return game_field.chips_amount == 0;
}

void show_game_state() {
    cout << "Number of row" << string(39, ' ') << "Chips" << endl;
    for (int i = 1; i < 4; i++) {
        int c = game_field.get_chip(i - 1);
        cout << string(5, ' ') << i << string(21, ' ') << string(c, '*') << string(22 + 5 - c, ' ') << c << '\n';
    }
}


void show_start_screen() {
    cout << string(23, ' ') << "Game Nim" << endl;
    cout << "You can take any num of chips from any row." << endl;
    cout << string(5, ' ') << "Winner id the player who take last chip." << endl;

    show_game_state();

    cout << "In your stroke enter your turn in format <ROW, CHIPS> (For example,\n    2 3 - Take 3 chips from 2 row\n    Or enter 0 0 for exit)" << endl;
    cout << "There are 3 start conditions (First turn by: 1 - user; 2 - computer; 3 - take it random)\0" << endl;
    
}

int user_turn() {
    //If user entered "0 0" then func return -1 and game breaks.
    //If user entered incorrect data then func return 1 and waiting for correct data
    //Else func returns 0
    cout << "Your turn: \0";
    int row, num;

    cin >> row >> num;
    if (cin.fail()) {
        throw runtime_error("Invalide input data! Expected turn <row, num_of_chips>");
    }

    if (row == 0 && num == 0) return END_GAME;

    return game_field.take_chips(row - 1, num);
}

int user_handler(){
    int user_moved = 0;
        while (!user_moved) {
            switch (user_turn()) {
            case END_GAME:
                cout << "Game break!" << endl;
                return END_GAME;
                break;
            case NOT_OK:
                cout << "Incorrect move!" << endl;
                break;
            case OK:
                user_moved = 1;
                break;
            }
        }
    return OK;
}

string pull_time(int row) {
    game_field.take_chips(row, 1);
    return ("Computer move: " + char(row + 49)) + ' ' + '\n' + '\0';
}

int xor_heaps(vector<int> d) {
    int f = game_field.get_chip(0) - d[0];
    int s = game_field.get_chip(1) - d[1];
    int t = game_field.get_chip(2) - d[2];

    return f ^ s ^ t;
}


string comp_turn() {
    
    if (xor_heaps(vector<int>{0, 0, 0}) == 0) {
        if (game_field.get_chip(0) > 0) return pull_time(0);
        else if (game_field.get_chip(1) > 0) return pull_time(1);
        else return pull_time(2);
    }

    vector<int> d(3);
    for (int h = 0; h < 3; h++) {
        for (int c = 1; c <= game_field.get_chip(h); c++) {
            d[h] = c;
            if (xor_heaps(d) == 0) {
                game_field.take_chips(h, c);
                return "Computer move: " + to_string(h + 1) + " " + to_string(c) + '\n' + '\0';
            }
            d[h] = 0;
        }
    }
}

int choose_player(){
    cout << "Choose your stroke: \0";
    int st;

    while (1){
        cin >> st;
        if (st < 1 || st > 3){
            cout << "Incorrect type. Try again\nChoose your stroke: \0" << endl;
            continue;
        }
        if (st == 3){
            srand(time(0));
            return rand() % 2 + 1;
        }

        return st;    
    }
}

int main() {
    show_start_screen();

    int user_stroke = choose_player(); // 1 - first; 2 - second;
    int stroke = 0;


    while (1) {
        if (stroke % 2 + 1 == user_stroke){
            if (user_handler() == END_GAME){
                cout << "Game was ended premature" << endl;
                break;
            }
            show_game_state();
        }
        else{
            string ct = comp_turn();
            cout << ct << endl;
            show_game_state();
        }

        if (game_stop()){
            cout << "Game over! " << (
                stroke % 2 + 1 == user_stroke ? 
                "User win's!\0" : 
                "Super-advanced artificial intelligence win's!\0"
            ) << endl;

            break;
        }
        
        

        stroke++;
    }

}