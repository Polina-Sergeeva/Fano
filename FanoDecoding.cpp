#include "FanoDecoding.h"
#include <iostream>

FanoDecoding::FanoDecoding(){}

FanoDecoding::~FanoDecoding(){}

void FanoDecoding::fanoDecoding(string s){
	in.open(s, ios::binary);
	map<string, unsigned char> table = getTable();
	ofstream out;
	writeToFile(out, table);
	in.close();
	out.close();
}

map<string, unsigned char> FanoDecoding::getTable(){
	map<string, unsigned char> table;
	for (int i = 0; i < 256; i++){
		string s;
		getline(in, s, '\n');
		if (s != " "){
			table.insert(make_pair(s, i));
		}
	}
	return table;
}

void FanoDecoding::writeToFile(ofstream& out, map<string, unsigned char>& table){
	string uncoded, in_str, s;
	getline(in, in_str, '\n');
	int noReadBits = in.get() - '0';
	in.get();
	while (!in.eof()){
		unsigned char const a = in.get();
		if (!in.eof()){
			s = byteToStr(a);
			for (size_t i = 0; i < s.size(); i++){
				uncoded.push_back(s[i]);
			}
			s.clear();
		}
	}
	s.clear();
	out.open(in_str, ios::binary);
	std::map<std::string, unsigned char>::iterator it;
	for (size_t i = 0; i < uncoded.size() - noReadBits; i++){
		s.push_back(uncoded[i]);
		it = table.find(s);
		if (it != table.end()){
			out << it->second;
			s.clear();
		}
	}
}

string FanoDecoding::byteToStr(unsigned char byte){
	std::string res(8, '0');
	unsigned char r;
	int i = 0;
	while (byte >= 2){
		r = byte % 2;
		byte = (byte - r) / 2;
		if (r == 1)
			res[7 - i] = '1';
		else
			res[7 - i] = '0';
		i++;
	}
	if (byte == 1)
		res[7 - i] = '1';
	else
		res[7 - i] = '0';
	return res;
}