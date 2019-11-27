#include "FileConfig.h"
using namespace std;

FileConfig::FileConfig() {
}

pair<string, string> FileConfig::getConfig(){
	string s;
	ifstream file("config.ini");
	while (getline(file, s)) {
		//cout << s << endl;
		stringstream ss;
		ss << s;
		pair<string, string> c;
		ss >> c.first;
		ss >> c.second;
		file.close();
		return c;
	}
	//return pair<string, string>();
}

void FileConfig::setConfig(string name, string value) {
	string s;
	vector<string>V;
	ifstream file("config.ini");
	while (getline(file, s)) {
		//cout << s << endl;
		stringstream ss;
		ss << s;
		pair<string, string> c;
		ss >> c.first;
		ss >> c.second;
		if (c.first == name) {
			c.second = value;
			s = c.first + " " + c.second;
		}
		V.push_back(s);
	}
	file.close();
	ofstream myfile;
	myfile.open("config.ini");
	for (int i = 0; i < V.size(); i++) {
		myfile << V[i] << "\n";
	}
	myfile.close();
}

FileConfig::~FileConfig() {}
