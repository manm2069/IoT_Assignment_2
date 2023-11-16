//libraries to integrate functionality
#include <WiFi.h> //wifi connection
#include <PubSubClient.h> //MQTT messaging
#include <Arduino.h> //Input and output

// Potentionmeter
const int moisturePin = 34;
int moistureValue = 0;

// Wi-Fi credentials: replace with those of your network
const char* ssid = "alivio";  // The name of the WiFi network
const char* password = "alivioalivio"; // The WiFi network passkey

// MQTT broker details: replace with your own
const char* mqtt_server = "salvio-pi.local"; // The MQTT broker's hostname or IP address
const int mqtt_port = 1883;  // MQTT broker port (1883 is default)
const char* mqtt_topic = "soil/moisture";  // MQTT topic to publish messages
// MQTT client name prefix (will add MAC address)
String name = "ESP32Client_";

// Create an instance of the WiFiClient class
WiFiClient espClient;
// Create an instance of the PubSubClient class
PubSubClient client(espClient);

// Timer for publishing every 5 seconds
unsigned long previousMillis = 0;
const long interval = 5000;

void setup() {
  // Start Serial communication
  Serial.begin(115200);

  // Read the MAC address
  uint8_t mac[6];
  esp_read_mac(mac, ESP_MAC_WIFI_STA);
  // Convert MAC address to a string
  char macStr[18]; // MAC address is 12 characters long without separators, plus null terminator
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  // Concatenate the name prefix with the MAC address 
  name = name + macStr;

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Set MQTT server and port
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  // Connect to MQTT if necessary
  if (!client.connected()) {
    connect();
  }

  // Get the current time
  unsigned long currentMillis = millis();

  // Publish a message every 5 seconds
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Read potentiometer value
    moistureValue = analogRead(moisturePin)
    Serial.print("");

    // Your message to publish
    String message = moistureValue;

    // Publish the message to the MQTT topic
    client.publish(mqtt_topic, message.c_str());
    Serial.println("Sent Moisture Value: " + name);
  }

  // Allow the PubSubClient to process incoming messages
  client.loop();
}

void connect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");

    // Attempt to connect
    if (client.connect(name.c_str())) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println("Try again in 5 seconds");
      delay(5000);
    }
  }
}
