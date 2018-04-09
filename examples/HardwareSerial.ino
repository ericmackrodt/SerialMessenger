#import <SerialMessenger.h>

String channels[] = {
  "Channel1",
  "Channel2"
};

SerialMessenger messenger(channels);

void setup() {
  messenger.subscribe("Channel1", &channel1);
  messenger.subscribe("Channel2", &channel1);
}

void loop() {
  messenger.handle();
}

void channel1(String message) {
  Serial.println(message);
}
