/*
  SerialMessenger.h - Easy Serial Communication for Arduino.
  Created by Eric Mackrodt 2018.
  Released into the public domain. MIT License.
*/
#ifndef SerialMessenger_h
#define SerialMessenger_h

#include "Arduino.h"

#ifdef SoftwareSerial_h
#include "SoftwareSerial.h"
#endif

class SerialMessenger
{
  public:
    #ifdef SoftwareSerial_h
    SerialMessenger(String channels[], SoftwareSerial * serial);
    #endif
    SerialMessenger(String channels[]);
    void subscribe(String channel, void (*func)(String));
    void send(String channel, String message);
    void setPrefix(char prefix);
    void setSuffix(char suffix);
    void setDelimiter(char delimiter);
    void handle();
    ~SerialMessenger();
  private:
    String _channels[];
    (void (*func)(String)) _channelFunctions[];
    SoftwareSerial * _softSerial;
};

#endif
