#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int TITLE_FONT_SIZE = 50;

// window dimensions
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 800;

// constants for player sprite sheet
constexpr int PLAYER_SPRITE_SHEET_WIDTH = 900;
constexpr int PLAYER_SPRITE_SHEET_HEIGHT = 700;

// constants for frame dimensions
constexpr int PLAYER_FRAME_WIDTH = 100;
constexpr int PLAYER_FRAME_HEIGHT = 100;
constexpr int PLAYER_FRAME_NUM = 9;

// constants for player sprite sheet animation index
constexpr int PLAYER_IDLE_INDEX = 0;
constexpr int PLAYER_WALK_INDEX = 1;

// constants for animations
constexpr float PLAYER_IDLE_SPEED = 0.5f;
constexpr float PLAYER_WALK_SPEED = 0.1f;

constexpr float PLAYER_SPRITE_SCALE = 0.0625f;

// camera constants
constexpr float CAMERA_ROTATION_SPEED = 1.5f;
constexpr float CAMERA_MIN_DISTANCE = 3.0f;
constexpr float CAMERA_MAX_DISTANCE = 20.0f;
constexpr float CAMERA_ZOOM_SPEED = 75.0f;
constexpr float CAMERA_HEIGHT = 2.0f;
constexpr float CAMERA_FOLLOW_SPEED = 5.0f;

#endif
