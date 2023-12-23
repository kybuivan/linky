#pragma once
#include <assimp/material.h>
#include <core/math/math.hpp>
#include <screen/graphics/mesh.hpp>
#include <screen/graphics/shader.hpp>

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;

namespace linky {
class model {
public:
    model(std::string const& path, bool gamma = false);
    void draw(Shader shader);

private:
    void load_model(std::string const& path);

    void process_node(aiNode* node, const aiScene* scene);

    mesh process_mesh(aiMesh* mesh, const aiScene* scene);

    std::vector<texture> load_material_textures(aiMaterial* mat, aiTextureType type, std::string typeName);

public:
    std::vector<texture> m_textures_loaded;
    std::vector<mesh>    m_meshes;
    std::string m_directory;
    std::string m_name;
    bool m_gamma_correction;
};
}