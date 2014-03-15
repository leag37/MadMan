//*************************************************************************************************
// Title: MMTask.cpp
// Author: Gael Huber
// Description: A task is a self-contained work unit. This class represents the base class for all
//	tasks to inherit and utilize.
//*************************************************************************************************
#include "core\MMTask.h"

namespace MadMan
{
	/**
	* Default constructor
	*/
	Task::Task()
		:	_status(PENDING)
	{ }

	/**
	* Destructor
	*/
	Task::~Task()
	{ }

	/**
	* Run this task
	*/
	void Task::run()
	{
		// Set the status to IN_PROGRESS
		_status = IN_PROGRESS;

		// Execute the task
		execute();

		// Set the status to DONE
		_status = DONE;
	}

	/**
	* Get the status of the task
	* @return
	*	TaskStatus The current status of the task
	*/
	TaskStatus Task::getStatus() const
	{
		return _status;
	}

}	// Namespace