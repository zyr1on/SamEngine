#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include "MeshData.h"

class Mesh {
public:
    Mesh(const MeshData& data);
    ~Mesh();

    void Draw() const;

private:
    unsigned int VAO, VBO, EBO;
    unsigned int indexCount;

    void SetupMesh(const MeshData& data);
};

#endif