#pragma once
#include<iostream>
#include<string>
#include"worker.h"
using namespace std;
//经理类声明
class Manager:public worker {
public:
	//构造函数
	Manager(int id, string name, int did);
	//显示岗位信息
	void showInfo();
	//获取岗位名称
	string getDeptName();
};