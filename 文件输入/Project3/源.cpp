#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main() {
	char buffer[256];
	ifstream myfile("./save.txt");


	if (!myfile) {
		cout << "Unable to open myfile";
		exit(1); // terminate with error

	}
	
	//int a, b;
	int i = 0, j = 0;
	int data[6];
	char str[15];

	while (!myfile.eof())
	{
		myfile.getline(buffer, 10);
		sscanf_s(buffer, "%d-%s",&data[i],str,sizeof(str));
		cout << data[i] << str << endl;
	//	data[i][0] = a;
	//	data[i][1] = b;
		i++;
	}
	myfile.close();
	getchar();
	ofstream outfile("./save.txt");
	if (!outfile) {
		cout << "Unable to open otfile";
		exit(1); // terminate with error

	}
	/*for (int k = 0; k < i; k++) {
		
		cout << data[k][0] << " " << data[k][1] << endl;
	}*/
	outfile << "5553-sdf" << endl;
	outfile.close();
//	cout << buffer[1];
	getchar();
	return 0;
}
