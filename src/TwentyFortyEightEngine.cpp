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
  bool moved = makeMove(direction);
  if (moved) {
    addRandomTile();
    if (!canMove()) {
      gameOver = true;
    }
  }
}


bool TwentyFortyEightEngine::isValidPosition(int row, int col) {
  return row >= 0 && row < gridLength && col >= 0 && col < gridLength;
}


bool TwentyFortyEightEngine::makeMove(Direction direction) {
  bool moved = false;

  int rowDirection = 0, columnDirection = 0;
  int startRow = 0, endRow = gridLength, stepRow = 1;
  int startCol = 0, endCol = gridLength, stepCol = 1;

  switch (direction) {
    case LEFT:
      rowDirection = 0, columnDirection = -1;
      break;
    case RIGHT:
      rowDirection = 0, columnDirection = 1;
      startCol = gridLength - 2, endCol = -1, stepCol = -1;
      break;
    case UP:
      rowDirection = -1, columnDirection = 0;
      break;
    case DOWN:
      rowDirection = 1, columnDirection = 0;
      startRow = gridLength - 2, endRow = -1, stepRow = -1;
      break;
  }

  for (int i = startRow; i != endRow; i += stepRow) {
    for (int j = startCol; j != endCol; j += stepCol) {
      if (grid[i][j] != 0) {
        int row = i, col = j;

        // Slide tile as far as possible
        while (
            isValidPosition(row + rowDirection, col + columnDirection) &&
            grid[row + rowDirection][col + columnDirection] == 0
        ) 
        {
            grid[row + rowDirection][col + columnDirection] = grid[row][col];
            grid[row][col] = 0;
            row += rowDirection;
            col += columnDirection;
            moved = true;
        }

        // Checking for merge
        if (
            isValidPosition(row + rowDirection, col + columnDirection) &&
            grid[row + rowDirection][col + columnDirection] == grid[row][col]
        ) 
        {
            grid[row + rowDirection][col + columnDirection] *= 2;
            score += grid[row + rowDirection][col + columnDirection];
            // If the merged tile is 2048, set gameWon to true, that does not
            // end the game, but allows to display a win message
            if (grid[row + rowDirection][col + columnDirection] == 2048) gameWon = true;
            grid[row][col] = 0;
            moved = true;
        }
      }
    }
  }

  return moved;
}
