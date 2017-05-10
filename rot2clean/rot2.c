
#define UART_BAUD 9600						/* serial transmission speed */

#include <stdio.h> 
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/pgmspace.h> 
#include <avr/interrupt.h> 
#include <stdlib.h>

#include "usart.h" 
#include "lcd.h"
//#include "rotary.h"


int main(void)
{ 
  uint8_t val=0, val_tmp =0; 

  /* init UART */
  USART_init(); 
  lcd_init(LCD_DISP_ON_CURSOR); 
  
  // Put a test string on the display
	lcd_clrscr(); 							// Clear display and home cursor
	lcd_gotoxy(0,0);
	lcd_puts("Display testing2");
  

 DDRD &=~ (1 << PD6);				/* PD6 and PD7 as input */
DDRD &=~ (1 << PD7);
PORTD |= (1 << PD6)|(1 << PD7);   /* PD6 and PD7 pull-up enabled   */
 
uint8_t read_gray_code_from_encoder(void )
	{
		uint8_t val=0;

		if(!bit_is_clear(PIND, PD6))
			val |= (1<<1);

		if(!bit_is_clear(PIND, PD7))
			val |= (1<<0);

		return val;
	}


  /* ready start value */
  val = read_gray_code_from_encoder(); 
  lcd_gotoxy(0,1);				// Go to second line
  int counter=0;
  char * string;
  
   while(1)
   { 
	   val_tmp = read_gray_code_from_encoder(); 

	   if(val != val_tmp)
	   { 
		   if( /*(val==2 && val_tmp==3) ||*/
			   (val==3 && val_tmp==1) || 
			   /*(val==1 && val_tmp==0) ||*/
			   (val==0 && val_tmp==2) 
			 ) 
		   { 
				
				USART_putstring("+");
				//lcd_puts("+");
				counter++;
		   } 
		   else if( /*(val==3 && val_tmp==2) ||*/
			   (val==2 && val_tmp==0) || 
			   /*(val==0 && val_tmp==1) ||*/
			   (val==1 && val_tmp==3) 
			 ) 
		   { 
				USART_putstring("-");
				//lcd_puts("-");
				counter--;
		   } 
			lcd_puts(itoa(counter,string,10));
		   val = val_tmp; 
	   } 

	   _delay_ms(1); 
   } 

  return 0;
}
