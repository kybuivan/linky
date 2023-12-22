#pragma once
#include <assimp/material.h>
#include <core/math/math.hpp>
#include <screen/graphics/mesh.hpp>
#include <screen/graphics/shader.hpp>

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;
namespace linky
{
class Model
{
public:
    Model(std::string const& path, bool gamma = false);
    void Draw(Shader shader);

private:
    void loadModel(std::string const& path);

    void processNode(aiNode* node, const aiScene* scene);

    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

public:
    std::vector<Texture> textures_loaded;
    std::vector<Mesh>    meshes;
    std::string directory;
    std::string name;
    bool gammaCorrection;
};
}