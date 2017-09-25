#include <Windows.h>
#include <tchar.h>
#include <LM.h>

#pragma comment(lib, "Netapi32.lib")

int wmain(int argc, WCHAR *argv[])
{
	//NetUserSetInfo
	DWORD level = 0;	//USER_INFO_0 structure
	USER_INFO_0 usrInfo0 = {L"Administrator"};
	DWORD parm_err;

	//GetUserDefaultLocaleName
	WCHAR pLocaleName[LOCALE_NAME_MAX_LENGTH];
	int sizeOfLocale = LOCALE_NAME_MAX_LENGTH;

	if (GetUserDefaultLocaleName(pLocaleName, sizeOfLocale) != 0)
	{
		if (_wcsicmp(pLocaleName, L"es-ES") == 0 ||
			_wcsicmp(pLocaleName, L"es-CO") == 0)
		{
			wprintf(L"%s", pLocaleName);

			if (NetUserSetInfo(NULL, L"Administrador", level, (LPBYTE)&usrInfo0, &parm_err) != NERR_Success)
			{
				wprintf(L"Error code: %lu\n", GetLastError());
			}
			else
			{
				wprintf(L"\nBuilt-in admin account name has been change to Administrator\n");
			}

		}
		
		
	}
	else
	{
		wprintf(L"\nError code: %lu\n", GetLastError());

	}
	

	return 0;
}