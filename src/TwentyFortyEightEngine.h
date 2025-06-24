#pragma once

#include <random>
#include <vector>


class TwentyFortyEightEngine {
public:
	TwentyFortyEightEngine();

	enum Direction { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3 };
	void reset();
	bool isGameOver() const;
	bool isGameWon() const;
	int getScore() const;
	int getTileValue(int row, int col) const;
	void processMove(Direction direction);
	std::uint8_t getGridLength() const;

private:
	const std::uint8_t gridLength;
	std::vector<std::vector<int>> grid;
	int score;
	bool gameOver;
	bool gameWon;
	std::random_device rd;
	std::mt19937 gen;

	void addRandomTile();
	bool canMove() const;
    bool makeMove(Direction direction);
    bool isValidPosition(int row, int col);
};