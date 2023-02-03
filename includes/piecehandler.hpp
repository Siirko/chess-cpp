#pragma once
#include "parser.hpp"
#include "pieces/piece.hpp"
#include <memory>
#include <string>

class Game;
class Tile;
class PieceHandler : public std::enable_shared_from_this<PieceHandler>
{
  public:
    std::shared_ptr<PieceHandler> getptr() { return shared_from_this(); }
    void forsythGeneration(Game &game, std::string fen);
    bool movePieceAt(Game &game, std::shared_ptr<Piece> piece, int x, int y);
    std::shared_ptr<Piece> getPieceAt(Game &game, int x, int y);
    void checkDiagonals(std::array<std::array<Tile, 8>, 8> board, Piece::PieceMove &result,
                        Parser::UpdateCoords coord);
    void checkRowsAndColumns(std::array<std::array<Tile, 8>, 8> board, Piece::PieceMove &result,
                             Parser::UpdateCoords coord);
};