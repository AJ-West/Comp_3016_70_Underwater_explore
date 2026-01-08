#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include "../variables.h"

using namespace glm;

// Test vector normalization
TEST(MathUtilitiesTest, VectorNormalization) {
    vec3 v(3.0f, 4.0f, 0.0f);
    vec3 normalized = normalize(v);
    
    float vecLength = glm::length(normalized);
    
    // Normalized vector should have length 1
    EXPECT_NEAR(vecLength, 1.0f, 0.001f);
}

// Test cross product
TEST(MathUtilitiesTest, CrossProduct) {
    vec3 a(1.0f, 0.0f, 0.0f);
    vec3 b(0.0f, 1.0f, 0.0f);
    vec3 result = cross(a, b);
    
    // Cross product of (1,0,0) x (0,1,0) should be (0,0,1)
    EXPECT_FLOAT_EQ(result.x, 0.0f);
    EXPECT_FLOAT_EQ(result.y, 0.0f);
    EXPECT_FLOAT_EQ(result.z, 1.0f);
}

// Test distance calculation (used in collision detection)
TEST(MathUtilitiesTest, DistanceCalculation) {
    vec3 a(0.0f, 0.0f, 0.0f);
    vec3 b(3.0f, 4.0f, 0.0f);
    
    vec3 diff = b - a;
    float mag = sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
    
    // Distance should be 5 (3-4-5 triangle)
    EXPECT_NEAR(mag, 5.0f, 0.001f);
}

// Test map size constants
TEST(MathUtilitiesTest, MapSizeConstants) {
    // Verify map size calculations
    int expectedMapSize = RENDER_DISTANCE * RENDER_DISTANCE;
    EXPECT_EQ(MAP_SIZE, expectedMapSize);
    
    // Verify triangles calculation
    int expectedSquaresRow = RENDER_DISTANCE - 1;
    EXPECT_EQ(squaresRow, expectedSquaresRow);
    
    int expectedTriangles = squaresRow * squaresRow * trianglesPerSquare;
    EXPECT_EQ(trianglesGrid, expectedTriangles);
}

// Test chunk size is negative (as per code)
TEST(MathUtilitiesTest, ChunkSizeNegative) {
    // Chunk size should be negative based on code
    EXPECT_LT(chunkSize, 0.0f);
    EXPECT_FLOAT_EQ(chunkSize, -0.25f);
}

// Test vector addition and subtraction
TEST(MathUtilitiesTest, VectorOperations) {
    vec3 a(1.0f, 2.0f, 3.0f);
    vec3 b(4.0f, 5.0f, 6.0f);
    
    vec3 sum = a + b;
    EXPECT_FLOAT_EQ(sum.x, 5.0f);
    EXPECT_FLOAT_EQ(sum.y, 7.0f);
    EXPECT_FLOAT_EQ(sum.z, 9.0f);
    
    vec3 diff = b - a;
    EXPECT_FLOAT_EQ(diff.x, 3.0f);
    EXPECT_FLOAT_EQ(diff.y, 3.0f);
    EXPECT_FLOAT_EQ(diff.z, 3.0f);
}

// Test vector scaling
TEST(MathUtilitiesTest, VectorScaling) {
    vec3 v(1.0f, 2.0f, 3.0f);
    float scale = 2.0f;
    
    vec3 scaled = v * scale;
    EXPECT_FLOAT_EQ(scaled.x, 2.0f);
    EXPECT_FLOAT_EQ(scaled.y, 4.0f);
    EXPECT_FLOAT_EQ(scaled.z, 6.0f);
}

