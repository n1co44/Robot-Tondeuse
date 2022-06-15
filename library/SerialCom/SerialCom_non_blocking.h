/*
 SerialCom protocol library - non-blocking.

 Devised and written by Nick Gammon - modified by Radek Vesely for Rep_Al Mower project
 Original library here: https://www.gammon.com.au/forum/?id=11428
 Date: 5 May 2022
 Version: 1.1 - for SW and HW serial

 Licence: Released for public use.

*/


#ifndef SerialCom_non_blocking_h
#define SerialCom_non_blocking_h

#include "Arduino.h"


class SerialCom
  {
  enum {
        STX = '\2',   // start of text
        ETX = '\3'    // end of text
  };  // end of enum

  // where we save incoming stuff
  byte * data_;

  // how much data is in the buffer
  const int bufferSize_;

  // this is true once we have valid data in buf
  bool available_;

  // an STX (start of text) signals a packet start
  bool haveSTX_;

  // count of errors
  unsigned long errorCount_;

  // variables below are set when we get an STX
  bool haveETX_;
  byte inputPos_;
  byte currentByte_;
  bool firstNibble_;
  unsigned long startTime_;

  // helper private functions
  byte crc8 (const byte *addr, byte len);
  void sendComplemented (const byte what);

  Stream *_theSerial; // Somewhere to store the object's pointer

  public:

    // constructor

    // How to write a library that support both HW and SW Serial communication
    // https://www.youtube.com/watch?v=-smhZUVd_0o
    SerialCom(Stream *serial, const byte bufferSize) : _theSerial(serial),  bufferSize_(bufferSize) {}
    SerialCom(Stream &serial, const byte bufferSize) : _theSerial(&serial), bufferSize_(bufferSize) {}

    // destructor - frees memory used
    ~SerialCom () { stop (); }

    // allocate memory for buf_
    void begin ();

    // free memory in buf_
    void stop ();

    // handle incoming data, return true if packet ready
    bool update ();

    // reset to no incoming data (eg. after a timeout)
    void reset ();

    // send data
    void sendMsg (const byte * data, const byte length);

    // returns true if packet available
    bool available () const { return available_; };

    // once available, returns the address of the current message
    byte * getData ()   const { return data_; }
    byte   getLength () const { return inputPos_; }

    // return how many errors we have had
    unsigned long getErrorCount () const { return errorCount_; }

    // return when last packet started
    unsigned long getPacketStartTime () const { return startTime_; }

    // return true if a packet has started to be received
    bool isPacketStarted () const { return haveSTX_; }

  }; // end of class SerialCom

#endif /* SerialCom_non_blocking_h */
