#include "DanceManager.h"


Dance1::Dance1() {
	reset();
}
void Dance1::dance(HumanoidRobot& robot) {
	if (m_dance1Angle >= 45 || m_dance1Angle <= -45) {
		m_dance1RotateClkW = !m_dance1RotateClkW;
	}
	if (m_dance1RotateClkW) {
		m_dance1Angle++;
	}
	else {
		m_dance1Angle--;
	}
	//robot turns side to side
	robot.setAngle(m_dance1Angle - robot.getAngle('y'), 'y');
	//get right arm bodypart angle when 
	GLdouble leftArmXAngle = robot.getAngleBodyPart(BodyPart::LeftArm, 'x');
	//get left arm bodypart angle
	GLdouble rightArmXAngle = robot.getAngleBodyPart(BodyPart::RightArm, 'x');
	if (m_windMillChecker >= 180) {
		//robot goes crazy and does the windmill because the music is too good
		robot.rotateBodyPart(BodyPart::LeftArm, 'x', m_dance1Angle / 2);
		robot.rotateBodyPart(BodyPart::RightArm, 'x', -m_dance1Angle / 2);
	}
	else {
		//robot doesn't have enough energy to do the windmill, so he chillaxes until he can go crazy again
		robot.rotateBodyPart(BodyPart::LeftArm, 'x', -m_dance1Angle / 2 - leftArmXAngle - 90);
		robot.rotateBodyPart(BodyPart::RightArm, 'x', m_dance1Angle / 2 - rightArmXAngle - 90);
	}
	//increment windmill checker
	m_windMillChecker = (m_windMillChecker + 1) % 360;
}
void Dance1::reset() {
	m_dance1Angle = 0;
	m_dance1RotateClkW = false;
	m_windMillChecker = 0;
}


Dance2::Dance2() {
	reset();
}
void Dance2::dance(HumanoidRobot& robot) {
	//raise arms
	if (!m_dance2RaiseLimbs) {
		robot.rotateBodyPart(BodyPart::LeftArm, 'z', -90);
		robot.rotateBodyPart(BodyPart::RightArm, 'z', 90);
		robot.rotateBodyPart(BodyPart::RightLeg, 'x', 90);
		m_dance2RaiseLimbs = true;
	}
	//https://en.wikipedia.org/wiki/Polar_coordinate_system
	//get current angle
	Vector3 pos = robot.getPos();
	float currentAngle = atan2(pos.z, pos.x) * 180.0f / std::numbers::pi;
	//increment angle
	currentAngle = fmodf(currentAngle + 0.5f, 360.0f);
	//get radius from center
	GLdouble radius = sqrt(pos.x * pos.x + pos.z * pos.z);
	//convert angle to radians
	float radians = currentAngle * std::numbers::pi / 180.0;
	//rotate dude around origin
	pos.x = radius * cos(radians);
	pos.z = radius * sin(radians);
	robot.setPos(pos);
	//make robot face the direction he's going
	radians += std::numbers::pi / 2.0f;
	//make robot spin in circles as he orbits
	robot.setAngle(1, 'y');
}
void Dance2::reset() {
	m_dance2RaiseLimbs = false;
}


Dance3::Dance3() {
	reset();
}
void Dance3::dance(HumanoidRobot& robot) {
	if (m_dance3ArmRaised == false) {
		robot.rotateBodyPart(BodyPart::LeftArm, 'z', -90);
		robot.rotateBodyPart(BodyPart::RightArm, 'z', 90);
		m_dance3ArmRaised = true;
	}
	//phase one is rase and lower right 
	if (m_dance3Counter < 45) {
		robot.rotateBodyPart(BodyPart::LeftArm, 'z', -1);
		robot.rotateBodyPart(BodyPart::RightArm, 'z', -1);
		robot.rotateBodyPart(BodyPart::Head, 'z', -0.5);
	}
	else if (m_dance3Counter < 90) {
		robot.rotateBodyPart(BodyPart::LeftArm, 'z', 1);
		robot.rotateBodyPart(BodyPart::RightArm, 'z', 1);
		robot.rotateBodyPart(BodyPart::Head, 'z', 0.5);
	}
	else if (m_dance3Counter < 135) {
		robot.rotateBodyPart(BodyPart::LeftArm, 'z', 1);
		robot.rotateBodyPart(BodyPart::RightArm, 'z', 1);
		robot.rotateBodyPart(BodyPart::Head, 'z', 0.5);
	}
	else if (m_dance3Counter < 180) {
		robot.rotateBodyPart(BodyPart::LeftArm, 'z', -1);
		robot.rotateBodyPart(BodyPart::RightArm, 'z', -1);
		robot.rotateBodyPart(BodyPart::Head, 'z', -0.5);
	}
	//handle leg movement
	if (m_dance3Counter % 60 < 15) {
		robot.rotateBodyPart(BodyPart::LeftLeg, 'x', 2);
		robot.rotateBodyPart(BodyPart::RightLeg, 'x', -2);
	}
	else if (m_dance3Counter % 60 < 30) {
		robot.rotateBodyPart(BodyPart::LeftLeg, 'x', -2);
		robot.rotateBodyPart(BodyPart::RightLeg, 'x', 2);
	}
	else if (m_dance3Counter % 60 < 45) {
		robot.rotateBodyPart(BodyPart::LeftLeg, 'x', -2);
		robot.rotateBodyPart(BodyPart::RightLeg, 'x', 2);
	}
	else {
		robot.rotateBodyPart(BodyPart::LeftLeg, 'x', 2);
		robot.rotateBodyPart(BodyPart::RightLeg, 'x', -2);
	}
	//make robot stuck in eternal flipping motion
	robot.setAngle(2, 'x');
	m_dance3Counter = (m_dance3Counter + 1) % 180;
}
void Dance3::reset() {
	m_dance3ArmRaised = false;
	m_dance3Counter = 0;
}


Dance4::Dance4() {
	reset();
}
void Dance4::dance(HumanoidRobot& robot) {
	if (m_dance4ArmRaised == false) {
		robot.rotateBodyPart(BodyPart::LeftArm, 'x', -90);
		robot.rotateBodyPart(BodyPart::RightArm, 'x', -90);
		m_dance4ArmRaised = true;
	}
	Vector3 pos = robot.getPos();
	/*handle pacing and spinning 180 degrees*/
	//pace backwards
	if (m_dance4Counter < 135) {
		pos.z -= 0.2;
		robot.setPos(pos);
	}
	//turn around 45
	else if (m_dance4Counter < 180) {
		robot.setAngle(4, 'y');
	}
	//pace forward some 90+45
	else if (m_dance4Counter < 315) {
		pos.z += 0.2;
		robot.setPos(pos);
	}
	//turn around 45
	else {
		robot.setAngle(4, 'y');
	}
	//handle leg and arm movement
	if (m_dance4Counter % 60 < 15) {
		robot.rotateBodyPart(BodyPart::LeftLeg, 'x', 2);
		robot.rotateBodyPart(BodyPart::RightLeg, 'x', -2);
		robot.rotateBodyPart(BodyPart::RightArm, 'x', 2);
		robot.rotateBodyPart(BodyPart::LeftArm, 'x', -2);
	}
	else if (m_dance4Counter % 60 < 30) {
		robot.rotateBodyPart(BodyPart::LeftLeg, 'x', -2);
		robot.rotateBodyPart(BodyPart::RightLeg, 'x', 2);
		robot.rotateBodyPart(BodyPart::RightArm, 'x', -2);
		robot.rotateBodyPart(BodyPart::LeftArm, 'x', 2);
	}
	else if (m_dance4Counter % 60 < 45) {
		robot.rotateBodyPart(BodyPart::LeftLeg, 'x', -2);
		robot.rotateBodyPart(BodyPart::RightLeg, 'x', 2);
		robot.rotateBodyPart(BodyPart::RightArm, 'x', -2);
		robot.rotateBodyPart(BodyPart::LeftArm, 'x', 2);
	}
	else {
		robot.rotateBodyPart(BodyPart::LeftLeg, 'x', 2);
		robot.rotateBodyPart(BodyPart::RightLeg, 'x', -2);
		robot.rotateBodyPart(BodyPart::RightArm, 'x', 2);
		robot.rotateBodyPart(BodyPart::LeftArm, 'x', -2);
	}
	m_dance4Counter = (m_dance4Counter + 1) % 360;
}
void Dance4::reset() {
	m_dance4Counter = 0;
	m_dance4ArmRaised = false;
}

Dance5::Dance5() {
	reset();
}
void Dance5::dance(HumanoidRobot& robot) {
	Vector3 pos = robot.getPos();
	//fly up into air while raising arms and flipping upside down and make legs go out 90 degrees
	if (m_dance5Counter < 45) {
		pos.y += 0.2;
		robot.setAngle(8, 'y');
		robot.setAngle(4, 'x');
		robot.rotateBodyPart(BodyPart::RightArm, 'z', 2);
		robot.rotateBodyPart(BodyPart::LeftArm, 'z', -2);
		robot.rotateBodyPart(BodyPart::RightLeg, 'x', 2);
		robot.rotateBodyPart(BodyPart::LeftLeg, 'x', -2);
	}
	//spin and land and make legs go in
	else if (m_dance5Counter < 90) {
		robot.setAngle(16, 'y');
		pos.y -= 0.25;
		robot.rotateBodyPart(BodyPart::RightLeg, 'x', -2);
		robot.rotateBodyPart(BodyPart::LeftLeg, 'x', 2);
	}
	//spin on head in a big circle really fast
	else if (m_dance5Counter < 180) {
		robot.setAngle(32, 'y');
	}
	//fly up in air again while spinning still and flipping and make legs go 90 degrees
	else if (m_dance5Counter < 225) {
		pos.y += 0.25;
		robot.setAngle(4, 'x');
		robot.setAngle(16, 'y');
		robot.rotateBodyPart(BodyPart::RightLeg, 'x', 2);
		robot.rotateBodyPart(BodyPart::LeftLeg, 'x', -2);
	}
	//land while lowering arms and still spinning and make legs go in
	else {
		pos.y -= 0.2;
		robot.rotateBodyPart(BodyPart::RightArm, 'z',-2);
		robot.rotateBodyPart(BodyPart::LeftArm, 'z', 2);
		robot.rotateBodyPart(BodyPart::RightLeg, 'x', -2);
		robot.rotateBodyPart(BodyPart::LeftLeg, 'x', 2);
		robot.setAngle(8, 'y');
	}
	robot.setPos(pos);
	m_dance5Counter = (m_dance5Counter + 1) % 270;
}
void Dance5::reset() {
	m_dance5Counter = 0;
}

/*Dance Manager function implementation*/
void DanceManager::registerRobots(std::vector<HumanoidRobot>& robots) {
	m_robots = &robots;
	m_originalPos.clear();
	for (auto& robot : robots) {
		Vector3 position = robot.getPos();
		m_originalPos.push_back(position);
	}
	m_uniqueDances.resize(robots.size());
	m_syncDances.resize(robots.size());
	restoreDefault();
}
void DanceManager::restoreDefault() {
	if (m_robots == nullptr) {
		return;
	}
	//reset all robots to default position
	for (int i = 0; i < m_robots->size(); i++) {
		//set default position
		m_robots->at(i).setPos({ m_originalPos[i].x, m_originalPos[i].y, m_originalPos[i].z});
	}
	//reset all robot rotations
	std::vector<char> dimensions = { 'x','y', 'z' };
	for (auto& robot : *m_robots) {
		//reset all rotation regarding the rotation itself
		for (char dimension : dimensions) {
			robot.setAngle(-robot.getAngle(dimension), dimension);
		}

		//reset all rotation regarding the limbs
		for (char dimension : dimensions) {
			robot.rotateBodyPart(BodyPart::Head, dimension, -robot.getAngleBodyPart(BodyPart::Head, dimension));
			robot.rotateBodyPart(BodyPart::Torso, dimension, -robot.getAngleBodyPart(BodyPart::Torso, dimension));
			robot.rotateBodyPart(BodyPart::LeftArm, dimension, -robot.getAngleBodyPart(BodyPart::LeftArm, dimension));
			robot.rotateBodyPart(BodyPart::RightArm, dimension, -robot.getAngleBodyPart(BodyPart::RightArm, dimension));
			robot.rotateBodyPart(BodyPart::LeftLeg, dimension, -robot.getAngleBodyPart(BodyPart::LeftLeg, dimension));
			robot.rotateBodyPart(BodyPart::RightLeg, dimension, -robot.getAngleBodyPart(BodyPart::RightLeg, dimension));
		}
	}
	//reset all dance objects
	for (int i = 0; i < m_uniqueDances.size(); i++) {
		if (m_uniqueDances[i] != nullptr) {
			m_uniqueDances[i]->reset();
		}
		
	}
	for (int i = 0; i < m_syncDances.size(); i++) {
		if (m_syncDances[i] != nullptr) {
			m_syncDances[i]->reset();
		}
		
	}

}
void DanceManager::setDance(int robotIndex, int danceIndex) {
	if (!m_robots) {
		return;
	}
	if (robotIndex >= m_robots->size() || robotIndex < 0) {
		return;
	}
	if (danceIndex > 4 || danceIndex < 0) {
		return;
	}
	m_uniqueDances[robotIndex] = std::move(getDance(danceIndex));
}
void DanceManager::setDefaultDances() {
	if (!m_robots) {
		return;
	}
	//restore to default settings
	restoreDefault();
	//give robots new their dances
	for (int i = 0; i < m_robots->size(); i++) {
		setDance(i, i);
	}
}
void DanceManager::setSyncDance(int danceIndex) {
	if (!m_robots) {
		return;
	}
	if (danceIndex < 0 || danceIndex > 4) {
		return;
	}
	//restore to default settings
	restoreDefault();
	//assign their synchronous dances
	for (int i = 0; i < m_robots->size(); i++) {
		m_syncDances[i] = std::move(getDance(danceIndex));
	}
}
void DanceManager::danceAllUnique() {
	if (!m_robots) {
		return;
	}
	for (int i = 0; i < m_robots->size(); i++) {
		if (m_uniqueDances[i] != nullptr) {
			m_uniqueDances[i]->dance(m_robots->at(i));
		}
	}
}

void DanceManager::danceAllSync() {
	if (!m_robots) {
		return;
	}
	for (int i = 0; i < m_robots->size(); i++) {
		if (m_syncDances[i] != nullptr) {
			m_syncDances[i]->dance(m_robots->at(i));
		}
	}
}

std::unique_ptr<DanceInterface> DanceManager::getDance(int danceIndex) {
	if (danceIndex < 0) {
		danceIndex = 0;
	}
	danceIndex %= 5;
	switch (danceIndex) {
		case 0:
			return std::make_unique<Dance1>();
			break;
		case 1:
			return std::make_unique<Dance2>();
			break;
		case 2:
			return std::make_unique<Dance3>();
			break;
		case 3:
			return std::make_unique<Dance4>();
			break;
		case 4:
			return std::make_unique<Dance5>();
			break;
	}
}