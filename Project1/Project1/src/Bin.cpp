#include "Bin.h"
#include "Vector3D.h"
#include <iostream>
#include <cstdlib>

//-----------------------------------------------------------------------------
// What does the int parameter represent?
// "...dictates how many Vector3D’s should fit inside the bin..."
// 
// 1. Is that the maximum number of vectors a bin can contain?
// 2. Or is it the number of vectors a bin must pre-allocate memory for?
// 
// Usually we don't want to pre-allocate memory we'll probably never use.
//-----------------------------------------------------------------------------
Bin::Bin(unsigned int numOfVectors)
	: m_Count(0)
	, m_MaxCount(numOfVectors)
	, m_Vectors(nullptr)
{
}

Bin::~Bin()
{
	FreeResources();
}

void Bin::FreeResources()
{
	for (unsigned int i = 0; i < m_Count; ++i)
	{
		// Kill vectors
		delete m_Vectors[i];
		m_Vectors[i] = nullptr;
	}
	free(m_Vectors);
	m_Vectors = nullptr;
}

Bin::Bin(const Bin& other)
	: m_Count(other.m_Count)
	, m_MaxCount(other.m_MaxCount)
	, m_Vectors(static_cast<Vector3D**>( malloc(m_Count * sizeof(Vector3D*)) ))
{
	if (m_Vectors == nullptr)
	{
		// Memory allocation failed
		return;
	}

	// Copy vector objects across
	for (unsigned int i = 0; i < m_Count; ++i)
	{
		m_Vectors[i] = new Vector3D(*other.m_Vectors[i]);
	}
}

Bin& Bin::operator=(const Bin& other)
{
	if (this == &other)
	{
		return *this;
	}

	// Free current resources
	FreeResources();

	// Copy members
	m_Count = other.m_Count;
	m_MaxCount = other.m_MaxCount;
	m_Vectors = static_cast<Vector3D**>(malloc(m_Count * sizeof(Vector3D*)));

	if (m_Vectors == nullptr)
	{
		// Memory allocation failed
		return *this;
	}

	// Copy vectors
	for (unsigned int i = 0; i < m_Count; ++i)
	{
		m_Vectors[i] = new Vector3D(*other.m_Vectors[i]);
	}
	return *this;
}

//-----------------------------------------------------------------------------
// Tells you whether a vector exists at some index
// 
// @param	index	Index
// @return	bool	true if vector exsists, false otherise
//-----------------------------------------------------------------------------
bool Bin::Exists(unsigned int index)
{
	if (m_Vectors == nullptr)
	{
		// Bin pack not even created
		return false;
	}
	if (index > m_Count - 1)
	{
		// Out of bounds
		return false;
	}
	if (m_Vectors[index] == nullptr)
	{
		// This element does not exist
		return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// Retrieves a copy of the nth vector in the bin
// 
// @param	index		Index of vector
// @param	outputVec	Output copy of the vector
// @return	bool		true if vector exists, false otherwise
//-----------------------------------------------------------------------------
bool Bin::Get(unsigned int index, Vector3D& outputVec)
{
	if (!Exists(index))
	{
		return false;
	}
	outputVec = *m_Vectors[index];
	return true;
}

//-----------------------------------------------------------------------------
// Have to check if the vector at that index exists. If it doesn't, either:
// 1. Return false
// 2. Throw an exception (lol)
// 3. Return -1 as a float (bad)
// 
// @param	index	Index
// @param	out		Output x value of the vector
// @return	bool	true if vector exists, false otherwise
//-----------------------------------------------------------------------------
bool Bin::GetX(unsigned int index, float& out)
{
	if (!Exists(index))
	{
		return false;
	}
	out = m_Vectors[index]->x;
	return true;
}

bool Bin::GetY(unsigned int index, float& out)
{
	if (!Exists(index))
	{
		return false;
	}
	out = m_Vectors[index]->y;
	return true;
}

bool Bin::GetZ(unsigned int index, float& out)
{
	if (!Exists(index))
	{
		return false;
	}
	out = m_Vectors[index]->z;
	return true;
}

//-----------------------------------------------------------------------------
// Creates and adds a new vector object to the bin
//
// @params	x,y,z	Vector
// @return	int		Index of the new entry in the bin or -1 if failed to add
// @notes			Will return -1 if allocation failed or bin is full.
//-----------------------------------------------------------------------------
int Bin::Add(float x, float y, float z)
{
	// Check if reached maximum bin size
	if (m_Count == m_MaxCount)
	{
		// Can't add any more items. The bin is full.
		return -1;
	}

	// Allocate / extend memory
	size_t newSize = (m_Count + 1) * sizeof(Vector3D*);
	Vector3D** pExtended = static_cast<Vector3D**>(realloc(m_Vectors, newSize));

	if (pExtended == nullptr)
	{
		// Reallocation failed, therefore can't add a new vector object
		return -1;
	}
	m_Vectors = pExtended;
	
	// Create the new vector object
	Vector3D* vector = new Vector3D(x, y, z);
	m_Vectors[m_Count] = vector;
	++m_Count;
	return m_Count - 1;
}

//-----------------------------------------------------------------------------
// Removes the vector object at some index in the bin
//
// @param	index	Index
// @return	bool	true if managed to delete, false otherwise
//-----------------------------------------------------------------------------
bool Bin::Remove(unsigned int index)
{
	if (!Exists(index))
	{
		// Can't remove an item which does not exist
		return false;
	}

	// Destroy the object
	delete m_Vectors[index];
	m_Vectors[index] = nullptr;

	// If deleting the last item
	if (m_Count == 1)
	{
		m_Count = 0;
		free(m_Vectors);
		m_Vectors = nullptr;
		return true;
	}

	// Otherwise shift the entire pack down from that position on
	for (unsigned int i = index; i < m_Count - 1; ++i)
	{
		m_Vectors[i] = m_Vectors[i + 1];
	}

	// Deallocate memory
	size_t newSize = (m_Count - 1) * sizeof(Vector3D*);
	Vector3D** pShrunk = static_cast<Vector3D**>(realloc(m_Vectors, newSize));

	if (pShrunk == nullptr)
	{
		// Reallocation failed.
		// TODO: This could be a potential problem if it ever happens.
		// Why? Because we're leaving a dangling nullptr in the pack.
		// On the bright side, it will probably never happen though.
		// Why? Because freeing memory is cheap.
		return false;
	}
	m_Vectors = pShrunk;

	--m_Count;
	return true;
}

unsigned int Bin::GetCount()
{
	return m_Count;
}

unsigned int Bin::GetMaxCount()
{
	return m_MaxCount;
}
