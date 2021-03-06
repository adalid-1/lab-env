#pragma once
#include "Vector4D.h"

class Matrix4D
{

private:
	
	float _matrix[16];


public:

	
//*******************************************************************************************************************************************************************
//Konstruktors

//Initiera matris med givna v�rden
	Matrix4D(float i0_0, float i0_1, float i0_2, float i0_3,
		float i1_0, float i1_1, float i1_2, float i1_3,
		float i2_0, float i2_1, float i2_2, float i2_3,
		float i3_0, float i3_1, float i3_2, float i3_3)
	{
		_matrix[0] = i0_0;
		_matrix[1] = i0_1;
		_matrix[2] = i0_2;
		_matrix[3] = i0_3;

		_matrix[4] = i1_0;
		_matrix[5] = i1_1;
		_matrix[6] = i1_2;
		_matrix[7] = i1_3;

		_matrix[8] = i2_0;
		_matrix[9] = i2_1;
		_matrix[10] = i2_2;
		_matrix[11] = i2_3;

		_matrix[12] = i3_0;
		_matrix[13] = i3_1;
		_matrix[14] = i3_2;
		_matrix[15] = i3_3;
	}



	//Default, identitetsmatris
	Matrix4D(void)
	{
		_matrix[0] = 1.0;
		_matrix[1] = 0.0;
		_matrix[2] = 0.0;
		_matrix[3] = 0.0;

		_matrix[4] = 0.0;
		_matrix[5] = 1.0;
		_matrix[6] = 0.0;
		_matrix[7] = 0.0;

		_matrix[8] = 0.0;
		_matrix[9] = 0.0;
		_matrix[10] = 1.0;
		_matrix[11] = 0.0;

		_matrix[12] = 0.0;
		_matrix[13] = 0.0;
		_matrix[14] = 0.0;
		_matrix[15] = 1.0;

	}
	//Kopieringskonstruktor
	Matrix4D(Matrix4D& matOther)
	{


		_matrix[0] = matOther._matrix[0];
		_matrix[1] = matOther._matrix[1];
		_matrix[2] = matOther._matrix[2];
		_matrix[3] = matOther._matrix[3];

		_matrix[4] = matOther._matrix[4];
		_matrix[5] = matOther._matrix[5];
		_matrix[6] = matOther._matrix[6];
		_matrix[7] = matOther._matrix[7];

		_matrix[8] = matOther._matrix[8];
		_matrix[9] = matOther._matrix[9];
		_matrix[10] = matOther._matrix[10];
		_matrix[11] = matOther._matrix[11];

		_matrix[12] = matOther._matrix[12];
		_matrix[13] = matOther._matrix[13];
		_matrix[14] = matOther._matrix[14];
		_matrix[15] = matOther._matrix[15];

	}


	//Rotationsmatriser

	Matrix4D RotationX(float radian)
	{
		Matrix4D rotation;
		rotation._matrix[5] = cos(radian);
		rotation._matrix[6] = -sin(radian);
		rotation._matrix[9] = sin(radian);
		rotation._matrix[10] = cos(radian);

		return  rotation;
	}
	Matrix4D RotationY(float radian)
	{
		Matrix4D rotation;
		rotation._matrix[0] = cos(radian);
		rotation._matrix[2] = sin(radian);
		rotation._matrix[8] = sin(radian);
		rotation._matrix[10] = cos(radian);

		return  rotation;
	}
	Matrix4D RotationZ(float radian)
	{
		Matrix4D rotation;
		rotation._matrix[0] = cos(radian);
		rotation._matrix[1] = -sin(radian);
		rotation._matrix[4] = sin(radian);
		rotation._matrix[5] = cos(radian);

		return  rotation;
	}

	void operator=(Matrix4D& matOther)
	{
		
		
		_matrix[0] = matOther._matrix[0];
		_matrix[1] = matOther._matrix[1];
		_matrix[2] = matOther._matrix[2];
		_matrix[3] = matOther._matrix[3];

		_matrix[4] = matOther._matrix[4];
		_matrix[5] = matOther._matrix[5];
		_matrix[6] = matOther._matrix[6];
		_matrix[7] = matOther._matrix[7];

		_matrix[8] = matOther._matrix[8];
		_matrix[9] = matOther._matrix[9];
		_matrix[10] = matOther._matrix[10];
		_matrix[11] = matOther._matrix[11];

		_matrix[12] = matOther._matrix[12];
		_matrix[13] = matOther._matrix[13];
		_matrix[14] = matOther._matrix[14];
		_matrix[15] = matOther._matrix[15];

		
	}
	void operator=(const Matrix4D& matOther)
	{


		_matrix[0] = matOther._matrix[0];
		_matrix[1] = matOther._matrix[1];
		_matrix[2] = matOther._matrix[2];
		_matrix[3] = matOther._matrix[3];

		_matrix[4] = matOther._matrix[4];
		_matrix[5] = matOther._matrix[5];
		_matrix[6] = matOther._matrix[6];
		_matrix[7] = matOther._matrix[7];

		_matrix[8] = matOther._matrix[8];
		_matrix[9] = matOther._matrix[9];
		_matrix[10] = matOther._matrix[10];
		_matrix[11] = matOther._matrix[11];

		_matrix[12] = matOther._matrix[12];
		_matrix[13] = matOther._matrix[13];
		_matrix[14] = matOther._matrix[14];
		_matrix[15] = matOther._matrix[15];


	}

	//*******************************************************************************************************************************************************************
	//Setter & Getter



	//Set bra
	float& operator[](int i)
	{
		return _matrix[i];

	}
	//Get bra
	float operator[](int i)const
	{
		return _matrix[i];

	}


	float get(int index)
	{
		
			return _matrix[index];
	

	}

	void set(int index, float value)
	{
	
			_matrix[index] = value;
	


	}

	//s�tt alla v�rden i matrisen
	void setAll(float i0_0, float i0_1, float i0_2, float i0_3,
		float i1_0, float i1_1, float i1_2, float i1_3,
		float i2_0, float i2_1, float i2_2, float i2_3,
		float i3_0, float i3_1, float i3_2, float i3_3)
	{
		_matrix[0] = i0_0;
		_matrix[1] = i0_1;
		_matrix[2] = i0_2;
		_matrix[3] = i0_3;

		_matrix[4] = i1_0;
		_matrix[5] = i1_1;
		_matrix[6] = i1_2;
		_matrix[7] = i1_3;

		_matrix[8] = i2_0;
		_matrix[9] = i2_1;
		_matrix[10] = i2_2;
		_matrix[11] = i2_3;

		_matrix[12] = i3_0;
		_matrix[13] = i3_1;
		_matrix[14] = i3_2;
		_matrix[15] = i3_3;

		

	}








	//*******************************************************************************************************************************************************************
//Matris-specifika r�knemetoder

	Matrix4D matrixScalarProduct(float scalar)
	{
		
		Matrix4D result;
		
			
		
				result._matrix[0] = _matrix[0] * scalar;
				result._matrix[1] = _matrix[1] * scalar;
				result._matrix[2] = _matrix[2] * scalar;
				result._matrix[3] = _matrix[3] * scalar;

				result._matrix[4] = _matrix[4] * scalar;
				result._matrix[5] = _matrix[5] * scalar;
				result._matrix[6] = _matrix[6] * scalar;
				result._matrix[7] = _matrix[7] * scalar;

				result._matrix[8] = _matrix[8] * scalar;
				result._matrix[9] = _matrix[9] * scalar;
				result._matrix[10] = _matrix[10] * scalar;
				result._matrix[11] = _matrix[11] * scalar;

				result._matrix[12] = _matrix[12] * scalar;
				result._matrix[13] = _matrix[13] * scalar;
				result._matrix[14] = _matrix[14] * scalar;
				result._matrix[15] = _matrix[15] * scalar;

			
		
		return result;



	}

	Matrix4D matrixAdd(Matrix4D other)
	{

	
		Matrix4D result;
		
			
				result._matrix[0] = _matrix[0] + other._matrix[0];
				result._matrix[1] = _matrix[1] + other._matrix[1];
				result._matrix[2] = _matrix[2] + other._matrix[2];
				result._matrix[3] = _matrix[3] + other._matrix[3];

				result._matrix[4] = _matrix[4] + other._matrix[4];
				result._matrix[5] = _matrix[5] + other._matrix[5];
				result._matrix[6] = _matrix[6] + other._matrix[6];
				result._matrix[7] = _matrix[7] + other._matrix[7];

				result._matrix[8] = _matrix[8] + other._matrix[8];
				result._matrix[9] = _matrix[9] + other._matrix[9];
				result._matrix[10] = _matrix[10] + other._matrix[10];
				result._matrix[11] = _matrix[11] + other._matrix[11];

				result._matrix[12] = _matrix[12] + other._matrix[12];
				result._matrix[13] = _matrix[13] + other._matrix[13];
				result._matrix[14] = _matrix[14] + other._matrix[14];
				result._matrix[15] = _matrix[15] + other._matrix[15];

			
		
		return result;

	}

	//Metod f�r att f� transponatet av en matris
	Matrix4D transpose()
	{



		Matrix4D newMat(_matrix[0], _matrix[4], _matrix[8], _matrix[12],
			_matrix[1], _matrix[5], _matrix[9], _matrix[13],
			_matrix[2], _matrix[6], _matrix[10], _matrix[14],
			_matrix[3], _matrix[7], _matrix[11], _matrix[15]);


		return newMat;
	}

	//
	//float Vector4D::operator*(const Vector4D& vSecond)
	Matrix4D operator*(Matrix4D& matOther)
	{
		Matrix4D result;

		


					result._matrix[0] = _matrix[0] * matOther._matrix[0] + _matrix[1] * matOther._matrix[4] + _matrix[2] * matOther._matrix[8] + _matrix[3] * matOther._matrix[12];
					result._matrix[1] = _matrix[0] * matOther._matrix[1] + _matrix[1] * matOther._matrix[5] + _matrix[2] * matOther._matrix[9] + _matrix[3] * matOther._matrix[13];
					result._matrix[2] = _matrix[0] * matOther._matrix[2] + _matrix[1] * matOther._matrix[6] + _matrix[2] * matOther._matrix[10] + _matrix[3] * matOther._matrix[14];
					result._matrix[3] = _matrix[0] * matOther._matrix[3] + _matrix[1] * matOther._matrix[7] + _matrix[2] * matOther._matrix[11] + _matrix[3] * matOther._matrix[15];

					result._matrix[4] = _matrix[4] * matOther._matrix[0] + _matrix[5] * matOther._matrix[4] + _matrix[6] * matOther._matrix[8] + _matrix[7] * matOther._matrix[12];
					result._matrix[5] = _matrix[4] * matOther._matrix[1] + _matrix[5] * matOther._matrix[5] + _matrix[6] * matOther._matrix[9] + _matrix[7] * matOther._matrix[13];
					result._matrix[6] = _matrix[4] * matOther._matrix[2] + _matrix[5] * matOther._matrix[6] + _matrix[6] * matOther._matrix[10] + _matrix[7] * matOther._matrix[14];
					result._matrix[7] = _matrix[4] * matOther._matrix[3] + _matrix[5] * matOther._matrix[7] + _matrix[6] * matOther._matrix[11] + _matrix[7] * matOther._matrix[15];

					result._matrix[8] = _matrix[8] * matOther._matrix[0] + _matrix[9] * matOther._matrix[4] + _matrix[10] * matOther._matrix[8] + _matrix[11] * matOther._matrix[12];
					result._matrix[9] = _matrix[8] * matOther._matrix[1] + _matrix[9] * matOther._matrix[5] + _matrix[10] * matOther._matrix[9] + _matrix[11] * matOther._matrix[13];
					result._matrix[10] = _matrix[8] * matOther._matrix[2] + _matrix[9] * matOther._matrix[6] + _matrix[10] * matOther._matrix[10] + _matrix[11] * matOther._matrix[14];
					result._matrix[11] = _matrix[8] * matOther._matrix[3] + _matrix[9] * matOther._matrix[7] + _matrix[10] * matOther._matrix[11] + _matrix[11] * matOther._matrix[15];
			

					result._matrix[12] = _matrix[12] * matOther._matrix[0] + _matrix[13] * matOther._matrix[4] + _matrix[14] * matOther._matrix[8] + _matrix[15] * matOther._matrix[12];
					result._matrix[13] = _matrix[12] * matOther._matrix[1] + _matrix[13] * matOther._matrix[5] + _matrix[14] * matOther._matrix[9] + _matrix[15] * matOther._matrix[13];
					result._matrix[14] = _matrix[12] * matOther._matrix[2] + _matrix[13] * matOther._matrix[6] + _matrix[14] * matOther._matrix[10] + _matrix[15] * matOther._matrix[14];
					result._matrix[15] = _matrix[12] * matOther._matrix[3] + _matrix[13] * matOther._matrix[7] + _matrix[14] * matOther._matrix[11] + _matrix[15] * matOther._matrix[15];
				


		return result;
	}


	


	//Vector matris produkt
	Vector4D operator*(Vector4D& vector)
	{
		
		Vector4D result;

		result[0] = _matrix[0] * vector[0] + _matrix[1] * vector[1] + _matrix[2] * vector[2] + _matrix[3] * vector[3];
		result[1] = _matrix[4] * vector[0] + _matrix[5] * vector[1] + _matrix[6] * vector[2] + _matrix[7] * vector[3];
		result[2] = _matrix[8] * vector[0] + _matrix[9] * vector[1] + _matrix[10] * vector[2] + _matrix[11] * vector[3];
		result[3] = _matrix[12] * vector[0] + _matrix[13] * vector[1] + _matrix[14] * vector[2] + _matrix[15] * vector[3];

		return result;
	}

	
	//DEN H�R BEH�VER FIXAS
	Matrix4D RotationVector(Vector4D vec, double angle)
	{
		Matrix4D C(0, -vec[2], vec[1], 0, vec[2], 0, -vec[0], 0, -vec[1], vec[0], 0, 0, 0, 0, 0, 1);
		Matrix4D D = C;
		D * D;
		D.matrixScalarProduct(1 - cos(angle));
		Matrix4D identity;
		Matrix4D Cade;

		C.matrixAdd(identity);

		C = identity;
		C.matrixScalarProduct(sin(angle));

		Cade.matrixScalarProduct(sin(angle));

		return identity;
	}

	//Fungerande matris invers
	Matrix4D Invert(Matrix4D inv)
	{
		float det;
		int i;


		Matrix4D invMat;

		invMat._matrix[0] = inv._matrix[5] * inv._matrix[10] * inv._matrix[15] -
			inv._matrix[5] * inv._matrix[11] * inv._matrix[14] -
			inv._matrix[9] * inv._matrix[6] * inv._matrix[15] +
			inv._matrix[9] * inv._matrix[7] * inv._matrix[14] +
			inv._matrix[13] * inv._matrix[6] * inv._matrix[11] -
			inv._matrix[13] * inv._matrix[7] * inv._matrix[10];

		invMat._matrix[4] = -inv._matrix[4] * inv._matrix[10] * inv._matrix[15] +
			inv._matrix[4] * inv._matrix[11] * inv._matrix[14] +
			inv._matrix[8] * inv._matrix[6] * inv._matrix[15] -
			inv._matrix[8] * inv._matrix[7] * inv._matrix[14] -
			inv._matrix[12] * inv._matrix[6] * inv._matrix[11] +
			inv._matrix[12] * inv._matrix[7] * inv._matrix[10];

		invMat._matrix[8] = inv._matrix[4] * inv._matrix[9] * inv._matrix[15] -
			inv._matrix[4] * inv._matrix[11] * inv._matrix[13] -
			inv._matrix[8] * inv._matrix[5] * inv._matrix[15] +
			inv._matrix[8] * inv._matrix[7] * inv._matrix[13] +
			inv._matrix[12] * inv._matrix[5] * inv._matrix[11] -
			inv._matrix[12] * inv._matrix[7] * inv._matrix[9];

		invMat._matrix[12] = -inv._matrix[4] * inv._matrix[9] * inv._matrix[14] +
			inv._matrix[4] * inv._matrix[10] * inv._matrix[13] +
			inv._matrix[8] * inv._matrix[5] * inv._matrix[14] -
			inv._matrix[8] * inv._matrix[6] * inv._matrix[13] -
			inv._matrix[12] * inv._matrix[5] * inv._matrix[10] +
			inv._matrix[12] * inv._matrix[6] * inv._matrix[9];

		invMat._matrix[1] = -inv._matrix[1] * inv._matrix[10] * inv._matrix[15] +
			inv._matrix[1] * inv._matrix[11] * inv._matrix[14] +
			inv._matrix[9] * inv._matrix[2] * inv._matrix[15] -
			inv._matrix[9] * inv._matrix[3] * inv._matrix[14] -
			inv._matrix[13] * inv._matrix[2] * inv._matrix[11] +
			inv._matrix[13] * inv._matrix[3] * inv._matrix[10];

		invMat._matrix[5] = inv._matrix[0] * inv._matrix[10] * inv._matrix[15] -
			inv._matrix[0] * inv._matrix[11] * inv._matrix[14] -
			inv._matrix[8] * inv._matrix[2] * inv._matrix[15] +
			inv._matrix[8] * inv._matrix[3] * inv._matrix[14] +
			inv._matrix[12] * inv._matrix[2] * inv._matrix[11] -
			inv._matrix[12] * inv._matrix[3] * inv._matrix[10];

		invMat._matrix[9] = -inv._matrix[0] * inv._matrix[9] * inv._matrix[15] +
			inv._matrix[0] * inv._matrix[11] * inv._matrix[13] +
			inv._matrix[8] * inv._matrix[1] * inv._matrix[15] -
			inv._matrix[8] * inv._matrix[3] * inv._matrix[13] -
			inv._matrix[12] * inv._matrix[1] * inv._matrix[11] +
			inv._matrix[12] * inv._matrix[3] * inv._matrix[9];

		invMat._matrix[13] = inv._matrix[0] * inv._matrix[9] * inv._matrix[14] -
			inv._matrix[0] * inv._matrix[10] * inv._matrix[13] -
			inv._matrix[8] * inv._matrix[1] * inv._matrix[14] +
			inv._matrix[8] * inv._matrix[2] * inv._matrix[13] +
			inv._matrix[12] * inv._matrix[1] * inv._matrix[10] -
			inv._matrix[12] * inv._matrix[2] * inv._matrix[9];

		invMat._matrix[2] = inv[1] * inv._matrix[6] * inv._matrix[15] -
			inv._matrix[1] * inv._matrix[7] * inv._matrix[14] -
			inv._matrix[5] * inv._matrix[2] * inv._matrix[15] +
			inv._matrix[5] * inv._matrix[3] * inv._matrix[14] +
			inv._matrix[13] * inv._matrix[2] * inv._matrix[7] -
			inv._matrix[13] * inv._matrix[3] * inv._matrix[6];

		invMat._matrix[6] = -inv._matrix[0] * inv._matrix[6] * inv._matrix[15] +
			inv._matrix[0] * inv._matrix[7] * inv._matrix[14] +
			inv._matrix[4] * inv._matrix[2] * inv._matrix[15] -
			inv._matrix[4] * inv._matrix[3] * inv._matrix[14] -
			inv._matrix[12] * inv._matrix[2] * inv._matrix[7] +
			inv._matrix[12] * inv._matrix[3] * inv._matrix[6];

		invMat._matrix[10] = inv._matrix[0] * inv._matrix[5] * inv._matrix[15] -
			inv._matrix[0] * inv._matrix[7] * inv._matrix[13] -
			inv._matrix[4] * inv._matrix[1] * inv._matrix[15] +
			inv._matrix[4] * inv._matrix[3] * inv._matrix[13] +
			inv._matrix[12] * inv._matrix[1] * inv._matrix[7] -
			inv._matrix[12] * inv._matrix[3] * inv._matrix[5];

		invMat._matrix[14] = -inv._matrix[0] * inv._matrix[5] * inv._matrix[14] +
			inv._matrix[0] * inv._matrix[6] * inv._matrix[13] +
			inv._matrix[4] * inv._matrix[1] * inv._matrix[14] -
			inv._matrix[4] * inv._matrix[2] * inv._matrix[13] -
			inv._matrix[12] * inv._matrix[1] * inv._matrix[6] +
			inv._matrix[12] * inv._matrix[2] * inv._matrix[5];

		invMat._matrix[3] = -inv._matrix[1] * inv._matrix[6] * inv._matrix[11] +
			inv._matrix[1] * inv._matrix[7] * inv._matrix[10] +
			inv._matrix[5] * inv._matrix[2] * inv._matrix[11] -
			inv._matrix[5] * inv._matrix[3] * inv._matrix[10] -
			inv._matrix[9] * inv._matrix[2] * inv._matrix[7] +
			inv._matrix[9] * inv._matrix[3] * inv._matrix[6];

		invMat._matrix[7] = inv._matrix[0] * inv._matrix[6] * inv._matrix[11] -
			inv._matrix[0] * inv._matrix[7] * inv._matrix[10] -
			inv._matrix[4] * inv._matrix[2] * inv._matrix[11] +
			inv._matrix[4] * inv._matrix[3] * inv._matrix[10] +
			inv._matrix[8] * inv._matrix[2] * inv._matrix[7] -
			inv._matrix[8] * inv._matrix[3] * inv._matrix[6];

		invMat._matrix[11] = -inv._matrix[0] * inv._matrix[5] * inv._matrix[11] +
			inv._matrix[0] * inv._matrix[7] * inv._matrix[9] +
			inv._matrix[4] * inv._matrix[1] * inv._matrix[11] -
			inv._matrix[4] * inv._matrix[3] * inv._matrix[9] -
			inv._matrix[8] * inv._matrix[1] * inv._matrix[7] +
			inv._matrix[8] * inv._matrix[3] * inv._matrix[5];

		invMat._matrix[15] = inv._matrix[0] * inv._matrix[5] * inv._matrix[10] -
			inv._matrix[0] * inv._matrix[6] * inv._matrix[9] -
			inv._matrix[4] * inv._matrix[1] * inv._matrix[10] +
			inv._matrix[4] * inv._matrix[2] * inv._matrix[9] +
			inv._matrix[8] * inv._matrix[1] * inv._matrix[6] -
			inv._matrix[8] * inv._matrix[2] * inv._matrix[5];


		det = inv._matrix[0] * invMat._matrix[0]
			+ inv._matrix[1] * invMat._matrix[4]
			+ inv._matrix[2] * invMat._matrix[8]
			+ inv._matrix[3] * invMat._matrix[12];

		if (det == 0)
		{
           // std::cout << "didn work";
			Matrix4D aba;
			return aba;
		}

       // std::cout << det << std::endl;
		det = (1.0 / det) ;

		for (i = 0; i < 16; i++)
			invMat._matrix[i] = invMat._matrix[i] * det ;

		return invMat;
	}


	Matrix4D translate(Vector4D v) {
		Matrix4D result;
		result[3] = v.getX();
		result[7] = v.getY();
		result[11] = v.getZ();
		result[15] = v.getW();

		return result;
	}

	//Dynga som kan komma till anv�ndning

	////Operations
	//Matrix4D rotation(const float radians);
	//Matrix4D secRotation(const float radians);


	////Set
	//float& operator[](const float a)
	//{
	//	int b;
	//	int d;
	//	float c = a / 4;
	//	b = c;
	//	c = fmod(c, 1.0);
	//	d = c * 4;

	//	return _matrix[b][d];

	//}

	////Get
	//float operator[](const float a) const
	//{
	//	int b;
	//	int d;
	//	float c = a / 4;
	//	b = c;
	//	c = fmod(c, 1.0);
	//	d = c * 4;

	//	return _matrix[b][d];

	//}



};