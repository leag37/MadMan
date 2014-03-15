//*************************************************************************************************
// Title: MMTimer.h
// Author: Gael Huber
// Description: Simple game timer
// Todo: Fix commenting within this class and the cpp class
//*************************************************************************************************
#ifndef __MMTIMER_H__
#define __MMTIMER_H__

namespace MadMan
{
	/** \addtogroup Core
	*	@{
	*/

	class Timer {
	public:
		/**
		* Default constructor
		*/
		Timer();

		/**
		* Destructor
		*/
		~Timer();

		/**
		* Query for total time in seconds
		* @return
		*	float The total time elapsed
		*/
		float totalTime() const;

		/**
		* Query for delta time in seconds
		* @return
		*	float The time elapsed since the last function call
		*/
		float deltaTime() const;

		// Reset the timer
		void reset();

		// Start the timer
		void start();

		// Stop the timer
		void stop();

		// Simulate a timer tick
		void tick();

	private:
		// Seconds per count
		double _secondsPerCount;

		// Current delta time
		double _deltaTime;

		// Time at timer reset
		__int64 _baseTime;

		// Time spent paused
		__int64 _pausedTime;

		// Stop time
		__int64 _stopTime;

		// Previous tick time
		__int64 _prevTime;

		// Current tick time
		__int64 _currTime;

		// Is the time currently stopped?
		bool _stopped;
	};

	/** @} */
}	// Namespace
#endif // __MMTIMER_H__