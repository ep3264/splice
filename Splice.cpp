/*
 * Splice.cpp
 *
 *  Created on: 9 ����. 2015 �.
 *      Author: user
 */

#include "Splice.h"

Splice::Splice() {
	 jmp_instr[0] = 0xE9;//0xE9- jmp
	// TODO Auto-generated constructor stub
}

Splice::~Splice() {
	// TODO Auto-generated destructor stub
}

 UINT Splice::CalcJump(UINT from, UINT to)
{
    return to-from-5;//0- (from-to)-5;
}
 ////
BYTE Splice::CalcLeng(PBYTE OriginAddr)
{
	BYTE totalLen=0;
	hde32s hs;
	// DISASM MyDisasm;
	 //MyDisasm.EIP = (UIntPtr)OriginAddr;
	 do {
		 totalLen+=  hde32_disasm(OriginAddr+totalLen,&hs);
		// totalLen+= Disasm(&MyDisasm);
		// MyDisasm.EIP = (UIntPtr)OriginAddr + (UIntPtr)totalLen;
	 }while(totalLen<5);
	 return totalLen;
}
///
void * Splice::SetBytes(BYTE * Func, BYTE * Hook)
{
	ULONG oldprotect;
	BYTE totalLen=CalcLeng(Func);
    void *Tramp=VirtualAlloc(0,totalLen+5,MEM_COMMIT | MEM_RESERVE ,PAGE_EXECUTE_READWRITE);
    *(UINT*)( jmp_instr+1)= CalcJump((UINT)Tramp+totalLen,(UINT) Func+totalLen);
    memcpy(Tramp, Func,totalLen);
	int temp = *((int*)(&Tramp));
    memcpy((void*)(temp+totalLen), jmp_instr,5);
    *(UINT*)( jmp_instr+1)= CalcJump((UINT)Func,(UINT) Hook);
	VirtualProtect(Func, totalLen, PAGE_EXECUTE_READWRITE, &oldprotect);
    memcpy(Func, jmp_instr,5);
  /*  if(delta){
    memset(Func+5,0x90,delta);
    }*/
	VirtualProtect(Func, totalLen, oldprotect, &oldprotect);
	return Tramp;
}
