// libbloom.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once
#include <iostream>
#include "murmurhash2.h"


// TODO: 在此处引用程序需要的其他标头。
class Bloom {
public:
	int entries;
	double error;
	int bits;
	int bytes;
	int hashes;

	Bloom(int entries, double error);
	int add(const void *buffer, int len);
	int check(const void *buffer, int len);
	void print();
	void clear();
	int reset();
	const char* version();

private:
	double dpe;
	unsigned char* buf;
	int ready;

	inline int set_bit_set_bit(unsigned char* buf, unsigned int x, int set_bit);
	int check_add(const void *buffer, int len, int add);
};
