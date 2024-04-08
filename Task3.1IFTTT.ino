#include <WiFiNINA.h>

// WiFi credentials
const char* ssid = "ddh";
const char* password = "123456789";

// IFTTT Webhooks settings
char   HOST_NAME[] = "maker.ifttt.com";
String PATH_NAME   = "/trigger/task/with/key/EU2TP8BUHSCZM54W"; // change your EVENT-NAME and YOUR-KEY
String queryString = "?value1=57&value2=25";

// Light sensor pin
const int lightSensorPin = A0;
int lightThreshold = 500; // Adjust based on your sensor and lighting conditions
bool sunlightPreviouslyDetected = false;

WiFiClient client;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Connect to WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void loop() {
  int lightValue = analogRead(lightSensorPin);

  if (lightValue > lightThreshold && !sunlightPreviouslyDetected) {
    // Sunlight started
    Serial.println("Sunlight detected. Sending start notification...");
    if (client.connect(HOST_NAME, 80)) {
      Serial.println("Start notification sent.");
    } else {
      Serial.println("Failed to send start notification.");
    }
    sunlightPreviouslyDetected = true;
  } else if (lightValue <= lightThreshold && sunlightPreviouslyDetected) {
    // Sunlight ended
    Serial.println("Sunlight no longer detected. Sending end notification...");
    if (client.connect(HOST_NAME, 80)) {
      Serial.println("End notification sent.");
    } else {
      Serial.println("Failed to send end notification.");
    }
    sunlightPreviouslyDetected = false;
  }

  delay(60000); // Check every minute
}


