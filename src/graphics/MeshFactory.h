#ifndef MESH_FACTORY_H
#define MESH_FACTORY_H

#include "MeshData.h"

class MeshFactory {
public:
    static MeshData CreateCube(float size = 1.0f);
    static MeshData CreatePlane(float width = 1.0f, float height = 1.0f);
    static MeshData CreateQuad(float width = 1.0f, float height = 1.0f);
    static MeshData CreateSphere(float radius = 1.0f, unsigned int segments = 32);
};

#endif