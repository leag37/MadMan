//*************************************************************************************************
// Title: MMTaskManager.cpp
// Author: Gael Huber
// Description: Manages a set of tasks
//*************************************************************************************************
#include "core\MMTaskManager.h"
#include "core\MMThreadInfo.h"
#include "core\MMTask.h"
#include <Windows.h>

// TEMP
#include "..\test\TestTask.h"
// END TEMP

namespace MadMan
{
	// Define thread process
	DWORD TaskHandler(LPVOID);

	// Initialize singleton
	template<> TaskManager* Singleton<TaskManager>::_singleton = 0;

	/**
	* Default constructor
	*/
	TaskManager::TaskManager()
		: Singleton()
	{ }

	/**
	* Destructor
	*/
	TaskManager::~TaskManager()
	{ }

	/**
	* Initialize the task manager
	*/
	void TaskManager::init()
	{
		// First, we must get the system information
		SYSTEM_INFO sysInfo;
		GetSystemInfo(&sysInfo);

		// The number of threads to initialize is the number of processors on the machine
		_numThreads = sysInfo.dwNumberOfProcessors;
		_numThreads = 0;

		// Create the threads
		_threads = new ThreadInfo*[_numThreads];
		_numInactiveThreads = _numThreads;

		for(unsigned int i = 0; i < _numThreads; ++i)
		{
			// Initialize thread info to 0
			_threads[i] = 0;

			// Create the thread
			DWORD threadId;
			HANDLE threadProc;
			threadProc = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&TaskHandler, 0, 0, &threadId);
			
			// Create a thread info to track each thread
			ThreadInfo* threadInfo = new ThreadInfo(i, threadProc, threadId);
			_threads[i] = threadInfo;

			//threadInfo->resume();
		}
	}

	/** 
	* Shut down the task manager
	*/
	void TaskManager::shutDown()
	{
	}

	/**
	* Fetch the info for a particular thread id
	* @return
	*	ThreadInfo* The information for the particular thread
	*/
	ThreadInfo* TaskManager::getInfoForThread(DWORD id)
	{
		for(unsigned int i = 0; i < _numThreads; ++i)
		{
			if(_threads[i] != 0)
			{
				if(_threads[i]->getThreadId() == id)
				{
					return _threads[i];
				}
			}
		}

		// Failed
		return 0;
	}

	/**
	* Add a task
	* @param
	*	Task* The task to add to the queue
	* @return
	*	bool True if the task was added successfully
	*/
	bool TaskManager::addTask(Task* task)
	{
		_taskQueue.enqueue(task);
		return true;
	}

	/**
	* Get a task from the queue
	* @param
	*	Task** Popuplates the pointer to the task
	* @return
	*	bool True if the task was successfully fetched
	*/
	bool TaskManager::getTask(Task** task)
	{
		return _taskQueue.dequeue(task);
	}

	/**
	* Get the number of pending tasks
	* @return
	*	int The number of pending tasks
	*/
	unsigned int TaskManager::getNumTasks() const
	{
		return _taskQueue.getSize();
	}

	// For now, keep this here
	DWORD TaskHandler(LPVOID threadParam)
	{
		// First, get thread info
		TaskManager* taskManager = TaskManager::getSingletonPtr();
		DWORD threadId = GetCurrentThreadId();

		// While the thread info is not yet available, keep requesting it
		ThreadInfo* info = 0;
		do
		{
			info = taskManager->getInfoForThread(threadId);
		} while(info == 0);

		// Next prepare to loop and get tasks
		Task* currentTask = 0;

		int a = 0;
		int b = 1;

		while(true)
		{
			int action = rand() % 2;
			Task* t;
			switch(action)
			{
			case 0:
				// Enqueue
				t = new TestTask(a, b);

				taskManager->addTask(t);

				++a;
				b += 2;

				break;

			case 1:
				// Dequeue
				if(taskManager->getTask(&t) == true)
				{
					t->run();
					delete t;
				}
				break;
			}
		}

		return 0;
	}

}	// Namespace