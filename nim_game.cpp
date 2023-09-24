#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


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
            return 1;

        field[row] -= num;
        return 0;
    }

    int get_chip(int row) {
        return field[row];
    }
};

GameField game_field;

bool game_stop() {
    if (game_field.get_chip(0) + game_field.get_chip(1) + game_field.get_chip(2) == 0)
        return 1;
    return 0;
}

void show_game_state() {
    cout << "Number of row" << string(39, ' ') << "Chips" << endl;;
    for (int i = 1; i < 4; i++) {
        int c = game_field.get_chip(i - 1);
        cout << string(5, ' ') << i << string(18, ' ') << string(c, '*') << string(22 + 5 - c, ' ') << c << '\n';
    }
}


void show_start_screen() {
    cout << string(23, ' ') << "Game Nim" << '\n';
    cout << "You can take any num of chips from any row." << endl;;
    cout << string(5, ' ') << "Winner id the player who take last chip." << endl;;

    show_game_state();

    cout << "˜˜˜˜˜˜˜ ˜˜˜ ˜˜˜ ˜ ˜˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜ (˜˜˜˜˜˜˜˜,\n    2 3 - ˜˜˜˜˜ ˜˜ 2 p˜˜a 3 ˜˜˜˜˜\n    ˜˜˜ ˜˜˜˜˜˜˜ 0 0 ˜˜˜ ˜˜˜˜˜˜)" << endl;;
    cout << "˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜! ˜˜˜˜˜!\n" << endl;;

}

int user_turn() {
    //If user entered "0 0" then func return -1 and game breaks.
    //If user entered incorrect data then func return 1 and waiting for correct data
    //Else func returns 0
    cout << "˜˜˜ ˜˜˜: ";
    int row, num;

    //!

    cin >> row >> num;
    if (cin.fail()) {
        throw runtime_error("˜˜˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜! ˜˜˜˜˜˜˜˜ ˜˜˜˜ <row, num_of_chips>");
    }

    if (row == 0 && num == 0) return -1;

    return game_field.take_chips(row - 1, num);
}

string pull_time(int row) {
    game_field.take_chips(row, 1);
    return ("Computer move: " + char(row + 1 + 48)) + ' ' + '\n';
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
                return "Computer move: " + char(h + 1 + 48) + ' ' + char(c + 48) + '\n';
            }
            d[h] = 0;
        }
    }
}

int main() {
    system("chcp 1251");

    show_start_screen();

    while (1) {
        int user_moved = 0;
        while (!user_moved) {
            switch (user_turn()) {
            case -1:
                cout << "Game break!" << endl;;
                return 0;
                break;
            case 1:
                cout << "Incorrect move!" << endl;;
                break;
            case 0:
                user_moved = 1;
                break;
            }
        }

        if (game_stop()) {
            cout << "Game over! User win's!" << endl;;
            break;
        }

        string ct = comp_turn();


        if (game_stop()) {
            cout << "Game over! Super-advanced artificial intelligence win's!" << endl;;
            break;
        }
        
        
        cout << ct << '\n';
        show_game_state();
    }
}