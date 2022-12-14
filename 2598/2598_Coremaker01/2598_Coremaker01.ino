/* I/O Pin 選擇使用 PB12 */
#define pin_led PB12
/*間隔 1000ms / 1秒*/
long interval = 10;
int ledState = LOW; // LED I/O 狀態
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  Serial3.begin(115200);
  pinMode(pin_led,OUTPUT);
}

void loop() {
  // read from port 3, send to port 0:
  if (Serial3.available()) {
    char c = Serial3.read();
    Serial.print(c);
	if (c=='1'){ 
		interval = 250;
	} else if (c=='2'){
		interval = 1000;
	}
  }
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval ){
    previousMillis = currentMillis;
    ledState == LOW ? ledState = HIGH : ledState = LOW;

     digitalWrite(pin_led,ledState);
  }
}
