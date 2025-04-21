#include <random>
#include <vector>

#include "TwentyFortyEightEngine.h"


  TwentyFortyEightEngine::TwentyFortyEightEngine()
      : grid_size_(4),
        grid(grid_size_, std::vector<int>(grid_size_, 0)),
        score(0),
        gameOver(false),
        gameWon(false),
        gen(rd()) {
    addRandomTile();
    addRandomTile();
  }

  void TwentyFortyEightEngine::reset() {
    for (int i = 0; i < grid_size_; i++) {
      for (int j = 0; j < grid_size_; j++) {
        grid[i][j] = 0;
      }
    }
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
    std::vector<std::pair<int, int>> emptyCells;
    for (int i = 0; i < grid_size_; i++) {
      for (int j = 0; j < grid_size_; j++) {
        if (grid[i][j] == 0) {
          emptyCells.push_back({i, j});
        }
      }
    }

    if (emptyCells.empty()) return;

    std::uniform_int_distribution<> disCells(
        0, static_cast<int>(emptyCells.size()) - 1);
    std::uniform_int_distribution<> disValue(1, 10);

    int idx = disCells(gen);
    int row = emptyCells[idx].first;
    int col = emptyCells[idx].second;

    grid[row][col] = (disValue(gen) <= 9) ? 2 : 4;
  }

  bool TwentyFortyEightEngine::canMove() {
    for (int i = 0; i < grid_size_; i++) {
      for (int j = 0; j < grid_size_; j++) {
        if (grid[i][j] == 0) return true;
      }
    }

    for (int i = 0; i < grid_size_; i++) {
      for (int j = 0; j < grid_size_ - 1; j++) {
        if (grid[i][j] == grid[i][j + 1]) return true;
      }
    }

    for (int i = 0; i < grid_size_ - 1; i++) {
      for (int j = 0; j < grid_size_; j++) {
        if (grid[i][j] == grid[i + 1][j]) return true;
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
    for (int i = 0; i < grid_size_; i++) {
      for (int j = 0; j < grid_size_; j++) {
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
    for (int i = 0; i < grid_size_; i++) {
      for (int j = grid_size_ - 2; j >= 0; j--) {
        if (grid[i][j] != 0) {
          int col = j;
          while (col < grid_size_ - 1 && grid[i][col + 1] == 0) {
            grid[i][col + 1] = grid[i][col];
            grid[i][col] = 0;
            col++;
            moved = true;
          }
          if (col < grid_size_ - 1 && grid[i][col + 1] == grid[i][col]) {
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
    for (int j = 0; j < grid_size_; j++) {
      for (int i = 0; i < grid_size_; i++) {
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
    for (int j = 0; j < grid_size_; j++) {
      for (int i = grid_size_ - 2; i >= 0; i--) {
        if (grid[i][j] != 0) {
          int row = i;
          while (row < grid_size_ - 1 && grid[row + 1][j] == 0) {
            grid[row + 1][j] = grid[row][j];
            grid[row][j] = 0;
            row++;
            moved = true;
          }
          if (row < grid_size_ - 1 && grid[row + 1][j] == grid[row][j]) {
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