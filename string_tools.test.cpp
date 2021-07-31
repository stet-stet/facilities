#include"string_tools.hpp"
#include"essentials.hpp"
#include<cassert>

using namespace facilities;


template<typename T>
auto x() -> std::basic_string<T>
{
    auto temp = x<char>();
    return std::basic_string<T>(temp.begin(),temp.end());
}

template<>
auto x() -> std::string
{
    return "Lorem ipsum dolor sit amet,";
}


template<typename T>
void test_split_join(){
    std::basic_string<T> s {x<T>() };
    std::vector<std::basic_string<T> > ss = {
        convert<T>("Lorem"),
        convert<T>("ipsum"),
        convert<T>("dolor"),
        convert<T>("sit"),
        convert<T>("amet,")
    };

    auto sres = split(s,' ');

    assert(sres[0] == ss[0]);
    assert(sres==ss);
    assert( join(split(s)) == convert<T>("Loremipsumdolorsitamet,"));
    assert( join(split(s)," ") == s);
}

template<typename T>
void test_strip(){
    std::basic_string<T> s {x<T>()};
    std::basic_string<T> b = convert<T>("Lorem ipsum dolor sit amet");
    assert( strip(s,",") == b );
    assert( strip(s,"Lot,") == convert<T>("rem ipsum dolor sit ame") );
}

template<typename T>
void test_starts_with_ends_with(){
    std::basic_string<T> s {x<T>()};
    std::basic_string<T> b = convert<T>("Lorem"), c = convert<T>(" Lore");
    std::basic_string<T> comma = convert<T>("amet,"), nocomma = convert<T>("amet");
    assert(starts_with(s,b));
    assert(!starts_with(s,c));
    assert(ends_with(s,comma));
    assert(!ends_with(s,nocomma));
}


int main(){
    std::basic_string<char32_t> s{x<char32_t>()};
    test_split_join<char>();
    test_split_join<char32_t>();
    test_split_join<char16_t>();
    test_strip<char>();
    test_strip<char32_t>();
    test_strip<char16_t>();
    test_starts_with_ends_with<char>();
    test_starts_with_ends_with<char16_t>();
    test_starts_with_ends_with<char32_t>();
}


