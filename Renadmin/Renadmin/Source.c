#include <Windows.h>
#include <tchar.h>
#include <LM.h>

#pragma comment(lib, "Netapi32.lib")

VOID ShowError(DWORD errCode)
{
	DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS;

	DWORD langId = LANG_USER_DEFAULT;
	LPWSTR errMsg;

	if (FormatMessageW(flags, NULL, errCode, langId, (LPWSTR)&errMsg, 0, NULL) == 0)
	{
		wprintf(L"Error code: %lu\n", GetLastError());

	}

	wprintf(L"\n%s\n", errMsg);

	LocalFree(errMsg);

}

int wmain(int argc, WCHAR *argv[])
{
	//NetUserSetInfo
	NET_API_STATUS netUserSet;
	LPWSTR userName = L"Administrador";
	DWORD level = 0;	//USER_INFO_0 structure
	USER_INFO_0 usrInfo0;
	DWORD parm_err;

	//GetUserDefaultLocaleName
	WCHAR pLocaleName[LOCALE_NAME_MAX_LENGTH];
	int sizeOfLocale = LOCALE_NAME_MAX_LENGTH;

	if (argc == 1)
	{
		fwprintf(stderr, L"\nUsage: %s NewAdminName\n", argv[0]);
		exit(1);
	}

	usrInfo0.usri0_name = argv[1];

	if (GetUserDefaultLocaleName(pLocaleName, sizeOfLocale) != 0)
	{
		if (_wcsicmp(pLocaleName, L"es-ES") == 0 ||
			_wcsicmp(pLocaleName, L"es-CO") == 0 ||
			_wcsicmp(pLocaleName, L"es-EC") == 0 ||
			_wcsicmp(pLocaleName, L"es-VE") == 0)			
		{
			wprintf(L"\nCurrent Language ID= %s", pLocaleName);

			netUserSet = NetUserSetInfo(NULL, userName, level, (LPBYTE)&usrInfo0, &parm_err);

			if (netUserSet != NERR_Success)
			{
				ShowError(netUserSet);
			}
			else
			{
				wprintf(L"\nBuilt-in admin account name has been change to %s\n", argv[1]);
			}

		}		
	}
	else
	{
		ShowError(GetLastError());

	}
	

	return 0;
}