

#define _CRT_SECURE_NO_WARNINGS
#include "BooksCollection.h" 
#include "Menu.h" 
#include <cstdio>
#include <iostream>
#define	  stop __asm nop	
#include <Windows.h>
void main()
{
	
	setlocale(LC_ALL, "Russian");
	BooksCollection library;
	initBooksCollection(library);
	help();
	bool run = true;
	while (run) {
		char choise = 0;
		userhi();
		scanf("%c", &choise);
		fflush(stdin);
		std::cout << std::endl;
		switch (choise) {
		case 'h':
			help();
			break;

		case 'q':
			run = false;
			break;
		case 'b':
			addDefaultBookshelf(library);
			break;
		case 'p':
			printTheCollection(library);
			break;
		case 'a':
			addNewBook(library);
			break;
		case 'n': //задание 4 варианта
			popularcategory(library);
			break;
		case 'd':
			deleteBook(library);
			break;
		case 's':
			saveToFile(library);
			break;
		case 'l':
			loadBookFromFile(library);
			break;
		case 'x':
			flushFile();
			break;
		case 'z':
			flushCollection(library);
			break;
		case 't':
			sortChoise(library);
			break;
		case'c':
			loadBookDeleted(library);
			break;
		default:
			std::cout << "вводите только то что есть в \'меню\', нажмите  'h'." << std::endl;
			break;
		}
	}
	flushTheStruct(library);
	std::cout << std::endl;
	std::cout << "the end" << std::endl;
	std::cout << _CrtDumpMemoryLeaks(); // если равно 0 утечек нету
	system("pause");
}