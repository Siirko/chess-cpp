#include "../../includes/board/tile.hpp"
#include "../../includes/pieces/piece.hpp"
#include <memory>

Tile::Tile()
{
    this->x = 0;
    this->y = 0;
    this->piece = nullptr;
}

Tile::~Tile() {}

void Tile::setPiece(std::shared_ptr<Piece> piece) { this->piece = piece; }

std::shared_ptr<Piece> Tile::getPiece() const { return this->piece; }

int Tile::getX() const { return this->x; }

int Tile::getY() const { return this->y; }

void Tile::setX(int x) { this->x = x; }

void Tile::setY(int y) { this->y = y; }
