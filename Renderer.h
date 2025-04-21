#pragma once

#include <functional>

#include "TwentyFortyEight.h"
#include "imgui.h"

class Renderer {
 private:
  struct TileStyle {
    ImVec4 background;
    ImVec4 text;
  };

  TileStyle getTileStyle(int value) {
    return {getTileColor(value), getTextColor(value)};
  }

  ImVec4 getTileColor(int value) {
    switch (value) {
      case 0:
        return ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
      case 2:
        return ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
      case 4:
        return ImVec4(0.9f, 0.9f, 0.8f, 1.0f);
      case 8:
        return ImVec4(0.9f, 0.8f, 0.7f, 1.0f);
      case 16:
        return ImVec4(0.9f, 0.7f, 0.5f, 1.0f);
      case 32:
        return ImVec4(0.9f, 0.6f, 0.4f, 1.0f);
      case 64:
        return ImVec4(0.9f, 0.5f, 0.3f, 1.0f);
      case 128:
        return ImVec4(0.9f, 0.4f, 0.2f, 1.0f);
      case 256:
        return ImVec4(0.9f, 0.3f, 0.1f, 1.0f);
      case 512:
        return ImVec4(0.9f, 0.2f, 0.1f, 1.0f);
      case 1024:
        return ImVec4(0.9f, 0.1f, 0.1f, 1.0f);
      case 2048:
        return ImVec4(0.9f, 0.0f, 0.0f, 1.0f);
      default:
        return ImVec4(0.8f, 0.0f, 0.0f, 1.0f);
    }
  }

  ImVec4 getTextColor(int value) {
    return value <= 4 ? ImVec4(0.2f, 0.2f, 0.2f, 1.0f)
                      : ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
  }

  void setupGameWindow(int width, int height) {
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin("2048 Game", nullptr,
                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowFontScale(4);
  }

  void renderGameControls(TwentyFortyEight& game, int width, int height,
                          std::function<void()> resetCallback) {
    ImGui::Dummy(ImVec2(0, height * 0.02f));
    ImGui::Text("Score: %d", game.getScore());

    const ImVec2 buttonSize(width * 0.10f, height * 0.05f);
    ImGui::SameLine();
    if (ImGui::Button("New Game", buttonSize)) resetCallback();

    ImGui::SameLine();
    if (ImGui::Button("Exit", buttonSize)) exit(0);

    ImGui::SameLine();
    ImGui::Text("Use arrow keys to move tiles");
    ImGui::Dummy(ImVec2(0, height * 0.02f));
    ImGui::Separator();
  }

  void renderGameGrid(const TwentyFortyEight& game, const ImVec2& gridStartPos,
                      float tileSize, float padding) {
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    // Draw grid background
    const ImVec2 gridEndPos(
        gridStartPos.x + (tileSize + padding) * 4 + padding,
        gridStartPos.y + (tileSize + padding) * 4 + padding);
    drawList->AddRectFilled(gridStartPos, gridEndPos,
                            IM_COL32(187, 173, 160, 255));

    // Draw tiles
    for (int row = 0; row < 4; row++) {
      for (int col = 0; col < 4; col++) {
        renderTile(game.getTileValue(row, col), gridStartPos, tileSize, padding,
                   row, col);
      }
    }
  }

  void renderTile(int value, const ImVec2& gridStartPos, float tileSize,
                  float padding, int row, int col) {
    const TileStyle style = getTileStyle(value);
    const ImVec2 tilePos =
        calculateTilePosition(gridStartPos, tileSize, padding, row, col);
    const ImVec2 tileEndPos(tilePos.x + tileSize, tilePos.y + tileSize);

    // Draw tile background
    ImGui::GetWindowDrawList()->AddRectFilled(
        tilePos, tileEndPos, ImGui::ColorConvertFloat4ToU32(style.background),
        5.0f);

    if (value > 0) {
      renderTileValue(value, tilePos, tileSize, style.text);
    }
  }

  ImVec2 calculateTilePosition(const ImVec2& gridStartPos, float tileSize,
                               float padding, int row, int col) {
    return ImVec2(gridStartPos.x + col * (tileSize + padding) + padding,
                  gridStartPos.y + row * (tileSize + padding) + padding);
  }

  void renderTileValue(int value, const ImVec2& tilePos, float tileSize,
                       const ImVec4& textColor) {
    char buffer[16];
    sprintf_s(buffer, sizeof(buffer), "%d", value);

    ImFont* font = ImGui::GetFont();
    const float fontSize = calculateFontSize(value, tileSize);
    const ImVec2 textSize =
        font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, buffer);
    const ImVec2 textPosition = centerTextInTile(tilePos, tileSize, textSize);

    ImGui::GetWindowDrawList()->AddText(
        font, fontSize, textPosition, ImGui::ColorConvertFloat4ToU32(textColor),
        buffer);
  }

  float calculateFontSize(int value, float tileSize) {
    if (value < 100) return tileSize / 3.0f;
    if (value < 1000) return tileSize / 3.5f;
    return tileSize / 4.0f;
  }

  ImVec2 centerTextInTile(const ImVec2& tilePos, float tileSize,
                          const ImVec2& textSize) {
    return ImVec2(tilePos.x + (tileSize - textSize.x) * 0.5f,
                  tilePos.y + (tileSize - textSize.y) * 0.5f);
  }

  void renderGameStatus(const TwentyFortyEight& game,
                        const ImVec2& gridStartPos, float gridSize,
                        float padding, int windowWidth) {
    if (!game.isGameOver() && !game.isGameWon()) return;

    const float verticalOffset = gridStartPos.y + gridSize + padding * 7;
    const char* statusText = game.isGameOver() ? "Game Over!" : "You Win!";
    const ImVec4 statusColor = game.isGameOver()
                                   ? ImVec4(1.0f, 0.0f, 0.0f, 1.0f)
                                   : ImVec4(0.0f, 1.0f, 0.0f, 1.0f);

    renderCenteredText(statusText, statusColor, verticalOffset, windowWidth);

    const char* message =
        game.isGameOver()
            ? "Press 'New Game' to play again."
            : "Continue playing or press 'New Game' to start over.";
    renderCenteredText(message, ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
                       verticalOffset + padding * 3, windowWidth);
  }

  void renderCenteredText(const char* text, const ImVec4& color, float yPos,
                          int windowWidth) {
    ImGui::SetCursorPos(
        ImVec2(windowWidth / 2 - ImGui::CalcTextSize(text).x / 2, yPos));
    ImGui::TextColored(color, text);
  }

 public:
  void renderGame(TwentyFortyEight& game, std::function<void()> resetCallback,
                  int width, int height) {
    setupGameWindow(width, height);
    renderGameControls(game, width, height, resetCallback);

    const float tileSize = height / 8.0f;
    const float padding = tileSize / 8.0f;
    const ImVec2 gridStartPos =
        calculateGridStartPosition(width, height, tileSize, padding);

    renderGameGrid(game, gridStartPos, tileSize, padding);
    renderGameStatus(game, gridStartPos, tileSize * 4, padding, width);

    ImGui::End();
  }

 private:
  ImVec2 calculateGridStartPosition(int windowWidth, int windowHeight,
                                    float tileSize, float padding) {
    ImVec2 startPos = ImGui::GetCursorScreenPos();
    const float gridSize = 4 * tileSize + 5 * padding;
    startPos.y += (windowHeight * 0.8f - gridSize) / 2.f;
    startPos.x += (windowWidth - gridSize) / 2.f;
    return startPos;
  }
};