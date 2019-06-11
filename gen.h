#ifndef GEN_H
#define GEN_H

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Gen
{

private:

    char comm;

public:

    Gen();

    void gen(string, string, string);

    void build();

    void prog();

    void del();

    void status();

};


#endif
