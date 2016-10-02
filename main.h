//
// Created by aren on 2/10/16.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <linux/input.h>
#include <fstream>
#include <iostream>
#include <sstream>

//select input here
#define VOLUMEKEYS "/dev/input/by-path/platform-i8042-serio-0-event-kbd"
#define CONFIGPATH "~/.config/x61keys/x61keys.conf"


#ifndef X61KEYS_MAIN_H
#define X61KEYS_MAIN_H
struct config;
int runSystemCommand(std::string command);
int readConfigFile();
#endif //X61KEYS_MAIN_H
