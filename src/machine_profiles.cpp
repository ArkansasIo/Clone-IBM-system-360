#include "ibmlegacy/runtime/machine_profiles.hpp"
namespace ibmlegacy::runtime {
MachineConfig ibm1401_4k_profile(){return {MachineKind::IBM1401,4000,"IBM 1401 4K educational profile",true,true,true};}
MachineConfig ibm1401_8k_profile(){return {MachineKind::IBM1401,8000,"IBM 1401 8K educational profile",true,true,true};}
MachineConfig system360_model30_profile(){return {MachineKind::System360,64*1024,"System/360 Model 30 illustrative profile",true,true,true};}
MachineConfig system360_model40_profile(){return {MachineKind::System360,128*1024,"System/360 Model 40 illustrative profile",true,true,true};}
MachineConfig system360_model50_profile(){return {MachineKind::System360,256*1024,"System/360 Model 50 illustrative profile",true,true,true};}
}