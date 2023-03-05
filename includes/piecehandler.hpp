#pragma once
#include "pieces/piece.hpp"
#include <memory>
#include <string>

class Piece;
class Game;
class PieceHandler
{
  public:
    void forsythGeneration(Game &game, std::string fen);
    bool movePieceAt(Game &game, std::shared_ptr<Piece> piece, int x, int y);
    std::shared_ptr<Piece> getPieceAt(Game &game, int x, int y);
    std::shared_ptr<Piece> makeCopy(std::shared_ptr<Piece> piece) const;
    void promotePiece(Piece &toPromote, PieceType type);
};