/*
http://stackoverflow.com/questions/11519759/how-to-read-low-level-mouse-click-position-in-linux
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <linux/input.h>
#include <fcntl.h>

//select input here
#define VOLUMEKEYS "/dev/input/by-path/platform-i8042-serio-0-event-kbd"

int main()
{
    int volumefd;
    struct input_event volumeie;

    bool mute = false;
    system("amixer set Master unmute");

    if((volumefd = open(VOLUMEKEYS, O_RDONLY)) == -1) {
        perror("opening volume keys");
        exit(EXIT_FAILURE);
    };

    while(true) {
        if(read(volumefd, &volumeie, sizeof(struct input_event))) {
            printf("volume, type %d\tcode %d\tvalue %d\n", volumeie.type, volumeie.code, volumeie.value);
            if(volumeie.code == 115){
                //volume up
                system("amixer set Master 1%+");
            } else if(volumeie.code == 114){
                //volume down
                system("amixer set Master 1%-");
            } else if(volumeie.code == 113){
                //mute
                system("amixer set Master 0");
            }
        }
    };
    return 0;
}
