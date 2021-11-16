#include "FileManager.h"
#include <cstdio>
#include <stdlib.h>
#include <iostream>

#pragma warning(disable:4996)


//Is not used
 bool FileManager::DecodeBase64FileToFile(const char* inputFileName, const char* outputFileName) {

	 FILE* inputFile = fopen(inputFileName, "rt");

	 FILE* outputFile = fopen(outputFileName, "wb");

	 if (!inputFile || !outputFile) return false;

	 char buffer[5];


	 while (fgets(buffer, 5, inputFile)) {

		 DecodeAndWriteBase64Quartet(buffer, outputFile);
	 }


	 return true;
 }

 void FileManager::DecodeAndWriteBase64Quartet(char* buffer , FILE* fileToWrite) {

	 
		 int padding= 0; 

		 int first = strchr(base64Table, buffer[0]) - base64Table;

		 int second = strchr(base64Table, buffer[1]) - base64Table;

		 int third = strchr(base64Table, buffer[2]) - base64Table;

		 int fourth = strchr(base64Table, buffer[3]) - base64Table;

		 if (first == 64) padding++;
		 if (second == 64) padding++;
		 if (third == 64) padding++;
		 if (fourth == 64) padding++;



		 int chr1 = (first << 2) | (second >> 4);

		 int chr2 = ((second & 15) << 4) | (third >> 2);

		 int chr3 = ((third & 3) << 6) | fourth;

		 if (padding == 2) {
			 fputc(chr1, fileToWrite);
		 }
		 else if (padding == 1) {
			 fputc(chr1, fileToWrite);
			 fputc(chr2, fileToWrite);
		 }
		 else {
			 fputc(chr1, fileToWrite);
			 fputc(chr2, fileToWrite);
			 fputc(chr3, fileToWrite);
		 }
 }

 

 bool FileManager::OpenAndParseMime(const char* path) {

	 FILE* mimeFile = fopen(path, "rt");


	 if (!mimeFile) return false;


	 char line[80];

	 bool reachContent = false;
	 bool reachBase64 = false;

	 char buf[4];

	 char fileName[150];

	 FILE* outputFile = NULL;

	 int fileCount = 0;

	 while(fgets(line,80,mimeFile)){

		 if (reachBase64) {

			 if (line[0] == '\n') {
				 reachContent = false;
				 reachBase64 = false;
				 fclose(outputFile);
				 outputFile = NULL;
				 continue;
			 }
			
			 int i = 0;
			 int t = 0;
			 while (line[t] != '\n' && line[t] !=0) {
				 buf[i++] = line[t++];
				 buf[i++] = line[t++];
				 buf[i++] = line[t++];
				 buf[i++] = line[t++];
				 i = 0;

				 DecodeAndWriteBase64Quartet(buf, outputFile);

			 }
			
		 }

		 if (reachContent && line[0] == '\n') {
			 if (!outputFile) {
				 parsedFiles.pop_back();
				 reachContent = false;
				 continue;
			 }
			 else {
				 reachBase64 = true;
			 }

		 }

		 if (strstr(line, "Content-Transfer-Encoding: base64")) {
			 reachContent = true;
		 }
		 if (reachContent && strstr(line, "filename")) {
			 if (sscanf(line, "%*[^\"]\"%31[^\"]\"", fileName) == 1) {

				 outputFile = CreateOutputFile(fileName);
				
			 }

		 }
	 }
	
	fclose(mimeFile);

	return true;
 }



 FILE* FileManager::CreateOutputFile(char* filename) {
	 char path[155] = { '.','\\' };
	 int i = 0;
	 while (filename[i] != 0) {
		 path[2 + i] = filename[i];
		 i++;
	 }
	 path[2 + i] = '\0';

	parsedFiles.push_back({ path });

	return fopen(path, "wb");
 }