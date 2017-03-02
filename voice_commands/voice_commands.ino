// Includes the BitVoicer library to the sketch
#include <BitVoicer11.h>

// Creates a new instance of the BitVoicerSerial
// class and sets up serial port to 0
BitVoicerSerial bit_voicer = BitVoicerSerial();
// Whether the Audio Streaming Calibration tool is running
boolean sampleTest = false;
// Stores data type retrieved by getData()
byte dataType = 0;
// The pin to read data from
int micPin = 0;

void setup() { 
  // Sets the analog reference to external (AREF pin)
  // WARNING!!! If anything is conected to the AREF pin,
  // this function MUST be called first. Otherwise, it will
  // damage the board.
  bit_voicer.setAnalogReference(BV_EXTERNAL);
  // Sets up the microcontroller to perform faster analog reads
  bit_voicer.setAudioInput(micPin);
  // Start serial communication
  Serial.begin(115200);
}

void loop() {
  // Sends audio to BitVoicer if the Streaming Calibration Tool
  // or the Speech Recognition Engine is running
  if (sampleTest || bit_voicer.engineRunning) {
    // The argument is the microseconds that the function has to
    // wait before reading. Achieves about 8000 readings per second
    bit_voicer.processAudio(46);
  }
}

// Runs when serial data is available in the buffer after a loop
void serialEvent() {
  // Reads the serial buffer and stores the received data type
  dataType = bit_voicer.getData();
 
  // If received data was the start/stop sampling command
  if(dataType == BV_COMMAND)
    sampleTest = bit_voicer.cmdData;
 
  // Signals Speech Recognition Engine to listen to audio streams
  if(dataType == BV_STATUS && bit_voicer.engineRunning)
    bit_voicer.startStopListening();
 
  // Checks if data type is the same as in the Voice Schema
  if(dataType == BV_STR)
    moveArm();
}

void moveArm() {
  if(bit_voicer.strData == "up") {
    // Move arm up
    digitalWrite(4, HIGH);
  }
  else if(bit_voicer.strData == "down") {
    // Move arm down
  }
  else if(bit_voicer.strData == "left") {
    // Move arm left
  }
  else if(bit_voicer.strData == "right") {
    // Move arm right
  }
  else if(bit_voicer.strData == "handshake") {
    // Make arm do a handshake
  }
  else if(bit_voicer.strData == "high five") {
    // Make arm do a high five
  }
  // Undefined command or no command at all
  else {
    bit_voicer.startStopListening();
    bit_voicer.sendToBV("COMMAND NOT DEFINED: " + bit_voicer.strData);
    bit_voicer.startStopListening();
  }
}
