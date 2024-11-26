#ifndef Generation_cpp
#define Generation_cpp

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
    static std::deque<GameObject> generateWorld(int intial, int left, int right) {
        std::deque<GameObject> blocks;

        for(int i = left; i <= right / BLOCK_SIZE; i++) {
            int num_blocks = Random.RandInt() % BLOCK_VARIATION + MIN_BLOCKS;

            for(int b = 0; b < num_blocks; b++) {
                GameObject g (Vector3({(i - intial) * BLOCK_SIZE, SCREEN_HEIGHT - b * BLOCK_SIZE, 0}), BLOCK_IMAGE_INDEX);
                blocks.push_back(g);
            }
        }
        
        return blocks;
    }
};


#endif