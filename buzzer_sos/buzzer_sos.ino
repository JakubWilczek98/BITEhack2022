int buzzPin = 8;

void setup()
{
pinMode(buzzPin, OUTPUT);
  
}
void flash(int duration)
{
digitalWrite(buzzPin, HIGH);
delay(duration);
digitalWrite(buzzPin, LOW);
delay(duration);

}

void loop()
{
flash(200); flash(200); flash(200);

delay(300);

flash(500); flash(500); flash(500);

flash(200); flash(200); flash(200);

delay(1000);

}
