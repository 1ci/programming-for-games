#include <iostream>
#include "Vector3D.h"
#include "Bin.h"

void TestVector3D();
void TestBin();

int main(int argc, char* argv[])
{
	TestVector3D();
	TestBin();

	std::cin.get();
	return 0;
}

void TestVector3D()
{
	Vector3D vec1(2.0f, 3.0f, 4.0f);
	Vector3D vec2(5.0f, 15.0f, 25.0f);
	Vector3D vec3 = vec1 + vec2;
	std::cout << vec3 << std::endl;

	Vector3D vec4;
	vec4 = Vector3D(10.0f, 20.0f, 30.0f);
	vec3 = vec4;

	std::cout << vec4 << std::endl;
	std::cout << "vec4.Magnitude() = " << vec4.Magnitude() << std::endl;
	std::cout << "vec4.Normalise() = " << vec4.Normalise() << std::endl;
	std::cout << "vec2.Cross(vec4) = " << vec2.Cross(vec4) << std::endl;
	std::cout << "vec1.Dot(vec3) = " << vec1.Cross(vec3) << std::endl;
}

void TestBin()
{
	int maxCount = 5;
	Bin bin(maxCount);

	for (int i = 0; i < maxCount; i++)
	{
		bin.Add(1.0f, 2.0f, 3.0f);
	}

	std::cout << "bin.GetCount() = " << bin.GetCount() << std::endl;
	std::cout << "bin.GetMaxCount() = " << bin.GetMaxCount() << std::endl;

	for (int i = 0; i < maxCount; i++)
	{
		Vector3D temp;
		if (bin.Get(i, temp))
		{
			std::cout << temp << std::endl;
		}
	}

	for (int i = 0; i < maxCount; i++)
	{
		bin.Remove(0);
	}

	std::cout << "bin.GetCount() = " << bin.GetCount() << std::endl;
	std::cout << "bin.GetMaxCount() = " << bin.GetMaxCount() << std::endl;
}
