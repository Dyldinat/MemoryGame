#include <iostream>
#include <Windows.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

void recordInList(unsigned long long gameTime, string mode) // запись результата
{
	void menu();

	string name;

	int minutes = gameTime / 60;
	int seconds = gameTime % 60;

	system("cls");
	cout << "Ваше время - " << minutes << " минут " << seconds << " секунд\n\n";
	cout << "Введите своё имя: ";
	cin >> name;

	ofstream out;

	out.open("G:/ОП/MemoryGame/Rating.txt", std::ios::binary | std::ios::app); // вписать путь до файла
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

	menu();
}

void printList() // вывод результатов
{
	ifstream in;
	string word;
	int counter = 1;

	system("cls");

	in.open("G:/ОП/MemoryGame/Rating.txt"); // вписать путь

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

void Play(int players, int mode, int speedLevel, int sequenceLength, string selectedMode)
{
	void menu();

	const int maxSequenceLength = 6;

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
	boolean gameOverPlayer[2] = { false, false };
	boolean winPlayer[2] = { false, false };
	int playerScore[2] = { 0, 0 };
	char option;

	in.open("G:/ОП/MemoryGame/Chars.txt"); // вписать путь
	if (in.is_open())
	{
		while (in >> read)
			VariantsPlayChars.push_back(read);
	}
	in.close();


	in.open("G:/ОП/MemoryGame/Words.txt"); // вписать путь
	if (in.is_open())
	{
		while (in >> read)
			VariantsPlayWords.push_back(read);
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
					if (players == 2)
						cout << "Попытка игрока " << p + 1 << endl;

					cout << "-----МЕМОРИ-----" << endl;
					cout << "----------------" << endl;
					cout << "Раунд " << round << endl;
					cout << j + 1 << ": " << Sequence[j];

					Sleep(speedLevel * 1000);
				}

				system("cls");
				if (players == 2)
					cout << "Попытка игрока " << p + 1 << endl;

				cout << "-----МЕМОРИ-----" << endl;
				cout << "----------------" << endl;
				cout << "Введите последовательность: " << endl;

				for (int i = 0; i < round; i++) // запись ответов в массив
					cin >> answers[i];

				for (int i = 0; i < round; i++) // проверка результатов
				{
					if (gameOverPlayer[p] == true)
						break;

					if (answers[i] != Sequence[i]) // при расхождении ответа с элементом последоваткльности выходим
					{
						gameOverPlayer[p] = true;

						if (players == 1)
							gameOverPlayer[1] = true;

						playerScore[p] = round - 1;
						round = 0;

						if (players == 2)
						{
							cout << "Игрок " << p + 1 << " не справился" << endl;

							if (gameOverPlayer[0] == true && gameOverPlayer[1] == false)
							{
								cout << "Введите 0 для старта хода следующего игрока" << endl;
								cin >> option;

								switch (option)
								{
								case '0':
									for (int i = 1; i < 4; i++)
									{
										cout << i;
										Sleep(1000);
									}
									cout << " --------------------- ИГРА НАЧАЛАСЬ --------------------- " << endl;
									Sleep(500);
									break;
								}
							}
							else
							{
								cout << "Введите 0 для продолжения" << endl;
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

						cout << "Игрок " << p + 1 << " успешло прошел раунд!" << endl;

						if (gameOverPlayer[0] == true && gameOverPlayer[1] == false)
						{
							cout << "Введите 0 для старта хода следующего игрока" << endl;
							cin >> option;

							switch (option)
							{
							case '0':
								for (int i = 1; i < 4; i++)
								{
									cout << i;
									Sleep(1000);
								}
								cout << " --------------------- ИГРА НАЧАЛАСЬ --------------------- " << endl;
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

						cout << "Игрок " << p + 1 << " успешло прошел раунд!" << endl;
						if (gameOverPlayer[0] == true && gameOverPlayer[1] == false)
						{
							cout << "Введите 0 для старта хода следующего игрока" << endl;
							cin >> option;

							switch (option)
							{
							case '0':
								for (int i = 1; i < 4; i++)
								{
									cout << i;
									Sleep(1000);
								}
								cout << " --------------------- ИГРА НАЧАЛАСЬ --------------------- " << endl;
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
					cout << "Правильно! Игра продолжается";

				round++;
			}
		}
	}

	if (gameOver) // завершение игры
	{
		if (players == 2)
		{
			system("cls");

			cout << "Счет игроков: " << playerScore[0] << ":" << playerScore[1] << endl;

			if (playerScore[0] > playerScore[1])
				cout << "Победил игрок 1" << endl;
			else if (playerScore[0] < playerScore[1])
				cout << "Победил игрок 2" << endl;
			else
				cout << "Ничья" << endl;

			cout << "Введите любой символ, чтобы вернуться в главное меню" << endl;
			cin >> option;

			switch (option)
			{
			default:
				menu();
				break;
			}
		}
		else
		{
			if (playerScore[0] == sequenceLength)
			{
				unsigned long long gameTime = (__rdtsc() - startTime) / 2160000000;

				system("cls");
				cout << "-----МЕМОРИ-----" << endl;
				cout << "----------------" << endl;
				cout << "Правильно! Вы выиграли!" << endl;
				cout << "Ваша последовательность:" << endl;
				for (int i = 0; i < maxSequenceLength; i++)
					cout << Sequence[i] << " ";
				cout << endl << "Время вашей игры: " << gameTime << " секунд" << endl;
				cout << "\nЖелаете сохранить свой результат?\n";
				cout << "\n1. Сохранить результат";
				cout << "\n0. Выход в главное меню\n";

				cin >> option;

				switch (option)
				{
				case '1':
					recordInList(gameTime, selectedMode);
					break;

				case '0':
					menu();
					break;
				}
			}
			else
			{
				cout << "Вы проиграли" << endl;
				cout << "Введите любой символ, чтобы вернуться в главное меню" << endl;
				cin >> option;

				switch (option)
				{
				case '0':
					menu();
					break;
				default:
					menu();
					break;
				}
			}
		}
	}
}

void selectSpeed(int players, int mode, int sequenceLength, string selectedMode)
{
	void selectLevel(int players, int mode, string selectedMode);

	char speedLevel;
	char option;

	system("cls");
	cout << "Выберите временной уровень сложности: " << endl;
	cout << "1. Лёгкий" << endl;
	cout << "2. Средний" << endl;
	cout << "3. Сложный" << endl;
	cout << "0. Назад к выбору длины" << endl;

	cin >> speedLevel;

	system("cls");
	cout << "Введите 0 для начала игры" << endl;
	cin >> option;

	switch (option)
	{
	case '0':
		cout << "3" << endl;
		Sleep(1000);
		cout << "2" << endl;
		Sleep(1000);
		cout << "1" << endl;
		Sleep(1000);
		break;
	}

	cout << " --------------------- ИГРА НАЧАЛАСЬ --------------------- " << endl;
	Sleep(500);


	switch (speedLevel)
	{
	case '1':
		cout << "Выбран уровень сложности: Лёгкий " << endl;
		speedLevel = 3;
		selectedMode += "Easy";
		Play(players, mode, speedLevel, sequenceLength, selectedMode);
		break;
	case '2':
		cout << "Выбран уровень сложности: Средний" << endl;
		speedLevel = 2;
		selectedMode += "Normal";
		Play(players, mode, speedLevel, sequenceLength, selectedMode);
		break;
	case '3':
		cout << "Выбран уровень сложности: Сложный" << endl;
		speedLevel = 1;
		selectedMode += "Hard";
		Play(players, mode, speedLevel, sequenceLength, selectedMode);
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

	cout << "Выберите длину" << endl;
	cout << "1 Четыре" << endl;
	cout << "2 Шесть" << endl;
	cout << "0. Назад к выбору режима" << endl;

	do
	{
		cin >> option;

		switch (option)
		{
		case '1':
			sequenceLength = 4;
			selectedMode += "4_";
			cout << endl << endl << " ВЫБРАНО: ДЛИНА ПОСЛЕДОВАТЕЛЬНОСТИ 4" << endl;
			cout << " Идет загрузка ";
			cout << " .";
			Sleep(1000);

			selectSpeed(players, mode, sequenceLength, selectedMode);

			continue;

		case '2':
			sequenceLength = 6;
			selectedMode += "6_";
			cout << endl << endl << " ВЫБРАНО: ДЛИНА ПОСЛЕДОВАТЕЛЬНОСТИ 6" << endl;
			cout << " Идет загрузка ";
			cout << " .";
			Sleep(1000);

			selectSpeed(players, mode, sequenceLength, selectedMode);

			continue;
		case '0':
			selectMode(players);
			continue;
		default:
			cout << endl << " Не правильно сделан выбор. Повторите попытку..." << endl;
			Sleep(500);
			selectLevel(players, mode, selectedMode);
			continue;
		}
	} while (option != '0');
}

void selectMode(int players) // для цифр/слов/символов
{
	void menu();

	char option;
	int mode;
	string selectedMode;

	system("cls");
	cout << "Выберите режим" << endl;
	cout << "1. Слова" << endl;
	cout << "2. Числа" << endl;
	cout << "3. Символы" << endl;
	cout << "0. Вернуться в меню" << endl;

	do
	{
		cin >> option;

		switch (option)
		{
		case '1':
			mode = 1;
			selectedMode = "Strings_";
			selectLevel(players, mode, selectedMode);
			continue;
		case '2':
			mode = 2;
			selectedMode = "Numbers_";
			selectLevel(players, mode, selectedMode);
			continue;
		case '3':
			mode = 3;
			selectedMode = "Chars_";
			selectLevel(players, mode, selectedMode);
			continue;
		case '0':
			menu();
			continue;
		default:
			selectMode(players);
			continue;
		}

	} while (option != '0');
}

void menu()
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
	cout << "1.На экране появится картинка, нужно её запомнить." << endl;
	cout << "2.Введите номер соответствующей картинки." << endl;
	cout << "3.Если номер был выбран верно, то на экране после показа " << endl;
	cout << "  первой картинки появится вторая." << endl;
	cout << "  Запомни их и последовательно впиши номера этих картинок." << endl;
	cout << "  Если и на этот раз номера картинок были выбраны верно, " << endl;
	cout << "  то игра продолжается." << endl;
	cout << "4.Если номер картинки(картинок) был указан неверно, " << endl;
	cout << "  то игра окончена." << endl;
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
			printList();

			cout << "\nВведите 0, чтобы вернуться в главное меню\n";
			cin >> back;

			if (back == '0')
				break;
		case '0':
			break;
		default:
			menu();
			break;
		}

	} while (option != '0');

	cout << "Вы вышли из игры";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	menu();

	return 0;
}
