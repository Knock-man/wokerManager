#pragma once
#include<iostream>
#include<string>
#include"worker.h"
using namespace std;
//普通员工类声明
class Employee:public worker {
public:
	//构造函数
	Employee(int id, string name, int did);
	//显示岗位信息
	void showInfo();
	//获取岗位名称
	string getDeptName();
};
