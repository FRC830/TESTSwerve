// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/Encoder.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/ProfiledPIDController.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/kinematics/SwerveModuleState.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <units/angular_velocity.h>
#include <units/time.h>
#include <units/velocity.h>
#include <units/voltage.h>
#include <wpi/numbers>
#include <rev/SparkMaxRelativeEncoder.h>
#include <rev/CANSparkMax.h>
#include <ctre/phoenix/sensors/CANCoder.h>


class SwerveModule {
    public:
        SwerveModule(int driveMotorChannel, int turningMotorChannel,
                     int driveEncoderChannelA, int driveEncoderChannelB,
                     int turningEncoderChannelA, int turningEncoderChannelB);
    frc::SwerveModuleState GetState() const;
    void SetDesiredState(const frc::SwerveModuleState& state);

    private:
        static constexpr double kWheelRadius = 0.0508;
        static constexpr int kEncoderResolution = 4096;

    static constexpr auto kModuleMaxAngularVelocity = wpi::numbers::pi * 1_rad_per_s;  // radians per second
    
    static constexpr auto kModuleMaxAngularAcceleration = wpi::numbers::pi * 2_rad_per_s / 1_s;  // radians per second^2

    rev::CANSparkMax m_driveMotor;
    rev::CANSparkMax m_turningMotor;

    rev::SparkMaxRelativeEncoder m_driveEncoder; 
    
    //commented out as we need an absolute encoder
    //rev::SparkMaxRelativeEncoder m_turningEncoder;

    rev::SparkMaxRelativeEncoder m_turningEncoder;


    frc2::PIDController m_drivePIDController{0.05, 0, 0};
    frc::ProfiledPIDController<units::radians> m_turningPIDController{
        0.05,
        0.0,
        0.0,
        {kModuleMaxAngularVelocity, kModuleMaxAngularAcceleration}
    };

    frc::SimpleMotorFeedforward<units::meters> m_driveFeedforward{
        0_V,
        0_V / 1_mps
    };

    frc::SimpleMotorFeedforward<units::radians> m_turnFeedforward{
        0_V, 0_V / 1_rad_per_s
    };
};
