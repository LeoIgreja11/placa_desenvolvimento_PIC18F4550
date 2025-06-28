/*
 * File:   main.c
 * Author: Leonardo Igreja Bezerra
 *
 * Created on 27 de Junho de 2025, 21:52
 */


#include "config.h"

#define _XTAL_FREQ 20000000


void main(void) {
    
    char disp[16] =
    {0b11111100,   //0  //0b01111111
     0b01100000,   //1  //0b11101111
     0b11011010,   //2  //0b11101111
     0b11110010,   //3  //0b11101111
     0b01100110,   //4  //0b11011111
     0b10110110,   //5  //0b11011111
     0b10111110,   //6  //0b11011111
     0b11100000,   //7  //0b10111111
     0b11111110,   //8  //0b10111111
     0b11110110,   //9  //0b10111111
     0b11101110,   //A  //0b11101111
     0b00111110,   //b  //0b11011111
     0b10011100,   //C  //0b10111111
     0b01111010,   //d  //0b01111111
     0b10011110,   //E  //0b01111111
     0b10001110};  //F  //0b01111111
    
    
    TRISB = 0b00000000;
    TRISD = 0b00001111;
       
    while(1){
      if(!PORTDbits.RD0) //1
        {
            LATD = 0b11101111;
            LATB = disp[1];
        }
      if(!PORTDbits.RD1) //2
        {
            LATD = 0b11101111;
            LATB = disp[2];
        }
      if(!PORTDbits.RD2) //3
        {
            LATD = 0b11101111;
            LATB = disp[3];
        }
      if(!PORTDbits.RD0) //4
        {
            LATD = 0b11011111;
            LATB = disp[4];
        }
      if(!PORTDbits.RD1) //5
        {
            LATD = 0b11011111;
            LATB = disp[5];
        }
      if(!PORTDbits.RD2) //6
        {
            LATD = 0b11011111;
            LATB = disp[6];
        }
      if(!PORTDbits.RD0) //7
        {
            LATD = 0b10111111;
            LATB = disp[7];
        }
      if(!PORTDbits.RD1) //8
        {
            LATD = 0b10111111;
            LATB = disp[8];
        }
      if(!PORTDbits.RD2) //9
        {
            LATD = 0b10111111;
            LATB = disp[9];
        }
      if(!PORTDbits.RD1) //0
        {
            LATD = 0b01111111;
            LATB = disp[0];
        }
      if(!PORTDbits.RD3) //a
        {
            LATD = 0b11101111;
            LATB = disp[10];
        }
      if(!PORTDbits.RD3) //b
        {
            LATD = 0b11011111;
            LATB = disp[11];
        }
      if(!PORTDbits.RD3) //c
        {
            LATD = 0b10111111;
            LATB = disp[12];
        }
      if(!PORTDbits.RD0) //d
        {
            LATD = 0b01111111;
            LATB = disp[13];
        }
      if(!PORTDbits.RD2) //e
        {
            LATD = 0b01111111;
            LATB = disp[14];
        }
      if(!PORTDbits.RD3) //f
        {
            LATD = 0b01111111;
            LATB = disp[15];
        } 
    
    }
   
    return;
}
