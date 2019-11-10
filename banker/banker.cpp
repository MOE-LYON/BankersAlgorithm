// banker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<vector>
#include<string>

using namespace std;


class Process
{
private:
	int N;  // resource number
	vector<int> Need, Max, Allocation;
public:
	void init(int m) {
		N = m;
		Need.resize(m);
		Max.resize(m);
		Allocation.resize(m);
		
		cout << "Please Enter the Allocation " << m <<" \n";
		for (auto & i : Allocation) {
			cin >> i;
		}

		cout << "Please Enter the Max " << m << " \n";
		for (auto & i : Max) {
			cin >> i;
		}

		for (int i = 0; i < m; ++i) {
			Need[i] = Max[i] - Allocation[i];
		}
	};

	bool CanAllocation(vector<int> req);

	void ChangeData(vector<int> req);

	void Restore(vector<int> req);
	vector<int> GetAllocation() {
		return Allocation;
	}
	bool compare(vector<int> worker) {
		for (int i = 0; i < worker.size(); ++i) {
			if (worker[i] < Need[i]) return false;
		}

		return true;
	}
	string toString() {
		string res = "";

		for (size_t i = 0; i < Allocation.size(); i++)
		{
			res += (to_string(Allocation[i]) + " ");
		}
		res += "  ";
		for (size_t i = 0; i < Max.size(); i++)
		{
			res += (to_string(Max[i]) + " ");
		}
		
		return res;
	}
	

};

vector<Process> processes; // ��������
vector<int> Available; //��Դ�ɷ�������
int n; //������
int m; // ��Դ��

bool Process::CanAllocation(vector<int> req) {

	for (int i = 0; i < req.size(); ++i)
	{
		if (req[i] > Need[i])
		{
			cout << "����" << i << "�������Դ��������Ҫ����Դ";
			cout << "���䲻�����������!" << endl;
			return false;
		}
		else if (req[i] > Available[i])
		{
			cout << "����" << i << "�������Դ����ϵͳ�����õ���Դ";
			cout << "�������,�������!" << endl;
			return false;
		}

	}
	return true;

}

void Process::ChangeData(vector<int> req) {
	for (int j = 0; j < req.size(); j++)
	{
		Available[j] -= req[j];
		Allocation[j] += req[j];
		Need[j] -= req[j];
	}

}
void Process::Restore(vector<int> req) {
	for (int j = 0; j < req.size(); j++)
	{
		Available[j] += req[j];
		Allocation[j] -= req[j];
		Need[j] += req[j];
	}
}
void init() {
	cout << "Please Enter the num of processes" << endl;

	cin >> n;
	processes.resize(n);

	cout << "Please Enter the number of  resources" << endl;
	
	cin >> m;
	Available.resize(m);
	for (auto& el : processes)
	{
		el.init(m);
	}

	cout << "Please Enter the resoures available " << m << endl;
	for (auto & i : Available) {
		cin >> i;
	}
}

void printProcess() {
	cout << "Processes info" << endl;
	for (auto p : processes)
	{
		cout << p.toString() << endl;
	}
	cout << endl;
	cout << "Availabe" << endl;
	for (auto ava : Available) {
		cout << ava << " ";
	}
	cout << endl<<endl;
}

bool safe() {
	vector<bool> finish(n, false);
	vector<int> worker = Available;
	vector<int> safeorder(0);
	for (int k = 0; k < n; ++k) { //ȫ�̼�����Դ 

		for (int i = 0; i < n; ++i) {
			if (finish[i])continue;

			if (processes[i].compare(worker)) {
				finish[i] = true;
				safeorder.push_back(i);
				vector<int> all = processes[i].GetAllocation();

				for (int e = 0; e < worker.size(); ++e) {
					worker[e] += all[e];
				}

				break;
			}

		}
	}
	

	for (int i = 0; i < n; ++i)
	{

		if (finish[i] == false)
		{
			cout << "ϵͳ����ȫ!!! ������Դ���벻�ɹ�!!!" << endl;
			return false;
		}
	}

	cout << "����ȫ�Լ�飬ϵͳ��ȫ�����η���ɹ�!!" << endl;
	cout << "��ȫ���к� ";
	for (int i = 0; i < safeorder.size(); ++i)
	{
		cout << "P" << safeorder[i] << ", ";
		if (i == safeorder.size() - 1) cout << endl;
	}
		
	


	cout << endl;

	return true;
}

bool request() {
	int i;
	cout << "��������Ҫ�������Դ���̺�(0-" << n - 1 << "):" << endl;
	cin >> i;
	cout << "���������" << i << "����Request����" << endl;
	vector<int> req(m);
	for (auto & i :req)
	{
		cin >> i;
	}
	if (!processes[i].CanAllocation(req)) {
		return false;
	}

	processes[i].ChangeData(req);

	if (!safe()) {
		
		processes[i].Restore(req);
		return false;
	}
	printProcess();
	return true;
}

int main() {

	init();
	if (!safe()) {
		cout << "init failed" << endl;
		return 0;
	}
	printProcess();
	while (true) {
		int x;
		cout << "1 Request" << endl;
		cout << "2 print processes info" << endl;
		cout << "0 Exit System" << endl;

		cin >> x;
		switch (x)
		{
		case 1:
			request();
			break;
		case 2:
			printProcess();
			break;
		case 0:
			exit(0);
		default:
			cout << "invalid input Please input again" << endl;
			break;
		}
	}
	return 0;
}