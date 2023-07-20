#pragma once
#include<iostream>
#include"worker.h"
#include<fstream>//文件操作
const string FILENAME = "empFile.txt";
using namespace std;
//职工管理类(打印菜单，退出功能)
class WokerManager {
public:
	WokerManager();
	~WokerManager();
	void MenuPrint();//打印菜单函数
	void exitSystem();//退出函数
	void Add_Emp();//添加员工函数
	void save();//保存文件函数
	int get_EmpNum();//统计文件中的人数
	void init_Emp();//初始化员工
	void Show_emp();//显示职工
	void Del_emp();//删除职工
	int IsExist(int id);//判断职工是否存在
	void Mod_Emp();//修改职工
	void Find_Emp();//查找
	void Sort_Emp();//排序
	void Clean_File();//清空

	int m_EmpNum;//维护职工数目
	worker** m_EmpArray;
	bool m_FilesIsEmpty;//判断文件是否为空
};
