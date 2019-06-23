#include <iostream>
#include <map> //���������� ��� ������������� ���� � ������� ������� � �������
#include <algorithm>//����������, ���������� �������������� ������� ������ � ������
#include <windows.h>
#include <stdlib.h>
#include <string>

using namespace std;


void Team_input(map<string, string>&);//������� ���������� ����� �������
void player_input(map<string, string>&, map<string, string>&);//������� ���������� ������ ������
string Heshing_player(string, string);//������� ����������� ���� �������
string Heshing_team(string);//������� ����������� �������� ������


int main()
{
	bool active = true;
	int chs_v;
	map<string, string> Team_list;//��� ��� ���������� �������� ������ � �����
	map<string, string> Player_list;//��� ��� ���������� ���� ������� � �����
	std::map<string, string>::iterator for_team, for_player;//���� ���������� ��� ����������� �����

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
			Team_input(Team_list);//������� ���������� �������� ������
			break;
		case 2:
			player_input(Team_list, Player_list);//������� ���������� ���� �������
			break;
		case 3://����� ������ ������ � �������
			system("cls");
			cout << "The list of teams: " << endl;
			for (for_team = Team_list.begin(); for_team != Team_list.end(); for_team++)//������ ��������� ��� ������ ������ ���� ���������
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
		case 4://����� �� ���������
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




void Team_input(map<string, string>& Team_nm)//�������� ������� ���������� �������� ������
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
	for_hs = Heshing_team(team);//����� ������� �����������
	map<string, string>::iterator it = Team_nm.find(team);
	if (it != Team_nm.end())//�������� �� ������� ������ �������� ������
	{
		cout << "Error" << endl;
		cout << "Already have such a team: " << it->first << endl;
		Sleep(3000);
	}
	else
	{
		Team_nm.insert(make_pair(team, for_hs));//���������� ������ �������� �������
		cout << "Added successfuly." << endl;
		Sleep(2000);
	}

	system("cls");
}


string Heshing_team(string Team_nm)//�������� ������� ����������� ������
{
	string hsh;
	string et_t_h;
	long int code;
	et_t_h = "";
	for (int i = 0; i < Team_nm.length(); i++)//���� � ������ �������� ������ ������ ������
	{
		code = (int)(Team_nm[i]);//��������� ���� ���������� �������
		if (i % 2 == 0)//��������������� �������� ������� ������� ���� �������
			reverse(et_t_h.begin(), et_t_h.end());
		et_t_h += to_string(code);//������ ��������� ����
	}
	reverse(et_t_h.begin(), et_t_h.end());//��������������� ��������� ���� �������
	return et_t_h;//����������� �������� ����
}


string Heshing_player(string book_title, string aut_kode)//�������� ����������� ���� �������
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
	aut_kode.resize(7);//���������� 7 ��������� ���� �������, � ������� ��������� �����
	et_t_h += aut_kode;
	reverse(et_t_h.begin(), et_t_h.end());
	return et_t_h;
}


void player_input(map<string, string>& team_nm, map<string, string>& player_nm)//�������� ���������� ����� �������
{
	string team;
	string player;
	string for_hs;
	string for_bk;
	bool otv_q = true;
	char otv;

	cout << "Input the football team name." << endl;//���� ������� ������������ ������
	cout << endl;
	cout << "> ";
	cin.ignore(1024, '\n');
	std::getline(std::cin, team);
	Sleep(500);
	system("cls");

	for_hs = Heshing_team(team);//����������� �������� ������, ��� �������� ��� �������
	map<string, string>::iterator it = team_nm.find(team);
	if (it != team_nm.end())
	{
		cout << "Input the player`s name" << endl;//���� ������� ����, ���� ����� ������
		cout << endl;
		cout << "> ";
		std::getline(std::cin, player);
		for_bk = Heshing_player(player, for_hs);//����� ������� ����������� ������
		Sleep(500);

		map<string, string>::iterator it_bk = player_nm.find(player);
		if (it_bk != player_nm.end())
		{//�������� �� ������� ������ � ����� ������
			cout << "Already have such the player: " << it->first << endl;
			Sleep(3000);
			system("cls");
			return;
		}
		else
		{//���������� � ��� ���� � ����� ������
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
		{//��������� ������� � ����������� ���������� ����� ������� ������
			system("cls");
			cout << "This team is not listed." << endl;
			cout << "Do you want to add it and continue work?(Y/N)" << endl;
			cout << endl;
			cout << "> ";
			cin >> otv;
			switch (otv)
			{
			case 'Y'://�������, ����� ������������ ����������� � ������� �����������
				system("cls");
				team_nm.insert(make_pair(team, for_hs));
				cout << "Added successfuly." << endl;
				Sleep(2000);
				system("cls");
				otv_q = false;
				break;
			case 'N'://�������, ����� ������������ ���������� ������ ��-�� ������ �������� �������
				system("cls");
				return;
				otv_q = false;
				break;
			default://���������� ������ ������ �����
				system("cls");
				cout << "Error. Incorrect symbol." << endl;
				Sleep(2000);
				system("cls");
			}
		}
		//���� ������, ���� ������� ����
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