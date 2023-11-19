
/* tinygb - a tiny gameboy emulator
   (c) 2022 by jewel */

#include <tinygb.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void write_log(const char *text, ...) {
    printf(text);
}

void open_log() {

}

void die(int status, const char *msg, ...) {

}
