#pragma once
#include <glad/glad.h>

#ifndef VARIABLES_H
#define VARIABLES_H

#define RENDER_DISTANCE 196 //Render width of map
#define MAP_SIZE RENDER_DISTANCE * RENDER_DISTANCE //Size of map in x & z space

//Amount of chunks across one dimension
const int squaresRow = RENDER_DISTANCE - 1;
//Two triangles per square to form a 1x1 chunk
static const int trianglesPerSquare = 2;
//Amount of triangles on map
static const int trianglesGrid = squaresRow * squaresRow * trianglesPerSquare;

//const float chunkSize = -0.0625f;
const float chunkSize = -0.25f;


#endif // !VARIABLES_H