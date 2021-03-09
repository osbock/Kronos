// foam dart chronograph -- single sensor
float dartLengthMM = 70.0;
float dartLengthFt = (dartLengthMM/25.4)/12.0;
#define sensorPin 11
void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(115200);
}

bool inDart = false;
long startDartTime = 0L;
void loop() {
  int reading = digitalRead(sensorPin);
  // if the sensor is low, something is above it
  if (!reading){
    if (!inDart){ // start of the dart
      Serial.println("start");
      startDartTime = micros();
      inDart = true;
    }// otherwise still in the dart.
  } else { //not blocked
    if (inDart){ // dart just ended
      inDart = false;
      long elapsed = micros()-startDartTime;
      float fps = dartLengthFt/((float)elapsed/1000000.0);
      Serial.print("fps: ");Serial.println(fps);
    }
  }

}
