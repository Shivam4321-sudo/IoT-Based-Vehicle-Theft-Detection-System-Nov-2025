# 🚲 Vehicle Theft Detection System (IoT-Based Smart Security)

## 📌 Overview

The **Vehicle Theft Detection System** is an IoT-based smart security solution designed to prevent vehicle theft using real-time monitoring, motion sensing, and location tracking. The system integrates **ESP32**, **MPU6050 motion sensor**, **GPS**, and **GSM (SIM800L)** to detect unauthorized movement and instantly notify the owner via SMS with live location.

This project demonstrates the practical application of **Embedded Systems, IoT, Wireless Communication, and Sensor Fusion** for real-world security problems.

---

## 🎯 Key Features

* 🔐 **Theft Detection** using MPU6050 (accelerometer + gyroscope)
* 📍 **Real-Time GPS Tracking**
* 📩 **Instant SMS Alerts** via GSM module (SIM800L)
* 📶 **Bluetooth-Based Owner Authentication**
* ⚡ **Low Power & Cost-Effective Design**
* 🚨 **Dual Mode Operation** (User Mode & Theft Mode)
* 🌐 Works **without internet** (GSM-based communication)

---

## 🛠️ Tech Stack

* **Hardware:** ESP32, MPU6050, GPS Module, SIM800L GSM
* **Software:** Embedded C / Arduino IDE
* **Communication:** GSM, GPS, Bluetooth (BLE)
* **Domain:** IoT, Embedded Systems, Wireless Communication

---

## 🧩 System Architecture

* ESP32 acts as the central controller
* MPU6050 detects motion/vibration
* GPS module fetches real-time location
* GSM module sends SMS alerts
* BLE scans for owner presence

---

## 🔄 Working Principle

1. System continuously scans for the owner's Bluetooth device
2. If the owner is detected → **User Mode (Safe State)**
3. If the owner is not detected → **Theft Mode Activated**
4. MPU6050 monitors abnormal movement
5. If movement exceeds threshold:

   * Theft is detected
   * GPS coordinates are fetched
   * SMS alert with Google Maps link is sent
6. System continues monitoring in loop

---

## 📊 Results & Performance

* ✅ Accurate detection of unauthorized movement
* ✅ Minimal false alarms due to threshold filtering
* ✅ Fast GPS acquisition and SMS delivery
* ✅ Reliable operation in real-time conditions

---

## 📷 Project Structure

```
Cycle-Theft-Detection-System/
│── README.md
│── report.pdf
│── code/
│── circuit/
│── results/
```

---

## 📄 Project Report

Detailed documentation is available here:
👉 `report.pdf`

---

## 🚀 Future Enhancements

* 📱 Mobile App Integration
* ☁️ Cloud-based Monitoring (IoT Dashboard)
* 📍 Geo-fencing Alerts
* 🔋 Battery Optimization & Solar Charging

---

## 💼 Applications

* Bicycle security for students & commuters
* Asset tracking systems
* Smart vehicle anti-theft solutions
* IoT-based surveillance systems

---

## 🏆 Key Skills Demonstrated

* Embedded System Design
* IoT System Development
* Sensor Integration & Calibration
* GSM/GPS Communication
* Real-Time Data Processing
* Debugging & Hardware-Software Co-design

---

## 👨‍💻 Contributors

* Shivam Sharma
* Bhavajeet

---

## 📬 Contact

For queries or collaboration:
📧 shivamsharmakatra65@gmaqil.com
🔗 https://www.linkedin.com/in/shivam-sharma-765504226/

---

## ⭐ If you like this project

Give it a ⭐ on GitHub and share!
