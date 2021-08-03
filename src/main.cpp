#define MARK_EXCESS_MICROS 20

#include <Arduino.h>
#include <IRremote.h>
#include "mappings.h"
#include <vector>

int IR_RECEIVE_PIN = 10;

IRData currIrData;
decode_type_t currProtocol;

std::map<uint16_t,action_t>& curr_cmd_2_action = samsung_cmd_2_action;
std::map<action_t,std::vector<int>>& curr_action_2_keys = vlc_action_2_keys;

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

// Holds down the keys except for the last one then presses the last one and releases all
void execute_keys(std::vector<int>& keys){
    for(auto i=keys.begin();i != (keys.end()-1);i++){
        Keyboard.press(*i);
    }

    Keyboard.write(keys.back());

    Keyboard.releaseAll();
}

bool receiveIr(IRData* irData){
    if (!IrReceiver.decode()) {
        return false;
    }

    if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
        IrReceiver.decodedIRData.flags = false; 
        Serial.println(F("Overflow detected"));
        return false;
    } else {
        IrReceiver.printIRResultShort(&Serial);
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            IrReceiver.printIRResultRawFormatted(&Serial, true);
        }
    }

    IrReceiver.resume();
    irData = &IrReceiver.decodedIRData;
    return true;
}

void loop() {
    if (!receiveIr(&currIrData)){
        return;
    }

    if(IrReceiver.decodedIRData.protocol != currProtocol){
        currProtocol = IrReceiver.decodedIRData.protocol;
        Serial.print("Switching protocol to ");Serial.print(getProtocolString(currProtocol));Serial.println();
        switch (currProtocol){
            case SAMSUNG:
                curr_cmd_2_action = samsung_cmd_2_action;
                break;        
            case NEC:
                curr_cmd_2_action = nec_cmd_2_action;
                break;
            default:
                Serial.println("Unsupported protocol");
        }
    }

    if (!(IrReceiver.decodedIRData.flags && IRDATA_FLAGS_IS_REPEAT)) {
        action_t action = curr_cmd_2_action[IrReceiver.decodedIRData.command];
        std::vector<int> keys = curr_action_2_keys[action];
        execute_keys(keys);
    }
}