#pragma once

#include "TileRenderer.h"
#include "TwentyFortyEightEngine.h"
#include "imgui.h"

class Renderer {
public:
    Renderer(TwentyFortyEightEngine& game, int windowWidth, int windowHeight);
    void renderGame() const;

private:
    int windowWidth_;
    int windowHeight_;
    TwentyFortyEightEngine& game_;
    TileRenderer tileRenderer_;

    void renderInfoText(const ImVec2& gridStartPos) const;
    void renderScoreText(const ImVec2& gridStartPos) const;
    void setupGameWindow() const;
    void renderGameControls() const;
    void renderGameGrid(const ImVec2& gridStartPos) const;
    void renderGameStatus(const ImVec2& gridStartPos) const;
    void renderCenteredText(const char* text, const ImVec4& color, float yPos) const;
    ImVec2 calculateGridStartPosition() const;
};