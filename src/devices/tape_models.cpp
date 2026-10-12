#include "ibmlegacy/devices/tape_models.hpp"
namespace ibmlegacy::devices {
TapeDriveConfig ibm729_model_ii_profile(){return {"IBM 729 Model II (profile)",200,0,false};}
TapeDriveConfig ibm729_model_iv_profile(){return {"IBM 729 Model IV (profile)",556,0,false};}
TapeDriveConfig ibm2401_profile(){return {"IBM 2401 Magnetic Tape Unit (profile)",800,0,false};}
TapeDriveConfig ibm2402_profile(){return {"IBM 2402 Magnetic Tape Unit (profile)",800,0,false};}
TapeDriveConfig ibm2403_profile(){return {"IBM 2403 Magnetic Tape Unit and Control (profile)",800,0,false};}
TapeDriveConfig ibm2404_profile(){return {"IBM 2404 Magnetic Tape Unit and Control (profile)",1600,0,false};}
}