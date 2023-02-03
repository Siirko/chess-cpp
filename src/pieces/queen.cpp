#include "../../includes/pieces/queen.hpp"
#include "../../includes/board/tile.hpp"
#include "../../includes/pieces/piece.hpp"
#include <array>
#include <iostream>
#include <string>

Queen::Queen(int x, int y, int color) : Piece(x, y, color), value{9} { this->setFirstMove(false); }

Queen::~Queen() {}

Piece::PieceMove Queen::isValidMove(std::array<std::array<Tile, 8>, 8> board, int x, int y)
{
    PieceMove result = {false, nullptr};
    // Check if the move is out of the board
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return result;
    // Check if the move is to the same position
    if (x == this->getX() && y == this->getY())
        return result;
    // check left down diagonal
    if (this->getMoveFunctions().size() != 0)
    {
        for (auto func : this->getMoveFunctions())
        {
            Parser::Coord to = {x, y};
            Parser::Coord from = {this->getX(), this->getY()};
            Parser::UpdateCoords coord;
            coord.from = from;
            coord.to = to;
            func(board, result, coord);
        }
    }
    else
    {
        throw std::runtime_error("No move functions");
    }
    result.valid_move = this->beforeCheckMove(board, result, x, y);
    return result;
}