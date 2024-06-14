//
// Created by aw1lt on 03/12/22.
//

#ifndef NEUTRONENGINE_MATRIX_H
#define NEUTRONENGINE_MATRIX_H

#include "Logger.h"
#include "Neutron/Helper.h"

#include "Neutron/macros/dll.h"

namespace Neutron::Math {
    class Vector2;

    template <unsigned int W, unsigned int H>
    class EXPORT Matrix {
    public:
        unsigned int width = W;
        unsigned int height = H;

        double data [W][H];

        double& operator ()(unsigned int x = 0, unsigned int y = 0) {
            Logger::Assert(x < width && y < height, "Index out of bounds", 5);

            return data[x][y];
        }

        double operator ()(unsigned int x = 0, unsigned int y = 0) const {
            Logger::Assert(x < width && y < height, "Index out of bounds", 5);

            return data[x][y];
        }



        Matrix<W, H> operator +(const Matrix<W, W> other) {
            Matrix<W, H> res;

            for (int x : range(W)) {
                for (int y : range(W)) {
                    res[x][y] = other[x][y] + this[x][y];
                }
            }
        }

        template <unsigned int _W, unsigned int _H>
        Matrix<_W, H> operator *(const Matrix<_W, _H>& other) {
            Logger::Assert(_H == W, "The width of the left hand must be the height of the right hand side", 5);

            Matrix<_W, H> res;

            for (int x : range(_W)) {
                for (int y : range(_H)) {
                    double val = 0;

                    for (int i : range(W)) {
                        val += this->data[i][y] * other.data[x][i];
                    }

                    res.data[x][y] = val;
                }
            }

            return res;
        }

        template <unsigned int _W, unsigned int _H>
        Matrix<W, H> operator *= (const Matrix<_W, _H>& other) {
            Logger::Assert(_H == H, "The height of the matrix on the right hand side was different to the height of the matrix on the left");

            Matrix<W, H> result = other * (*this);
            this->data = result.data;
            return *this;
        }

        bool operator ==(const Matrix<W, H>& other) {
            for (int x : range(W)) {
                for (int y : range(H)) {
                    if (this->data[x][y] != other.data[x][y]) {
                        return false;
                    }
                }
            }

            return true;
        }

        bool operator !=(const Matrix<W, H>& other) {
            return !(*this == other);
        }

        operator std::string() {
            std::string res;

            for(int y : range(H)) {
                res.append("[ ");

                for (int x : range(W)) {
                    res.append(std::to_string(data[x][y]) + " ");
                }

                res.append("]\n");
            }

            return res;
        }

        Matrix(double data [W][H]) {
            Logger::Assert(W != 0 && H != 0, "Invalid Matrix size (Width and height should be 1 or higher)", 5);

            this->data = data;
        }

        Matrix() {
            Logger::Assert(W != 0 && H != 0, "Invalid Matrix size (Width and height should be 1 or higher)", 5);

            for (int x : range(W)) {
                for (int y : range(H)) {
                    data[x][y] = 0;
                }
            }
        }

        static Matrix<W, H> Identity() {
            Logger::Assert(W, "Invalid Matrix size (Width and height should be 1 or higher)", 5);
            Logger::Assert(W == H, "Width and height must be equal for Identity matrix", 5);

            Matrix<W, H> res;

            for (int i : range(W)) {
                res.data[i][i] = 1;
            }

            return res;
        }

        static Matrix<W, H> Translate(std::initializer_list<double> args) {
            Logger::Assert(W, "Invalid Matrix size (Width and height should be 1 or higher)", 5);
            Logger::Assert(args.size() == W - 1, "Args size should be less than width", 5);
            Logger::Assert(W == H, "Width and height must be equal for Scaling matrix", 5);

            Matrix<W, H> res;

            int index = 0;

            for (auto arg : args) {
                res.data[W-1][index] = arg;
                index++;
            }
            for (int i : range(W)) {
                res.data[i][i] = 1;
            }

            return res;
        }

        static Matrix<W, H> Scale(std::initializer_list<double> args) {
            Logger::Assert(W, "Invalid Matrix size (Width and height should be 1 or higher)", 5);
            Logger::Assert(args.size() == W - 1, "Args size should be exactly width - 1", 5);
            Logger::Assert(W == H, "Width and height must be equal for Translating matrix", 5);

            Matrix<W, H> res;

            int index = 0;

            for (auto arg : args) {
                res.data[index][index] = arg;
                index++;
            }

            res.data[W-1][W-1] = 1;

            return res;
        }
    };

} // Neutron

#endif //NEUTRONENGINE_MATRIX_H
