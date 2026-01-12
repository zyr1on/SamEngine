#ifndef MESH_DATA_H
#define MESH_DATA_H

#include <vector>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct MeshData {
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
};

#endif