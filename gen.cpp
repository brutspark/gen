#include "gen.h"

Gen::Gen()
{
    //comm=this->comm;
}

void Gen::gen(string f_name, string mcu, string p_name)
{

    const char *path_name="/home/empolyee/HamakarqIO/";
    ofstream m_file(path_name);
    m_file.open("_Makefile");
    m_file << "PRG = " << p_name << "\n";
    m_file << "OBJ = " << p_name << ".o\n";
    m_file << "MCU_TARGET = " << mcu << "\n";
    m_file << "OPTIMIZE = -O2\n";
    m_file << "DEFS = \n";
    m_file << "LIBS = \n";
    m_file << "# You should not have to change anything below here.\n";
    m_file << "CC = avr-gcc\n";

    m_file << "# Override is only needed by avr-lib build system.\n";

    m_file << "override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)\n";
    m_file << "override LDFLAGS       = -Wl,-Map,$(PRG).map\n";

    m_file << "OBJCOPY        = avr-objcopy\n";
    m_file << "OBJDUMP        = avr-objdump\n";

    m_file << "all: $(PRG).elf lst text eeprom\n";

    m_file << "$(PRG).elf: $(OBJ)\n";
    m_file << "  	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)\n";

    m_file << "# dependency:\n";
    m_file << p_name << ".o: " << p_name << ".c" <<  " iocompat.h\n";

    m_file << "clean:\n";
    m_file << "	rm -rf *.o $(PRG).elf *.eps *.png *.pdf *.bak \n";
    m_file << "	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)\n";

    m_file << "lst:  $(PRG).lst\n";

    m_file << "%.lst: %.elf\n";
    m_file << "	$(OBJDUMP) -h -S $< > $@\n";

    m_file << "# Rules for building the .text rom images\n";

    m_file << "text: hex bin srec\n";

    m_file << "hex:  $(PRG).hex\n";
    m_file << "bin:  $(PRG).bin\n";
    m_file << "srec: $(PRG).srec\n";

    m_file << "%.hex: %.elf\n";
    m_file << "	$(OBJCOPY) -j .text -j .data -O ihex $< $@\n";

    m_file << "%.srec: %.elf\n";
    m_file << "	$(OBJCOPY) -j .text -j .data -O srec $< $@\n";

    m_file << "%.bin: %.elf\n";
    m_file << "	$(OBJCOPY) -j .text -j .data -O binary $< $@\n";

    m_file << "# Rules for building the .eeprom rom images\n";

    m_file << "eeprom: ehex ebin esrec\n";

    m_file << "hex:  $(PRG)_eeprom.hex\n";
    m_file << "bin:  $(PRG)_eeprom.bin\n";
    m_file << "srec: $(PRG)_eeprom.srec\n";

    m_file << "%_eeprom.hex: %.elf\n";
    m_file << "	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@ 	|| { echo empty $@ not generated; exit 0; }\n";

    m_file << "%_eeprom.srec: %.elf\n";
    m_file << "	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $@ || { echo empty $@ not generated; exit 0; }\n";

    m_file << "%_eeprom.bin: %.elf\n";
    m_file << "	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $@ || { echo empty $@ not generated; exit 0; }\n";

    m_file << "# Every thing below here is used by avr-libc's build system and can be ignored\n";
    m_file << "# by the casual user.\n";

    m_file << "FIG2DEV                 = fig2dev\n";
    m_file << "EXTRA_CLEAN_FILES       = *.hex *.bin *.srec\n";

    m_file << "dox: eps png pdf\n";

    m_file << "eps: $(PRG).eps\n";
    m_file << "png: $(PRG).png\n";
    m_file << "pdf: $(PRG).pdf\n";

    m_file << "%.eps: %.fig\n";
    m_file << "	$(FIG2DEV) -L eps $< $@\n";

    m_file << "%.pdf: %.fig\n";
    m_file << "	$(FIG2DEV) -L pdf $< $@\n";

    m_file << "%.png: %.fig\n";
    m_file << "	$(FIG2DEV) -L png $< $@\n";

    m_file.close();


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
