//
// Created by aw1lt on 08/12/22.
//

#ifndef NEUTRONENGINE_SHADER_H
#define NEUTRONENGINE_SHADER_H

//TODO: Shaders seem to crash when using default

#include <string>
#include "glm/fwd.hpp"

namespace Neutron {
    class Shader {
    public:
        struct ShaderType {
            inline static int NONE = -1; inline static int VERTEX = 0; inline static int FRAGMENT = 1;
        };

        std::string VertexSource;
        std::string FragmentSource;
        unsigned int id;

        inline static std::string default_vert = "#version 330 core\n"
                                                 "layout(location = 0) in vec4 position;\n"
                                                 "void main()  {\n"
                                                 "    gl_Position = position;\n"
                                                 "}";
        inline static std::string default_frag = "#version 330 core\n"
                                                 "layout(location = 0) out vec4 color;\n"
                                                 "void main()  {\n"
                                                 "    color = vec4(1, 1, 1, 1);\n"
                                                 "}";



        Shader(const std::string& vs, const std::string& fs);
        explicit Shader(const std::string& path);
        ~Shader();

        static Shader ParseShader(const std::string& filepath);
        static unsigned int CompileShader(unsigned int type, const std::string& source);

        // utility uniform functions
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setMat4(const std::string& name, const glm::mat4& mat) const; // TODO: use Math::Matrix


        void Enable() const;
        static void Disable();

        void Constructor(const std::string& vs, const std::string& fs);
    };

}

#endif //NEUTRONENGINE_SHADER_H
