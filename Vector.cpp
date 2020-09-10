#include <iostream>
#include <cstddef>
#include <algorithm>

template<typename T>
class Vector {
private:
	int theSize;
	int theCapacity;
	T* objects;

public:
	explicit Vector(int initSize = 0)
	: theSize{initSize}, theCapacity { initSize * 2}
	{
		objects = new T[theCapacity]; // allocate space for our Vector
	}
	Vector(const Vector<T>& v)  // copy constructor
	: theSize{v.theSize}, theCapacity{v.theCapacity}, objects{nullptr}
	{
		objects = new T[theCapacity];
		for (int k = 0; k < theSize; ++k)
			objects[k] = v.objects[k];
	}
	Vector(Vector<T>&& v); // move constructor
	Vector<T>& operator=(const Vector<T>& v) // copy assignment
	{
		Vector<T> copy = v; // using copy constructor
		std::swap(*this, copy);
		return *this;
	}
	Vector<T>& operator=(Vector<T>&& v) // move assignment
	{
		std::swap(theSize, v.theSize);
		std::swap(theCapacity, v.theCapacity);
		std::swap(objects, v.objects);
		
		return *this;
	}
	~Vector() // destructor
	{
		delete [] objects;
	}
	void reserve(std::size_t n)
	{
		if( n < theSize)
			return;
		
		T *newVector = new T[n];
		for(int k = 0; k < theSize; ++k)
			newVector[k] = std::move(objects[k]); // temp store
		
		theCapacity = n;
		std::swap(objects, newVector); // remove old data
		delete [] newVector; // free temp variable
	}
	void resize(std::size_t n)
	{
		if(n > theCapacity)
			reserve(theSize * 2);
		theSize = n;
	}
	T& operator[](std::size_t i) // mutator
	{ return objects[i]; }
	const T& operator[](std::size_t i) const // accesssor
	{ return objects[i]; }
	std::size_t size() const
	{ return theSize; }
	bool empty() const
	{ return size() == 0; }
	int capacity() const
	{ return theCapacity; }

	void pop_back()
	{ theSize--; }
	void push_back(T& val)
	{
		if (theCapacity == theSize)
			resize(theCapacity*2 + 1);
		objects[theSize++] = std::move(val);
	}
	const T& back() const
	{ return objects[theSize - 1]; }
	
	// iterators typedef
	typedef T* iterator;
	typedef const T* const_iterator;
	
	iterator begin()
	{ return &objects[0]; }
	iterator end()
	{ return &objects[size()]; }
	
	const_iterator begin() const
	{ return &objects[0]; }
	const_iterator end() const
	{ return &objects[size()]; }
};

int main()
{
	return 0;
}