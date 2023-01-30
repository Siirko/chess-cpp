#include "../../includes/board/board.hpp"
#include "../../includes/gamewatcher.hpp"
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
    case 'P':
        return color == Color::WHITE ? "♙" : "♟";
    case 'T':
        return color == Color::WHITE ? "♖" : "♜";
    case 'K':
        return color == Color::WHITE ? "♘" : "♞";
    case 'B':
        return color == Color::WHITE ? "♗" : "♝";
    case 'Q':
        return color == Color::WHITE ? "♕" : "♛";
    case 'R':
        return color == Color::WHITE ? "♔" : "♚";
    default:
        return " ";
    }
}

void Board::printBoard()
{
    std::string space5 = std::string(5, ' ');
    std::cout << std::endl;
    std::cout << "     a     b     c     d     e     f     g     h    " << std::endl;
    std::cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << std::endl;
    for (int i = 8; i > 0; i--)
    {
        std::cout << i << " "; // numérotation ligne dans affichage
        for (int j = 0; j < 8; j++)
        {
            std::cout << "|";
            if (this->board[j][i - 1].getPiece() != nullptr)
            {
                std::cout << "\u0020\u0020"; // U+0020 est un esapce utf-8 taille police
                char type = this->board[j][i - 1].getPiece()->getType();
                std::cout << pieceSymbol(type, (Color)this->board[j][i - 1].getPiece()->getColor());
                std::cout << "\u0020"
                          << " ";
            }
            else
            {
                std::cout << space5;
            }
        }
        std::cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
        std::cout << std::endl;
    }
}

Tile Board::getTile(int x, int y) const { return this->board[x][y]; }

std::array<std::array<Tile, 8>, 8> Board::getBoard() const { return this->board; }

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

void Board::doCastling(std::shared_ptr<Piece> piece, Color color, int x, int y)
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
    std::pair<bool, std::shared_ptr<Piece>> valid_move;
    // First element is a bool that tells if the move is valid, the second element
    // is the piece that is eaten, null if no piece has been eaten
    try
    {
        valid_move = piece->isValidMove(this->board, x, y);
    }
    catch (const std::exception &e)
    {
        throw std::invalid_argument("can't move king");
    }
    if (GameWatcher::getInstance().isKingInCheck(this->board, (Color)piece->getColor()) &&
        GameWatcher::getInstance().isKingInCheckAfterMove(this->board, piece, x, y) && valid_move.first)
    {
        throw std::invalid_argument("king is check !");
    }
    if (valid_move.first)
    {
        // check if caste move
        if (piece->getType() == PieceType::KING && piece->getNumMoves() == 0 &&
            valid_move.second != nullptr && valid_move.second->getType() == PieceType::TOWER)
        {
            this->doCastling(piece, (Color)valid_move.second->getColor(), x, y);
            return eatenPiece;
        }
        else if (valid_move.second != nullptr && valid_move.second->getColor() == piece->getColor())
        {
            throw std::invalid_argument("Can't eat your own piece!");
        }
        else if (valid_move.second != nullptr && valid_move.second->getType() == PieceType::KING)
        {
            throw std::invalid_argument("Can't eat the King!");
        }
        else if (valid_move.second != nullptr)
        {
            eatenPiece = valid_move.second;
            std::cout << "Eaten piece: " << eatenPiece->getType() << std::endl;
            this->board[piece->getX()][piece->getY()].setPiece(nullptr);
            this->board[valid_move.second->getX()][valid_move.second->getY()].setPiece(nullptr);
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
    // TODO: print board like printBoard() method
    os << "Board TODO" << std::endl;
    return os;
}