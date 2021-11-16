// LAB5_Zerebkovs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include "FileManager.h"



#pragma warning(disable:4996)

int main()
{

	FileManager manager;
	

	bool isParsingSuccessful=manager.OpenAndParseMime("Email.3.eml");

	if (isParsingSuccessful) {
		
			for (int i = 0; i < manager.parsedFiles.size(); i++) {

				std::wstring stemp = std::wstring(manager.parsedFiles.at(i).path.begin(), manager.parsedFiles.at(i).path.end());
				LPCWSTR path= stemp.c_str();

				ShellExecute(0, 0, path, 0, 0, SW_SHOW);
			}
	}
}

