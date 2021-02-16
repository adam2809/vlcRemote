#include "Arduino.h"
#include <Keyboard.h>

#define ACTION_COUNT 10

class ActionSet{
    public:
		virtual void play();
		virtual void forward();
		virtual void back();
		virtual void sub();
		virtual void next();
		virtual void prev();
		virtual void info();
		void volUp(){
            Keyboard.write(KEY_UP_ARROW);
        }
		void volDown(){
            Keyboard.write(KEY_DOWN_ARROW);
        }		
        void fullscreen(){
            Keyboard.write('f');
        }
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
            }else if(command == _dispatchArr[3]){
                Serial.println("SUB");
                _actionSet->sub();
            }else if(command == _dispatchArr[4]){
                Serial.println("NEXT");
                _actionSet->next();
            }else if(command == _dispatchArr[5]){
                Serial.println("PREV");
                _actionSet->prev();
            }else if(command == _dispatchArr[6]){
                Serial.println("INFO");
                _actionSet->info();
            }else if(command == _dispatchArr[7]){
                Serial.println("VOLUP");
                _actionSet->volUp();
            }else if(command == _dispatchArr[8]){
                Serial.println("VOLDOWN");
                _actionSet->volDown();
            }else if(command == _dispatchArr[9]){
                Serial.println("FULLSCREEN");
                _actionSet->fullscreen();
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

class VLCActionSet : public ActionSet{
    public:
        void play(){
            Keyboard.write(' ');
        }
		virtual void next(){
            Keyboard.write('n');
        }
		virtual void prev(){
            Keyboard.write('p');
        }
		virtual void info(){
            Keyboard.write('t');
        }
};

class VLCMacActionSet : public VLCActionSet{
    public:
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

        void sub(){
            Keyboard.write('s');
        }
};
class VLCLinuxActionSet : public VLCActionSet{
    public:
        void forward(){
            Keyboard.write(KEY_RIGHT_ARROW);
        }
        void back(){
            Keyboard.write(KEY_LEFT_ARROW);
        }
        void sub(){
            Keyboard.write('v');
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
        void sub(){
            Keyboard.write('c');
        }
		virtual void next(){
            Keyboard.press(KEY_LEFT_SHIFT);

            Keyboard.write('n');

            Keyboard.releaseAll();
        }
		virtual void prev(){
            Keyboard.press(KEY_LEFT_SHIFT);

            Keyboard.write('p');

            Keyboard.releaseAll();
        }
		virtual void info(){
            Serial.println("Command not supported");
        }
};
