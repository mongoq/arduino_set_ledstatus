# https://arduino.stackexchange.com/questions/16776/how-to-connect-arduino-device-to-linux

#!/bin/bash

echo -e "\n--- MongoQ's 3x LED Parser ---\n"

#echo "${#1}"
#echo "$#"
#if ($# != 1)
#&& (${#1} != 3)
#echo $#

#TODO ...
#echo ${1:0:1}
#echo ${1:1:1}
#echo ${1:2:1}

if [ $# != 1 ] || [ ${#1} != 3 ]
then
 echo -e "Run with Parameter '101' to activate RGB LEDs\n"
 exit 1
fi

tty=/dev/ttyUSB0
stty -F $tty cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts -hupcl
#sleep 1

echo $1 > $tty

#read "reply" < $tty
#echo $reply

# TODO: Inmplement Talkback ...

#if [ "$reply" == "OK\n" ] 
#then
# echo -e "Done ;-)";
#fi

echo -e "Done ;-)\n"

#Use this ?! --> Reset ?!
#stty -F $tty hupcl
