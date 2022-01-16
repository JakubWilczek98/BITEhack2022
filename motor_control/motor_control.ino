#ifdef ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
#else
  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#endif


// Zamienień na&nbsp;własne dane WiFi
const char* ssid = "BITEhack2022";
const char* password = "hackathon";

// Stworzenie obiektu AsyncWebServer na&nbsp;porcie 80
AsyncWebServer server(80);


// HTML code
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>

</head>
<body>
  <h2>Serwer ESP DS18B20</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i>
    <span class="ds-labels">Odleglosc</span>
    <span id="distance">%DISTANCE%</span>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("distance").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/distance", true);
  xhttp.send();
}, 10000) ;
</script>
</html>)rawliteral";


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

// Zastępuje placeholder wartościami DHT
String processor(const String& var){
  //Serial.println(var);
  if(var == "DISTANCE"){
    return String(CM);
  }
  return String();
}

void setup() {
  Serial.begin(9600);
    
  // Łączenie z&nbsp;WiFi
  WiFi.begin(ssid, password);
  Serial.println("łączenie z&nbsp;WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  // Wyświetlanie lokalnego adresu IP ESP
  Serial.println(WiFi.localIP());

  // Przekierowanie do&nbsp;strony root / web
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/distance", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send_P(200, "text/plain", String(CM).c_str());
  });

  // Start server
  server.begin();

  
  pinMode(leftMotor, OUTPUT);
  pinMode(rigtMotor, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(micPin, INPUT);
  pinMode(SOSDiode, OUTPUT);

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
