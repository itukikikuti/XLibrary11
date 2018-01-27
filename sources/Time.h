class Time {
	PRIVATE float time = 0.0f;
	PRIVATE float deltaTime = 0.0f;
	PRIVATE int frameRate = 0;
	PRIVATE float second = 0.0f;
	PRIVATE int frameCount = 0;
	LARGE_INTEGER preCount;
	LARGE_INTEGER frequency;

	PUBLIC Time() {
		preCount = GetCounter();
		frequency = GetCountFrequency();
	}
	PUBLIC ~Time() {

	}
	PUBLIC float GetTime() {
		return time;
	}
	PUBLIC float GetDeltaTime() {
		return deltaTime;
	}
	PUBLIC int GetFrameRate() {
		return frameRate;
	}
	PUBLIC void Update() {

		LARGE_INTEGER count = GetCounter();
		deltaTime = (float)(count.QuadPart - preCount.QuadPart) / frequency.QuadPart;
		preCount = GetCounter();

		time += deltaTime;


		frameCount++;
		second += deltaTime;
		if (second >= 1.0f) {
			frameRate = frameCount;
			frameCount = 0;
			second -= 1.0f;
		}
	}
	PRIVATE LARGE_INTEGER GetCounter() {
		LARGE_INTEGER counter;
		QueryPerformanceCounter(&counter);
		return counter;
	}
	PRIVATE LARGE_INTEGER GetCountFrequency() {
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		return frequency;
	}
};
