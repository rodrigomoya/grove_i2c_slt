/*
 * grove_i2c_slt.h
 *
 * Copyright (c) 2017 rizoma.io
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


#ifndef __GROVE_SLT_H__
#define __GROVE_SLT_H__

#include "suli2.h"

//GROVE_NAME        "Grove - SLT - Single"
//SKU               10101233216312351SDS23ASDASDASDASD
//IF_TYPE           I2C
//IMAGE_URL         https://d3s5r33r268y59.cloudfront.net/4974/products/thumbs/2015-10-26T14:22:55.624Z-DSC01306.JPG.2560x2560_q85.jpg
//DESCRIPTION       "Driver for SLT de Tindie"
//WIKI_URL          http://www.rizoma.io
//ADDED_AT          "2017-05-05"
//AUTHOR            "Rodrigo Moya Toro - rodrigo@rizoma.io"


#define SHT31_ADDR    0x44
#define SHT31_MEAS_HIGHREP_STRETCH 0x2C06
#define SHT31_MEAS_MEDREP_STRETCH  0x2C0D
#define SHT31_MEAS_LOWREP_STRETCH  0x2C10
#define SHT31_MEAS_HIGHREP         0x2400
#define SHT31_MEAS_MEDREP          0x240B
#define SHT31_MEAS_LOWREP          0x2416
#define SHT31_READSTATUS           0xF32D
#define SHT31_CLEARSTATUS          0x3041
#define SHT31_SOFTRESET            0x30A2
#define SHT31_HEATEREN             0x306D
#define SHT31_HEATERDIS            0x3066

class GroveSLT
{
	public:
		GroveSLT(int pinsda, int pinscl);

		/**
		 * Change address of Sensor
		 * 
		 * @param nindex - Nuevo Indice(0--9) 
		 * @param aindex - Actual Indice (0--9)
		 * 
		 * @return bool 
		 */		
		bool read_address(int nindex, int aindex, int *newaddress);
		
		/**
		 * ReadTemperature
		 * 
		 * @param index - Indice, por defecto es cero = 0x20 
		 * 
		 * @return bool 
		 */	
		bool read_temperature(int index, float *temperature);
		
		/**
		 * ReadLight
		 * 
		 * @param index - Indice, por defecto es cero = 0x20 
		 * 
		 * @return bool 
		 */			
		bool read_light(int index, float *light);

		/**
		 * SoilLight
		 * 
		 * @param index - Indice, por defecto es cero = 0x20 
		 * 
		 * @return bool 
		 */		
		bool read_soil(int index, float *soil);
	    bool read_temperature_sht(float *temperature);
	    bool read_humidity_sht(float *humidity);
	    void reset_sht(void);
	    void heater_sht(boolean);
	    uint8_t crc8_sht(const uint8_t *data, int len);

	private:
    	I2C_T *i2c;
	    boolean getTempHum_sht(void);
	    void writeCommand_sht(uint16_t cmd);
	    int get_address(int nindex);

    float temperature, light, soil, reader, error;
    int naddr, aaddr, addr;

    // sht31
    float humi, temp;

};
#endif