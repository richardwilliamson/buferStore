/*
SoftwareSerial.cpp (formerly NewSoftSerial.cpp) - 
Multi-instance software serial library for Arduino/Wiring
-- Interrupt-driven receive and other improvements by ladyada
   (http://ladyada.net)
-- Tuning, circular buffer, derivation from class Print/Stream,
   multi-instance support, porting to 8MHz processors,
   various optimizations, PROGMEM delay tables, inverse logic and 
   direct port writing by Mikal Hart (http://www.arduiniana.org)
-- Pin change interrupt macros by Paul Stoffregen (http://www.pjrc.com)
-- 20MHz processor support by Garrett Mace (http://www.macetech.com)
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


// 
// Includes
// 
#include <Arduino.h>
#include <BufferStore.h>

//
// Statics
//
char BufferStore::_transmit_buffer[_SS_MAX_TX_BUFF];
volatile uint8_t BufferStore::_transmit_buffer_tail = 0;
//constructor


union MsgLength   //this means I can acces the bytes and the long value for a 4 didgit int (long)
{
    unsigned long value;
    byte bytes[4];
};

BufferStore::BufferStore()
{
    
}
//
// Private methods
//


//
// Destructor
//
BufferStore::~BufferStore()
{

}


//
// Public methods
//



size_t BufferStore::write(uint8_t b)
{
  if (_transmit_buffer_tail<_SS_MAX_TX_BUFF)
  {
      _transmit_buffer[_transmit_buffer_tail++ +4] = b; //add 4 to the end so that we can prepend the size on the top
      return _transmit_buffer_tail;
  }
  return 1;
}

void BufferStore::sendOut(Print &p)
{
    //add the size
    
    MsgLength tLen;
    tLen.value = _transmit_buffer_tail;
    _transmit_buffer[3] = tLen.bytes[0];
    _transmit_buffer[2] = tLen.bytes[1];
    _transmit_buffer[1] = tLen.bytes[2];
    _transmit_buffer[0] = tLen.bytes[3];

    
    p.write(_transmit_buffer, _transmit_buffer_tail+4);
    _transmit_buffer_tail = 0;
}
