#define MARK_EXCESS_MICROS 20
#define VOL_UP_KEY 0xB0
#define VOL_DOWN_KEY 0xEA

#include <Arduino.h>
#include <IRremote.h>
#include "RemoteAction.cpp"

int IR_RECEIVE_PIN = 10;



void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)  || defined(ARDUINO_attiny3217)
    delay(2000); // To be able to connect Serial monitor after reset or power up and before first printout
#endif

    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    Serial.println("Enabling IRin");

    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

    Serial.print(F("Ready to receive IR signals at pin "));
    Serial.println(IR_RECEIVE_PIN);

    Keyboard.begin();
}

uint16_t receiveIr(){
    if (!IrReceiver.decode()) {
        return 0;
    }

    if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
        IrReceiver.decodedIRData.flags = false; 
        Serial.println(F("Overflow detected"));
        return 0;
    } else {
        IrReceiver.printIRResultShort(&Serial);
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            IrReceiver.printIRResultRawFormatted(&Serial, true);
        }
    }
    Serial.println();

    IrReceiver.resume();

    if (IrReceiver.decodedIRData.address == 0) {
        return IrReceiver.decodedIRData.command;
    }

    return 0;
}


void loop() {
    Dispatcher dispatcher = Dispatcher();
    YTActionSet ytActionSet = YTActionSet();
    VLCMacActionSet vlcActionSet = VLCMacActionSet();
    dispatcher.setActionSet(&vlcActionSet);

    delay(200);
    uint16_t received = receiveIr();

    if (received != 0){
        dispatcher.dispatchCommand(received);
    }
}