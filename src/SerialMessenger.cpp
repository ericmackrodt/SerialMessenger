#include <Arduino.h>
#include <SerialMessenger.h>
#include <vector>

#ifdef SoftwareSerial_h
#include <SoftwareSerial.h>
#endif

SerialMessenger::SerialMessenger() {}

#ifdef SoftwareSerial_h
SerialMessenger::SerialMessenger(SoftwareSerial * serial) {
  _softSerial = serial;
}
#endif 

SerialMessenger::subscribe(String channel, void(*func)(String)) {
  int index = _channels.indexOf(channel);
  _channelFunctions[index] = func;
}

SerialMessenger::publish(String channel, String message) {
  
}
