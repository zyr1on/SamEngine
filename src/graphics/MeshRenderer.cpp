#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
    : mesh(mesh), material(material) {}

void MeshRenderer::SetMesh(std::shared_ptr<Mesh> mesh) {
    this->mesh = mesh;
}

void MeshRenderer::SetMaterial(std::shared_ptr<Material> material) {
    this->material = material;
}

void MeshRenderer::Render() const {
    if (mesh && material) {
        material->Apply();
        mesh->Draw();
    }
}