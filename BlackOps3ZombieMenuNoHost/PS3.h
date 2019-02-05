#include <sys/prx.h>
#include <cellstatus.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/ppu_thread.h>
#include <string.h>
#include <sys/sys_time.h>
#include <sys/time_util.h>
#include <assert.h>
#include <sys/process.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/return_code.h>
#include <stddef.h>
#include <math.h>
#include <stdarg.h>
#include <typeinfo>
#include <vector>
#include <pthread.h>
#include <locale.h>
#include <cell/error.h>
#include <sys/paths.h> 
#include <sys/fs.h> 
#include <sys/fs_external.h> 
#include <cell/cell_fs.h>
#include <ppu_intrinsics.h>
#include <cell/fs/cell_fs_file_api.h>
#include <sys/types.h>
#include <time.h>
//Basic Calls
int console_write(const char * s)
{ 
	uint32_t len;
	system_call_4(403, 0, (uint64_t) s, std::strlen(s), (uint64_t) &len);
	return_to_user_prog(int);
}
void sleep(usecond_t time)
{
	sys_timer_usleep(time * 1000);
}
char byteArray[100];
	char* ReadBytes(int address, int length)
	{
		for (int i = 0; i < length; i++)
		{
			byteArray[i] = *(char*)(address + (i));
		}
		return byteArray;
	}
	char returnRead[100];

	char* ReadString(int address)
	{
		memset(&returnRead[0], 0, sizeof(returnRead));
		int strlength = 100;
		char* StrBytes = ReadBytes(address, strlength);
		for (int i = 0; i < strlength; i++)
		{
			if (StrBytes[i] != 0x00)
				returnRead[i] = StrBytes[i];
			else
				break;
		}
		return returnRead;
	}
	
//Require For Hooking
//Credits To Thriefboy For Hooking/Write Process Func
int Memcpy(void* destination, const void* source, size_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);
	__dcbst(destination);
	__sync();
	__isync();
	return_to_user_prog(int);
}
void PatchInJump(int Address, int Destination, bool Linked) 
{
	// use this data to copy over the address
	int FuncBytes[4];

	// Get the actual destination address
	Destination = *(int *)Destination;

	FuncBytes[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF); // lis     %r11, dest>>16
	if (Destination & 0x8000) // If bit 16 is 1
		FuncBytes[0] += 1;

		FuncBytes[1] = 0x396B0000 + (Destination & 0xFFFF); // addi    %r11, %r11, dest&0xFFFF
		FuncBytes[2] = 0x7D6903A6; // mtctr    %r11

		FuncBytes[3] = 0x4E800420; // bctr

		if (Linked)
			FuncBytes[3] += 1; // bctrl

		Memcpy((void*)Address, FuncBytes, 4 * 4);
}