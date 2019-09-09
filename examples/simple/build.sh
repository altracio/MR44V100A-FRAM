#!/bin/bash

\rm boron_firm* ;

particle compile boron --target 1.2.1 \
  fram-simple.cpp \
  ../../src/MR44V100A-FRAM.cpp \
  ../../src/MR44V100A-FRAM.h \
;

# stty -f /dev/tty.usbmodem* 14400 ;

particle flash --usb boron_firm* ;