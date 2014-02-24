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
		 *	DWORD The Id for this thread
		 */
		ThreadInfo(DWORD threadId);

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
		 * Set the isActive flag for this thread.
		 * @param
		 *	bool Whether this thread is marked as active or inactive
		 */
		void setIsActive(bool isActive);

	private:
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