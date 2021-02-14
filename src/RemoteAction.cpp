#include "Arduino.h"
#include <Keyboard.h>

#define ACTION_COUNT 3

class ActionSet{
    public:
		virtual void play();
		virtual void forward();
		virtual void back();
}; 
class Dispatcher{
	public:
		Dispatcher(ActionSet* actionSet,uint16_t dispatchArr[ACTION_COUNT]){
            _actionSet = actionSet;
            setDispatchArr(dispatchArr);
        }
		void dispatchCommand(uint16_t command){
            if (command == _dispatchArr[0]){
                Serial.println("PLAY");
                _actionSet->play();
            }else if(command == _dispatchArr[1]){
                Serial.println("FWD");
                _actionSet->forward();
            }else if(command == _dispatchArr[2]){
                Serial.println("BACK");
                _actionSet->back();
            }else{
                Serial.println("Command not recognized");
            }
        }

        void setActionSet(ActionSet* actionSet){
            _actionSet = actionSet;
        }
        ActionSet* getActionSet(){
            return _actionSet;
        }

        void setDispatchArr(uint16_t dispatchArr[ACTION_COUNT]){
            for(int i=0;i<ACTION_COUNT;i++){
                _dispatchArr[i] = dispatchArr[i];
            }
        }


	private:
        ActionSet* _actionSet;
        uint16_t _dispatchArr[ACTION_COUNT];
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
