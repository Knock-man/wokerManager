#include<iostream>
#include"Manager.h"
#include<string>
using namespace std;
//employee��ʵ��
// 
//ʵ�ֹ��캯��
Manager::Manager(int id, string name, int did) {
	m_Id = id;
	m_Name = name;
	m_DeptId = did;
}
//ʵ����ʾ������Ϣ����
void Manager::showInfo() {
	cout << "ְ����ţ�" << this->m_Id << "\tְ��������" << this->m_Name << "\t��λ��"
		<< this->getDeptName() << "\t��λְ������ϰ彻���ĸ������񣬲��·������Ա��" << endl;
}
//ʵ����ʾ��λ���Ʒ���
string Manager::getDeptName() {
	return "����";
}