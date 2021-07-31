#ifndef ESSENTIAL_STRING_TOOLS_HPP
#define ESSENTIAL_STRING_TOOLS_HPP

/*
   strings made easier.(but a little bit slower)

   written by Jayeon Yi(stet-stet) - with a HUGE influence from Dongryul Kim
   July 23rd, 2021
   Actually I have no idea what to write here (lol)   */

#include<string>
#include<string_view>
#include<memory>
#include<vector>

//TODO:make these constexpr; as many as possible

namespace facilities{

// a set of tool functions

template<typename T, size_t N>
inline std::basic_string<T> convert(const char(&arr)[N]){
    return std::basic_string<T>(arr,arr+N-1); //minus the null char.
}

template<typename T, typename U=char>
inline std::vector<std::basic_string<T> > split(const std::basic_string<T>& s, U token=' '){    
    size_t count=0;
    for(const T& x: s){
        if(x==token) ++count;
    }
    std::vector<std::basic_string<T> > ret(count+1);
    size_t length=0,count2=0;
    for(size_t i=0;i<s.size();++i){
        if(s[i] == token){
            ret[count2++] = s.substr(i-length, length);
            length=0;
        }
        else ++length;
    }
    if(length>0) ret[count2] = s.substr(s.size()-length,length);
    else ret[count2] = std::basic_string<T>();
    return ret;
}

//TODO: make an *efficient* split(const s::bs<T>&, const s::bs<T>&)

template<typename T, typename U>
inline auto strip(const std::basic_string<T>& s, std::basic_string<U> toStrip)
    -> std::basic_string<T>
{
    size_t begin=0,end=s.size()-1;
    for(;;++begin){
        bool exists = false;
        for(U& x: toStrip){
            if(x == s[begin]) { exists=true; break; }
        }
        if(!exists) break;
    }
    for(;;--end){
        bool exists = false;
        for(U& x: toStrip){
            if(x == s[end]) { exists=true; break; }
        }
        if(!exists) break;
    }
    return s.substr(begin, end-begin+1);
}

template<typename T, size_t N>
inline auto strip(const std::basic_string<T>& s, const char (&toStrip)[N]){
    return strip(s, convert<T>(toStrip));
}

#define MAKE_SPECIALIZED_STRIP(ttt,whitespacechars) \
    inline std::basic_string<ttt> strip(const std::basic_string<ttt>& s){ \
        return strip(s, whitespacechars); \
    }

MAKE_SPECIALIZED_STRIP(char, convert<char>(" \n\r\t\f\v"));
MAKE_SPECIALIZED_STRIP(wchar_t, convert<wchar_t>(" \n\r\t\f\v"));
MAKE_SPECIALIZED_STRIP(char16_t, convert<char16_t>(" \n\r\t\f\v"));
MAKE_SPECIALIZED_STRIP(char32_t, convert<char32_t>(" \n\r\t\f\v"));
//TODO: come up with a viable way to extend this function to utf-8, non-8bit-char contexts(eg. wchar)

template<typename CTR, typename T>
inline auto join(CTR&& list, std::basic_string<T> delimiter)
    -> std::basic_string<typename CTR::value_type::value_type >
{
    size_t sz=0;
    for(auto& x: list){
        sz += x.size();
    }
    std::basic_string<T> ret;
    std::basic_string<T> delim (delimiter.begin(), delimiter.end()); //can we do this without this line?

    ret.reserve(sz * sizeof(T) + delim.size()*(list.size()-1) * sizeof(T) );
    for(auto it = list.begin();it != list.end();++it){
        if(it!=list.begin()) ret.append(delim);
        ret.append( *it );
    }
    ret.shrink_to_fit();
    return ret;
}

template<typename CTR, typename T = typename std::decay_t<CTR>::value_type::value_type>
inline auto join(CTR&& list){
    return join(std::forward<std::remove_reference_t<CTR>>(list), convert<T>(""));
}

template<typename CTR, int N, typename T = typename std::decay_t<CTR>::value_type::value_type>
inline auto join(CTR&& list, const char (&delimiter)[N]){
    return join(std::forward<std::remove_reference_t<CTR>>(list),convert<T>(delimiter));
}


//starts_with co
template<typename T>
inline bool starts_with(const std::basic_string<T>& s, const std::basic_string<T>& to_find){
    if(to_find.size() > s.size()) return false;
    auto s_it = s.begin();
    auto to_find_it = to_find.begin();
    for(; to_find_it!=to_find.end(); ++to_find_it,++s_it){
        if(*s_it != *to_find_it) return false;
    }
    return true;
} 

template<typename T>
inline bool ends_with(const std::basic_string<T>& s, const std::basic_string<T>& to_find){
    if(to_find.size() > s.size()) return false;
    auto s_it = s.rbegin();
    auto to_find_it = to_find.rbegin();
    for(; to_find_it != to_find.rend() ; ++s_it, ++to_find_it){
        if(*s_it != *to_find_it) return false;
    }
    return true;
}

}

#endif
