/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Your Boy Dan                                              */
/*    Created:      Sat Nov 09 2019                                           */
/*    Description:  V5 code - 8869S                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "v5.h"
#include "v5_vcs.h"

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)

using namespace vex;

brain Brain;
motor DriveFL = motor(PORT1,gearSetting::ratio18_1, true);
motor DriveFR = motor(PORT3,gearSetting::ratio18_1, true);
motor DriveBL = motor(PORT4,gearSetting::ratio18_1, true);
motor DriveBR = motor(PORT6,gearSetting::ratio18_1, true);
motor LiftR = motor(PORT7,gearSetting::ratio36_1, true);
motor LiftL = motor(PORT8,gearSetting::ratio36_1);
motor ClawR = motor(PORT9,gearSetting::ratio36_1);
motor ClawL = motor(PORT10,gearSetting::ratio36_1);
controller Controller = controller();
competition Competition;


// void moveChassis(float flDeg, float frDeg, float brDeg, float blDeg){
//   bool fl = true;
//   bool fr = true;
//   bool bl = true;
//   bool br = true;
//   while(br||bl||fl||fr){
//     if(/*code to check if less than deg... motor encoder flDrive.encoder < flDeg  &&*/ fl ){
//        DriveFL.spin(directionType::fwd,50,velocityUnits::pct);
//     }else{
//       fl = false;
//     }
//     if(/*code to check if less than deg... motor encoder flDrive.encoder < flDeg  &&*/ fl ){
//        DriveFR.spin(directionType::fwd,50,velocityUnits::pct);
//     }else{
//       fr = false;
//     }
//     if(/*code to check if less than deg... motor encoder flDrive.encoder < flDeg  &&*/ fl ){
//        DriveBL.spin(directionType::fwd,50,velocityUnits::pct);
//     }else{
//       bl = false;
//     }
//     if(/*code to check if less than deg... motor encoder flDrive.encoder < flDeg  &&*/ fl ){
//        DriveBR.spin(directionType::fwd,50,velocityUnits::pct);
//     }else{
//       br = false;
//     }
//   }
// }

void moveLeft(float distance){
    DriveFL.resetRotation();
    DriveFR.resetRotation();
    DriveBL.resetRotation();
    DriveBR.resetRotation();

    float degrees = distance * 360 /(2*1.625*3.141592653); // distance was in inches
    DriveFL.spin(directionType::fwd,50,velocityUnits::pct);
    DriveBL.spin(directionType::fwd,-50,velocityUnits::pct);
    DriveFR.spin(directionType::fwd,50,velocityUnits::pct);
    DriveBR.rotateTo(degrees,rotationUnits::deg,-50,velocityUnits::pct);
    
    DriveFR.rotateTo(degrees,rotationUnits::deg,50,velocityUnits::pct, false);
    DriveFL.rotateTo(degrees,rotationUnits::deg,50,velocityUnits::pct, false);
    DriveBL.rotateTo(-degrees,rotationUnits::deg,50,velocityUnits::pct, false);
    DriveBR.rotateTo(-degrees,rotationUnits::deg,50,velocityUnits::pct, false);
}

void moveForward(float distance){
    DriveFL.resetRotation();
    DriveFR.resetRotation();
    DriveBL.resetRotation();
    DriveBR.resetRotation();

    float degrees = distance * 1.4142135 * 360 /(2*1.625*3.141592653); // distance was in inches
    DriveFR.rotateTo(degrees,rotationUnits::deg,50,velocityUnits::pct, false);
    DriveFL.rotateTo(-degrees,rotationUnits::deg,50,velocityUnits::pct, false);
    DriveBL.rotateTo(-degrees,rotationUnits::deg,50,velocityUnits::pct, false);
    DriveBR.rotateTo(degrees,rotationUnits::deg,50,velocityUnits::pct, false);
}

void moveBackward(float distance){
    DriveFL.resetRotation();
    DriveFR.resetRotation();
    DriveBL.resetRotation();
    DriveBR.resetRotation();

    float degrees = distance * 1.4142135 * 360 /(2*1.625*3.141592653); // distance was in inches

    DriveFR.rotateTo(-degrees,rotationUnits::deg,50,velocityUnits::pct, false);
    DriveFL.rotateTo(degrees,rotationUnits::deg,50,velocityUnits::pct, false);
    DriveBL.rotateTo(degrees,rotationUnits::deg,50,velocityUnits::pct, false);
    DriveBR.rotateTo(-degrees,rotationUnits::deg,50,velocityUnits::pct, false);
}

void moveRight(double distance){
    DriveFL.resetRotation();
    DriveFR.resetRotation();
    DriveBL.resetRotation();
    DriveBR.resetRotation();

    float degrees = distance * 1.4142135 * 360 /(2*1.625*3.141592653); // distance was in inches
    DriveFL.spin(directionType::fwd,-50,velocityUnits::pct);

    DriveFR.rotateTo(-degrees,rotationUnits::deg,50,velocityUnits::pct, false);
    DriveFL.rotateTo(-degrees,rotationUnits::deg,50,velocityUnits::pct, false);
    DriveBL.rotateTo(degrees,rotationUnits::deg,50,velocityUnits::pct, false);
    DriveBR.rotateTo(degrees,rotationUnits::deg,50,velocityUnits::pct, false);
}

void TurnRight(float degreesTurn){
    DriveFL.resetRotation();
    DriveFR.resetRotation();
    DriveBL.resetRotation();
    DriveBR.resetRotation();

    float distance = 8.25*2*3.141592653*degreesTurn/360;
    float degrees = distance * 360 /(2*1.625*3.141592653); // distance was in inches

    DriveFR.rotateTo(-degrees,rotationUnits::deg,50,velocityUnits::pct, false);
    DriveFL.rotateTo(-degrees,rotationUnits::deg,50,velocityUnits::pct, false);
    DriveBL.rotateTo(-degrees,rotationUnits::deg,50,velocityUnits::pct, false);
    DriveBR.rotateTo(-degrees,rotationUnits::deg,50,velocityUnits::pct, false);
}

void TurnLeft(float degrees){
    TurnRight(-degrees);
}

void LiftUP(double degrees){
    LiftR.resetRotation();
    LiftL.resetRotation();

    LiftR.rotateTo(degrees,rotationUnits::deg,100,velocityUnits::pct, false);
    LiftL.rotateTo(degrees,rotationUnits::deg,100,velocityUnits::pct, false);
   
}

void LiftDown(double degrees){
    LiftR.resetRotation();
    LiftL.resetRotation();

    LiftR.rotateTo(-degrees,rotationUnits::deg,100,velocityUnits::pct, false);
    LiftL.rotateTo(-degrees,rotationUnits::deg,100,velocityUnits::pct, false);

    LiftR.stop();
    LiftL.stop();    
}

void pre_auton( void ) {
    DriveFL.resetRotation();
    DriveFR.resetRotation();
    DriveBL.resetRotation();
    DriveBR.resetRotation();
    LiftR.resetRotation();
    LiftL.resetRotation();            
}

void autonomous( void ) {
    /*
  //dummy claw code here
  LiftUP(400);
  moveRight(1);
  moveForward(20);
  LiftDown(200);
  //dummy claw code here
  LiftDown(200);
  //dummy claw code here
  LiftUP(400);
  TurnRight(45);
  */
 moveForward(45);
 moveBackward(20);    
}

void usercontrol( void ) {
  while (1) {
      if(Controller.ButtonR1.pressing()){ 
          LiftR.spin(directionType::fwd,100,velocityUnits::pct);
          LiftL.spin(directionType::fwd,100,velocityUnits::pct);
      }else if(Controller.ButtonR2.pressing()){
          LiftR.spin(directionType::fwd,-100,velocityUnits::pct);
          LiftL.spin(directionType::fwd,-100,velocityUnits::pct);
      }else{
          LiftL.stop(brakeType::brake);
          LiftR.stop(brakeType::brake);
      }
      if(abs(Controller.Axis4.value()) <= 5 && abs(Controller.Axis1.value()) <= 5 && abs(Controller.Axis2.value()) <= 5){
          DriveFR.stop(brakeType::brake);
          DriveFL.stop(brakeType::brake);
          DriveBR.stop(brakeType::brake);
          DriveBL.stop(brakeType::brake);
    }else{
          DriveFR.spin(directionType::fwd,-Controller.Axis4.value() + Controller.Axis2.value() - Controller.Axis1.value(),velocityUnits::pct);
          DriveFL.spin(directionType::fwd,-Controller.Axis4.value() - Controller.Axis1.value() - Controller.Axis2.value(),velocityUnits::pct);
          DriveBR.spin(directionType::fwd,- Controller.Axis4.value() + Controller.Axis2.value() + Controller.Axis1.value(),velocityUnits::pct);
          DriveBL.spin(directionType::fwd,- Controller.Axis4.value() + Controller.Axis1.value() - Controller.Axis2.value(),velocityUnits::pct);
    }
      if(Controller.ButtonL1.pressing()){
          ClawR.spin(directionType::rev,-100,velocityUnits::pct);
          ClawL.spin(directionType::rev,100,velocityUnits::pct);
      }else if(Controller.ButtonL2.pressing()){
          ClawR.spin(directionType::rev,100,velocityUnits::pct);
          ClawL.spin(directionType::rev,-100,velocityUnits::pct);
      }else{
          ClawL.stop(brakeType::brake);
          ClawR.stop(brakeType::brake);
      }
           
    task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

int main() {
    pre_auton();
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );                      
    while(1) {
      task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }      
}
