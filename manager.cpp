#include<iostream>
#include"Manager.h"
#include<string>
using namespace std;
//employee类实现
// 
//实现构造函数
Manager::Manager(int id, string name, int did) {
	m_Id = id;
	m_Name = name;
	m_DeptId = did;
}
//实现显示个人信息方法
void Manager::showInfo() {
	cout << "职工编号：" << this->m_Id << "\t职工姓名：" << this->m_Name << "\t岗位："
		<< this->getDeptName() << "\t岗位职责：完成老板交代的各项任务，并下发任务给员工" << endl;
}
//实现显示岗位名称方法
string Manager::getDeptName() {
	return "经理";
}