#include <core/io/image_loader.hpp>
#include <core/io/file_stream.hpp>
#include <core/string/string.hpp>
#include <core/math/vector.hpp>
#include <screen/graphics/model.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace linky
{
unsigned int TextureFromFile(const char* path, const std::string& directory)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, format;
    auto pixels = core::image_loader::load_stb_image(filename, width, height, format);
    
    if (pixels)
    {
        GLenum gFormat;
        if (format == 1)
            gFormat = GL_RED;
        else if (format == 3)
            gFormat = GL_RGB;
        else if (format == 4)
            gFormat = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, gFormat, width, height, 0, gFormat, GL_UNSIGNED_BYTE, pixels.value());
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        delete pixels.value();
    }
    else
    {
        std::cout << pixels.error() << std::endl;
    }
    return textureID;
}

model::model(std::string const &path, bool gamma)
{
    m_gamma_correction = gamma;
    load_model(path);
}

void model::draw(Shader shader)
{
    for (auto mesh : m_meshes)
        mesh.draw(shader);
}

void model::load_model(std::string const &path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    m_directory = path.substr(0, path.find_last_of('/'));

    process_node(scene->mRootNode, scene);
}

void model::process_node(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(process_mesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        process_node(node->mChildren[i], scene);
    }
}

mesh model::process_mesh(aiMesh *ms, const aiScene *scene) 
{
    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<texture> textures;

    for (unsigned int i = 0; i < ms->mNumVertices; i++)
    {
        vertex vt;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.

        vector.x = ms->mVertices[i].x;
        vector.y = ms->mVertices[i].y;
        vector.z = ms->mVertices[i].z;
        vt.Position = vector;

        if (ms->HasNormals())
        {
            vector.x = ms->mNormals[i].x;
            vector.y = ms->mNormals[i].y;
            vector.z = ms->mNormals[i].z;
            vt.Normal = vector;
        }

        if (ms->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = ms->mTextureCoords[0][i].x;
            vec.y = ms->mTextureCoords[0][i].y;
            vt.TexCoords = vec;

            vector.x = ms->mTangents[i].x;
            vector.y = ms->mTangents[i].y;
            vector.z = ms->mTangents[i].z;
            vt.Tangent = vector;

            vector.x = ms->mBitangents[i].x;
            vector.y = ms->mBitangents[i].y;
            vector.z = ms->mBitangents[i].z;
            vt.Bitangent = vector;
        }
        else
            vt.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vt);
    }
    for (unsigned int i = 0; i < ms->mNumFaces; i++)
    {
        aiFace face = ms->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material = scene->mMaterials[ms->mMaterialIndex];

    std::vector<texture> diffuseMaps = load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<texture> specularMaps = load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    std::vector<texture> normalMaps = load_material_textures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    std::vector<texture> heightMaps = load_material_textures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return mesh(vertices, indices, textures);
}

std::vector<texture> model::load_material_textures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        
        bool skip = false;
        for (unsigned int j = 0; j < m_textures_loaded.size(); j++)
        {
            if (std::strcmp(m_textures_loaded[j].m_path.data(), str.C_Str()) == 0)
            {
                textures.push_back(m_textures_loaded[j]);
                skip = true; 
                break;
            }
        }
        if (!skip)
        {   
            texture tex;
            tex.m_id = TextureFromFile(str.C_Str(), this->m_directory);
            tex.m_name = typeName;
            tex.m_path = str.C_Str();
            textures.push_back(tex);
            m_textures_loaded.push_back(tex); 
        }
    }
    return textures;
}
}