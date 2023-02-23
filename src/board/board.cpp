#include "../../includes/board/board.hpp"
#include "../../includes/gameruler.hpp"
#include <array>
#include <iostream>
#include <memory>
#include <string>

Board::Board() { this->initBoard(); }

Board::~Board() {}

void Board::initBoard()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            this->board[i][j].setX(i);
            this->board[i][j].setY(j);
            this->board[i][j].setPiece(nullptr);
        }
    }
}

std::string pieceSymbol(char type, Color color)
{
    switch (type)
    {
    case PieceType::PAWN:
        return color == Color::WHITE ? "♙" : "♟";
    case PieceType::TOWER:
        return color == Color::WHITE ? "♖" : "♜";
    case PieceType::KNIGHT:
        return color == Color::WHITE ? "♘" : "♞";
    case PieceType::BISHOP:
        return color == Color::WHITE ? "♗" : "♝";
    case PieceType::QUEEN:
        return color == Color::WHITE ? "♕" : "♛";
    case PieceType::KING:
        return color == Color::WHITE ? "♔" : "♚";
    default:
        return " ";
    }
}

Tile Board::getTile(int x, int y) const { return this->board[x][y]; }

array2d<Tile, 8, 8> Board::getArray() const { return this->board; }

void Board::setPiece(std::shared_ptr<Piece> piece)
{
    this->board[piece->getX()][piece->getY()].setPiece(piece);
}

void Board::updatePiece(std::shared_ptr<Piece> piece, int x, int y)
{
    this->board[piece->getX()][piece->getY()].setPiece(nullptr);
    this->board[x][y].setPiece(piece);
    piece->setX(x);
    piece->setY(y);
    piece->updateNumMoves();
}

void Board::doCastling(std::shared_ptr<Piece> piece, int x, int y)
{
    int towerX = x;
    int n_pos_towerX = x == 0 ? 3 : 5;
    int n_pos_kingX = x == 0 ? 2 : 6;
    std::shared_ptr<Piece> tower = this->board[towerX][y].getPiece();
    this->updatePiece(tower, n_pos_towerX, y);
    this->updatePiece(piece, n_pos_kingX, y);
}

std::shared_ptr<Piece> Board::movePiece(std::shared_ptr<Piece> piece, int x, int y)
{
    std::shared_ptr<Piece> eatenPiece = nullptr;
    Piece::PieceMove future_move;
    try
    {
        future_move = piece->isValidMove(this->board, x, y);
    }
    catch (const std::exception &e)
    {
        throw std::invalid_argument("can't move king");
    }
    if (future_move.valid_move)
    {
        // check if caste move
        if (piece->getType() == PieceType::KING && piece->getNumMoves() == 0 &&
            future_move.eaten_piece != nullptr && future_move.eaten_piece->getType() == PieceType::TOWER)
        {
            this->doCastling(piece, x, y);
            return eatenPiece;
        }
        // chec if pawn can do a promotion
        else if (piece->getType() == PieceType::PAWN && (y == 0 || y == 7))
        {
            // this->doPromotion(piece, x, y);
            return eatenPiece;
        }
        else if (future_move.eaten_piece != nullptr &&
                 future_move.eaten_piece->getColor() == piece->getColor())
        {
            throw std::invalid_argument("Can't eat your own piece!");
        }
        else if (future_move.eaten_piece != nullptr && future_move.eaten_piece->getType() == PieceType::KING)
        {
            throw std::invalid_argument("Can't eat the King!");
        }
        else if (future_move.eaten_piece != nullptr)
        {
            eatenPiece = future_move.eaten_piece;
            std::cout << "Eaten piece: " << eatenPiece->getType() << std::endl;
            this->board[piece->getX()][piece->getY()].setPiece(nullptr);
            this->board[future_move.eaten_piece->getX()][future_move.eaten_piece->getY()].setPiece(nullptr);
        }
        else
        {
            std::cout << "No piece eaten" << std::endl;
            this->board[piece->getX()][piece->getY()].setPiece(nullptr);
        }
        piece->setX(x);
        piece->setY(y);
        this->board[x][y].setPiece(piece);
        piece->updateNumMoves();
    }
    else
    {
        throw std::invalid_argument("Invalid move");
    }
    return eatenPiece;
}

std::ostream &operator<<(std::ostream &os, const Board &board)
{
    std::string space5 = std::string(5, ' ');
    os << std::endl;
    os << "     a     b     c     d     e     f     g     h    " << std::endl;
    os << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << std::endl;
    for (int i = 8; i > 0; i--)
    {
        os << i << " "; // numérotation ligne dans affichage
        for (int j = 0; j < 8; j++)
        {
            os << "|";
            if (board.board[j][i - 1].getPiece() != nullptr)
            {
                os << "\u0020\u0020"; // U+0020 est un esapce utf-8 taille police
                char type = board.board[j][i - 1].getPiece()->getType();
                os << pieceSymbol(type, (Color)board.board[j][i - 1].getPiece()->getColor());
                os << "\u0020"
                   << " ";
            }
            else
            {
                os << space5;
            }
        }
        os << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
        os << std::endl;
    }
    return os;
}