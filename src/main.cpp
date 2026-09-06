#include <Arduino.h>

#include "Config/HardwareConfig.h"
#include "Drivers/Esp32Gpio.h"
#include "Infrastructure/MosfetActuator.h"
#include "Application/IrrigationController.h"


Esp32Gpio mosfetTrig(
    HardwareConfig::MOSFET_TRIG_PIN
);

MosfetActuator pumpActuator(
    mosfetTrig
);

IrrigationController irrigation(
    pumpActuator
);


void setup() {

    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("================================");
    Serial.println("          SOPHIA GAIA");
    Serial.println("       ACTUATOR SPRINT 01");
    Serial.println("================================");


    // Inicializa GPIO
    mosfetTrig.begin();

    Serial.println("GPIO................ OK");
    Serial.println("MOSFET ACTUATOR..... OK");
    Serial.println("IRRIGATION.......... READY");

    Serial.println("================================");
    Serial.println("PUMP: OFF");
    Serial.println("================================");

}


void loop() {

    Serial.println(">>> LIGANDO BOMBA");

    irrigation.start();

    Serial.println("PUMP STATE: ON");

    delay(3000);


    Serial.println(">>> DESLIGANDO BOMBA");

    irrigation.stop();

    Serial.println("PUMP STATE: OFF");

    delay(5000);
}