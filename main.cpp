
#include "main.h"

constexpr unsigned int str2int(std::string str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

struct configTemplate{
    std::string volumeup;
    std::string volumedown;
    std::string mutetrue;
    std::string mutefalse;
    std::string mute;
};

struct configTemplate config;

int runSystemCommand(std::string command){
    int pid = fork();
    if (pid==0){
        execl("/bin/sh", "-c", command);
        return 0;
    }
}

int readConfigFile(){
    std::string line;
    std::ifstream ConfigFile;

    ConfigFile.open(CONFIGPATH);
    if (ConfigFile.is_open()){
        while (getline(ConfigFile, line)){
            std::string parameter;
            std::string name;
            char splitter = '=';
            std::stringstream linestream(line);

            getline(linestream, name, splitter);
            getline(linestream, parameter, splitter);

            switch (str2int(name)){
                case str2int("volumeup"):
                    config.volumeup = parameter;
                case str2int("volumedown"):
                    config.volumedown = parameter;
                case str2int("mutetrue"):
                    config.mutetrue = parameter;
                case str2int("mutefalse"):
                    config.mutefalse = parameter;
                case str2int("mute"):
                    config.mute = parameter;
                default:
                    perror("config file syntax error, invalid button name");
                    return 1;
            }
        }
        ConfigFile.close();
        return 0;
    }
}

int main() {
    int thinkpadkeys;
    struct input_event thinkpadInputEvent;

    bool mute = false;
    runSystemCommand("amixer set Master unmute");

    if((thinkpadkeys = open(VOLUMEKEYS, O_RDONLY)) == -1) {
        perror("opening volume keys");
        return 1;
    };

    while(true) {
        if(read(thinkpadkeys, &thinkpadInputEvent, sizeof(struct input_event))) {
            printf("volume, type %d\tcode %d\tvalue %d\n", thinkpadInputEvent.type, thinkpadInputEvent.code, thinkpadInputEvent.value);
            if(thinkpadInputEvent.code == 115){
                //volume up
                runSystemCommand("amixer set Master 1%+");
            } else if(thinkpadInputEvent.code == 114){
                //volume down
                runSystemCommand("amixer set Master 1%-");
            } else if(thinkpadInputEvent.code == 113){
                //mute
                runSystemCommand("amixer set Master mute");
            }
        }
    };
    return 0;
}
