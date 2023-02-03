#pragma once
#include "board/board.hpp"
#include "piecehandler.hpp"
#include "pieces/piece.hpp"
#include "pieces/roi.hpp"
#include <array>
#include <memory>
#include <vector>

class Game
{
  private:
    Board board;
    PieceHandler piece_handler;
    // 0 black, 1 white
    int turn;
    int num_turns;
    bool check;
    bool checkMate;
    bool staleMate;
    std::vector<std::shared_ptr<Piece>> black_eaten_pieces;
    std::vector<std::shared_ptr<Piece>> white_eaten_pieces;
    std::vector<std::shared_ptr<Piece>> alive_pieces;
    void init();

  public:
    Game();
    ~Game();
    void run();
    std::shared_ptr<Roi> getWhiteKing() const;
    std::shared_ptr<Roi> getBlackKing() const;
    std::vector<std::shared_ptr<Piece>> getAlivePieces() const;
    std::vector<std::shared_ptr<Piece>> &getBlackEatenPieces();
    std::vector<std::shared_ptr<Piece>> &getWhiteEatenPieces();
    Board &getBoard();
    PieceHandler &getPieceHandler();
    void printInfo();
    void addAlivePiece(std::shared_ptr<Piece> piece);
    void removeAlivePiece(std::shared_ptr<Piece> piece);
};