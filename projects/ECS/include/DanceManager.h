#pragma once
#include "HumanoidRobot.h"
#include <vector>
#include <memory>
#include <numbers>
#include <cmath>

/*Interface used by dance objects*/
class DanceInterface {
	public:
		virtual void dance(HumanoidRobot& robot) = 0;
		virtual void reset() = 0;
};
/*Dance objects with custom dance behavior that can be associated with a robot*/
class Dance1 : public DanceInterface {
	public:
		Dance1();
		void dance(HumanoidRobot& robot) override;
		void reset() override;
	private:
		float m_dance1Angle;
		bool m_dance1RotateClkW;
		int m_windMillChecker;
};
class Dance2 : public DanceInterface {
	public:
		Dance2();
		void dance(HumanoidRobot& robot) override;
		void reset() override;
	private:
		bool m_dance2RaiseLimbs;
};
class Dance3 : public DanceInterface {
	public:
		Dance3();
		void dance(HumanoidRobot& robot) override;
		void reset() override;
	private:
		bool m_dance3ArmRaised;
		int m_dance3Counter;
};
class Dance4 : public DanceInterface {
	public:
		Dance4();
		void dance(HumanoidRobot& robot) override;
		void reset() override;
	private:
		int m_dance4Counter;
		bool m_dance4ArmRaised;
};
class Dance5 : public DanceInterface {
	public:
		Dance5();
		void dance(HumanoidRobot& robot) override;
		void reset() override;
	private:
		int m_dance5Counter;
};

/*Manages robots and their associated dances*/
class DanceManager {
public:
	DanceManager() : m_robots(nullptr){}
	void registerRobots(std::vector<HumanoidRobot>& robots);
	void restoreDefault(); //restores original position and rotation
	void setDance(int robotIndex, int danceIndex); //set robot dance specifically
	void setDefaultDances(); //sets default dances where each robot has a unique dance
	void setSyncDance(int danceIndex); //used to set robots to same dance
	void danceAllUnique(); //makes robots dance with their unique dances
	void danceAllSync(); //makes robots dance with their in sync dances
private:
	std::unique_ptr<DanceInterface> getDance(int danceIndex); // used for getting dance
	std::vector<HumanoidRobot>* m_robots; //pointer to robots
	std::vector<std::unique_ptr<DanceInterface>> m_uniqueDances;
	std::vector<std::unique_ptr<DanceInterface>> m_syncDances;
	std::vector<Vector3> m_originalPos; //original positions of the robots
};

