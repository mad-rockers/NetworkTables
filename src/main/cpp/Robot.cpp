// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <frc/XboxController.h>
#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"


void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  // Get the default instance of NetworkTables that was created automatically
  // when the robot program starts
  auto inst = nt::NetworkTableInstance::GetDefault();

  // Get the table within that instance that contains the data. There can
  // be as many tables as you like and exist to make it easier to organize
  // your data. In this case, it's a table called datatable.
  auto table = inst.GetTable("datatable");

  // Start publishing topics within that table that correspond to the X and Y values
  // for some operation in your program.
  // The topic names are actually "/datatable/x" and "/datatable/y".
  xPub = table->GetDoubleTopic("x").Publish();
  yPub = table->GetDoubleTopic("y").Publish();
}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  frc::SmartDashboard::PutBoolean("bA : ", bA);
  frc::SmartDashboard::PutBoolean("bB : ", bB);
  frc::SmartDashboard::PutBoolean("bX : ", bX);
  frc::SmartDashboard::PutBoolean("bY : ", bY);
  frc::SmartDashboard::PutBoolean("leftbump : ", leftbump);
  frc::SmartDashboard::PutBoolean("rightbump : ", rightbump);
  frc::SmartDashboard::PutNumber("left_x : ", left_x);
  frc::SmartDashboard::PutNumber("left_y : ", left_y);
  frc::SmartDashboard::PutNumber("right_x : ", right_x);
  frc::SmartDashboard::PutNumber("right_y : ", right_y);
  frc::SmartDashboard::PutNumber("leftTrigger : ", leftTrigger);
  frc::SmartDashboard::PutNumber("rightTrigger : ", rightTrigger);
  frc::SmartDashboard::PutNumber("AprilTag_ID : ", tid);
  
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}

double x = 0;
double y = 0;

void Robot::TeleopPeriodic() {
  
  tid = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tid",0.0);
  leftbump = xbox.GetLeftBumper();
  rightbump = xbox.GetRightBumper();
  
  
  bA = xbox.GetAButton();
  bB = xbox.GetBButton();
  bX = xbox.GetXButton();
  bY = xbox.GetYButton();

  
  left_x = xbox.GetLeftX();
  left_y = xbox.GetLeftY();
  right_x = xbox.GetRightX();
  right_y = xbox.GetRightY();
  
  rightTrigger = xbox.GetRightTriggerAxis();
  leftTrigger = xbox.GetLeftTriggerAxis();

    // Publish values that are constantly increasing.
    xPub.Set(x);
    yPub.Set(y);
    x += 0.05;
    y += 0.05;

}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
