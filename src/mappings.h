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
    {0x7F,MODECNG}  
};

std::map<uint16_t,action_t> nec_cmd_2_action = {
    {0x43,PLAY},
    {0x40,FWD},
    {0x44,BACK},
    {0x47,NEXT},
    {0x45,PREV},
    {0x46,MENU},
    {0x47,VOLUP},
    {0x48,VOLDOWN},
    {0xD,MODECNG}
};

std::map<action_t,std::vector<int>> action_2_keys[] = {
    [VLC] = {
        {PLAY,std::vector<int>({' '})},
        {FWD,std::vector<int>({KEY_RIGHT_ARROW})},
        {BACK,std::vector<int>({KEY_LEFT_ARROW})},
        {NEXT,std::vector<int>({'n'})},
        {PREV,std::vector<int>({'p'})},
        {MENU,std::vector<int>({'t'})},
        {VOLUP,std::vector<int>({KEY_UP_ARROW})},
        {VOLDOWN,std::vector<int>({KEY_DOWN_ARROW})}
    },
    [YT] = {
        {PLAY,std::vector<int>({'k'})},
        {FWD,std::vector<int>({'l'})},
        {BACK,std::vector<int>({'j'})},
        {NEXT,std::vector<int>({KEY_LEFT_SHIFT,'n'})},
        {PREV,std::vector<int>({KEY_LEFT_SHIFT,'p'})},
        {VOLUP,std::vector<int>({KEY_UP_ARROW})},
        {VOLDOWN,std::vector<int>({KEY_DOWN_ARROW})}
    }
};


