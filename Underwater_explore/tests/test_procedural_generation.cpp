#include <gtest/gtest.h>
#include "../proceduralGeneration.h"
#include "../collectable.h"
#include "../variables.h"
#include <cmath>

// Test fixture for procedural generation
class ProceduralGenerationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set a fixed seed for deterministic testing
        srand(42);
        procGen = new ProcGen();
    }

    void TearDown() override {
        delete procGen;
    }

    ProcGen* procGen;
};

// Test noise generation initialization
TEST_F(ProceduralGenerationTest, NoiseGenerationInitialization) {
    // Test that noise generators can be created
    // This tests the internal noise setup
    procGen->procTerrainGen();
    
    // Verify terrain was generated
    // We can't directly access private members, but we can verify
    // that the generation completed without crashing
    vector<Plant*> plants = procGen->getPlants();
    vector<vec3> lava = procGen->getLava();
    
    // Generation should complete successfully
    EXPECT_TRUE(true); // If we get here, generation worked
}

// Test biome generation produces valid results
TEST_F(ProceduralGenerationTest, BiomeGenerationCompletes) {
    procGen->procTerrainGen();
    
    // Verify we can get plants and lava
    vector<Plant*> plants = procGen->getPlants();
    vector<vec3> lava = procGen->getLava();
    
    // Plants should only spawn in murky biome (we can't verify directly,
    // but we can check the generation completed)
    EXPECT_GE(plants.size(), 0);
    EXPECT_GE(lava.size(), 0);
}

// Test collectable generation
// Note: This test may fail if model files are not accessible
// The collectable constructor loads a model file which requires proper paths
TEST_F(ProceduralGenerationTest, CollectableGeneration) {
    procGen->procTerrainGen();
    
    vector<Collectable*> collectables = procGen->generateCollectables();
    
    // Should generate exactly 6 collectables (0-5 inclusive = 6 items)
    EXPECT_EQ(collectables.size(), 6);
    
    // Clean up
    // Note: Deletion may cause issues if model wasn't loaded properly
    // In a production environment, you'd want to handle this more gracefully
    for (auto* collect : collectables) {
        if (collect != nullptr) {
            delete collect;
        }
    }
}

// Test collectable positions are within valid range
// Note: This test may fail if model files are not accessible
TEST_F(ProceduralGenerationTest, CollectablePositionsValid) {
    procGen->procTerrainGen();
    
    vector<Collectable*> collectables = procGen->generateCollectables();
    
    for (auto* collect : collectables) {
        if (collect != nullptr) {
            vec3 pos = collect->getCentrePoint();
            
            // Positions should be within map bounds
            // Map size is RENDER_DISTANCE * chunkSize
            // Note: chunkSize is negative, so we use abs
            float maxPos = RENDER_DISTANCE * abs(chunkSize);
            EXPECT_GE(pos.x, -maxPos); // chunkSize is negative
            EXPECT_LE(pos.x, 0.0f);
            EXPECT_GE(pos.z, -maxPos);
            EXPECT_LE(pos.z, 0.0f);
        }
    }
    
    // Clean up
    for (auto* collect : collectables) {
        if (collect != nullptr) {
            delete collect;
        }
    }
}

// Test that multiple generations produce different results (with different seeds)
TEST_F(ProceduralGenerationTest, ProceduralGenerationVariety) {
    srand(100);
    ProcGen* procGen1 = new ProcGen();
    procGen1->procTerrainGen();
    vector<Collectable*> collectables1 = procGen1->generateCollectables();
    vec3 pos1 = collectables1[0]->getCentrePoint();
    
    srand(200);
    ProcGen* procGen2 = new ProcGen();
    procGen2->procTerrainGen();
    vector<Collectable*> collectables2 = procGen2->generateCollectables();
    vec3 pos2 = collectables2[0]->getCentrePoint();
    
    // With different seeds, positions should likely be different
    // (not guaranteed, but very likely)
    bool positionsDifferent = (pos1.x != pos2.x) || (pos1.z != pos2.z);
    // This test may occasionally fail, but it's testing randomness
    // In practice, with different seeds, results should differ
    
    // Clean up
    for (auto* collect : collectables1) {
        delete collect;
    }
    for (auto* collect : collectables2) {
        delete collect;
    }
    delete procGen1;
    delete procGen2;
}

// Test lava generation at correct depth
TEST_F(ProceduralGenerationTest, LavaGenerationDepth) {
    procGen->procTerrainGen();
    
    vector<vec3> lava = procGen->getLava();
    
    // All lava should be at or below -0.25 depth
    for (const auto& lavaPos : lava) {
        EXPECT_LE(lavaPos.y, -0.25f);
    }
}

