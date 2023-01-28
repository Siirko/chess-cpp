#include "../../includes/pieces/piece.hpp"
#include <iostream>
#include <string>

Piece::Piece(int x, int y, int color) : x{x}, y{y}, color{color}, firstMove{true} {}

Piece::~Piece() {}

void Piece::setX(int x) { this->x = x; }

void Piece::setY(int y) { this->y = y; }

int Piece::getX() const { return this->x; }

int Piece::getY() const { return this->y; }

void Piece::setColor(int color) { this->color = color; }

int Piece::getColor() const { return this->color; }

bool Piece::getFirstMove() const { return this->firstMove; }

void Piece::setFirstMove(bool firstMove) { this->firstMove = firstMove; }

char Piece::getType()
{
    // Get the name of the piece and print the first letter
    // index 1 is choosen because for exemple name is "4Pawn"
    std::string type = typeid(*this).name();
    return type.at(1);
}

int Piece::getNumMoves() const { return this->num_moves; }

void Piece::updateNumMoves() { this->num_moves++; }

std::ostream &operator<<(std::ostream &os, const Piece &piece)
{
    std::string color = piece.color == Color::BLACK ? "BLACK" : "WHITE";
    os << "Type: " << typeid(piece).name() << std::endl
       << "Color: " << color << std::endl
       << "First move: " << piece.firstMove << std::endl
       << "Position: "
       << "x->" << piece.x << " y->" << piece.y << std::endl
       << "Num of moves: " << piece.num_moves << std::endl;
    return os;
}