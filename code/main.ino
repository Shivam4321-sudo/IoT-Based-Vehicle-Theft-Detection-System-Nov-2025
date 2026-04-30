#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <TinyGPSPlus.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

/* -------- USER CONFIG -------- */
const std::string OWNER_MAC = "42:58:E0:DC:C8:C6";
const char* ALARM_PHONE_NUMBER = "8767314166";
#define LED_PIN 2

/* -------- BLE CONFIG -------- */
const unsigned long PARKING_MODE_DELAY = 5000;
const unsigned long RECONNECT_INTERVAL = 2000;

bool ownerMode = false;
bool isConnected = false;
bool parkingMode = false;

unsigned long lastDisconnectTime = 0;
unsigned long lastReconnectAttempt = 0;

BLEServer* pServer = nullptr;
BLEAdvertising* pAdvertising = nullptr;

/* -------- GPS + GSM -------- */
TinyGPSPlus gps;

#define RXD2 16  // GPS TX → ESP32 RX
#define TXD2 17  // GPS RX → ESP32 TX
#define RXD1 26  // GSM TX → ESP32 RX
#define TXD1 27  // GSM RX → ESP32 TX

const double FALLBACK_LAT = 22.25087985226172;
const double FALLBACK_LNG = 84.90129894984148;

/* -------- MPU6050 -------- */
Adafruit_MPU6050 mpu;

const float ACCEL_THRESHOLD_G = 0.05;
const float ACCEL_DELTA_G = 0.03;

float lastAccTotal = 1.0;

/* -------- FLAGS -------- */
bool theftFlag = false;

/* -------- FUNCTION DECLARATIONS -------- */
void restartAdvertising();
void sendCommand(const char* cmd);
void sendSMS(const char* number, const String &message);
void checkMPUandDecide();

/* -------- BLE CALLBACKS -------- */
class MyServerCallbacks : public BLEServerCallbacks {

  void onConnect(BLEServer* pServer) override {
    isConnected = true;
    parkingMode = false;
    digitalWrite(LED_PIN, LOW);

    Serial.println("Device connected");
    ownerMode = true;  // Simplified (MAC check can be added)
  }

  void onDisconnect(BLEServer* pServer) override {
    isConnected = false;
    lastDisconnectTime = millis();
    Serial.println("Device disconnected");
  }
};

/* -------- FUNCTIONS -------- */

void restartAdvertising() {
  if (pAdvertising) {
    pAdvertising->start();
    Serial.println("BLE advertising restarted");
  }
}

void sendCommand(const char* cmd) {
  Serial1.println(cmd);
  delay(1000);
}

void sendSMS(const char* number, const String &message) {
  Serial.println("Sending SMS...");
  sendCommand("AT");
  sendCommand("AT+CMGF=1");

  Serial1.print("AT+CMGS=\"");
  Serial1.print(number);
  Serial1.println("\"");

  delay(1000);
  Serial1.print(message);
  Serial1.write(26); // Ctrl+Z
  delay(3000);

  Serial.println("SMS sent successfully");
}

void checkMPUandDecide() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float accTotal = sqrt(
    a.acceleration.x * a.acceleration.x +
    a.acceleration.y * a.acceleration.y +
    a.acceleration.z * a.acceleration.z
  ) / 9.81;

  float delta = fabs(accTotal - lastAccTotal);

  if (parkingMode && delta > ACCEL_DELTA_G) {
    theftFlag = true;
    digitalWrite(LED_PIN, HIGH);
    Serial.println("⚠ Movement Detected: Possible Theft!");
  }

  lastAccTotal = accTotal;
}

/* -------- SETUP -------- */
void setup() {
  Serial.begin(115200);

  Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1); // GSM
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); // GPS

  pinMode(LED_PIN, OUTPUT);

  // BLE Init
  BLEDevice::init("Smart_Bike_Lock");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  // MPU6050 Init
  if (!mpu.begin()) {
    Serial.println("MPU6050 not found!");
    while (1);
  }

  Serial.println("System ready...");
}

/* -------- LOOP -------- */
void loop() {

  if (!isConnected) {
    unsigned long now = millis();

    if (now - lastDisconnectTime > PARKING_MODE_DELAY) {
      parkingMode = true;
    }
  }

  checkMPUandDecide();

  if (theftFlag) {
    String msg = "🚨 Bike Theft Detected!\n";

    if (gps.location.isValid()) {
      msg += "https://www.google.com/maps?q=";
      msg += String(gps.location.lat(), 6);
      msg += ",";
      msg += String(gps.location.lng(), 6);
    } else {
      msg += "Location unavailable";
    }

    sendSMS(ALARM_PHONE_NUMBER, msg);
    theftFlag = false;
  }

  delay(500);
}
