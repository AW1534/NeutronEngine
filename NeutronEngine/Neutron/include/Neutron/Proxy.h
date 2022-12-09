//
// Created by aw1lt on 03/12/22.
//

#ifndef NEUTRONENGINE_PROXY_H
#define NEUTRONENGINE_PROXY_H

#include <string>
#include "Neutron/Math/Concepts.h"

namespace Neutron {
    template <typename T>
    class EXPORT Proxy {
    private:
        T* pointer;
    public:
        Proxy(T& ptr) : pointer(&ptr) {};
        Proxy() : pointer(NULL) {};

        static std::string to_string(const Proxy proxy) {
            return std::to_string(*proxy->pointer);
        }

        static inline void set_ref(Proxy<T>& p, T& v) { p.pointer = &v; }

        template <typename _T>
        operator _T () {
            return static_cast<_T>(*pointer);
        }

        T operator * () const {
            return *(this->pointer);
        }

        T* operator ->() {
            return this->pointer;
        }

        T operator -() {
            return -(*this->pointer);
        }


        T operator +() {
            return +(*this->pointer);
        }

        #pragma region interactions with other proxies

        T operator +(const Proxy<T> other) {
            return *this->pointer + *other.pointer;
        }

        T operator -(const Proxy<T> other) {
            return *this->pointer - *other.pointer;
        }

        T operator *(const Proxy<T> other) {
            return *this->pointer * *other.pointer;
        }

        T operator /(const Proxy<T> other) {
            return *this->pointer / *other.pointer;
        }

        T operator +=(const Proxy<T> other) {
            return *this->pointer += *other.pointer;
        }

        T operator -=(const Proxy<T> other) {
            return *this->pointer -= *other.pointer;
        }

        T operator *=(const Proxy<T> other) {
            return *this->pointer *= *other.pointer;
        }

        T operator /=(const Proxy<T> other) {
            return *this->pointer /= *other.pointer;
        }

        T operator =(Proxy<T> value) {
            Logger::Assert(this->pointer != nullptr, "cannot assign to nullptr, please use Proxy<T>::set_ref()");
            return *this->pointer = static_cast<T>(*value.pointer);
        }

        bool operator ==(Proxy<T> other) {
            return *other.pointer == *this->pointer;
        }

        bool operator !=(Proxy<T> other) {
            return *other.pointer != *this->pointer;
        }

        bool operator >(Proxy<T> other) {
            return *other.pointer > *this->pointer;
        }

        bool operator <(Proxy<T> other) {
            return *other.pointer < *this->pointer;
        }

        #pragma endregion

        #pragma region interactions with other variables

        template <typename _T>
        requires Number<_T>
        T operator +(const _T other) {
            return *this->pointer + other;
        }

        template <typename _T>
        requires Number<_T>
        T operator -(const _T other) {
            return *this->pointer - other;
        }

        template <typename _T>
        requires Number<_T>
        T operator *(const _T other) {
            return *this->pointer * other;
        }

        template <typename _T>
        requires Number<_T>
        T operator /(const _T other) {
            return *this->pointer / other;
        }

        template <typename _T>
        requires Number<_T>
        T operator +=(const _T other) {
            return *this->pointer += other;
        }

        template <typename _T>
        requires Number<_T>
        T operator -=(const _T other) {
            return *this->pointer -= other;
        }

        template <typename _T>
        requires Number<_T>
        T operator *=(const _T other) {
            return *this->pointer *= other;
        }

        template <typename _T>
        requires Number<_T>
        T operator /=(const _T other) {
            return *this->pointer /= other;
        }

        template <typename _T>
        requires Number<_T>
        T operator =(_T value) {
            Logger::Assert(this->pointer != nullptr, "cannot assign to nullptr, please use Proxy<T>::set_ref()");
            return *this->pointer = static_cast<T>(value);
        }

        template <typename _T>
        requires Number<_T>
        bool operator ==(_T other) {
            return other == *this->pointer;
        }

        template <typename _T>
        requires Number<_T>
        bool operator !=(_T other) {
            return other != *this->pointer;
        }

        template <typename _T>
        requires Number<_T>
        bool operator >(_T other) {
            return *this->pointer > other;
        }

        template <typename _T>
        requires Number<_T>
        bool operator <(_T other) {
            return  *this->pointer < other;
        }

        #pragma endregion

        friend std::ostream& operator <<(std::ostream& s, const Proxy& p) {
            return s << *p->pointer;
        }

        friend std::istream& operator >>(std::istream& s, const Proxy& p) {
            return *p->pointer >> s;
        }
    };
}
#endif //NEUTRONENGINE_PROXY_H
