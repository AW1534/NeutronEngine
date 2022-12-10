//
// Created by aw1lt on 08/12/22.
//

#ifndef NEUTRONEXAMPLEC_SHADER_H
#define NEUTRONEXAMPLEC_SHADER_H


#include <string>

namespace Neutron {
    class Shader {
    public:
        Shader(std::string path);

        std::string VertexSource;
        std::string FragmentSource;
        unsigned int id;

        Shader(std::string vs, std::string fs);
        ~Shader();

        static Shader ParseShader(const std::string& filepath);
        static unsigned int CompileShader(unsigned int type, const std::string& source);

        // utility uniform functions
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;

        void Enable();
        void Disable();

        void Constructor(std::string vs, std::string fs);
    };

}

#endif //NEUTRONEXAMPLEC_SHADER_H
