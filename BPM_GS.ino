#include "ArduinoJson.h"
#include "EspMQTTClient.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

EspMQTTClient client{
  "Wokwi-GUEST", // SSID do WiFi
  "",             // Senha do wifi
  "mqtt.tago.io", // Endereço do servidor
  "Default",      // Usuario
  "1d7ce6b2-8199-49b4-95db-8ffd76204ce4",   // Token do device
  "esp",          // Nome do device
  1883            // Porta de comunicação
};

const int pinoPotenciometro = 32; // Pino do potenciômetro
int batimentosCardiacos = 0;

void onConnectionEstablished(){ // Função chamada quando a conexão é estabelecida

}

void setup() {
    Serial.begin(9600);
    Wire.begin(); // Inicia a comunicação I2C para o display OLED

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
        Serial.println(F("Erro ao iniciar o display OLED"));
        for(;;);
    }

    Serial.println("Conectando ao wifi");
    while (!client.isWifiConnected()) { // Loop de tentativa de conexão WiFi
        Serial.print('.');
        client.loop();
        delay(1000);
    }
    Serial.println("MQTT Conectado");
}

void loop() {
    delay(1000);
    int valorPotenciometro = analogRead(pinoPotenciometro);

    // Convertendo o valor do potenciômetro para batimentos cardíacos simulados
    batimentosCardiacos = map(valorPotenciometro, 0, 1023, 60, 150); // Mapeia o valor do potenciômetro para a faixa de batimentos cardíacos (60 a 150 bpm)

    Serial.print("Batimentos Cardíacos: "); // Exibição dos batimentos cardíacos no terminal serial
    Serial.println(batimentosCardiacos);

    char bufferJson[100];

    // Enviar batimentos cardíacos para a plataforma Tago.io
    sprintf(bufferJson, "{\"variable\":\"batimentos\",\"value\":%d}", batimentosCardiacos);
    client.publish("tago/data", bufferJson);

    client.loop();

    // Mostrar batimentos cardíacos no terminal serial
    Serial.print("Batimentos Cardíacos: ");
    Serial.println(batimentosCardiacos);

    // Mostrar batimentos cardíacos no display OLED
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("BPM: ");
    display.println(batimentosCardiacos);
    display.display();

    delay(1000);
}
