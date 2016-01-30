/*
http://stackoverflow.com/questions/11519759/how-to-read-low-level-mouse-click-position-in-linux
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <linux/input.h>
#include <fcntl.h>

//select input here
#define THINKVANTAGE "/dev/input/by-path/platform-thinkpad_acpi-event"

int main()
{

    int thinkvantagefd;
    struct input_event thinkvantageie;

    if((thinkvantagefd = open(THINKVANTAGE, O_RDONLY)) == -1) {
        perror("opening thinkvantage key");
        exit(EXIT_FAILURE);
    };

    while(true) {
        if(read(thinkvantagefd, &thinkvantageie, sizeof(struct input_event))) {
            printf("thinkvantage, type %d\tcode %d\tvalue %d\n", thinkvantageie.type, thinkvantageie.code, thinkvantageie.value);
            if(thinkvantageie.type == 4)
        }
    };
    return 0;
}
