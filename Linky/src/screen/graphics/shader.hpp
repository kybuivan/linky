#pragma once

#include <glad/gl.h>
#include <core/math/math.hpp>
#include <string>

namespace linky
{
class Shader
{
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    
    ~Shader();
    
    void use()
    {
        glUseProgram(ID);
    }

    unsigned int get() const
    {
        return ID;
    }

    inline void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    inline void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    inline void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    inline void setMat4(const std::string& name, glm::mat4 value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

    inline void setVec2(const std::string& name, glm::vec2 vec2) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), vec2.x, vec2.y);
    }

    inline void setVec3(const std::string& name, float f0, float f1, float f2) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), f0, f1, f2);
    }

    inline void setVec3(const std::string& name, glm::vec3 vec3) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), vec3.x, vec3.y, vec3.z);
    }

private:
    void checkCompileErrors(unsigned int shader, std::string type);

private:
    unsigned int ID;
};
}