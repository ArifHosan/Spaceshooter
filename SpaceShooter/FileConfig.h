#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;
class FileConfig
{
public:
	FileConfig();

	pair<string, string> getConfig();

	void setConfig(string name, string value);

	~FileConfig();
	
};

