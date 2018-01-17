#include <cstring>
#include <iostream>
#include <string>

#ifdef _WIN32
#include "WinTimer.h"
#else
#include "PosixTimer.h"
#endif

using std::cout;
using std::endl;
using std::string;

#define TEST_CASES 10
#define BENCH_ITERATIONS 10000
#define ASCII_TABLE_SIZE 256

// Kernel encoder function
extern string base64_stream_encode_plain_64bit(const char *src, size_t srclen);

// Wrapper encoder function
extern string base64_encode(const char *src, size_t srclen);

const char* dict = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_$";

string encode64_naive(const char* src, uint32_t length)
{
	char* resArr = new char[length * 2 + 1];

	uint32_t e = 0;
	uint8_t i = 0;
	uint32_t resIdx = 0;

	while (e < length)
	{
		uint8_t d;

		switch (i)
		{
			case 0: i = 1; d = ((src[e] >> 2) & 0x3f); break;
			case 1: i = 2; d = (((src[e] & 0x03) << 4) | ((e + 1 < length) ? ((src[e + 1] >> 4) & 0x0f) : 0)); ++e; break;
			case 2: i = 3; d = (((src[e] & 0x0f) << 2) | ((e + 1 < length) ? ((src[e + 1] >> 6) & 0x03) : 0)); ++e; break;
			case 3: i = 0; d = (src[e] & 0x3f); ++e; break;
		}

		char c = dict[d];

		switch (c)
		{
			case '0':	resArr[resIdx++] = '0'; resArr[resIdx++] = '0'; break;
			case '_':	resArr[resIdx++] = '0'; resArr[resIdx++] = '1'; break;
			case '$':	resArr[resIdx++] = '0'; resArr[resIdx++] = '2'; break;

			default:	resArr[resIdx++] = c; break;
		}
	}

	resArr[resIdx] = '\0';

	string result(resArr);

	delete[] resArr;

	return result;
}

string encode64_naive_dict2(const char* src, uint32_t length)
{
	const char dictExtra[ASCII_TABLE_SIZE] = {
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,	/* 0  .. 9  */
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,	/* 10 .. 19 */
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,	/* 20 .. 29 */
		0,  0,  0,  0,  0,  0, '2', 0,  0,  0,	/* 30 .. 39 */ // '$'(36)
		0,  0,  0,  0,  0,  0,  0,  0, '0', 0,	/* 40 .. 49 */ // '0'(48)
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,	/* 50 .. 59 */
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,	/* 60 .. 69 */
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,	/* 70 .. 79 */
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,	/* 80 .. 89 */
		0,  0,  0,  0,  0, '1', 0,  0,  0,  0,	/* 90 .. 99 */ // '_'(95)
	};

	char* resArr = new char[length * 2 + 1];

	uint32_t e = 0;
	uint8_t i = 0;
	uint32_t resIdx = 0;

	while (e < length)
	{
		uint8_t d;

		switch (i)
		{
			case 0: i = 1; d = ((src[e] >> 2) & 0x3f); break;
			case 1: i = 2; d = (((src[e] & 0x03) << 4) | ((e + 1 < length) ? ((src[e + 1] >> 4) & 0x0f) : 0)); ++e; break;
			case 2: i = 3; d = (((src[e] & 0x0f) << 2) | ((e + 1 < length) ? ((src[e + 1] >> 6) & 0x03) : 0)); ++e; break;
			case 3: i = 0; d = (src[e] & 0x3f); ++e; break;
		}

		char c = dict[d];
		resArr[resIdx] = c;

		char c2 = dictExtra[c];

		if (c2)
		{
			resArr[resIdx++] = '0';
			resArr[resIdx] = c2;
		}

		resIdx++;
	}

	resArr[resIdx] = '\0';

	string result(resArr);

	delete[] resArr;

	return result;
}

const char* test_strings[TEST_CASES] = {
	"",
	"abcDEF",
	"Hello world",
	"Encoding64 test",
	"// This is... CNN <!-- ",
	"-9223372036854775807LL - 1",
	"supercalifragilisticexpialidocious",
	"https://msdn.microsoft.com/en-us/library/mt764276.aspx",
	"I always wanted to be somebody, but now I realize I should have been more specific.",
	"@P=split//,\".URRUU\\c8R\";@d=split//,\"\nrekcah xinU / lreP rehtona tsuJ\";sub p{@p{\"r$p\",\"u$p\"}=(P,P);pipe\"r$p\",\"u$p\";++$p;($q*=2)+=$f=!fork;map{$P=$P[$f^ord($p{$_})&6];$p{$_}=/ ^$P/ix?$P:close$_}keys%p}p;p;p;p;p;map{$p{$_}=~/^[P.]/&&close$_}%p;wait until$?;map{/^r/&&<$_>}%p;$_=$d[$q];sleep rand(2)if/\\S/;print",
};

int test_strings_lengths[TEST_CASES];

const char* reference_encode64[TEST_CASES] = {
	"",
	"YWJjREVG",
	"SGVsbG8gd29ybGQ",
	"RW5jb2Rpbmc2NCB00ZXN00",
	"Ly8gVGhpcyBpcy4uLiBDTk4gPCEtLSA",
	"LTkyMjMzNzIwMzY4NTQ3NzU4MDdMTCAtIDE",
	"c3VwZXJjYWxpZnJhZ2lsaXN00aWNleHBpYWxpZG9jaW91cw",
	"aHR00cHM6Ly9tc2RuLm1pY3Jvc29mdC5jb200vZW4tdXMvbGlicmFyeS9tdDc2NDI3Ni5hc3B4",
	"SSBhbHdheXMgd2FudGVkIHRvIGJlIHNvbWVib2R5LCBidXQgbm93IEkgcmVhbGl6ZSBJIHNob3VsZCBoYXZlIGJlZW4gbW9yZSBzcGVjaWZpYy4",
	"QFA9c3BsaXQvLywiLlVSUlVVXGM4UiI7QGQ9c3BsaXQvLywiCnJla2NhaCB4aW5VIC8gbHJlUCByZWh00b25hIHRzdUoiO3N1YiBwe00BweyJyJHAiLCJ1JHAifT00oUCxQKTtwaXBlInIkcCIsInUkcCI7KyskcDsoJHEqPTIpKz00kZj00hZm9yazttYXB7JFA9JFBbJGZeb3JkKCRweyRffSkmNl007JHB7JF99PS8gXiRQL2l4PyRQOmNsb3NlJF99a2V5cyVwfXA7cDtwO3A7cDttYXB7JHB7JF99PX4vXltQLl00vJiZjbG9zZSRffSVwO3dhaXQgdW500aWwkPzttYXB7L15yLyYmPCRfPn00lcDskXz00kZFskcV007c2xlZXAgcmFuZCgyKWlmL1xTLztwcmludA",
};

void init_lengths()
{
	for (int i = 0; i < TEST_CASES; i++)
	{
		test_strings_lengths[i] = strlen(test_strings[i]);
	}
}

bool test_string_encode(const char* src, size_t srclen, const char* ref)
{
	string expected = string(ref);

	string encoded = encode64_naive(src, srclen);
	//string encoded = encode64_naive_dict2(src, srclen);
	//string encoded = base64_stream_encode_plain_64bit(src, srclen);
	//string encoded = base64_encode(src, srclen);

	if (encoded != expected)
	{
		cout << "Test failed! " << endl;
		cout << "Encoded  = " << encoded << endl;
		cout << "Expected = " << expected << endl;

		return false;
	}

	return true;
}

void benchmark_string_encode(const char* src, int len)
{
#ifdef WIN32
	WinTimer timer(1000.0); // ms
#else
	PosixTimer timer(1000.0); // ms
#endif

	for (int j = 0; j < BENCH_ITERATIONS; j++)
	{
		encode64_naive(src, len);
		//encode64_naive_dict2(src, len);
		//base64_stream_encode_plain_64bit(src, len);
		//base64_encode(src, len);
	}

	cout << timer.TimeElapsed() << "ms (" << BENCH_ITERATIONS << " iterations)" << endl;
}

int main()
{
	int failed = 0;

	init_lengths();

	for (int i = 0; i < TEST_CASES; i++)
	{
		cout << "Encoding test #" << i + 1 << "... " << endl;

		if (!test_string_encode(test_strings[i], strlen(test_strings[i]), reference_encode64[i]))
		{
			failed++;
		}

		benchmark_string_encode(test_strings[i], test_strings_lengths[i]);
	}

	cout << "[" << (TEST_CASES - failed) << "/" << TEST_CASES << "] passed." << endl;

	return 0;
}
