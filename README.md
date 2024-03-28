## FaroTech Base Robot Control Software

This is modified version of software used to control FRC 9281 Team robot in 2024 Istanbul Regional Event.

# FLOWCHART

                    Start
                      |
                      V
             Initialize Software
                      |
                      V
         Jump into Teleop/Autonomous
                      |
                      V
    --> Wait for signal from the driver <--
    |                                     |
    <--   Control Base or RingoShooter  -->
                      |
                      V
                 Stop Motors
                      |
                      V
                   Shutdown

## Things to change in future:
- Improve the stability and strength of the robot's structure for safe operation in a variety of field conditions.
- Improve the effectiveness of patient lifting and transport systems to optimize the process of evacuating the wounded.
- Continue development of the user interface and communication systems for ease of use by medical personnel and effective coordination of battlefield operations.
- Continue work on enhancing the autonomy and intelligence of the robot, enabling independent decision-making and adaptation to changing operational conditions. (GPS and Deep Learning based terrain recognition)
- Test and evaluate new features and modifications to the prototype based on feedback from medical personnel and battlefield medical experts.
- Consolidate field test data and analyzing the results to further optimize the design and adapt it to real battlefield needs.
