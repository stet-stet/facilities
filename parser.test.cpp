#include"parser.hpp"
#include"essentials.hpp"
#include<iostream>
using std::cout, std::endl;
using namespace facilities;
int main(int argc, char** argv){
    
    PARSE(argc,argv);

    if( SANITYCHECK(a,b) ){
        print("yes, a and b are present");
    }
    if( !SANITYCHECK(c) ){
        print("no, c isn't present");
    }

    RETRIEVE(a,to_vector<int>);
    RETRIEVE(b,csv_to_vector<long double>);

    for(auto&& x:a) cout << x << ',';
    cout<<endl;
    for(auto&& x:b) cout << x << ',';
    cout<<endl;

    UNPACK(c); // should throw and exit.
}
