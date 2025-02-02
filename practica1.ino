const int red_pin = 13;
const int yellow_pin = 12;
const int green_pin = 11;
const int echo_pin = 9;
const int trig_pin = 8;
const int interrupt_pin = 2;

const float speed_of_sound = 0.0343; // in cm/microseconds
volatile byte state = LOW;

float duration, distance1, distance2, currentSpeed;
unsigned long time1, time2;

void setup() {

  Serial.begin(9600, SERIAL_8N1);
  
  pinMode(red_pin, OUTPUT);
  pinMode(yellow_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(trig_pin, OUTPUT);
  pinMode(interrupt_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin), blink, FALLING);

  
}

void blink() {
  
  state = !state;
  Serial.println(state);
}
float getDistance() {
  // Envía un pulso de 10us al pin TRIG
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  
  duration = pulseIn(echo_pin, HIGH);

  float distance = (duration * speed_of_sound) / 2;
  
  return distance;
}

float getSpeed(float distance1, float distance2, unsigned long time1, unsigned long time2) {
  // Envía un pulso de 10us al pin TRIG
  float deltaTime = (time2-time1);
  Serial.println(deltaTime);
  float deltaDistance = (distance2-distance1);
  Serial.println(deltaDistance);

  float speed = (deltaDistance/deltaTime)*10;
  
  return speed;
}

void loop() {
  distance1 = getDistance();
  time1 = millis();
  delay(10);
  distance2 = getDistance();
  time2 = millis();
  currentSpeed = getSpeed(distance1, distance2, time1, time2);
  Serial.println("---------------------------------");
  Serial.print("Current Speed: ");
  Serial.print(currentSpeed);
  Serial.println(" m/s");
  delay(500);
  
}


