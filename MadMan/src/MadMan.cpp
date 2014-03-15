//*************************************************************************************************
// Title: MadMan.cpp
// Author: Gael Huber
// Description: Entry point for Mad Man Engine
//*************************************************************************************************
#include "core\MMTaskManager.h"

#include <random>
#include <time.h>
#include "..\test\TestTask.h"
#include "core\MMTimer.h"

namespace MadMan
{
	unsigned long TestTask::Iterations = 0;
}

using namespace MadMan;

int main()
{
	// Create task manager
	TaskManager* taskManager = new TaskManager();
	taskManager->init();
	
	srand((unsigned int)time(0));
	int a = 0;
	int b = 1;

	TestTask::Iterations = 0;
	Timer timer;
	timer.reset();
	timer.start();

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

		// Take a poll of the current time
		static float elapsedTime = 0.0f;
		timer.tick();
		elapsedTime += timer.deltaTime();
		if(elapsedTime > 1.0f)
		{
			std::cout << "Performed " << TestTask::Iterations << " tasks per second." << std::endl;
			InterlockedExchange(&TestTask::Iterations, 0);
			elapsedTime = 0.0f;
		}
		
	}

	return 0;
}