#ifndef STET_STET_STET_ESSENTIALS_HPP
#define STET_STET_STET_ESSENTIALS_HPP

//C++17
#include<iostream>
#include<algorithm>
#include<typeinfo>
#include<string_view>
#include<cxxabi.h>

template<typename... Types>
inline std::ostream& output(std::ostream& out, Types... args){
    ( out << ... << args ) << std::endl;
    return out;
}

#define print(...) output(std::cout, __VA_ARGS__)
#define log(...) output(std::clog, __VA_ARGS__)
#define err(...) output(std::cerr,__VA_ARGS__)

template<typename T>
inline std::ostream& iteroutput(std::ostream& out, const T& arg){
    out << "{";
    for(auto&& x: arg) out << x << ", ";
    out << "}"<<std::endl;
    return out;
}

#define iterprint(...) iteroutput(std::cout, __VA_ARGS__);
#define iterlog(...) iteroutput(std::clog, __VA_ARGS__);
#define itererr(...) iteroutput(std::cerr, __VA_ARGS__);

//only on G++

#ifdef __GNUC__

inline std::string demangledTypename(std::string_view sv){
    int status;
    char * realname =  abi::__cxa_demangle(sv.data(),0,0,&status);
    std::string name(realname); free(realname);
    return name;
}

template<typename T>
struct ThisIsAType{};

#define typenameof(a) demangledTypename(typeid(a).name())
#define nameoftype(t) demangledTypename(typeid(ThisIsAType<t>()).name())

#endif


#endif
