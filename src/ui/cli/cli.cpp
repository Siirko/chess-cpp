#include "../../../includes/ui/cli/cli.hpp"
#include "../../../includes/gameruler.hpp"
#include "../../../includes/pieces/piece.hpp"
#include "../../../includes/ui/cli/parser.hpp"

#include <iostream>
#include <memory>
#include <vector>

CLI::CLI() : Game() {}

CLI::~CLI() {}

void CLI::run()
{
    std::cout << "Game running" << std::endl;
    std::cout << *this << std::endl;
    std::string input;
    do
    {
        if (input.empty())
            continue;
        Parser::UpdateCoords coords = Parser::parseInput(input, (Color)this->getTurn());
        std::shared_ptr<Piece> piece =
            this->getPieceHandler().getPieceAt(*this, coords.from.x, coords.from.y);
        if (piece != nullptr && piece->getColor() == this->getTurn())
        {
            if (this->getPieceHandler().movePieceAt(*this, piece, coords.to.x, coords.to.y))
            {
                this->updateTurn();
                this->updateNumTurns();
                std::cout << *this << std::flush;
                this->setCheck(GameRuler::getInstance().isKingInCheck(this->getBoard().getArray(),
                                                                      (Color)this->getTurn()));
                this->setCheckMate(GameRuler::getInstance().isKingInCheckMate(this->getBoard().getArray(),
                                                                              (Color)this->getTurn()));
                this->setStaleMate(GameRuler::getInstance().isKingInStaleMate(this->getBoard().getArray(),
                                                                              (Color)this->getTurn()));
                if (this->getCheckMate())
                    break;
                if (this->getStaleMate())
                    break;
            }
        }
        else if (piece == nullptr)
        {
            std::cout << "No piece at this position" << std::endl;
        }
        else if (piece->getColor() != this->getTurn())
        {
            std::cout << (piece->getColor() == Color::WHITE ? "BLACK" : "WHITE") << " turn" << std::endl;
        }
    } while ((input = Parser::getInput()) != "/exit" && this->getCheckMate() != true);
    if (this->getCheckMate())
    {
        std::string color = this->getTurn() == Color::BLACK ? "WHITE" : "BLACK";
        std::cout << "Checkmate, " << color << " Won !" << std::endl;
    }
    else if (this->getStaleMate())
        std::cout << "Stalemate, Draw !" << std::endl;
}