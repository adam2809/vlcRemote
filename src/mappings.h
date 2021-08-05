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
    MODECNG
} action_t;

#define MODE_COUNT 2
typedef enum {
    VLC,
    YT
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
    {0x19,MODECNG}
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
    }
};


