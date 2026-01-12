#include "MeshFactory.h"
#include<cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

MeshData MeshFactory::CreateCube(float size) {
    MeshData data;
    float s = size / 2.0f;

    data.Vertices = {
        {{-s, -s,  s}, {0, 0, 1}, {0, 0}}, {{ s, -s,  s}, {0, 0, 1}, {1, 0}},
        {{ s,  s,  s}, {0, 0, 1}, {1, 1}}, {{-s,  s,  s}, {0, 0, 1}, {0, 1}},
        {{-s, -s, -s}, {0, 0,-1}, {1, 0}}, {{-s,  s, -s}, {0, 0,-1}, {1, 1}},
        {{ s,  s, -s}, {0, 0,-1}, {0, 1}}, {{ s, -s, -s}, {0, 0,-1}, {0, 0}},
        {{-s,  s, -s}, {0, 1, 0}, {0, 1}}, {{-s,  s,  s}, {0, 1, 0}, {0, 0}},
        {{ s,  s,  s}, {0, 1, 0}, {1, 0}}, {{ s,  s, -s}, {0, 1, 0}, {1, 1}},
        {{-s, -s, -s}, {0,-1, 0}, {0, 0}}, {{ s, -s, -s}, {0,-1, 0}, {1, 0}},
        {{ s, -s,  s}, {0,-1, 0}, {1, 1}}, {{-s, -s,  s}, {0,-1, 0}, {0, 1}},
        {{ s, -s, -s}, {1, 0, 0}, {1, 0}}, {{ s,  s, -s}, {1, 0, 0}, {1, 1}},
        {{ s,  s,  s}, {1, 0, 0}, {0, 1}}, {{ s, -s,  s}, {1, 0, 0}, {0, 0}},
        {{-s, -s, -s}, {-1,0, 0}, {0, 0}}, {{-s, -s,  s}, {-1,0, 0}, {1, 0}},
        {{-s,  s,  s}, {-1,0, 0}, {1, 1}}, {{-s,  s, -s}, {-1,0, 0}, {0, 1}}
    };
    for (int i = 0; i < 24; i += 4) {
        data.Indices.push_back(i);     data.Indices.push_back(i + 1); data.Indices.push_back(i + 2);
        data.Indices.push_back(i);     data.Indices.push_back(i + 2); data.Indices.push_back(i + 3);
    }
    return data;
}

MeshData MeshFactory::CreatePlane(float width, float height) {
    MeshData data;
    float w = width / 2.0f;
    float h = height / 2.0f;

    data.Vertices = {
        {{-w, 0,  h}, {0, 1, 0}, {0, 0}},
        {{ w, 0,  h}, {0, 1, 0}, {1, 0}},
        {{ w, 0, -h}, {0, 1, 0}, {1, 1}},
        {{-w, 0, -h}, {0, 1, 0}, {0, 1}}
    };

    data.Indices = { 0, 1, 2, 0, 2, 3 };

    return data;
}

MeshData MeshFactory::CreateQuad(float width, float height)
{
    MeshData data;

    float w = width  * 0.5f;
    float h = height * 0.5f;

    data.Vertices = {
        // pos               normal        uv
        {{-w, -h, 0.0f}, {0, 0, 1}, {0, 0}},
        {{ w, -h, 0.0f}, {0, 0, 1}, {1, 0}},
        {{ w,  h, 0.0f}, {0, 0, 1}, {1, 1}},
        {{-w,  h, 0.0f}, {0, 0, 1}, {0, 1}}
    };

    data.Indices = { 0, 1, 2, 0, 2, 3 };

    return data;
}


MeshData MeshFactory::CreateSphere(float radius, unsigned int segments) {
    MeshData data;

    for (unsigned int y = 0; y <= segments; ++y) {
        for (unsigned int x = 0; x <= segments; ++x) {
            
            float xSegment = (float)x / (float)segments;
            float ySegment = (float)y / (float)segments;

            float xPos = std::cos(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);
            float yPos = std::cos(ySegment * M_PI); // Y ekseni yukarı
            float zPos = std::sin(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);

            Vertex v;
            v.Position = glm::vec3(xPos * radius, yPos * radius, zPos * radius);
            v.Normal = glm::vec3(xPos, yPos, zPos); // Kürede normal, pozisyonun normalize halidir
            v.TexCoords = glm::vec2(xSegment, ySegment);
            
            data.Vertices.push_back(v);
        }
    }

    for (unsigned int y = 0; y < segments; ++y) {
        for (unsigned int x = 0; x < segments; ++x) {
            unsigned int first = (y * (segments + 1)) + x;
            unsigned int second = first + segments + 1;

            data.Indices.push_back(first);
            data.Indices.push_back(second);
            data.Indices.push_back(first + 1);

            data.Indices.push_back(second);
            data.Indices.push_back(second + 1);
            data.Indices.push_back(first + 1);
        }
    }

    return data;
}