#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Menu.h"
#include "BooksCollection.h"
#include <unordered_map>


const int INIT_SIZE = 3;
const char textTxt[] = "text.txt";
const char deletedTxt[] = "deleted.txt";
char* categoriesToStrings[] = { "Programming", "Classic", "Post Modern", "Bigraphy", "Trash" };
enum SortType {
	title,
	author,
	year,
	price,
	category,
	SORT_LABELS_SIZE
};

const char* sortLabels[] = { "по заголовку", "по автору", "по году", "цене", "по категории" };

float(*comparator[])(const Book&, const Book&) = {
	compareTitles,
	compareAuthors,
	compareYears,
	comparePrices,
	compareCategory
};

void initBooksCollection(BooksCollection& coolect) {
	coolect.numberOfBooks = 0;
	coolect.capacity = INIT_SIZE;
	coolect.books = new Book * [INIT_SIZE];
}

int mostFrequentNumber(int* numbers, int size) {
	std::unordered_map<int, int> frequencyMap;
	int mostFrequentNum = numbers[0];

	for (int i = 0; i < size; i++) {
		frequencyMap[numbers[i]]++;
		if (frequencyMap[numbers[i]] > frequencyMap[mostFrequentNum]) {
			mostFrequentNum = numbers[i];
		}
	}

	return mostFrequentNum;
}

void addNewBook(BooksCollection& coolect) {
	if (coolect.numberOfBooks <= coolect.capacity) {
		insertBook(coolect);
		if (coolect.numberOfBooks == coolect.capacity) {
			enlargeTheCollection(coolect);
		}
	}
	else {
		enlargeTheCollection(coolect);
		insertBook(coolect);
	}
}

void addNewBook(BooksCollection& coolect, Book* book) {
	if (coolect.numberOfBooks <= coolect.capacity) {
		insertBook(coolect, book);
		if (coolect.numberOfBooks == coolect.capacity) {
			enlargeTheCollection(coolect);
		}
	}
	else {
		enlargeTheCollection(coolect);
		insertBook(coolect, book);
	}
}

void enlargeTheCollection(BooksCollection& coolect) { // пополнение коллекции
	Book** tmp = new Book * [coolect.capacity];
	int prevCap = coolect.capacity;
	int newCapacity = coolect.capacity + INIT_SIZE;
	for (int i = 0; i < coolect.capacity; i++) {
		tmp[i] = coolect.books[i];
	}
	delete[] coolect.books;
	coolect.books = new Book * [newCapacity];
	coolect.capacity = newCapacity;
	for (int i = 0; i < prevCap; i++) {
		coolect.books[i] = tmp[i];

	}
}

void insertBook(BooksCollection& coolect) {
	Book* newBook = new Book();
	initBook(*newBook);
	coolect.numberOfBooks++;
	coolect.books[coolect.numberOfBooks - 1] = newBook;
}

void insertBook(BooksCollection& coolect, Book* book) {
	Book* newBook = book;
	coolect.numberOfBooks++;
	coolect.books[coolect.numberOfBooks - 1] = newBook;
}

void printTheCollection(const BooksCollection& coolect) {
	using namespace std;
	setlocale(LC_ALL, "Russian");
	if (isEmpty(coolect)) {
		cout << "нет книг в картотеке!" << endl;
	}
	else {
		printDivLine();
		cout << "    *** картотека ***" << endl;
		printDivLine();
		for (int i = 0; i < coolect.numberOfBooks; i++) {
			printBook(*coolect.books[i]);
		}
		printDivLine();
	}
}

bool isEmpty(const BooksCollection& coolect) {
	if (coolect.numberOfBooks == 0) {
		return true;
	}
	else {
		return false;
	}
}

void saveToFileD(const BooksCollection& coolect, int s) {
	if (isEmpty(coolect))
		return;

	char fileName[] = "deleted.txt";
	printf("сохран€ем в \'%s\' файл...\n. . . вы сможете восстановить файл\n", fileName);
	FILE* file = fopen(fileName, "w");
	if (file) {

		Book book = *coolect.books[s];
		fprintf(file, "%s %s %d %.2lf %d \n", book.author, book.title, book.year, book.price, book.category);

		fclose(file);
	}
	else {
		printFileError();
	}
}

void deleteBook(BooksCollection& coolect) {
	using namespace std;
	int choise = 0;
	int supper = 0;
	while (true) {
		cout << "удалить диапозон - 1, одну книгу - 2, меню - 3" << endl;
		cin >> supper;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "¬ы ввели не число!" << endl;
		}
			else if (supper == 2) {
				cout << "какую книгу вы хотите удалить: " << endl;
				printBookTitles(coolect);

				cin >> choise;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					cout << "¬ы ввели не число!" << endl;
					
				}
				else {
					int chosenIndex = choise - 1;
					saveToFileD(coolect, chosenIndex);
					for (int i = chosenIndex; i < coolect.numberOfBooks; i++) {
						coolect.books[i] = coolect.books[i + 1];
					}
					coolect.numberOfBooks--;
					printBookTitles(coolect);
					break;
				}
		}

			else if (supper == 1) {
			while (true) {
				int deleter = supper + 1;
				int start = 0;
				int end = 0;
				printBookTitles(coolect);
				cout << "введите страт диапазона" << endl;
				cin >> start;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					cout << "¬ы ввели не число!" << endl;
					break;
				}


				cout << "введите конец диапазона" << endl;
				cin >> end;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					cout << "¬ы ввели не число!" << endl;
					break;

				}
				int z = 1;
				for (int i = start - 1; i <= end - 1; i++) {
					coolect.books[i] = coolect.books[coolect.numberOfBooks - z];
					z++;

				}
				for (int i = end - start + 1; i > 0; i--) {
					coolect.numberOfBooks--;

				}
				printBookTitles(coolect);
				break;
			}
		}
		else if (supper == 3) {
			break;
			help();
		}
		
		else {
			cout << "введите нужное число из списка" << endl;
		}
	}
}

void printBookTitles(const BooksCollection& coolect) {
	using namespace std;
	for (int i = 0; i < coolect.numberOfBooks; i++) {

		cout << "[" << i + 1 << "] - " << getTitle(*coolect.books[i]) << endl;
	}
}

void flushTheStruct(BooksCollection& coolect) {
	for (int i = 0; i < coolect.numberOfBooks; i++) {
		delete coolect.books[i];
	}
	coolect.capacity = 0;
	coolect.numberOfBooks = 0;
	delete[] coolect.books;
}

void addDefaultBookshelf(BooksCollection& coolect) {
	addDefaultBook(coolect, "Bruce_Eckel", "Thinling_In_Java", 1998, 1200.00, PROGRAMMING);
	addDefaultBook(coolect, "Bruce_Eckel", "Atomic_Scala", 2012, 2050.00, PROGRAMMING);
	addDefaultBook(coolect, "Sebastien_Goasguen", "Docker_in_Cloud", 2016, 1500.00, PROGRAMMING);
	addDefaultBook(coolect, "Matthew_Campbell", "Microservices_in_Go", 2016, 1800.20, PROGRAMMING);
	addDefaultBook(coolect, "Pete_Goodliffe", "Becoming_a_Better_Programmer", 2014, 1755.90, PROGRAMMING);
	addDefaultBook(coolect, "Ivan_Turgenev", "A_Month_in_the_Country", 1848, 200.00, CLASSICS);
	addDefaultBook(coolect, "Alexandra_Marinina", "Men_Games", 2012, 20.00, TRASH_LIT);
	addDefaultBook(coolect, "Alexander_Suvorov", "Science_Of_Victory", 1806, 850.00, BIOGRAPHY);
	addDefaultBook(coolect, "Kernighan_and_Richie", "The_C_programming_language", 1978, 991.00, PROGRAMMING);
	addDefaultBook(coolect, "Bjarne_Stroustroup", "The_C++_programming_language", 1997, 600.00, PROGRAMMING);
	addDefaultBook(coolect, "Kernighan_and_Donovan", "The_Go_programming_language", 2015, 1315.00, PROGRAMMING);
	addDefaultBook(coolect, "Steve_McConnel", "Code_Complete", 1993, 1200.99, PROGRAMMING);
	addDefaultBook(coolect, "Bob_Martin", "Clean_Code", 2009, 653.00, PROGRAMMING);
	addDefaultBook(coolect, "Viktor_Pelevin", "Generation_P", 1999, 300.00, POST_MODERN);
	addDefaultBook(coolect, "Vladimir_Sorokin", "Blue_Fat", 1999, 280.00, POST_MODERN);
	addDefaultBook(coolect, "Leo_Tolstoy", "War_and_Peace", 1869, 339.00, CLASSICS);
	addDefaultBook(coolect, "Anton_Chekhov", "The_Cherry_Orchard", 1904, 169.52, CLASSICS);
	addDefaultBook(coolect, "Sau_Sheong_Chang", "Go_Web_Programming", 2016, 2411.00, PROGRAMMING);
	addDefaultBook(coolect, "Walter_Isaacson", "Steve_Jobs", 2011, 1000.00, BIOGRAPHY);
	addDefaultBook(coolect, "Darya_Dontcova", "Evlampiya_Romanova", 2001, 50.00, TRASH_LIT);
	addDefaultBook(coolect, "Chuck_Palahniuk", "Survivor", 1999, 304.00, POST_MODERN);
	addDefaultBook(coolect, "Alexander_Pushkin", "The_Fountain_of_Bakhchisaray", 1823, 200.00, CLASSICS);
	
}

void addDefaultBook(BooksCollection& coolect, char* author, char* title, int year, double price, Category cat) {
	Book* book = new Book();
	strcpy_s(book->author, AUTHOR_SZ, author);
	strcpy_s(book->title, TITLE_SZ, title);
	book->year = year;
	book->price = price;
	book->category = cat;
	addNewBook(coolect, book);
	
}



void saveToFile(const BooksCollection& coolect) {
	if (isEmpty(coolect))
		return;

	char fileName[] = "text.txt";
	printf("сохран€ем в \'%s\' файл...\n", fileName);
	FILE* file = fopen(fileName, "w");
	if (file) {
		for (int i = 0; i < coolect.numberOfBooks; i++) {
			Book book = *coolect.books[i];
			fprintf(file, "%s %s %d %.2lf %d \n", book.author, book.title, book.year, book.price, book.category);
		}
		fclose(file);
	}
	else {
		printFileError();
	}
}

void loadBookFromFile(BooksCollection& coolect) {
	printf("загружаем из \'%s\' файла...\n", textTxt);
	FILE* file = fopen(textTxt, "r");
	if (file) {
		int lines = countNumberOfLines(file);
		file = fopen(textTxt, "r");
		for (int i = 0; i < lines; i++) {
			Book* book = new Book();
			scanBook(file, *book);
			addNewBook(coolect, book);
		}
		fclose(file);
	}
	else {
		printFileError();
	}
}

void loadBookDeleted(BooksCollection& coolect) {
	printf("загружаем из \'%s\' файла...\n", deletedTxt);
	FILE* file = fopen(deletedTxt, "r");
	if (file) {
		int lines = countNumberOfLines(file);
		file = fopen(deletedTxt, "r");
		for (int i = 0; i < lines; i++) {
			Book* book = new Book();
			scanBook(file, *book);
			addNewBook(coolect, book);
			flushFileD();
		}
		fclose(file);
	}
	else {
		printFileError();
	}
}

void scanBook(FILE* file, Book& book) {
	fscanf(file, "%s %s %d %lf %d \n", book.author, book.title, &book.year, &book.price, &book.category);
}

int countNumberOfLines(FILE* file) {
	unsigned int numberOfLines = 0;
	char ch;
	while (EOF != (ch = getc(file))) {
		if (ch == '\n')
			numberOfLines++;
	}
	fclose(file);
	return numberOfLines;
}

void printFileError() {
	puts("ошибка, неполучаетс€ открыть файл(\n");
}

void flushFile() { // 
	FILE* file = fopen(textTxt, "w");
	if (file) {
		fflush(file);
		fclose(file);
	}
}

void flushFileD() { // 
	FILE* file = fopen(deletedTxt, "w");
	if (file) {
		fflush(file);
		fclose(file);
	}
}

void flushCollection(BooksCollection& coolect) {
	coolect.capacity = INIT_SIZE;
	coolect.numberOfBooks = 0;
	delete[] coolect.books;
	coolect.books = new Book * [coolect.capacity];
}

void sortChoise(BooksCollection& coolect) {
	using namespace std;
	int choise = 0;
	cout << "выберите тип сортировки: " << endl;
	for (int i = 0; i < SORT_LABELS_SIZE; i++) {
		cout << i << " - sort " << sortLabels[i] << endl;
	}
	while (true) {
		userhi("sorting");
		fflush(stdin);
		scanf("%d", &choise);
		fflush(stdin);
		if (isSortChoiseValid(choise)) {
			break;
		}
		else {
			printf("неточный ввод, попробуйте ещЄ раз!\n");
			continue;
		}
	}
	sort(coolect, comparator[choise]);
}


bool isSortChoiseValid(int choise) {
	if (choise < title || choise >= SORT_LABELS_SIZE) {
		return false;
	}
	else {
		return true;
	}
}

void sort(BooksCollection& coolect, float(*comparators)(const Book&, const Book&)) {
	Book** booksArray = coolect.books;
	for (int i = 1; i < coolect.numberOfBooks; i++) {
		for (int j = 0; j < coolect.numberOfBooks - 1; j++) {

			if (comparators(*booksArray[j], *booksArray[j + 1]) > 0) { //сортировка пузырьком // в comparators - подставл€етс€ нужна€ функци€ и сравниевает книги по нужному критерию
				Book* tmpBook = booksArray[j];
				booksArray[j] = booksArray[j + 1];
				booksArray[j + 1] = tmpBook;
			}
			else if (comparators(*booksArray[j], *booksArray[j + 1]) == 0) {
				if (compareYears(*booksArray[j], *booksArray[j + 1]) > 0) {
					Book* tmpBook = booksArray[j];
					booksArray[j] = booksArray[j + 1];
					booksArray[j + 1] = tmpBook;


				}
			}
		}
	}
}





void popularcategory(BooksCollection& coolect) { // списком дин



	Book** booksArray = coolect.books;
	int a = 0, b = 0, c = 0, d = 0, e = 0;
	int* alphabet = new int[50];

	for (int i = 0; i < coolect.numberOfBooks; i++) {
		
		alphabet[i] = booksArray[i]->category;


	}
	int t = mostFrequentNumber(alphabet, coolect.numberOfBooks);
	std::cout << "самое попул€рна€ категори€:" << categoriesToStrings[t] << std::endl;

	//for (int i = 0; i < coolect.numberOfBooks; i++) {
	//	std::cout << alphabet[i] << std::endl;
	//}
}







			/*
	std::string result = findLargestVariableName(a, b, c, d, e);
	char* categoriesToString[] = { "Programming", "Classic", "Post Modern", "Bigraphy", "Trash" };
	if (result == "a") {
		std::cout << "самый попул€рный жанр:" << categoriesToString[0] << std::endl;
	}
	else if (result == "b") {
		std::cout << "самый попул€рный жанр:" << categoriesToString[1] << std::endl;
	}
	else if (result == "c") {
		std::cout << "самый попул€рный жанр:" << categoriesToString[2] << std::endl;
	}
	else if (result == "d") {
		std::cout << "самый попул€рный жанр:" << categoriesToString[3] << std::endl;
	}
	else if (result == "e") {
		std::cout << "самый попул€рный жанр:" << categoriesToString[4] << std::endl;
	}
	else {
		std::cout << result << std::endl;
	}*/

	


/*	enum Category {
		PROGRAMMING,
		CLASSICS,
		POST_MODERN,
		BIOGRAPHY,
		TRASH_LIT
	};*/
