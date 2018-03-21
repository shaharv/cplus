#include <cstdio>
#include <cstdint>
#include <climits>

// C++ Standard (ISO/IEC 14882:2003(E))
//
// 4.7 Integral conversions[conv.integral]
//
// 2. If the destination type is unsigned, the resulting value is the least
// unsigned integer congruent to the source integer (modulo 2n where n is the
// number of bits used to represent the unsigned type). [Note:In a two
// complement representation, this conversion is conceptual and there is no
// change in the bit pattern (if there is no truncation).]
//
// 3. If the destination type is signed, the value is unchanged if it can
// be represented in the destination type (and bit - field width); otherwise,
// the value is implementation - defined.

int main()
{
	int32_t val01_i32  = INT32_MAX;
	int64_t val01_i64  = static_cast<int64_t>(val01_i32);
	uint64_t val01_u64 = static_cast<uint64_t>(val01_i32);

	printf("Test cast #1\n");
	printf("val01_i32 = %d\n",   val01_i32);
	printf("val01_i64 = %lld\n", val01_i64);
	printf("val01_u64 = %llu\n", val01_u64);
	printf("\n");

	uint32_t val02_u32 = UINT32_MAX;
	int64_t val02_i64  = static_cast<int64_t>(val02_u32);
	uint64_t val02_u64 = static_cast<uint64_t>(val02_u32);

	printf("Test cast #2\n");
	printf("val02_u32 = %u\n", val02_u32);
	printf("val02_i64 = %lld\n", val02_i64);
	printf("val02_u64 = %llu\n", val02_u64);
	printf("\n");

	int64_t val03_i64 = 0xfeffffffffffffffll;
	int32_t val03_i32 = static_cast<int32_t>(val03_i64);

	printf("Test cast #3\n");
	printf("val03_i64 = %lld\n", val03_i64);
	printf("val03_i64 = 0x%llx\n", val03_i64);
	printf("val03_i32 = %d\n", val03_i32);
	printf("val03_i32 = 0x%x\n", val03_i32);

	return 0;
}
