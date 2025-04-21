
#include "Renderer.h"
#include <format>


Renderer::Renderer(std::shared_ptr<TwentyFortyEightEngine> game, int windowWidth, int windowHeight) :
    windowWidth_(windowWidth),
    windowHeight_(windowHeight),
    game_(game),
    tileRenderer_(std::make_unique<TileRenderer>(windowHeight / 8.f, windowHeight / 8.f / 8.f)) 
{}


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
    ImGui::Begin("2048 Game", nullptr, ImGuiWindowFlags_NoDecoration);
    ImGui::SetWindowFontScale(4);
}


void Renderer::renderGameControls() const {
    const ImVec2 buttonSize(windowWidth_ * 0.10f, windowHeight_ * 0.05f);

    ImGui::SetCursorPos(ImVec2(windowWidth_ / 2 - windowWidth_ * 0.105f, windowHeight_ * 0.02f));
    if (ImGui::Button("New Game", buttonSize)) game_->reset();
    ImGui::SameLine();
    ImGui::Dummy(ImVec2(windowWidth_ * 0.02f, 0));
    ImGui::SameLine();
    if (ImGui::Button("Exit", buttonSize)) exit(0);

    ImGui::Dummy(ImVec2(0, windowHeight_ * 0.02f));
    ImGui::Separator();
}


void Renderer::renderScoreText(const ImVec2& gridStartPos) const {
  std::string scoreText = std::format("Score: {}", game_->getScore());
  const float verticalOffset = gridStartPos.y - (tileRenderer_->getTilePaddingSize() * 3);

  renderCenteredText(scoreText.c_str(), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), verticalOffset);
}


void Renderer::renderInfoText(const ImVec2& gridStartPos) const {
  const float verticalOffset = gridStartPos.y - (tileRenderer_->getTilePaddingSize() * 6);

  renderCenteredText("Use arrow keys to move tiles",
                     ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
                     verticalOffset);
}


void Renderer::renderGameGrid(const ImVec2& gridStartPos) const {
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    const ImVec2 gridEndPos(
        gridStartPos.x +
            (tileRenderer_->getTileSize() + tileRenderer_->getTilePaddingSize()) *
                game_->getGridLength() +
            tileRenderer_->getTilePaddingSize(),
        gridStartPos.y +
            (tileRenderer_->getTileSize() + tileRenderer_->getTilePaddingSize()) *
                game_->getGridLength() +
            tileRenderer_->getTilePaddingSize()
    );
    drawList->AddRectFilled(gridStartPos, gridEndPos, IM_COL32(187, 173, 160, 255));

    for (int row = 0; row < game_->getGridLength(); row++) {
        for (int col = 0; col < game_->getGridLength(); col++) {
            tileRenderer_->renderTile(game_->getTileValue(row, col), gridStartPos, row, col);
        }
    }
}

void Renderer::renderGameStatus(const ImVec2& gridStartPos) const {
    if (!game_->isGameOver() && !game_->isGameWon()) return;

    const float verticalOffset = 
        gridStartPos.y + tileRenderer_->getTileSize() * game_->getGridLength() +
        tileRenderer_->getTilePaddingSize() * (game_->getGridLength() + 2);

    const char* statusText = game_->isGameOver() ? "Game Over!" : "You Win!";
    const ImVec4 statusColor = game_->isGameOver()
                                    ? ImVec4(1.0f, 0.0f, 0.0f, 1.0f)
                                    : ImVec4(0.0f, 1.0f, 0.0f, 1.0f);

    renderCenteredText(statusText, statusColor, verticalOffset);

    const char* message =
        game_->isGameOver()
            ? "Press 'New Game' to play again."
            : "Continue playing or press 'New Game' to start over.";

    renderCenteredText(message, ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
                        verticalOffset + tileRenderer_->getTilePaddingSize() * (game_->getGridLength() - 1));
}

void Renderer::renderCenteredText(const char* text, const ImVec4& color, float yPos) const {
    ImGui::SetCursorPos(ImVec2(windowWidth_ / 2 - ImGui::CalcTextSize(text).x / 2, yPos));
    ImGui::TextColored(color, text);
}

ImVec2 Renderer::calculateGridStartPosition() const {
    ImVec2 startPos = ImGui::GetCursorScreenPos();

    const float gridSize =
        game_->getGridLength() * tileRenderer_->getTileSize() +
        (game_->getGridLength() + 1) * tileRenderer_->getTilePaddingSize();

    startPos.y += (windowHeight_ * 0.8f - gridSize) / 2.f;
    startPos.x += (windowWidth_ - gridSize) / 2.f;

    return startPos;
}