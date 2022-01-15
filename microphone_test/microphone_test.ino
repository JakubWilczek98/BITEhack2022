int analogsound = A3;
int val = 0;
void setup () {
  Serial.begin(9600);
}


void loop () {
  float sum = 0;
  for ( int i=0 ; i < 2000 ; i++) {
  if (analogRead(analogsound)>sum)
  sum=analogRead(analogsound);
  }
  Serial.println(sum);
}
