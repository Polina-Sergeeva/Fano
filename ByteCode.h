#ifndef BYTE_CODE
#define BYTE_CODE

#include <vector>
#include <string>

class ByteCode{
private:
	char byte;
	int freq;
	std::string code;
public:
	ByteCode(char b, int f) : byte(b), freq(f){}
	char getByte(){
		return byte;
	}
	int getFrequency(){
		return freq;
	}
	std::string getCode(){
		return code;
	}
	void addCode(int c){
		code.push_back(c);
	}
	~ByteCode(){}
};
#endif