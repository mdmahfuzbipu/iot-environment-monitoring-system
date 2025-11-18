#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>

// ------------------ SENSOR SETUP ------------------
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP280 bmp;
const int mqPin = 34;

// ------------------ WIFI & SERVER ------------------
const char *ssid = "Your-WiFi-Name";
const char *password = "Your-WiFi-Password";
const char *serverName = "http://your-ip:8000/api/data/";

// ------------------ SETUP ------------------
void setup()
{
    Serial.begin(115200);

    dht.begin();

    if (!bmp.begin())
    {
        Serial.println("BMP280 not found! Pressure will be sent as null.");
    }

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");
}

// ------------------ LOOP ------------------
void loop()
{
    // Read sensors
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    float pressure = bmp.begin() ? bmp.readPressure() / 100.0F : NAN; // hPa
    float air_quality = analogRead(mqPin);

    // Prepare JSON
    String temperatureStr = isnan(temperature) ? "null" : String(temperature, 2);
    String humidityStr = isnan(humidity) ? "null" : String(humidity, 2);
    String pressureStr = isnan(pressure) ? "null" : String(pressure, 2);
    String airStr = isnan(air_quality) ? "null" : String(air_quality, 0);

    String jsonData = "{\"temperature\":" + temperatureStr +
                      ",\"humidity\":" + humidityStr +
                      ",\"air_quality\":" + airStr +
                      ",\"pressure\":" + pressureStr + "}";

    // Send to Django
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        http.begin(serverName);
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(jsonData);
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        http.end();
    }
    else
    {
        Serial.println("WiFi disconnected! Reconnecting...");
        WiFi.reconnect();
    }

    delay(5000);
}
