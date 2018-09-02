#include <stdio.h>

void io_hlt(void);
void io_cli(void);
void io_out8(int port, int data);
int io_load_eflags(void);
void io_store_eflags(int eflags);

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);
void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
void init_screen(char * vram, int xsize, int ysize);
void putfont8(char * vram, int xsize, int x, int y, char c, char *font);
void putfont8_asc(char * vram, int xsize, int x, int y, char c, unsigned char *s);
void init_mouse_cursor8(char *mouse, char fc, char edge, char bc);
void putblock8_8(char *vram, int vxsize, int pxsize,
    int pysize, int px0, int py0, char *buf, int bxsize);

#define COL8_000000  0
#define COL8_FF0000  1
#define COL8_00FF00  2
#define COL8_FFFF00  3
#define COL8_0000FF  4
#define COL8_FF00FF  5
#define COL8_00FFFF  6
#define COL8_FFFFFF  7
#define COL8_C6C6C6  8
#define COL8_840000  9
#define COL8_008400 10
#define COL8_848400 11
#define COL8_000084 12
#define COL8_840084 13
#define COL8_008484 14
#define COL8_848484 15

struct BOOTINFO {
  char cyls, leds, vmode, reserve;
  short scrnx, scrny;
  char *vram;
};

void HariMain(void) {

  struct BOOTINFO *binfo = (struct BOOTINFO *) 0x0ff0;

  init_palette();

  init_screen(binfo->vram, binfo->scrnx, binfo->scrny);

	char mcursor[256];
  init_mouse_cursor8(mcursor, COL8_FFFFFF, COL8_000000, COL8_008484);

  int mx, my;
  // 画面中央にマウスカーソルが表示されるように計算
  mx = (binfo->scrnx - 16) / 2;
  my = (binfo->scrny - 28 - 16) / 2; // 縦はタスクバーの28pxを考慮
  // マウスを描画
  putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
  // 座標を画面左上に描画
	char s[40];
  sprintf(s, "(%d, %d)", mx, my);
  putfont8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);

  for(;;){
	  io_hlt();
  }
}

void putblock8_8(char *vram, int vxsize, int pxsize,
    int pysize, int px0, int py0, char *buf, int bxsize) {
  int x, y;
  for(y = 0; y < pysize; y++) {
    for(x = 0; x < pxsize; x++) {
      vram[(py0 + y) * vxsize + (px0 + x)] = buf[y * bxsize + x];
    }
  }
  return;
}


void init_mouse_cursor8(char *mouse, char fc, char edge, char bc) {
  // マウスカーソルを準備
  static char cursor[16][16] = {
		"**************..",
		"*OOOOOOOOOOO*...",
		"*OOOOOOOOOO*....",
		"*OOOOOOOOO*.....",
		"*OOOOOOOO*......",
		"*OOOOOOO*.......",
		"*OOOOOOO*.......",
		"*OOOOOOOO*......",
		"*OOOO**OOO*.....",
		"*OOO*..*OOO*....",
		"*OO*....*OOO*...",
		"*O*......*OOO*..",
		"**........*OOO*.",
		"*..........*OOO*",
		"............*OO*",
		".............***"
  };

  int x, y;
  for(y = 0; y < 16; y++) {
    for(x = 0; x < 16; x++) {
      if(cursor[y][x] == '*') {
        mouse[y * 16 + x] = edge;
      }
      if(cursor[y][x] == 'O') {
        mouse[y * 16 + x] = fc;
      }
      if(cursor[y][x] == '.') {
        mouse[y * 16 + x] = bc;
      }
    }
  }
  return;
}

void putfont8_asc(char * vram, int xsize, int x, int y, char c, unsigned char *s) {
  extern char hankaku[4096];
  int i;
  for(i=0; *s != 0x00; i++, s++) {
    putfont8(vram, xsize, x + i*8, y, c, hankaku + *s * 16);
  }
}


void putfont8(char * vram, int xsize, int x, int y, char c, char *font) {
  int i;
  char *p, d/*data*/;
  for(i=0; i<16; i++) {
    p = vram + (y + i) * xsize + x;
    d = font[i];
    if((d & 0x80) != 0) {p[0] = c;}
    if((d & 0x40) != 0) {p[1] = c;}
    if((d & 0x20) != 0) {p[2] = c;}
    if((d & 0x10) != 0) {p[3] = c;}
    if((d & 0x08) != 0) {p[4] = c;}
    if((d & 0x04) != 0) {p[5] = c;}
    if((d & 0x02) != 0) {p[6] = c;}
    if((d & 0x01) != 0) {p[7] = c;}
  }
  return;
}


void init_screen(char * vram, int xsize, int ysize) {
  boxfill8(vram, xsize, COL8_008484,          0,          0, xsize -  1, ysize - 29);
  boxfill8(vram, xsize, COL8_C6C6C6,          0, ysize - 28, xsize -  1, ysize - 28);
  boxfill8(vram, xsize, COL8_FFFFFF,          0, ysize - 27, xsize -  1, ysize - 27);
  boxfill8(vram, xsize, COL8_C6C6C6,          0, ysize - 26, xsize -  1, ysize -  1);

  boxfill8(vram, xsize, COL8_FFFFFF,          3, ysize - 24,         59, ysize - 24);
  boxfill8(vram, xsize, COL8_FFFFFF,          2, ysize - 24,          2, ysize -  4);
  boxfill8(vram, xsize, COL8_848484,          3, ysize -  4,         59, ysize -  4);
  boxfill8(vram, xsize, COL8_848484,         59, ysize - 23,         59, ysize -  5);
  boxfill8(vram, xsize, COL8_000000,          2, ysize -  3,         59, ysize -  3);
  boxfill8(vram, xsize, COL8_000000,         60, ysize - 24,         60, ysize -  3);

  boxfill8(vram, xsize, COL8_848484, xsize - 47, ysize - 24, xsize -  4, ysize - 24);
  boxfill8(vram, xsize, COL8_848484, xsize - 47, ysize - 23, xsize - 47, ysize -  4);
  boxfill8(vram, xsize, COL8_FFFFFF, xsize - 47, ysize -  3, xsize -  4, ysize -  3);
  boxfill8(vram, xsize, COL8_FFFFFF, xsize -  3, ysize - 24, xsize -  3, ysize -  3);
}

void boxfill8( unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1) {
  int x, y;
  for(y = y0; y <= y1; y++) {
    for(x = x0; x <= x1; x++) {
      vram[y * xsize + x] = c;
    }
  }
}

void init_palette(void) {
  static unsigned char table_rgb[16 * 3] = {
    0x00, 0x00, 0x00, /*  0:黒 */
    0xff, 0x00, 0x00, /*  1:明るい赤 */
    0x00, 0xff, 0x00, /*  2:明るい緑 */
    0xff, 0xff, 0x00, /*  3:明るい黄色 */
    0x00, 0x00, 0xff, /*  4:明るい青 */
    0xff, 0x00, 0xff, /*  5:明るい紫 */
    0x00, 0xff, 0xff, /*  6:明るい水色 */
    0xff, 0xff, 0xff, /*  7:白 */
    0xc6, 0xc6, 0xc6, /*  8:明るい灰色 */
    0x84, 0x00, 0x00, /*  9:暗い赤 */
    0x00, 0x84, 0x00, /* 10:暗い緑 */
    0x84, 0x84, 0x00, /* 11:暗い黄色 */
    0x00, 0x00, 0x84, /* 12:暗い青 */
    0x84, 0x00, 0x84, /* 13:暗い紫 */
    0x00, 0x84, 0x84, /* 14:暗い水色 */
    0x84, 0x84, 0x84  /* 15:暗い水色 */
  };
  set_palette(0, 15, table_rgb);
  return;

  /* static char 命令は、データにしか使えないけどDB命令相当 */
}

void set_palette(int start, int end, unsigned char *rgb) {
  int i, eflags;
  eflags = io_load_eflags(); /* 割り込み許可フラグの値を記録する */
  io_cli();                  /* 許可フラグを0にして割り込みを禁止にする */
  io_out8(0x03c8, start);
  for(i = start; i <= end; i++) {
    io_out8(0x03c9, rgb[0] / 4);
    io_out8(0x03c9, rgb[1] / 4);
    io_out8(0x03c9, rgb[2] / 4);
    rgb += 3;
  }
  io_store_eflags(eflags); /* 割り込み許可フラグを元に戻す */
  return;
}
