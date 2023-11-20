#pragma once
class MapGenerator
{
private:
	static int i_mProgress;

public:
	MapGenerator();
	~MapGenerator();

	static int GetProgress() { return i_mProgress; }
	static void SetProgress(int _mProgress) { i_mProgress = _mProgress; }

	static void Start();
	static void Divide();
	static void GenerateRoom();
	static void GenerateRoad();
};

