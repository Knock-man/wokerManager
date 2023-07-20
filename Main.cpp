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
		printf("                       请输入操作：");
		int op;
		cin >> op;
		cout << endl;
		switch (op)
		{
		case 1: {
			wm.Add_Emp();//增加职工信息
			break;
		}
		case 2: {
			wm.Show_emp();//显示职工信息
			break;
		}
		case 3: {
			wm.Mod_Emp();//修改职工信息
			break;
		}
		case 4: {
			wm.Find_Emp();//查找职工信息
			break;
		}
		case 5: {
			wm.Del_emp();//删除职工信息
			break;
		}
		case 6: {
			wm.Sort_Emp();//按编号排序
			break;
		}
		case 7: {
			wm.Clean_File();//清空所有文档
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