#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "Mesh.h"
#include "Material.h"
#include <memory>

class MeshRenderer {
public:
    MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);

    void SetMesh(std::shared_ptr<Mesh> mesh);
    void SetMaterial(std::shared_ptr<Material> material);

    std::shared_ptr<Mesh> GetMesh() const { return mesh; }
    std::shared_ptr<Material> GetMaterial() const { return material; }

    void Render() const;

private:
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
};

#endif