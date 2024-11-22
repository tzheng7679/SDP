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
     * @param x_distance
     * How far to draw blocks for
     */
    static std::vector<GameObject> generateWorld(int x_distance) {
        std::vector<GameObject> blocks;

        for(int i = 0; i < x_distance / BLOCK_SIZE; i++) {
            int num_blocks = Random.RandInt() % BLOCK_VARIATION + MIN_BLOCKS;

            for(int b = 0; b < num_blocks; b++) {
                GameObject g (Vector3({i * BLOCK_SIZE, SCREEN_HEIGHT - b * BLOCK_SIZE, 0}), BLOCK_INDEX);
                blocks.push_back(g);
            }
        }
        
        return blocks;
    }
};


#endif