

//test 3
#include <WiFi.h>
#include <HTTPClient.h>

// WiFi Credentials
const char* ssid = "POCO";  
const char* password = "pritam67";

// Blockchain Server URL
const char* serverUrl = "http://192.168.4.100:8080/verify_device";

// Static IP Configuration
IPAddress local_IP(192, 168, 4, 110);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 0, 0);

// Serial Communication with Arduino
HardwareSerial mySerial(2);  

void setup() {
    Serial.begin(115200);
    mySerial.begin(9600, SERIAL_8N1, 26, 27); // RX=16, TX=17 (Connect to Arduino's TX=10, RX=11)

    // Connect to WiFi
    WiFi.config(local_IP, gateway, subnet);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
}

void loop() {
    if (mySerial.available()) {
        String deviceID = mySerial.readStringUntil('\n');
        deviceID.trim();
        
        Serial.println("📥 Received Device ID: " + deviceID);
        
        if (deviceID.length() > 0) {
            String serverResponse = checkDeviceInBlockchain(deviceID);
            Serial.println("🔗 Blockchain Response: " + serverResponse);
            
            mySerial.println(serverResponse); // Send response back to Arduino Uno
        }
    }
    delay(3000);
}

String checkDeviceInBlockchain(String deviceID) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    String requestData = "{\"device_id\": \"" + deviceID + "\"}";
    Serial.println("📡 Sending Data: " + requestData);

    int httpResponseCode = http.POST(requestData);
    String response = http.getString();
    
    http.end();

    Serial.print("Server Response Code: ");
    Serial.println(httpResponseCode);
    
    if (httpResponseCode == 200) {
        return "Authorized";  // Device is in the blockchain
    } else {
        return "Not Authorized";  // Device is not in the blockchain
    }
} 

