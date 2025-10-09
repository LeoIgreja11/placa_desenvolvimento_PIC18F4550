#include "config.h"             //biblioteca config.h
#include "config_pins.h"        //biblioteca config_pins.h
#include "LCD.h"                //biblioteca LCD.h


#define _XTAL_FREQ 20000000     //define a frequencia do cristal oscilador em 20MHz

char horas = 13;
char min = 59;
char seg = 55;
char cursorInit=5; //define o cursor inicial
static int formato = 24;


void __interrupt() HighPriorityISR(void){
    INTCONbits.INT0IF = 0;
    if(formato == 12){
        // Se estava em 12h e vai mudar para 24h, converte para 24h
        if(horas == 12) horas = 0;         // 12 AM -> 00h
        else if(horas < 12);               // AM -> mantém
        else horas += 12;                  // PM -> soma 12
    }
    formato = 24;
}

void __interrupt(low_priority) LowPriorityISR(void){
    INTCON3bits.INT1IF = 0;
    if(formato == 24){
        // Se estava em 24h e vai mudar para 12h, converte para 12h
        if(horas == 0) horas = 12;         // 00h -> 12 AM
        else if(horas > 12) horas -= 12;   // 13~23 -> subtrai 12
        // else mantém (1~12 AM)
    }
    formato = 12;
}


void main(void){                //main
    TRISE = 0;                  //define os pinos E como saída
    TRISD = 0;                  //define os pinos D como saída
    TRISB = 0x00000011;
    LATE = 0;                   //define os pinos E em nível lógico baixo
    
    INTCON2bits.RBPU = 0;
    
    RCONbits.IPEN = 1;
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    
    INTCONbits.INT0F = 0;
    INTCONbits.INT0IE = 1;
    INTCON2bits.INTEDG0 = 0;
    
    
    INTCON3bits.INT1IF = 0;
    INTCON3bits.INT1IE = 1;
    INTCON2bits.INTEDG1 = 0;
    
    INTCON3bits.INT1IF = 0;
    
    LCD_Init();                 //inicializa o display
    LCD_SetCursor(1,2);
    LCD_String("Horario UTC-3");      
    
    
  
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

             if(horas == formato){
                 horas = 0;
             }
             
             if(formato == 12){
                 LCD_SetCursor(2,15);
                LCD_String(".");
             }
        }
}
