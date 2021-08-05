#include <map>
#include <vector>
#include <Keyboard.h>

typedef enum {
    PLAY,
    FWD,
    BACK,
    NEXT,
    PREV,
    MENU,
    VOLUP,
    VOLDOWN,
    UP,
    DOWN,
    SUBS,
    INFO,
    FULLSCREEN,
    SKIP_INTRO_NETFLIX,
    MODECNG
} action_t;

#define MODE_COUNT 3
typedef enum {
    VLC,
    YT,
    NETFLIX
} mode_t;

std::map<uint16_t,action_t> samsung_cmd_2_action = {
    {0x31,PLAY},
    {0x33,FWD},
    {0x32,BACK},
    {0x34,NEXT},
    {0x35,PREV},
    {0x3A,MENU},
    {0x47,VOLUP},
    {0x48,VOLDOWN},
    {0x7D,SUBS},
    {0x3A,INFO},
    {0x7C,FULLSCREEN},
    {0x5A,SKIP_INTRO_NETFLIX},
    {0x7F,MODECNG}  
};

std::map<uint16_t,action_t> nec_cmd_2_action = {
    {0x43,PLAY},
    {0x40,FWD},
    {0x44,BACK},
    {0x47,NEXT},
    {0x45,PREV},
    {0x46,MENU},
    {0x15,VOLUP},
    {0x07,VOLDOWN},
    {0x09,SUBS},
    {0x46,INFO},
    {0xD,FULLSCREEN},
    {0x4A,SKIP_INTRO_NETFLIX},
    {0x19,MODECNG}
};

std::map<uint16_t,action_t> sony_cmd_2_action = {
    {0x1A,PLAY},
    {0x33,FWD},
    {0x34,BACK},
    {0x1C,NEXT},
    {0x1B,PREV},
    {0x1A,MENU},
    {0x12,VOLUP},
    {0x13,VOLDOWN},
    {0x4D,SUBS},
    {0xA4,INFO},
    {0x4C,FULLSCREEN},
    {0x25,SKIP_INTRO_NETFLIX},
    {0x4F,MODECNG}
};

std::map<action_t,std::vector<char>> action_2_keys[] = {
    [VLC] = {
        {PLAY,std::vector<char>({' '})},
        {FWD,std::vector<char>({(char) KEY_RIGHT_ARROW})},
        {BACK,std::vector<char>({(char) KEY_LEFT_ARROW})},
        {NEXT,std::vector<char>({'n'})},
        {PREV,std::vector<char>({'p'})},
        {MENU,std::vector<char>({'t'})},
        {VOLUP,std::vector<char>({(char) KEY_UP_ARROW})},
        {VOLDOWN,std::vector<char>({(char) KEY_DOWN_ARROW})},
        {INFO,std::vector<char>({'t'})},
        {FULLSCREEN,std::vector<char>({'f'})},
        {SUBS,std::vector<char>({'v'})}
    },
    [YT] = {
        {PLAY,std::vector<char>({'k'})},
        {FWD,std::vector<char>({'l'})},
        {BACK,std::vector<char>({'j'})},
        {NEXT,std::vector<char>({(char) KEY_LEFT_SHIFT,'n'})},
        {PREV,std::vector<char>({(char) KEY_LEFT_SHIFT,'p'})},
        {VOLUP,std::vector<char>({(char) KEY_UP_ARROW})},
        {VOLDOWN,std::vector<char>({(char) KEY_DOWN_ARROW})},
        {FULLSCREEN,std::vector<char>({'f'})},
        {SUBS,std::vector<char>({'c'})}                                                                                          
    },
    [NETFLIX] = {
        {PLAY,std::vector<char>({' '})},
        {FWD,std::vector<char>({(char) KEY_RIGHT_ARROW})},
        {BACK,std::vector<char>({(char) KEY_LEFT_ARROW})},
        {VOLUP,std::vector<char>({(char) KEY_UP_ARROW})},
        {VOLDOWN,std::vector<char>({(char) KEY_DOWN_ARROW})},
        {FULLSCREEN,std::vector<char>({'f'})},
        {SKIP_INTRO_NETFLIX,std::vector<char>({'s'})}                                                                                          
    }
};


