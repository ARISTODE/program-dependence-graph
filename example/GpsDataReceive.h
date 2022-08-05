/*!
 *  \file GpsDataRecieve.h
 *  \brief Utilities to fill out the non-encoded members of a GpsData_t.
 *
 *  The ICD of the ORION_PKT_GPS_DATA does not send any data in ECEF, it's
 *  all in LLA and NED. The utilities in this module use the LLA and NED data
 *  to compute ECEF equivalents to what is transmitted with the packet
 *  encoding. The ECEF data members of the GpsData_t structure are null
 *  encoded, which means they do not get sent when the packet is transmitted.
 *  Instead, when the packet is received, the utilities in this function
 *  fill out the ECEF data. This makes ECEF data available to receivers of this
 *  packet, without incurring the extra bandwidth of encoding that data.
 *
 *  The conversion functions are automatically called by the ProtoGen
 *  generated decodeGpsDataPacketStructure() function. To avoid circular
 *  includes the argument to these functions must be void pointers. This
 *  problem will be resolved when ProtoGen is upgraded.
 */

#ifndef GPS_DATA_RECEIVE_H_
#define GPS_DATA_RECEIVE_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//! Fill out null-encoded ECEF position and velocity members of the GpsData_t after it was received via ORION_PKT_GPS_DATA packet
void constructGpsEcefPosVel(void* gpsdata_t);

//! Fill out null-encoded ECEF uncertainty members of the GpsData_t after it was received via ORION_PKT_GPS_DATA packet
void constructGpsEcefUncertainty(void* gpsdata_t);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // GPS_DATA_RECEIVE_H_
