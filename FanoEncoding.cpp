#include "FanoEncoding.h"
#include <iostream>
#include <math.h>

FanoEncoding::FanoEncoding(){}

FanoEncoding::~FanoEncoding(){}

void FanoEncoding::fanoEncoding(string in_str){
	in.open(in_str, ios::binary);
	if (!in.is_open()){
		cout << endl << "Невозможно открыть файл";
		exit(1);
	}
	multimap<int, unsigned char> frequencies = countFrequencies();
	std::vector<ByteCode> byteCodes;
	for (std::multimap<int, unsigned char>::iterator it = frequencies.begin(); it != frequencies.end(); ++it){
		byteCodes.push_back(ByteCode(it->second, it->first));
	}
	makeCodes(0, byteCodes.size() - 1, byteCodes);
	ofstream out;
	out.open("encoded", ios::binary);
	writeToFile(out, byteCodes, in_str);
	in.close();
	out.close();
}

multimap<int, unsigned char> FanoEncoding::countFrequencies(){
	multimap<int, unsigned char> frequencies;
	vector<int> alf(256, 0);
	unsigned char a = in.get();
	while (!in.eof()){
		alf[a]++;
		a = in.get();
	}
	for (int i = 0; i < 256; i++){
		if (alf[i] != 0){
			frequencies.insert(make_pair(alf[i], i));
		}
	}
	return frequencies;
}

void FanoEncoding::makeCodes(int first, int last, std::vector<ByteCode>& byteCodes){
	if (first >= last){
		return;
	}
	if (first == last - 1){
		byteCodes[first].addCode('0');
		byteCodes[last].addCode('1');
	}
	int right = last;
	int left = first;
	int rightSum = byteCodes[right].getFrequency();
	int leftSum = byteCodes[left].getFrequency();
	while (left != right - 1){
		if (leftSum > rightSum){
			right--;
			rightSum += byteCodes[right].getFrequency();
		}
		else{
			left++;
			leftSum += byteCodes[left].getFrequency();
		}
	}
	for (int i = first; i <= left; i++){
		byteCodes[i].addCode('0');
	}
	for (int i = right; i <= last; i++){
		byteCodes[i].addCode('1');
	}
	makeCodes(first, left, byteCodes);
	makeCodes(right, last, byteCodes);
}

void FanoEncoding::writeToFile(ofstream &out, std::vector<ByteCode>& byteCodes, string&in_str){
	map<unsigned char, string> codesMap;
	for (std::vector<ByteCode>::iterator i = byteCodes.begin(); i != byteCodes.end(); ++i){
		codesMap.insert(std::make_pair(i->getByte(), i->getCode()));
	}
	string encoded;
	in.clear();
	in.seekg(0);
	unsigned char a = in.get();
	while (!in.eof()){
		std::map<unsigned char, string>::iterator it = codesMap.find(a);
		encoded += it->second;
		a = in.get();
	}
	for (int i = 0; i < 256; i++){
		std::map<unsigned char, string>::iterator it = codesMap.find(i);
		if (it != codesMap.end()){
			out << it->second;
		}
		else{
			out << " ";
		}
		out << "\n";
	}
	out << in_str;
	out << "\n";
	int no_read_bits = 0;
	while ((no_read_bits + encoded.size()) % 8 != 0)
		no_read_bits++;
	out << no_read_bits << "\n";
	int index = 0;
	for (size_t i = 0; i < (encoded.size() - (encoded.size() % 8)) / 8; i++, index += 8){
		out << stringToByte(index, index + 7, encoded);
	}
	if (no_read_bits != 0){
		out << stringToByte(index, encoded.size() - 1, encoded);
	}
}

unsigned char FanoEncoding::stringToByte(int first, int last, string& code){
	unsigned char res = 0;
	for (int i = first, j = 7; i <= last; i++, j--){
		if (code[i] == '1'){
			res += pow(2, j);
		}
	}
	return res;
}