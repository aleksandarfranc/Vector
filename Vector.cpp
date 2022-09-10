#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
#include "Vector.h"
template<typename T>
void PrintVector(const Vector<T>& vector)
{
	for (int i = 0; i < vector.Size(); i++)
		cout << vector[i] << endl;
	
	cout << "-------------------------------------------" << endl;
}

struct Vector3 {
	float x = 0.0f, y = 0.0f, z = 0.0f;
	int* m_memoryBlock;

	Vector3() { 
		m_memoryBlock = new int[4];
	}

	Vector3(float scalar)
		: x(scalar), y(scalar), z(scalar) {
		m_memoryBlock = new int[4];
	}
	Vector3(float x, float y, float z)
		: x(x), y(y), z(z) {m_memoryBlock = new int[4];}
	Vector3(const Vector3& copyVec) = delete;

	Vector3(Vector3&& copyVec)
		: x(copyVec.x), y(copyVec.y), z(copyVec.z)
	{
		printf("Move\n");
		m_memoryBlock = copyVec.m_memoryBlock;
		copyVec.m_memoryBlock = nullptr;
	}

	Vector3& operator=(const Vector3& vec) = delete;

	Vector3& operator=(Vector3&& vec) {
		printf("move assign\n");
		x = vec.x;
		y = vec.y;
		z = vec.z;

		m_memoryBlock = vec.m_memoryBlock;
		vec.m_memoryBlock = nullptr;

		return *this;
	}

	~Vector3()
	{
		printf("Destroy \n");
		delete [] m_memoryBlock;
	}
};

ostream& operator<<(ostream& stream, const Vector3& vec)
{
	stream << vec.x << ", " << vec.y << ", " << vec.z << endl;
	return stream;
}

int main() {
	
	{
		Vector<string> vector;
		vector.emplace_back("hello");
		vector.emplace_back("hello");
		vector.emplace_back("hello");
		vector.emplace_back("hello");
		vector.emplace_back("hello");
		vector.emplace_back("Helo");
		vector.emplace_back("Helo");
		vector.PopBack();
	}

	return 0;
}
