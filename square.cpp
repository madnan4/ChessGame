//
// Created by Adnan Ali on 1/2/25.
//
// Implementation for Square

#include <iostream>
#include <string>
#include "square.h"

using namespace std;

Square::Square()
        : color(Color::Unknown), piece(Piece::UnknownPiece), occupied(false) {}
Square::Square(Color color, Piece piece)
        : color(color), piece(piece), occupied(true) {}


string Square::colorToString() { //get color of the piece for the name
    switch (color) {
        case Color::White: return "|w";
        case Color::Black: return "|b";
        default: return "U";
    }
}

string Square::pieceToString() {//get color of the piece for the name
    switch (piece) {
        case Piece::Rook: return colorToString()+"R|";
        case Piece::Knight: return colorToString()+"N|";
        case Piece::Bishop: return colorToString()+"B|";
        case Piece::Queen: return colorToString()+"Q|";
        case Piece::King: return colorToString()+"K|";
        case Piece::Pawn: return colorToString()+"P|";
        default: return "|__|";
    }
}
Color Square::getColor(){
    return color;
}

Piece Square::getPiece() {
    return piece;
}

bool Square::getOccupied() const {
    return occupied;
}

string Square::getName() {
    return pieceToString();
}