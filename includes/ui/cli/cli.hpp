#pragma once
#include "../../game.hpp"
/**
 * @brief CLI class is responsible for handling the command line interface.
 */
class CLI : public Game
{
  public:
    CLI();
    ~CLI();
    void run() override;
    void promotePawn(std::shared_ptr<Piece> &toPromote) override;
};