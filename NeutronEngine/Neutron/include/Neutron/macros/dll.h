//
// Created by aw1lt on 06/12/22.
//

#ifndef _DLL_H
#define _DLL_H

#if defined(_MSC_VER)
//  Microsoft Visual C++
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#elif defined(__GNUC__) || defined(__GNUG__) || defined(__NINJA__) || defined(__GXX__) || defined(__clang__)
//  GCC, Clang, NinJa, G++, Clang
#define EXPORT __attribute__((visibility("default")))
#define IMPORT

#elif defined(__MINGW32__) || defined(__MINGW64__)
//  MinGW (Minimalist GNU for Windows)
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#else
//  Fallback for unknown compilers
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

#endif //_DLL_H
