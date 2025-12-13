#pragma once

#include "FastNoiseLite.h"

#include "variables.h"

using namespace std;

class ProcGen {
public:
	ProcGen(){}
	~ProcGen(){}

    void createTerrainNoise() {
        //Setting noise type to Perlin
        TerrainNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        //Sets the noise scale
        TerrainNoise.SetFrequency(0.05f);
        //Generates a random seed between integers 0 & 100
        int terrainSeed = rand() % 100;
        //Sets seed for noise
        TerrainNoise.SetSeed(terrainSeed);
    }

    void createBiomeNoise() {
        BiomeNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
        BiomeNoise.SetFrequency(0.05f);
        int biomeSeed = rand() % 100;
        TerrainNoise.SetSeed(biomeSeed);
    }

    void procTerrainGen() {      
        // create noise for terrain and biomes to generate from
        createTerrainNoise();
        createBiomeNoise();        

        //define where each biome
        biomeGeneration();
        
        //generate the vertices for the map
        generateVertices();  
        // generates the indicies for the map chuncks
        generateChunks();
        
        bind();
    }

    void biomeGeneration() {
        //Terrain vertice index
        int i = 0;
        //Using x & y nested for loop in order to apply noise 2-dimensionally
        for (int y = 0; y < RENDER_DISTANCE; y++)
        {
            for (int x = 0; x < RENDER_DISTANCE; x++)
            {
                //Retrieval of biome to set
                float biomeValue = BiomeNoise.GetNoise((float)x, (float)y);

                if (biomeValue <= -0.75f) //Plains
                {
                    terrainVertices[i][3] = 0.0f;
                    terrainVertices[i][4] = 0.75f;
                    terrainVertices[i][5] = 0.25f;
                }
                else //Desert
                {
                    terrainVertices[i][3] = 1.0f;
                    terrainVertices[i][4] = 1.0f;
                    terrainVertices[i][5] = 0.5f;
                }

                //Setting of height from 2D noise value at respective x & y coordinate
                float noiseVal = TerrainNoise.GetNoise((float)x, (float)y);
                if (noiseVal >= 0.4) {
                    terrainVertices[i][1] = TerrainNoise.GetNoise((float)x, (float)y) * TerrainNoise.GetNoise((float)x, (float)y) * 10;
                }
                else if (noiseVal >= 0.25) {
                    terrainVertices[i][1] = TerrainNoise.GetNoise((float)x, (float)y) * TerrainNoise.GetNoise((float)x, (float)y) * 7.5;
                }
                else if (noiseVal >= 0) {
                    terrainVertices[i][1] = TerrainNoise.GetNoise((float)x, (float)y) * TerrainNoise.GetNoise((float)x, (float)y) * 5;
                }
                else {
                    terrainVertices[i][1] = -TerrainNoise.GetNoise((float)x, (float)y) * TerrainNoise.GetNoise((float)x, (float)y);
                }
                if (terrainVertices[i][1] <= -0.25) {
                    terrainVertices[i][3] = 1.0f;
                    terrainVertices[i][4] = 0.0f;
                    terrainVertices[i][5] = 0.0f;
                }

                i++;
            }
        }
    }

    void generateVertices() {
        float drawingStartPosition = 0.0f;
        float columnVerticesOffset = drawingStartPosition;
        float rowVerticesOffset = drawingStartPosition;

        int rowIndex = 0;
        //procedural generation
        for (int i = 0; i < MAP_SIZE; i++)
        {
            //Generation of x & z vertices for horizontal plane
            terrainVertices[i][0] = columnVerticesOffset;
            terrainVertices[i][2] = rowVerticesOffset;

            //Shifts x position across for next triangle along grid
            columnVerticesOffset = columnVerticesOffset + chunkSize;

            //Indexing of each chunk within row
            rowIndex++;
            //True when all triangles of the current row have been generated
            if (rowIndex == RENDER_DISTANCE)
            {
                //Resets for next row of triangles
                rowIndex = 0;
                //Resets x position for next row of triangles
                columnVerticesOffset = drawingStartPosition;
                //Shifts y position
                rowVerticesOffset = rowVerticesOffset + chunkSize;
            }
        }
    }

    void generateChunks() {
        //Positions to start mapping indices from
        int columnIndicesOffset = 0;
        int rowIndicesOffset = 0;

        //Generation of map indices in the form of chunks (1x1 right angle triangle squares)
        int rowIndex = 0;

        for (int i = 0; i < trianglesGrid - 1; i += 2)
        {
            terrainIndices[i][0] = columnIndicesOffset + rowIndicesOffset; //top left
            terrainIndices[i][2] = RENDER_DISTANCE + columnIndicesOffset + rowIndicesOffset; //bottom left
            terrainIndices[i][1] = 1 + columnIndicesOffset + rowIndicesOffset; //top right

            terrainIndices[i + 1][0] = 1 + columnIndicesOffset + rowIndicesOffset; //top right
            terrainIndices[i + 1][2] = RENDER_DISTANCE + columnIndicesOffset + rowIndicesOffset; //bottom left
            terrainIndices[i + 1][1] = 1 + RENDER_DISTANCE + columnIndicesOffset + rowIndicesOffset; //bottom right

            //Shifts x position across for next chunk along grid
            columnIndicesOffset = columnIndicesOffset + 1;

            //Indexing of each chunk within row
            rowIndex++;

            //True when all chunks of the current row have been generated
            if (rowIndex == squaresRow)
            {
                //Resets for next row of chunks
                rowIndex = 0;
                //Resets x position for next row of chunks
                columnIndicesOffset = 0;
                //Shifts y position
                rowIndicesOffset = rowIndicesOffset + RENDER_DISTANCE;
            }
        }
    }

    void bind() {
        //Sets index of VAO
        glGenVertexArrays(NumVAOs, VAOs);
        //Binds VAO to a buffer
        glBindVertexArray(VAOs[0]);
        //Sets indexes of all required buffer objects
        glGenBuffers(NumBuffers, Buffers);

        //Binds vertex object to array buffer
        glBindBuffer(GL_ARRAY_BUFFER, Buffers[Triangles]);
        //Allocates buffer memory for the vertices of the 'Triangles' buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(terrainVertices), terrainVertices, GL_STATIC_DRAW);

        //Binding & allocation for indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[Indices]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(terrainIndices), terrainIndices, GL_STATIC_DRAW);

        //Allocation & indexing of vertex attribute memory for vertex shader
        //Positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //Colours
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        //Textures to generate
        glGenTextures(NumBuffers, Buffers);

        //Unbinding
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        //Binding texture to type 2D texture
        glBindTexture(GL_TEXTURE_2D, Buffers[Textures]);

        //Selects x axis (S) of texture bound to GL_TEXTURE_2D & sets to repeat beyond normalised coordinates
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //Selects y axis (T) equivalently
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        //Sets to use linear interpolation between adjacent mipmaps
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //Sets to use linear interpolation upscaling (past largest mipmap texture)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void draw() {
        glBindTexture(GL_TEXTURE_2D, Buffers[Textures]);
        glBindVertexArray(VAOs[0]); //Bind buffer object to render
        glDrawElements(GL_TRIANGLES, MAP_SIZE * 32, GL_UNSIGNED_INT, 0);
    }
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