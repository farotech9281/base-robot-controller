// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
// Copyright (c) FaroTech 9281

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <ctre/Phoenix.h>
#include <frc/XboxController.h>
#include <frc/motorcontrol/MotorControllerGroup.h>

class Robot : public frc::TimedRobot
{
  ctre::phoenix::motorcontrol::can::TalonSRX retractor{9}, r_retractor{8}, l_retractor{7};
  ctre::phoenix::motorcontrol::can::VictorSPX m_frontLeft{1}, m_rearLeft{2}, m_frontRight{3}, m_rearRight{4};

  frc::DifferentialDrive m_drive{[&](double output)
                                 { m_frontLeft.Set(VictorSPXControlMode::PercentOutput, output); },
                                 [&](double output)
                                 { m_frontRight.Set(VictorSPXControlMode::PercentOutput, output); }};
  frc::XboxController drv_pad{0};
  bool enabled{false};

public:
  Robot()
  {
  }

  void RobotInit() override
  {

    r_retractor.SetInverted(true);
    l_retractor.SetInverted(true);

    m_rearLeft.Follow(m_frontLeft);
    m_rearRight.Follow(m_frontRight);
  }

  void TeleopPeriodic() override
  {

    m_drive.TankDrive(-drv_pad.GetLeftY(), -drv_pad.GetRightY());

    if (drv_pad.GetAButton())
    {
      // TODO: Set 7 more power than 8
      retractor.Set(TalonSRXControlMode::PercentOutput, 0.75);
      r_retractor.Set(TalonSRXControlMode::PercentOutput, 1.2);
      l_retractor.Set(TalonSRXControlMode::PercentOutput, 1.2);
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