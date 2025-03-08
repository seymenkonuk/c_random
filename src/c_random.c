#include "c_random.h"

// SEED DEĞERİNİ ALIR
// @return success: 1 Ocak 1970'den geçen mikro saniye
static uint64_t getSeed()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

// RASTGELE KÜÇÜK SAYI ÜRETİR
// Açıklama: max < RAND_MAX ise kullanılmalıdır! Aksi durumda hatalı çalışır.
// @param max: üretilmesi istenen sayının maksimum değeri (bu sayı dahil değil)
// @return success: 0 ile max arasında rastgele sayı
static uint64_t	generateRandShort(uint64_t max)
{
	uint64_t result;
	// Hesapla
	do
	{
		result = rand();
	} while (result > RAND_MAX - (RAND_MAX + 1) % max);
	// return 
	return result % max;
}

// SAYININ KAÇ BİT OLDUĞUNU HESAPLAR
// @param number: sayı
// @return success: 0 ile max arasında rastgele sayı
static uint8_t	getBitLength(uint64_t number)
{
	uint64_t result;
	//
	if (number == 0)
		return 1;
	//
	result = 0;	
	while (number > 0)
	{
		number = number >> 1;
		result++;
	}
	return result;
}

// RASTGELE BİT ÜRETİR
// @return success: 0 ya da 1 üretir
static uint64_t	generateRandBit()
{
	return generateRandShort(2);
}

// RASTGELE BİTLER ÜRETİR
// @param bitLength: üretilecek sayının bit uzunluğu
// @return success: bitLength adet bite sahip rastgele sayı
static uint64_t	generateRandBits(uint8_t bitLength)
{
	uint64_t result;
	result = 0;
	// Hesapla
	while (bitLength > 0)
	{
		result = (result << 1) + generateRandBit();
		bitLength--;
	}
	// return 
	return result;
}

// RASTGELE BÜYÜK SAYI ÜRETİR
// Açıklama: max değeri RAND_MAX dan büyük olduğunda bile çalışır
// @param max: üretilmesi istenen sayının maksimum değeri (bu sayı dahil değil)
// @return success: 0 ile max arasında rastgele sayı
static uint64_t	generateRandLong(uint64_t max)
{
	//
	uint64_t result;
	uint8_t bitLength;
	//
	bitLength = getBitLength(max);
	//
	do
	{
		result = generateRandBits(bitLength);
	} while (result >= max);
	//
	return result;
}

// RASTGELE SAYI ÜRETİR
// @param max: üretilmesi istenen sayının maksimum değeri (bu sayı dahil değil)
// @return success: 0 ile max arasında rastgele sayı
static uint64_t	generateRand(uint64_t max)
{
	// rand() fonksiyonu bu sayıyı üretebiliyorsa öyle üret
	if (max < RAND_MAX)
		return generateRandShort(max);
	// rand() fonksiyonu bu kadar büyük bir sayı üretemiyorsa, başka şekilde üret
	return generateRandLong(max);
}

// İKİ SAYI ARASINDA RASTGELE SAYI ÜRETİR
// @param min: üretilmesi istenen sayının minimum değeri (bu sayı dahil)
// @param max: üretilmesi istenen sayının maksimum değeri (bu sayı dahil değil)
// @return success: min ile max arasında rastgele sayı
int64_t	generateRandom(int64_t min, int64_t max)
{
	// Karıştırılmadıysa Karıştır
	if (!isUsedSrand)
		srand(getSeed());
	// Parameter Error
	if (min > max)
		return generateRandom(max, min);
	// 
	return min + (int64_t)generateRand(max - min);
}