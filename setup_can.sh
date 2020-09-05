#!/bin/bash


state='up'
setup=1
devname="ttyACM0"

echo This script may or may not work. Who knows?
echo

if [[ $1 == "teardown" ]]; then
  state='down'
  setup=0
elif [[ $1 == "" ]]; then
  state="up"
  setup=1
elif [[ $1 != "" ]]; then
  devname=$1
else
  echo "Unrecognized command $1"
  exit 1
fi


if [ "$EUID" -ne 0 ]; then
  echo "This must be run as root, otherwise it will fail."
  exit 1
fi

ls /dev | grep $devname > /dev/null

if (( $? != 0 )); then
  echo "$devname was not found. Please make sure the CANable is plugged in and functioning."
  exit $?
fi

if (( $setup == 1 )); then
  # -s is to set the speed, values are from 0 to 8, with 0 being 125k

  # -s0 = 10k
  # -s1 = 20k
  # -s2 = 50k
  # -s3 = 100k
  # -s4 = 125k
  # -s5 = 250k
  # -s6 = 500k
  # -s7 = 750k
  # -s8 = 1M

  slcand -o -c -s8 /dev/$devname can0
  if (( $? != 0 )); then
    echo Unable to init can0. Is it already setup?
    echo "check to make sure the device name is correct using dmesg -kT"
  fi

  # set the can interface up
  ip link set can0 up

  if (( $? != 0 )); then
    echo Unable to set can0 to state UP
  fi

else
  echo closing can0 link
  ip link set can0 down

  if (( $? != 0 )); then
    echo Unable to set can0 to state DOWN
  fi

fi

echo "Setup complete."
