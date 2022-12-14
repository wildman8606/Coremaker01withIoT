void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);

}

void loop() {
  // read from port 0, send to port 1:
  if (Serial.available()) {
    char c = Serial.read();
    Serial3.print(c);

  }
  // read from port 1, send to port 0:
  if (Serial3.available()) {
    char c = Serial3.read();
    Serial.print(c);
  }
}
