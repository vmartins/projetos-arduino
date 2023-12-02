#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>

#define ESP01_LED_BUILTIN 2

const char* ssid = "WIFI_NOME";
const char* password = "WIFI_SENHA";
MDNSResponder mdns;

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

void setup(void) {
  Serial.begin(115200);

  pinMode(ESP01_LED_BUILTIN, OUTPUT);
  digitalWrite(ESP01_LED_BUILTIN, HIGH); // led off

  Serial.println("");
  Serial.print("Conectando ao wifi (");
  Serial.print(ssid);
  Serial.print("): ");

  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  
  // Aguardando conexão
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(ESP01_LED_BUILTIN, LOW); // led on
    delay(500);
    Serial.print(".");
    digitalWrite(ESP01_LED_BUILTIN, HIGH); // led off
  }

  digitalWrite(ESP01_LED_BUILTIN, LOW); // led on
  Serial.println("");
  Serial.print("Conectado em: ");
  Serial.println(ssid);
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP().toString());

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Servidor HTTP iniciado!");
}

void loop(void) {
  server.handleClient();
  mdns.update();
}
