#!/bin/bash
sudo apt update -y  > /dev/null
sudo apt upgrade -y > /dev/null
sudo apt install -y libsdl2-dev libsdl2-ttf-dev libc6 > /dev/null
./make > /dev/null


