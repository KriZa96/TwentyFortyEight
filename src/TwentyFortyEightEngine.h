#pragma once

#include <random>
#include <vector>


class TwentyFortyEightEngine {
public:
	enum Direction { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3 };

	TwentyFortyEightEngine();

	void reset();
    bool isGameOver() const;
    bool isGameWon() const;
	int getScore() const;
	int getTileValue(int row, int col) const;
	void processMove(Direction direction);
    std::uint8_t getGridLength() const;

private:
	std::uint8_t gridLength;
	std::vector<std::vector<int>> grid;
	int score;
	bool gameOver;
	bool gameWon;
	std::random_device rd;
	std::mt19937 gen;

	void addRandomTile();
	bool canMove() const;
	bool moveLeft();
	bool moveRight();
	bool moveUp();
	bool moveDown();
};