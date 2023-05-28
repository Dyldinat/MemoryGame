#include <iostream>
#include <Windows.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

void printLoading()
{
	char option;
	system("cls");
	cout << " Введите любой символ, чтобы начать игру" << endl << " ";
	cin >> option;
	cout << " Идет загрузка: ";
	for (int i = 3; i > 0; i--)
	{
		Sleep(1000);
		cout << i << " ";
	}
	cout << endl << " ---------   ИГРА НАЧАЛАСЬ   ---------" << endl;	Sleep(500);
}

void enterRecord(unsigned long long gameTime, string mode) // запись результата
{
	void openMenu();

	string name;
	int minutes = gameTime / 60;
	int seconds = gameTime % 60;

	system("cls");
	cout << " Ваше время - " << minutes << " минут " << seconds << " секунд\n\n";
	cout << " Введите своё имя: ";
	cin >> name;

	ofstream out;

	out.open("C:/Users/Admin/Desktop/Основы программирования/Учебная практика 2023г/Rating.txt", std::ios::binary | std::ios::app); 
	if (out.is_open())
	{
		out << "\n" << name << " " << mode;

		if (minutes < 10)
			out << " 0" << minutes;
		else
			out << " " << minutes;
		if (seconds < 10)
			out << " 0" << seconds;
		else
			out << " " << seconds;
	}
	out.close();

	cout << "\nВаши данные успешно записаны";
	Sleep(500);

	openMenu();
}

void printRecords() // вывод результатов
{
	ifstream in;
	string word;
	int counter = 1;

	system("cls");

	in.open("C:/Users/Admin/Desktop/Основы программирования/Учебная практика 2023г/Rating.txt"); 

	if (in.is_open())
	{
		for (int i = 0; i < 68; i++)
		{
			if (i == 0)
				cout << "+";
			else if (i == 26)
				cout << "+";
			else if (i == 46)
				cout << "+";

			else if (i == 67)
				cout << "+";
			else
				cout << "-";
		}

		cout << "\n|";
		cout << setw(14) << right << "Имя" << setw(12) << "|" << setw(12) << right << "Режим" << setw(8) << "|" << setw(13) << right << "Время" << setw(8) << "|" << endl;

		for (int i = 0; i < 68; i++)
		{
			if (i == 0)
				cout << "+";
			else if (i == 26)
				cout << "+";
			else if (i == 46)
				cout << "+";

			else if (i == 67)
				cout << "+";
			else
				cout << "-";
		}
		cout << "\n";

		while (in >> word)
		{
			if (counter % 10 == 1)
			{
				cout << "| " << setw(24) << left << word << "| ";
			}
			if (counter % 10 == 2)
			{
				cout << setw(18) << word << "| ";
			}

			if (counter % 10 == 3)
			{
				cout << word << " минут ";
			}

			if (counter % 10 == 4)
			{
				cout << word;
				cout << " секунд |\n";
				counter = 0;
			}

			counter++;
		}

		for (int i = 0; i < 68; i++)
		{
			if (i == 0)
				cout << "+";
			else if (i == 26)
				cout << "+";
			else if (i == 46)
				cout << "+";

			else if (i == 67)
				cout << "+";
			else
				cout << "-";
		}
		cout << "\n";
	}
}

void startGame(int players, int mode, int speedLevel, int sequenceLength, string selectedMode)
{
	void openMenu();
	const int maxSequenceLength = 8;

	string Sequence[maxSequenceLength]; // сгенерированная последовательность
	string answers[maxSequenceLength] = {}; // массив ответов
	boolean gameOver = false; // для завершения игры
	boolean win = false; // для победы
	int roundCount = sequenceLength; // число раундов
	int round = 1;
	ifstream in;
	string read;
	unsigned long long startTime;
	vector<string> VariantsPlayChars;
	vector<string> VariantsPlayWords;
	vector<string> VariantsPlayNumbers;
	boolean gameOverPlayer[2] = { false, false };
	boolean winPlayer[2] = { false, false };
	int playerScore[2] = { 0, 0 };
	char option;

	in.open("C:/Users/Admin/Desktop/Основы программирования/Учебная практика 2023г/Chars.txt"); 
	if (in.is_open())
	{
		while (in >> read)
			VariantsPlayChars.push_back(read);
	}
	in.close();

	in.open("C:/Users/Admin/Desktop/Основы программирования/Учебная практика 2023г/Words.txt"); 
	if (in.is_open())
	{
		while (in >> read)
			VariantsPlayWords.push_back(read);
	}
	in.close();

	in.open("C:/Users/Admin/Desktop/Основы программирования/Учебная практика 2023г/Numbers.txt");
	if (in.is_open())
	{
		while (in >> read)
			VariantsPlayNumbers.push_back(read);
	}
	in.close();

	switch (mode) // создание последовательности
	{
	case 1: // строки
		for (int i = 0; i < maxSequenceLength; ++i)
		{
			int k = rand() % VariantsPlayWords.size();
			Sequence[i] = VariantsPlayWords[k];
		}
		break;
	case 2: // числа
		for (int i = 0; i < maxSequenceLength; ++i)
		{
			int k = rand() % VariantsPlayNumbers.size();
			Sequence[i] = VariantsPlayNumbers[k];
		}
		break;
	case 3: // символы
		for (int i = 0; i < maxSequenceLength; ++i)
		{
			int k = rand() % VariantsPlayChars.size();
			Sequence[i] = VariantsPlayChars[k];
		}
		break;
	default:
		break;
	}

	startTime = __rdtsc();

	while (!gameOver)
	{
		for (int p = 0; p < players; p++)
		{
			if (gameOverPlayer[0] == true && gameOverPlayer[1] == true)
			{
				gameOver = true;
				break;
			}

			for (int i = 0; i < roundCount; i++) // все раунды
			{
				if (gameOverPlayer[p] == true) // при завершении игры останавливаем игру (выход из цикла)
					break;

				for (int j = 0; j < round; j++) // внутри одного раунда
				{
					system("cls");
					
					cout << " -------------------------------------" << endl;
					cout << " ----------   ИГРА МЕМОРИ   ----------" << endl;
					cout << " -------------------------------------" << endl;

					if (players == 2)
						cout << " Попытка игрока " << p + 1 << endl;

					cout << endl << " Раунд " << round << endl;
					cout << " " << j + 1 << ": " << Sequence[j];

					Sleep(speedLevel * 1000);
				}

				system("cls");
				
				cout << " -------------------------------------" << endl;
				cout << " ----------   ИГРА МЕМОРИ   ----------" << endl;
				cout << " -------------------------------------" << endl;
				if (players == 2)
					cout << " Попытка игрока " << p + 1 << endl;
				cout << endl << " Введите последовательность: " << endl;

				for (int i = 0; i < round; i++) // запись ответов в массив
				{
					cout << " ";
					cin >> answers[i];
				}

				for (int i = 0; i < round; i++) // проверка результатов
				{
					if (gameOverPlayer[p] == true)
						break;

					if (answers[i] != Sequence[i]) // при расхождении ответа с элементом последовательности выходим
					{
						gameOverPlayer[p] = true;

						if (players == 1)
							gameOverPlayer[1] = true;

						playerScore[p] = round - 1;
						round = 0;

						if (players == 2)
						{
							cout << " Игрок " << p + 1 << " не справился" << endl << endl;

							if (gameOverPlayer[0] == true && gameOverPlayer[1] == false)
							{
								cout << " Введите 0 для старта хода следующего игрока" << endl << " ";
								cin >> option;

								switch (option)
								{
								case '0':
									cout << " Идет загрузка: ";
									for (int i = 3; i > 0; i--)
									{
										cout << i << " ";
										Sleep(1000);
									}
									cout << endl << " ---------   ИГРА НАЧАЛАСЬ   ---------" << endl;
									Sleep(500);
									break;
								}
							}
							else
							{
								cout << " Введите 0 для продолжения" << endl;
								cout << " ";
								cin >> option;
							}
						}

						break;
					}

					if (sequenceLength == 4 && i == 3) // для режима с последовательностью из 4
					{
						win = true;
						gameOverPlayer[p] = true;

						if (players == 1)
							gameOverPlayer[1] = true;

						playerScore[p] = round;
						round = 0;

						cout << " Игрок " << p + 1 << " успешло прошел раунд!" << endl << endl;

						if (gameOverPlayer[0] == true && gameOverPlayer[1] == false)
						{
							cout << " Введите 0 для старта хода следующего игрока" << endl << " ";
							cin >> option;

							switch (option)
							{
							case '0':
								for (int i = 3; i > 0; i--)
								{
									cout << i << " ";
									Sleep(1000);
								}
								cout << endl << " ---------   ИГРА НАЧАЛАСЬ   ---------" << endl;
								Sleep(500);
								break;
							}

						}

						break;
					}

					if (sequenceLength == 6 && i == 5) // для 6
					{
						win = true;
						gameOverPlayer[p] = true;

						if (players == 1)
							gameOverPlayer[1] = true;

						playerScore[p] = round;
						round = 0;

						cout << " Игрок " << p + 1 << " успешло прошел раунд!" << endl << endl;

						if (gameOverPlayer[0] == true && gameOverPlayer[1] == false)
						{
							cout << " Введите 0 для старта хода следующего игрока" << endl << " ";
							cin >> option;

							switch (option)
							{
							case '0':
								cout << " Идет загрузка: ";
								for (int i = 3; i > 0; i--)
								{
									cout << i << " ";
									Sleep(1000);
								}
								cout << endl << "  ---------   ИГРА НАЧАЛАСЬ   ---------" << endl;
								Sleep(500);
								break;
							}

						}

						break;
					}

					if (sequenceLength == 8 && i == 7) // для 8
					{
						win = true;
						gameOverPlayer[p] = true;

						if (players == 1)
							gameOverPlayer[1] = true;

						playerScore[p] = round;
						round = 0;

						cout << " Игрок " << p + 1 << " успешло прошел раунд!" << endl << endl;

						if (gameOverPlayer[0] == true && gameOverPlayer[1] == false)
						{
							cout << " Введите 0 для старта хода следующего игрока" << endl << " ";
							cin >> option;

							switch (option)
							{
							case '0':
								cout << " Идет загрузка: ";
								for (int i = 3; i > 0; i--)
								{
									cout << i << " ";
									Sleep(1000);
								}
								cout << endl << "  ---------   ИГРА НАЧАЛАСЬ   ---------" << endl;
								Sleep(500);
								break;
							}

						}

						break;
					}
				}

				if (gameOverPlayer[p] == true)
					break;

				if (gameOverPlayer[p] == false)
					cout << " Правильно! Игра продолжается";

				round++;
			}
		}
	}

	if (gameOver) // завершение игры
	{
		if (players == 2)
		{
			system("cls");
			cout << " -------------------------------------" << endl;
			cout << " ----------   ИГРА МЕМОРИ   ----------" << endl;
			cout << " -------------------------------------" << endl << endl;

			cout << " Счет игроков: " << playerScore[0] << ":" << playerScore[1] << endl;

			if (playerScore[0] > playerScore[1])
				cout << " Победил игрок 1!" << endl;
			else if (playerScore[0] < playerScore[1])
				cout << " Победил игрок 2!" << endl;
			else
				cout << " Ничья" << endl;

			cout << endl << " Введите любой символ, чтобы вернуться в главное меню" << endl << " ";
			cin >> option;

			switch (option)
			{
			default:
				openMenu();
				break;
			}
		}
		else
		{
			if (playerScore[0] == sequenceLength)
			{
				unsigned long long gameTime = (__rdtsc() - startTime) / 2160000000;

				system("cls");
				cout << " -------------------------------------" << endl;
				cout << " ----------   ИГРА МЕМОРИ   ----------" << endl;
				cout << " -------------------------------------" << endl << endl;
				cout << " Правильно! Вы выиграли!" << endl << endl;
				cout << " Ваша последовательность:" << endl << " ";
				for (int i = 0; i < sequenceLength; i++)
					cout << Sequence[i] << " ";
				cout << endl << endl << " Время вашей игры: " << gameTime << " секунд" << endl << endl;
				cout << " Желаете сохранить свой результат?" << endl;
				cout << " 1. Сохранить результат" << endl;
				cout << " 0. Выход в главное меню" << endl << " ";
				cin >> option;

				switch (option)
				{
				case '1':
					enterRecord(gameTime, selectedMode);
					break;

				case '0':
					openMenu();
					break;
				}
			}
			else
			{
				cout << " Вы проиграли!" << endl << endl;
				cout << " Введите любой символ, чтобы вернуться в главное меню" << endl << " ";
				cin >> option;

				switch (option)
				{
				case '0':
					openMenu();
					break;
				default:
					openMenu();
					break;
				}
			}
		}
	}
}

void selectSpeed(int players, int mode, int sequenceLength, string selectedMode) //скорость
{
	void selectLevel(int players, int mode, string selectedMode);
	char speedLevel;
	
	system("cls");
	cout << " -------------------------------------" << endl;
	cout << " ----------   ИГРА МЕМОРИ   ----------" << endl;
	cout << " -------------------------------------" << endl << endl;

	cout << " Выберите временной уровень сложности: " << endl;
	cout << " 1. Лёгкий" << endl;
	cout << " 2. Средний" << endl;
	cout << " 3. Сложный" << endl << endl;
	cout << " 0. Назад к выбору длины" << endl << endl;

	cout << " ";
	cin >> speedLevel;

	switch (speedLevel)
	{
	case '1':
		cout << " Выбран уровень сложности: Лёгкий " << endl;
		Sleep(1500);
		speedLevel = 3;
		selectedMode += "Easy";
		printLoading();
		startGame(players, mode, speedLevel, sequenceLength, selectedMode);
		break;
	case '2':
		cout << " Выбран уровень сложности: Средний" << endl;
		Sleep(1500);
		speedLevel = 2;
		selectedMode += "Normal";
		printLoading();
		startGame(players, mode, speedLevel, sequenceLength, selectedMode);
		break;
	case '3':
		cout << " Выбран уровень сложности: Сложный" << endl;
		Sleep(1500);
		speedLevel = 1;
		selectedMode += "Hard";
		printLoading();
		startGame(players, mode, speedLevel, sequenceLength, selectedMode);
		break;
	case '0':
		selectLevel(players, mode, selectedMode);
		break;
	default:
		selectSpeed(players, mode, sequenceLength, selectedMode);
		break;
	}
}

void selectLevel(int players, int mode, string selectedMode) // длина последовательности
{
	void selectMode(int players);

	int sequenceLength;
	char option;

	system("cls");
	cout << " -------------------------------------" << endl;
	cout << " ----------   ИГРА МЕМОРИ   ----------" << endl;
	cout << " -------------------------------------" << endl << endl;

	cout << " Выберите длину последовательности" << endl;
	cout << " 1. Четыре" << endl;
	cout << " 2. Шесть" << endl;
	cout << " 3. Восемь" << endl << endl;
	cout << " 0. Назад к выбору режима" << endl << endl;

	do
	{
		cout << " ";
		cin >> option;

		switch (option)
		{
		case '1':
			sequenceLength = 4;
			selectedMode += "4_";
			cout << " Выбрана длина последовательности: Четыре" << endl;
			Sleep(1500);

			selectSpeed(players, mode, sequenceLength, selectedMode);

			continue;

		case '2':
			sequenceLength = 6;
			selectedMode += "6_";
			cout << " Выбрана длина последовательности: Шесть" << endl;
			Sleep(1500);

			selectSpeed(players, mode, sequenceLength, selectedMode);

			continue;

		case '3':
			sequenceLength = 8;
			selectedMode += "8_";
			cout << " Выбрана длина последовательности: Восемь" << endl;
			Sleep(1500);

			selectSpeed(players, mode, sequenceLength, selectedMode);

			continue;
		case '0':
			selectMode(players);
			continue;
		default:
			cout << " Не правильно сделан выбор. Повторите попытку..." << endl;
			Sleep(500);
			selectLevel(players, mode, selectedMode);
			continue;
		}
	} while (option != '0');
}

void selectMode(int players) // для чисел/слов/символов
{
	void openMenu();

	char option;
	int mode;
	string selectedMode;

	system("cls");
	cout << " -------------------------------------" << endl;
	cout << " ----------   ИГРА МЕМОРИ   ----------" << endl;
	cout << " -------------------------------------" << endl << endl;

	cout << " Выберите режим" << endl;
	cout << " 1. Слова" << endl;
	cout << " 2. Числа" << endl;
	cout << " 3. Символы" << endl << endl;
	cout << " 0. Вернуться в меню" << endl << endl;

	do
	{
		cout << " ";
		cin >> option;

		switch (option)
		{
		case '1':
			mode = 1;
			selectedMode = "Strings_";
			cout << " Выбран режим: Слова";
			Sleep(1500);
			selectLevel(players, mode, selectedMode);
			continue;
		case '2':
			mode = 2;
			selectedMode = "Numbers_";
			cout << " Выбран режим: Числа";
			Sleep(1500);
			selectLevel(players, mode, selectedMode);
			continue;
		case '3':
			mode = 3;
			selectedMode = "Chars_";
			cout << " Выбран режим: Символы";
			Sleep(1500);
			selectLevel(players, mode, selectedMode);
			continue;
		case '0':
			openMenu();
			continue;
		default:
			selectMode(players);
			continue;
		}

	} while (option != '0');
}

void openMenu()
{
	system("cls");
	cout << " ---------------------------------------------------------" << endl;
	cout << " ---------------                       -------------------" << endl;
	cout << " ---------------      ИГРА МЕМОРИ      -------------------" << endl;
	cout << " ---------------                       -------------------" << endl;
	cout << " ---------------------------------------------------------" << endl;
	cout << " ---------------      ПРАВИЛА ИГРЫ     -------------------" << endl;
	cout << " ---------------------------------------------------------" << endl;
	cout << "    Мемори – игра на развитие памяти" << endl;
	cout << " 1.На экране появится картинка, нужно её запомнить." << endl;
	cout << " 2.Введите номер соответствующей картинки." << endl;
	cout << " 3.Если номер был выбран верно, то на экране после показа " << endl;
	cout << "   первой картинки появится вторая." << endl;
	cout << "   Запомни их и последовательно впиши номера этих картинок." << endl;
	cout << "   Если и на этот раз номера картинок были выбраны верно, " << endl;
	cout << "   то игра продолжается." << endl;
	cout << " 4.Если номер картинки(картинок) был указан неверно, " << endl;
	cout << "   то игра окончена." << endl;
	cout << " ---------------------------------------------------------" << endl;
	cout << " ---------------       МЕНЮ ИГРЫ       -------------------" << endl << endl;
	cout << " ---- НАЧАТЬ ИГРУ ОДНОМУ               - НАЖМИТЕ [1]    " << endl;
	cout << " ---- НАЧАТЬ ИГРУ ВДВОЕМ               - НАЖМИТЕ [2]    " << endl;
	cout << " ---- РЕЗУЛЬТАТЫ                       - НАЖМИТЕ [3]    " << endl;
	cout << " ---- ПОКИНУТЬ ИГРУ                    - НАЖМИТЕ [0]    " << endl;
	cout << " ---------------------------------------------------------" << endl;
	cout << " ---- СДЕЛАЙТЕ СВОЙ ВЫБОР И НАЖМИТЕ ENTER:  ";

	char option;
	char back;

	do
	{
		cout << " ";
		cin >> option;

		switch (option)
		{
		case '1':
			selectMode(1);
			break;
		case '2':
			selectMode(2);
			break;
		case '3':
			printRecords();

			cout << " Введите любой символ, чтобы вернуться в главное меню" << endl << " ";
			cin >> back;
			openMenu();
			break;
		case '0':
			break;
		default:
			openMenu();
			break;
		}

	} while (option != '0');

	cout << "Вы вышли из игры";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	openMenu();

	return 0;
}