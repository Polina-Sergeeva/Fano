#include <iostream>
#include <fstream>
#include <string>
#include "FanoEncoding.h"
#include "FanoDecoding.h"
#include <locale.h>
using namespace std;

int main(){
	setlocale(LC_ALL, "Russian");
	int input;
	cout << "Кодирование и декодирование с помощью алгоритма Фано" << endl;
	cout << "Введите 0, если хотите закодировать файл; введите 1, если хотите раскодировать файл" << endl;
	cin >> input;
	if (input == 0){
		cout << "Введите имя файла: " << endl;
		string s;
		cin >> s;
		FanoEncoding f;
		f.fanoEncoding(s);
		cout << "Файл закодирован. Название файла encoded." << endl;
	}
	else if (input == 1){
		cout << "Введите имя файла: " << endl;
		string s;
		cin >> s;
		FanoDecoding f2;
		f2.fanoDecoding(s);
		cout << "Файл раскодирован." << endl;
	}
	else{
		cout << "Неверный ввод" << endl;
	}
	system("pause");
	return 0;
}