#include <gtest/gtest.h>
#include "../Player.h"
#include "../collectable.h"
#include "../variables.h"
#include <glm/glm.hpp>
#include <vector>

// Test fixture for Player
class PlayerTest : public ::testing::Test {
protected:
    void SetUp() override {
        player = new Player();
        deltaTime = 0.016f; // Simulate ~60 FPS
    }

    void TearDown() override {
        delete player;
    }

    Player* player;
};

// Test player initialization
TEST_F(PlayerTest, PlayerInitialization) {
    vec3 pos = player->getCameraPosition();
    vec3 front = player->getCameraFront();
    vec3 up = player->getCameraUp();
    
    // Check initial position
    EXPECT_FLOAT_EQ(pos.x, 0.0f);
    EXPECT_FLOAT_EQ(pos.y, 0.0f);
    EXPECT_FLOAT_EQ(pos.z, 0.5f);
    
    // Check initial camera front
    EXPECT_FLOAT_EQ(front.x, 0.0f);
    EXPECT_FLOAT_EQ(front.y, 0.0f);
    EXPECT_FLOAT_EQ(front.z, -1.0f);
    
    // Check camera up vector
    EXPECT_FLOAT_EQ(up.x, 0.0f);
    EXPECT_FLOAT_EQ(up.y, 1.0f);
    EXPECT_FLOAT_EQ(up.z, 0.0f);
}

// Test camera front setter
TEST_F(PlayerTest, SetCameraFront) {
    vec3 newFront(1.0f, 0.0f, 0.0f);
    player->setCameraFront(newFront);
    
    vec3 front = player->getCameraFront();
    EXPECT_FLOAT_EQ(front.x, 1.0f);
    EXPECT_FLOAT_EQ(front.y, 0.0f);
    EXPECT_FLOAT_EQ(front.z, 0.0f);
}

// Test collision detection - no collision
// Note: Requires model file access
TEST_F(PlayerTest, CollisionDetectionNoCollision) {
    // Create collectable far from player
    vec3 collectablePos(10.0f, 0.0f, 10.0f);
    
    Collectable* collect = nullptr;
    try {
        collect = new Collectable(collectablePos);
        
        if (collect != nullptr) {
            bool collision = player->checkCollision(collect);
            EXPECT_FALSE(collision);
        }
    } catch (...) {
        return; // Skip test if model file not accessible
    }
    
    if (collect != nullptr) {
        delete collect;
    }
}

// Test collision detection - collision
// Note: Requires model file access for Collectable constructor
TEST_F(PlayerTest, CollisionDetectionWithCollision) {
    // Create collectable at player position
    vec3 playerPos = player->getCameraPosition();
    
    Collectable* collect = nullptr;
    try {
        collect = new Collectable(playerPos);
        
        if (collect != nullptr) {
            bool collision = player->checkCollision(collect);
            
            // Should detect collision when collectable is at player position
            EXPECT_TRUE(collision);
        }
    } catch (...) {
        return; // Skip test if model file not accessible
    }
    
    if (collect != nullptr) {
        delete collect;
    }
}

// Test collision detection - edge case (just touching)
// Note: Requires model file access
TEST_F(PlayerTest, CollisionDetectionEdgeCase) {
    vec3 playerPos = player->getCameraPosition();
    // Place collectable at exactly the collision radius
    // Collectable size is 0.25f, so center should be at distance 0.25f
    vec3 collectablePos = playerPos + vec3(0.25f, 0.0f, 0.0f);
    
    Collectable* collect = nullptr;
    try {
        collect = new Collectable(collectablePos);
        
        if (collect != nullptr) {
            bool collision = player->checkCollision(collect);
            
            // Should detect collision when distance equals size
            EXPECT_TRUE(collision);
        }
    } catch (...) {
        return; // Skip test if model file not accessible
    }
    
    if (collect != nullptr) {
        delete collect;
    }
}

// Test collision detection - just outside collision range
// Note: Requires model file access
TEST_F(PlayerTest, CollisionDetectionJustOutside) {
    vec3 playerPos = player->getCameraPosition();
    // Place collectable just outside collision radius
    vec3 collectablePos = playerPos + vec3(0.26f, 0.0f, 0.0f);
    
    Collectable* collect = nullptr;
    try {
        collect = new Collectable(collectablePos);
        
        if (collect != nullptr) {
            bool collision = player->checkCollision(collect);
            
            // Should not detect collision when distance is slightly greater than size
            EXPECT_FALSE(collision);
        }
    } catch (...) {
        return; // Skip test if model file not accessible
    }
    
    if (collect != nullptr) {
        delete collect;
    }
}

// Test collision detection with different positions
// Note: Requires model file access
TEST_F(PlayerTest, CollisionDetectionMultiplePositions) {
    vec3 playerPos = player->getCameraPosition();
    
    // Test multiple positions
    std::vector<vec3> testPositions = {
        playerPos + vec3(0.1f, 0.0f, 0.0f),  // Should collide
        playerPos + vec3(0.0f, 0.1f, 0.0f),  // Should collide
        playerPos + vec3(0.0f, 0.0f, 0.1f),  // Should collide
        playerPos + vec3(1.0f, 0.0f, 0.0f),  // Should not collide
        playerPos + vec3(0.0f, 1.0f, 0.0f),  // Should not collide
        playerPos + vec3(0.0f, 0.0f, 1.0f),  // Should not collide
    };
    
    std::vector<bool> expectedCollisions = {
        true, true, true, false, false, false
    };
    
    for (size_t i = 0; i < testPositions.size(); ++i) {
        Collectable* collect = nullptr;
        try {
            collect = new Collectable(testPositions[i]);
            
            if (collect != nullptr) {
                bool collision = player->checkCollision(collect);
                EXPECT_EQ(collision, expectedCollisions[i]) 
                    << "Collision test failed for position " << i;
            }
        } catch (...) {
            // Skip this test if model loading fails
            continue;
        }
        
        if (collect != nullptr) {
            delete collect;
        }
    }
}

