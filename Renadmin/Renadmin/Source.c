#include <Windows.h>
#include <tchar.h>
#include <LM.h>

#pragma comment(lib, "Netapi32.lib")



int wmain(int argc, WCHAR *argv[])
{
	//NetUserSetInfo
	DWORD level = 0;	//USER_INFO_0 structure
	USER_INFO_0 usrInfo0;
	DWORD parm_err;

	//GetSystemDefaultLocaleName
	WCHAR pLocaleName[LOCALE_NAME_MAX_LENGTH];
	int sizeOfLocale = LOCALE_NAME_MAX_LENGTH;

	if (GetSystemDefaultLocaleName(pLocaleName, sizeOfLocale) != 0)
	{
		wprintf(L"\nCurrent Locale: %s\n", pLocaleName);
	}
	else
	{
		wprintf(L"\nError code: %lu\n", GetLastError());

	}

	getchar();

	return 0;
}