#ifndef Generation_cpp
#define Generation_cpp

#define BLOCK_SIZE 10
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define MIN_BLOCKS 5
#define BLOCK_VARIATION 5
#define BLOCK_INDEX 1

#include <FEHRandom.h>
#include <classes.cpp>
#include <vector>

struct Generation {
    /**
     * Generates a vector of blocks for x_distance
     * @param left
     * How many blocks left to draw
     * @param right
     * How many blocks right to draw
     */
    static std::vector<GameObject> generateWorld(int intial, int left, int right) {
        std::vector<GameObject> blocks;

        for(int i = left; i <= right / BLOCK_SIZE; i++) {
            int num_blocks = Random.RandInt() % BLOCK_VARIATION + MIN_BLOCKS;

            for(int b = 0; b < num_blocks; b++) {
                GameObject g (Vector3({(i - intial) * BLOCK_SIZE, SCREEN_HEIGHT - b * BLOCK_SIZE, 0}), BLOCK_INDEX);
                blocks.push_back(g);
            }
        }
        
        return blocks;
    }
};


#endif