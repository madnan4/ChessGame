
#include "chessboard.h"
#include <iostream>
#include <string>
#include <cmath>

// Implementation for Square
Square::Square()
        : color(Color::Unknown), piece(Piece::UnknownPiece), occupied(false) {}
Square::Square(Color color, Piece piece)
        : color(color), piece(piece), occupied(true) {}
string Square::colorToString() {
    switch (color) {
        case Color::White: return "|w";
        case Color::Black: return "|b";
        default: return "U";
    }
}

string Square::pieceToString() {
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
Chessboard::Chessboard() {
    currentPlayer = Color::White;
    attackColor = Color::Black;
    createBoard();
    kingHasMoved[0] = kingHasMoved[1] = false; // Both kings haven't moved
    rookHasMoved[0][0] = rookHasMoved[0][1] = false; // White rooks
    rookHasMoved[1][0] = rookHasMoved[1][1] = false; // Black rooks
    enPassantX = -1;
    enPassantY = -1;
    enPassantPossible = false;
//    print();
}
void Chessboard::createBoard() {
    for(auto & i : board) {
        for(auto & j : i) {
            Square piece = Square();
            j = piece;
        }
    }
}

void Chessboard::print() {
    ChessboardIterator it_end = this->end();
    ChessboardIterator it_begin = this->begin();
    string toPrint = "    a    b    c    d    e    f    g    h\n";
    string add;
    int i = 0;
    int k = 1;

    for (ChessboardIterator it = it_begin; it != it_end; ++it) {
        if (!add.empty()) {
            add += " ";
        }
        add += (*it).getName();
        i++;
        if (i % 8 == 0)
        {
            if (!toPrint.empty()) // if toPrint is not empty, prepend a newline character to it
            {
                if (toPrint != " ") {
                    toPrint = " \n" + toPrint;
                }
//                toPrint = "\n" + toPrint;
            }

            toPrint = to_string(k) + " "+ add + toPrint;
            k++;
            add = ""; // clear add string after adding it to toPrint
            i = 0; // reset the counter
        }
    }
    toPrint = "    a    b    c    d    e    f    g    h\n" + toPrint;
    cout << toPrint<<endl;
}
int Chessboard::place(int x, int y, Color c, Piece p)
{
    //valid x values
    if(x<0 || x>7)
    {
        return -1;
    }
    //valid y values
    else if(y < 0 || y > 7)
    {
        return -2;
    }
    //if square occupied or not
    else if(board[y][x].getOccupied())
    {
        return -3;
    }
    //valid color values
    else if(c != Color::White && c != Color::Black)
    {
        return -4;
    }
    //valid piece values
    else if(p != Piece::Bishop && p != Piece::King&& p != Piece::Knight&& p != Piece::Rook&& p != Piece::Queen&& p != Piece::Pawn)
    {
        return -5;
    }
    else
    {
        //if everything is okay place the piece
        Square piece = Square(c, p);

        board[y][x] = piece;
        if(board[y][x].getPiece() == Piece::King &&board[y][x].getColor() == Color::White) {
            if (x!=whiteKingX || y!=whiteKingY) {
                kingHasMoved[0] = true;
                whiteKingX = x;
                whiteKingY = y;
            }
        }
        if(board[y][x].getPiece() == Piece::King &&board[y][x].getColor() == Color::Black) {
            if (x!=blackKingX || y!=blackKingY) {
                kingHasMoved[1] = true;
                blackKingX = x;
                blackKingY = y;
            }
        }
        return 1;
    }

}
int Chessboard::get(int x, int y, Color &c, Piece &p)
{
    if(x<0 || x>7)//valid x values
    {
        return -1;
    }
    else if(y < 0 || y > 7)//valid y values
    {
        return -2;
    }
    else if(!board[y][x].getOccupied())//if square is occupied
    {
        return -3;
    }
    else
    {
        //if everything is okay get the info and update the arguments
        Square piece = board[y][x];
        c = piece.getColor();
        p = piece.getPiece();
        return 1;
    }
}


int Chessboard::move(int fromX, int fromY, int toX, int toY)
{
    if(fromX<0 || fromX>7)//valid fromX
    {
        cout << "Invalid from X" << endl;
        return -1;
    }
    else if(fromY < 0 || fromY > 7)//valid fromY
    {
        cout << "Invalid from Y" << endl;
        return -2;
    }
    else if(toX < 0 || toX > 7)//valid toX
    {
        cout << "Invalid to X" << endl;
        return -3;
    }
    else if(toY < 0 || toY > 7)//valid toY
    {
        cout << "Invalid to Y" << endl;
        return -4;
    }
    else if(!board[fromY][fromX].getOccupied())//if board is not occupied at fromx,y
    {
        cout << "There is no piece in that position" << endl;
        return -5;
    }
    else if(board[toY][toX].getColor() == board[fromY][fromX].getColor())//if moving to a square with same color piece
    {
        cout << "The to position is already occupied by your other piece" << endl;
        return -7;
    }
    else{
        //check for valid move for each piece and if the path is clear
        Square square = Square();
        Piece piece =board[fromY][fromX].getPiece();
        if (enPassantPossible && piece != Piece::Pawn) {
            resetEnPassant(enPassantX,enPassantY, enPassantPossible);
        }
        if (inCheck && piece != Piece::King) {
            cout << "You are in check please move your king."<< endl;
        }
        if (board[fromY][fromX].getColor() == currentPlayer)
        {

            switch (piece)
            {
                case Piece::Rook:
                    if(validRookMove(fromX,fromY,toX,toY))
                    {
                        if (validMakeMove(fromX,fromY,toX,toY)) {
                            if (currentPlayer == Color::White) {
                                if (fromY == 0) { rookHasMoved[0][0] = true;}
                                if (fromY == 7) { rookHasMoved[0][1] = true;}
                            }if (currentPlayer == Color::Black) {
                                if (fromY == 0) { rookHasMoved[1][0] = true;}
                                if (fromY == 7) { rookHasMoved[1][1] = true;}
                            }
                            isKingInCheck();
                            return 1;
                        }else {
                            return -7;
                        }
                    }else {
                        cout << "invalid move" << endl;
                        return -7;
                    }
                    break;
                case Piece::Knight:
                    if(validKnightMove(fromX,fromY,toX,toY))
                    {
                        if (validMakeMove(fromX,fromY,toX,toY)) {isKingInCheck();return 1;}
                        else {return -7;}
                    }else {
                        cout << "invalid move" << endl;
                        return -7;
                    }
                    break;
                case Piece::Bishop:
                    if(validBishopMove(fromX,fromY,toX,toY))
                    {
                        if (validMakeMove(fromX,fromY,toX,toY)) {isKingInCheck();return 1;}
                        return -7;
                    }else {
                        cout << "invalid move" << endl;
                        return -7;
                    }
                    break;
                case Piece::King:
                    if(validKingMove(fromX,fromY,toX,toY)) {
                        if (validMakeMove(fromX,fromY,toX,toY)){
                            inCheck = false;
                            if (currentPlayer == Color::White) {
                                kingHasMoved[0] = true;
                            }if (currentPlayer == Color::Black) {
                                kingHasMoved[1] = true;
                            }
                            isKingInCheck();
                            return 1;
                        }else{return -7;}
                    }else {
                        cout << "invalid move" << endl;
                        return -7;
                    }
                    break;
                case Piece::Queen:
                    if(validQueenMove(fromX,fromY,toX,toY))
                    {
                        if (validMakeMove(fromX,fromY,toX,toY)) {return 1;}
                        else {return -7;}
                    }else {
                        cout << "invalid move" << endl;
                        return -7;
                    }
                    break;
                case Piece::Pawn:
                    if(validPawnMove(fromX,fromY,toX,toY))
                    {
                        if (validMakeMove(fromX,fromY,toX,toY)) {
                            checkPawnPromotion(toX,toY);
                            isKingInCheck();
                            return 1;
                        }else{return -7;}
                    }else {
                        cout << "invalid move" << endl;
                        return -7;
                    }
                    break;
                case Piece::UnknownPiece:
                    break;
            }
            isKingInCheck();
        }else {
            if (currentPlayer == Color::White) {
                cout << "it is white piece's turn" << endl;
            }
            else {cout << "it is black piece's turn" << endl;}
        }
    }
}
void Chessboard::changePlayer() {
    if (currentPlayer == Color::White) {
        currentPlayer = Color::Black;
        attackColor = Color::White;
    }
    else{currentPlayer = Color::White; attackColor = Color::Black;}
}
bool Chessboard::validMakeMove(int fromX, int fromY, int toX, int toY)
{
    if (board[fromY][fromX].getPiece() == Piece::King) {updateKing(toX,toY);}
    int kingX = (currentPlayer == Color::White) ? whiteKingX : blackKingX;
    int kingY = (currentPlayer == Color::White) ? whiteKingY : blackKingY;

    Square temp = board[toY][toX];
    board[toY][toX] = board[fromY][fromX];
    board[fromY][fromX] = Square();
    // Check if the king is in check
    if (isSquareUnderAttack(kingX, kingY))
        {
        if (board[toY][toX].getPiece() == Piece::King) {updateKing(fromX,fromY);}
        board[fromY][fromX] = board[toY][toX];
        board[toY][toX] = temp;
        cout << "Can't move that piece" << endl;
        return false;
    }
    changePlayer();
    return true;
}

bool Chessboard::validKnightMove(int fromX, int fromY, int toX, int toY)
{
    int xMove = abs(fromX - toX);
    int yMove = abs(fromY - toY);
    if((xMove == 2 && yMove == 1) || (xMove == 1 && yMove == 2))
    {
        return true;
    }
    return false;
}

bool Chessboard::validQueenMove(int fromX, int fromY, int toX, int toY)
{
    if(validBishopMove(fromX,fromY,toX,toY) || validRookMove(fromX,fromY,toX,toY))
    {
        return true;
    }
    return false;
}

bool Chessboard::validPawnMove(int fromX, int fromY, int toX, int toY) {

    if (board[toY][toX].getOccupied() && board[toY][toX].getColor() == board[fromY][fromX].getColor()) {
        return false;
    }

    int direction = (board[fromY][fromX].getColor() == Color::White) ? 1 : -1;
    int row = (board[fromY][fromX].getColor() == Color::White) ? 1 : 6;

    if (fromY + direction == toY && fromX == toX ) {
        if (!board[toY][toX].getOccupied()) {
            return true;
        }
    }

    if (fromY == row && toY == fromY + 2 * direction && fromX == toX ) {
        if (!board[fromY + direction][fromX].getOccupied() && !board[toY][toX].getOccupied()) {
            enPassantX = fromX;
            enPassantY = fromY + direction;
            enPassantPossible = true;
            return true;
        }
    }

    if (fromY + direction == toY && abs(fromX - toX) == 1 ) {
        if (toX == enPassantX && toY == enPassantY) {
            board[enPassantY-direction][enPassantX] = Square(); // Remove captured pawn
            resetEnPassant(enPassantX, enPassantY, enPassantPossible);
            return true;
        }

        if (board[toY][toX].getOccupied() && board[toY][toX].getColor() != board[fromY][fromX].getColor()) {
            return true;
        }
    }

    return false;
}


bool Chessboard::validKingMove(int fromX, int fromY, int toX, int toY) {
    if (fromX == toX && fromY == toY) {
        return false;
    }
    if (std::abs(fromX - toX) == 2 && fromY == toY && !inCheck) { // Castling
        int rookX = (toX > fromX) ? 7 : 0;
        int rookIndex = (toX > fromX) ? 1 : 0;

        // Check if king or rook has moved
        if (kingHasMoved[currentPlayer == Color::White ? 0 : 1] || rookHasMoved[currentPlayer == Color::White ? 0 : 1][rookIndex]) {
            // cout << "here"<<endl;
            return false;
        }

        // Check for pieces in between
        int step = (toX > fromX) ? 1 : -1;
        for (int x = fromX + step; x != toX + step; x += step) {
            if (board[fromY][x].getOccupied() || isSquareUnderAttack(x, fromY)) {
                return false;
            }
        }
        performCastling( fromX,  fromY, toX, toY);
        return true;
    }
    if (std::abs(fromX - toX) <= 1 && std::abs(fromY - toY) <= 1 && !isSquareUnderAttack(toX, toY)&&board[toY][toX].getColor() != board[fromY][fromX].getColor()) {
        return true;
    }
    return false;
}
bool Chessboard::validBishopMove(int fromX, int fromY, int toX, int toY)
{
    if(abs(toX - fromX) != abs(toY - fromY))
    {
        return false;
    }
    if (toX == fromX && toY == fromY)
    {
        return false;
    }
    int xMove = (toX > fromX) ? 1 : -1;
    int yMove = (toY > fromY) ? 1 : -1;
    int x, y;
    for (x = fromX + xMove, y = fromY + yMove; x != toX; x += xMove, y += yMove) {
        if (board[y][x] .getOccupied()) {
            return false;  // Path is not clear
        }
    }
    return true;
}



bool Chessboard::validRookMove(int fromX, int fromY, int toX, int toY) {
    if (fromX == toX && fromY == toY) {
        return false; // No movement
    }

    // Check for a vertical movement
    if (fromX == toX) {
        int yStep = (toY > fromY) ? 1 : -1;
        for (int y = fromY + yStep; y != toY; y += yStep) {
            if (board[y][fromX].getOccupied()) {
                return false; // There is a piece in the way
            }
        }
        return true; // Valid vertical movement
    }
    // Check for a horizontal movement
    else if (fromY == toY) {
        int xStep = (toX > fromX) ? 1 : -1;
        for (int x = fromX + xStep; x != toX; x += xStep) {
            if (board[fromY][x].getOccupied()) {
                return false; // There is a piece in the way
            }
        }
        return true; // Valid horizontal movement
    }
    return false; // Not a valid movement (neither vertical nor horizontal)
}
bool Chessboard::isKingInCheck() {
    int kingX = (currentPlayer == Color::White) ? whiteKingX : blackKingX;
    int kingY = (currentPlayer == Color::White) ? whiteKingY : blackKingY;
    if (isSquareUnderAttack(kingX, kingY)) {
        cout << "CHECK:: " << static_cast<char>(kingX+97) << kingY+1<<" "<< board[kingY][kingX].getName() <<" in check" << endl ;
        inCheck = true;
        return true;
    }
    return false;
}

bool Chessboard::isSquareUnderAttack(int x, int y) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[j][i].getOccupied() && board[j][i].getColor() == attackColor) {
                Piece piece = board[j][i].getPiece();
                switch (piece) {
                    case Piece::Rook:
                        if (validRookMove(i, j, x, y)) return true;
                    break;
                    case Piece::Knight:
                        if (validKnightMove(i, j, x, y)) return true;
                    break;
                    case Piece::Bishop:
                        if (validBishopMove(i, j, x, y)) return true;
                    break;
                    case Piece::Queen:
                        if (validQueenMove(i, j, x, y)) return true;
                    break;
                    case Piece::King:
                        if (validKingMove(i, j, x, y)) return true;
                    break;
                    case Piece::Pawn:
                        if (validPawnMove(i, j, x, y)) return true;
                    break;
                    default:
                        break;
                }
            }
        }
    }
    return false;
}

void Chessboard::resetEnPassant(int& enPassantX,int& enPassantY, bool& enPassantPossible)
{
    enPassantX = -1;
    enPassantY = -1;
    enPassantPossible = false;
}
void Chessboard::updateKing(int X, int Y)
{
    if (currentPlayer == White) {
        whiteKingX = X;
        whiteKingY = Y;
    }
    else {
        blackKingX = X;
        blackKingY = Y;
    }
}

void Chessboard::checkPawnPromotion(int toX, int toY) {
    if (toY == 0 || toY == 7)
        {
        promotePawn = true;
    }
}
void Chessboard::promotePawnFunc(int toX, int toY, string input) {
    promotePawn = false;
    Color color = board[toY][toX].getColor();
    board[toY][toX] = Square();

    if (input == "k") {
        board[toY][toX] = Square(color, Piece::Knight);
    } else if (input == "b") {
        board[toY][toX] = Square(color, Piece::Bishop);
    } else if (input == "r") {
        board[toY][toX] = Square(color, Piece::Rook);
    } else if (input == "q") {
        board[toY][toX] = Square(color, Piece::Queen);
    } else {
        std::cout << "Invalid piece! Please enter K, R, B, or Q." << std::endl;
    }
}


ChessboardIterator Chessboard::begin() {
    return ChessboardIterator(*this, 0); // assuming you want to start from position 0
}
ChessboardIterator Chessboard::end() {
    return ChessboardIterator(*this, 64); // one past the last valid position (63)
}

bool Chessboard::isCheckmate() {
    // Find the current player's king position
    int kingX = (currentPlayer == Color::White) ? whiteKingX : blackKingX;
    int kingY = (currentPlayer == Color::White) ? whiteKingY : blackKingY;

    // Check if the king is in check
    if (!isSquareUnderAttack(kingX, kingY)) {
        return false; // Not checkmate if the king is not in check
    }
    //check if king can move
    int a[8][2] = {{1,0},{1,1},{1,-1},{0,-1},{0,1},{-1,0},{-1,-1},{-1,1}};
    for (int i = 0; i < 8; i++) {
        int toY = kingY + a[i][0];
        int toX = kingX + a[i][1];
        if (toX >= 0 && toX < 8 && toY >= 0 && toY < 8) {
            if (validKingMove(kingX, kingY, toX, toY)) {
                Square temp = board[toY][toX];
                board[toY][toX] = board[kingY][kingX];
                board[kingY][kingX] = Square();
                if (!isSquareUnderAttack(toX, toY))
                {
                    // cout <<"checking kings position"<<endl;
                    // cout << toX << ", " << toY << endl;
                    board[kingY][kingX] =board[toY][toX];
                    board[toY][toX] = temp;
                    return false;
                }

            }

        }
    }

    // Check if any move can resolve the check
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if (board[y][x].getOccupied() && board[y][x].getColor() == currentPlayer) {
                Piece piece = board[y][x].getPiece();

                // Simulate all valid moves for the piece
                for (int toY = 0; toY < 8; ++toY) {
                    for (int toX = 0; toX < 8; ++toX) {
                        // std::cout << "Simulating move: (" << x << ", " << y << ") -> (" << toX << ", " << toY << ")" << std::endl;
                        // std::cout << "King position during simulation: (" << kingX << ", " << kingY << ")" << std::endl;
                        if (isValidMove(x, y, toX, toY)) {
                            // Simulate the move
                            Square temp = board[toY][toX];
                            board[toY][toX] = board[y][x];
                            board[y][x] = Square();

                            // Update king position if the king is moved
                            int prevKingX = kingX, prevKingY = kingY;
                            if (piece == Piece::King) {
                                kingX = toX;
                                kingY = toY;
                            }

                            // Check if the king is still in check
                            bool stillInCheck = isSquareUnderAttack(kingX, kingY);

                            // Undo the move
                            board[y][x] = board[toY][toX];
                            board[toY][toX] = temp;

                            // Restore king's position if it was moved
                            if (piece == Piece::King) {
                                kingX = prevKingX;
                                kingY = prevKingY;
                            }

                            // If the king is no longer in check, it's not checkmate
                            if (!stillInCheck)
                                {
                                cout <<"checking every position "<< toY << ", " << toX << ", " << piece << std::endl;
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }

    // If no valid move removes the check, it's checkmate
    cout <<"CheckMate!!"<<endl;
    return true;
}


bool Chessboard::isValidMove(int fromX, int fromY, int toX, int toY) {
    Piece piece = board[fromY][fromX].getPiece();
    switch (piece) {
        case Piece::Rook: return validRookMove(fromX, fromY, toX, toY);
        case Piece::Knight: return validKnightMove(fromX, fromY, toX, toY);
        case Piece::Bishop: return validBishopMove(fromX, fromY, toX, toY);
        case Piece::Queen: return validQueenMove(fromX, fromY, toX, toY);
        case Piece::King: return validKingMove(fromX, fromY, toX, toY);
        case Piece::Pawn: return validPawnMove(fromX, fromY, toX, toY);
        default: return false;
    }
}
void Chessboard::performCastling(int fromX, int fromY, int toX, int toY) {
    int rookFromX = (toX > fromX) ? 7 : 0; // Right rook for kingside, left rook for queenside
    int rookToX = (toX > fromX) ? toX - 1 : toX + 1;

    // Move the rook
    board[toY][rookToX] = board[fromY][rookFromX];
    board[fromY][rookFromX] = Square();
    if (currentPlayer == Color::White) {
        if (fromY == 0) { rookHasMoved[0][0] = true;}
        if (fromY == 7) { rookHasMoved[0][1] = true;}
    }if (currentPlayer == Color::Black) {
        if (fromY == 0) { rookHasMoved[1][0] = true;}
        if (fromY == 7) { rookHasMoved[1][1] = true;}
    }
}