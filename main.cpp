#include "gen.h"

int main()
{
    Gen obj;
    obj.gen("Makefile", "atmega328p", "led");
    obj.build();
    
    
return 0;

}
