//
// Created by aw1lt on 08/12/22.
//

#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <vector>

#include "Neutron/Shader.h"
#include <Logger/Logger.h>

namespace Neutron {
    Shader Shader::ParseShader(const std::string &filepath) {
        std::ifstream stream(filepath);

        std::string line;
        std::stringstream ss[2] = {};
        int type = ShaderType::NONE;
        if (filepath.ends_with(".vert"))
            type = ShaderType::VERTEX;
        else if (filepath.ends_with(".frag"))
            type = ShaderType::FRAGMENT;


        while (getline(stream, line)) {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
            }
            else {
                if (type != ShaderType::NONE) {
                    ss[(int)type] << line << '\n';
                } else if(line != "") {
                    Logger::Log("Shader code, But no Type has been detected yet. Visit (URL) to learn more.");
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
            glGetShaderInfoLog(id, log_length, NULL, v.data());
            std::string s(begin(v), end(v));

            Logger::Warn(s, "NEUTRON");

            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &result);
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            Logger::Warn("Failed to compile " + std::string(type == GL_VERTEX_SHADER ? "vertex" : "fragment") + "shader\n" + message, "NEUTRON");
            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
        // create a shader program
        unsigned int program = glCreateProgram();
        Logger::Log(std::to_string(program));

        unsigned int vs = 0;
        unsigned int fs = 0;

        if (vertexShader != "") {
            vs = Shader::CompileShader(GL_VERTEX_SHADER, vertexShader);
        }

        if (fragmentShader != "") {
            fs = Shader::CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
        }



        glAttachShader(program, vs);
        glAttachShader(program, fs);

        glLinkProgram(program);

        GLint program_linked;

        glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
        Logger::Log("Program link status" + std::to_string((bool)program_linked), "NEUTRON");
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

    void Shader::Constructor(std::string vs, std::string fs) {
        this->VertexSource = vs;
        this->FragmentSource = fs;
        this->id = CreateShader(vs, fs);
    }

    Shader::Shader(std::string vs, std::string fs) {
        Constructor(vs, fs);
    }

    Shader::Shader(std::string path) {
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
        glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
    }

    void Shader::Enable() {
        glUseProgram(this->id);
    }

    void Shader::Disable() {
        glUseProgram(0);
    }

    Shader::~Shader() {
        glDeleteProgram(this->id);
    }

}


