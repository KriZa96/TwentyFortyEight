#pragma once

#include <string>

#include "Config.h"
#include "TileRenderer.h"


TileRenderer::TileRenderer(float tileSize, float tilePadding) : tileSize_(tileSize), tilePaddingSize_(tilePadding) {}


float TileRenderer::getTileSize() const { return tileSize_; }


float TileRenderer::getTilePaddingSize() const { return tilePaddingSize_; }


void TileRenderer::renderTile(int value, const ImVec2& gridStartPos, int row, int col) const {
    const TileStyle style = TileColorConfig::getTileStyle(value);
	const ImVec2 tilePos = calculateTilePosition(gridStartPos, row, col);
	const ImVec2 tileEndPos(tilePos.x + tileSize_, tilePos.y + tileSize_);

	ImGui::GetWindowDrawList()->AddRectFilled(
        tilePos, 
		tileEndPos,
        ImGui::ColorConvertFloat4ToU32(style.background),
        TileRenderConfig::TILE_CORNER_RADIUS
	);

	if (value > 0) renderTileValue(value, tilePos, style.text);
}


ImVec2 TileRenderer::calculateTilePosition(const ImVec2& gridStartPos, int row, int col) const {
	return ImVec2(
		gridStartPos.x + col * (tileSize_ + tilePaddingSize_) + tilePaddingSize_,
		gridStartPos.y + row * (tileSize_ + tilePaddingSize_) + tilePaddingSize_
	);
}


void TileRenderer::renderTileValue(int value, const ImVec2& tilePos, const ImVec4& textColor) const {
	std::string text = std::to_string(value);

	ImFont* font = ImGui::GetFont();
	const float fontSize = calculateFontSize(value);
	const ImVec2 textSize =	font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, text.c_str());
	const ImVec2 textPosition = centerTextInTile(tilePos, textSize);

	ImGui::GetWindowDrawList()->AddText(font, fontSize, textPosition, ImGui::ColorConvertFloat4ToU32(textColor), text.c_str());
}


float TileRenderer::calculateFontSize(int value) const {
  if (value < TileRenderConfig::MEDIUM_FONT_THRESHOLD)
    return tileSize_ / TileRenderConfig::LARGE_FONT_DIVISOR;
  if (value < TileRenderConfig::SMALL_FONT_THRESHOLD)
    return tileSize_ / TileRenderConfig::MEDIUM_FONT_DIVISOR;
  return tileSize_ / TileRenderConfig::SMALL_FONT_DIVISOR;
}


ImVec2 TileRenderer::centerTextInTile(const ImVec2& tilePos, const ImVec2& textSize) const {
	return ImVec2(
		tilePos.x + (tileSize_ - textSize.x) * 0.5f,
		tilePos.y + (tileSize_ - textSize.y) * 0.5f
	);
}
