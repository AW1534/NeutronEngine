//
// Created by aw1lt on 06/12/22.
//

#ifndef _DLL_H
#define _DLL_H

#if defined(_MSC_VER)
//  Microsoft
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
//  GCC
    #define EXPORT __attribute__((visibility("default")))
    #define IMPORT
#else
//  do nothing and hope for the best?
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

#endif //_DLL_H
