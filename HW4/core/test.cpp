#include<iostream>
#include<fstream>
using namespace std;
void main3() {
	fstream file;
	char buffer[200];
	int x[200];
	int x_count = 0;
	char* pStart = buffer;

	char* pEnd;
	char* pEnd_1;
	char* pEnd_2;

	int d;
	file.open("GroundTruth_1.txt", ios::in);
	if (!file)
		cout << "無法開啟檔案!\n";
	else {


		do {
			file.getline(buffer, sizeof(buffer));
			int d1, d2,d3,d4;
			d1 = strtod(buffer, &pEnd);
			d2 = strtod(pEnd, &pEnd_1);
			d3 = strtod(pEnd_1, &pEnd_2);
			d4 = strtod(pEnd_2,NULL);
			printf("%d\n", d1);
		} while (!file.eof());
		file.close();
	}

	system("pause");
}
