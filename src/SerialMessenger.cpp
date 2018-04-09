#include <Arduino.h>
#include <SerialMessenger.h>
#include <SoftwareSerial.h>

SerialMessenger::SerialMessenger() {
  _isHardwareSerial = true;
}

SerialMessenger::SerialMessenger(SoftwareSerial* serial) {
  _softSerial = serial;
  _isHardwareSerial = false;
} 

int SerialMessenger::subscribe(String channel, void (*func)(String)) {
  _channels[_channelsCount] = channel;
  _chanelFunctions[_channelsCount] = func;
  _channelsCount++;
  return _channelsCount - 1;
}

void SerialMessenger::setPrefix(char prefix) {
  _prefix = prefix;
}

void SerialMessenger::setSuffix(char suffix) {
  _suffix = suffix;
}

void SerialMessenger::setDelimiter(char delimiter) {
  _delimiter = delimiter;
}

void SerialMessenger::send(String channel) {
  _print(_prefix + channel + _suffix);
}

void SerialMessenger::send(String channel, String message) {
  _print(_prefix + channel + _delimiter + message + _suffix);
}

void SerialMessenger::handle() {
  if (_received()) {
    for (int i = 0; i < _channelsCount; i++) {
      if (_isChannel(_channels[i])) {
        _chanelFunctions[i](_getParameter());
      }
    }
  }
}

// Private Functions

bool SerialMessenger::_serialAvailable() {
  if (_isHardwareSerial == true) {
    return Serial.available();
  } else {
    return _softSerial->available();
  }
}

int SerialMessenger::_read() {
  if (_isHardwareSerial == true) {
    return Serial.read();
  } else {
    return _softSerial->read();
  }
}

void SerialMessenger::_print(String message) {
  if (_isHardwareSerial == true) {
    Serial.print(message);
  } else {
    _softSerial->print(message);
  }
}

bool SerialMessenger::_received() {
  if(_serialAvailable()) {
      char read = char(_read());

      if (read == _prefix) {
        _isReadingMessage = true;
        return false;
      } else if(read == _suffix) {
        _message  = _buffer;
        _buffer = "";
        _isReadingMessage = false;
        return true;
      } else if (_isReadingMessage == true) {
        _buffer += read;
        return false;
      } else {
        return false;
      }
    } else {
      return false;
    }
}

String SerialMessenger::_getChannel() {
  int delimiter = _message.indexOf(_delimiter);

  if (delimiter > -1) {
    return _message.substring(0, delimiter);
  } else {
    return _message;
  }
}

String SerialMessenger::_getParameter() {
  int delimiter = _message.indexOf(_delimiter);
  int end = _message.length();

  if (delimiter > -1 && end > delimiter) {
    return _message.substring(delimiter + 1, end);
  } else {
    return "";
  }
}

bool SerialMessenger::_isChannel(String channel) {
  return _getChannel() == channel;
}
