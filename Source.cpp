/******************************************************************************************
 * Graham's Algorithms.cpp : Defines the entry point for the console application.         *
 *																						  *
 * Author: Lea Middleton                                                                  *
 *																						  *
 * Date: 4.4.4018																		  *
 ******************************************************************************************/
 

#include "getFiles.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int main() {

	const char fileName1[] = "case1.txt";
	Files file1(fileName1);
	file1.openFile(file1.getFile());

	const char fileName2[] = "case2.txt";
	Files file2(fileName2);
	file2.openFile(file2.getFile());

	const char fileName3[] = "case3.txt";
	Files file3(fileName3);
	file3.openFile(file3.getFile());

	const char fileName4[] = "case4.txt";
	Files file4(fileName4);
	file4.openFile(file4.getFile());
	
	const char fileName5[] = "case5.txt";
	Files file5(fileName5);
	file5.openFile(file5.getFile());
	
	const char fileName6[] = "case6.txt";
	Files file6(fileName6);
	file6.openFile(file6.getFile());
	
	printf("Press any key to exit a press enter: ");
	getchar();
	return(EXIT_SUCCESS);
}

