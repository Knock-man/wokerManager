#pragma once
#include<iostream>
#include<string>
#include"worker.h"
using namespace std;
//��ͨԱ��������
class Employee:public worker {
public:
	//���캯��
	Employee(int id, string name, int did);
	//��ʾ��λ��Ϣ
	void showInfo();
	//��ȡ��λ����
	string getDeptName();
};
