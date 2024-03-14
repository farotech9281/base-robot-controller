// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
// Copyright (c) FaroTech 9281

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <ctre/Phoenix.h>
#include <frc/XboxController.h>

class Robot : public frc::TimedRobot
{
  ctre::phoenix::motorcontrol::can::TalonSRX retractor{9}, r_retractor{8}, l_retractor{7};
  frc::XboxController drv_pad{0};
  bool enabled{false};

public:
  Robot()
  {
    r_retractor.SetInverted(true);
    l_retractor.SetInverted(true);
  }

  void RobotInit() override
  {
  }

  void TeleopPeriodic() override
  {
    if (drv_pad.GetAButtonPressed())
    {
      retractor.Set(TalonSRXControlMode::PercentOutput, 0.75);
      r_retractor.Set(TalonSRXControlMode::PercentOutput, 1.0);
      l_retractor.Set(TalonSRXControlMode::PercentOutput, 1.0);
    }
    else
    {
      retractor.Set(TalonSRXControlMode::PercentOutput, 0.0);
      r_retractor.Set(TalonSRXControlMode::PercentOutput, 0.0);
      l_retractor.Set(TalonSRXControlMode::PercentOutput, 0.0);
    }
  }
};

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif