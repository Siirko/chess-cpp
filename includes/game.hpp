#pragma once
#include "board/board.hpp"
#include "piecehandler.hpp"
#include "pieces/king.hpp"
#include "pieces/pawn.hpp"
#include "pieces/piece.hpp"
#include <array>
#include <memory>
#include <vector>
/**
 * @brief Game class is the base class for CLI and GUI games.
 * @note This class is abstract.
 */
class Game
{
  private:
    Board board;
    PieceHandler piece_handler;
    // 0 black, 1 white
    int turn;
    int num_turns;
    bool check;
    bool checkMate;
    bool staleMate;
    bool resigned;
    bool draw;
    std::vector<std::shared_ptr<Piece>> black_eaten_pieces;
    std::vector<std::shared_ptr<Piece>> white_eaten_pieces;
    std::vector<std::shared_ptr<Piece>> alive_pieces;
    void init();

  public:
    Game();
    virtual ~Game();
    /**
     * @brief Runs the game.
     * @note entry point for the game.
     */
    virtual void run() = 0;
    /**
     * @brief Promotes the pawn to the given piece.
     * @param toPromote The pawn to promote.
     * @note This function is virtual so that it can be overridden in the CLI and GUI games.
     */
    virtual void promotePawn(std::shared_ptr<Piece> &toPromote) = 0;
    /**
     * @brief Get the White King piece
     * @return The White King piece
     */
    std::shared_ptr<King> getWhiteKing() const;
    /**
     * @brief Get the Black King piece
     * @return The Black King piece
     */
    std::shared_ptr<King> getBlackKing() const;
    /**
     * @brief Get alive pieces from current game
     * @return Alive pieces from current game
     */
    std::vector<std::shared_ptr<Piece>> getAlivePieces() const;
    /**
     * @brief Get eaten pieces from Black player
     * @return Eaten pieces from Black player
     */
    std::vector<std::shared_ptr<Piece>> &getBlackEatenPieces();
    /**
     * @brief Get eaten pieces from White player
     * @return Eaten pieces from White player
     */
    std::vector<std::shared_ptr<Piece>> &getWhiteEatenPieces();
    /**
     * @brief Get board reference from current game
     * @return Board from current game
     */
    Board &getBoard();
    /**
     * @brief Get board from current game
     * @return Board from current game
     */
    Board getBoard() const;
    /**
     * @brief Get piece handler reference from current game
     * @return Piece handler from current game
     */
    PieceHandler &getPieceHandler();
    /**
     * @brief Get piece handler from current game
     * @return Piece handler from current game
     */
    PieceHandler getPieceHandler() const;
    /**
     * @brief Get whose turn it is from current game
     * @return 0 if it is Black's turn, 1 if it is White's turn
     */
    int getTurn() const;
    /**
     * @brief Update whose turn it is from current game
     */
    void updateTurn();
    /**
     * @brief Get number of turns from current game
     * @return Number of turns from current game
     */
    int getNumTurns() const;
    /**
     * @brief Update number of turns from current game
     */
    void updateNumTurns();
    /**
     * @brief Get the Check status from current game
     * @return True if there is a check, false otherwise
     */
    bool getCheck() const;
    /**
     * @brief Get the Check status from current game
     * @param color The color of the player to check
     * @return True if there is a check, false otherwise
     */
    bool getCheck(Color color) const { return this->turn == color && this->check; }
    /**
     * @brief Set the Check status from current game
     * @param check The new check status
     */
    void setCheck(bool check);
    /**
     * @brief Get the Check Mate status from current game
     * @return True if there is a check mate, false otherwise
     */
    bool getCheckMate() const;
    /**
     * @brief Set the Check Mate status from current game
     * @param checkMate The new check mate status
     */
    void setCheckMate(bool checkMate);
    /**
     * @brief Get the Stale Mate status from current game
     * @return True if there is a stale mate, false otherwise
     */
    bool getStaleMate() const;
    /**
     * @brief Set the Stale Mate status from current game
     * @param staleMate The new stale mate status
     */
    void setStaleMate(bool staleMate);
    /**
     * @brief Add a piece to the alive pieces list
     * @param piece The piece to add
     */
    void addAlivePiece(std::shared_ptr<Piece> piece);
    /**
     * @brief Remove a piece from the alive pieces list
     * @param piece The piece to remove
     */
    void removeAlivePiece(std::shared_ptr<Piece> piece);
    /**
     * @brief Return a snapshot of the current game state as a string
     */
    std::string endResult() const;
    /**
     * @brief Update the status of the game
     */
    void updateStatus();
    bool getResigned() const { return this->resigned; }
    bool getDraw() const { return this->draw; }
    void setResigned() { this->resigned = true; }
    void setDraw() { this->draw = true; }
    Color whoResigned() const;
    friend std::ostream &operator<<(std::ostream &os, const Game &game);
};