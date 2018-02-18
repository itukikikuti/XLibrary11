class Timer {
	PROTECTED float time = 0.0f;
	PROTECTED float deltaTime = 0.0f;
	PROTECTED int frameRate = 0;
	PROTECTED float second = 0.0f;
	PROTECTED int frameCount = 0;
	LARGE_INTEGER preCount;
	LARGE_INTEGER frequency;

	PUBLIC Timer() {
		Initialize();
	}
	PUBLIC ~Timer() {
	}
	PROTECTED virtual void Initialize() {
		preCount = GetCounter();
		frequency = GetCountFrequency();
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
	PROTECTED LARGE_INTEGER GetCounter() {
		LARGE_INTEGER counter;
		QueryPerformanceCounter(&counter);
		return counter;
	}
	PROTECTED LARGE_INTEGER GetCountFrequency() {
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		return frequency;
	}
};
