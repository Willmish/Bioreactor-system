#pragma once

#include <Wire.h>

#define pca_addr 0x40
#define mode_reg 0x00
#define AUTOINC 0b0100000

void write8(byte, byte);
void write16(byte, short);
short read16(byte);
