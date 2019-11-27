#pragma once

#include<iostream>

using namespace std;

class SpaceshipModel  {
private:
	unsigned short int id;
	string name;
	string motherland;


public:
	void setId(unsigned short int ID) {
		this->id = ID;
	}
	unsigned short int getId() {
		return this->id;
	}

	void setName(string NAME) {
		this->name = NAME;
	}
	string getName() {
		return this->name;
	}

	void setMotherland(string M) {
		this->motherland = M;
	}
	string getMotherland() {
		return this->motherland;
	}

	SpaceshipModel() {
		this->id = 0;
		this->name = "";
		this->motherland = "";
	}
	SpaceshipModel(unsigned short int ID, string NAME, string MOTHERLAND) {
		this->id = ID;
		this->name = NAME;
		this->motherland = MOTHERLAND;
	}
};


