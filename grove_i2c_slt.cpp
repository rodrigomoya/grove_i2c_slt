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
  delay(3000);
}

/* read_temperature */
bool GroveSLT::read_temperature(int index, float *temperature)
{
  addr = get_address(index);
  Wire.beginTransmission(addr);
  Wire.write(5);
  error = Wire.endTransmission();
  delay(300);

  Wire.requestFrom(addr, 2);
  if(Wire.available()>=2){
    reader = Wire.read()<<8;
    reader += Wire.read();
  } else {
    reader = error;
  }

  *temperature = reader/(float)10;
  return true;
}

/* read_light */
bool GroveSLT::read_light(int index, float *light)
{
  addr = get_address(index);
  Wire.beginTransmission(addr);
  Wire.write(3);
  Wire.endTransmission();
  delay(500);

  Wire.beginTransmission(addr);
  Wire.write(4);
  error = Wire.endTransmission();
  delay(500);

  Wire.requestFrom(addr, 2);
  if(Wire.available()>=2){
    reader = Wire.read()<<8;
    reader += Wire.read();
  } else {
    reader = error;
  }

  *light = reader;
  delay(1500);

  return true;
}

/* read_soil */
bool GroveSLT::read_soil(int index, float *soil)
{
  addr = get_address(index);
  Wire.beginTransmission(addr);
  Wire.write(0);
  error = Wire.endTransmission();
  delay(500);

  Wire.requestFrom(addr, 2);
  if(Wire.available()>=2){
    reader = Wire.read()<<8;
    reader += Wire.read();
  } else {
    reader = error;
  }

  *soil = reader;
  return true;
}

/* change_address */
bool GroveSLT::read_address(int nindex, int aindex, int *newaddress)
{
  aaddr = get_address(aindex);
  naddr = get_address(nindex);
 
  /* setting */
  Wire.beginTransmission(aaddr);
  Wire.write(1);
  Wire.write(naddr);
  Wire.endTransmission();  
  delay(1000);

  /* reset */
  Wire.beginTransmission(naddr);
  Wire.write(6);
  Wire.endTransmission();  
  delay(1000);

  /* read */
  Wire.beginTransmission(naddr);
  error = Wire.endTransmission();

  *newaddress = naddr;
  return true;
}

/* get_address */
int GroveSLT::get_address(int nindex)
{
  switch (nindex) {
    case 0:
      naddr = 0x20;
      break;
    case 1:
      naddr = 0x21;
      break;
    case 2:
      naddr = 0x22;
      break;
    case 3:
      naddr = 0x23;
      break;
    case 4:
      naddr = 0x24;
      break;
    default:
      naddr = 0x20;
  }
  return naddr;
}

// SHT31 - codigo 
bool GroveSLT::read_temperature_sht(float *temperature) {
  if (! getTempHum_sht()) return NAN;
  *temperature = temp;
  return true;  
}

bool GroveSLT::read_humidity_sht(float *humidity) {  
  if (! getTempHum_sht() ) return NAN;
  *humidity = humi;
  return true;  
}

void GroveSLT::reset_sht(void) {
  writeCommand_sht(SHT31_SOFTRESET);
  delay(500);
}

void GroveSLT::heater_sht(boolean h) {
  if (h)
    writeCommand_sht(SHT31_HEATEREN);
  else
    writeCommand_sht(SHT31_HEATERDIS);
}

uint8_t GroveSLT::crc8_sht(const uint8_t *data, int len) {
  const uint8_t POLYNOMIAL(0x31);
  uint8_t crc(0xFF);
  
  for ( int j = len; j; --j ) {
    crc ^= *data++;
    for ( int i = 8; i; --i ) {
      crc = ( crc & 0x80 )
      ? (crc << 1) ^ POLYNOMIAL
      : (crc << 1);
    }
  }
  return crc; 
}

boolean GroveSLT::getTempHum_sht(void) {
  uint8_t readbuffer[6];
  writeCommand_sht(SHT31_MEAS_HIGHREP);
  
  delay(500);
  Wire.requestFrom(SHT31_ADDR, (uint8_t)6);
  if (Wire.available() != 6) 
    return false;
  for (uint8_t i=0; i<6; i++) {
    readbuffer[i] = Wire.read();
  }
  uint16_t ST, SRH;
  ST = readbuffer[0];
  ST <<= 8;
  ST |= readbuffer[1];

  if (readbuffer[2] != crc8_sht(readbuffer, 2)) return false;

  SRH = readbuffer[3];
  SRH <<= 8;
  SRH |= readbuffer[4];

  if (readbuffer[5] != crc8_sht(readbuffer+3, 2)) return false;
 
  double stemp = ST;
  stemp *= 175;
  stemp /= 0xffff;
  stemp = -45 + stemp;
  temp = stemp;
  
  double shum = SRH;
  shum *= 100;
  shum /= 0xFFFF;
  
  humi = shum;
  return true;
}

void GroveSLT::writeCommand_sht(uint16_t cmd) {
  Wire.beginTransmission(SHT31_ADDR);
  Wire.write(cmd >> 8);
  Wire.write(cmd & 0xFF);
  Wire.endTransmission();      
}
