# facilities
essential facilities for any development work - compiled into a single header. WIP


## parser

An easy and painless way to make command-line tools.

```
#include"parser.hpp"

int main(int argc,char** argv){
    PARSE(argc, argv);
    if(SANITYCHECK(arg1,arg2,arg3)){
    }
    UNPACK( arg1, arg2 );
    RETRIEVE( arg3, to_vector<long double> );

    print(arg1[0]);
    print(arg2[0]);
    iterprint(arg3);
}

```

compile and try:

```
./a.out --arg1 hi --arg2 hello --arg3 3.1415 9265358.9793238 4.62643 38327.33
```

support & shorthands for default arguments are currently under construction.
