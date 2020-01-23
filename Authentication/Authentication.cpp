#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include <io.h>
#include <sstream>
#include <ostream>
#include <wininet.h>
#include <cstring>
#include <string>
#pragma comment(lib, "wininet")

using namespace std;

#pragma region Misc
std::string replaceAll(std::string subject, const std::string& search,
	const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}
std::string DownloadURL(const char* URL)
{
	HINTERNET interwebs = InternetOpenA("Mozilla/5.0", INTERNET_CONNECTION_PROXY, NULL, NULL, NULL);
	HINTERNET urlFile;
	std::string rtn;
	if (interwebs) {
		urlFile = InternetOpenUrlA(interwebs, URL, NULL, NULL, NULL, NULL);
		if (urlFile) {
			char buffer[2000];
			DWORD bytesRead;
			do {
				InternetReadFile(urlFile, buffer, 2000, &bytesRead);
				rtn.append(buffer, bytesRead);
				memset(buffer, 0, 2000);
			} while (bytesRead);
			InternetCloseHandle(interwebs);
			InternetCloseHandle(urlFile);
			std::string p = replaceAll(rtn, "|n", "\r\n");
			return p;
		}
	}
	InternetCloseHandle(0);
	std::string p = replaceAll(rtn, "|n", "\r\n");
	return p;
}

#pragma endregion

void auth()
{
	DWORD dwVolumeSerialNumber;
	std::string url = (std::string)"https://pastebin.com/raw/5itfWvfM"; // Your text files over here.
	GetVolumeInformation(L"C:\\", NULL, 0, &dwVolumeSerialNumber, NULL, NULL, NULL, 0);
	std::string HDDserial = std::to_string(dwVolumeSerialNumber);
	std::string HTTPResponse = DownloadURL(url.c_str());
	std::size_t found = HTTPResponse.find(HDDserial);
	if (found != std::string::npos)
	{
		cout << "Auth Sucessfully!" << endl;
	}
	else
	{
		cout << "Auth Failed!" << endl;
		cout << HDDserial << endl;
	}
}

int main()
{
	cout << "Verify the thingy" << endl;
	auth();
	system("pause");//execuse me? your can learn this by using commands prompt
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu