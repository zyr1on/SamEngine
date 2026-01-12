#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> // OpenGL fonksiyonları için (glew de olabilir)
#include "MeshData.h"

class Mesh {
public:
    // Constructor: MeshData'yı alır ve GPU'ya yükler
    Mesh(const MeshData& data);
    ~Mesh();

    // Çizim fonksiyonu
    void Draw() const;

private:
    unsigned int VAO, VBO, EBO;
    unsigned int indexCount;

    void SetupMesh(const MeshData& data);
};

#endif