// pca9685.ino, an API for the PCA9685


#include "pca9685.h"


void write8(byte reg, byte n) {
  Wire.beginTransmission(pca_addr);
  Wire.write(reg);
  Wire.write(n);
  Wire.endTransmission();
}


void write16(byte reg, short n) {
  Wire.beginTransmission(pca_addr);
  Wire.write(reg);
  Wire.write(n & 0xff);
  Wire.write((n & 0xff00) >> 8);
  Wire.endTransmission();
}


short read16(byte reg) {
  Wire.beginTransmission(pca_addr);
  Wire.write(reg);
  Wire.endTransmission(false);

  Wire.requestFrom(pca_addr, 2);
  byte n1 = Wire.read();
  byte n2 = Wire.read();
  Wire.endTransmission();

  return (int) (n2 << 8) + n1;
}
