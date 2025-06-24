#pragma once

#include "imgui.h"


class TileRenderer {
public:
	TileRenderer(float tileSize, float tilePadding);
	void renderTile(int value, const ImVec2& gridStartPos, int row, int col) const;
	float getTileSize() const;
	float getTilePaddingSize() const;

private:
	float tileSize_;
	float tilePaddingSize_;

	ImVec2 calculateTilePosition(const ImVec2& gridStartPos, int row, int col) const;
	void renderTileValue(int value, const ImVec2& tilePos, const ImVec4& textColor) const;
	float calculateFontSize(int value) const;
	ImVec2 centerTextInTile(const ImVec2& tilePos, const ImVec2& textSize) const;
};