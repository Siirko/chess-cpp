#pragma once
#include "../../game.hpp"

class CLI : public Game
{
  public:
    CLI();
    ~CLI();
    void run() override;
    void promotePawn(std::shared_ptr<Piece> &toPromote) override;
};