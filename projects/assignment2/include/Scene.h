#pragma once

#include "HumanoidRobot.h"
#include "AudioController.h"
#include "Camera.h"
#include "Box.h"
#include "Axes.h"

//IGNORE THIS FILE, was trying to make everything fit into a single class but I was having issues with glut getting to work with it.
//it's a work in progress for the next assignment
class Scene{
	public:
		//calls initScene
		Scene();

		//initialize the scene
		void initScene();

		//draw the scene
		void drawScene();

		//function for handling input, used as a callback
		void processKeys(unsigned char key, int x, int y);
		void processMouse(int button, int state, int x, int y);

		//functions responsible for orbiting camera around robot in scene, used by menu class
		void orbitAroundX(int option);
		void orbitAroundY(int option);
		void orbitAroundZ(int option);

		//functions for changing camera perspective, used by menu class as callbacks when creating menu
		void changePerspectiveType(int option);

		//functions responsible for rotating robot,  as callbacks when creating menu
		void rotateAroundX(int option);
		void rotateAroundY(int option);
		void rotateAroundZ(int option);

		//functions responsible for changing robot body part colors, used by menu class as callbacks when creating menu
		void headColorChange(int option);
		void torsoColorChange(int option);
		void leftLegColorChange(int option);
		void leftArmColorChange(int option);
		void rightLegColorChange(int option);
		void rightArmColorChange(int option);

		////function responsible for animation, will be used within animation callback
		//void animation(int value) {
  //          if (dance) {
  //              if (!rotate_clockwise) {
  //                  angle += 1;
  //                  if (angle >= 45) {
  //                      rotate_clockwise = !rotate_clockwise;
  //                  }
  //              }
  //              else {
  //                  angle -= 1;
  //                  if (angle <= -45) {
  //                      rotate_clockwise = !rotate_clockwise;
  //                  }
  //              }
  //              //robot turns side to side
  //              robot.setAngle(angle - robot.getAngle('y'), 'y');
  //              //get right arm bodypart angle when 
  //              GLdouble leftArmXAngle = robot.getAngleBodyPart(BodyPart::LeftArm, 'x');
  //              //get left arm bodypart angle
  //              GLdouble rightArmXAngle = robot.getAngleBodyPart(BodyPart::RightArm, 'x');
  //              if (windMillChecker >= 180) {
  //                  //robot goes crazy and does the windmill because the music is too good
  //                  robot.rotateBodyPart(BodyPart::LeftArm, 'x', angle / 2);
  //                  robot.rotateBodyPart(BodyPart::RightArm, 'x', -angle / 2);
  //              }
  //              else {
  //                  //robot doesn't have enough energy to do the windmill, so he chillaxes until he can go crazy again
  //                  robot.rotateBodyPart(BodyPart::LeftArm, 'x', -angle / 2 - leftArmXAngle - 90);
  //                  robot.rotateBodyPart(BodyPart::RightArm, 'x', angle / 2 - rightArmXAngle - 90);
  //              }
  //              //increment windmill checker
  //              windMillChecker = (windMillChecker + 1) % 360;
  //              //till head sidie

  //          }
  //          else {
  //              //reset all animations
  //              if (robot.getAngle('y') != 0.0) {
  //                  //reset robot angle
  //                  robot.setAngle(-robot.getAngle('y'), 'y');
  //                  rotate_clockwise = true;
  //                  angle = 0.0;
  //                  //reset body part angles
  //                  GLdouble leftArmXAngle = robot.getAngleBodyPart(BodyPart::LeftArm, 'x');
  //                  GLdouble rightArmXAngle = robot.getAngleBodyPart(BodyPart::RightArm, 'x');
  //                  robot.rotateBodyPart(BodyPart::LeftArm, 'x', -leftArmXAngle);
  //                  robot.rotateBodyPart(BodyPart::RightArm, 'x', -rightArmXAngle);
  //              }
  //          }
  //          glutPostRedisplay();
  //          //call again for the future
  //          glutTimerFunc(16, animation, 0);
		//}



	private:
		//variables relating to how we should draw the scene
		char m_drawMode; //Indicates drawmode for the robot, whether that be wire mode, vertex mode, or solid mode
		bool m_drawAxis; //indicates whether to draw the axix or not
		bool m_grayScale;
		bool m_musicToggle;
		bool m_dance;
		GLdouble m_angle;
		bool m_rotateClockwise;
		int m_windMillChecker;
		//Objects in the scene
		Axes m_axe;
		HumanoidRobot m_robot;
		Camera m_camera;
		AudioController m_audioController;

};
