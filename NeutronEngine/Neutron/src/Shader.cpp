//
// Created by aw1lt on 08/12/22.
//

#include <fstream>
#include <sstream>
#include <glad/gl.h>
#include <vector>

#include "Neutron/Shader.h"
#include "Logger.h"
#include "glm/gtc/type_ptr.hpp"

namespace Neutron {
    Shader Shader::ParseShader(const std::string &filepath) {
        std::ifstream stream(filepath);

        std::string line;
        std::stringstream ss[2] = {};
        int type = ShaderType::NONE;
        if (filepath.ends_with(".vert") || filepath.ends_with(".vertex"))
            type = ShaderType::VERTEX;
        else if (filepath.ends_with(".frag") || filepath.ends_with(".fragment"))
            type = ShaderType::FRAGMENT;


        while (getline(stream, line)) {
            if (line.starts_with("//")) { // ignore comments
                continue;
            }
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
            }
            else {
                if (type != ShaderType::NONE) {
                    ss[(int)type] << line << '\n';
                } else if(!line.empty()) {
                    Logger::Warn("Shader code, But no Type has been detected yet. use #shader [type] to set the type");
                }
            }
        }

        std::string vert = ss[ShaderType::VERTEX].rdbuf()->in_avail() != 0 ? ss[ShaderType::VERTEX].str() : Shader::default_vert;
        std::string frag = ss[ShaderType::FRAGMENT].rdbuf()->in_avail() != 0 ? ss[ShaderType::FRAGMENT].str() : Shader::default_frag;

        return {vert, frag};
    }

    unsigned int Shader::CompileShader(unsigned int type, const std::string &source) {
        Logger::Info("Compiling shader of type " + std::to_string(type), "NEUTRON");
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            GLint log_length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);
            std::vector<char> v(log_length);
            glGetShaderInfoLog(id, log_length, nullptr, v.data());
            std::string s(begin(v), end(v));

            Logger::Warn(s, "NEUTRON");

            int length = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &result);
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            Logger::Warn("Failed to compile " + std::string(type == GL_VERTEX_SHADER ? "vertex" : "fragment") + "shader\n" + message, "NEUTRON");
            glDeleteShader(id);
            Logger::Log("hey");
            return 0;
        }

        return id;
    }

    static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
        // create a shader program
        unsigned int program = glCreateProgram();
        //Logger::Log(std::to_string(program));

        unsigned int vs = 0;
        unsigned int fs = 0;

        if (!vertexShader.empty()) {
            vs = Shader::CompileShader(GL_VERTEX_SHADER, vertexShader);
        }

        if (!fragmentShader.empty()) {
            fs = Shader::CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
        }



        glAttachShader(program, vs);
        glAttachShader(program, fs);

        glLinkProgram(program);

        GLint program_linked;

        glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
        Logger::Log("Shader Program (" + std::to_string(program) + ") link status: " + std::to_string((bool)program_linked), "NEUTRON");
        if (program_linked != GL_TRUE)
        {
            GLsizei log_length = 0;
            GLchar message[1024];
            glGetProgramInfoLog(program, 1024, &log_length, message);
            Logger::Warn(std::string("Failed to link shader program\n") + message, "NEUTRON");
        }

        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    void Shader::Constructor(const std::string& vs, const std::string& fs) {
        this->VertexSource = vs;
        this->FragmentSource = fs;
        this->id = CreateShader(vs, fs);
    }

    Shader::Shader(const std::string& vs, const std::string& fs) {
        Constructor(vs, fs);
    }

    Shader::Shader(const std::string& path) {
        Shader s = ParseShader(path);
        Constructor(s.VertexSource, s.FragmentSource);
    }

    void Shader::setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
    }

    void Shader::setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
    }

    void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void Shader::Enable() const {
        glUseProgram(this->id);
    }

    void Shader::Disable() {
        glUseProgram(0);
    }

    Shader::~Shader() {
        Disable();
        glDeleteProgram(this->id);
    }

}


