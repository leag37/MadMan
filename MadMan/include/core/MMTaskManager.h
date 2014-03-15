//*************************************************************************************************
// Title: MMTaskManager.h
// Author: Gael Huber
// Description: Manages a set of tasks
//*************************************************************************************************
#ifndef __MMTASKMANAGER_H__
#define __MMTASKMANAGER_H__

#include "MMSingleton.h"
#include "data_structures\MMLocklessQueue.h"
#include <Windows.h>

namespace MadMan
{
	/** \addtogroup Core
	*	@{
	*/

	class Task;
	class ThreadInfo;

	class TaskManager : public Singleton<TaskManager>
	{
	public:
		/**
		* Default constructor
		*/
		TaskManager();

		/**
		 * Destructor
		 */
		virtual ~TaskManager();

		/**
		 * Fetch the singleton instance
		 * @return 
		 *	T The singleton instance
		 */
		static TaskManager getSingleton()
		{
			assert(_singleton);
			return *_singleton;
		}

		/** 
		 * Fetch the singleton pointer
		 * @return 
		 *	T* A pointer to the singleton instance
		 */
		static TaskManager* getSingletonPtr()
		{
			return _singleton;
		}

		/**
		* Initialize the task manager
		*/
		void init();

		/** 
		* Shut down the task manager
		*/
		void shutDown();

		/**
		 * Fetch the info for a particular thread id
		 * @return
		 *	ThreadInfo* The information for the particular thread
		 */
		ThreadInfo* getInfoForThread(DWORD id);

		/**
		* Add a task
		* @param
		*	Task* The task to add to the queue
		* @return
		*	bool True if the task was added successfully
		*/
		bool addTask(Task* task);

		/**
		* Get a task from the queue
		* @param
		*	Task** Popuplates the pointer to the task
		* @return
		*	bool True if the task was successfully fetched
		*/
		bool getTask(Task** task);

		/**
		* Get the number of pending tasks
		* @return
		*	int The number of pending tasks
		*/
		unsigned int getNumTasks() const;

	private:
		TaskManager(const TaskManager& rhs);

		TaskManager& operator=(const TaskManager& rhs);

	private:
		/**
		* Array of threads and corresponding info
		*/
		ThreadInfo** _threads;
		
		/**
		 * Total number of threads
		 */
		unsigned int _numThreads;

		/**
		 * Number of inactive threads
		 */
		unsigned int _numInactiveThreads;

		/**
		* Task queue
		*/
		LocklessQueue<Task*> _taskQueue;
	};

	/** @} */

}	// Namespace

#endif // __MMTASKMANAGER_H__