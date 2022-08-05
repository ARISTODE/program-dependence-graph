#ifndef QUATERNION_H
#define QUATERNION_H

/*!
 * \file
 * Quaternion is a 4 element vector that represents the rotation from the
 * body to a reference frame. The choice of reference frame is arbitrary but is
 * typically NED or ECEF.  Note that the roll, pitch, and yaw functions are
 * defined based on the reference frame.  They typically only make sense if the
 * reference frame is NED.
 */

#include "dcm.h"

//! Enumeration for a quaternion attitude vector
enum
{
    Q0,
    Q1,
    Q2,
    Q3,
    NQUATERNION
};

// C++ compilers: don't mangle us
#ifdef __cplusplus
extern "C" {
#endif

//! Convert a quaternion to a DCM
void quaternionToDCM(const float quat[NQUATERNION], DCM_t* dcm);

//! Convert a DCM to quaternion
void dcmToQuaternion(const DCM_t* dcm, float quat[NQUATERNION]);

//! Initialize the quaternion to 0 roll, 0 pitch, 0 yaw
void initQuaternion(float quat[NQUATERNION]);

//! Fill out the quaternion from an Euler roll angle
void setQuaternionBasedOnRoll(float quat[NQUATERNION], float roll);

//! Fill out the quaternion from an Euler pitch angle
void setQuaternionBasedOnPitch(float quat[NQUATERNION], float pitch);

//! Fill out the quaternion from an Euler yaw angle
void setQuaternionBasedOnYaw(float quat[NQUATERNION], float yaw);

//! Fill out the quaternion from Euler angles
void setQuaternionBasedOnEuler(float quat[NQUATERNION], float yaw, float pitch, float roll);

//! Compute the Euler yaw angle of a quaternion.
float quaternionYaw(const float quat[NQUATERNION]);

//! Compute the Euler pitch rotation of a quaternion.
float quaternionPitch(const float quat[NQUATERNION]);

//! Compute the cosine of the Euler pitch angle of a quaternion
float quaternionCosPitch(const float quat[NQUATERNION]);

//! Compute the sin of the Euler pitch angle of a quaternion
float quaternionSinPitch(const float quat[NQUATERNION]);

//! Compute the Euler roll rotation.
float quaternionRoll(const float quat[NQUATERNION]);

//! Compute the cosine of the Euler roll angle of a quaternion
float quaternionCosRoll(const float quat[NQUATERNION]);

//! Compute the sin of the Euler roll angle of a quaternion
float quaternionSinRoll(const float quat[NQUATERNION]);

//! Use a quaternion to rotate a vector.
void quaternionApplyRotation(const float quat[NQUATERNION], const float input[], float output[]);

//! Use a quaternion to rotate a vector, in the reverse direction.
void quaternionApplyReverseRotation(const float quat[NQUATERNION], const float input[], float output[]);

//! Compute the length of a quaternion which should be 1.0
float quaternionLength(const float quat[NQUATERNION]);

//! Multiply two quaternions together
float* quaternionMultiply( const float p[NQUATERNION], const float q[NQUATERNION], float r[NQUATERNION]);

//! Multiply two quaternions together such that r = p^-1*q
float* quaternionMultiplyInverseA( const float p[NQUATERNION], const float q[NQUATERNION], float r[NQUATERNION]);

//! Multiply two quaternions together such that r = p*q^-1
float* quaternionMultiplyInverseB( const float p[NQUATERNION], const float q[NQUATERNION], float r[NQUATERNION]);

//! Convert a quaternion to a rotation vector
float* quaternionToRotVec( const float quat[NQUATERNION],  float rotVec[NVECTOR3]);

//! Convert a rotation vector to a quaternion
float* rotVecToQuaternion( const float rotVec[NVECTOR3], float quat[NQUATERNION] );

//! Test quaternion operations
BOOL testQuaternion(void);

//////////////////////////////////////////////////
// Functions for double precision quaternion below

//! Convert a quaternion to a DCM
void quaterniondToDCM(const double quat[NQUATERNION], DCMd_t* dcm);

//! Convert a quaternion to a DCM (float)
void quaterniondToDCMf(const double quat[NQUATERNION], DCM_t* dcm);

//! Convert a DCM to quaternion
void dcmToQuaterniond(const DCMd_t* dcm, double quat[NQUATERNION]);

//! Convert a DCM (float) to quaternion
void dcmfToQuaterniond(const DCM_t* dcm, double quat[NQUATERNION]);

//! Initialize the quaternion to 0 roll, 0 pitch, 0 yaw
void initQuaterniond(double quat[NQUATERNION]);

//! Fill out the quaternion from an Euler roll angle
void setQuaterniondBasedOnRoll(double quat[NQUATERNION], double roll);

//! Fill out the quaternion from an Euler pitch angle
void setQuaterniondBasedOnPitch(double quat[NQUATERNION], double pitch);

//! Fill out the quaternion from an Euler yaw angle
void setQuaterniondBasedOnYaw(double quat[NQUATERNION], double yaw);

//! Fill out the quaternion from Euler angles
void setQuaterniondBasedOnEuler(double quat[NQUATERNION], double yaw, double pitch, double roll);

//! Compute the Euler yaw angle of a quaternion.
double quaterniondYaw(const double quat[NQUATERNION]);

//! Compute the Euler pitch rotation of a quaternion.
double quaterniondPitch(const double quat[NQUATERNION]);

//! Compute the cosine of the Euler pitch angle of a quaternion
double quaterniondCosPitch(const double quat[NQUATERNION]);

//! Compute the sin of the Euler pitch angle of a quaternion
double quaterniondSinPitch(const double quat[NQUATERNION]);

//! Compute the Euler roll rotation.
double quaterniondRoll(const double quat[NQUATERNION]);

//! Compute the cosine of the Euler roll angle of a quaternion
double quaterniondCosRoll(const double quat[NQUATERNION]);

//! Compute the sin of the Euler roll angle of a quaternion
double quaterniondSinRoll(const double quat[NQUATERNION]);

//! Use a quaternion to rotate a vector.
void quaterniondApplyRotation(const double quat[NQUATERNION], const double input[], double output[]);

//! Use a quaternion to rotate a vector, in the reverse direction.
void quaterniondApplyReverseRotation(const double quat[NQUATERNION], const double input[], double output[]);

//! Compute the length of a quaternion which should be 1.0
double quaterniondLength(const double quat[NQUATERNION]);

//! Multiply two quaternions together
double* quaterniondMultiply( const double p[NQUATERNION], const double q[NQUATERNION], double r[NQUATERNION]);

//! Multiply two quaternions together such that r = p^-1*q
double* quaterniondMultiplyInverseA( const double p[NQUATERNION], const double q[NQUATERNION], double r[NQUATERNION]);

//! Multiply two quaternions together such that r = p*q^-1
double* quaterniondMultiplyInverseB( const double p[NQUATERNION], const double q[NQUATERNION], double r[NQUATERNION]);

//! Convert a quaternion to a rotation vector
double* quaterniondToRotVec( const double quat[NQUATERNION],  double rotVec[NVECTOR3]);

//! Convert a rotation vector to a quaternion
double* rotVecToQuaterniond( const double rotVec[NVECTOR3], double quat[NQUATERNION] );

//! Test quaternion operations
BOOL testQuaterniond(void);

// C++ compilers: don't mangle us
#ifdef __cplusplus
}
#endif

#endif // QUATERNION_H
