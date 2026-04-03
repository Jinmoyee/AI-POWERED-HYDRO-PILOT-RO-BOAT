# 🚤 AI-POWERED HYDRO PILOT RO-BOAT

An **AI-driven autonomous robotic boat** for **real-time water quality monitoring and automated chemical treatment**.  
The system combines **IoT sensors, GPS navigation, obstacle avoidance, cloud connectivity, and machine learning** to create a smart, closed-loop water management solution.

---

## 📌 Overview

The **AI-Powered Hydro Pilot RO-Boat** is an unmanned surface vehicle designed to operate in ponds, lakes, and reservoirs.  
It continuously monitors water quality parameters and uses a **Random Forest machine learning model** to predict and dispense the correct amount of treatment chemicals automatically.

This reduces human intervention, saves chemicals, and improves environmental sustainability.

---

## 🎯 Objectives

- Autonomous navigation using GPS waypoints  
- Real-time water quality monitoring  
- AI-based chemical dosage prediction  
- Automated chemical dispensing  
- Cloud-based monitoring and logging  

---

## 🧠 Key Features

### 🚀 Autonomous Navigation
- GPS-based waypoint tracking  
- Ultrasonic sensor–based obstacle avoidance  

### 💧 Water Quality Monitoring
- pH  
- Turbidity  
- Temperature  
- Total Dissolved Solids (TDS)  

### 🤖 AI-Based Chemical Dosing
- Random Forest multi-output regression model  
- Predicts dosage for:
  - Alum  
  - Bleaching Powder  
  - Baking Soda  
  - Activated Carbon  

### 🔁 Closed-Loop System
- Re-checks water after dosing  
- Automatically adjusts chemical quantity if required  

### ☁️ Cloud Integration
- Firebase Realtime Database  
- Remote monitoring via mobile/web app  

---

## 🏗️ System Architecture

- **ESP32** – Navigation, sensor integration, obstacle avoidance  
- **ESP8266** – Chemical dosing controller  
- **Raspberry Pi 4** – Machine learning inference  
- **Firebase** – Cloud database & monitoring  
- **Peristaltic Pumps** – Precise chemical dispensing  

---

## 🧪 Machine Learning Model

- **Algorithm:** Random Forest Regressor  
- **Type:** Multi-output regression  

### 🔢 Inputs
- pH  
- Turbidity  
- Temperature  
- TDS  
- Water Volume  

### 📤 Outputs
- Alum dosage  
- Bleach dosage  
- Baking Soda dosage  
- Activated Carbon dosage  

### 📊 Performance
- R² Score ≈ 0.97  
- MAE ≈ 2.0  

---

![image alt](https://github.com/Jinmoyee/AI-POWERED-HYDRO-PILOT-RO-BOAT/blob/9bebd1d94e23209ee725dc1ca90c1d01111f0bd0/Boat_Movement.png)
![image alt](https://github.com/Jinmoyee/AI-POWERED-HYDRO-PILOT-RO-BOAT/blob/9bebd1d94e23209ee725dc1ca90c1d01111f0bd0/Boat_Movement.png)
![image alt](https://github.com/Jinmoyee/AI-POWERED-HYDRO-PILOT-RO-BOAT/blob/9bebd1d94e23209ee725dc1ca90c1d01111f0bd0/Boat_Movement.png)

---

## 🛠️ Hardware Requirements

- ESP32  
- ESP8266  
- GPS Module  
- Ultrasonic Sensors  
- pH Sensor  
- Turbidity Sensor  
- TDS Sensor  
- Temperature Sensor  
- Peristaltic Pumps  
- Servo Motors  
- L298N Motor Driver  
- Battery & Power Modules  

---

## 💻 Software & Tools

- Arduino IDE  
- Python 3.9+  
- Scikit-learn  
- Pandas, NumPy, Matplotlib  
- Firebase Realtime Database  
- Jupyter Notebook / Google Colab  

---

## 🔄 Working Flow

1. Boat navigates to GPS waypoint  
2. Sensors collect water parameters  
3. Data sent to Raspberry Pi  
4. ML model predicts chemical dosage  
5. ESP8266 activates peristaltic pumps  
6. Chemicals dispensed  
7. Water re-tested  
8. Process repeats until safe levels are reached  

---

## 🌍 Applications

- Aquaculture ponds  
- Lakes & reservoirs  
- Wastewater treatment  
- Industrial water bodies  
- Environmental monitoring  

---

## 🚀 Future Scope

- Solar-powered operation  
- LiDAR-based obstacle detection  
- Edge AI deployment  
- Multi-boat coordination  
- Government water management integration  

---

## 👥 Team Members

- **Monjinur Alom**  
- **Jinmoyee Thakuria**  
- **Ashmita Sarkar**  

**Project Guide:**  
Md. Jainul Abudin  
HOD, Department of CSE, RIST  

---

## 🎓 Academic Details

- **Degree:** B.Tech (Computer Science & Engineering)  
- **Institute:** Regional Institute of Science & Technology (RIST)  
- **University:** North Eastern Hill University (NEHU)  
- **Academic Year:** 2025  

---

## 📜 License

This project is developed for **academic and research purposes**.  
Feel free to fork and extend with proper credit.
