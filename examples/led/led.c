/**
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **/
 
 // pfowler@newioit.com.au 21/05/2017

// Geeetech LEDs on PA.0 and PA.1
// OEx sets I/O Direction of the 8 port pins (0=Input, 1=Output)
// IOx Output: Sets value. Input & Output: read value
// i.e.
//   OEA |= 0x01  - Set PA.0 to Output
//   IOA |= 0x01  - Set PA.0 output value to 1

// Location of IOA and OEA
//__sfr __at(0x80) IOA;
//__sfr __at(0xb2) OEA;

#include <fx2regs.h>
#include <delay.h>

// Macros to return bit value
#define _BV(bit) (1 << (bit))
// Macro to flip bits
#define xbi(sfr, bit)   ((sfr) ^= _BV(bit))


void main(void)
{
	unsigned char i;
	OEA |= 0x03;        // PA.0 & PA.1 to Outputs
	OEB |= 0b100;	// PB.2 to output
	IOA = 0x02;         // Led 1 Off, Led 2 On
	for (;;) {          // Loop forever
		PB2 ^= 1;
		xbi(IOA, 0);    // Flip PA.0
		xbi(IOA, 1);    // Flip PA.1
		delay(100);	// sleep for 100ms
		//for (i=0; i < 50; i++){}
	}
}
