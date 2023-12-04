#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>

#define ESP01_LED_BUILTIN 2

const char* ssid = "WIFI_NOME";
const char* password = "WIFI_SENHA";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html",
              "<html>" \
                "<head><title>Interruptor</title><meta content=\"width=device-width,maximum-scale=1.0,initial-scale=1.0,minimum-scale=0.9,user-scalable=no\" name=\"viewport\"></head>" \
                "<body style=\"background-color:#e0e0e0; font-family:Tahoma, Geneva, sans-serif; color:#212121\">" \
                  "<h1 style=\"text-align: center;\">Interruptor #1</h1>" \
                  "<p style=\"text-align: center\"><a href=\"toggle?gpio=0\"><img width=\"200\" src=\"https://i.imgur.com/47QGiOr.png\"></a></p>" \
                "</body>" \
              "</html>");
}

void handleToggle() {
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "gpio") {
      int gpio = server.arg(i).toInt();
      Serial.print("Toggle GPIO");
      Serial.println(gpio);

      pinMode(gpio, OUTPUT);
      int gpioState = digitalRead(gpio);
      Serial.print("GPIO state");
      Serial.println(gpioState);

      if (gpioState == 0) {
        digitalWrite(gpio, HIGH);
      } else {
        digitalWrite(gpio, LOW);
      }
    }
  }
  handleRoot();
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  server.send(404, "text/plain", message);
}

void WiFiEvent(WiFiEvent_t event) {
    switch(event) {
        case WIFI_EVENT_STAMODE_CONNECTED:
          digitalWrite(ESP01_LED_BUILTIN, LOW); // led on
          break;

        case WIFI_EVENT_STAMODE_AUTHMODE_CHANGE:
          break;

        case WIFI_EVENT_STAMODE_GOT_IP:
            Serial.println();
            Serial.print("Conectado em: ");
            Serial.println(ssid);
            
            Serial.print("Endereço IP: ");
            Serial.println(WiFi.localIP().toString());

            break;
            
        case WIFI_EVENT_STAMODE_DISCONNECTED:
            digitalWrite(ESP01_LED_BUILTIN, HIGH); // led off
            Serial.println("Desconectado!");
            break;

        default:
          Serial.printf("[WiFi-event] event: %d\n", event);
          break;
    }
}

void setup(void) {
  Serial.begin(115200);

  pinMode(ESP01_LED_BUILTIN, OUTPUT);
  digitalWrite(ESP01_LED_BUILTIN, HIGH); // led off

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] Aguarde %d...\n", t);
    Serial.flush();
    delay(1000);
  }
  
  Serial.println("");
  Serial.print("Conectando ao wifi (");
  Serial.print(ssid);
  Serial.print("): ");

  WiFi.mode(WIFI_STA);
  WiFi.onEvent(WiFiEvent);
  WiFi.begin(ssid, password);
  
  // Aguardando conexão
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(ESP01_LED_BUILTIN, LOW); // led on
    Serial.print(".");
    delay(500);
    digitalWrite(ESP01_LED_BUILTIN, HIGH); // led off
  }

  Serial.println("");
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  
  if (MDNS.begin("esp8266", WiFi.localIP())) {
    Serial.println("mDNS iniciado [hostname=esp8266.local]");
    MDNS.addService("http", "tcp", 80);
  }

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("Servidor HTTP iniciado!");
  digitalWrite(ESP01_LED_BUILTIN, LOW); // led on
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
