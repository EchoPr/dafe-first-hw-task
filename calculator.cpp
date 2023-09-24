#include <iostream>
#include <vector>

using namespace std;


class Token{
public:
    char type;
    double val;

    Token(){};
    Token(char t):type(t){};
    Token(int v):type('0'), val(v){};
};

Token get_token();


int main(){
    vector<Token> tokens;

    while (cin){
        tokens.push_back(get_token());
    }
}