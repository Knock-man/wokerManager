#include<iostream>
#include"Boss.h"
#include<string>
using namespace std;
//Boss类实现
//实现构造函数
Boss::Boss(int id, string name, int did) {
	m_Id = id;
	m_Name = name;
	m_DeptId = did;
}
//实现显示个人信息方法
void Boss::showInfo() {
	cout << "职工编号：" << this->m_Id << "\t职工姓名：" << this->m_Name << "\t岗位："
		<< this->getDeptName() << "\t岗位职责：管理公司所有事务" << endl;
}
//实现显示岗位名称方法
string Boss::getDeptName() {
	return "总裁";
}