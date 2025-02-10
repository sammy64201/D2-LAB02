/*
 * ADC.c
 *
 * Created: 2/2/2025 12:20:28 AM
 *  Author: samue
 */ 

#include "ADC.h"

void initADC(){
	ADMUX = 0;
	// REFERENCIA AVCC = 5V
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);
	// JUSTIFICACION A LA IZQUIERDA
	ADMUX |= (1 << ADLAR);
	// PRESCALER 128
	ADCSRA = 0;
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	// INTERRUPCION DE ADC
	ADCSRA |= (1 << ADIE);
	// HABILITAR ADC
	ADCSRA |= (1 << ADEN);
}

uint16_t readADC(uint8_t canal){
	canal &= 0x07;
	ADMUX &= 0xF8;
	
	// SELECCION DE CANAL
	switch (canal) {
		case 0:
			ADMUX |= 0b0000;
			break;
		case 1:
			ADMUX |= 0b0001; 
			break;
		case 2:
			ADMUX |= 0b0010;
			break;
		case 3:
			ADMUX |= 0b0011;
			break;
		case 4:
			ADMUX |= 0b0100;
			break;
		case 5:
			ADMUX |= 0b0101;
			break;
		case 6:
			ADMUX |= 0b0110;
			break;
		case 7:
			ADMUX |= 0b0111;
			break;
		default:
			return 0;		
	}
	// INICIAR CONVERSION
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC ));
	return ADCH;
}