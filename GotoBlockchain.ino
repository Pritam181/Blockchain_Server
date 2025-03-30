// #include <WiFi.h>
// #include <HTTPClient.h>

// const char* ssid = "POCO";  // Replace with your WiFi credentials
// const char* password = "pritam67";
// const char* serverUrl = "http://192.168.4.100:8080/verify_device";

// String deviceID;
// WiFiClient client;
// HardwareSerial mySerial(2);  // Use Serial2 for communication with Arduino

// void setup() {
//     Serial.begin(115200);
//     mySerial.begin(9600, SERIAL_8N1, 26, 27); 
    
//     WiFi.begin(ssid, password);
//     Serial.print("Connecting to WiFi...");
    
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         Serial.print(".");
//     }
    
//     Serial.println("\nConnected to WiFi");
// }

// void loop() {
//     if (mySerial.available()) {
//         deviceID = mySerial.readStringUntil('\n');
//         deviceID.trim();
        
//         Serial.println("Received Device ID: " + deviceID);
        
//         if (deviceID.length() > 0) {
//             String serverResponse = checkDeviceInBlockchain(deviceID);
//             Serial.println("Blockchain Response: " + serverResponse);
            
//             mySerial.println(serverResponse); // Send response back to Arduino
//         }
//     }
//     delay(3000);
// }

// String checkDeviceInBlockchain(String deviceID) {
//     HTTPClient http;
//     http.begin(serverUrl);
//     http.addHeader("Content-Type", "application/json");

//     String requestData = "{\"device_id\": \"" + deviceID + "\"}";
//     int httpResponseCode = http.POST(requestData);
//     String response = http.getString();
    
//     http.end();

//     if (httpResponseCode == 200) {
//         return "Authorized";
//     } else {
//         return "Not Authorized";
//     }
// }



//test 1
// #include <WiFi.h>
// #include <HTTPClient.h>

// const char* ssid = "POCO";  // Replace with your WiFi SSID
// const char* password = "pritam67";  // Replace with your WiFi password
// const char* serverUrl = "http://192.168.4.100:8080/verify_device";  // Replace with your blockchain server URL

// String deviceID = "ESP32-001";  // Sample device ID
// WiFiClient client;

// IPAddress local_IP(192, 168, 4, 110);
// IPAddress gateway(192, 168, 4, 1);
// IPAddress subnet(255, 255, 0, 0);
// void setup() {
//     Serial.begin(115200);
//       WiFi.config(local_IP, gateway, subnet);
//     // Connect to WiFi
//     WiFi.begin(ssid, password);
//     Serial.print("Connecting to WiFi...");
    
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         Serial.print(".");
//     }
    
//     Serial.println("\nConnected to WiFi!");
    
//     // Send data to the server
//     sendDeviceIDToServer();
// }

// void loop() {
//     // Send data every 5 seconds
//     sendDeviceIDToServer();
//     delay(5000);
// }

// void sendDeviceIDToServer() {
//     if (WiFi.status() == WL_CONNECTED) {
//         HTTPClient http;
//         http.begin(serverUrl);  // Set the server URL
//         http.addHeader("Content-Type", "application/json");  // Set header

//         // Create JSON payload
//         String requestData = "{\"device_id\": \"" + deviceID + "\"}";

//         Serial.println("Sending Data: " + requestData);  // Debugging

//         int httpResponseCode = http.POST(requestData);  // Send POST request
//         String response = http.getString();  // Get server response

//         Serial.print("Server Response Code: ");
//         Serial.println(httpResponseCode);
//         Serial.print("Response: ");
//         Serial.println(response);

//         http.end();  // Close connection
//     } else {
//         Serial.println("WiFi not connected!");
//     }
// }


//test2
// #include <WiFi.h>
// #include <HTTPClient.h>

// // WiFi credentials
// const char* ssid = "POCO";
// const char* password = "pritam67";

// // Blockchain Server Address
// const char* serverAddress = "http://192.168.4.100:8080/verify_device"; // Change this to your blockchain server URL

// // Static IP Configuration
// IPAddress local_IP(192, 168, 4, 110);
// IPAddress gateway(192, 168, 4, 1);
// IPAddress subnet(255, 255, 0, 0);

// // LED Pin
// const int ledPin = 2;

// // Global variables
// bool wifiConnected = false;

// // Function to ensure stable WiFi connection
// void connectToWiFi() {
//     WiFi.config(local_IP, gateway, subnet);
//     WiFi.begin(ssid, password);
    
//     Serial.print("Connecting to WiFi");
//     for (int i = 0; i < 15; i++) { // Try for 15 seconds
//         if (WiFi.status() == WL_CONNECTED) {
//             wifiConnected = true;
//             Serial.println("\n✅ WiFi Connected!");
//             Serial.print("📡 ESP32 Static IP: ");
//             Serial.println(WiFi.localIP());
//             return;
//         }
//         Serial.print(".");
//         delay(1000);
//     }
    
//     Serial.println("\n⚠️ WiFi Connection Failed! Retrying...");
//     wifiConnected = false;
// }

// // Function to send device ID to Blockchain Server
// void sendToBlockchain(const String& deviceID) {
//     if (!wifiConnected) {
//         Serial.println("⚠️ WiFi Not Connected. Skipping request...");
//         return;
//     }

//     HTTPClient http;
//     http.begin(serverAddress);
//     http.addHeader("Content-Type", "application/json");

//     String jsonPayload = "{\"device_id\": \"" + deviceID + "\"}";
//     Serial.println("📡 Sending Data to Blockchain: " + jsonPayload);

//     int httpResponseCode = http.POST(jsonPayload);
//     String response = http.getString();

//     Serial.print("🔄 Server Response Code: ");
//     Serial.println(httpResponseCode);
//     Serial.print("📩 Response: ");
//     Serial.println(response);

//     // If the device is unauthorized, blink LED
//     if (response.indexOf("\"status\": \"unauthorized\"") >= 0) {
//         Serial.println("🚨 Unauthorized Device Detected! Blinking LED...");
//         for (int i = 0; i < 5; i++) {
//             digitalWrite(ledPin, HIGH);
//             delay(200);
//             digitalWrite(ledPin, LOW);
//             delay(200);
//         }
//     } else {
//         Serial.println("✅ Device Authorized. Keeping LED ON...");
//         digitalWrite(ledPin, HIGH); // Keep LED ON
//     }

//     http.end();
// }

// void setup() {
//     Serial.begin(115200);
//     pinMode(ledPin, OUTPUT);
//     digitalWrite(ledPin, LOW); // Start with LED OFF

//     connectToWiFi();
    
//     // Example: Sending a test device ID
//     sendToBlockchain("ESP32-001");
// }

// void loop() {
//     // Your logic for reading device ID from serial or other source can go here
//     delay(5000); // Wait before sending another request
// }

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

//test 4
// #include <WiFi.h>
// #include <HTTPClient.h>

// const char* ssid = "POCO";  
// const char* password = "pritam67";
// const char* serverUrl = "http://192.168.4.100:8080/verify_device";

// String deviceID;
// WiFiClient client;
// HardwareSerial mySerial(2);  // Using Serial2 on ESP32 (RX=16, TX=17)

// void setup() {
//     Serial.begin(115200);
//     mySerial.begin(9600, SERIAL_8N1, 26, 27); // RX=26, TX=27

//     WiFi.begin(ssid, password);
//     Serial.print("Connecting to WiFi...");
    
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         Serial.print(".");
//     }
    
//     Serial.println("\n✅ Connected to WiFi");
// }

// void loop() {
//     if (mySerial.available()) {
//         deviceID = mySerial.readStringUntil('\n');
//         deviceID.trim();
        
//         Serial.println("Received Device ID: " + deviceID);
        
//         if (deviceID.length() > 0) {
//             String serverResponse = checkDeviceInBlockchain(deviceID);
//             Serial.println("Blockchain Response: " + serverResponse);
            
//             mySerial.println(serverResponse); // Send response back to Arduino Uno
//         }
//     }
//     delay(3000);
// }

// String checkDeviceInBlockchain(String deviceID) {
//     HTTPClient http;
//     http.begin(serverUrl);
//     http.addHeader("Content-Type", "application/json");

//     String requestData = "{\"device_id\": \"" + deviceID + "\"}";
//     Serial.println("Sending Data: " + requestData);
    
//     int httpResponseCode = http.POST(requestData);
//     String response = http.getString();
    
//     http.end();

//     if (httpResponseCode == 200) {
//         return "Authorized";
//     } else {
//         return "Not Authorized";
//     }
// }


