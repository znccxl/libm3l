/*
 *     Copyright (C) 2012  Adam Jirasek
 * 
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU Lesser General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 * 
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU Lesser General Public License for more details.
 * 
 *     You should have received a copy of the GNU Lesser General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *     
 *     contact: libm3l@gmail.com
 * 
 */

/*
 * the pack754 and unpack754 functions are transcript of Brian Hall code from the Beej's Guide to Network Programming
 * http://beej.us/guide/bgnet/output/html/multipage/advanced.html, Contact beej@beej.us for more information.
 */

/*
 *     Function NumberConversion.c
 *
 *     Date: 2012-07-19
 * 
 * 
 *     Description:
 * 
 *
 *     Input parameters:
 * 
 *
 *     Return value:
 * 
 * 
 *
 *     Modifications:
 *     Date		Version		Patch number		CLA 
 *
 *
 *     Description
 * 
 */



#include "Header.h"
#include "NumberConversion.h"


// uint64_t pack754(long double f, unsigned bits, unsigned expbits)
// {
// 	long double fnorm;
// 	int shift;
// 	long long sign, exp, significand;
// 	unsigned significandbits = bits - expbits - 1; // mantisa = total - exponent -1 for sign

Uint64_t pack754(lmlongdouble_t f, unsigned bits, unsigned expbits)
{
	long double fnorm;
	lmint_t shift;
	lmllint_t sign, exp, significand;
	unsigned significandbits = bits - expbits - 1; // mantisa = total - exponent -1 for sign
/*
 * if number is zero return 0
 */
	if (f == 0.0) return 0;
/*
 * check sign and begin normalization
 */
	if (f < 0) { 
		sign = 1; fnorm = -f; 
	}
	else { 
		sign = 0; fnorm = f; 
	}
/*
 * get the normalized form of f and track the exponent
 */
	shift = 0;
	while(fnorm >= 2.0) { fnorm /= 2.0; shift++; }
	while(fnorm < 1.0)  { fnorm *= 2.0; shift--; }
	fnorm = fnorm - 1.0;
/*
 * calculate the binary form (non-float) of the significand data
 */
	significand = fnorm * ((1LL<<significandbits) + 0.5f);
/*
 * get the biased exponent
 */
	exp = shift + ((1<<(expbits-1)) - 1); // shift + bias
/*
 * return the final answer
 */
	return (sign<<(bits-1)) | (exp<<(bits-expbits-1)) | significand;
}

// long double unpack754(uint64_t i, unsigned bits, unsigned expbits)
// {
// 	long double result;
// 	long long shift;
// 	unsigned bias;
// 	unsigned significandbits = bits - expbits - 1; // mantisa = total - exponent -1 for sign
lmlongdouble_t unpack754(Uint64_t i, unsigned bits, unsigned expbits)
{
	lmlongdouble_t result;
	lmllint_t shift;
	unsigned bias;
	unsigned significandbits = bits - expbits - 1; // mantisa = total - exponent -1 for sign
/*
 * if number is zero return 0
 */
	if (i == 0) return 0.0;
/*
 * pull the significand
 *	mask
 *	convert back to float
 *	add the one back on
 */
	result = (i&((1LL<<significandbits)-1));
	result /= (1LL<<significandbits);
	result += 1.0f;
/*
 * deal with the exponent
 */
	bias = (1<<(expbits-1)) - 1;
	shift = ((i>>significandbits)&((1LL<<expbits)-1)) - bias;
	while(shift > 0) { result *= 2.0; shift--; }
	while(shift < 0) { result /= 2.0; shift++; }
/*
 * sign it
 */
	result *= (i>>(bits-1))&1? -1.0: 1.0;
	
	return result;
}

/*
 * converts double to HEX
 */
char * double_2_Hex(double a)
{
//    char *buf = new char[17]; // double is 8-byte long, so we have 2*8 + terminating \0

	char buf[17];
	char *d2c;
	char *n = buf;
	int i;

	d2c = (char *) &a;
	
	for(i = 0; i < 8; i++){
		sprintf(n, "%02X", *d2c++);
		n += 2;
	} 
	*(n) = '\0';
	
	return n;
}
