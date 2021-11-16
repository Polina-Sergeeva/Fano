#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <utility>
#include "ByteCode.h"
using namespace std;

class FanoEncoding{
private:
	ifstream in;
	multimap<int, unsigned char> countFrequencies();
	void makeCodes(int first, int last, std::vector<ByteCode>& byteCodes);
	void writeToFile(ofstream &out, std::vector<ByteCode>& byteCodes, string& in_str);
	unsigned char stringToByte(int first, int last, string& code);
public:
	FanoEncoding();
	~FanoEncoding();
	void fanoEncoding(string in_str);
};