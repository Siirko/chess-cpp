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
void print() { printf("ereeeee"); }
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
                piece = std::make_shared<Pawn>(x, y, Color::WHITE);
                break;
            case 'P':
                piece = std::make_shared<Pawn>(x, y, Color::BLACK);
                break;
            case 'r':
                piece = std::make_shared<Tower>(x, y, Color::WHITE);
                break;
            case 'R':
                piece = std::make_shared<Tower>(x, y, Color::BLACK);
                break;
            case 'n':
                piece = std::make_shared<Knight>(x, y, Color::WHITE);
                break;
            case 'N':
                piece = std::make_shared<Knight>(x, y, Color::BLACK);
                break;
            case 'b':
                piece = std::make_shared<Bishop>(x, y, Color::WHITE);
                break;
            case 'B':
                piece = std::make_shared<Bishop>(x, y, Color::BLACK);
                break;
            case 'q':
            {
                piece = std::make_shared<Queen>(x, y, Color::WHITE);
                auto function_diags = &PieceHandler::checkDiagonals;
                auto funcion_rows_columns = &PieceHandler::checkRowsAndColumns;
                piece->getMoveFunctions().push_back(std::bind(function_diags, this, std::placeholders::_1,
                                                              std::placeholders::_2, std::placeholders::_3));
                piece->getMoveFunctions().push_back(std::bind(funcion_rows_columns, this,
                                                              std::placeholders::_1, std::placeholders::_2,
                                                              std::placeholders::_3));
                break;
            }
            case 'Q':
            {
                piece = std::make_shared<Queen>(x, y, Color::BLACK);
                auto function_diags = &PieceHandler::checkDiagonals;
                auto funcion_rows_columns = &PieceHandler::checkRowsAndColumns;
                piece->getMoveFunctions().push_back(std::bind(function_diags, this, std::placeholders::_1,
                                                              std::placeholders::_2, std::placeholders::_3));
                piece->getMoveFunctions().push_back(std::bind(funcion_rows_columns, this,
                                                              std::placeholders::_1, std::placeholders::_2,
                                                              std::placeholders::_3));
                break;
            }
            case 'k':
                piece = std::make_shared<Roi>(x, y, Color::WHITE);
                break;
            case 'K':
                piece = std::make_shared<Roi>(x, y, Color::BLACK);
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

void PieceHandler::checkDiagonals(std::array<std::array<Tile, 8>, 8> board, Piece::PieceMove &result,
                                  Parser::UpdateCoords coord)
{
    if (coord.to.x - coord.from.x == coord.to.y - coord.from.y)
    {
        for (int i = coord.from.x - 1, j = coord.from.y - 1; i > coord.to.x && j > coord.to.y; i--, j--)
        {
            if (board[i][j].getPiece() != nullptr)
                return;
        }
        result = {true, board[coord.to.x][coord.to.y].getPiece()};
    }
    // check right up diagonal
    else if (coord.from.x - coord.to.x == coord.from.y - coord.to.y)
    {
        for (int i = coord.from.x + 1, j = coord.from.y + 1; i < coord.to.x && j < coord.to.y; i++, j++)
        {
            if (board[i][j].getPiece() != nullptr)
                return;
        }
        result = {true, board[coord.to.x][coord.to.y].getPiece()};
    }
    // check left up diagonal
    else if (coord.to.x - coord.from.x == coord.from.y - coord.to.y)
    {
        for (int i = coord.from.x - 1, j = coord.from.y + 1; i > coord.to.x && j < coord.to.y; i--, j++)
        {
            if (board[i][j].getPiece() != nullptr)
                return;
        }
        result = {true, board[coord.to.x][coord.to.y].getPiece()};
    }
    // check right down diagonal
    else if (coord.from.x - coord.to.x == coord.to.y - coord.from.y)
    {
        for (int i = coord.from.x + 1, j = coord.from.y - 1; i < coord.to.x && j > coord.to.y; i++, j--)
        {
            if (board[i][j].getPiece() != nullptr)
                return;
        }
        result = {true, board[coord.to.x][coord.to.y].getPiece()};
    }
}

void PieceHandler::checkRowsAndColumns(std::array<std::array<Tile, 8>, 8> board, Piece::PieceMove &result,
                                       Parser::UpdateCoords coord)
{
    // Check if the move is horizontal
    if (coord.to.x == coord.from.x)
    {
        // Check if is going up
        if (coord.to.y > coord.from.y)
        {
            // Check if there is a piece in the way
            for (int i = coord.from.y + 1; i < coord.to.y; i++)
            {
                if (board[coord.to.x][i].getPiece() != nullptr)
                    return;
            }
            result = {true, board[coord.to.x][coord.to.y].getPiece()};
        }
        // Check if is going down
        else
        {
            // Check if there is a piece in the way
            for (int i = coord.from.y - 1; i > coord.to.y; i--)
            {
                if (board[coord.to.x][i].getPiece() != nullptr)
                    return;
            }
            result = {true, board[coord.to.x][coord.to.y].getPiece()};
        }
    }
    // Check if the move is vertical
    else if (coord.to.y == coord.from.y)
    {
        // Check if is going right
        if (coord.to.x > coord.from.x)
        {
            // Check if there is a piece in the way
            for (int i = coord.from.x + 1; i < coord.to.x; i++)
            {
                if (board[i][coord.to.y].getPiece() != nullptr)
                    return;
            }
            result = {true, board[coord.to.x][coord.to.y].getPiece()};
        }
        // Check if is going left
        else
        {
            // Check if there is a piece in the way
            for (int i = coord.from.x - 1; i > coord.to.x; i--)
            {
                if (board[i][coord.to.y].getPiece() != nullptr)
                    return;
            }
            result = {true, board[coord.to.x][coord.to.y].getPiece()};
        }
        result = {true, board[coord.to.x][coord.to.y].getPiece()};
    }
}