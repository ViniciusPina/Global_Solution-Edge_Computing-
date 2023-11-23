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
