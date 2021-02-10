#include <Arduino.h>
#include <IRremote.h>
#include <Keyboard.h>

#define IR_RECEIVE_PIN 16

IRrecv Rx(IR_RECEIVE_PIN);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)
    delay(2000);
#endif
    Serial.println(F("START " __FILE__ " from " __DATE__));

    IrReceiver.enableIRIn();
    IrReceiver.blink13(true);

    Serial.print(F("Ready to receive IR signals at pin "));
    Serial.println(IR_RECEIVE_PIN);

}


long receiveIrCode(){
    long res = -1;
    if (IrReceiver.decode()) { 
        if (IrReceiver.results.overflow) {
            Serial.println("IR code too long.");
            return -1;
        }

        res = IrReceiver.results.value;
        
        Serial.print("Received code: ");
        Serial.print(res, HEX);
        Serial.println();


        IrReceiver.resume();
    }
    return res;
}

void performIrAction(long code){
    switch (code){
        case 0xFFC23D:
            Serial.println("PLAY");
            break;
        default:
            Serial.print("Code could not have been matched to action: ");
            Serial.print(code, HEX);
            Serial.println();
            break;
    }
}

void loop() {
    long code = receiveIrCode();
    if(code == -1){
        return;
    }
    performIrAction(code);
}
