#pragma once
#include "Vector3D.h"

class Bin
{
private:
	unsigned int m_Count;
	unsigned int m_MaxCount; // space left available
	Vector3D** m_Vectors;
public:
	explicit Bin(unsigned int numOfVectors);
	~Bin();

	// Copy constructor
	Bin(const Bin& other);

	// Copy assignment
	Bin& operator=(const Bin& other);

	bool Exists(unsigned int index);
	bool Get(unsigned int index, Vector3D& outputVec);

	bool GetX(unsigned int index, float& out);
	bool GetY(unsigned int index, float& out);
	bool GetZ(unsigned int index, float& out);

	int Add(float x, float y, float z);
	bool Remove(unsigned int index);

	unsigned int GetCount();
	unsigned int GetMaxCount();
private:
	void FreeResources();
};
