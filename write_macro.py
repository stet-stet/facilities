import sys
import os


def do(filename):
    with open(filename,'a') as file:
        for i in range(1,65):
            s = f"#define EXPAND_AS_STRING{i}("
            for j in range(1,i+1):
                s += f"_{j},"
            s = s[:-1]+") "
            for j in range(1,i+1):
                s += f"#_{j},"
            s = s[:-1]
            file.write(s+'\n')
        file.write('\n\n\n')
        for i in range(1,65):
            s = f"#define UNPACK_AS_DEFINITION{i}("
            for j in range(1,i+1):
                s += f"_{j},"
            s = s[:-1]+") "
            for j in range(1,i+1):
                s += f"SINGLE_DEFINITION(_{j}) "
            file.write(s+'\n')
        file.write("\n\n\n")



if __name__=="__main__":
    do(sys.argv[1])
