#include <sys/sys_time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/timer.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netex/net.h>
#include <netex/errno.h>
#include <string.h>
#pragma region Declarations
#include <sys/ppu_thread.h>
#include <string.h>
#include <sys/sys_time.h>
#include <sys/time_util.h>
#include <stdarg.h>
#include <assert.h>
#include <sys/process.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/return_code.h>
#include <sys/prx.h>
#include <stddef.h>
#include <math.h>
#include <stdarg.h>
#include <cellstatus.h>
#include <typeinfo>
#include <vector>
#include <pthread.h>
#include <locale.h>
#include <cell/error.h>
#include <sys/paths.h>
#include <time.h>
#include <net\if_dl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cell/cell_fs.h>
#include <cell/sysmodule.h>
#include <stdio.h>
#include <string.h>
#include <cell/fs/cell_fs_errno.h>
#include <cell/fs/cell_fs_file_api.h>
#include <ppu_intrinsics.h>
#include <cstdlib>
#include "Dialog.h"
#pragma comment(lib, "net_stub")
#pragma comment(lib, "netctl_stub")

#define SERVER_PORT htons(80)

int Socket;
struct hostent *Host;
struct sockaddr_in SocketAddress;
char bufferReturn[10000];
char RequestBuffer[2000];

char *HookName;

int WriteinConsole(const char * s)
{
	uint32_t len;
	system_call_4(403, 0, (uint64_t)s, std::strlen(s), (uint64_t)&len);
	return_to_user_prog(int);
}

void SleepMM(usecond_t time)
{
	sys_timer_usleep(time * 1000);
}

char* SocketRequest(char* URL, char* Key, char* Path = "")
{
	Host = gethostbyname(URL);
	SocketAddress.sin_addr.s_addr = *((unsigned long*)Host->h_addr);
	SocketAddress.sin_family = AF_INET;
	SocketAddress.sin_port = SERVER_PORT;
	Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(Socket, (struct sockaddr *)&SocketAddress, sizeof(SocketAddress)) != 0) {
		return "CONNECTION ERROR";
	}
	strcpy(RequestBuffer, "GET /");
	if (strlen(Path) > 0){
		strcat(RequestBuffer, Path);
	}
	strcat(RequestBuffer, Key);
	strcat(RequestBuffer, " HTTP/1.0\r\nHOST: ");
	strcat(RequestBuffer, URL);
	strcat(RequestBuffer, "\r\n\r\n");

	send(Socket, RequestBuffer, strlen(RequestBuffer), 0);

	while (recv(Socket, bufferReturn, 10000, 0) > 0)
	{
		return bufferReturn;
		SleepMM(1);
	}
	socketclose(Socket);
}

void WriteByte(int Address, unsigned char Input)
{
	*(unsigned char*)Address = Input;
}

void encryptDecrypt(char *input, char *output) {
	char key[] = { 'K', 'C', 'Q' }; //Can be any chars, and any size array


	for (int i = 0; i < strlen(input); i++) {
		output[i] = input[i] ^ key[i % (sizeof(key) / sizeof(char))];
	}
}

bool IsRequest(char* Key)
{

	char* check = SocketRequest("http://boost4ever.livehost.fr/Server/api.php?username=MrNiato", Key);
	char* s = strstr(check, "wrongpassword");
	if (s != NULL)
	{
		
		return true;
	}
	else
	{
		return false;
	}
}

int ExitThisShit()
{
	system_call_1(41, 0);
	return_to_user_prog(int);
}
char* Key; // Key Amount . Change it if you need 
char* GetKey()
{
	int fd;
	int ret;
	uint64_t pos;
	uint64_t nread;

	cellMsgDialogProgressBarInc(0, 1);
	cellMsgDialogProgressBarSetMsg(0, "Loading Key...");
	ret = cellFsOpen("/dev_hdd0/tmp/key.txt", 0, &fd, NULL, 0);
	if (!ret)
	{
		cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
		ret = cellFsRead(fd, Key, sizeof(ret), &nread);
		if (!ret)
		{
			Dialog::msgdialog_mode = 2;
			Dialog::Show("Key good");
			cellFsClose(fd);
		}
		else
		{
			cellMsgDialogClose(5.0);
			SleepMM(500);
			Dialog::msgdialog_mode = 2;
			Dialog::Show("Key failed to Read!");
			ExitThisShit();
		}
	}
	else
	{
		cellMsgDialogClose(5.0);
		SleepMM(500);
		Dialog::msgdialog_mode = 2;
		Dialog::Show("Key failed to load!");
		ExitThisShit();
	}
	return;
}