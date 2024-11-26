// Constants used throughout process

#ifndef Constants_cpp
#define Constants_cpp

// Proteus constants
#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 320

#define CAM_POS c.getPosition().x - SCREEN_WIDTH / 2

// World generation / block constants
#define BLOCK_SIZE 10
#define MIN_BLOCKS 5
#define BLOCK_VARIATION 5

// Button Constants
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 50
#define PADDING 5

// macros so I don't have to write this every damn time
#define NEWLINE << "\n";
#define TAB << "\t" << 
#define TABEND << "\t";

// Image indices
#define CHARACTER_IMAGE_INDEX 0
#define BLOCK_IMAGE_INDEX 1

// save files
#define C_SAVE_PATH "saves/c.txt" // character save file
#define O_SAVE_PATH "saves/obs.txt" // objects save file

// physical constants
#define VELOCITY_INITIAL 1
#define VELOCITY_MAX 3.0
#define ACCELERATION 1
#define G 0.5
#define DELTA_T .00

#endif