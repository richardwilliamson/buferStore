/*

-- ATmega1280/2560 support by Brett Hagman (http://www.roguerobotics.com/)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

The latest version of this library can always be found at
http://arduiniana.org.
*/

#ifndef BufferStore_h
#define BufferStore_h

#include <Print.h>
/******************************************************************************
* Definitions
******************************************************************************/

#define _SS_MAX_TX_BUFF 255 // TX buffer size

class BufferStore: public Print
{
private:
  // per object data


  // static data
  static char _transmit_buffer[_SS_MAX_TX_BUFF];
  static volatile uint8_t _transmit_buffer_tail;

  // private methods

  // private static method for timing

public:
  // public methods
  BufferStore();
  ~BufferStore();

   size_t write(uint8_t byte); //virtual
  
  using Print::write;
    
   void sendOut(Print &p);

};

// Arduino 0012 workaround
#undef int
#undef char
#undef long
#undef byte
#undef float
#undef abs
#undef round

#endif
