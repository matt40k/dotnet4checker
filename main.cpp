#include <Windows.h>
#include <tchar.h>


const TCHAR *RegistryKeyName          = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v4\\Full");
const TCHAR *RegistryValueName    = _T("Install");

bool ReturnRegistryValue(HKEY, const TCHAR*, const TCHAR*, DWORD, LPBYTE, DWORD);
bool DotNetFourInstallCheck();

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{	
	if(DotNetFourInstallCheck() == true)
	{
		MessageBox(0,"The Microsoft .NET Framework 4.0 Full is not installed on this machine!!","WARNING",0);
	
		if( MessageBox( NULL,"Would you like to be directed to where you can download it?\n","Would you like to install...",MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			ShellExecute(NULL,TEXT("open"), TEXT("http://www.microsoft.com/downloads/en/details.aspx?familyid=0a391abd-25c1-4fc0-919f-b21f31ab88b7"), TEXT(""),NULL,SW_HIDE);
		}
	}
	else
	{
		MessageBox(0,"The Microsoft .NET Framework 4.0 Full is installed!","Success",0);
	}
}

bool DotNetFourInstallCheck() //Check for dotnet four
{
    bool Installed = false;
    DWORD Value=0;

	if (ReturnRegistryValue(HKEY_LOCAL_MACHINE, RegistryKeyName, RegistryValueName, NULL, (LPBYTE)&Value, sizeof(DWORD)))
	{
		if (Value == 1)
		{
			Installed = true;
		}
	}
	return Installed;
}

bool ReturnRegistryValue(HKEY hk, const TCHAR * pszKey, const TCHAR * pszValue, DWORD dwType, LPBYTE data, DWORD dwSize) //Checking value
{
    HKEY hkOpened;

    if (RegOpenKeyEx(hk, pszKey, 0, KEY_READ, &hkOpened) != ERROR_SUCCESS)
    {
        return false;
    }

    if (RegQueryValueEx(hkOpened, pszValue, 0, &dwType, (LPBYTE)data, &dwSize) != ERROR_SUCCESS)
    {
        RegCloseKey(hkOpened);
        return false;
    }

    RegCloseKey(hkOpened); //Close it up

    return true;
}