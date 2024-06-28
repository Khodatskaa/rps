#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>

enum class Move { ROCK, PAPER, SCISSORS, INVALID };

class Game {
public:
    Game(int rounds);
    void playRound(Move player1Move, Move player2Move);
    std::string getResult() const;
    bool isGameOver() const;
    void displayStats() const;

private:
    int totalRounds;
    int currentRound;
    int player1Score;
    int player2Score;
    std::vector<std::string> roundsResults;

    Move getMoveFromString(const std::string& moveStr) const;
    std::string moveToString(Move move) const;
};

#endif // GAME_H
