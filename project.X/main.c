#include "config.h"             //biblioteca config.h
#include "config_pins.h"        //biblioteca config_pins.h
#include "LCD.h"                //biblioteca LCD.h


#define _XTAL_FREQ 20000000     //define a frequencia do cristal oscilador em 20MHz


void main(void){                //main
    TRISE = 0;                  //define os pinos E como saída
    TRISD = 0;                  //define os pinos D como saída
    LATE = 0;                   //define os pinos E em nível lógico baixo
    
    LCD_Init();                 //inicializa o display
    LCD_SetCursor(1,2);
    LCD_String("Horario UTC-3");      //escreve IFPR - Paranavai
    
    char horas = 23;
    char min = 59;
    char seg = 55;
    
        
    char cursorInit=5; //define o cursor inicial
  
    while(1){
        char unihoras = horas % 10 + 48;
        char dezhoras = horas / 10 + 48;
        char unimin   = min % 10 + 48;
        char dezmin   = min / 10 + 48;
        char uniseg   = seg % 10 + 48; 
        char dezseg   = seg / 10 + 48;
                
        LCD_SetCursor(2,cursorInit);
        LCD_Char(dezhoras);
        
        LCD_SetCursor(2,cursorInit+1);
        LCD_Char(unihoras);
        
        LCD_SetCursor(2,cursorInit+2);
        LCD_String(":");
        
        LCD_SetCursor(2,cursorInit+3);
        LCD_Char(dezmin);
        
        LCD_SetCursor(2,cursorInit+4);
        LCD_Char(unimin);
        
        LCD_SetCursor(2,cursorInit+5);
        LCD_String(":");
        
        LCD_SetCursor(2,cursorInit+6);
        LCD_Char(dezseg);
        
        LCD_SetCursor(2,cursorInit+7);
        LCD_Char(uniseg);

        __delay_ms(1000);
        seg++; //incrementa o segundo
        
        if(seg == 60) {
            seg = 0;
            min++;
        }
        
        if(min == 60){
            min = 0;
            horas++;           
        }
        
        if(horas == 24){
            horas = 0;
        }
    }    
    
}                             
