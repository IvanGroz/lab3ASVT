#include "BSTree.h"
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include "RBSTree.h"

#define key int
#define val string

using namespace std;

int _print_t(typename Collection<key, val>::Node* tree, int is_left, int offset, int depth, char s[20][255])
{
	char b[20];
	int width = 5;

	if (!tree) return 0;

	sprintf_s(b, "(%03d)", tree->getKey());

	int left = _print_t(tree->left, 1, offset, depth + 1, s);
	int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
	for (int i = 0; i < width; i++)
		s[depth][offset + left + i] = b[i];

	if (depth && is_left) {

		for (int i = 0; i < width + right; i++)
			s[depth - 1][offset + left + width / 2 + i] = '-';

		s[depth - 1][offset + left + width / 2] = '.';

	}
	else if (depth && !is_left) {

		for (int i = 0; i < left + width; i++)
			s[depth - 1][offset - width / 2 + i] = '-';

		s[depth - 1][offset + left + width / 2] = '.';
	}
#else
	for (int i = 0; i < width; i++)
		s[2 * depth][offset + left + i] = b[i];

	if (depth && is_left) {

		for (int i = 0; i < width + right; i++)
			s[2 * depth - 1][offset + left + width / 2 + i] = '-';

		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

	}
	else if (depth && !is_left) {

		for (int i = 0; i < left + width; i++)
			s[2 * depth - 1][offset - width / 2 + i] = '-';

		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset - width / 2 - 1] = '+';
	}
#endif

	return left + width + right;
}

void print_t(typename Collection<int, string>::Node* tree)
{
	char s[20][255];
	for (int i = 0; i < 20; i++)
		sprintf_s(s[i], "%80s", " ");

	_print_t(tree, 0, 0, 0, s);

	for (int i = 0; i < 20; i++)
		printf("%s\n", s[i]);
}

void repaintConsole()
{
	HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cd;
	cd.X = 0;
	cd.Y = 0;
	SetConsoleCursorPosition(hd, cd);
}

void checkInt(istream& ios, int& value) {
	while (!(ios >> value) || ios.get() != '\n') // cin.fail() возвращает 1 если установлет failbit
	{
		cout << "Нужны только цифры!\n";
		ios.clear(); // сбрасывает все биты потока, тоесть поток становится "хорошим"
		ios.sync();//Удалим данные из буффера
		cin.ignore(999, '\n');
		cout << "Введите число: ";
	}
}

void drawMenu(int& index) {
	string head = " Циклический двусвязный список (Выберите стрелочками одну из доступных команд )\n";
	string arrStr[] = {
		" Размер('size') \n",
		" Очистка('clear') \n",
		" Проверка на пустоту('empty') \n" ,
		" Добавление элемента в дерево('insert') \n" ,
		" Получение доступа к элементу по ключу('get') \n",
		" Изменить значение элемента по ключу('put') \n" ,
		" Удалить элемент по ключу('remove') \n",
		" Обход дерева согласно заданию('showByScheme') \n",
		" Получить порядок узла('getOrder') \n" ,
		" Показать('show')[пробел] \n",
		" Тестирование('test') \n",
		" Выйти('exit') \n " };

	int size = sizeof(arrStr) / sizeof(string);
	if (index >= size) {
		index = 0;
	}
	else {
		if (index < 0) {
			index = size - 1;
		}
	}
	arrStr[index].insert(arrStr[index].begin(), '>');
	repaintConsole();
	cout << head;
	for (string var : arrStr)
	{
		cout << var;
	}
}

void hideCursor() {
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}


int main() {
	system("chcp 1251 > nul");

	hideCursor();
	srand(time(NULL));
	RBSTree<key, val> tree;
	tree.insert(60,"Николай");
	tree.insert(20,"Димитрий");
	tree.insert(70,"Иван");
	tree.insert(40,"Лена");
	tree.insert(10,"Александр");
	tree.insert(30, "Татьяна");
	tree.insert(50, "Наталья");
	
	int index = 0;
	key keyTmp;
	val valTmp;
					RBSTree<key, val> testTree2;
					BSTree<key, val> testTree;
	while (true) {

		try
		{
			drawMenu(index);
			switch (_getch())//27-esc 13-enter 8 - backspace 32-space
			{
			case 80://up
				index++;
				break;
			case 72://down
				index--;
				break;
			case 32://space
				system("cls");
				
				print_t(tree.getRoot());
 				//tree.draw( cout);
				
				system("pause");
				system("cls");
				break;
			case 8:
			case 27://exit
				return 0;
				break;
			case 13://enter
				switch (index)
				{
				case 0://размер

					system("cls");
					cout << "Размер дерева = " << tree.size() << endl;

					system("pause");
					system("cls");
					break;
				case 1://Очистка('clear')

					system("cls");
					tree.clear();
					cout << "Дерево очищено" << endl;

					system("pause");
					system("cls");
					break;
				case 2://Проверка на пустоту('empty')

					system("cls");
					cout << " Дерево " << (tree.empty() ? "" : "не ") << "пусто!" << endl;
					system("pause");
					system("cls");
					break;
				case 3://Добавление элемента в дерево('insert')

					system("cls");
					cout << "Введите ключ (цифры): ";
					checkInt(cin, keyTmp);
					cout << "Значение элемента:";
					cin >> valTmp;
					tree.insert(keyTmp, valTmp);
					cout << "Элемент успешно добавлен!" << endl;
					system("pause");
					system("cls");
					break;
				case 4://Получение доступа к элементу по ключу('get')

					system("cls");
					cout << "Введите ключ элемента, значение которого хотите получить:";
					checkInt(cin, keyTmp);
					cout << "Значение элемента = " << tree.get(keyTmp) << endl;

					system("pause");
					system("cls");
					break;
				case 5://Изменить значение элемента по ключу('put')

					system("cls");
					
					cout << "Введите значение ключа:";
					checkInt(cin, keyTmp);
					cout << "Введите значение элемента:";
					cin >> valTmp;
					tree.put(keyTmp, valTmp);
					cout << "PUTTED" << endl;

					system("pause");
					system("cls");
					break;
				case 6://Удалить элемент по ключу('remove')

					system("cls");
					cout << "Введите значение ключа:";
					checkInt(cin, keyTmp);
					tree.remove(keyTmp);
					cout << "Удалено\n";
					system("pause");
					system("cls");
					break;
				case 7://Обход дерева согласно заданию('showByScheme')

					system("cls");
					tree.showByScheme(cout);
					system("pause");
					system("cls");
					break;
				case 8://Порядок узла

					system("cls");
					cout << "Введите значение ключа:";
					checkInt(cin,keyTmp);
					cout << "Для узла с ключом:" << keyTmp << " порядок равняется:" << tree.getOrder(keyTmp) << endl;
					system("pause");
					system("cls");
					break;
				case 9://Показать('show')[пробел]

					system("cls");
					cout << "Выбериите как показать дерево:\n1) Симметрично \n2) Обратно\n Введите цифру:";
					int i;
					checkInt(cin, i);
					if (i == 1) {
						tree.showDirectly(cout);
					}
					else {
						if (i == 2) {
							tree.showBack(cout);
						}
						else
						{
							cout << "\nТакой комманды нет!\n";
						}
					}
					system("pause");
					system("cls");
					break;
				case 10://Тестирование('test')

					system("cls");
					cout << "Введите кол-во узлов дерева:";
					int nodesAmount, rangeKey;
					checkInt(cin, nodesAmount);
					cout << "Введите верхнюю границу диапазона генерации значения ключа от 0 до:";
					checkInt(cin, rangeKey);
					
					for (int i = 0; i < nodesAmount; i++)
						testTree.insert(rand() % rangeKey, "a" + rand() % 26);
					testTree.countMovingInsert = 0;
					for (int i = 0; i < nodesAmount / 2; i++) {
						testTree.insert(rand() % nodesAmount, "a" + rand() % 26);
						try
						{
							testTree.remove(rand() % nodesAmount);
						}
						catch (const std::exception&) {}//Для пропуска сообщений о том что некоторые узлы былди не найдены
						try
						{
							testTree.get(rand() % rangeKey);
						}
						catch (const std::exception&) {}
					}
					cout << "Тест двоичного дерева INSERT = " << testTree.countMovingInsert / float(nodesAmount / 2) * 1.39f << endl
						<< "Тест двоичного дерева DELETE = " << testTree.countMovingDelete / float(nodesAmount / 2) * 1.39f << endl
						<< "Тест двоичного дерева SEARCH = " << testTree.countMovingFind / float(nodesAmount / 2) * 1.39f << endl;
					
					testTree2.countMovingInsert = 0;
					testTree2.countMovingDelete = 0;
					testTree2.countMovingFind = 0;
					for (int i = 0; i < nodesAmount; i++)
						testTree2.insert(rand() % rangeKey, "a" + rand() % 26);
					testTree2.countMovingInsert = 0;
					for (int i = 0; i < nodesAmount / 2; i++) {
						testTree2.insert(rand() % nodesAmount, "a" + rand() % 26);
						try
						{
							testTree2.remove(rand() % nodesAmount);
						}
						catch (const std::exception&) {}//Для пропуска сообщений о том что некоторые узлы былди не найдены
						try
						{
							testTree2.get(rand() % rangeKey);
						}
						catch (const std::exception&) {}
					}
					cout <<"Тест рандомизированного двоичного дерева INSERT = " << testTree2.countMovingInsert / float(nodesAmount / 2) * 1.39f << endl
						<< "Тест рандомизированного двоичного дерева DELETE = " << testTree2.countMovingDelete / float(nodesAmount / 2) * 1.39f << endl
						<< "Тест рандомизированного двоичного дерева SEARCH = " << testTree2.countMovingFind / float(nodesAmount / 2) * 1.39f << endl;
					testTree.clear();
					testTree2.clear();
					system("pause");
					system("cls");
					break;
				case 11://exit

					system("cls");
					exit(0);
					system("pause");
					system("cls");
					break;
				}

				break;
			}
		}
		catch (const std::exception& e)
		{
			system("cls");

			cout << e.what() << endl;
			system("pause");
			system("cls");
		}
	}
}








