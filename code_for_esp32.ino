#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Pin for the lamp
const int lampPin = 2;

WebServer server(80);

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Lamp Control</h1>";
  html += "<button onclick=\"window.location.href='/lamp_on'\">Turn On</button>";
  html += "<button onclick=\"window.location.href='/lamp_off'\">Turn Off</button>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleLampOn() {
  String html = "<html><body>";
  html += "<h1>Lamp Control</h1>";
  html += "<button onclick=\"window.location.href='/lamp_on'\">Turn On</button>";
  html += "<button onclick=\"window.location.href='/lamp_off'\">Turn Off</button>";
  html += "</body></html>";
  server.send(200, "text/html", html);
  digitalWrite(lampPin, HIGH);
  server.send(200, "text/plain", html);
}

void handleLampOff() {
  String html = "<html><body>";
  html += "<h1>Lamp Control</h1>";
  html += "<button onclick=\"window.location.href='/lamp_on'\">Turn On</button>";
  html += "<button onclick=\"window.location.href='/lamp_off'\">Turn Off</button>";
  html += "</body></html>";
  server.send(200, "text/html", html);
  digitalWrite(lampPin, LOW);
  server.send(200, "text/plain", html);
}

void setup() {
  pinMode(lampPin, OUTPUT);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Handle root URL
  server.on("/", handleRoot);

  // Handle lamp control URLs
  server.on("/lamp_on", handleLampOn);
  server.on("/lamp_off", handleLampOff);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
