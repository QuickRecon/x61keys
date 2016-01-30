# x61keys
An application to allow the Thinkpad x61 volume and 'ThinkVantage' buttons to be functional.

The volume keys are now functional.

To run just compile volume/main.cpp with the command:
```
gcc ./volume/main.cpp
```
and run a.out as root with:
```
sudo a.out
```

Presssing the volume up/down keys will adjust the alsa volume and the mute key will set it to 0.
