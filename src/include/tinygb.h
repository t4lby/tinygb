
/* tinygb - a tiny gameboy emulator
   (c) 2022 by jewel */

#pragma once

#include <stdint.h>
#include <SDL.h>

#define GB_WIDTH    160
#define GB_HEIGHT   144

#define GB_CPU_SPEED        4194304 // Hz
#define CGB_CPU_SPEED       8388608

/* DISPLAY:

    Width                       160 px
    Height                      144 px
    Refresh rate                59.7 Hz
    Visible v-lines             144 lines
    Invisible v-lines           10 lines
    Total v-lines               154 lines
    Total refresh time          16.7504 ms
    Time per v-line             0.108769 ms
    Time for visible lines      15.6627 ms
    Time for invisible lines    1.08769 ms
    V-sync pause                1.08769 ms

 * VALUES TO BE USED TO KEEP THINGS IN SYNC:

    CPU Cycles/Millisecond      CPU_SPEED/1000
    CPU Cycles/Refresh Line     Above * Time per v-line

 */

#define REFRESH_RATE            59.7        // Hz
#define TOTAL_REFRESH_TIME      16.7504     // ms
#define REFRESH_TIME_LINE       0.108769    // ms
#define VSYNC_PAUSE             1.08769     // ms

typedef struct {
    int cpu_cycles_ms, cpu_cycles_vline, cpu_cycles_timer;
    int current_cycles;
    int main_cycles;    // how many times we should cycle in main()
} timing_t;

typedef struct {
    uint16_t af, bc, de, hl, sp, pc, ime;
} cpu_t;

#define FLAG_ZF     0x80
#define FLAG_N      0x40
#define FLAG_H      0x20
#define FLAG_CY     0x10

extern long rom_size;
extern void *rom, *ram;
extern int is_cgb;

extern int cpu_speed;

extern SDL_Window *window;
extern timing_t timing;

void open_log();
void write_log(const char *, ...);
void die(int, const char *, ...);
void memory_start();
void cpu_start();
void display_start();
void timer_start();
void cpu_cycle();
void cpu_log();

uint8_t read_byte(uint16_t);
uint16_t read_word(uint16_t);
void write_byte(uint16_t, uint8_t);

// interrupts
uint8_t if_read();
uint8_t ie_read();

// display
void write_display_io(uint16_t, uint8_t);
uint8_t read_display_io(uint16_t);
void display_cycle();

// serial
void sb_write(uint8_t);
void sc_write(uint8_t);

// timer
void timer_write(uint16_t, uint8_t);
void timer_cycle();