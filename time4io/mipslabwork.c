/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int* tRISE = 0xbf886100;
  *(tRISE) = 0;
  volatile int* porte = 0xbf886110;
  *(porte) = 0;
  TRISD |= 0x0FE0;
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  volatile int* porte = 0xbf886110;
  //last nibble is always F, the rest is set 0 -> F; Ex. getbtns: 000 -> 0xFFFF, 001 -> 0XFF0F, 110 -> 0x00FF
  int helper = ((((getbtns() & 1) ==0) * 0xF0) | (((getbtns() & 2) ==0) * 0xF00) | (((getbtns() & 4) == 0) * 0xF000)) | 0xF;
  //last nibble is always 0; getbtns "1" -> (hex)getsw(); Ex. getsw() = 7, getbtns = 011 -> 0x0770, 101 -> 7070
  int setval = (((getbtns() & 1) * getsw()) | (((getbtns() & 2) != 0) * getsw())<<4 | ((((getbtns() & 4) != 0) * getsw()))<<8) << 4;
  mytime &= helper;
  mytime |= setval;
  delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  (*porte)++;
  display_image(96, icon);
}
