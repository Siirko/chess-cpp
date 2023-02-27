#pragma once
#include "board/board.hpp"
#include "piecehandler.hpp"
#include "pieces/king.hpp"
#include "pieces/piece.hpp"
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
    virtual void run() = 0;
    std::shared_ptr<King> getWhiteKing() const;
    std::shared_ptr<King> getBlackKing() const;
    std::vector<std::shared_ptr<Piece>> getAlivePieces() const;
    std::vector<std::shared_ptr<Piece>> &getBlackEatenPieces();
    std::vector<std::shared_ptr<Piece>> &getWhiteEatenPieces();
    Board &getBoard();
    Board getBoard() const;
    PieceHandler &getPieceHandler();
    PieceHandler getPieceHandler() const;
    int getTurn() const;
    void updateTurn();
    int getNumTurns() const;
    void updateNumTurns();
    bool getCheck() const;
    bool getCheck(Color color) const { return this->turn == color && this->check; }
    void setCheck(bool check);
    bool getCheckMate() const;
    void setCheckMate(bool checkMate);
    bool getStaleMate() const;
    void setStaleMate(bool staleMate);
    void addAlivePiece(std::shared_ptr<Piece> piece);
    void removeAlivePiece(std::shared_ptr<Piece> piece);
    std::string endResult() const;
    friend std::ostream &operator<<(std::ostream &os, const Game &game);
};