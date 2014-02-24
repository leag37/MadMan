//*************************************************************************************************
// Title: MMSingleton.h
// Author: Gael Huber
// Description: A singleton instance.
//*************************************************************************************************
#ifndef __MMSINGLETON_H__
#define __MMSINGLETON_H__

#include <assert.h>

namespace MadMan
{
	/** \addtogroup Core
	*	@{
	*/

	/**
	 *	Provides the base implementation for a Singleton-pattern class.
	 */
	template <typename T>
	class Singleton
	{
	public:
		/**
		 * Default constructor
		 */
		Singleton() 
		{ 
			// Assign singleton instance to self
			asset(_singleton != 0);
			_singleton = static_cast<T*>(this);
		}

		/**
		 * Destructor
		 */
		~Singleton()
		{
			// Delete the singleton instance
			if(_singleton != 0)
			{
				delete _singleton;
				_singleton = 0;
			}
		}

		/**
		 * Fetch the singleton instance
		 * @return 
		 *	T The singleton instance
		 */
		static T getSingleton()
		{
			assert(_singleton);
			return *_singleton;
		}

		/** 
		 * Fetch the singleton pointer
		 * @return 
		 *	T* A pointer to the singleton instance
		 */
		static T* getSingletonPtr()
		{
			return _singleton;
		}

	protected:
		/**
		 * Singleton instance
		 */
		static T* _singleton;

	private:
		/**
		 * Copy constructor
		 * @param
		 *	Singelton& Singleton to copy
		 */
		Singleton(const Singleton<T>& value)
		{
			// Do nothing
		}

		/**
		 * Assignment operator
		 * @param
		 *	Singleton& Singleton to assign
		 * @return
		 *	Singleton& Resultant singleton
		 */
		Singleton& operator=(const Singleton<T>& value)
		{
			*this = value;
			return *this;
		}
	};

	/** @} */

}	// Namespace

#endif // __MMSINGLETON_H__