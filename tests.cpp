#include <gtest/gtest.h>
#include "chessboard.h"

TEST(ChessboardTests, BoardInitialization) {
    Chessboard board;
    EXPECT_EQ(board.place(0, 0, Color::White, Piece::Rook), 1); // Valid placement
    EXPECT_EQ(board.place(0, 0, Color::White, Piece::Rook), -3); // Square already occupied
}

TEST(ChessboardTests, RookMovement) {
    Chessboard board;
    board.place(0, 0, Color::White, Piece::Rook);
    board.place(7, 7, Color::Black, Piece::Rook);
    board.place(1, 5, Color::Black, Piece::Pawn);
    board.place(1,6,Color::Black, Piece::King);

    EXPECT_EQ(board.blackKingX,1);
    EXPECT_EQ(board.blackKingY,6);
    board.print();
    // //checkfor vertical movement
    EXPECT_EQ(board.move(0, 0, 7, 6), -7); // Invalid move
    EXPECT_EQ(board.move(0, 0, 0, 5), 1); // Valid move

    //check for horizontal movement
    EXPECT_EQ(board.move(7, 7, 5, 5), -7); // Invalid move
    EXPECT_EQ(board.move(7, 7, 0, 7), 1); // Valid move

    //check for piece in the middle invalid move
    EXPECT_EQ(board.move(0, 5, 4, 5), -7);

    //check if rook will take the piece
    EXPECT_EQ(board.move(0, 5, 1, 5), 1);

    ASSERT_TRUE(board.inCheck);
    board.print();
}

TEST(ChessboardTests, KnightMovement) {
    Chessboard board;
    board.place(1, 0, Color::White, Piece::Knight);
    board.place(6, 7, Color::Black, Piece::Knight);

    //check movement
    EXPECT_EQ(board.move(1, 0, 0,2),1);
    EXPECT_EQ(board.move(6, 7, 5,5),1);
    EXPECT_EQ(board.move(0, 2, 2,3),1);
    EXPECT_EQ(board.move(5, 5, 4,3),1);

    //check if knight takes
    EXPECT_EQ(board.move(2, 3, 3,5),1);
    EXPECT_EQ(board.move(4, 3, 3,5),1);
    board.print();
}
TEST(ChessboardTests,BishopMovement)
{
    Chessboard board;
    board.place(2, 0, Color::White, Piece::Bishop);
    board.place(5, 7, Color::Black, Piece::Bishop);
    board.place(6, 1, Color::White, Piece::Pawn);
    board.print();
    //check movement
    EXPECT_EQ( board.move(2,0,5,3),1);
    EXPECT_EQ( board.move(5,7,3,5),1);
    //black should take white
    EXPECT_EQ(board.move(5,3,4,4),1);
    EXPECT_EQ(board.move(3,5,4,4),1);

    // //check invalid move if piece in the middle
    EXPECT_EQ(board.move(6,1,6,2),1);//move white pawn in the way
    EXPECT_EQ(board.move(4,4,7,1),-7);
    board.print();
}


TEST(ChessboardTests, QueenMovement) {
    Chessboard board;
    board.place(3, 0, Color::White, Piece::Queen);
    board.place(3, 7, Color::Black, Piece::Queen);
    board.place(5, 3, Color::Black, Piece::Pawn);

    board.place(0,1,Black,Piece::King);
    board.print();
    //checkfor vertical movement
    EXPECT_EQ(board.move(3,0,4,2), -7); // Invalid move
    EXPECT_EQ(board.move(3,0,3,3), 1); // Valid move

    //check for horizontal movement
    EXPECT_EQ(board.move(3,7,4,5), -7); // Invalid move
    EXPECT_EQ(board.move(3,7,6,7), 1); // Valid move

    //check for piece in the middle invalid move
    EXPECT_EQ(board.move(3,3,7,3), -7);
    //
    // //check for diagonal movement
    EXPECT_EQ(board.move(3,3,7,7),1);
    EXPECT_EQ(board.move(6,7,3,4), 1); // Valid move
    board.print();
}

TEST(ChessboardTests, PawnMoveMent) {
    Chessboard board;
    board.place(0,6,Color::Black,Piece::Pawn);
    board.place(1,3,White,Piece::Pawn);
    board.place(1,6,Color::Black,Piece::Pawn);
    board.place(2,6,Color::White,Piece::Pawn);
    board.print();
    //pawn can move one square but not two when not on initial square
    EXPECT_EQ(board.move(1,3,1,5),-7); //not valid
    EXPECT_EQ(board.move(1,3,1,4),1); //valid

    //pawn cant move backwards
    EXPECT_EQ(board.move(0,6,0,7),-7);

    //pawn cam move two squares when on initial square
    EXPECT_EQ(board.move(0,6,0,4),1);

    //pawn can enpassant
    EXPECT_EQ(board.move(1,4,0,5),1);

    //pawn can only move diaganol if it can take a opposing piece
    EXPECT_EQ(board.move(1,6,2,5),-7); // not valid
    EXPECT_EQ(board.move(1,6,0,5),1);

    //pawn should be able to promote
    //checked this manually!
    board.move(2,6,2,7);
    board.promotePawnFunc(2,7,"q");
    board.print();
}

TEST(ChessboardTests, KingMovement) {
    Chessboard board;
    board.place(4,0,Color::White, Piece::King);
    board.place(4,7,Color::Black, Piece::King);
    board.place(7,0,Color::White, Piece::Rook);
    board.place(0,7,Color::Black, Piece::Rook);
    board.place(7,7,Color::Black, Piece::Rook);

    board.print();
    //check for castling
    EXPECT_EQ(board.move(4,0,6,0),1);

    //castling should not be possible if the king or rook as moved
    EXPECT_EQ(board.move(7,7,7,6),1); //move rook
    EXPECT_EQ(board.move(6,0,6,1),1); //play whites turn
    //check castling now
    EXPECT_EQ(board.move(4,7,6,7),-7);

    //check long castle
    EXPECT_EQ(board.move(4,7,3,7),1);
    board.print();
    //check for checks and checkmate
    Chessboard board2;
    board2.place(4,7,Black,King);
    board2.place(7,0,White,Rook);
    board2.place(0,0,White,Rook);

    board.print();

}
TEST(ChessboardTests, KingCheckmate) {
    Chessboard board;
    board.place(4,7,Black,King);
    board.place(7,0,White,Rook);
    board.place(0,0,White,Rook);
    board.print();
    //check for checks and checkmate
    EXPECT_EQ(board.move(0,0,0,6),1);
    EXPECT_EQ(board.move(4,7,5,7),1);
    EXPECT_EQ(board.move(7,0,7,7),1);
    EXPECT_TRUE(board.inCheck);
    EXPECT_TRUE(board.isCheckmate());
    board.print();
}