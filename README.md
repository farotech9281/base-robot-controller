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
- Modify / Upgrade Ringo Shooter to be able to take people
- Robot must be able to transport at least 1 person
- GPS based Autonomous drive
- Implement computer vision algorithm that detects the difficulty of the terrain