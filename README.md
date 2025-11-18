# 🌍 IoT-Based Real-Time Environmental Monitoring System

## 📌 Project Overview

This project collects real-time **temperature, humidity, air quality, and pressure** data using ESP32 and multiple sensors, then sends it to a **Django backend**, where the data is stored, processed, and visualized through a **web-based dashboard**.

It is designed as a scalable IoT monitoring solution suitable for **smart homes, agriculture, and research-based environmental studies**.

---

## 🛠️ System Architecture

```
ESP32  →  Django REST API  →  Database  →  Web Dashboard (Charts)
```

---

## 🔧 Hardware Used

| Component | Purpose                       |
| --------- | ----------------------------- |
| ESP32     | Wi-Fi enabled microcontroller |
| DHT11     | Temperature & Humidity Sensor |
| BMP280    | Atmospheric Pressure Sensor   |
| MQ Sensor | Air Quality / Gas Sensor      |

---

## 🧠 Software Used

* Python 3
* Django & Django REST Framework
* Chart.js (frontend visualization)
* Arduino IDE (ESP32 programming)
* SQLite database (default)
* Virtual Environment (`venv`)

---

## 📂 Project Structure

```
📦 Project Root
 ┣━ env_monitor/          # Django main project
 ┣━ sensors/              # Django app
 ┣━ templates/sensors/    # Dashboard HTML
 ┣━ esp32/                # ESP32 firmware
 ┣━ requirements.txt
 ┣━ manage.py
```

---

## 🚀 How It Works

1️⃣ ESP32 reads all sensor values every 5 seconds
2️⃣ Converts readings into a JSON payload
3️⃣ Sends POST request to Django API endpoint `/api/data/`
4️⃣ Django validates & stores data in database
5️⃣ Dashboard fetches latest values and generates real‑time charts

---

## 📡 API Endpoint

```
POST http://your-ip:8000/api/data/
```

Example payload:

```json
{
  "temperature": 26.5,
  "humidity": 52.7,
  "air_quality": 580,
  "pressure": 1007.2
}
```

---

## 🖥️ Dashboard Preview

✔ Real‑time charts
✔ Null‑value safe
✔ Displays latest 20 readings

*(Screenshots will be added later)*

---

## 📁 ESP32 Firmware

Located inside:

```
esp32/esp32_env_monitor.ino
```

This code sends sensor readings as JSON to Django API.

---

## 📊 Results

* Successfully collects live environmental data
* Data visible in interactive web dashboard
* Works even if a sensor reading is missing

*(Graphs/screenshots will be added later)*

---

## 🌱 Future Improvements

🔹 Add rainfall monitoring (useful for drought regions like Lalpur)
🔹 Add radiation sensor (for research near Rooppur Nuclear Plant)
🔹 Deploy backend on cloud (AWS / Railway / PythonAnywhere)
🔹 Store data in TimescaleDB for long‑term analysis
🔹 Build mobile app to monitor live readings

---

## 🏷️ Developed By

**Mahfuz Hossain**
Department of ICE, BAUET
📅 November 2025

---

## ⭐ Contribution

Pull requests are welcome! Feel free to fork & improve.

---

## 🛡 License

This project is released under the **MIT License**.
