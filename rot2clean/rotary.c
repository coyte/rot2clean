/*
 * rotary.c
 *
 *  Created on: 10 Mar 2017
 *      Author: niels
 */

#include <avr/io.h>
#include <avr/pgmspace.h>


#include "rotary.h"


uint8_t read_gray_code_from_encoder(void )
	{
		uint8_t val=0;

		if(!bit_is_clear(PIND, PD6))
			val |= (1<<1);

		if(!bit_is_clear(PIND, PD7))
			val |= (1<<0);

		return val;
	}

