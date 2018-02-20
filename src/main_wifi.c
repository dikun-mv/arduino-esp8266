#include <ESP8266WiFi.h>

const char* WIFI_SSID = "";
const char* WIFI_PASS = "";
const char* HOST_NAME = "esp8266.local";

int LED_PIN = 2;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  Serial.println("");
  Serial.print("SETUP: connecting to wifi ");
  Serial.print(WIFI_SSID);
  Serial.print(" ");

  WiFi.hostname(HOST_NAME);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("SETUP: wifi connected");
  Serial.print("SETUP: local ip: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("SETUP: server started");
}

void loop() {
  WiFiClient client = server.available();

  if (!client) {
    return;
  }

  while (!client.available()) {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  client.flush();

  if (request.indexOf("/led_pin=on") != -1)  {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED_PIN: on");
  }

  if (request.indexOf("/led_pin=off") != -1)  {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED_PIN: off");
  }

  client.println("HTTP/1.1 204 No Content");
  delay(1);
}
