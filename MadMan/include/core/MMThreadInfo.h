//*************************************************************************************************
// Title: MMThreadInfo.h
// Author: Gael Huber
// Description: Data accessor and control information for a thread
//*************************************************************************************************
#ifndef __MMTHREADINFO_H__
#define __MMTHREADINFO_H__

#include <Windows.h>

namespace MadMan
{
	/** \addtogroup Core
	*	@{
	*/

	class ThreadInfo
	{
	public:
		/**
		 * Default constructor
		 */
		ThreadInfo();

		/**
		* Constructor
		* @param
		*	DWORD The friendly id for this thread
		* @param
		*	HANDLE The thread process handle
		* @param
		*	DWORD The Id for this thread
		*/
		ThreadInfo(DWORD friendlyId, HANDLE threadProc, DWORD threadId);

		/**
		* Destructor
		*/
		~ThreadInfo();

		/**
		* @return
		*	DWORD The friendly id for this thread
		*/
		DWORD getFriendlyId() const;

		/**
		* @return
		*	HANDLE The thread process handle
		*/
		HANDLE getThreadProc() const;

		/**
		* @return
		*	DWORD The thread id
		*/
		DWORD getThreadId() const;

		/**
		* @return
		*	bool True if the thread is active, false otherwise
		*/
		bool getIsActive() const;

		/**
		* Suspend the thread
		* @return
		*	bool True if the thread is successfully suspended, false otherwise
		*/
		bool suspend();

		/** 
		* Wake the thread
		* @return
		*	bool True if the thread is successfully resumed, false otherwise
		*/
		bool resume();
		
	private:
		/**
		 * The friendly id for the thread. Each thread has a friendly id that is used for quick lookup
		 * in the TaskManager
		 */
		DWORD _friendlyId;

		/**
		 * Handle to the thread
		 */
		HANDLE _threadProc;

		/**
		 * The thread id
		 */
		DWORD _threadId;

		/**
		 * Is this thread currently active?
		 */
		bool _isActive;
	};

	/** @} */

}	// Namespace

#endif // __MMTHREADINFO_H__