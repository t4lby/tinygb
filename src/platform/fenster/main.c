#include "fenster.h"
#include <stdio.h>
#include <tinygb.h>

#define SCALING 4
#define W (SCALING * GB_WIDTH)
#define H (SCALING * GB_HEIGHT)
long rom_size;
char *rom_filename;
int scaling = SCALING;
int frameskip = 0;  // no skip
timing_t timing;

uint32_t buf[W * H];
struct fenster f = {
    .title = "tinygb",
    .width = W,
    .height = H,
    .buf = buf,
};

void delay(int ms){
  fenster_sleep(ms);
}

void update_window(uint32_t *framebuffer) {
}

void update_border(uint32_t *framebuffer) {
}

void resize_sgb_window() {
}

static int keyMapping[128] = {
  [90] = JOYPAD_A      , // z
  [88] = JOYPAD_B      , // x
  [10] = JOYPAD_START  , // enter
  //['a'] = JOYPAD_SELECT ,
  [19] = JOYPAD_RIGHT  , 
  [20] = JOYPAD_LEFT   , 
  [17] = JOYPAD_UP     , 
  [18] = JOYPAD_DOWN   , 
};

static int run() {
  rom_filename = "crystal.gbc";
  FILE *rom_file = fopen(rom_filename, "r");
  if(!rom_file) {
    write_log("unable to open %s for reading\n", rom_file);
    return -1;
  }
  fseek(rom_file, 0L, SEEK_END);
  rom_size = ftell(rom_file);
  fseek(rom_file, 0L, SEEK_SET);
  write_log("loading rom from file %s, %d KiB\n", rom_filename, rom_size/1024);

  rom = malloc(rom_size);
  if(!rom) {
    write_log("unable to allocate memory\n");
    fclose(rom_file);
    return -1;
  }

  if(!fread(rom, 1, rom_size, rom_file)) {
      write_log("an error occured while reading from rom file\n");
      fclose(rom_file);
      free(rom);
      return -1;
  }

  fclose(rom_file);

  // start emulation
  memory_start();
  cpu_start();
  display_start(f.buf);
  timer_start();
  sound_start();

  fenster_open(&f);
  while (fenster_loop(&f) == 0) {

    // input 
    for (int i = 0; i < 128; i++) {
      if (keyMapping[i]) {
        joypad_handle(f.keys[i], keyMapping[i]);
      }
    }


    for(timing.current_cycles = 0; timing.current_cycles < timing.main_cycles; ) {
        cpu_cycle();
        display_cycle();
        timer_cycle();
    }
  }
  fenster_close(&f);
  return 0;
}

#if defined(_WIN32)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine,
                   int nCmdShow) {
  (void)hInstance, (void)hPrevInstance, (void)pCmdLine, (void)nCmdShow;
  return run();
}
#else
int main() { return run(); }
#endif
