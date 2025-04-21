#pragma once

#include <random>
#include <vector>


class TwentyFortyEight {
 private:
  std::uint8_t grid_size_;
  std::vector<std::vector<int>> grid;
  int score;
  bool gameOver;
  bool gameWon;
  std::random_device rd;
  std::mt19937 gen;

 public:
  enum Direction { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3 };

  TwentyFortyEight()
      : grid_size_(4),
        grid(grid_size_, std::vector<int>(grid_size_, 0)),
        score(0),
        gameOver(false),
        gameWon(false),
        gen(rd()) {
    addRandomTile();
    addRandomTile();
  }

  void reset() {
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

  bool isGameOver() const { return gameOver; }
  bool isGameWon() const { return gameWon; }
  int getScore() const { return score; }
  int getTileValue(int row, int col) const { return grid[row][col]; }

  void addRandomTile() {
    std::vector<std::pair<int, int>> emptyCells;
    for (int i = 0; i < grid_size_; i++) {
      for (int j = 0; j < grid_size_; j++) {
        if (grid[i][j] == 0) {
          emptyCells.push_back({i, j});
        }
      }
    }

    if (emptyCells.empty()) return;

    std::uniform_int_distribution<> disCells(0, static_cast<int>(emptyCells.size()) - 1);
    std::uniform_int_distribution<> disValue(1, 10);

    int idx = disCells(gen);
    int row = emptyCells[idx].first;
    int col = emptyCells[idx].second;

    grid[row][col] = (disValue(gen) <= 9) ? 2 : 4;
  }

  bool canMove() {
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

  void processMove(Direction direction) {
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

 private:
  bool moveLeft() {
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

  bool moveRight() {
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

  bool moveUp() {
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

  bool moveDown() {
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
};