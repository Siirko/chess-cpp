#include "../../includes/pieces/piece.hpp"
#include "../../includes/board/tile.hpp"
#include "../../includes/gameruler.hpp"
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

bool Piece::beforeCheckMove(array2d<Tile, 8, 8> board, PieceMove result, int x, int y)
{
    if (result.valid_move == false)
    {
        result = {false, nullptr};
    }
    else if (GameRuler::getInstance().isKingInCheckAfterMove(board, this->getptr(), result.valid_move, x, y))
    {
        result = {false, nullptr};
    }
    else if (result.eaten_piece != nullptr && result.eaten_piece->getColor() == this->getColor() &&
             this->getType() != PieceType::KING)
    {
        result = {false, nullptr};
    }
    return result.valid_move;
}

bool Piece::canMove(array2d<Tile, 8, 8> board)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (this->isValidMove(board, i, j, true).valid_move)
                return true;
        }
    }
    return false;
}

std::vector<std::pair<int, int>> Piece::getValidMoves(array2d<Tile, 8, 8> board)
{
    std::vector<std::pair<int, int>> valid_moves;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            try
            {
                if (this->isValidMove(board, i, j, true).valid_move)
                    valid_moves.push_back(std::make_pair(i, j));
            }
            catch (const std::exception &e)
            {
                continue;
            }
        }
    }
    return valid_moves;
}

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