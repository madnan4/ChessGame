#ifndef CHESSGAME_CHESSBOARD_H
#define CHESSGAME_CHESSBOARD_H


#pragma once
#include <iostream>
#include <string>
#include "square.h"

using namespace std;


class chessboard;
class ChessboardIterator;
class Chessboard {
private:
    Square board[8][8];
    bool kingHasMoved[2]{};
    bool rookHasMoved[2][2]{};
    bool validRookMove(int fromX, int fromY, int toX, int toY) const;
    bool validPawnMove(int fromX, int fromY, int toX, int toY);
    bool validKingMove(int fromX, int fromY, int toX, int toY);
    bool validBishopMove(int fromX, int fromY, int toX, int toY);
    bool validQueenMove(int fromX, int fromY, int toX, int toY);
    static bool validKnightMove(int fromX, int fromY, int toX, int toY);
    bool isValidMove(int fromX, int fromY, int toX, int toY);
    void performCastling(int fromX, int fromY, int toX, int toY);
    bool validMakeMove(int fromX, int fromY, int toX, int toY);
    bool isKingInCheck();
    bool isSquareUnderAttack(int x, int y);
    void updateKing(int X, int Y);
    static void resetEnPassant(int& enPassantX,int& enPassantY, bool& enPassantPossible);
    void checkPawnPromotion(int toX, int toY);
    void changePlayer();

public:
    friend class ChessboardIterator;
    bool check_mate = false;
    int enPassantX;
    int enPassantY;
    bool promotePawn = false;
    int whiteKingX{}, whiteKingY{};
    int blackKingX{}, blackKingY{};
    bool enPassantPossible;
    bool checkMate{};
    bool inCheck = false;
    Color currentPlayer;
    Color attackColor;

    Chessboard();
    bool isCheckmate();
    bool isStaleMate();
    void createBoard();
    void print();
    int place(int x, int y, Color c, Piece p);
    int get(int x, int y, Color &c, Piece &p);
    int move(int fromX, int fromY, int toX, int toY);
    void promotePawnFunc(int toX, int toY, string input);
    void getPlayer() const{if (currentPlayer == White){cout << "It is White piece's turn"<< endl;} else{cout << "It is Black piece's turn"<< endl;}};

    ChessboardIterator begin();
    ChessboardIterator end();
};

class ChessboardIterator {
private:
    int position; // a number in [0..64]
    Chessboard chessboard;

public:
    ChessboardIterator(Chessboard &board, int pos){
        chessboard = board;
        position = pos;
    }

    void xy(int &x, int &y) {
        y = position / 8;
        x = position % 8;
    }
    Square operator*()
    {
        int x, y;
        this -> xy(x, y);
        return chessboard.board[y][x];
    }
    ChessboardIterator &operator++() {
        if (position < 64) {
            ++position;
        }

        //        position++;
        return *this;
    }
    int operator!=(ChessboardIterator &a)
    {
        return this->position != a.position;
    }
};

#endif //CHESSGAME_CHESSBOARD_H