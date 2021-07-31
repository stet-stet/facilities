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
// TODO : how to make this comfortably usable for any basic_string<T>?

template<typename T=char>
inline std::vector<std::basic_string<T> > split(const std::basic_string<T>& s, T token=' '){    
    size_t count=0;
    for(const T& x: s){
        if(x==token) ++count;
    }
    std::vector<std::basic_string<T> > ret(count+1);
    size_t length=0,count2=0;
    for(size_t i=0;i<s.size();++i){
        if(s[i] == token){
            if(length==0) ret[count2++] = std::basic_string<T>();
            else ret[count2++] = s.substr(i-length, length);
            length=0;
        }
        else ++length;
    }
    if(length>0) ret[count2] = s.substr(s.size()-length,length);
    else ret[count2] = std::basic_string<T>();
    return ret;
}

//TODO: make an *efficient* split(const s::bs<T>&, const s::bs<T>&)

template<typename T>
inline auto strip(const std::basic_string<T>& s, std::basic_string<T> toStrip){
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

template<typename T, size_t N>
inline auto strip(const std::basic_string<T>& s, const T(&toStrip)[N]){
    std::basic_string<T> arg {toStrip, N};
    return strip(s, arg);
}

template<typename T, size_t N>
inline auto strip(const std::basic_string<T>& s, T toStrip){
    std::basic_string<T> arg { toStrip };
    return strip(s, arg);
}

#define MAKE_SPECIALIZED_STRIP(ttt,whitespacechars) \
    inline std::basic_string<ttt> strip(const std::basic_string<ttt>& s){ \
        return strip(s, whitespacechars); \
    }

MAKE_SPECIALIZED_STRIP(char, std::string(" \n\r\t\f\v") );
//TODO: come up with a viable way to extend this function to utf-8, non-8bit-char contexts(eg. wchar)

template<typename CTR, typename T=char
/*    typename = std::enable_if_t<
                    std::is_same< std::decay_t<decltype(std::declval<CTR>[0])>,
                                  std::basic_string<T> >::value
               >*/
>
inline std::basic_string<T> join(CTR&& list, std::basic_string<T> delimiter=""){
    //TODO: does this really have to take a vector?
    size_t sz=0;
    for(auto& x: list){
        sz += x.size();
    }
    std::basic_string<T> ret;
    ret.reserve(sz * sizeof(T) + delimiter.size()*(list.size()-1));
    for(auto it = list.begin();it != list.end();++it){
        if(it!=list.begin()) ret.append(delimiter);
        ret.append( *it );
    }
    ret.shrink_to_fit();
    return ret;
}

template<typename CTR, typename T, int N>
inline auto join(CTR&& list, const T(&delimiter)[N]){
    std::basic_string<T> arg {delimiter};
    return join(std::forward<CTR>(list),arg);
}

template<typename CTR, typename T>
inline auto join(CTR&& list, T delimiter){
    std::basic_string<T> arg {delimiter};
    return join(std::forward<CTR>(list),arg);
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
