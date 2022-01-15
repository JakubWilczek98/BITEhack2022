int leftMotor = 25;
int rigtMotor = 26;
int delay_time = 800;  // Aprox 180 degrees

int trigPin = 12;
int echoPin = 14;
int CM;
long CZAS;

void go_straight() {
  digitalWrite(leftMotor, HIGH);
  digitalWrite(rigtMotor, HIGH);
}

void stop_it() {
  digitalWrite(leftMotor, LOW);
  digitalWrite(rigtMotor, LOW);  
}

void turn_left() {
  digitalWrite(leftMotor, HIGH);
  digitalWrite(rigtMotor, LOW);
}

void turn_right() {
  digitalWrite(leftMotor, LOW);
  digitalWrite(rigtMotor, HIGH);
}

void pomiar_odleglosci ()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  digitalWrite(echoPin, HIGH); 
  CZAS = pulseIn(echoPin, HIGH);
  CM = CZAS / 58;
}

void setup() {
  pinMode(leftMotor, OUTPUT);
  pinMode(rigtMotor, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(115200);

  delay(delay_time * 2);
}

void loop() {

  pomiar_odleglosci();

  if (CM > 40) {
    go_straight();
    delay(200);
    Serial.println("Going straight");
    stop_it();
  }
  else{
    Serial.println("Stopping");
    delay(delay_time * 2);
    Serial.println("Turning");
    turn_right();
    delay(delay_time);
    stop_it();
    delay(delay_time * 2);
  };
  
  pomiar_odleglosci();  
  Serial.print("Zmierzona odleglosc: ");
  Serial.print(CM);
  Serial.println(" cm");
  
}
