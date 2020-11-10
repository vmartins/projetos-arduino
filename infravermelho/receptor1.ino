#define IRMP_INPUT_PIN 3
//#include <irmpSelectMain15Protocols.h> // Isso habilita os 15 principais protocolos
#define IRMP_SUPPORT_NEC_PROTOCOL 1  // Isso habilita apenas um protocolo
#include <irmp.c.h>

IRMP_DATA irmp_data;

void setup()
{
  Serial.begin(115200);
  delay(2000);

  irmp_init();
  irmp_irsnd_LEDFeedback(true); // Habilitar feedback de sinal de recepção em LED_BUILTIN

  Serial.println("Pronto para receber sinais IR no pino " + String(IRMP_INPUT_PIN));
}

void loop()
{
  if (irmp_get_data(&irmp_data) && !(irmp_data.flags & IRMP_FLAG_REPETITION)) {
    // mapeamento das teclas do controle XS-001
    switch (irmp_data.command) {
      case 0x45: Serial.println("POWER"); break;
      case 0x46: Serial.println("MODE"); break;
      case 0x47: Serial.println("MUTE"); break;
      case 0x44: Serial.println("|<<"); break;
      case 0x40: Serial.println(">>|"); break;
      case 0x43: Serial.println(">|"); break;
      case 0x7:  Serial.println("-"); break;
      case 0x15: Serial.println("+"); break;
      case 0x9:  Serial.println("EQ"); break;
      case 0x16: Serial.println("0"); break;
      case 0x19: Serial.println("USB/SD"); break;
      case 0xD:  Serial.println("<-"); break;
      case 0xC:  Serial.println("1"); break;
      case 0x18: Serial.println("2"); break;
      case 0x5E: Serial.println("3"); break;
      case 0x8:  Serial.println("4"); break;
      case 0x1C: Serial.println("5"); break;
      case 0x5A: Serial.println("6"); break;
      case 0x42: Serial.println("7"); break;
      case 0x52: Serial.println("8"); break;
      case 0x4A: Serial.println("9"); break;
      default: irmp_result_print(&irmp_data);
    }

//    // mapeamento das teclas do controle KEYES
//    switch (irmp_data.command) {
//      case 0x46: Serial.println("UP"); break;
//      case 0x44: Serial.println("LEFT"); break;
//      case 0x40: Serial.println("OK"); break;
//      case 0x43: Serial.println("RIGHT"); break;
//      case 0x15: Serial.println("DOWN"); break;
//      case 0x16: Serial.println("1"); break;
//      case 0x19: Serial.println("2"); break;
//      case 0xD:  Serial.println("3"); break;
//      case 0xC:  Serial.println("4"); break;
//      case 0x18: Serial.println("5"); break;
//      case 0x5E: Serial.println("6"); break;
//      case 0x8:  Serial.println("7"); break;
//      case 0x1C: Serial.println("8"); break;
//      case 0x5A: Serial.println("9"); break;
//      case 0x42: Serial.println("*"); break;
//      case 0x52: Serial.println("0"); break;
//      case 0x4A: Serial.println("#"); break;
//      default: irmp_result_print(&irmp_data);
//    }
  }
}