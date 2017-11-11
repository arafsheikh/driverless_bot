# include <stdarg.h>

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

int calibration = 2;

// Wheel 2
int m2 = 255 - calibration; // Signal to Wheel 2

void debug(int num, ...) {
  va_list valist;
  va_start(valist, num);
  int i;
  for (i=0; i < num; i++) {
    Serial.println(va_arg(valist, int));
  }
  va_end(valist);
}

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
  analogWrite(E2, 248 - calibration); 

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
  
  int kp = 275/60;
  
  error = distance - 29;
  
  analogWrite(E1, kp * error); // Run in m1 Speed
  analogWrite(E2, (kp * error) - calibration); // Run in m2 speed
  if(error > 60 || error < 30)
  {
    analogWrite(E1, 255);
    analogWrite(E2, 255 - calibration);
  }
  if ((error > -3 && error < 4)) {
    analogWrite(E1, 0);
    analogWrite(E2, 0);
  }
  if(error < 0 ||  distance <= 0 )
  {
  digitalWrite(I1, LOW);
  digitalWrite(I2, HIGH);
  digitalWrite(I3, HIGH);
  digitalWrite(I4, LOW);
  analogWrite(E1, kp * error);
  analogWrite(E2, (kp * error) - calibration);
  }
  delay(100);

  debug(2, error, kp);
}
