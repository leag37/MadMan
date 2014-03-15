//*************************************************************************************************
// Title: MMThreadInfo.cpp
// Author: Gael Huber
// Description: Data accessor and control information for a thread
//*************************************************************************************************
#include "core\MMThreadInfo.h"

namespace MadMan
{
	/**
	* Default constructor
	*/
	ThreadInfo::ThreadInfo()
		:	_friendlyId(0),
			_threadProc(0),
			_threadId(0),
			_isActive(false)
	{ }

	/**
	* Constructor
	* @param
	*	DWORD The friendly id for this thread
	* @param
	*	HANDLE The thread process handle
	* @param
	*	DWORD The Id for this thread
	*/
	ThreadInfo::ThreadInfo(DWORD friendlyId, HANDLE threadProc, DWORD threadId)
		:	_friendlyId(friendlyId),
			_threadProc(threadProc),
			_threadId(threadId),
			_isActive(false)
	{ }

	/**
	* Destructor
	*/
	ThreadInfo::~ThreadInfo()
	{
		_friendlyId = 0;
		_threadProc = 0;
		_threadId = 0;
		_isActive = false;
	}

	/**
	* @return
	*	DWORD The friendly id for this thread
	*/
	DWORD ThreadInfo::getFriendlyId() const
	{
		return _friendlyId;
	}

	/**
	 * @return
	 *	HANDLE The thread process handle
	 */
	HANDLE ThreadInfo::getThreadProc() const
	{
		return _threadProc;
	}

	/**
	* @return
	*	DWORD The thread id
	*/
	DWORD ThreadInfo::getThreadId() const
	{
		return _threadId;
	}

	/**
	* @return
	*	bool True if the thread is active, false otherwise
	*/
	bool ThreadInfo::getIsActive() const
	{
		return _isActive;
	}

	/**
	 * Suspend the thread
	 * @return
	 *	bool True if the thread is successfully suspended, false otherwise
	 */
	bool ThreadInfo::suspend()
	{
		// If the thread is already suspended, return false
		if(_isActive == false)
		{
			return false;
		}

		// Set active to false as we prepare to suspend this thread
		_isActive = false;

		DWORD result = SuspendThread(_threadProc);

		// If result failed, set isActive back to true
		if(result == (DWORD) - 1)
		{
			_isActive = true;
		}

		return _isActive == false;
	}

	/** 
	 * Wake the thread
	 * @return
	 *	bool True if the thread is successfully resumed, false otherwise
	 */
	bool ThreadInfo::resume()
	{
		// If the thread is already active, return false
		if(_isActive == true)
		{
			return false;
		}

		// Set active to true so we know we are attempting to activate it
		_isActive = true;

		// Attempt to resume the thread
		DWORD result = ResumeThread(_threadProc);

		// If the resume failed, set isActive back to false
		if(result == (DWORD) - 1)
		{
			_isActive = false;
		}

		return _isActive == true;
	}

}	// Namespace