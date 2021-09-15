// libbloom.cpp: 定义应用程序的入口点。
//

#include <cmath>
#include <cstdlib>
#include "../include/libbloom.h"
#include "../include/murmurhash2.h"

using namespace std;


/*
* 
*/
Bloom::Bloom(int entries, double error) {
	ready = Bloom::entries = bits = bytes = hashes = 0;
	Bloom::error = dpe = 0;
	buf = nullptr;

	if (entries < 1000 || error <= 0) {
	
		return;
	}

	Bloom::entries = entries;
	Bloom::error = error;

	double ln2 = 0.693147180559945;
	double ln22 = 0.480453013918201;

	dpe = -(log(error) / ln22);

	bits = int(dpe * entries);
	if (bits % 8) {
		bytes = bits / 8 + 1;
	}
	else {
		bytes = bits / 8;
	}

	hashes = (int)(ceil(ln2 * dpe));
	buf = (unsigned char*)calloc(bits, sizeof(unsigned char));
	if (buf == nullptr) {
		return;
	}

	ready = 1;
}

int Bloom::add(const void* buffer, int len)
{
	return check_add(buffer, len, 1);
}

int Bloom::check(const void* buffer, int len)
{
	return check_add(buffer, len, 0);
}

void Bloom::print(){
	cout << "entries is :" << entries << endl;
	cout << "error   is :" << error   << endl;
	cout << "bits    is :" << bits    << endl;
	cout << "bytes   is :" << bytes   << endl;
	cout << "hashes  is :" << hashes  << endl;

	cout << "dpe     is :" << dpe     << endl;
	cout << "ready   is :" << ready   << endl;
}

void Bloom::clear(){
	if (ready) {
		free(buf);
	}

	ready = 0;
}

int Bloom::reset(){
	if (!ready) return 1;
	memset(buf, 0, bits);
	return 0;
}


inline int Bloom::set_bit_set_bit(unsigned char* buf, unsigned int x, int set_bit)
{
	unsigned int byte = x >> 3;
	unsigned char c = buf[byte];
	unsigned int mask = 1 << (x % 8);

	if (c & mask) {
		return 0;
	}
	else{
		if (set_bit) {
			buf[byte] = c | mask;
		}

		return 0;
	}
}

int Bloom::check_add(const void *buffer, int len, int add)
{
	if (ready == 0) {
		return -1;
	}
	int hits = 0;
	register unsigned int a = MurmurHash2(buffer, len, 0x9747b28c);
	register unsigned int b = MurmurHash2(buffer, len, a);
	register unsigned int x;
	register unsigned int i;
	for (i = 0; i < hashes; i++)
	{
		x = (a + b * i) % bits;
		if (set_bit_set_bit(buf, x, add)) {
			hits++;
		}
		else if (!add) {
			return 0;
		}
	}

	if (hits == hashes) {
		return 1;
	}

	return 0;
}