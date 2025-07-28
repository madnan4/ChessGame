#include <iostream>
#include <sstream>
#include <vector>
#include "chessboard.h"

using namespace std;
void create_Board(Chessboard& chessboard)
{
    chessboard.place(0, 0, White, Piece::Rook);
    chessboard.place(1, 0,White, Piece::Knight);
    chessboard.place(2, 0, Color::White, Piece::Bishop);
    chessboard.place(3, 0, Color::White, Piece::Queen);
    chessboard.place(4, 0, Color::White, Piece::King);
    chessboard.place(5, 0, Color::White, Piece::Bishop);
    chessboard.place(6, 0, Color::White, Piece::Knight);
    chessboard.place(7, 0, Color::White, Piece::Rook);
    for (int i = 0; i < 8; i++)
    {
        chessboard.place(i, 1,White, Pawn);
    }
    chessboard.place(0, 7, Black, Rook);
    chessboard.place(1, 7, Black, Knight);
    chessboard.place(2, 7, Black, Bishop);
    chessboard.place(3, 7, Black, Queen);
    chessboard.place(4, 7, Black, King);
    chessboard.place(5, 7, Black, Bishop);
    chessboard.place(6, 7, Black, Knight);
    chessboard.place(7, 7, Black, Rook);
    for (int i = 0; i < 8; i++) {
        chessboard.place(i, 6, Black, Pawn);
    }

    //check stalemate
    // chessboard.place(0, 6, Black, King);
    // chessboard.place(2, 5, White, Bishop);
    // chessboard.place(0, 0, Color::White, Piece::Rook);
    // chessboard.place(0, 4, Color::White, Piece::Pawn);
    // chessboard.place(2, 6, Color::Black, Piece::Pawn);
    // chessboard.place(7, 7, White, Rook);
    // chessboard.place(1, 0, White, Rook);
}
string promote() {
    while (true) {
        std::string input;
        std::cout << "You can promote the pawn. Please enter the first letter of the piece you would like to promote it to\nKnight, Rook, bishop, Queen. " << std::endl;
        std::cout << "K, R, B, Q, " << std::endl;
        std::cin >> input;

        // Ensure the input is a single character and convert to lowercase
        if (input.length() == 1) {
            input[0] = tolower(input[0]);
            if (input[0] == 'k' || input[0] == 'r' || input[0] == 'b' || input[0] == 'q')
                return input;
        } else {
            std::cout << "Invalid input! Please enter a single letter." << std::endl;
        }
    }
}

void play_game()
{
    bool checkMate = false;
    bool staleMate = false;
    Chessboard chessboard;
    create_Board(chessboard);
    chessboard.print();
    while(!checkMate && !staleMate)
    {
        chessboard.getPlayer();
        string command = "";
        cout << "Please enter the piece location and the intended location."
        << "\nfor example white pawn is at a, 2 to move it to a,4 please enter a,2,a,4" << endl;
        cin >> command;
        stringstream ss(command);
        string token;
        vector<int> tokens;
        int i = 1;
        while (std::getline(ss, token, ','))
        {
            if (i%2 == 0) {
                tokens.push_back(stoi(token));
            } else { tokens.push_back((int)(token[0]));}
            i++;
        }
        chessboard.move(tokens[0]-97, tokens[1]-1, tokens[2]-97, tokens[3]-1);
        if (chessboard.promotePawn) {
            string input = promote();
            chessboard.promotePawnFunc(tokens[2]-97, tokens[3]-1, input);
        }
        tokens.clear();
        checkMate = chessboard.isCheckmate();
        staleMate = chessboard.isStaleMate();
        chessboard.print();
    }
}

int main() {
    play_game();
    return 0;
}
