/*
 * Título:   Projeto 3
 * Disciplina: Sistemas Embarcados e Microcontroladores
 * 
 * IFPR - Campus Paranavaí
 * Author: Leonardo Igreja Bezerra
 *
 * 30/11/2025 - 05/12/2025
 */

// ==== Bibliotecas =====
#include "config.h"
#include "LCD.h"
#include "config_pins.h"
#include <stdio.h>

// === Frequência do Cristal Oscilador ===
#define _XTAL_FREQ 20000000

// ========== Protótipo de Funções ==========
void UART_Escreve_Texto(const char *text);
void UART_Escreve(char data);

// ===== Função main =====
void main(void) {
//==================== CONFIGURAÇÃO DO LCD ====================
    //Configurações dos pinos do LCD
    TRISD = 0b00000000;
    TRISE = 0b00000000;
    LATE  = 0b00000000;

//==================== CONFIGURAÇÃO DA COMUNICAÇÃO UART ====================
    //Configurações da Transmissão UART
    TRISCbits.TRISC6 = 1;
    TRISCbits.TRISC7 = 1;
    
    SPBRG  = 15; // ((20000000)/(19200*64))-1 = 15 - Configuração do baud rate
    SPBRGH = 0;
    
    //Configurações de transmissão serial
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 0;
    RCSTAbits.SPEN = 1;
    TXSTAbits.TXEN = 1;
 
//==================== CONFIGURAÇÃO DA VENTOINHA ====================
    //Configurações Iniciais da Ventoinha
    TRISBbits.TRISB0 = 0; //Define como saída
    LATBbits.LATB0   = 0; //Inicia com a ventoinha desligada
 
//==================== CONFIGURAÇÃO DO PWM ====================
    //Configurações do PWM
    TRISCbits.TRISC2 = 0;
    T2CON = 0b00000111;
    PR2 = 30;//PR2 = (1/10000)/(4*(1/20000000)*16))-1 = 30,25 -> 30
    CCPR1L  = 0b01110101; //Configuração inicial desse registrador
    CCP1CON = 0b00001100; //Configuração inicial desse registrador
    
//==================== CONFIGURAÇÃO DO AD ====================
    //Configurações do ADC (Configurar para utilizar o canal A0 e A3)
    ADCON0 = 0b00001101; //(bit 5-2) = Seleciona o canal
    ADCON1 = 0b00001011; //(bit 3-0) = Configura a porta AN3, AN2, AN1 e AN0 como analógicas, e as demais digitais
    ADCON2 = 0b10000111;
    
 //==================== VARIÁVEIS E INICIALIZAÇÃO DO LCD ====================  
    //Inicializa o Display LCD
    LCD_Init();
    
    //Variáveis
    int adc;
    float tensao, temperatura;
    char buffer[16], statusVent[1], bufferPorc[4], bufferTemp[4];
    float porcentagem;
    char pwmSinal;
    
 //=========================== LOOP INFINITO ===========================     
    while(1){
        // ==== Configurações do ADC para o POTENCIOMETRO ====
        ADCON0 = 0b00001101; //Seleciona o canal AN3
        __delay_us(10);
        
        ADCON0bits.GO = 1;

        while(ADCON0bits.GO);
        adc = ADRESH;
        adc = (adc << 8) + ADRESL;

        tensao = (float)adc*5/1023;
        porcentagem = tensao*100/5;
        pwmSinal = ((porcentagem) / 100) * (PR2+1) * 4; //Valor a ser utilizado nas instruções dos registradores
        
        // ========== Configurações do ADC para o LM35 ==========
        ADCON0 = 0b00000001; //Seleciona o canal AN0
        __delay_us(10);
        
        ADCON0bits.GO = 1;

        while(ADCON0bits.GO);
        adc = ADRESH;
        adc = (adc << 8) + ADRESL;
        
        temperatura = (((float)adc*5/1023)/0.01) / 2; //VERIFICAR SE SERÁ APLICADO O GANHO DE -2
                
        // ==== Configurações do PWM para o duty cicle ajustável ====
        CCPR1L  = pwmSinal >> 2; //desloca 2 bits para a direita
        CCP1CONbits.DC1B1 = (pwmSinal >> 1) & 0x01; //VERIFICAR DEPOIS
        CCP1CONbits.DC1B0 = (pwmSinal)      & 0x01; //VERIFICAR DEPOIS
       
        //Condicional para o acionamento da ventoinha e desligamento da potencia
        if(temperatura >= 35){
            LATBbits.LATB0 = 1; //Liga a ventoinha
            porcentagem = 0; // Coloca o duty cicle em 0;
            __delay_ms(10);
        }
        //Condicional para quando a temperatura retornar a menos de 32°C
        else if(temperatura < 32){
            LATBbits.LATB0 = 0; //Desliga a ventoinha
            porcentagem = tensao*100/5; // Retorna a fornecer potencia ao resistor;
            __delay_ms(10);
        }
        
        // ============ Informações para o DISPLAY LCD ============
        LCD_Clear();
        sprintf(buffer,"%0.1f", porcentagem); //transforma a porcentagem em string e envia para a variavel buffer

        // Potencia:ABC.D%
        LCD_SetCursor(1,1);
        LCD_String("Potencia: "); //"Potencia: "
        LCD_String(buffer); //"ABC.D"
        LCD_Char(0b00100101); //"%"
        
        sprintf(buffer,"%0.1f", temperatura); //transforma a porcentagem em string e envia para a variavel buffer

        // Temperat.=XY.Z°C
        LCD_SetCursor(2,1);
        LCD_String("Temperat.="); //"Temperat.= "
        LCD_String(buffer); //"XY.Z"
        LCD_Char(0b11011111); //"°"
        LCD_String("C"); //"C"
        
        UART_Escreve_Texto("Duty cicle: ");
        sprintf(bufferPorc,"%.1f", porcentagem);
        UART_Escreve_Texto(bufferPorc);
        UART_Escreve_Texto("% | Temperatura: ");
        sprintf(bufferTemp,"%.1f", temperatura);
        UART_Escreve_Texto(bufferTemp);
        //UART_Escreve(248); //colocar o símbolo °
        UART_Escreve_Texto("°C | Ventoinha: ");
        if(LATBbits.LATB0) UART_Escreve_Texto("1");
        else               UART_Escreve_Texto("0");
        UART_Escreve_Texto("\r\n");
          
        __delay_ms(100);
        
     } //end while
}//end main

void UART_Escreve_Texto(const char *text){
    while(*text){
        UART_Escreve(*text++);
    }
}

void UART_Escreve(char data){
    while(!TXSTAbits.TRMT);
    TXREG = data;
}

