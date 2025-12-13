#pragma once

#include <vector>

#include <glad/glad.h> 

#include "FastNoiseLite.h"

#include "collectable.h"

#include "variables.h"

using namespace std;

class ProcGen {
public:
    ProcGen();
    ~ProcGen();

    void createTerrainNoise();

    void createBiomeNoise();

    void procTerrainGen();

    void biomeGeneration();

    void generateVertices();

    void generateChunks();

    vector<Collectable*> generateCollectables();

    void bind();

    void draw();

private:
    //Assigning perlin noise type for map
    FastNoiseLite TerrainNoise;
    FastNoiseLite BiomeNoise;

    // Map chunk locations
    GLuint terrainIndices[trianglesGrid][3];

    //Generation of height map vertices
    GLfloat terrainVertices[MAP_SIZE][6];

    //VAO vertex attribute positions in correspondence to vertex attribute type
    enum VAO_IDs { Triangles, Indices, Colours, Textures, NumVAOs = 2 };
    //VAOs
    GLuint VAOs[NumVAOs];

    //Buffer types
    enum Buffer_IDs { ArrayBuffer, NumBuffers = 4 };
    //Buffer objects
    GLuint Buffers[NumBuffers];
};