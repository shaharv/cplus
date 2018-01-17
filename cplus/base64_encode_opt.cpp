// Simplified and flattened version of generic 64-bit base64 encoder from
// Fast Base64 stream encoder/decoder library:
// https://github.com/aklomp/base64
//
// aklomp/base64 is licensed under the BSD 2-clause "Simplified" License.

/*
Copyright (c) 2005-2007, Nick Galbreath
Copyright (c) 2013-2017, Alfred Klomp
Copyright (c) 2015-2017, Wojciech Mula
Copyright (c) 2016-2017, Matthieu Darbois
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

- Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <cstdint>
#include <cstdlib>
#include <string>

// Define machine endianness. This is for GCC:
#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
	#define BASE64_LITTLE_ENDIAN 1
#else
	#define BASE64_LITTLE_ENDIAN 0
#endif

// This is for Clang:
#ifdef __LITTLE_ENDIAN__
	#define BASE64_LITTLE_ENDIAN 1
#endif

#ifdef __BIG_ENDIAN__
	#define BASE64_LITTLE_ENDIAN 0
#endif

// Endian conversion functions:
#if BASE64_LITTLE_ENDIAN
	#if defined(_MSC_VER)
		// Microsoft Visual C++:
		#define cpu_to_be32(x)	_byteswap_ulong(x)
		#define cpu_to_be64(x)	_byteswap_uint64(x)
		#define be32_to_cpu(x)	_byteswap_ulong(x)
		#define be64_to_cpu(x)	_byteswap_uint64(x)
	#else
		// GCC and Clang:
		#define cpu_to_be32(x)	__builtin_bswap32(x)
		#define cpu_to_be64(x)	__builtin_bswap64(x)
		#define be32_to_cpu(x)	__builtin_bswap32(x)
		#define be64_to_cpu(x)	__builtin_bswap64(x)
	#endif
#else
	// No conversion needed:
	#define cpu_to_be32(x)	(x)
	#define cpu_to_be64(x)	(x)
	#define be32_to_cpu(x)	(x)
	#define be64_to_cpu(x)	(x)
#endif 

using std::string;

string base64_encode(const char *src, size_t srclen);
string base64_encoded_customize(string encoded);
string base64_stream_encode_plain_64bit(const char *src, size_t srclen);

const uint8_t base64_table_enc[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_$";

string base64_encode(const char *src, size_t srclen)
{
	string encoded = base64_stream_encode_plain_64bit(src, srclen);

	return base64_encoded_customize(encoded);
}

string base64_encoded_customize(string encoded)
{
	const char* encArr = encoded.c_str();
	size_t outl = encoded.length();

	char* outFinal = new char[outl * 2 + 1];
	int outIdx = 0;

	for (uint32_t i = 0; i < outl; i++)
	{
		char c = encArr[i];

		switch (c)
		{
			case '0':	outFinal[outIdx++] = '0'; outFinal[outIdx++] = '0'; break;
			case '_':	outFinal[outIdx++] = '0'; outFinal[outIdx++] = '1'; break;
			case '$':	outFinal[outIdx++] = '0'; outFinal[outIdx++] = '2'; break;

			default:	outFinal[outIdx++] = c; break;
		}
	}

	outFinal[outIdx++] = '\0';

	string result((char*)outFinal);

	delete[] outFinal;

	return result;
}

string base64_stream_encode_plain_64bit(const char *src, size_t srclen)
{
	if (srclen == 0)
	{
		return "";
	}

	char* out = new char[srclen * 2 + 1];

	// Assume that *out is large enough to contain the output.
	// Theoretically it should be 4/3 the length of src.
	const uint8_t *c = (const uint8_t *)src;
	uint8_t *o = (uint8_t *)out;

	// Use local temporaries to avoid cache thrashing:
	size_t outl = 0;
	int bytes = 0;
	unsigned char carry = 0;

	// Turn three bytes into four 6-bit numbers:
	// in[0] = 00111111
	// in[1] = 00112222
	// in[2] = 00222233
	// in[3] = 00333333

	// Duff's device, a for() loop inside a switch() statement. Legal!
	switch (bytes)
	{
		for (;;)
		{
		case 0:
			// If we have 64-bit ints, pick off 6 bytes at a time for as long as we can,
			// but ensure that there are at least 8 bytes available to avoid segfaulting:
			while (srclen >= 8)
			{
				// Load string:
				uint64_t str = *(uint64_t *)c;

				// Reorder to 64-bit big-endian, if not already in that format. The
				// workset must be in big-endian, otherwise the shifted bits do not
				// carry over properly among adjacent bytes:
				str = cpu_to_be64(str);

				// Shift input by 6 bytes each round and mask in only the lower 6 bits;
				// look up the character in the Base64 encoding table and write it to
				// the output location:
				*o++ = base64_table_enc[(str >> 58) & 0x3F];
				*o++ = base64_table_enc[(str >> 52) & 0x3F];
				*o++ = base64_table_enc[(str >> 46) & 0x3F];
				*o++ = base64_table_enc[(str >> 40) & 0x3F];
				*o++ = base64_table_enc[(str >> 34) & 0x3F];
				*o++ = base64_table_enc[(str >> 28) & 0x3F];
				*o++ = base64_table_enc[(str >> 22) & 0x3F];
				*o++ = base64_table_enc[(str >> 16) & 0x3F];

				c += 6;		// 6 bytes of input
				outl += 8;	// 8 bytes of output
				srclen -= 6;
			}

			if (srclen-- == 0) {
				break;
			}
			*o++ = base64_table_enc[*c >> 2];
			carry = (*c++ << 4) & 0x30;
			bytes++;
			outl += 1;

		case 1:
			if (srclen-- == 0) {
				break;
			}
			*o++ = base64_table_enc[carry | (*c >> 4)];
			carry = (*c++ << 2) & 0x3C;
			bytes++;
			outl += 1;

		case 2:
			if (srclen-- == 0) {
				break;
			}
			*o++ = base64_table_enc[carry | (*c >> 6)];
			*o++ = base64_table_enc[*c++ & 0x3F];
			bytes = 0;
			outl += 2;
		}
	}

	if (bytes)
	{
		*o++ = base64_table_enc[carry];
		outl += 1;
	}

	*o = '\0';

	string result((char*)out);

	delete[] out;

	return result;
}
