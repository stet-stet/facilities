#include"essentials.hpp"

int main(){
    int b;
    const int& c=b;
    int const* const d = &b;
    print(typenameof(b));
    print(typenameof(c),typenameof(d));
}
