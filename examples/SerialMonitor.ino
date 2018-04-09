#import <SerialMessenger.h>

SerialMessenger messenger;

void setup() {
  Serial.begin(115200);
  Serial.println("Started!");
  messenger.subscribe("Channel1", &channel1);
}

void loop() {
  messenger.handle();
}

void channel1(String message) {
  messenger.send("Received", message);
}