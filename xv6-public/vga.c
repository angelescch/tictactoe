#include "types.h"
#include "defs.h"
#include "memlayout.h"
#include "x86.h"

#define VGA_AC_INDEX        0x3C0
#define VGA_AC_WRITE        0x3C0
#define VGA_AC_READ         0x3C1
#define VGA_MISC_WRITE      0x3C2
#define VGA_SEQ_INDEX       0x3C4
#define VGA_SEQ_DATA        0x3C5
#define VGA_DAC_READ_INDEX  0x3C7
#define VGA_DAC_WRITE_INDEX 0x3C8
#define VGA_DAC_DATA        0x3C9
#define VGA_MISC_READ       0x3CC
#define VGA_GC_INDEX        0x3CE
#define VGA_GC_DATA         0x3CF
#define VGA_CRTC_INDEX      0x3D4
#define VGA_CRTC_DATA       0x3D5
#define VGA_INSTAT_READ     0x3DA
#define VGA_NUM_SEQ_REGS    5
#define VGA_NUM_CRTC_REGS   25
#define VGA_NUM_GC_REGS     9
#define VGA_NUM_AC_REGS     21
#define VGA_NUM_REGS    (1 + VGA_NUM_SEQ_REGS + VGA_NUM_CRTC_REGS + \
                        VGA_NUM_GC_REGS + VGA_NUM_AC_REGS)

unsigned char g_320x200x256[] =
{
/* MISC */
  0x63,
/* SEQ */
  0x03, 0x01, 0x0F, 0x00, 0x0E,
/* CRTC */
  0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
  0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x9C, 0x0E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3,
  0xFF,
/* GC */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
  0xFF,
/* AC */
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
  0x41, 0x00, 0x0F, 0x00, 0x00
};

unsigned char g_80x25_text[] =
{
/* MISC */
  0x67,
/* SEQ */
  0x03, 0x00, 0x03, 0x00, 0x02,
/* CRTC */
  0x5F, 0x4F, 0x50, 0x82, 0x55, 0x81, 0xBF, 0x1F,
  0x00, 0x4F, 0x0D, 0x0E, 0x00, 0x00, 0x00, 0x50,
  0x9C, 0x0E, 0x8F, 0x28, 0x1F, 0x96, 0xB9, 0xA3,
  0xFF,
/* GC */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0E, 0x00,
  0xFF,
/* AC */
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
  0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
  0x0C, 0x00, 0x0F, 0x08, 0x00
};

// void set_palette(int palette[])
// {
//   for (int i = 0; i < 256; i++){
//     for (int)
//   }
// }

void
write_regs(unsigned char *regs)
{
  unsigned i;
/* write MISCELLANEOUS reg */
  outb(VGA_MISC_WRITE, *regs);
  regs++;
/* write SEQUENCER regs */
  for(i = 0; i < VGA_NUM_SEQ_REGS; i++){
    outb(VGA_SEQ_INDEX, i);
    outb(VGA_SEQ_DATA, *regs);
    regs++;
  }
/* unlock CRTC registers */
  outb(VGA_CRTC_INDEX, 0x03);
  outb(VGA_CRTC_DATA, inb(VGA_CRTC_DATA) | 0x80);
  outb(VGA_CRTC_INDEX, 0x11);
  outb(VGA_CRTC_DATA, inb(VGA_CRTC_DATA) & ~0x80);
/* make sure they remain unlocked */
  regs[0x03] |= 0x80;
  regs[0x11] &= ~0x80;
/* write CRTC regs */
  for(i = 0; i < VGA_NUM_CRTC_REGS; i++){
    outb(VGA_CRTC_INDEX, i);
    outb(VGA_CRTC_DATA, *regs);
    regs++;
  }
/* write GRAPHICS CONTROLLER regs */
  for(i = 0; i < VGA_NUM_GC_REGS; i++){
    outb(VGA_GC_INDEX, i);
    outb(VGA_GC_DATA, *regs);
    regs++;
  }
/* write ATTRIBUTE CONTROLLER regs */
  for(i = 0; i < VGA_NUM_AC_REGS; i++){
    (void)inb(VGA_INSTAT_READ);
    outb(VGA_AC_INDEX, i);
    outb(VGA_AC_WRITE, *regs);
    regs++;
  }
/* lock 16-color palette and unblank display */
  (void)inb(VGA_INSTAT_READ);
  outb(VGA_AC_INDEX, 0x20);
}

void
read_regs(unsigned char *regs)
{
  unsigned i;
/* read MISCELLANEOUS reg */
  *regs = inb(VGA_MISC_READ);
  regs++;
/* read SEQUENCER regs */
  for(i = 0; i < VGA_NUM_SEQ_REGS; i++){
    outb(VGA_SEQ_INDEX, i);
    *regs = inb(VGA_SEQ_DATA);
    regs++;
  }
/* read CRTC regs */
  for(i = 0; i < VGA_NUM_CRTC_REGS; i++){
    outb(VGA_CRTC_INDEX, i);
    *regs = inb(VGA_CRTC_DATA);
    regs++;
  }
/* read GRAPHICS CONTROLLER regs */
  for(i = 0; i < VGA_NUM_GC_REGS; i++){
    outb(VGA_GC_INDEX, i);
    *regs = inb(VGA_GC_DATA);
    regs++;
  }
/* read ATTRIBUTE CONTROLLER regs */
  for(i = 0; i < VGA_NUM_AC_REGS; i++){
    (void)inb(VGA_INSTAT_READ);
    outb(VGA_AC_INDEX, i);
    *regs = inb(VGA_AC_READ);
    regs++;
  }
/* lock 16-color palette and unblank display */
  (void)inb(VGA_INSTAT_READ);
  outb(VGA_AC_INDEX, 0x20);
}

void
modeswitch(int mode)
{
  switch (mode)
  {
  case 0:
    write_regs(g_80x25_text);
    break;
  case 1:
    write_regs(g_320x200x256);
    break;
  }
}

void
plotpixel(int x, int y, int color)
{
  int ofset = 0xA0000 + 320*y + x; 
  *(char *)P2V(ofset) = color;
}

void
plotrectangle(int x1, int y1, int x2, int y2, int color)
{
  for(int x=x1; x<x2; x++){
    for(int y=y1; y<y2; y++){
      plotpixel(x, y, color);
    }
  }
}

/*void
+printimage(int whith, int length, int x, int y, char *bitmap, int scale)
 {
   int ofset;
-  for(int i = y; i < length + y; i++ ){
-    for(int j = x; j < whith + x; j++){
-      ofset = 0xA0000 + 320*i + j;
-      *(char *)P2V(ofset) = bitmap[(i-y)*whith+(j-x)];
+  for(int i = y; i < length + y; i++){
+      for(int j = x; j < whith + x; j++){
+          ofset = 0xA0000 + 320*(i+k_y) + j + k_x;
+          *(char *)P2V(ofset) = bitmap[(i-y)*whith+(j-x)];
+        }
+      }
     }
   }
-}
+}*/

void
printimage(int whith, int length, int x, int y, char *bitmap, int scale)
{
  for(int i = 0; i < length; i++){
    for(int j = 0; j < whith; j++){
      plotrectangle( x + scale*j    , y + scale*i,
                     x + scale*(j+1), y + scale*(i+1), bitmap[i*whith+j]
                   );
    }
  }
}

void
vgainit(void)
{
  *(int *)P2V(0xB8F90) = 0x3E00 + ' ';
  *(int *)P2V(0xB8F92) = 0x3E00 + 'S';
  *(int *)P2V(0xB8F94) = 0x3E00 + 'O';
  *(int *)P2V(0xB8F96) = 0x3E00 + '2';
  *(int *)P2V(0xB8F98) = 0x3E00 + '0';
  *(int *)P2V(0xB8F9A) = 0x3E00 + '2';
  *(int *)P2V(0xB8F9C) = 0x3E00 + '1';
  *(int *)P2V(0xB8F9E) = 0x3E00 + ' ';

  modeswitch(1);
  // for(int i = 0xA0000; i < 0xBFFFF; i++){
  //   *(char *)P2V(i) = i % 15;
  // }
  modeswitch(0);
}
