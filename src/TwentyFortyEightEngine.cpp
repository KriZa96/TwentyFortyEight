#include <random>
#include <vector>

#include "TwentyFortyEightEngine.h"


  TwentyFortyEightEngine::TwentyFortyEightEngine() : 
      gridLength(4),
      grid(gridLength, std::vector<int>(gridLength, 0)),
      score(0),
      gameOver(false),
      gameWon(false),
      gen(rd()) 
  {
    addRandomTile();
    addRandomTile();
  }


std::uint8_t TwentyFortyEightEngine::getGridLength() const { return gridLength; }


void TwentyFortyEightEngine::reset() {
    std::for_each(grid.begin(), grid.end(), [](std::vector<int>& row) {
        std::fill(row.begin(), row.end(), 0);
    });
    score = 0;
    gameOver = false;
    gameWon = false;
    addRandomTile();
    addRandomTile();
}


bool TwentyFortyEightEngine::isGameOver() const { return gameOver; }


bool TwentyFortyEightEngine::isGameWon() const { return gameWon; }


int TwentyFortyEightEngine::getScore() const { return score; }


int TwentyFortyEightEngine::getTileValue(int row, int col) const {
    return grid[row][col];
}

void TwentyFortyEightEngine::addRandomTile() {
    // Getting all empty cells in the grid
    std::vector<std::pair<int, int>> emptyCells;
    for (int i = 0; i < gridLength; i++) {
        for (int j = 0; j < gridLength; j++) {
            if (grid[i][j] == 0) {
                emptyCells.push_back({i, j});
            }
        }
    }

    // If there are no empty cells, we cannot add a new tile
    // But maybe we can still move, so game is not over
    if (emptyCells.empty()) return;

    // Generating a random index for empty cells vector
    std::uniform_int_distribution<> disCells(0, static_cast<int>(emptyCells.size()) - 1);
    int idx = disCells(gen);
    // Getting the row and column of the selected empty cell
    int row = emptyCells[idx].first;
    int col = emptyCells[idx].second;

    // Generating a random value (2 or 4) to place in the selected cell
    // 90% chance for 2, 10% chance for 4
    std::uniform_int_distribution<> disValue(1, 10);
    grid[row][col] = (disValue(gen) <= 9) ? 2 : 4;
}


bool TwentyFortyEightEngine::canMove() const {
    for (int i = 0; i < gridLength; i++) {
        for (int j = 0; j < gridLength; j++) {
            // If there is empty cell we can move
            if (grid[i][j] == 0) return true;
            // if there are mergable cells in some column we can merge
            if (i < gridLength - 1 && grid[i][j] == grid[i + 1][j]) return true;
            // if there are mergable cells in some row we can merge
            if (j < gridLength - 1 && grid[i][j] == grid[i][j + 1]) return true;
        }
    }
    return false;
}


void TwentyFortyEightEngine::processMove(Direction direction) {
    bool moved = false;
    switch (direction) {
        case LEFT:
            moved = moveLeft();
            break;
        case RIGHT:
            moved = moveRight();
            break;
        case UP:
            moved = moveUp();
            break;
        case DOWN:
            moved = moveDown();
            break;
    }

    if (moved) {
        addRandomTile();
        if (!canMove()) {
            gameOver = true;
        }
    }
}


bool TwentyFortyEightEngine::moveLeft() {
    bool moved = false;
    for (int i = 0; i < gridLength; i++) {
        for (int j = 0; j < gridLength; j++) {
            if (grid[i][j] != 0) {
                int col = j;
                while (col > 0 && grid[i][col - 1] == 0) {
                    grid[i][col - 1] = grid[i][col];
                    grid[i][col] = 0;
                    col--;
                    moved = true;
                }
                if (col > 0 && grid[i][col - 1] == grid[i][col]) {
                    grid[i][col - 1] *= 2;
                    score += grid[i][col - 1];
                    if (grid[i][col - 1] == 2048) gameWon = true;
                    grid[i][col] = 0;
                    moved = true;
                }
            }
        }
    }
    return moved;
}


bool TwentyFortyEightEngine::moveRight() {
    bool moved = false;
    for (int i = 0; i < gridLength; i++) {
        for (int j = gridLength - 2; j >= 0; j--) {
            if (grid[i][j] != 0) {
                int col = j;
                while (col < gridLength - 1 && grid[i][col + 1] == 0) {
                    grid[i][col + 1] = grid[i][col];
                    grid[i][col] = 0;
                    col++;
                    moved = true;
                }
                if (col < gridLength - 1 && grid[i][col + 1] == grid[i][col]) {
                    grid[i][col + 1] *= 2;
                    score += grid[i][col + 1];
                    if (grid[i][col + 1] == 2048) gameWon = true;
                    grid[i][col] = 0;
                    moved = true;
                }
            }
        }
    }
    return moved;
}


bool TwentyFortyEightEngine::moveUp() {
    bool moved = false;
    for (int j = 0; j < gridLength; j++) {
        for (int i = 0; i < gridLength; i++) {
            if (grid[i][j] != 0) {
                int row = i;
                while (row > 0 && grid[row - 1][j] == 0) {
                    grid[row - 1][j] = grid[row][j];
                    grid[row][j] = 0;
                    row--;
                    moved = true;
                }
                if (row > 0 && grid[row - 1][j] == grid[row][j]) {
                    grid[row - 1][j] *= 2;
                    score += grid[row - 1][j];
                    if (grid[row - 1][j] == 2048) gameWon = true;
                    grid[row][j] = 0;
                    moved = true;
                }
            }
        }
    }
    return moved;
}


bool TwentyFortyEightEngine::moveDown() {
    bool moved = false;
    for (int j = 0; j < gridLength; j++) {
        for (int i = gridLength - 2; i >= 0; i--) {
            if (grid[i][j] != 0) {
                int row = i;
                while (row < gridLength - 1 && grid[row + 1][j] == 0) {
                    grid[row + 1][j] = grid[row][j];
                    grid[row][j] = 0;
                    row++;
                    moved = true;
                }
                if (row < gridLength - 1 && grid[row + 1][j] == grid[row][j]) {
                    grid[row + 1][j] *= 2;
                    score += grid[row + 1][j];
                    if (grid[row + 1][j] == 2048) gameWon = true;
                    grid[row][j] = 0;
                    moved = true;
                }
            }
        }
    }
    return moved;
}