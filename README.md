# Global_Solution-Edge_Computing-
Autores: Vinicius Pina Rm 550986 , Felipe Hideki Rm98323
Link da simulação: https://wokwi.com/projects/382143837686402049

Problema de Saúde Abordado:
O projeto parece abordar a monitorização dos batimentos cardíacos. Ao ler um valor de um potenciômetro (simulando uma medição cardíaca), 
converte esse valor em batimentos cardíacos simulados (60 a 150 bpm) e envia esses dados para a plataforma Tago.io.
Essa informação pode ser usada para monitorar e analisar a frequência cardíaca, 
o que é crucial para identificar possíveis problemas cardíacos ou para monitorar a saúde cardiovascular em geral.

Visão Geral da Solução Proposta:
Hardware:
Utiliza um potenciômetro para simular medição de batimentos cardíacos.
Display OLED para exibir a frequência cardíaca em tempo real.
Conexão WiFi para enviar dados para a plataforma Tago.io.
Software:
Usa a biblioteca ArduinoJson para manipular os dados em formato JSON.
Usa EspMQTTClient para estabelecer a conexão MQTT e enviar dados para o servidor.
Utiliza a biblioteca Adafruit_SSD1306 para controlar o display OLED.
Configuração e Execução:
Configuração de Hardware:

Conecte o potenciômetro ao pino definido (pinoPotenciometro).
Conecte o display OLED seguindo as especificações (SCREEN_WIDTH, SCREEN_HEIGHT, etc.).
Configuração de Software:

Instale as bibliotecas necessárias (ArduinoJson, EspMQTTClient, Adafruit_GFX, Adafruit_SSD1306) no ambiente de desenvolvimento (IDE do Arduino).
Copie e cole o código no IDE do Arduino.
Verifique se as informações de conexão WiFi e Tago.io estão corretas.
Execução:

Carregue o código para o dispositivo ESP32.
Abra o monitor serial para visualizar as mensagens de depuração (Serial.println).
Verifique se os batimentos cardíacos simulados estão sendo exibidos no display OLED e se estão sendo enviados para a plataforma Tago.io.




Codigo do projeto:
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

void onConnectionEstablished(){

}

void setup() {
    Serial.begin(9600);
    Wire.begin(); // Inicia a comunicação I2C para o display OLED

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
        Serial.println(F("Erro ao iniciar o display OLED"));
        for(;;);
    }

    Serial.println("Conectando ao wifi");
    while (!client.isWifiConnected()) {
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

    Serial.print("Batimentos Cardíacos: ");
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

