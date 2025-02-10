/*
 * D2-Lab-02.c
 *
 * Created: 2/2/2025 12:10:34 AM
 * Author : samue
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "ADC/ADC.h"
#include "LCD/LCD.h"
#include "UART/UART.h"

uint8_t contador = 0x00;



char buffer[16];


void setup(){
	initADC();
	init_LCD();
	
	initUART9600();
	
	LCD_CURSOR(0, 0);
	LCD_STR("S1   S2   S3");
}

int main(void)
{
	
	setup();

	

    /* Replace with your application code */
    while (1) 
    {
		
		
		// OBTENGO DATORS
		uint16_t pot1 = readADC(0); 
		uint16_t pot2 = readADC(1); 
		float volt1 = (pot1 / 255.0) * 5.0;
		float volt2 = (pot2 / 255.0) * 5.0;
		float volt3 = (contador / 255.0) * 5.0;

		// POSICIONAR EL CURSOR
		LCD_CURSOR(0, 1);
		// CONVERTIR A ASCII LOS DATOS DEL POTENCIOMETRO
		//itoa(pot1, buffer, 10);
		dtostrf(volt1, 4, 2, buffer);
		// CARGO VALORES
		LCD_STR(buffer);
		LCD_STR("    "); 

		// REPETIR PROCESO PERO CON EL POTENCIOMETRO 2
		LCD_CURSOR(5, 1);
		//itoa(pot2, buffer, 10);
		dtostrf(volt2, 4, 2, buffer);
		LCD_STR(buffer);
		LCD_STR("    ");
		
		// REPETIR PROCESO PERO PARA EL CONTADOR
		LCD_CURSOR(10, 1);
		itoa(contador, buffer, 10);
		//dtostrf(volt3, 4, 2, buffer);
		LCD_STR(buffer);
		LCD_STR("    ");
		if (UCSR0A & (1 << RXC0)){
			char recibe = recieveUART();
			if (recibe == '+') {
				contador ++;
			}
		else if (recibe == '-') {
			contador--;
		}
		}

		_delay_ms(100); 
		
		

    }
}






	
	
	