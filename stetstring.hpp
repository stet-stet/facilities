#ifndef STETSTRING_HPP_
#define STETSTRING_HPP_

/*
   strings made easier.
   - fluent interface
   - 
   written by Jayeon Yi(stet-stet) - with a HUGE influence from Dongryul Kim
   July 23rd, 2021
   Actually I have no idea what to write here (lol)   */

#include<string>
#include<string_view>
#include<memory>

namespace facilities{

// a set of tool functions
// TODO much later: extend everything to basic_string<T>

template<typename T>
inline std::vector<std::basic_string<T> > split(const std::basic_string<T>& s, T token=' '){
    //TODO: perfect forwarding.
}

template<typename T>
inline std::basic_string<T> strip(const std::basic_string<T>& s, const std::basic_string<T>& toStrip){
    size_t begin=0,end=s.size()-1;
    for(;;++begin){
        bool exists = false;
        for(T x: toStrip){
            if(x == s[begin]) { exists=true; break; }
        }
        if(!exists) break;
    }
    for(;;--end){
        bool exists = false;
        for(T x: toStrip){
            if(x == s[end]) { exists=true; break; }
        }
        if(!exists) break;
    }
    return s.substr(begin, end-begin+1);
}

#define MAKE_SPECIALIZED_STRIP(ttt,thewhitespaceliteral) \
    inline std::basic_string<ttt> strip(const std::basic_string<ttt>& s){ \
        return strip(s, thewhitespaceliteral); \
    }
MAKE_SPECIALIZED_STRIP(char, " \n\t"); //and so on. TODO start here.

class stetString{
    std::string s;
    public:
    
    template<typename... T>
    stetString(T&&... other) : s(other...) {}

    std::string substr(size_t a,size_t size){
        return s.substr(a,size);
    }

    
    // returning string_view from functions is bad practice
    // but what if we can limit 
    std::string_view substr(size_t a,size_t size){
        return std::string_view(s);
    }
};




}

#endif
