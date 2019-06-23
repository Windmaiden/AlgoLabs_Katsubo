#include <iostream>
#include <map> //Библиотека для использования мапа и базовых методов и функций
#include <algorithm>//Библиотека, включающая дополнительные функции работы с мапами
#include <windows.h>
#include <stdlib.h>
#include <string>

using namespace std;


void Team_input(map<string, string>&);//фукнция добавления новой команды
void player_input(map<string, string>&, map<string, string>&);//функция добавления нового игрока
string Heshing_player(string, string);//Функция хеширования имен игроков
string Heshing_team(string);//фукнция хеширования названий команд


int main()
{
	bool active = true;
	int chs_v;
	map<string, string> Team_list;//мап для сохранения названий команд и хешей
	map<string, string> Player_list;//мап для сохранения имен игроков и хешей
	std::map<string, string>::iterator for_team, for_player;//пара итераторов для прохождения мапов

	while (active)
	{
		cout << "Select the type of input value:" << endl;
		cout << "1. Football team" << endl;
		cout << "2. Player" << endl;
		cout << "3. Show all elements" << endl;
		cout << "4. Exit" << endl;
		cout << endl;
		cout << "> ";
		cin >> chs_v;
		Sleep(500);
		system("cls");
		switch (chs_v)
		{
		case 1:
			Team_input(Team_list);//Функция добавления названий команд
			break;
		case 2:
			player_input(Team_list, Player_list);//Функция добавления имен игроков
			break;
		case 3://Вывод списка команд и игроков
			system("cls");
			cout << "The list of teams: " << endl;
			for (for_team = Team_list.begin(); for_team != Team_list.end(); for_team++)//Проход итератора для вывода каждой пары элементов
				cout << for_team->first << " : " << for_team->second << endl;
			cout << endl;
			cout << "The list of players: " << endl;
			for (for_player = Player_list.begin(); for_player != Player_list.end(); for_player++)
				cout << for_player->first << " : " << for_player->second << endl;
			cout << endl;
			system("pause");
			Sleep(500);
			system("cls");
			break;
		case 4://Выход из программы
			active = false;
			cout << "Closing the program." << endl;
			Sleep(1500);
			break;
		default:
			cout << endl;
			cout << "Error. Select one of the suggested values." << endl;
			cout << endl;
			Sleep(3000);
			system("cls");
			break;
		}

	}

	return 0;
}




void Team_input(map<string, string>& Team_nm)//Описание функции добавления названий команд
{
	string team;
	string for_hs;

	cout << "Input the football team name." << endl;
	cout << endl;
	cout << "> ";
	cin.ignore(1024, '\n');
	std::getline(std::cin, team);
	Sleep(500);
	system("cls");
	for_hs = Heshing_team(team);//Вызов функции хеширования
	map<string, string>::iterator it = Team_nm.find(team);
	if (it != Team_nm.end())//Проверка на наличие такого названия команд
	{
		cout << "Error" << endl;
		cout << "Already have such a team: " << it->first << endl;
		Sleep(3000);
	}
	else
	{
		Team_nm.insert(make_pair(team, for_hs));//Добавление нового названия команды
		cout << "Added successfuly." << endl;
		Sleep(2000);
	}

	system("cls");
}


string Heshing_team(string Team_nm)//Описание функции хеширования команд
{
	string hsh;
	string et_t_h;
	long int code;
	et_t_h = "";
	for (int i = 0; i < Team_nm.length(); i++)//Цикл с числом итераций равным длинне строки
	{
		code = (int)(Team_nm[i]);//Получение кода конкретнго символа
		if (i % 2 == 0)//Переворачивание значения каждого второго кода символа
			reverse(et_t_h.begin(), et_t_h.end());
		et_t_h += to_string(code);//Сборка конечного хеша
	}
	reverse(et_t_h.begin(), et_t_h.end());//Переворачивание конечного хеша команды
	return et_t_h;//Возвращение значения хеша
}


string Heshing_player(string book_title, string aut_kode)//Описание хеширования имен игроков
{
	string hsh;
	string et_t_h;
	int hlp;
	long int code;
	et_t_h = "";
	for (int i = 0; i < book_title.length(); i++)
	{
		code = (int)(book_title[i]);
		if (i % 2 == 0)
			reverse(et_t_h.begin(), et_t_h.end());
		et_t_h += to_string(code);
	}
	aut_kode.resize(7);//Добавление 7 элементов хеша команды, к которой относится игрок
	et_t_h += aut_kode;
	reverse(et_t_h.begin(), et_t_h.end());
	return et_t_h;
}


void player_input(map<string, string>& team_nm, map<string, string>& player_nm)//Описание добалвения новых игроков
{
	string team;
	string player;
	string for_hs;
	string for_bk;
	bool otv_q = true;
	char otv;

	cout << "Input the football team name." << endl;//Ввод команды добавляемого игрока
	cout << endl;
	cout << "> ";
	cin.ignore(1024, '\n');
	std::getline(std::cin, team);
	Sleep(500);
	system("cls");

	for_hs = Heshing_team(team);//Хеширование названия команд, для проверки его наличия
	map<string, string>::iterator it = team_nm.find(team);
	if (it != team_nm.end())
	{
		cout << "Input the player`s name" << endl;//Если команда есть, ввод имени игрока
		cout << endl;
		cout << "> ";
		std::getline(std::cin, player);
		for_bk = Heshing_player(player, for_hs);//Вызов фукнции хеширования игрока
		Sleep(500);

		map<string, string>::iterator it_bk = player_nm.find(player);
		if (it_bk != player_nm.end())
		{//Проверка на наличие игрока с таким именем
			cout << "Already have such the player: " << it->first << endl;
			Sleep(3000);
			system("cls");
			return;
		}
		else
		{//Добавление в мап хеша и имени игрока
			player_nm.insert(make_pair(player, for_bk));
			system("cls");
			cout << "Added successfuly." << endl;
			Sleep(2000);
			system("cls");
			return;
		}
	}
	else
	{
		while (otv_q)
		{//Отсутсвие команды и предложение добавления новой команды игрока
			system("cls");
			cout << "This team is not listed." << endl;
			cout << "Do you want to add it and continue work?(Y/N)" << endl;
			cout << endl;
			cout << "> ";
			cin >> otv;
			switch (otv)
			{
			case 'Y'://Вариант, когда пользователь соглашается и команда добавляется
				system("cls");
				team_nm.insert(make_pair(team, for_hs));
				cout << "Added successfuly." << endl;
				Sleep(2000);
				system("cls");
				otv_q = false;
				break;
			case 'N'://Вариант, когда прекращается добавление игрока из-за отказа добавить команду
				system("cls");
				return;
				otv_q = false;
				break;
			default://Обработчик ошибок левого ввода
				system("cls");
				cout << "Error. Incorrect symbol." << endl;
				Sleep(2000);
				system("cls");
			}
		}
		//Ввод игрока, если комнада есть
		cout << "Input the player`s name" << endl;
		cout << endl;
		cout << "> ";
		cin.ignore(1024, '\n');
		std::getline(std::cin, player);
		for_bk = Heshing_player(player, for_hs);
		Sleep(500);

		map<string, string>::iterator it_bk = player_nm.find(player);
		if (it_bk != player_nm.end())
		{
			system("cls");
			cout << "Already have such the player: " << it_bk->first << endl;
			Sleep(3000);
			system("cls");
			return;
		}
		else
		{
			system("cls");
			player_nm.insert(make_pair(player, for_bk));
			cout << "Added successfuly." << endl;
			Sleep(2000);
			system("cls");
			return;
		}

	}


}