#pragma once

class Vector4D
{
private:
	float _Vector[4];

public:
	
	//Initalisering
	Vector4D(void)
	{
		_Vector[0] = 0.0;
		_Vector[1] = 0.0;
		_Vector[2] = 0.0;
		_Vector[3] = 0.0;
	}

	Vector4D(float x, float y, float z, float w)
	{
		_Vector[0] = x;
		_Vector[1] = y;
		_Vector[2] = z;
		_Vector[3] = w;
	}

	Vector4D(const Vector4D& vOther)
	{
		_Vector[0] = vOther._Vector[0];
		_Vector[1] = vOther._Vector[1];
		_Vector[2] = vOther._Vector[2];
		_Vector[3] = vOther._Vector[3];
	}




	//Setters & getters
	float getX()
	{
		return _Vector[0];
	}

	float getY()
	{
		return _Vector[1];
	}

	float getZ()
	{
		return _Vector[2];
	}

	float getW()
	{
		return _Vector[3];
	}

	void setX(float Xnew)
	{
		_Vector[0] = Xnew;

	}

	void setY(float Ynew)
	{
		_Vector[1] = Ynew;

	}
	void setZ(float Znew)
	{
		_Vector[2] = Znew;

	}
	void setW(float Wnew)
	{
		_Vector[3] = Wnew;

	}

	void setXYZW(float Xnew, float Ynew, float Znew, float Wnew)
	{
		_Vector[0] = Xnew;
		_Vector[1] = Ynew;
		_Vector[2] = Znew;
		_Vector[3] = Wnew;
	}

	//Komma åt vectorn i en vectorklass med standard vectorsyntax []
	float& operator[](const int i)
	{
		return _Vector[i];
	}

	float operator[](const int i)const
	{
		return _Vector[i];
	}


	
//*******************************************************************************************************************************************************************
//Matematiska funktioner

//Adderar två vektorer
	Vector4D addVector(Vector4D vFirst, Vector4D vSecond)
	{
		Vector4D vNew;                                                    //Skapar en ny vektor (innehåller resultatet av beräkningen)
		vNew._Vector[0] = vFirst._Vector[0] + vSecond._Vector[0];        //Nya vektorn får x-värde som är summan av två vektorers x-värde adderade
		vNew._Vector[1] = vFirst._Vector[1] + vSecond._Vector[1];	    //Nya vektorn får y-värde som är summan av två vektorers y-värde adderade
		vNew._Vector[2] = vFirst._Vector[2] + vSecond._Vector[2];	   //Nya vektorn får z-värde som är summan av två vektorers z-värde adderade
		vNew._Vector[3] = vFirst._Vector[3] + vSecond._Vector[3];	  //Nya vektorn får w-värde som är summan av två vektorers w-värde adderade
		return vNew;												 //Den nya vektorn returneras
	}


	//Subtraherar två vektorer
	Vector4D subVector(Vector4D vFirst, Vector4D vSecond)
	{
		Vector4D vNew;													  //Skapar en ny vektor (innehåller resultatet av beräkningen)
		vNew._Vector[0] = vFirst._Vector[0] - vSecond._Vector[0];        //Nya vektorn får x-värde som är differensen av två vektorers x-värden.
		vNew._Vector[1] = vFirst._Vector[1] - vSecond._Vector[1];       //Nya vektorn får y-värde som är differensen av två vektorers y-värden.
		vNew._Vector[2] = vFirst._Vector[2] - vSecond._Vector[2];      //Nya vektorn får z-värde som är differensen av två vektorers z-värden.
		vNew._Vector[3] = vFirst._Vector[3] - vSecond._Vector[3];     //Nya vektorn får w-värde som är differensen av två vektorers w-värden.
		return vNew;												 //Den nya vektorn returneras 
	}

	//multiplikation vektor med skalär
	Vector4D multScalarVector(float scalar, Vector4D Vector) //OBS skalären måste vara en float
	{
		Vector4D newVec;											 //Skapar en ny vektor (innehåller resultatet av beräkningen)
		newVec._Vector[0] = scalar * Vector._Vector[0];			    //Nya vektorn får x-värde som är produkten av en skalär och det gammla x-värdet.
		newVec._Vector[1] = scalar * Vector._Vector[1];			   //Nya vektorn får y-värde som är produkten av en skalär och det gammla y-värdet.
		newVec._Vector[2] = scalar * Vector._Vector[2];			  //Nya vektorn får z-värde som är produkten av en skalär och det gammla z-värdet.
		newVec._Vector[3] = scalar * Vector._Vector[3];			 //Nya vektorn får w-värde som är produkten av en skalär och det gammla w-värdet.
		return newVec;											//Den nya vektorn returneras


	}

	//Scalärprodukten av två vektorer (Dotprodukt)
	float scalProdVector(Vector4D vFirst, Vector4D vSecond)
	{
		float scalar = vFirst._Vector[0] * vSecond._Vector[0] + vFirst._Vector[1] * vSecond._Vector[1] + vFirst._Vector[2] * vSecond._Vector[2] + vFirst._Vector[3] * vSecond._Vector[3];
		// x y z och w värdena från de två vektorerna mulipliceras med varandra (X1*X2, Y1*Y2 osv) och adderas sedan till en skalär.

		return scalar;

	}

	//Längden av en vektor
	float lenVector(Vector4D Vector)
	{
		float length = sqrt(Vector._Vector[0] * Vector._Vector[0] + Vector._Vector[1] * Vector._Vector[1] + Vector._Vector[2] * Vector._Vector[2] + Vector._Vector[3] * Vector._Vector[3]);
		//Längden av en vektor beräknas: sqrt(x^2 + y^2)
		return length;
	}

	//Enhets vektor
	Vector4D unitVector(Vector4D Vector)
	{
		float len = lenVector(Vector);
		Vector4D Unit;									   //Ny (enhets)vektor skapas
		Unit._Vector[0] = Vector._Vector[0] / len;	      //x-värdet delas med längden av vektorn
		Unit._Vector[1] = Vector._Vector[1] / len;	     //y-värdet delas med längden av vektorn
		Unit._Vector[2] = Vector._Vector[2] / len;	     //y-värdet delas med längden av vektorn

		return Unit;                                   //Vektorn returneras

	}
	//Kryssprodukt för XYZ
	Vector4D crossProduct(Vector4D vFirst, Vector4D vSecond)
	{
		Vector4D VecReturn;
		VecReturn._Vector[0] = (vFirst._Vector[1] * vSecond._Vector[2]) - (vFirst._Vector[2] * vSecond._Vector[1]);          // Xn = Y1 * Z2    -    Z1 * Y2
		VecReturn._Vector[1] = (vFirst._Vector[2] * vSecond._Vector[0]) - (vFirst._Vector[0] * vSecond._Vector[2]);        //  Yn = Z1 * X2    -    X1 * Z2
		VecReturn._Vector[2] = (vFirst._Vector[0] * vSecond._Vector[1]) - (vFirst._Vector[1] * vSecond._Vector[0]);     //   Zn = X1 * Y2    -    Y1 * X2
		return VecReturn;
	}


	//*******************************************************************************************************************************************************************
	//operator överlagring//



	//Operator överlagring Addition av vektorer
	Vector4D operator+(const Vector4D& vSecond)
	{
		//return addVector(*this, vSecond);                          

		return addVector((*this), vSecond);
	}
	//Operator överlagring Subtraktion av vektorer
	Vector4D operator-(const Vector4D& vSecond)
	{

		return subVector((*this), vSecond);
	}

	//Operator överlagring multiplikation skalär med vektor
	Vector4D operator*(const float& scalar)
	{

		return multScalarVector(scalar, (*this));

	}

	//Operator överlagring skalärprodukt
	float operator*(const Vector4D& vSecond)
	{


		return scalProdVector((*this), vSecond);

	}



	//*******************************************************************************************************************************************************************
	//Logiska operatorer


	//Operator överlagring jämförelse med == 
	bool operator==(const Vector4D& vSecond)
	{
		if (_Vector[0] == vSecond._Vector[0] &&
			_Vector[1] == vSecond._Vector[1] &&
			_Vector[2] == vSecond._Vector[2] &&
			_Vector[3] == vSecond._Vector[3])
		{
			return true;
		}

		return false;

	}

	//Operator överlagring jämförelse med !=
	bool operator!=(const Vector4D& vSecond)
	{
		if (_Vector[0] != vSecond._Vector[0] &&
			_Vector[1] != vSecond._Vector[1] &&
			_Vector[2] != vSecond._Vector[2] &&
			_Vector[3] != vSecond._Vector[3])
		{
			return true;
		}

		return false;

	}


	//*******************************************************************************************************************************************************************
	//Destructor


	~Vector4D(void)
	{


	}

};