#ifndef STET_STET_STET_ESSENTIALS_HPP
#define STET_STET_STET_ESSENTIALS_HPP

//C++17
#include<iostream>
#include<algorithm>
#include<typeinfo>
#include<string_view>
#include<cxxabi.h>

template<typename... Types>
std::ostream& output(std::ostream& out, Types... args){
    ( out << ... << args ) << std::endl;
    return out;
}

#define print(...) output(std::cout, __VA_ARGS__)
#define log(...) output(std::clog, __VA_ARGS__)
#define err(...) output(std::cerr,__VA_ARGS__)

//only on G++

#ifdef __GNUC__

std::string demangledTypename(std::string_view sv){
    int status;
    char * realname =  abi::__cxa_demangle(sv.data(),0,0,&status);
    std::string name(realname); free(realname);
    return name;
}

#define typenameof(a) demangledTypename(typeid(a).name())

#endif


#endif
