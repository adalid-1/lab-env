using namespace std;
//#include "Header.h"
#include <iostream>
#include "Vector4D.h"
#include "Matrix4D.h"
#include "Math.h"



int main()
{
	cout << "Hello World \n";
	class bulle {
	public:
			float bullen[4][4];

			bulle(void)
			{
				bullen[0][2] = 13.0f;

			}


			float& operator()(const int i, const int d)
			{
				return bullen[i][d];
			}

		
	};


	bulle gofika;
	float agust = gofika(0, 2);
	cout << agust << endl;

	//Vector testing 
	cout << "Testing starts here: " << endl;


	

	Vector4D enVec;


	enVec[0] = 3.0f; 
	enVec[1] = 2.0f;
	enVec[2] = 4.0f;
	enVec[3] = 4.0f;
	cout << enVec[0] << endl;

	Vector4D enNy(2.0f, 1.0f, 5.0f, 0);

	Vector4D tredje(enVec.crossProduct(enVec, enNy));

	for (int i = 0; i < 4; i++)
	{
		cout << tredje[i] << " ";
	}
	cout << endl;

	
	bool isEqual = enVec == enNy;
	if(isEqual)
	{
		cout << "they are equal" << endl;
	}
	cout << isEqual << endl; 


	//Matrix testing
	Matrix4D identityy;
	Matrix4D enMatris;




	enMatris = identityy.matrixScalarProduct(5.0);
	Matrix4D trd(1, 1, 1, 1,   1, 1, 1, 3,   1, 2, 1, 5,   1, 2, 4, 5);
	trd = trd.Invert(trd);
	Matrix4D bullar = identityy ;
	cout << "Here comes some matrixvalues: " << endl;


	for (int i = 0; i < 16; i++)
	{

		enMatris[i] = i + 1;
		
	}

	//tredje = enMatris * enNy;



	for (int i = 0; i < 4; i++)
	{
		cout << tredje[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 16; i++)
	{
		cout << trd[i] << " ";
	}
	cout << endl;
	






	int a; 

	

	cin >> a;
return 0;
}