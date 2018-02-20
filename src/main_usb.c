int LED_PIN = 2;

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    delay(1);
  }

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  Serial.println("");
  Serial.println("SETUP: done");
}

void loop() {
  String input = "";

  while (Serial.available()) {
    char byte = (char) Serial.read();
    input += byte;
  }

  if (input.indexOf("led_pin=on") != -1) {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED_PIN: on");
  }

  if (input.indexOf("led_pin=off") != -1) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED_PIN: off");
  }
}
