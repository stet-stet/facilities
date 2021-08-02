#ifndef STET_COMMAND_LINE_PARSER_HPP
#define STET_COMMAND_LINE_PARSER_HPP

#include<unordered_map>
#include<vector>
#include<string>
#include"string_tools.hpp"
#include<algorithm>


#include<iostream>

namespace facilities{

class COMMAND_LINE_PARSER_DO_NOT_INSTANTIATE{
    std::unordered_map<std::string, std::vector<std::string>> the_map;
    public:
    void parse(int argc, char** argv){
        std::vector<std::string> current;
        std::string argname = "";
        std::string dd = "--";
        for(int i=1;i<argc;++i){
            if(starts_with(std::string(argv[i]),dd)){
                the_map[argname] = current;
                current.clear();
                argname = std::string(argv[i]+2);
            }
            else{
                current.push_back(argv[i]);
            }
        }
        the_map[argname] = current;
    }
    std::vector<std::string> get(std::string arg){
        if(the_map.count(arg)) return the_map[arg];
        else throw std::invalid_argument(
                "Either)\n"
                "  I. invalid arguments were given, or\n"
                "  II. parser.parse was not called\n"
                );
    }
    
    template<typename T>
    auto retrieve(std::string arg, T (*processor)(const std::vector<std::string>&)){
        return processor(get(arg));
    }

    bool sanitycheck(std::string arg) const{
        return the_map.count(arg)>0;
    }

    bool batch_sanitycheck(const std::vector<std::string>& args) const{
        return std::all_of(args.begin(),args.end(),
                [*this](std::string arg){return sanitycheck(arg);} );
    }
};

static COMMAND_LINE_PARSER_DO_NOT_INSTANTIATE parser;

//helper functions for parser.

template<typename T>
T sto(const std::string& x){
    throw std::invalid_argument("sto<?> called, this should not have been called");
}

#define DEFINE_STO( type, func ) \
template<> \
type sto<type>(const std::string& x){\
    return func(x);\
}

DEFINE_STO(int,stoi);
DEFINE_STO(long,stol);
DEFINE_STO(long long,stoll);
DEFINE_STO(unsigned long, stoul);
DEFINE_STO(unsigned long long, stoull);
DEFINE_STO(float, stof);
DEFINE_STO(double, stod);
DEFINE_STO(long double, stold);
DEFINE_STO(std::string, std::string);

template<typename T>
std::vector<T> to_vector(const std::vector<std::string>& arg){
    std::vector<T> ret(arg.size());
    for(auto a = arg.begin(),r = ret.begin();
            a != arg.end();
            ++a,++r){
        *r = sto<T>(*a);
    }
    return ret;
}

template<typename T>
std::vector<T> csv_to_vector(const std::vector<std::string>& arg){
    auto combined = join(arg,"");
    return to_vector<T>( split(combined, ',' ) );
}

//write one for MSVC too
#include "parsermacro.hpp"


} //namespace facilities
#endif
