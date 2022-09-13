#pragma once

template<typename Vector>
class VectorIterator {
public:
	using Type = typename Vector::Type;
	using Reference = typename Vector::Reference;
	using Pointer = typename Vector::Pointer;

	VectorIterator(Pointer ptr): ptr(ptr){}

	Reference operator*()
	{
		return *ptr;
	}

	Pointer operator->()
	{
		return ptr;
	}

	Reference operator[](size_t index)
	{
		return (ptr[index]);
	}

	VectorIterator& operator++()
	{
		ptr++;
		return *this;
	}

	VectorIterator& operator++(int)
	{
		VectorIterator iterator = *this;
		++(*this); 
		return iterator;
	}

	VectorIterator& operator--()
	{
		ptr--;
		return *this;
	}

	VectorIterator& operator--(int)
	{
		VectorIterator iterator = *this;
		--(*this);
		return iterator;
	}

	bool operator==(const VectorIterator& other) const
	{
		return ptr == other.ptr;
	}


	bool operator!=(const VectorIterator& other) const
	{
		return !(*this == other);
	}

private:
	
	Pointer ptr;
};


template<typename T>
class Vector {
public:
	using Type = typename T;
	using Reference = Type&;
	using Pointer = Type*;
	using Iterator = VectorIterator<Vector<T>>;
public:
	Vector()
	{
		ReAlloc(2);
	}

	~Vector()
	{
		Clear();
		::operator delete(m_data, m_capacity*sizeof(T));
	}

	void push_back(const T& element)
	{
		if (m_size >= m_capacity)
			ReAlloc(m_capacity * 1.5);

		m_data[m_size] = element;
		m_size++;
 	}

	void push_back(T&& element)
	{
		if (m_size >= m_capacity)
			ReAlloc(m_capacity * 1.5);

		m_data[m_size] = std::move(element);
		m_size++;
	}

	template<typename... Argumenti>
	T& emplace_back(Argumenti&&... arg)
	{
		if (m_size >= m_capacity)
			ReAlloc(m_capacity * 1.5);

		new(&m_data[m_size]) T(std::forward<Argumenti>(arg)...); // direktno kontrisali u niz
		//m_data[m_size] = T(std::forward<Argumenti>(arg)...); // ovako smo ga bili konstruisali na steku pa pomerili (move) u niz m_data

		return m_data[m_size++];
	}

	void PopBack()
	{
		if (m_size > 0)
		{
			m_size--;
			m_data[m_size].~T();
		}
	}

	void Clear()
	{
		for (size_t i = 0; i < m_size; i++)
			m_data[i].~T();
		m_size = 0;
		//m_data = nullptr;
		//m_capacity = 0;
	}

	size_t Size() const
	{
		return m_size;
	}

	const T& operator[](size_t index) const
	{
		if (index >= m_size)
		{
			// assert
		}
		return m_data[index];
	}

	T& operator[](size_t index)
	{
		if (index >= m_size)
		{
			// assert
		}
		return m_data[index];
	}

	Iterator begin()
	{
		return Iterator(m_data);
	}

	Iterator end()
	{
		return Iterator(m_data + m_size);
	}

private:
	void ReAlloc(size_t newCapacity)
	{
		if (newCapacity < m_size)
			m_size = newCapacity;

		T* newData = (T*)::operator new (newCapacity * sizeof(T));

		for (size_t i = 0; i < m_size; i++)
			//new(&newData[i])T(std::move(m_data[i]));
			newData[i] = std::move(m_data[i]);

		for (size_t i = 0; i < m_capacity; i++)
			m_data[i].~T();

		::operator delete(m_data, m_capacity*sizeof(T));
		m_data = newData;
		m_capacity = newCapacity;
	}

	
private:
	size_t m_size = 0;
	size_t m_capacity = 0;
	T* m_data = nullptr;
};
