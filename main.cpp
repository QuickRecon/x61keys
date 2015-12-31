/*
http://stackoverflow.com/questions/11519759/how-to-read-low-level-mouse-click-position-in-linux
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <linux/input.h>
#include <alsa/asoundlib.h>
#include <fcntl.h>

//select input here
#define VOLUMEKEYS "/dev/input/by-path/platform-i8042-serio-0-event-kbd"
#define THINKVANTAGE "/dev/input/by-path/platform-thinkpad_acpi-event"
/*
void SetAlsaMasterVolume(long volume)
{
    long min, max;
    snd_mixer_t *handle;
    snd_mixer_selem_id_t *sid;
    const char *card = "default";
    const char *selem_name = "Master";

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    snd_mixer_selem_set_playback_volume_all(elem, volume * max / 100);

    snd_mixer_close(handle);
}
**/
int main()
{
    int volumefd;
    struct input_event volumeie;

    int thinkvantagefd;
    struct input_event thinkvantageie;

    if((volumefd = open(VOLUMEKEYS, O_RDONLY)) == -1) {
        perror("opening volume keys");
        exit(EXIT_FAILURE);
    };

    if((thinkvantagefd = open(THINKVANTAGE, O_RDONLY)) == -1) {
        perror("opening thinkvantage key");
        exit(EXIT_FAILURE);
    };

    while(true) {
        if(read(volumefd, &volumeie, sizeof(struct input_event))) {
            printf("volume, type %d\tcode %d\tvalue %d\n", volumeie.type, volumeie.code, volumeie.value);
        } else {

        }
        if(read(thinkvantagefd, &thinkvantageie, sizeof(struct input_event))) {
            printf("thinkvantage, type %d\tcode %d\tvalue %d\n", thinkvantageie.type, thinkvantageie.code, thinkvantageie.value);
        } else {
            
        }
    };
    return 0;
}
