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
		:	_threadId(0),
			_isActive(false)
	{ }

	/**
	* Constructor
	* @param
	*	DWORD The Id for this thread
	*/
	ThreadInfo::ThreadInfo(DWORD threadId)
		:	_threadId(threadId),
			_isActive(false)
	{ }

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
	* Set the isActive flag for this thread.
	* @param
	*	bool Whether this thread is marked as active or inactive
	*/
	void ThreadInfo::setIsActive(bool isActive)
	{
		_isActive = isActive;
	}

}	// Namespace