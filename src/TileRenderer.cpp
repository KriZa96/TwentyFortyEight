
#include <string>

#include "TileRenderer.h"


TileRenderer::TileRenderer(float tileSize, float tilePadding) : tileSize_(tileSize), tilePaddingSize_(tilePadding) {}


float TileRenderer::getTileSize() const { return tileSize_; }


float TileRenderer::getTilePaddingSize() const { return tilePaddingSize_; }


void TileRenderer::renderTile(int value, const ImVec2& gridStartPos, int row, int col) const {
	const TileStyle style = getTileStyle(value);
	const ImVec2 tilePos = calculateTilePosition(gridStartPos, row, col);
	const ImVec2 tileEndPos(tilePos.x + tileSize_, tilePos.y + tileSize_);

	ImGui::GetWindowDrawList()->AddRectFilled(tilePos, tileEndPos, ImGui::ColorConvertFloat4ToU32(style.background), 5.0f);

	if (value > 0) renderTileValue(value, tilePos, style.text);
}


TileRenderer::TileStyle TileRenderer::getTileStyle(int value) const {
	return {getTileColor(value), getTextColor(value)};
}


ImVec4 TileRenderer::getTileColor(int value) const {
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


ImVec4 TileRenderer::getTextColor(int value) const {
	return value <= 4 ? ImVec4(0.2f, 0.2f, 0.2f, 1.0f) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
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
	if (value < 100) return tileSize_ / 3.0f;
	if (value < 1000) return tileSize_ / 3.5f;
	return tileSize_ / 4.0f;
}


ImVec2 TileRenderer::centerTextInTile(const ImVec2& tilePos, const ImVec2& textSize) const {
	return ImVec2(
		tilePos.x + (tileSize_ - textSize.x) * 0.5f,
		tilePos.y + (tileSize_ - textSize.y) * 0.5f
	);
}
