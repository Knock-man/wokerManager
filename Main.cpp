#include<iostream>
#include"wokerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
using namespace std;
int main() {
	WokerManager wm;
	while (1) {
		wm.MenuPrint();
		printf("                       �����������");
		int op;
		cin >> op;
		cout << endl;
		switch (op)
		{
		case 1: {
			wm.Add_Emp();//����ְ����Ϣ
			break;
		}
		case 2: {
			wm.Show_emp();//��ʾְ����Ϣ
			break;
		}
		case 3: {
			wm.Mod_Emp();//�޸�ְ����Ϣ
			break;
		}
		case 4: {
			wm.Find_Emp();//����ְ����Ϣ
			break;
		}
		case 5: {
			wm.Del_emp();//ɾ��ְ����Ϣ
			break;
		}
		case 6: {
			wm.Sort_Emp();//���������
			break;
		}
		case 7: {
			wm.Clean_File();//��������ĵ�
			break;
		}
		default:
			wm.exitSystem();
			break;
		}
		system("cls");
	}
	cin.get();
	return 0;
}