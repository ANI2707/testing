#include <iostream>
#include <fstream>

using namespace std;

class MyFile {
	char buffer[40], fname[10];
	int roll, count;
	string name, address;
	fstream file;
public:
	MyFile(){
		roll = 0;
		count = 0;
		name = '\0';
		address = '\0';
		cout << "Enter name of file : ";
		cin >> fname;
	}
	~MyFile() {
		remove("file");
	}
	void writeFile();
	void readFile();
	void searchRecord();
	void deleteRecord();
};

void MyFile :: writeFile() {
	file.open(fname, ios::out);

	if(!file)
		cout << "\n\nThere is an Error Opening file..." << endl;
	else {
		cout << "Enter number of records : " ;
		cin >> count;
		for(int i=0; i<count; i++) {
			cout << "Roll number : ";
			cin >> roll;
			cout << "Name : ";
			cin >> name;
			cout << "Address : ";
			cin >> address;
			file << roll << " " << name << " " << address << endl;
		}
	}
	file.close();
}

void MyFile :: searchRecord() {
	file.open(fname, ios::in);
	if(!file)
		cout << "\n\nError 404 File Not Found..." << endl;
	else {
		string temp;
		cout << "Enter Roll No to Search : ";
		cin >> temp;
		while(!file.eof()) {
			file.getline(buffer, 40);
			string a;
			a += buffer[0];
			a += buffer[1];
			if(temp == a){
				cout << "Record Found" << endl << buffer;
				return;
			}
		}
		cout << "Record Not Found!!!";
	}
	file.close();
}

void MyFile :: readFile() {
	file.open(fname, ios::in);
	if(!file)
		cout << "\n\nError 404 File Not Found..." << endl;
	else {
		int i=0;
		while(!file.eof()) {
			file.getline(buffer, 40);
			cout << "Record " << i << " : " << buffer << endl;
			i++;
		}
	}
	file.close();
}

void MyFile :: deleteRecord() {
	fstream tempfile;
	tempfile.open("TempFile.txt", ios::out);
	file.open(fname, ios::in);
	if(!file)
		cout << "\n\nError 404 File Not Found..." << endl;
	else {
		string temp;
		cout << "Enter Roll No to Search : ";
		cin >> temp;
		while(!file.eof()) {
			file.getline(buffer, 40);
			string a;
			a += buffer[0];
			a += buffer[1];
			if(temp == a)
				cout << "Record Deleted" << endl << buffer << endl;
			else
				tempfile << buffer << endl;
		}
	}
	file.close();
	tempfile.close();

	tempfile.open("TempFile.txt", ios::in);
	file.open(fname, ios::out);
	if(!file)
		cout << "\n\nThere is an Error Opening file..." << endl;
	else {
		while(!tempfile.eof()) {
			tempfile.getline(buffer, 40);
			file << buffer << endl;
		}
	}
	file.close();
	tempfile.close();

	cout << "Updated File is : " << endl;
	readFile();

	remove("TempFile.txt");
}

int main() {
	MyFile file;

//	file.writeFile();

//	file.readFile();

//	file.searchRecord();

	file.deleteRecord();

	return 0;
}

