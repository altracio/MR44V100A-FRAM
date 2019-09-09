# MR44V100A-FRAM

*Particle driver for MR44V100A FRAM*

This little board is a FRAM (Ferroelectric RAM).

It's 1MB in size, and the main benefit is that it's non-volatile like EEPROM so the contents are preserved if you remove power, but it's also very fast and doesn't have the limited wear cycles of EEPROM.

## Circuit

The pins on the Adafruit breakout connect as typical for an I2C device:

- VCC to 3V3
- VSS to GND
- WP not connected (connect to VCC to prevent writes to the memory)
- SCL connect to D1 (SCL)
- SDA connect to D0 (SDA)
- A2 not connected. Connect to VCC to change the I2C address. 
- A1 not connected. Connect to VCC to change the I2C address. 

## Using the code

Typically you create a global variable for the FRAM:

```
MR44V100A fram(Wire, 0);
```

The first parameter is the Wire interface to use, typically Wire (D0/D1). On the Electron you can also use Wire1 (C4/C5).

The second parameter is the address. Pass 0 if you left the A0-A3 pins unconnected. It can be 0-7 depending on the value set on A0-A3.

From setup you typically call:

```
fram.begin();
```

To read and write data you use the readData and writeData methods:

```
bool readData(size_t framAddr, uint8_t *data, size_t dataLen);
bool writeData(size_t framAddr, const uint8_t *data, size_t dataLen);
```

You can also use get and put like the [EEPROM API](https://docs.particle.io/reference/firmware/photon/#eeprom). This makes it easy to convert code between using the built-in EEPROM and FRAM as you can use the calls nearly identically.

