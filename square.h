//
// Created by Adnan Ali on 1/2/25.
//

#ifndef SQUARE_H
#define SQUARE_H

#pragma once
#include <iostream>
#include <string>


using namespace std;

enum Color {
    White, Black, Unknown
};

enum Piece
{
    Rook, Knight, Bishop, King, Queen, Pawn , UnknownPiece
};



class Square {
private:
    Color color;
    Piece piece;
    bool occupied;

    string colorToString();
    string pieceToString();

public:
    Square(Color color, Piece piece);
    Square();
    Color getColor();
    Piece getPiece();
    bool getOccupied() const;
    string getName();
};
#endif //SQUARE_H
