/*
 * Splice.h
 *
 *  Created on: 9 ����. 2015 �.
 *      Author: user
 */
#include "windows.h"
#include "HDE/hde32.h"
//#include "BeaEngine.h"
#ifndef SPLICE_H_
#define SPLICE_H_

class Splice {
public:
	Splice();
	virtual ~Splice();
	void * SetBytes(BYTE * Func, BYTE * Hook);
private:
	BYTE  jmp_instr[5];
	UINT CalcJump(UINT from, UINT to);
	BYTE CalcLeng(PBYTE OriginAddr);
};

#endif /* SPLICE_H_ */
