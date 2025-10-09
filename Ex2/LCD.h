#ifndef LCD_H
#define LCD_H

#include <xc.h>
#include <stdint.h>
#include "config_pins.h"

#define config_orig 0b00001110

#ifndef _XTAL_FREQ
    #define _XTAL_FREQ 20000000     //definição da frequência do cristal oscilador
#endif

#ifndef RS
   #define RS LATEbits.LATE0       //define o pino em que RS está conectado
#endif

#ifndef EN
    #define EN LATEbits.LATE1       //define o pino em que EN está conectado
#endif

#ifndef DB4
    #define DB4 LATDbits.LATD4      //define o pido em que D4 está conectado
#endif

#ifndef DB5
    #define DB5 LATDbits.LATD5      //define o pino em que D5 está conectado
#endif

#ifndef DB6
    #define DB6 LATDbits.LATD6      //define o pino em que D5 está conectado
#endif

#ifndef DB7
    #define DB7 LATDbits.LATD7      //define o pino em que D5 está conectado
#endif


// Funções públicas
void enable(void);
void LCD_Init(void);
void LCD_Cmd(uint8_t cmd);
void LCD_Char(char data);
void LCD_String(const char *str);
void LCD_SetCursor(uint8_t row, uint8_t column);
void LCD_Clear(void);
void LCD_LefttoRight(void);
void LCD_RighttoLeft(void);
void LCD_Home(void);
void LCD_ScrollDisplayLeft(void);
void LCD_ScrollDisplayRight(void);
void LCD_Blink(void);
void LCD_noBlink(void);
void LCD_noCursor(void); //
void LCD_Cursor(void); //
void LCD_noDisplay(void); //
void LCD_Display(void); //
void LCD_AutoScroll(void);//
void LCD_noAutoScroll(void);//



#endif