#include <string>
#include <fstream>
#include <map>
using namespace std;

class FanoDecoding{
private:
	ifstream in;
	map<string, unsigned char> getTable();
	void writeToFile(ofstream& out, map<string, unsigned char>& table);
	string byteToStr(unsigned char byte);
public:
	FanoDecoding();
	~FanoDecoding();
	void fanoDecoding(string s);
};