
#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif // !_USE_MATH_DEFINES

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <functional>


#ifndef uint
typedef unsigned int uint;
#endif

#ifndef byte
typedef unsigned char byte;
#endif



enum  BooleanCode :unsigned char
{
	PART0_OUT = 0,//part0 ��part1����Ĳ�����Ƭ��Ҳ��part0�ĳ�ʼֵ��
	PART1_OUT = 1,//part1 ��part0����Ĳ�����Ƭ��Ҳ��part1�ĳ�ʼֵ��
	PART0_IN = 2, //part0 ��part1����Ĳ�����Ƭ
	PART1_IN = 3, //part1 ��part0����Ĳ�����Ƭ

	PART_SHELL_OUT = 4,//��ʱ����part0������Ĳ�����Ƭ��ͬ0����Ϊpart0�ĳ�ֵ��
	PART_SHELL_IN = 6,//��ʱ����part1������Ĳ�����Ƭ��ͬ2��

	PART0_COPLANAR = 8,//part0����
	PART1_COPLANAR = 9,//part1���棬�ҷ����part0һ��
	PART1_RECOPLANAR = 7,//part1���棬�������part0��һ��
	BADTRI = 10 //�������Σ���Ҫɾ��
};


struct BoolData {
	byte bool_alg_data;
};

struct Tri {
	BoolData data;
	bool    isDegenerate;
	union {
		struct {
			int  origa, origb, origc;
		};
		int oriv[3];
	};
	union {
		struct {
			uint a, b, c; // vertex ids
		};
		uint v[3];
	};
	uint ref;
	Tri() { isDegenerate = false; }
	bool oriEqual(const Tri& _rhs)
	{
		if (origa == _rhs.origa && origb == _rhs.origb && origc == _rhs.origc) return true;
		if (origa == _rhs.origa && origb == _rhs.origc && origc == _rhs.origb) return true;
		if (origa == _rhs.origb && origb == _rhs.origa && origc == _rhs.origc) return true;
		if (origa == _rhs.origb && origb == _rhs.origc && origc == _rhs.origa) return true;
		if (origa == _rhs.origc && origb == _rhs.origa && origc == _rhs.origb) return true;
		if (origa == _rhs.origc && origb == _rhs.origb && origc == _rhs.origa) return true;
		return false;
	}
};

// snap the value a into the specified range
inline double clamp(double a, double mina, double maxa) {
    return std::min(maxa, std::max(mina, a));
}
inline float  clamp(float  a, float  mina, float  maxa) {
    return std::min(maxa, std::max(mina, a));
}

// modulo the value a into the specified range
inline double wrap(double a, double mina, double maxa) {
    double val = std::fmod(a - mina, maxa - mina);
    if(val < 0.0) val += maxa-mina;
    return val + mina;
}
inline float  wrap(float  a, float  mina, float  maxa) {
    float val = std::fmod(a - mina, maxa - mina);
    if(val < 0.0) val += maxa-mina;
    return val + mina;
}


inline void initRand() {
    // currently none!  Should seed using clock
    srand(uint(time(0)));
}

inline double drand(double min, double max) {
    const double invMAX = 1.0/double(RAND_MAX);
    double rand0to1 = double(std::rand())*invMAX;
    return (max-min)*rand0to1 + min;
}

inline uint randMod(uint range) {
    return std::rand()%range;
}



