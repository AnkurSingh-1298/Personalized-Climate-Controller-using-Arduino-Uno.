#include <IRremote.hpp>

#define IR_RECEIVE_PIN 2
String receivedValue = "";
unsigned long lastReceiveTime = 0;
const unsigned long debounceDelay = 500; // Adjust debounce delay as needed

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, RC5); // Start the receiver with RC5 protocol
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long currentTime = millis();
    if (currentTime - lastReceiveTime > debounceDelay) {
      // Print the received raw data
      Serial.print("Raw Data: ");
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

      receivedValue = String(IrReceiver.decodedIRData.decodedRawData, HEX); // Convert raw data to string

      // Print the received value
      Serial.print("Received Value: ");
      Serial.println(receivedValue);

      // Print the decoded IR result in one line
      IrReceiver.printIRResultShort(&Serial);

      // Print the statement required to send this data
      IrReceiver.printIRSendUsage(&Serial);

      lastReceiveTime = currentTime; // Update last receive time
    }
    // Enable receiving of the next value
    IrReceiver.resume();
  }
}
