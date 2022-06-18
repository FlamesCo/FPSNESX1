
#include <iostream>
#include <cstdio>
#include <cstring>

#include "cpu.h"
#include "ppu.h"
#include "memory.h"
#include "cartridge.h"
#include "apu.h"
#include "input.h"
#include "snes.h"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Usage: ./snes9x <rom file>\n");
        return 0;
    }

    // Load ROM file
    FILE* rom = fopen(argv[1], "rb");
    if(!rom) {
        printf("Error opening %s\n", argv[1]);
        return 1;
    }

    // Initialize emulator
    SNES snes;
    snes.init();

    // Load cartridge
    snes.cartridge.load(rom);

    // Reset emulator
    snes.cpu.reset();

    // Main emulation loop
    while(1) {
        snes.cpu.execute();
        snes.ppu.execute();
        snes.apu.execute();
    }

    return 0;
}
