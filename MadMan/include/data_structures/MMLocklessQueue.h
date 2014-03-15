//*************************************************************************************************
// Title: MMLocklessQueue.h
// Author: Gael Huber
// Description: A lockless queue accessible via multiple threads
//*************************************************************************************************
#ifndef __MMLOCKLESSQUEUE_H__
#define __MMLOCKLESSQUEUE_H__

#include <Windows.h>
#include <intrin.h>

// TEMP
#include <iostream>
// END TEMP

namespace MadMan
{
	/** \addtogroup data_structures
	*	@{
	*/

	template <typename T>
	class LocklessQueue
	{
	public:
		// Node class for lockless queue
		class Node;

	public:
		/**
		* Default constructor
		*/
		LocklessQueue()
		{
			//Node* node = new Node();
			_head = _tail = 0;//node;
			_size = 0;
		}

		/**
		* Destructor
		*/
		~LocklessQueue()
		{
			// TODO
		}

		/**
		* Enqueue a value
		* @param
		*	T The value to enqueue
		*/
		void enqueue(T value)
		{
			// Cases:
			// 1) 0 entries (head is 0 and tail is 0)
			//	- If both tail and head are 0
			// 		- Set tail to new value if _tail is 0
			//			- Set head to new value
			// 2) At least 1 entry (tail is not 0)
			// 	- If tail.next is not 0, move _tail forward
			//	- Else if tail.next is 0, set tail.next to new value (provided that tail.next is still 0)
			// 	- Try to set tail to be the new value
			Node* node = new Node();
			node->value = value;
			node->next = 0;

			Node* head = 0;
			Node* tail = 0;
			
			for(;;)
			{
				head = _head;
				tail = _tail;
				if(head == 0 && tail == 0)
				{
					if(InterlockedCompareExchange((long*)&_tail, (long)node, (long)tail) == 0)
					{
						InterlockedExchange((long*)&_head, (long)node);
						break;
					}
				}
				else if(head != 0 && tail != 0)
				{
					Node* next = tail->next;
					if(next != 0)
					{
						InterlockedCompareExchange((long*)&_tail, (long)next, (long)tail);
					}
					else if(tail == _tail)
					{
						if(InterlockedCompareExchange((long*)&tail->next, (long)node, (long)next) == (long)next)
						{
							InterlockedCompareExchange((long*)&_tail, (long)node, (long)tail);
							break;
						}
					}
				}
			}

			// Increment the queue size
			InterlockedIncrement(&_size);
		}

		/**
		* Dequeue an entry
		* @param
		*	T* The value from the front of the queue
		* @return
		*	bool Return true if the dequeue was successful, false otherwise
		*/
		bool dequeue(T* entry)
		{
			// Cases:
			// 1) 0 entries (head is 0 and tail is 0)
			//	- Fail
			// 2) 1 entry (head is tail)
			// 	- If head equals tail
			//		- Set _tail to 0 if _head is _tail
			//			- Remove head
			//			- Process removed entry
			// 3) At least 2 entries (head is not tail and neither is 0)
			//	- If head is _head
			// 		- Move _head forward to next as long as head is still _head
			Node* head = 0;
			Node* tail = 0;

			for(;;)
			{
				head = _head;
				tail = _tail;

				if(head == 0 || tail == 0)
				{
					return false;
				}
				else if(head == tail)
				{
					if(InterlockedCompareExchange((long*)&_tail, 0, (long)_head) == (long)_head)
					{
						head = _head;
						InterlockedExchange((long*)&_head, 0);
						break;
					}
				}
				else if(head == _head && _tail != 0)
				{
					if(InterlockedCompareExchange((long*)&_head, (long)head->next, (long)head) == (long)head)
					{
						break;
					}
				}
			}

			*entry = head->value;
			delete head;

			// Decrement the queue size
			InterlockedDecrement(&_size);

			// Dequeue was successful
			return true;
		}

		/**
		* Return the queue size
		* @return
		*	unsigned int The number of elements in the queue
		*/
		unsigned int getSize() const
		{
			return _size;
		}

	private:
		/**
		* The number of elements
		*/
		unsigned int _size;

		/**
		* Head of the queue
		*/
		Node* _head;

		/**
		* Tail of the queue
		*/
		Node* _tail;	 
	};

	/**
	* Implementation for node
	*/
	template <typename T>
	class LocklessQueue<T>::Node
	{
	public:
		/**
		* Default constructor
		*/
		Node()
		{
			next = 0;
		}

	public:
		Node* next;
		T value;
	};
	
	/** @} */
}	// Namespace

#endif // __MMLOCKLESSQUEUE_H__