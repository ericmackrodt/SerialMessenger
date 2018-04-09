/*
  SerialMessenger.h - Easy Serial Communication for Arduino.
  Created by Eric Mackrodt 2018.
  Released into the public domain. MIT License.
*/
#ifndef SerialMessenger_h
#define SerialMessenger_h

#include "Arduino.h"
#include <SoftwareSerial.h>

#ifdef SERIALMESSENGER_EVENTS_NUMBER
#define NUMBER_EVENTS SERIALMESSENGER_EVENTS_NUMBER
#endif

#ifndef NUMBER_EVENTS
#define NUMBER_EVENTS 5
#endif

class SerialMessenger
{
  public:
    SerialMessenger();
    SerialMessenger(SoftwareSerial* serial);
    int subscribe(String channel, void (*func)(String));
    void send(String message);
    void send(String channel, String message);
    void setPrefix(char prefix);
    void setSuffix(char suffix);
    void setDelimiter(char delimiter);
    void handle();
  private:
    bool _isHardwareSerial;
    bool _isReadingMessage;
    String _channels[NUMBER_EVENTS];
    void (*_chanelFunctions[NUMBER_EVENTS])(String);
    int _channelsCount;
    char _prefix = '^';
    char _suffix = '$';
    char _delimiter = '#';
    String _buffer = "";
    String _message = "";
    SoftwareSerial* _softSerial;
    // Private Functions
    bool _serialAvailable();
    bool _received();
    String _getChannel();
    String _getParameter();
    bool _isChannel(String channel);
    int _read();
    void _print(String message);
};

#endif
