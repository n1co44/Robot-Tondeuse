/*
 SerialCom protocol library - non-blocking.

 Devised and written by Nick Gammon - modified by Radek Vesely for Rep_Al Mower project
 Original library here: https://www.gammon.com.au/forum/?id=11428
 Date: 5 May 2022
 Version: 1.1 - for SW and HW serial

 Can send from 1 to 255 bytes from one node to another with:

 * Packet start indicator (STX)
 * Each data byte is doubled and inverted to check validity
 * Packet end indicator (ETX)
 * Packet CRC (checksum)


 To allow flexibility with hardware (eg. Serial, SoftwareSerial, I2C)
 you provide three "callback" functions which send or receive data. Examples are:


 PERMISSION TO DISTRIBUTE

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.


 LIMITATION OF LIABILITY

 The software is provided "as is", without warranty of any kind, express or implied,
 including but not limited to the warranties of merchantability, fitness for a particular
 purpose and noninfringement. In no event shall the authors or copyright holders be liable
 for any claim, damages or other liability, whether in an action of contract,
 tort or otherwise, arising from, out of or in connection with the software
 or the use or other dealings in the software.

 */


#include <SerialCom_non_blocking.h>


// allocate the requested buffer size
void SerialCom::begin ()
  {
  data_ = (byte *) malloc (bufferSize_);
  reset ();
  errorCount_ = 0;
  } // end of SerialCom::begin

// get rid of the buffer
void SerialCom::stop ()
{
  reset ();
  free (data_);
  data_ = NULL;
} // end of SerialCom::stop

// called after an error to return to "not in a packet"
void SerialCom::reset ()
  {
  haveSTX_ = false;
  available_ = false;
  inputPos_ = 0;
  startTime_ = 0;
  } // end of SerialCom::reset

// calculate 8-bit CRC
byte SerialCom::crc8 (const byte *addr, byte len)
{
  byte crc = 0;
  while (len--)
    {
    byte inbyte = *addr++;
    for (byte i = 8; i; i--)
      {
      byte mix = (crc ^ inbyte) & 0x01;
      crc >>= 1;
      if (mix)
        crc ^= 0x8C;
      inbyte >>= 1;
      }  // end of for
    }  // end of while
  return crc;
}  // end of SerialCom::crc8

// send a byte complemented, repeated
// only values sent would be (in hex):
//   0F, 1E, 2D, 3C, 4B, 5A, 69, 78, 87, 96, A5, B4, C3, D2, E1, F0
void SerialCom::sendComplemented (const byte what)
{
byte c;

  // first nibble
  c = what >> 4;
  _theSerial->write ((c << 4) | (c ^ 0x0F));

  // second nibble
  c = what & 0x0F;
  _theSerial->write ((c << 4) | (c ^ 0x0F));

}  // end of SerialCom::sendComplemented

// send a message of "length" bytes (max 255) to other end
// put STX at start, ETX at end, and add CRC
void SerialCom::sendMsg (const byte * data, const byte length)
{
  _theSerial->write (STX);  // STX
  for (byte i = 0; i < length; i++)
    sendComplemented (data [i]);
  _theSerial->write (ETX);  // ETX
  sendComplemented (crc8 (data, length));
}  // end of SerialCom::sendMsg

// called periodically from main loop to process data and
// assemble the finished packet in 'data_'

// returns true if packet received.

// You could implement a timeout by seeing if isPacketStarted() returns
// true, and if too much time has passed since getPacketStartTime() time.

bool SerialCom::update ()
  {
  // no data? can't go ahead (eg. begin() not called)
  if (data_ == NULL)
     return false;

  while (_theSerial->available () > 0)
    {
    byte inByte = _theSerial->read ();
    switch (inByte)
      {

        case STX:   // start of text
          haveSTX_ = true;
          haveETX_ = false;
          inputPos_ = 0;
          firstNibble_ = true;
          startTime_ = millis ();
          break;

        case ETX:   // end of text (now expect the CRC check)
          haveETX_ = true;
          break;

        default:
          // wait until packet officially starts
          if (!haveSTX_)
            break;

          // check byte is in valid form (4 bits followed by 4 bits complemented)
          if ((inByte >> 4) != ((inByte & 0x0F) ^ 0x0F) )
            {
            reset ();
            errorCount_++;
            break;  // bad character
            } // end if bad byte

          // convert back
          inByte >>= 4;

          // high-order nibble?
          if (firstNibble_)
            {
            currentByte_ = inByte;
            firstNibble_ = false;
            break;
            }  // end of first nibble

          // low-order nibble
          currentByte_ <<= 4;
          currentByte_ |= inByte;
          firstNibble_ = true;

          // if we have the ETX this must be the CRC
          if (haveETX_)
            {
            if (crc8 (data_, inputPos_) != currentByte_)
              {
              reset ();
              errorCount_++;
              break;  // bad crc
              } // end of bad CRC

            available_ = true;
            return true;  // show data ready
            }  // end if have ETX already

          // keep adding if not full
          if (inputPos_ < bufferSize_)
        	  data_ [inputPos_++] = currentByte_;
          else
            {
            reset (); // overflow, start again
            errorCount_++;
            }

          break;

      }  // end of switch
    }  // end of while incoming data

  return false;  // not ready yet
  } // end of SerialCom::update

