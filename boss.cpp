#include<iostream>
#include"Boss.h"
#include<string>
using namespace std;
//Boss��ʵ��
//ʵ�ֹ��캯��
Boss::Boss(int id, string name, int did) {
	m_Id = id;
	m_Name = name;
	m_DeptId = did;
}
//ʵ����ʾ������Ϣ����
void Boss::showInfo() {
	cout << "ְ����ţ�" << this->m_Id << "\tְ��������" << this->m_Name << "\t��λ��"
		<< this->getDeptName() << "\t��λְ�𣺹���˾��������" << endl;
}
//ʵ����ʾ��λ���Ʒ���
string Boss::getDeptName() {
	return "�ܲ�";
}