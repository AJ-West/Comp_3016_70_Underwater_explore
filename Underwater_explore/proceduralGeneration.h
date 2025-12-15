#pragma once

#include <vector>

#include <glad/glad.h> 

#include "FastNoiseLite.h"

#include "variables.h"

#include "stb_image.h"

using namespace std;

class Collectable;

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

    void generateTextures();

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
    GLfloat terrainVertices[MAP_SIZE][8];

    //VAO vertex attribute positions in correspondence to vertex attribute type
    enum VAO_IDs { Triangles, Indices, Colours, Textures, NumVAOs = 2 };
    //VAOs
    GLuint VAOs[NumVAOs];

    //Buffer types
    enum Buffer_IDs { ArrayBuffer, NumBuffers = 4 };
    //Buffer objects
    GLuint Buffers[NumBuffers];
};