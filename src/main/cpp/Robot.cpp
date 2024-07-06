// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
// Copyright (c) FaroTech 9281

#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/XboxController.h>
#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <ctre/Phoenix.h>

// Main class
class Robot : public frc::TimedRobot
{
  // Retractor and base motors definition
  // TODO: Verify motor controllers compatibility
  ctre::phoenix::motorcontrol::can::TalonSRX retractor{9}, r_retractor{8},
      l_retractor{7}, l_arm{6}, r_arm{5};
  ctre::phoenix::motorcontrol::can::VictorSPX m_frontLeft{1}, m_rearLeft{2},
      m_frontRight{3}, m_rearRight{4};

  // Initializing the DifferentialDrive object
  frc::DifferentialDrive m_drive{[&](double output)
                                 { m_frontLeft.Set(VictorSPXControlMode::PercentOutput, output); },
                                 [&](double output)
                                 { m_frontRight.Set(VictorSPXControlMode::PercentOutput, output); }};

  // Main controller object
  frc::XboxController drv_pad{0};
  bool enabled{false}; // enabled is used to determine if Retractor should be active

public:
  // Functions, that are being called after initialization of main Robot object
  void RobotInit() override
  {
    // inverting the two main retractor's motors
    r_retractor.SetInverted(true);
    l_retractor.SetInverted(true);

    // making the less significant motor follow the main ones
    m_rearLeft.Follow(m_frontLeft);
    m_rearRight.Follow(m_frontRight);
  }

  // The Robot's manual driving mode while true loop
  void TeleopPeriodic() override
  {
    // Enabling the TankDrive mode on Robot
    m_drive.TankDrive(-drv_pad.GetLeftY(), -drv_pad.GetRightY());

    // Listening for driver to press A on Xbox gamepad
    if (drv_pad.GetAButton())
    {
      // Retractor functions (pulling mode)
      retractor.Set(TalonSRXControlMode::PercentOutput, 0.75);
    }
    else // Disable the Retractor pulling mode if driver released the A button on gamepad
    {
      retractor.Set(TalonSRXControlMode::PercentOutput, 0.0);
    }

    if (drv_pad.GetBButton())
    {
      // Retractor functions (shooting mode)
      r_retractor.Set(TalonSRXControlMode::PercentOutput, 1.0);
      l_retractor.Set(TalonSRXControlMode::PercentOutput, 1.0);
    }
    else // Disable the Retractor shooting mode if driver released the B button on gamepad
    {
      r_retractor.Set(TalonSRXControlMode::PercentOutput, 0.0);
      l_retractor.Set(TalonSRXControlMode::PercentOutput, 0.0);
    }

    if (drv_pad.GetRightBumper()) // handling the arm functionality
    {
      r_arm.Set(TalonSRXControlMode::PercentOutput, 0.3);
      l_arm.Set(TalonSRXControlMode::PercentOutput, 0.3);
    }
    else if (drv_pad.GetLeftBumper())
    {
      r_arm.Set(TalonSRXControlMode::PercentOutput, -0.3);
      l_arm.Set(TalonSRXControlMode::PercentOutput, -0.3);
    }
    else
    {
      r_arm.Set(TalonSRXControlMode::PercentOutput, 0.0);
      l_arm.Set(TalonSRXControlMode::PercentOutput, 0.0);
    }
  }

  // Autonomous movement
  void AutonomousPeriodic()
  {
    m_drive.TankDrive(0.5, 0.5);
    sleep(2);
    m_drive.TankDrive(0.0, 0.0);
    exit(0);
  }
};

// function that starts the robot
#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
