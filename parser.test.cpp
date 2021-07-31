#include"parser.hpp"
#include"essentials.hpp"
#include<iostream>
using std::cout, std::endl;
using namespace facilities;
int main(int argc, char** argv){
    
    parser.parse(argc,argv);

    if( parser.batch_sanitycheck({"a","b"}) ){
        print("yes, a and b are present");
    }
    if( !parser.batch_sanitycheck({"c"})){
        print("no, c isn't present");
    }

    auto a = parser.retrieve("a",to_vector<int>);
    auto b = parser.retrieve("b",csv_to_vector<long double>);

    for(auto&& x:a) cout << x << ',';
    cout<<endl;
    for(auto&& x:b) cout << x << ',';
    cout<<endl;

    auto c = parser.get("c"); // should throw and exit.
}
