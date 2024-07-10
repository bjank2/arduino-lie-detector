// Team 4
// Erica Ly, 652818474 and Ely4, Bianca Jankiewicz 675305960, bjanki2
// Lie Detector
// Our project is a lie detector that will buzz with the buzzer and turn on a red led if the user is lying. 
// If the user is telling the truth a green led will come on and the red one will turn off. No buzzer tone is activated.
// The lie will be detected using a galvanic skin sensor (GSR) and a heart rate/pulse sensor. By using these two different
// devices we are able to more accurately detect if the user is lying or not. Both input values will need to be elevated in order
// for a lie to be detected. 

#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
// input board
// red goes to rx black goes to tx

int hrThreshold = 550;
int gsrThreshold = 0;
int gsrVal;
int gsrCheck;
const int hr = A0;
const int gsr = A1;
String hrTemp = "";
String gsrTemp = "";
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object from PulseSensor library


void setup() {
  Serial.begin(9600);
  long sum = 0;

  // initialize pulse sensor library variables
  pulseSensor.analogInput(hr);
  pulseSensor.setThreshold(hrThreshold);
  if (pulseSensor.begin()) {
    // Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.
  }


  // get a baseline reading for the gsr sensor + find average
  for (int i = 0; i < 500; i++) {
    gsrVal = analogRead(gsr);
    sum += gsrVal;
    delay(5);
  }

  Serial.println("Completed baseline readings");
  gsrThreshold = sum / 500;
}

void loop() {
  // check pulse sensor initiation and grab value
  if (pulseSensor.sawStartOfBeat()) {
    int bpm = pulseSensor.getBeatsPerMinute();
    Serial.print("BPM: ");
    Serial.println(bpm);

    // read gsr and check that its under the threshold by reading it a second time
    gsrVal = analogRead(gsr);
    gsrCheck = gsrThreshold - gsrVal;
    Serial.print("GSR Threshold: ");
    Serial.println(gsrCheck);
              
    if (abs(gsrCheck) > 50) {
      gsrVal = analogRead(gsr);
      gsrCheck = gsrThreshold - gsrVal;
      Serial.print("GSR Threshold: ");
      Serial.println(gsrCheck);

      // the user is lying, check that the bpm is above 80 as an elevated heart rate and that the threshold is above 50 
      if (abs(gsrCheck > 50) && bpm > 80) {
        Serial.write(1);
      } else {
        Serial.write(0);
      }
    }
  }
  delay(20);
}
