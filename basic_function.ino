
int irPin = D1;
int flameSensor =A0;
int Red_led =D2;
int Green_led =D5;
int Blue_led =D6;
int buzzerPin =D0;
const int trigPin = D3;
const int echoPin = D4;
// D2 R , D5 G , D6 B , D0 Buzzer 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Setup ");
  pinMode(buzzerPin ,OUTPUT);
  pinMode(Red_led ,OUTPUT);
  pinMode(Green_led ,OUTPUT);
  pinMode(Blue_led ,OUTPUT);
  pinMode(irPin,INPUT);
  pinMode(flameSensor,INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}


void setColor(int r, int g , int b ){
  // for comon anode we subtrate the value from 255 to invert it .
  analogWrite(Red_led, 255-r );
  analogWrite(Green_led, 255-g);
  analogWrite(Blue_led,255-b);
  
}
long duration;
int distance;

void setBuzzer(char intensity) {
  switch (intensity) {
    case 'h': 
      for(int i = 0; i < 6; i++) { 
        digitalWrite(buzzerPin, HIGH);
        delay(120);
        digitalWrite(buzzerPin, LOW); 
        delay(120);
      }
      break;
      
    case 'm':
      for(int i = 0; i < 6; i++) {
        digitalWrite(buzzerPin, HIGH);
        delay(400);
        digitalWrite(buzzerPin, LOW);
        delay(400);
      }
      break;
      
    case 'l':
      for(int i = 0; i < 6; i++) {
        digitalWrite(buzzerPin, HIGH);
        delay(800);
        digitalWrite(buzzerPin, LOW);
        delay(800);
      }
      break;
      
    case 'w':
      for(int i = 0; i < 6; i++) {
        digitalWrite(buzzerPin, HIGH);
        delay(600);
        digitalWrite(buzzerPin, LOW);
        delay(600);
      }
      break;
      
    default:
      digitalWrite(buzzerPin, LOW);
      break;
  }
}


void checkFire(){
  /*
  • Below 300: The sensor is flooded with infrared light (flame is very close or huge).
  • 300 to 600: Moderate infrared detection (a steady flame at medium distance).
  • 600 to 900: Light infrared detection (a small candle flame far away, or slight ambient light interference).
  • Above 900: The sensor sees normal room conditions (safe zone).
  
  */
  int flameState = analogRead(flameSensor);
  if(flameState<300){
    Serial.println("FIRE DETECTED: HIGH Intensity");
    setColor(255,0,0);
    setBuzzer('h');

  }else if(flameState >= 300 && flameState < 600){
    Serial.println("FIRE DETECTED: MEDIUM  Intensity");
    setColor(255, 130, 0);
    setBuzzer('m');

  }else if (flameState >= 600 && flameState < 900){
    Serial.println("FIRE DETECTED: LOW Intensity");
    setColor(255, 70, 0);
    setBuzzer('w');
  }else{
    Serial.println("Safe: No fire.");
    setColor(0,255,0);
    // setBuzzer('l');
    digitalWrite(buzzerPin, LOW);
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  int irState = digitalRead(irPin);
  int flameSatate = analogRead(flameSensor);

  Serial.println("IR sensor value is : "+ String(irState));
  Serial.println("flame sensor value is : " + String(flameSatate));
    
  checkFire();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // 2. Trigger the sensor by sending a HIGH pulse for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // 3. Read the echoPin. pulseIn returns the travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // 4. Calculate the distance in centimeters
  // Formula: (Speed of sound is 0.034 cm per microsecond) / 2
  distance = duration * 0.034 / 2;
  
  // 5. Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(600);
}
