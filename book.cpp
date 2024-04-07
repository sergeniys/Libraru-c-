#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "book.h"
#include "Menu.h"


char* categoriesToString[] = { "Programming", "Classic", "Post Modern", "Bigraphy", "Trash" };

void printBook(const Book& book) {
	printf("TITLE:\t\t%s\nAUTHOR:\t\t%s\nCATEGORY:\t%s\nRELEASE DATE:\t%d\nPRICE:\t\t%.2lf RUR\n",
		book.title, book.author, categoriesToString[book.category], book.year, book.price);
	printDivLine();
}

void initBook(Book& book) {
	using namespace std;
	while (true) {
		char title[TITLE_SZ];
		printf("введите название: ");
		scanf("%s", &title);
		if (title == " ") {
			cout << "попробуйте ещё раз" << endl;
			
		}

		else {
			strcpy_s(book.title, TITLE_SZ, title);
			fflush(stdin);
			break;
		}
	}
	while (true) {
		char author[AUTHOR_SZ];
		printf("введите атвора: ");
		scanf("%s", &author);
		if (author == " ") {
			cout << "попробуйте ещё раз" << endl;
			
		}
		else {

			strcpy_s(book.author, AUTHOR_SZ, author);
			fflush(stdin);
			break;
		}
	}
	int year = 0;
	printf("введите год: ");
	while (true) {
		//scanf("%d", &year);
		cin >> year;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Вы ввели не число!" << endl;
		}
		else if (year < 0 || year > 2023) {
			printf("неравильный год, попробуйте ещё раз: ");
			continue;
		}
		else {
			book.year = year;
			break;
		}

	}
	double price = 0.0;
	printf("введите цену: ");
	while (true) {
		cin >>  price;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Вы ввели не число!" << endl;
		}
		else if (price < 0)
			printf("цена не может быть отрицательной, попробуйте ещё раз:\n");
		else {
			book.price = price;
			break;
		}
	}

	int idcategory = 0;
	int catNum = sizeof(categoriesToString) / sizeof(categoriesToString[0]) + 1;
	while (true) {
		printDivLine();
		puts("доступные категории:");
		printDivLine();
		for (int i = 0; i < catNum - 1; i++) {
			using namespace std;
			printf("[%d] - %s\n", (i + 1), categoriesToString[i]);
		}
		printf("выберите категорию: [1...%d]\n> ", catNum);
		cin>>idcategory;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Вы ввели не число!" << endl;
		}
		else if (idcategory < 1 || idcategory >= catNum) {
			printf("вы ввели неверную категорию");
		}
		else {
			book.category = static_cast<Category>(idcategory - 1);
			break;
		}
	}
}


//функции для сортировки
float compareTitles(const Book& first, const Book& second) {
	return std::strcmp(first.title, second.title);
}

float compareAuthors(const Book& first, const Book& second) {
	return std::strcmp(first.author, second.author);
}

float compareYears(const Book& first, const Book& second) {
	return first.year - second.year;
}

float comparePrices(const Book& first, const Book& second) {
	return first.price - second.price;
}

float compareCategory(const Book& first, const Book& second) {
	return first.category - second.category;
}

char* getTitle(Book& book) {
	return book.title;
}

