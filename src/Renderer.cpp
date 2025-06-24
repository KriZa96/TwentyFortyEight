#pragma once

#include "Config.h"
#include "Renderer.h"
#include <format>


Renderer::Renderer(TwentyFortyEightEngine& game, int windowWidth, int windowHeight) :
    windowWidth_(windowWidth),
    windowHeight_(windowHeight),
    game_(game),
    tileRenderer_(
        windowHeight / TileRenderConfig::TILE_SIZE_DIVISOR,
        windowHeight / TileRenderConfig::TILE_SIZE_DIVISOR / TileRenderConfig::TILE_PADDING_DIVISOR
    ) {}


void Renderer::renderGame() const {
    setupGameWindow();
    renderGameControls();

    const ImVec2 gridStartPos = calculateGridStartPosition();
    renderGameGrid(gridStartPos);
    renderGameStatus(gridStartPos);
    renderScoreText(gridStartPos);
    renderInfoText(gridStartPos);

    ImGui::End();
}


void Renderer::setupGameWindow() const {
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(windowWidth_, windowHeight_));
    ImGui::Begin(DisplayConfig::WINDOW_TITLE, nullptr, ImGuiWindowFlags_NoDecoration);
    ImGui::SetWindowFontScale(UIConfig::WINDOW_FONT_SCALE);
}


void Renderer::renderGameControls() const {
    const ImVec2 buttonSize(windowWidth_ * UIConfig::BUTTON_WIDTH_RATIO, windowHeight_ * UIConfig::BUTTON_HEIGHT_RATIO);
    ImGui::SetCursorPos(
        ImVec2(windowWidth_ / 2 - windowWidth_ * (UIConfig::BUTTON_WIDTH_RATIO + UIConfig::BUTTON_SPACING_RATIO / 2), 
        windowHeight_ * UIConfig::VERTICAL_SPACING_RATIO
    ));
    
    if (ImGui::Button(UIConfig::NEW_GAME_BUTTON_TEXT, buttonSize)) game_.reset();
    ImGui::SameLine();
    ImGui::Dummy(ImVec2(windowWidth_ * UIConfig::BUTTON_SPACING_RATIO, 0));
    ImGui::SameLine();
    if (ImGui::Button(UIConfig::EXIT_BUTTON_TEXT, buttonSize)) exit(0);

    ImGui::Dummy(ImVec2(0, windowHeight_ * UIConfig::VERTICAL_SPACING_RATIO));
    ImGui::Separator();
}


void Renderer::renderScoreText(const ImVec2& gridStartPos) const {
  std::string scoreText =
      std::format(UIConfig::SCORE_TEXT_FORMAT, game_.getScore());
  const float verticalOffset =
      gridStartPos.y - (tileRenderer_.getTilePaddingSize() *
                        TileRenderConfig::SCORE_TEXT_OFFSET);

  renderCenteredText(scoreText.c_str(), UIConfig::LIGHT_TEXT, verticalOffset);
}


void Renderer::renderInfoText(const ImVec2& gridStartPos) const {
  const float verticalOffset = gridStartPos.y - (tileRenderer_.getTilePaddingSize() * TileRenderConfig::INFO_TEXT_OFFSET);
  renderCenteredText(UIConfig::INSTRUCTION_TEXT, UIConfig::LIGHT_TEXT, verticalOffset);
}


void Renderer::renderGameGrid(const ImVec2& gridStartPos) const {
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    const ImVec2 gridEndPos(
        gridStartPos.x +
            (tileRenderer_.getTileSize() + tileRenderer_.getTilePaddingSize()) *
                game_.getGridLength() +
            tileRenderer_.getTilePaddingSize(),
        gridStartPos.y +
            (tileRenderer_.getTileSize() + tileRenderer_.getTilePaddingSize()) *
                game_.getGridLength() +
            tileRenderer_.getTilePaddingSize()
    );
    drawList->AddRectFilled(
        gridStartPos, 
        gridEndPos,
        ImGui::ColorConvertFloat4ToU32(DisplayConfig::GRID_BACKGROUND_COLOR)
    );

    for (int row = 0; row < game_.getGridLength(); row++) {
        for (int col = 0; col < game_.getGridLength(); col++) {
            tileRenderer_.renderTile(game_.getTileValue(row, col), gridStartPos, row, col);
        }
    }
}

void Renderer::renderGameStatus(const ImVec2& gridStartPos) const {
    if (!game_.isGameOver() && !game_.isGameWon()) return;

    const float verticalOffset = 
        gridStartPos.y + tileRenderer_.getTileSize() * game_.getGridLength() +
        tileRenderer_.getTilePaddingSize() * (game_.getGridLength() + TileRenderConfig::STATUS_TEXT_OFFSET);

    const char* statusText = game_.isGameOver() ? UIConfig::GAME_OVER_TEXT : UIConfig::GAME_WIN_TEXT;
    const ImVec4 statusColor = game_.isGameOver() ? UIConfig::GAME_OVER_COLOR : UIConfig::GAME_WIN_COLOR;

    renderCenteredText(statusText, statusColor, verticalOffset);

    const char* message = game_.isGameOver() ? UIConfig::GAME_OVER_MESSAGE : UIConfig::GAME_WIN_MESSAGE;

    renderCenteredText(
        message, 
        UIConfig::LIGHT_TEXT,
        verticalOffset + tileRenderer_.getTilePaddingSize() * (game_.getGridLength() - 1)
    );
}

void Renderer::renderCenteredText(const char* text, const ImVec4& color, float yPos) const {
    ImGui::SetCursorPos(ImVec2(windowWidth_ / 2 - ImGui::CalcTextSize(text).x / 2, yPos));
    ImGui::TextColored(color, text);
}

ImVec2 Renderer::calculateGridStartPosition() const {
    ImVec2 startPos = ImGui::GetCursorScreenPos();

    const float gridSize =
        game_.getGridLength() * tileRenderer_.getTileSize() +
        (game_.getGridLength() + 1) * tileRenderer_.getTilePaddingSize();

    startPos.y += (windowHeight_ * UIConfig::GRID_AREA_RATIO - gridSize) / 2.f;
    startPos.x += (windowWidth_ - gridSize) / 2.f;

    return startPos;
}