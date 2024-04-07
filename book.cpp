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
		printf("������� ��������: ");
		scanf("%s", &title);
		if (title == " ") {
			cout << "���������� ��� ���" << endl;
			
		}

		else {
			strcpy_s(book.title, TITLE_SZ, title);
			fflush(stdin);
			break;
		}
	}
	while (true) {
		char author[AUTHOR_SZ];
		printf("������� ������: ");
		scanf("%s", &author);
		if (author == " ") {
			cout << "���������� ��� ���" << endl;
			
		}
		else {

			strcpy_s(book.author, AUTHOR_SZ, author);
			fflush(stdin);
			break;
		}
	}
	int year = 0;
	printf("������� ���: ");
	while (true) {
		//scanf("%d", &year);
		cin >> year;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "�� ����� �� �����!" << endl;
		}
		else if (year < 0 || year > 2023) {
			printf("����������� ���, ���������� ��� ���: ");
			continue;
		}
		else {
			book.year = year;
			break;
		}

	}
	double price = 0.0;
	printf("������� ����: ");
	while (true) {
		cin >>  price;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "�� ����� �� �����!" << endl;
		}
		else if (price < 0)
			printf("���� �� ����� ���� �������������, ���������� ��� ���:\n");
		else {
			book.price = price;
			break;
		}
	}

	int idcategory = 0;
	int catNum = sizeof(categoriesToString) / sizeof(categoriesToString[0]) + 1;
	while (true) {
		printDivLine();
		puts("��������� ���������:");
		printDivLine();
		for (int i = 0; i < catNum - 1; i++) {
			using namespace std;
			printf("[%d] - %s\n", (i + 1), categoriesToString[i]);
		}
		printf("�������� ���������: [1...%d]\n> ", catNum);
		cin>>idcategory;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "�� ����� �� �����!" << endl;
		}
		else if (idcategory < 1 || idcategory >= catNum) {
			printf("�� ����� �������� ���������");
		}
		else {
			book.category = static_cast<Category>(idcategory - 1);
			break;
		}
	}
}


//������� ��� ����������
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

