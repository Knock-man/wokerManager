#include<iostream>
#include"employee.h"
#include<string>
using namespace std;
//employee��ʵ��
// 
//ʵ�ֹ��캯��
Employee::Employee(int id, string name, int did) {
	m_Id = id;
	m_Name = name;
	m_DeptId = did;
}
//ʵ����ʾ������Ϣ����
void Employee::showInfo() {
	cout << "ְ����ţ�" << this->m_Id << "\tְ��������" << this->m_Name << "\t��λ��" 
		<< this->getDeptName() << "\t��λְ����ɾ������ĸ�������" << endl;
}
//ʵ����ʾ��λ���Ʒ���
string Employee::getDeptName() {
	return "Ա��";
}