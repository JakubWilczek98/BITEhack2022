int leftMotor = 25;
int rigtMotor = 26;
int delay_time = 800;  // Aprox 180 degrees

int trigPin = 12;
int echoPin = 14;
int CM;
long CZAS;

int micPin = 27;
int soundThresh = 2100;

int SOSDiode = 13;

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

void stop()
{
  while(1);
}

void flash(int duration, int Pin)
{
  digitalWrite(Pin, HIGH);
  delay(duration);
  digitalWrite(Pin, LOW);
  delay(duration);
}

void sosSignal(int Pin) {
  flash(200, Pin); flash(200, Pin); flash(200, Pin);

  delay(300);
  
  flash(500, Pin); flash(500, Pin); flash(500, Pin);
  
  flash(200, Pin); flash(200, Pin); flash(200, Pin);
  
  delay(1000);
}

void setup() {
  pinMode(leftMotor, OUTPUT);
  pinMode(rigtMotor, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(micPin, INPUT);
  pinMode(SOSDiode, OUTPUT);

  Serial.begin(9600);

  delay(delay_time * 2);
}

void loop() {
  pomiar_odleglosci();

  Serial.println(CM);

  int micVal = digitalRead(micPin);

  if (micVal == HIGH) {
    Serial.println("Znalazlem!!!!!");
    // digitalWrite(SOSDiode, HIGH);
    sosSignal(SOSDiode);
    stop_it();
    stop();
  }

  if (CM > 35) {
    go_straight();
    delay(200);
    stop_it();
  }
  else{
    delay(delay_time * 2);
    turn_right();
    delay(delay_time);
    stop_it();
    delay(delay_time * 2);
  };
}
