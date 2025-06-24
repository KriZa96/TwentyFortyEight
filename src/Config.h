#pragma once

#include "imgui.h"

struct DisplayConfig {
    static constexpr int OPENGL_VERSION_MAJOR = 3;
    static constexpr int OPENGL_VERSION_MINOR = 0;
    static constexpr const char* WINDOW_TITLE = "2048 Game";
    static constexpr const char* OPENGL_VERSION_STRING = "#version 130";
    static constexpr int VSYNC_ENABLED = 1;

    static inline const ImVec4 BACKGROUND_COLOR =
        ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    static inline const ImVec4 GRID_BACKGROUND_COLOR =
        ImVec4(187 / 255.0f, 173 / 255.0f, 160 / 255.0f, 1.0f);
};


struct GameConfig {
    static constexpr int GRID_SIZE = 4;
    static constexpr int WINNING_TILE_VALUE = 2048;
    static constexpr int INITIAL_TILES_COUNT = 2;
    static constexpr int TILE_2_PROBABILITY = 90;
    static constexpr int PROBABILITY_RANGE = 100;
};


struct UIConfig {
    static constexpr float WINDOW_FONT_SCALE = 4.0f;
    static constexpr float BUTTON_WIDTH_RATIO = 0.10f;
    static constexpr float BUTTON_HEIGHT_RATIO = 0.05f;
    static constexpr float BUTTON_SPACING_RATIO = 0.02f;
    static constexpr float VERTICAL_SPACING_RATIO = 0.02f;
    static constexpr float GRID_AREA_RATIO = 0.8f;

    static constexpr const char* NEW_GAME_BUTTON_TEXT = "New Game";
    static constexpr const char* EXIT_BUTTON_TEXT = "Exit";
    static constexpr const char* SCORE_TEXT_FORMAT = "Score: {}";
    static constexpr const char* GAME_OVER_TEXT = "Game Over!";
    static constexpr const char* GAME_WIN_TEXT = "You Win!";
    static constexpr const char* INSTRUCTION_TEXT = "Use arrow keys to move tiles";
    static constexpr const char* GAME_OVER_MESSAGE = "Press 'New Game' to play again.";
    static constexpr const char* GAME_WIN_MESSAGE = "Continue playing or press 'New Game' to start over.";

    static inline const ImVec4 LIGHT_TEXT = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    static inline const ImVec4 DARK_TEXT = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    static inline const ImVec4 GAME_OVER_COLOR = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    static inline const ImVec4 GAME_WIN_COLOR = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
};

struct TileRenderConfig {
  static constexpr float TILE_SIZE_DIVISOR = 8.0f;
  static constexpr float TILE_PADDING_DIVISOR = 8.0f;
  static constexpr float TILE_CORNER_RADIUS = 5.0f;
  static constexpr float SCORE_TEXT_OFFSET = 3.0f;
  static constexpr float INFO_TEXT_OFFSET = 6.0f;
  static constexpr float STATUS_TEXT_OFFSET = 2.0f;

  static constexpr float LARGE_FONT_DIVISOR = 3.0f;
  static constexpr float MEDIUM_FONT_DIVISOR = 3.5f;
  static constexpr float SMALL_FONT_DIVISOR = 4.0f;
  static constexpr int MEDIUM_FONT_THRESHOLD = 100;
  static constexpr int SMALL_FONT_THRESHOLD = 1000;
  static constexpr int DARK_TEXT_THRESHOLD = 4;
};


struct TileColorConfig {
  struct TileStyle {
    ImVec4 background;
    ImVec4 text;
  };

  static inline const ImVec4 EMPTY_TILE = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
  static inline const ImVec4 TILE_2 = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
  static inline const ImVec4 TILE_4 = ImVec4(0.9f, 0.9f, 0.8f, 1.0f);
  static inline const ImVec4 TILE_8 = ImVec4(0.9f, 0.8f, 0.7f, 1.0f);
  static inline const ImVec4 TILE_16 = ImVec4(0.9f, 0.7f, 0.5f, 1.0f);
  static inline const ImVec4 TILE_32 = ImVec4(0.9f, 0.6f, 0.4f, 1.0f);
  static inline const ImVec4 TILE_64 = ImVec4(0.9f, 0.5f, 0.3f, 1.0f);
  static inline const ImVec4 TILE_128 = ImVec4(0.9f, 0.4f, 0.2f, 1.0f);
  static inline const ImVec4 TILE_256 = ImVec4(0.9f, 0.3f, 0.1f, 1.0f);
  static inline const ImVec4 TILE_512 = ImVec4(0.9f, 0.2f, 0.1f, 1.0f);
  static inline const ImVec4 TILE_1024 = ImVec4(0.9f, 0.1f, 0.1f, 1.0f);
  static inline const ImVec4 TILE_2048 = ImVec4(0.9f, 0.0f, 0.0f, 1.0f);
  static inline const ImVec4 TILE_DEFAULT = ImVec4(0.8f, 0.0f, 0.0f, 1.0f);

  static ImVec4 getTileColor(int value) {
    switch (value) {
      case 0:
        return EMPTY_TILE;
      case 2:
        return TILE_2;
      case 4:
        return TILE_4;
      case 8:
        return TILE_8;
      case 16:
        return TILE_16;
      case 32:
        return TILE_32;
      case 64:
        return TILE_64;
      case 128:
        return TILE_128;
      case 256:
        return TILE_256;
      case 512:
        return TILE_512;
      case 1024:
        return TILE_1024;
      case 2048:
        return TILE_2048;
      default:
        return TILE_DEFAULT;
    }
  }

  static ImVec4 getTextColor(int value) {
    return value <= TileRenderConfig::DARK_TEXT_THRESHOLD
               ? UIConfig::DARK_TEXT
               : UIConfig::LIGHT_TEXT;
  }

  static TileStyle getTileStyle(int value) {
    return {getTileColor(value), getTextColor(value)};
  }
};
