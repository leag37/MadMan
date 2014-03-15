// Create a sample task that adds two numbers
#ifndef __TESTTASK_H__
#define __TESTTASK_H__

#include "core\MMTask.h"
#include <iostream>
#include <Windows.h>

namespace MadMan
{
	class TestTask : public Task
	{
	public:
		TestTask(int a, int b)
			:	Task(),
				_a(a),
				_b(b)
		{ }

		~TestTask()
		{ }

		int getC() const
		{
			return _c;
		}

		static unsigned long Iterations;

	protected:
		void execute()
		{
			_c = _a + _b;

			InterlockedIncrement(&Iterations);
		}

	private:
		int _a;
		int _b;
		int _c;
	};

}	// Namespace

#endif // __TESTTASK_H__