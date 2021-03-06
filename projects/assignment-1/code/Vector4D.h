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

	//Komma �t vectorn i en vectorklass med standard vectorsyntax []
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

//Adderar tv� vektorer
	Vector4D addVector(Vector4D vFirst, Vector4D vSecond)
	{
		Vector4D vNew;                                                    //Skapar en ny vektor (inneh�ller resultatet av ber�kningen)
		vNew._Vector[0] = vFirst._Vector[0] + vSecond._Vector[0];        //Nya vektorn f�r x-v�rde som �r summan av tv� vektorers x-v�rde adderade
		vNew._Vector[1] = vFirst._Vector[1] + vSecond._Vector[1];	    //Nya vektorn f�r y-v�rde som �r summan av tv� vektorers y-v�rde adderade
		vNew._Vector[2] = vFirst._Vector[2] + vSecond._Vector[2];	   //Nya vektorn f�r z-v�rde som �r summan av tv� vektorers z-v�rde adderade
		vNew._Vector[3] = vFirst._Vector[3] + vSecond._Vector[3];	  //Nya vektorn f�r w-v�rde som �r summan av tv� vektorers w-v�rde adderade
		return vNew;												 //Den nya vektorn returneras
	}


	//Subtraherar tv� vektorer
	Vector4D subVector(Vector4D vFirst, Vector4D vSecond)
	{
		Vector4D vNew;													  //Skapar en ny vektor (inneh�ller resultatet av ber�kningen)
		vNew._Vector[0] = vFirst._Vector[0] - vSecond._Vector[0];        //Nya vektorn f�r x-v�rde som �r differensen av tv� vektorers x-v�rden.
		vNew._Vector[1] = vFirst._Vector[1] - vSecond._Vector[1];       //Nya vektorn f�r y-v�rde som �r differensen av tv� vektorers y-v�rden.
		vNew._Vector[2] = vFirst._Vector[2] - vSecond._Vector[2];      //Nya vektorn f�r z-v�rde som �r differensen av tv� vektorers z-v�rden.
		vNew._Vector[3] = vFirst._Vector[3] - vSecond._Vector[3];     //Nya vektorn f�r w-v�rde som �r differensen av tv� vektorers w-v�rden.
		return vNew;												 //Den nya vektorn returneras 
	}

	//multiplikation vektor med skal�r
	Vector4D multScalarVector(float scalar, Vector4D Vector) //OBS skal�ren m�ste vara en float
	{
		Vector4D newVec;											 //Skapar en ny vektor (inneh�ller resultatet av ber�kningen)
		newVec._Vector[0] = scalar * Vector._Vector[0];			    //Nya vektorn f�r x-v�rde som �r produkten av en skal�r och det gammla x-v�rdet.
		newVec._Vector[1] = scalar * Vector._Vector[1];			   //Nya vektorn f�r y-v�rde som �r produkten av en skal�r och det gammla y-v�rdet.
		newVec._Vector[2] = scalar * Vector._Vector[2];			  //Nya vektorn f�r z-v�rde som �r produkten av en skal�r och det gammla z-v�rdet.
		newVec._Vector[3] = scalar * Vector._Vector[3];			 //Nya vektorn f�r w-v�rde som �r produkten av en skal�r och det gammla w-v�rdet.
		return newVec;											//Den nya vektorn returneras


	}

	//Scal�rprodukten av tv� vektorer (Dotprodukt)
	float scalProdVector(Vector4D vFirst, Vector4D vSecond)
	{
		float scalar = vFirst._Vector[0] * vSecond._Vector[0] + vFirst._Vector[1] * vSecond._Vector[1] + vFirst._Vector[2] * vSecond._Vector[2] + vFirst._Vector[3] * vSecond._Vector[3];
		// x y z och w v�rdena fr�n de tv� vektorerna mulipliceras med varandra (X1*X2, Y1*Y2 osv) och adderas sedan till en skal�r.

		return scalar;

	}

	//L�ngden av en vektor
	float lenVector(Vector4D Vector)
	{
		float length = sqrt(Vector._Vector[0] * Vector._Vector[0] + Vector._Vector[1] * Vector._Vector[1] + Vector._Vector[2] * Vector._Vector[2] + Vector._Vector[3] * Vector._Vector[3]);
		//L�ngden av en vektor ber�knas: sqrt(x^2 + y^2)
		return length;
	}

	//Enhets vektor
	Vector4D unitVector(Vector4D Vector)
	{
		float len = lenVector(Vector);
		Vector4D Unit;									   //Ny (enhets)vektor skapas
		Unit._Vector[0] = Vector._Vector[0] / len;	      //x-v�rdet delas med l�ngden av vektorn
		Unit._Vector[1] = Vector._Vector[1] / len;	     //y-v�rdet delas med l�ngden av vektorn
		Unit._Vector[2] = Vector._Vector[2] / len;	     //y-v�rdet delas med l�ngden av vektorn

		return Unit;                                   //Vektorn returneras

	}
	//Kryssprodukt f�r XYZ
	Vector4D crossProduct(Vector4D vFirst, Vector4D vSecond)
	{
		Vector4D VecReturn;
		VecReturn._Vector[0] = (vFirst._Vector[1] * vSecond._Vector[2]) - (vFirst._Vector[2] * vSecond._Vector[1]);          // Xn = Y1 * Z2    -    Z1 * Y2
		VecReturn._Vector[1] = (vFirst._Vector[2] * vSecond._Vector[0]) - (vFirst._Vector[0] * vSecond._Vector[2]);        //  Yn = Z1 * X2    -    X1 * Z2
		VecReturn._Vector[2] = (vFirst._Vector[0] * vSecond._Vector[1]) - (vFirst._Vector[1] * vSecond._Vector[0]);     //   Zn = X1 * Y2    -    Y1 * X2
		return VecReturn;
	}


	//*******************************************************************************************************************************************************************
	//operator �verlagring//



	//Operator �verlagring Addition av vektorer
	Vector4D operator+(const Vector4D& vSecond)
	{
		//return addVector(*this, vSecond);                          

		return addVector((*this), vSecond);
	}
	//Operator �verlagring Subtraktion av vektorer
	Vector4D operator-(const Vector4D& vSecond)
	{

		return subVector((*this), vSecond);
	}

	//Operator �verlagring multiplikation skal�r med vektor
	Vector4D operator*(const float& scalar)
	{

		return multScalarVector(scalar, (*this));

	}

	//Operator �verlagring skal�rprodukt
	float operator*(const Vector4D& vSecond)
	{


		return scalProdVector((*this), vSecond);

	}



	//*******************************************************************************************************************************************************************
	//Logiska operatorer


	//Operator �verlagring j�mf�relse med == 
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

	//Operator �verlagring j�mf�relse med !=
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