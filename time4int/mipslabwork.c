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
// #include <stdio.h>
// #include <string.h>

int mytime = 0x5957;
int prime = 1234567;
int timeoutcount = 0;
char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void ) {
  // timeoutcount = 0;
  //   time2string( textstring, mytime );
  //   display_string( 3, textstring );
  //   display_update();
  //   tick( &mytime );
  //   delay(1000);
  if(IFS(0) & (1<<8)) 
  {
    timeoutcount++;
    IFS(0) = 0;
  }
  if(timeoutcount >= 10)
  {
    timeoutcount = 0;
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
  }
}
/* Lab-specific initialization goes here */
void labinit( void )
{

  //1/80.000.000 -> 256/80.000.000 -> 100ms = 31.250 
  T2CON = 0x8070; //256 prescaling
  PR2 = 31250;
  TMR2 = 0;
  IEC(0) |= (1<<8); //enable Interrupt 0xbf881060
  // IEC(0) = 0xFFFFffff; 
  IPC(2) |= 31;//max priority
  enable_interrupt();
  IFS(0) = 0;
  return;
}

/* This function is called repetitively from the main program */
void labwork( void ) {
  // if(IFS(0) & (1<<8)) user_isr();
  prime = nextprime( prime );
  display_string( 0, itoaconv( prime ) );
  display_update();
}
