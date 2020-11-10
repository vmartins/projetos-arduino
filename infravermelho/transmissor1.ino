#define IRSND_OUTPUT_PIN 4
#define IRSND_IR_FREQUENCY 38000
#include <irsndSelectMain15Protocols.h>
#include <irsnd.c.h>

IRMP_DATA irsnd_data;

void setup()
{
    Serial.begin(115200);
    delay(2000);

    irsnd_init();
    irmp_irsnd_LEDFeedback(true); // Habilitar feedback de sinal de recepção em LED_BUILTIN

    Serial.println("Pronto para enviar sinais IR no pino " + String(IRSND_OUTPUT_PIN));
}

void loop()
{   
    Serial.println("Tecla POWER do controle XS-001");
    irsnd_data.protocol = IRMP_NEC_PROTOCOL;
    irsnd_data.address = 0xFF00;
    irsnd_data.command = 0x45;
    irsnd_data.flags = 1; // repeat frame times
    irsnd_send_data(&irsnd_data, false);

    delay(500);

    Serial.println("Tecla '-' do controle XS-001");
    irsnd_data.protocol = IRMP_NEC_PROTOCOL;
    irsnd_data.address = 0xFF00;
    irsnd_data.command = 0x7;
    irsnd_data.flags = 2; // repeat frame times
    irsnd_send_data(&irsnd_data, false);

    delay(1500);
}
