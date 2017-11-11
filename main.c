# define E1 3 // Enable Pin for motor 1
# define E2 5 // Enable Pin for motor 2

# define I1 4 // Control pin 1 for motor 1
# define I2 2 // Control pin 2 for motor 1
# define I3 8 // Control pin 1 for motor 2
# define I4 7 // Control pin 2 for motor 2
# define trigPin A0
# define echoPin A1

// Wheel 1
int m1 = 255; // Signal to Wheel 1

// Wheel 2
int m2 = 255; // Signal to Wheel 2

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);

  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  pinMode(I3, OUTPUT);
  pinMode(I4, OUTPUT);

  digitalWrite(I1, HIGH);
  digitalWrite(I2, LOW);
  digitalWrite(I3, LOW);
  digitalWrite(I4, HIGH);
}

void loop(){

  digitalWrite(I1, HIGH);
  digitalWrite(I2, LOW);
  digitalWrite(I3, LOW);
  digitalWrite(I4, HIGH);
  analogWrite(E1, 248); 
  analogWrite(E2, 248); 

  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  if (distance >= 200 || distance <= 0) {
    Serial.println("Out of range");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(100);
}
