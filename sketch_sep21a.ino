#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"
#include <ESPmDNS.h>

// Įrašyk savo namų Wi-Fi duomenis
const char* ssid = "TP-Link_33FC";
const char* password = "H4WDr5Wj";

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

WebServer server(80);

// 1. Sukuriame naują "nematomą" adresą, kuris grąžina tik grynus skaičius
void handleData() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  
  // Jei jutiklis užstrigo, grąžiname brūkšnelius
  if (isnan(t) || isnan(h)) {
    server.send(200, "application/json", "{\"temp\":\"--\", \"hum\":\"--\"}");
    return;
  }
  
  // Sukuriame duomenų paketą
  String json = "{\"temp\":\"" + String(t, 1) + "\", \"hum\":\"" + String(h, 1) + "\"}";
  server.send(200, "application/json", json);
}

// 2. Pagrindinis puslapis su atnaujinimo varikliuku
void handleRoot() {
  String html = "<html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<style>body{font-family: Arial, sans-serif; text-align: center; margin-top: 50px; background-color: #f4f4f9;} ";
  html += "h1{color: #333;} .box{background: white; padding: 20px; border-radius: 10px; display: inline-block; box-shadow: 0px 4px 10px rgba(0,0,0,0.1);} ";
  html += ".data{font-size: 2.5em; font-weight: bold; color: #0066cc;}</style>";
  
  // JavaScript kodas, kuris kas 2000 milisekundžių (2 sek.) prašo naujų duomenų
  html += "<script>";
  html += "setInterval(function() {";
  html += "  fetch('/data').then(response => response.json()).then(data => {";
  html += "    document.getElementById('t').innerHTML = data.temp + ' &deg;C';";
  html += "    document.getElementById('h').innerHTML = data.hum + ' %';";
  html += "  });";
  html += "}, 2000);"; 
  html += "</script></head>";
  
  // HTML struktūra (atkreipk dėmesį į id='t' ir id='h' - pagal juos JavaScript suranda, ką pakeisti)
  html += "<body><div class='box'><h1>Mano ESP32 Orų Stotelė</h1>";
  html += "<p>Temperatūra</p><p class='data' id='t'>Kraunama...</p>";
  html += "<p>Drėgmė</p><p class='data' id='h'>Kraunama...</p>";
  html += "</div></body></html>";
  
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Jungiamasi prie Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nPrisijungta!");
  Serial.print("Tavo ESP32 IP adresas yra: ");
  Serial.println(WiFi.localIP());

  // Registruojame kelius
  server.on("/", handleRoot);        // Žmogui matomas puslapis
  server.on("/data", handleData);    // Nematomas kelias duomenims
  server.begin();
  if (MDNS.begin("stotele")) {
    Serial.println("mDNS veikia! Narsykleje iveskite: http://stotele.local");
  }
}

void loop() {
  server.handleClient(); // Laukia lankytojų
}