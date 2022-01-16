int leftMotor = 25;
int rigtMotor = 26;
int delay_time = 800;  // Aprox 180 degrees

int trigPin = 12;
int echoPin = 14;
int CM;
long CZAS;

int micPin = 27;
int soundThresh = 3200;

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

  int count = 0;
  float sum = 450;
  while (count < 20){
    if (analogRead(micPin) > sum){
      sum=analogRead(micPin);
    }
    count++;
  }
  Serial.println(sum);

  if (sum > soundThresh) {
    Serial.println("Znalazlem!!!!!");
    digitalWrite(SOSDiode, HIGH);
    stop_it();
    stop();
  }

  if (CM > 40) {
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
