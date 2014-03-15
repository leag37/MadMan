//*************************************************************************************************
// Title: MMTask.h
// Author: Gael Huber
// Description: A task is a self-contained work unit. This class represents the base class for all
//	tasks to inherit and utilize.
//*************************************************************************************************
#ifndef __MMTASK_H__
#define __MMTASK_H__

namespace MadMan
{
	/** \addtogroup Core
	*	@{
	*/

	enum TaskStatus
	{
		PENDING = 0,
		IN_PROGRESS,
		DONE
	};

	class Task
	{
	public:
		/**
		* Default constructor
		*/
		Task();

		/**
		* Destructor
		*/
		virtual ~Task();

		/**
		* Run this task
		*/
		void run();

		/**
		* Get the status of the task
		* @return
		*	TaskStatus The current status of the task
		*/
		TaskStatus getStatus() const;

	protected:
		/** 
		* The core execution of the task
		*/
		virtual void execute() = 0;

	private:
		/**
		 * The current status of the task
		 */
		TaskStatus _status;
	};

	/** @} */

}	// Namespace

#endif // __MMTASK_H__