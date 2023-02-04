#include "../includes/piecehandler.hpp"
#include "../includes/game.hpp"
#include "../includes/pieces/bishop.hpp"
#include "../includes/pieces/knight.hpp"
#include "../includes/pieces/pawn.hpp"
#include "../includes/pieces/piece.hpp"
#include "../includes/pieces/queen.hpp"
#include "../includes/pieces/roi.hpp"
#include "../includes/pieces/tower.hpp"

#include <iostream>

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
            case 'p':
                piece = std::make_shared<Pawn>(x, y, Color::BLACK);
                break;
            case 'P':
                piece = std::make_shared<Pawn>(x, y, Color::WHITE);
                break;
            case 'r':
                piece = std::make_shared<Tower>(x, y, Color::BLACK);
                break;
            case 'R':
                piece = std::make_shared<Tower>(x, y, Color::WHITE);
                break;
            case 'n':
                piece = std::make_shared<Knight>(x, y, Color::BLACK);
                break;
            case 'N':
                piece = std::make_shared<Knight>(x, y, Color::WHITE);
                break;
            case 'b':
                piece = std::make_shared<Bishop>(x, y, Color::BLACK);
                break;
            case 'B':
                piece = std::make_shared<Bishop>(x, y, Color::WHITE);
                break;
            case 'q':
                piece = std::make_shared<Queen>(x, y, Color::BLACK);
                break;
            case 'Q':
                piece = std::make_shared<Queen>(x, y, Color::WHITE);
                break;
            case 'k':
                piece = std::make_shared<Roi>(x, y, Color::BLACK);
                break;
            case 'K':
                piece = std::make_shared<Roi>(x, y, Color::WHITE);
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

bool PieceHandler::movePieceAt(Game &game, std::shared_ptr<Piece> piece, int x, int y)
{
    bool valid = true;
    try
    {
        std::shared_ptr<Piece> eatenPiece = game.getBoard().movePiece(piece, x, y);
        if (eatenPiece != nullptr && eatenPiece->getType() != PieceType::KING)
        {
            if (eatenPiece->getColor() == Color::WHITE)
                game.getBlackEatenPieces().push_back(eatenPiece);
            else
                game.getWhiteEatenPieces().push_back(eatenPiece);
            game.removeAlivePiece(eatenPiece);
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        valid = false;
    }
    return valid;
}

std::shared_ptr<Piece> PieceHandler::getPieceAt(Game &game, int x, int y)
{
    auto piece = game.getBoard().getTile(x, y).getPiece();
    return piece != nullptr ? piece : nullptr;
}