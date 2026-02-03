#include "vex.h"

using namespace vex;

brain Brain;
competition Competition;
controller Controller;
motor leftfront (PORT1, ratio6_1, true);
motor leftmiddle (PORT2, ratio6_1, true);
motor leftback (PORT3, ratio6_1, true);
motor rightfront (PORT4, ratio6_1, false);
motor rightmiddle (PORT5, ratio6_1, false);
motor rightback (PORT6, ratio6_1, false);
motor intake (PORT7, ratio18_1, true);
motor body (PORT8, ratio6_1, false);
motor director (PORT9, ratio18_1, true);
motor_group leftdrivetrain (leftfront, leftmiddle, leftback);
motor_group rightdrivetrain (rightfront, rightmiddle, rightback);
motor_group initalscoremech (intake);
motor_group bodyscoremeck (body);
drivetrain Train = drivetrain(leftdrivetrain, rightdrivetrain, 3.25 * M_PI, 12.5, 11, inches, 1.5);
digital_out Matchloader = digital_out(Brain.ThreeWirePort.A);
//DO NOT REMOVE
digital_out hook = digital_out(Brain.ThreeWirePort.B);

// this is the matchloader code
void MatchloaderToggle() {
  Matchloader.set(!Matchloader.value());
}
//this is for de-score hook DO NOT REMOVE
void hookToggle() {
  hook.set(!hook.value());
}

void pre_auton(void) {
}

void skillsplaceholder() {
  Train.setDriveVelocity(100, percent);
  Train.driveFor(3, inches);
  intake.spin(reverse);
   body.spin(reverse);
}

void compplaceholder() {
  Train.setDriveVelocity(80, percent);
Train.driveFor(58, inches);
Train.turnFor(-100, degrees);
}

void blueredright() {
  Train.setDriveVelocity(15, percent);
  Train.setTurnVelocity(100, percent);
  intake.setVelocity(100, percent);
  body.setVelocity(20, percent);
  director.setVelocity(40, percent);
  intake.spin(reverse);
  Train.driveFor(23, inches);
  body.spin(reverse);
   Train.driveFor(45, inches);
   Train.driveFor(-2, inches);
   Train.turnFor(-64, degrees);
   Train.driveFor(27, inches);
   body.spin(forward);
   intake.spin(forward, 60, velocityUnits::pct);

}

void redblueleft() {
  Train.setDriveVelocity(15, percent);
  Train.setTurnVelocity(100, percent);
  intake.setVelocity(100, percent);
  body.setVelocity(20, percent);
  director.setVelocity(40, percent);
  intake.spin(reverse);
  Train.driveFor(27, inches);
  body.spin(reverse);
   Train.driveFor(41, distanceUnits::in, 15, velocityUnits::pct);
   Train.driveFor(-9, inches);
   Train.turnFor(55, degrees);
   Train.driveFor(26.5, inches);
   body.spinFor(1, vex::timeUnits::sec);
   body.spin(reverse);
   director.spin(forward);


}
void Skillsauton() {
  Train.setDriveVelocity(100, percent);
  Train.driveFor(12, inches);
  Train.driveFor(36, inches)
}
void autonomous(void) {
  //blueredright();
  // skillsplaceholder();
  // compplaceholder();
  redblueleft();
}

void usercontrol(void) {
  while (1) {
    Train.arcade(Controller.Axis3.position(), Controller.Axis1.position());
    if (Controller.ButtonR2.pressing()) {
      initalscoremech.spin(forward, 100, percent);
    } else {
      initalscoremech.stop();
    }
    if (Controller.ButtonR1.pressing()) {
      initalscoremech.spin(reverse, 100, percent);
    }
    if (Controller.ButtonR1.pressing()) {
      bodyscoremeck.spin(reverse, 100, percent) ;
    } else {
      bodyscoremeck.stop();
    }
    if (Controller.ButtonR2.pressing()) {
      bodyscoremeck.spin(forward, 100, percent) ;
    }
    if (Controller.ButtonL2.pressing()) {
      director.spin(forward, 100, percent);
    } else {
      director.stop();
    }
    if (Controller.ButtonL1.pressing()) {
      director.spin(reverse, 100, percent);
    }
    wait(20, msec);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  Controller.ButtonB.pressed(MatchloaderToggle);
  Controller.ButtonY.pressed(hookToggle);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
