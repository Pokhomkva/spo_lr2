#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>


#define BUF_SIZE 256
TCHAR* szName=new TCHAR[20];;
TCHAR* szMsg = new TCHAR[20];

int _tmain()
{
   _tprintf(TEXT("Enter mapping name:"));
   std::cin >> szMsg;
   HANDLE hMapFile;
   LPCTSTR pBuf;

   hMapFile = OpenFileMapping(
                   FILE_MAP_ALL_ACCESS,
                   FALSE,
                   szName);
   if (GetLastError() == 2){
   	hMapFile = CreateFileMapping(
                 INVALID_HANDLE_VALUE,
                 NULL,
                 PAGE_READWRITE,
                 0,
                 BUF_SIZE,
                 szName);
   }


   if (hMapFile == NULL)
   {
      _tprintf(TEXT("Could not create file mapping object (%d).\n"),
             GetLastError());
      return 1;
   }
   pBuf = (LPTSTR) MapViewOfFile(hMapFile,
                        FILE_MAP_ALL_ACCESS,
                        0,
                        0,
                        BUF_SIZE);

   if (pBuf == NULL)
   {
      _tprintf(TEXT("Could not map view of file (%d).\n"),
             GetLastError());

       CloseHandle(hMapFile);

      return 1;
   }
   int i = 4;
   while (i > 0){

	   _tprintf(TEXT(" Enter 1 for writing \n Enter 2 for reading \n Enter 3 for exit \n"));

	   std::cin >> i;
	   if (i == 1){
	   	_tprintf(TEXT("Enter the message:"));

		std::cin >> szMsg;
	   	CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
	    _getch();
	   }
	   if (i == 2){
	   	_tprintf(pBuf);
	   	_tprintf("\n");
	   }
	   if (i == 3){
	    i = 0;
	   }
	}

   UnmapViewOfFile(pBuf);

   CloseHandle(hMapFile);

   return 0;
}
