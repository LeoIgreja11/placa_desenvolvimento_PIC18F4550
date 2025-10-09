#include "LCD.h"

void enable(void){
    EN = 1;                     //Envia sinal alto para o pino conectado ao Enable
    __delay_us(1);              //Aguarda 1us (o mínimo é de 450ns, vide página 49 do datasheet do controlador)
    EN = 0;                     //Envia sinal baixo para o pino conectado ao Enable
    __delay_us(100);            //Aguarda 100us para execução
                                //(o mínimo para execução é de 37us, vide tabela 6 do datasheet do controaldor)
}

static void Nibble(uint8_t nibble){
    DB7 = (nibble & 0b00001000) >> 3;     //compara dado com o 5º bit mais significativo e desloca o valor em 3 posições
    DB6 = (nibble & 0b00000100) >> 2;     //compara dado com o 6º bit mais significativo e desloca o valor em 2 posições
    DB5 = (nibble & 0b00000010) >> 1;     //compara dado com o 7º bit mais significativo e desloca o valor em 1 posições
    DB4 = (nibble & 0b00000001) >> 0;     //compara dado com o 8º bit mais significativo (bit menos significativo)
    enable();                           //Envia o pulso de habilitação da execução da instrução pelo controlador
}

void LCD_Init(void){
    __delay_ms(50);         //Aguarda pelo menos 50ms após ligar o microcontrolador (mínimo 40ms)
    
    //Interface em 8 bits
    DB7 = 0;
    DB6 = 0;
    DB5 = 1;
    DB4 = 1;
    enable();               //Envia o pulso de habilitação da execução da instrução pelo controlador
    __delay_us(4500);       //Aguarda 4,5ms (mínimo 4,1ms)
    
    //Interface em 8 bits
    DB7 = 0;
    DB6 = 0;
    DB5 = 1;
    DB4 = 1;
    enable();               //Envia o pulso de habilitação da execução da instrução pelo controlador
    __delay_us(120);        //Aguarda 120us (mínimo 100us)
    
    //Interface em 8 bits
    DB7 = 0;
    DB6 = 0;
    DB5 = 1;
    DB4 = 1;
    enable();               //Envia o pulso de habilitação da execução da instrução pelo controlador
    
    //Interface em 4 bits (8 bits de largura: 2 x 4 bits)
    DB7 = 0;
    DB6 = 0;
    DB5 = 1;
    DB4 = 0;
    enable();               //Envia o pulso de habilitação da execução da instrução pelo controlador
    
    //Interface em 4 bits, 2 linhas (N = 1) e 5x8 (F = 0)
    DB7 = 0;
    DB6 = 0;
    DB5 = 1;
    DB4 = 0;
    enable();               //Envia o pulso de habilitação da execução da instrução pelo controlador
    
    DB7 = 1;
    DB6 = 0;
    DB5 = 0;
    DB4 = 0;
    enable();               //Envia o pulso de habilitação da execução da instrução pelo controlador
    
    //desliga display, cursor e o piscar do cursor
    DB7 = 0;
    DB6 = 0;
    DB5 = 0;
    DB4 = 0;
    enable();               //Envia o pulso de habilitação da execução da instrução pelo controlador
    
    DB7 = 1;    
    DB6 = 0;                //desliga display  
    DB5 = 0;                //desliga cursor            
    DB4 = 0;                //desliga piscar do cursor
    enable();               //Envia o pulso de habilitação da execução da instrução pelo controlador
    
    //limpa display
    DB7 = 0;
    DB6 = 0;
    DB5 = 0;
    DB4 = 0;
    enable();               //Envia o pulso de habilitação da execução da instrução pelo controlador
    
    DB7 = 0;    
    DB6 = 0;                  
    DB5 = 0;                            
    DB4 = 1;                
    enable();               //Envia o pulso de habilitação da execução da instrução pelo controlador
    
    //Configuração para que a cada comendo de escrito, o endereço seja incrementado e que o cursor se mova para a direita
    //sem movimentar o texto no display
    DB7 = 0;
    DB6 = 0;
    DB5 = 0;
    DB4 = 0;
    enable();
    
    DB7 = 0;
    DB6 = 1;
    DB5 = 1;                //endereço de escrita é incrementado (cursor se move para direita)
    DB4 = 0;                //texto não se movimenta no dsplay
    enable();
    
    
    //Ligado o display e o cursor
    //Configuração para ligar display, cursor e desligar o piscar do cursor
    DB7 = 0;
    DB6 = 0;
    DB5 = 0;
    DB4 = 0;
    enable();
    
    DB7 = 1;
    DB6 = 1;                //liga display
    DB5 = 1;                //liga cursor
    DB4 = 0;                //piscar do cursor desligado
    enable();
}

void LCD_Cmd(uint8_t comando){
    RS = 0;
    Nibble(comando >> 4);
    Nibble(comando & 0x0F);
}

void LCD_Char(char dado){
    RS = 1;
    Nibble(dado>>4);
    Nibble(dado & 0x0F);  
}

void LCD_String(const char *string){
    while(*string){
        LCD_Char(*string++);
    }
}

void LCD_SetCursor(uint8_t linha, uint8_t coluna){
    uint8_t posicao;
    
    if(linha == 1){
        posicao = 0b10000000 + (coluna - 1);
    }
    if(linha == 2){
        posicao = 0b11000000 + (coluna - 1);
    }
    LCD_Cmd(posicao);
}

void LCD_Clear(void){
    LCD_Cmd(0b00000001);
    __delay_ms(2);
}

void LCD_LefttoRight(void){
    LCD_Cmd(0b00000110);
}

void LCD_RighttoLeft(void){
    LCD_Cmd(0b00000100);
}

void LCD_Home(void){
    LCD_Cmd(0b00000010);
}

void LCD_ScrollDisplayLeft(void){
    LCD_Cmd(0b00011100);
}

void LCD_ScrollDisplayRight(void){
    LCD_Cmd(0b00011000);
}

void LCD_Blink(void){
    LCD_Cmd(config_orig | 0b00000001);
}

void LCD_noBlink(void){
    LCD_Cmd(config_orig | 0b00000000);
}

void LCD_noCursor(void){
    //LCD_Cmd(config_orig | 0b)
}

void LCD_Cursor(void){
    
}