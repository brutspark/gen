#include "gen.h"

#define F_PATH "home/dog/gen/gen_test/output/"

Gen::Gen()
{
    //comm=this->comm;
}

void Gen::gen(string f_name, string mcu, string p_name)
{

    const char *path_name=F_PATH;
    ofstream m_file(path_name);
    m_file.open("Makefile");
    m_file << "PRG = " << p_name << "\n";
    m_file << "OBJ = " << p_name << ".o\n";
    m_file << "MCU_TARGET = " << mcu << "\n";
    m_file << "OPTIMIZE = -O2\n";
    m_file << "DEFS = \n";
    m_file << "LIBS = \n";
    m_file << "CFLAGS=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes -Os -mcall-prologues\n";
    m_file << "#\n";
    m_file << p_name << ".hex : " << p_name << ".elf\n";
    m_file << "     avr-size " << p_name << ".elf\n";
    m_file << "     avr-objcopy -R .eeprom -O ihex " << p_name << ".elf" << p_name << ".hex\n";

    m_file << p_name << ".hex : " << p_name << ".o\n";
    m_file <<       "avr-gcc $(CFLAGS) -o " << p_name << ".elf -Wl,-Map, " << p_name << ".map " << p_name <<".o\n";

    m_file << p_name << ".o : " << p_name << ".c\n";
    m_file << "     avr-gcc $(CFLAGS) -Os -c " << p_name << ".c\n";
    m_file << "#\n";


    m_file.close();


}

void Gen::build()
{
    system("make ~/gen/gen_test/output/Makefile");
}

void Gen::prog()
{
    system("sudo avr-dude -p m8 -c ispmkII -e -U flash:w:.hex");
}


/*int main (int argc, char *argv[]) {
    
    string file_name;
for (int i = 0; i < argc; ++i)
{
  //if (argv[i] != " ")
  file_name = argv[i];
  //else if (argv[i] )
  //if (argv[i] == "")
}
       return 0;
}*/
