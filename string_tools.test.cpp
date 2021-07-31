#include"string_tools.hpp"
#include"essentials.hpp"
#include<cassert>

using namespace facilities;
std::string x = "Lorem ipsum dolor sit amet,";

void test_split_join(){
    std::string s {x};
    std::vector<std::string> ss = {"Lorem","ipsum","dolor","sit","amet,"};
    auto sres = split(s);
    print(typenameof(sres));
    print(sres[0],sres[1],sres[2]);

    assert(sres==ss);
    
    print(join(split(s))," ");
    assert( join(split(s)) == "Loremipsumdolorsitamet,");
    assert( join(split(s)," ") == s);
}

void test_strip(){
    std::string s {x};
    std::string b {"Lorem ipsum dolor sit amet"};
    assert( strip(s,",") == b );
}

void test_starts_with_ends_with(){
    std::string s {x};
    std::string b {"Lore"}, c{"lore"};
    std::string comma {"amet,"}, nocomma{"amet"};
    assert(starts_with(s,b));
    assert(!starts_with(s,c));
    assert(ends_with(s,comma));
    assert(!ends_with(s,nocomma));
}


int main(){
    test_split_join();
    test_strip();
    test_starts_with_ends_with();
}


