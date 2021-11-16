#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#pragma once

using namespace std;

struct OutputFile 
{

	string path;
	
};

class FileManager
{
private:

	 char base64Table[65] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/','=' };

	 void DecodeAndWriteBase64Quartet(char* buffer, FILE* fileToWrite);

	 FILE* CreateOutputFile(char* fileName);
public:
	 vector<OutputFile> parsedFiles;

	 bool DecodeBase64FileToFile(const char* inputFileName, const char* outputFileName);

	 bool OpenAndParseMime(const char* path);
};

