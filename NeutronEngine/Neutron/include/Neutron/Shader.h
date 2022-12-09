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
        int id;

        Shader(std::string vs, std::string fs);

        static Shader ParseShader(const std::string& filepath);
        static unsigned int CompileShader(unsigned int type, const std::string& source);

        void Constructor(std::string vs, std::string fs);
    };

}

#endif //NEUTRONEXAMPLEC_SHADER_H
