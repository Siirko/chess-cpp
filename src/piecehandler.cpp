#include "../includes/piecehandler.hpp"
#include "../includes/game.hpp"
#include "../includes/pieces/bishop.hpp"
#include "../includes/pieces/knight.hpp"
#include "../includes/pieces/pawn.hpp"
#include "../includes/pieces/piece.hpp"
#include "../includes/pieces/queen.hpp"
#include "../includes/pieces/rook.hpp"
#include <functional>
#include <iostream>

// can't do tolower() at compile time (constexpr), so doing this for
// the sake of readability
const char UPPER_TO_LOWER = 'a' - 'A';
void PieceHandler::forsythGeneration(Game &game, std::string fen)
{
    int x = 0;
    int y = 0;
    for (size_t i = 0; i < fen.length(); i++)
    {
        if (fen[i] == '/')
        {
            x = 0;
            y++;
        }
        else if (fen[i] >= '1' && fen[i] <= '8')
        {
            x += fen[i] - '0';
        }
        else
        {
            std::shared_ptr<Piece> piece = nullptr;
            switch (fen[i])
            {
            case PieceType::PAWN + UPPER_TO_LOWER:
                piece = std::make_shared<Pawn>(x, y, Color::WHITE);
                break;
            case PieceType::PAWN:
                piece = std::make_shared<Pawn>(x, y, Color::BLACK);
                break;
            case PieceType::ROOK + UPPER_TO_LOWER:
                piece = std::make_shared<Rook>(x, y, Color::WHITE);
                break;
            case PieceType::ROOK:
                piece = std::make_shared<Rook>(x, y, Color::BLACK);
                break;
            case PieceType::KNIGHT + UPPER_TO_LOWER:
                piece = std::make_shared<Knight>(x, y, Color::WHITE);
                break;
            case PieceType::KNIGHT:
                piece = std::make_shared<Knight>(x, y, Color::BLACK);
                break;
            case PieceType::BISHOP + UPPER_TO_LOWER:
                piece = std::make_shared<Bishop>(x, y, Color::WHITE);
                break;
            case PieceType::BISHOP:
                piece = std::make_shared<Bishop>(x, y, Color::BLACK);
                break;
            case PieceType::QUEEN + UPPER_TO_LOWER:
                piece = std::make_shared<Queen>(x, y, Color::WHITE);
                break;
            case PieceType::QUEEN:
                piece = std::make_shared<Queen>(x, y, Color::BLACK);
                break;
            case PieceType::KING + UPPER_TO_LOWER:
                piece = std::make_shared<King>(x, y, Color::WHITE);
                break;
            case PieceType::KING:
                piece = std::make_shared<King>(x, y, Color::BLACK);
                break;
            default:
                break;
            }
            if (piece != nullptr)
            {
                game.getBoard().setPiece(piece);
                game.addAlivePiece(piece);
                x++;
            }
        }
    }
}

void setFirstMove(Game &game)
{
    for (auto pawn : game.getAlivePieces())
    {
        if (pawn->getFirstMove() && game.getTurn() == pawn->getColor() && pawn->getType() == PieceType::PAWN)
            pawn->setFirstMove(false);
    }
}

bool PieceHandler::movePieceAt(Game &game, std::shared_ptr<Piece> piece, int x, int y)
{
    bool valid = true;
    try
    {
        setFirstMove(game);
        std::shared_ptr<Piece> eatenPiece = game.getBoard().movePiece(piece, x, y);
        if (eatenPiece != nullptr && eatenPiece->getType() != PieceType::KING)
        {
            if (eatenPiece->getColor() == Color::WHITE)
                game.getBlackEatenPieces().push_back(eatenPiece);
            else
                game.getWhiteEatenPieces().push_back(eatenPiece);
            game.removeAlivePiece(eatenPiece);
        }
        if (piece->getType() == PieceType::PAWN && (piece->getY() == 0 || piece->getY() == 7))
        {
            // It should update manually, but apparently
            // the pointers are not being updated
            game.removeAlivePiece(piece);
            // ping-pong
            game.promotePawn(piece);
            game.getBoard().setPiece(piece);
            game.addAlivePiece(piece);
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        valid = false;
    }
    return valid;
}

void PieceHandler::promotePiece(std::shared_ptr<Piece> &toPromote, PieceType type)
{
    switch (type)
    {
    case PieceType::QUEEN:
        toPromote.reset(new Queen(toPromote->getX(), toPromote->getY(), toPromote->getColor()));
        break;
    case PieceType::ROOK:
        toPromote.reset(new Rook(toPromote->getX(), toPromote->getY(), toPromote->getColor()));
        break;
    case PieceType::BISHOP:
        toPromote.reset(new Bishop(toPromote->getX(), toPromote->getY(), toPromote->getColor()));
        break;
    case PieceType::KNIGHT:
        toPromote.reset(new Knight(toPromote->getX(), toPromote->getY(), toPromote->getColor()));
        break;
    default:
        break;
    }
}

std::shared_ptr<Piece> PieceHandler::getPieceAt(Game &game, int x, int y)
{
    auto piece = game.getBoard().getTile(x, y).getPiece();
    return piece != nullptr ? piece : nullptr;
}