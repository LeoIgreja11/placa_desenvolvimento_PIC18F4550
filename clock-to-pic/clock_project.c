/*
 * File:   clock_project.c
 * Author: Leonardo Igreja Bezerra
 *
 * Created on 30 de Maio de 2025, 21:41
 */

#include "config.h"             // Inclui o arquivo de configuração dos bits de controle
                                // Este arquivo também inclui a biblioteca xc

#define _XTAL_FREQ 20000000     // Definição da frequência do cristal oscilador (20 MHz)

// Variáveis Globais
char disp[10] =
{
    0b11111100,  // 0
    0b01100000,  // 1
    0b11011010,  // 2
    0b11110010,  // 3
    0b01100110,  // 4
    0b10110110,  // 5
    0b10111110,  // 6
    0b11100000,  // 7
    0b11111110,  // 8
    0b11110110   // 9
};

// Define o horário manualmente
char hora;
char min;
char seg;

// Protótipos das funções
void define_hora(int formato);

// Função Principal
void main(void)
{
    TRISB = 0b00000000;   // Configura todos os pinos da PORTB como saída (dados para os displays)
    TRISD = 0b00000000;   // Configura todos os pinos da PORTD como saída (controle dos displays)

    LATB = 0x00;
    LATD = 0x00;

    //DEFINIR HORÁRIO MANUALMENTE
    hora = 1;
    min  = 59;
    seg  = 42;
    
    while (1)
    {
        define_hora(12); //DEFINIR O FORMATO DO RELÓGIO MANUALMENTE
    }
}

// Função de controle do relógio e dos displays
void define_hora(int formato)
{
    if(formato == 12){
    seg++;
    if (seg == 60) { seg = 0; min++; }
    if (min == 60) { min = 0; hora++; }
    if (hora == 12) { hora = 0; }

    int unihora = hora % 10;
    int dezhora = hora / 10;
    int unimin  = min  % 10;
    int dezmin  = min  / 10;
    int uniseg  = seg  % 10;
    int dezseg  = seg  / 10;

    // Proteção contra valores inválidos
    if (unihora >= 0 && unihora < 10 &&
        dezhora >= 0 && dezhora < 10 &&
        unimin  >= 0 && unimin  < 10 &&
        dezmin  >= 0 && dezmin  < 10 &&
        uniseg  >= 0 && uniseg  < 10 &&
        dezseg  >= 0 && dezseg  < 10)
    {
        for (int i = 0; i < 167; i++)  // multiplexação
        {
            LATD = 0b10000000; // Unidade de segundo
            LATB = disp[uniseg];
            __delay_ms(1);

            LATD = 0b01000000; // Dezena de segundo
            LATB = disp[dezseg];
            __delay_ms(1);

            LATD = 0b00100000; // Unidade de minuto
            LATB = disp[unimin];
            __delay_ms(1);

            LATD = 0b00010000; // Dezena de minuto
            LATB = disp[dezmin];
            __delay_ms(1);

            LATD = 0b00001000; // Unidade de hora
            LATB = disp[unihora];
            __delay_ms(1);

            LATD = 0b00000100; // Dezena de hora
            LATB = disp[dezhora];
            __delay_ms(1);
        }
    }
    else
    {
        // Apaga displays caso algum valor esteja fora da faixa
        LATD = 0x00;
        LATB = 0x00;
     }
    }
    else if(formato == 24){
    seg++;
    if (seg == 60) { seg = 0; min++; }
    if (min == 60) { min = 0; hora++; }
    if (hora == 24) { hora = 0; }

    int unihora = hora % 10;
    int dezhora = hora / 10;
    int unimin  = min  % 10;
    int dezmin  = min  / 10;
    int uniseg  = seg  % 10;
    int dezseg  = seg  / 10;

    // Proteção contra valores inválidos
    if (unihora >= 0 && unihora < 10 &&
        dezhora >= 0 && dezhora < 10 &&
        unimin  >= 0 && unimin  < 10 &&
        dezmin  >= 0 && dezmin  < 10 &&
        uniseg  >= 0 && uniseg  < 10 &&
        dezseg  >= 0 && dezseg  < 10)
    {
        for (int i = 0; i < 167; i++)  // multiplexação
        {
            LATD = 0b10000000; // Unidade de segundo
            LATB = disp[uniseg];
            __delay_ms(1);

            LATD = 0b01000000; // Dezena de segundo
            LATB = disp[dezseg];
            __delay_ms(1);

            LATD = 0b00100000; // Unidade de minuto
            LATB = disp[unimin];
            __delay_ms(1);

            LATD = 0b00010000; // Dezena de minuto
            LATB = disp[dezmin];
            __delay_ms(1);

            LATD = 0b00001000; // Unidade de hora
            LATB = disp[unihora];
            __delay_ms(1);

            LATD = 0b00000100; // Dezena de hora
            LATB = disp[dezhora];
            __delay_ms(1);
        }
    }
    else
    {
        // Apaga displays caso algum valor esteja fora da faixa
        LATD = 0x00;
        LATB = 0x00;
     }
    }
    else
    {
        // Apaga displays caso algum valor esteja fora da faixa
        LATD = 0x00;
        LATB = 0x00;
     }
}
