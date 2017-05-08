/*
 * grove_i2c_slt.cpp
 *
 * Copyright (c) 2016 Rizoma.io .
 * Website    : www.rizoma.io
 * Author     : Rodrigo Moya
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "suli2.h"
#include "grove_i2c_slt.h" 

GroveSLT::GroveSLT(int pinsda, int pinscl) {
  this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
  suli_i2c_init(i2c, pinsda, pinscl);  
  Wire.begin();

  Wire.beginTransmission(0x20);
  Wire.write(6);
  Wire.endTransmission();

  delay(500);
}

/* read_temperature */
bool GroveSLT::read_temperature(float *temperature)
{
  Wire.beginTransmission(0x20);
  Wire.write(0x05);
  Wire.endTransmission();
  delay(300);

  Wire.requestFrom(0x20, 2);
  unsigned int reader = reader | Wire.read();

  *temperature = reader;
  return true;
}

/* read_light */
bool GroveSLT::read_light(float *light)
{
  Wire.beginTransmission(0x20);
  Wire.write(0x04);
  Wire.endTransmission();
  delay(300);

  Wire.requestFrom(0x20, 2);
  unsigned int reader = Wire.read() << 8;

  *light = reader;
  return true;
}

/* read_soil */
bool GroveSLT::read_soil(float *soil)
{
  Wire.beginTransmission(0x20);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(300);

  Wire.requestFrom(0x20, 2);
  unsigned int reader = Wire.read() << 8;

  *soil = reader;
  return true;
}