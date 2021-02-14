#include "Arduino.h"
#include <Keyboard.h>

class ActionSet{
    public:
		virtual void play();
		virtual void forward();
		virtual void back();
}; 
class Dispatcher{
	public:
		Dispatcher(){
        }
		void dispatchCommand(uint16_t command){
            switch (command){
                case 0x43:
                    Serial.println("PLAY");
                    _actionSet->play();
                    break;
                case 0x40:
                    Serial.println("FWD");
                    _actionSet->forward();
                    break;
                case 0x44:
                    Serial.println("BACK");
                    _actionSet->back();
                    break;
                default:
                    Serial.println("Command not recognized");
                    break;
            } 
        }

        void setActionSet(ActionSet* actionSet){
            _actionSet = actionSet;
        }
        ActionSet* getActionSet(){
            return _actionSet;
        }
	protected:
        ActionSet* _actionSet;
};

class VLCMacActionSet : public ActionSet{
    public:
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

class YTActionSet : public ActionSet{
    public:
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
