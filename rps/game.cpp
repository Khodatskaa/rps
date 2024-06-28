#include "game.h"

Game::Game(int rounds) : totalRounds(rounds), currentRound(0), player1Score(0), player2Score(0) {}

void Game::playRound(Move player1Move, Move player2Move) {
    std::string result;

    if (player1Move == player2Move) {
        result = "Draw";
    }
    else if ((player1Move == Move::ROCK && player2Move == Move::SCISSORS) ||
        (player1Move == Move::PAPER && player2Move == Move::ROCK) ||
        (player1Move == Move::SCISSORS && player2Move == Move::PAPER)) {
        result = "Player 1 wins";
        player1Score++;
    }
    else {
        result = "Player 2 wins";
        player2Score++;
    }

    roundsResults.push_back("Round " + std::to_string(currentRound + 1) + ": " + moveToString(player1Move) + " vs " + moveToString(player2Move) + " -> " + result);
    currentRound++;
}

std::string Game::getResult() const {
    if (player1Score > player2Score) {
        return "Player 1 wins the game!";
    }
    else if (player2Score > player1Score) {
        return "Player 2 wins the game!";
    }
    else {
        return "The game is a draw!";
    }
}

bool Game::isGameOver() const {
    return currentRound >= totalRounds;
}

void Game::displayStats() const {
    for (const auto& result : roundsResults) {
        std::cout << result << std::endl;
    }
    std::cout << "Final Result: " << getResult() << std::endl;
}

Move Game::getMoveFromString(const std::string& moveStr) const {
    if (moveStr == "rock") return Move::ROCK;
    if (moveStr == "paper") return Move::PAPER;
    if (moveStr == "scissors") return Move::SCISSORS;
    return Move::INVALID;
}

std::string Game::moveToString(Move move) const {
    switch (move) {
    case Move::ROCK: return "rock";
    case Move::PAPER: return "paper";
    case Move::SCISSORS: return "scissors";
    default: return "invalid";
    }
}
