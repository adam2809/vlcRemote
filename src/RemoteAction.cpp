#include "Arduino.h"
#include <Keyboard.h>

class RemoteAction{
	public:
		RemoteAction(){
        }
		void perform(uint16_t command){
            switch (command){
                case 0x43:
                    Serial.println("PLAY");
                    play();
                    break;
                case 0x40:
                    Serial.println("FWD");
                    forward();
                    break;
                case 0x44:
                    Serial.println("BACK");
                    back();
                    break;
                default:
                    Serial.println("Command not recognized");
                    break;
            } 
        }
	protected:
		virtual void play();
		virtual void forward();
		virtual void back();
};
class VLCRemoteAction : public RemoteAction{
    protected:
        void play(){
            Keyboard.write(' ');
        }
        void forward(){
            Keyboard.press(KEY_LEFT_GUI);
            Keyboard.press(KEY_LEFT_ALT);

            Keyboard.write(KEY_RIGHT_ARROW);

            Keyboard.releaseAll();
        }
        void back(){
            Keyboard.press(KEY_LEFT_GUI);
            Keyboard.press(KEY_LEFT_ALT);

            Keyboard.write(KEY_LEFT_ARROW);

            Keyboard.releaseAll();
        }
};

class YTRemoteAction : public RemoteAction{
    protected:
        void play(){
            Keyboard.write('k');
        }
        void forward(){
            Keyboard.write('l');
        }
        void back(){
            Keyboard.write('j');
        }
};
