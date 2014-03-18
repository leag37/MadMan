//*************************************************************************************************
// Title: MMArray.h
// Author: Gael Huber
// Description: A simple array class
//*************************************************************************************************
#ifndef __MMARRAY_H__
#define __MMARRAY_H__

#include "Core\MMSystem.h"

namespace MadMan
{
	/** \addtogroup DataStructures
	*	@{
	*/

	template <typename T>
	class Array
	{
	public:
		/** 
		* Default constructor
		*/
		Array();

		/** 
		* Constructor
		* @param
		*	MUINT capacity The default capacity of the array
		* @param
		*	MUINT growthRate The amount by which to grow the array when it needs to expand
		*/
		Array(MUINT capacity, MUINT growthRate);

		/**
		* Copy constructor
		* @param
		*	const Array<T>& value The array to copy
		*/
		Array(const Array<T>& value);

		/**
		* Destructor
		*/
		~Array();

		/**
		* Assignment operator
		* @param
		*	const Array<T>& value The array to copy
		* @return
		*	Array<T>& The array after assignment
		*/
		Array<T>& operator=(const Array<T>& value);

		/**
		* Access operator
		* @param
		*	MUINT index The array index to access
		* @return
		*	T& The element at the specified index
		*/
		T& operator[](MUINT index);

		/**
		* Access operator
		* @param
		*	MUINT index The array index to access
		* @return
		*	const T& The element at the specified index
		*/
		const T& operator[](MUINT index) const;

		/**
		* Push an element to the back of the array
		* @param
		*	const T& value The element to add to the array
		*/
		void pushBack(const T& value);

		/**
		* Push an element to the front of the array. All other elements get shifted by one
		* @param
		*	const T& value The element to add to the array
		*/
		void pushFront(const T& value);

		/**
		* Pop an element from the back of the array.
		* @return
		*	const T value The element removed from the array
		*/
		T popBack();

		/**
		* Pop an element from the front of the array. All elements get shifted forward by one
		* @return
		*	const T value The element removed from the array
		*/
		T popFront();

		/**
		* Get the current size
		* @return
		*	MUINT The size of the array
		*/
		MUINT getSize() const;

		/**
		* Get the current capacity
		* @return
		*	MUINT The capacity of the array
		*/
		MUINT getCapacity() const;

	private:
		/**
		* Grow the array
		*/
		void _grow();

	private:
		/**
		* The array of elements T
		*/
		T* _elements;

		/**
		* The current size of the array
		*/
		MUINT _size;

		/**
		* The maximum size of the array at its current state
		*/
		MUINT _capacity;

		/**
		* The growth rate of the capacity when resizing the array
		*/
		MUINT _growthRate;
	};

	/** @} */

	/** 
	* Default constructor
	*/
	template <typename T>
	Array<T>::Array()
		:	_size(0),
			_capacity(1),
			_growthRate(1)
	{
		// Initialize the array
		_elements = new T[_capacity];
	}

	/** 
	* Constructor
	* @param
	*	MUINT capacity The default capacity of the array
	* @param
	*	MUINT growthRate The amount by which to grow the array when it needs to expand
	*/
	template <typename T>
	Array<T>::Array(MUINT capacity = 1, MUINT growthRate = 1)
		:	_size(0),
			_capacity(capacity),
			_growthRate(growthRate)
	{
		_elements = new T[_capacity];
	}

	/**
	* Copy constructor
	* @param
	*	const Array<T>& value The array to copy
	*/
	template <typename T>
	Array<T>::Array(const Array<T>& value)
		:	_size(value._size),
			_capacity(value._capacity),
			_growthRate(value._growthRate)
	{
		_elements = new T[_capacity];
		for(MUINT i = 0; i < _size; ++i)
		{
			_elements[i] = value._elements[i];
		}
	}

	/**
	* Destructor
	*/
	template <typename T>
	Array<T>::~Array()
	{
		// Destroy the array
		delete[] _elements;
	}

	/**
	* Assignment operator
	* @param
	*	const Array<T>& value The array to copy
	* @return
	*	Array<T>& The array after assignment
	*/
	template <typename T>
	Array<T>& Array<T>::operator=(const Array<T>& value)
	{
		// Self-assignment check
		if(this == &value)
		{
			return *this;
		}

		// Delete current set of elements
		delete[] _elements;

		// Set new properties
		_size = value._size;
		_capacity = value._capacity;
		_growthRate = value._growthRate;

		// Re-allocate space for elements
		_elements = new T[_size];

		for(MUINT i = 0; i < _size; ++i)
		{
			_elements[i] = value._elements[i];
		}

		return *this;
	}

	/**
	* Access operator
	* @param
	*	MUINT index The array index to access
	* @return
	*	T& The element at the specified index
	*/
	template <typename T>
	T& Array<T>::operator[](MUINT index)
	{
		// Check that index < _size
		assert(index < _size);

		// Return the value
		return _elements[index];
	}

	/**
	* Access operator
	* @param
	*	MUINT index The array index to access
	* @return
	*	const T& The element at the specified index
	*/
	template <typename T>
	const T& Array<T>::operator[](MUINT index) const
	{
		// Check that index < size
		assert(index < size);

		return _elements[index];
	}

	/**
	* Push an element to the back of the array
	* @param
	*	const T& value The element to add to the array
	*/
	template <typename T>
	void Array<T>::pushBack(const T& value)
	{
		// If we are at max capacity, grow the array
		if(_size == _capacity)
		{
			_grow();
		}

		// Push onto the back of the array
		_elements[_size++] = value;
	}

	/**
	* Push an element to the front of the array. All other elements get shifted by one
	* @param
	*	const T& value The element to add to the array
	*/
	template <typename T>
	void Array<T>::pushFront(const T& value)
	{
		if(_size == _capacity)
		{
			_grow();
		}

		// Move all elements forward 1 index value
		for(MUINT i = _size, MUINT j = ++_size; i >= 0; --i, --j)
		{
			_elements[j] = _elements[i];
		}
		_elements[0] = value;
	}

	/**
	* Pop an element from the back of the array.
	* @return
	*	const T value The element removed from the array
	*/
	template <typename T>
	T Array<T>::popBack()
	{
		assert(_size > 0);

		T value = _elements[--_size];

		return value;
	}

	/**
	* Pop an element from the front of the array. All elements get shifted forward by one
	* @return
	*	const T value The element removed from the array
	*/
	template <typename T>
	T Array<T>::popFront()
	{
		assert(_size > 0);

		T value = _elements[0];

		for(MUINT i = 0, MUINT j = 1; i < _size; ++i, ++j)
		{
			_elements[i] = _elements[j];
		}
		return value;
	}

	/**
	* Get the current size
	* @return
	*	MUINT The size of the array
	*/
	template <typename T>
	MUINT Array<T>::getSize() const
	{
		return _size;
	}

	/**
	* Get the current capacity
	* @return
	*	MUINT The capacity of the array
	*/
	template <typename T>
	MUINT Array<T>::getCapacity() const
	{
		return _capacity;
	}

	/**
	* Grow the array
	*/
	template <typename T>
	void Array<T>::_grow()
	{
		// Increase the capacity
		_capacity += _growthRate;

		// Create a new array and copy over the data
		T* newElements = new T[_capacity];
		for(MUINT i = 0; i < _size; ++i)
		{
			newElements[i] = _elements[i];
		}
		
		// Delete elements
		delete[] _elements;

		// Assign the new value
		_elements = newElements;
	}

}	// Namespace

#endif // __MMARRAY_H__