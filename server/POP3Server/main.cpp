
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#include "server.h"




#define AUTOMAT_COUNT 3
#define MSGBOX_COUNT 3

extern dbAdapter dbHelper;

/* FSM system instance. */


DWORD WINAPI SystemThread(void *data) {
	
	printf("[*] Starting system...\n");
	//sys.Start();
	
	SrvAuto server;
	server.Initialize();


	/* Finish thread */
	return 0;
}

void main(int argc, char* argv[]) {
	
	DWORD thread_id;
	HANDLE thread_handle;
	
	/* Start operating thread. */
	thread_handle = CreateThread(NULL, 0, SystemThread, NULL, 0, &thread_id);

	/* Wait for end. */
	while (1) {}

	

	/* Notify the system to stop - this causes the thread to finish */
	printf("[*] Stopping system...\n");
	//sys.StopSystem();

	/* Free the thread handle */
	CloseHandle(thread_handle);


}