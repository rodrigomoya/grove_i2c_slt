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


#ifndef __GROVE_SHT31_H__
#define __GROVE_SHT31_H__

#include "suli2.h"

//GROVE_NAME        "Grove - SLT - Single"
//SKU               1010123321631235123
//IF_TYPE           I2C
//IMAGE_URL         https://d3s5r33r268y59.cloudfront.net/4974/products/thumbs/2015-10-26T14:22:55.624Z-DSC01306.JPG.2560x2560_q85.jpg
//DESCRIPTION       "Driver for SLT de Tindie"
//WIKI_URL          http://www.rizoma.io
//ADDED_AT          "2017-05-05"
//AUTHOR            "Rodrigo Moya Toro - rodrigo@rizoma.io"

class GroveSLT
{
	public:
		GroveSLT(int pinsda, int pinscl);;    
		bool read_temperature(float *temperature);
		bool read_light(float *light);
		bool read_soil(float *soil);

	private:
    	I2C_T *i2c;

    uint8_t _i2caddr;
    float temperature, light, soil, reader;
};
#endif