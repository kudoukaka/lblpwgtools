#include "CAFAna/Systs/EnergySysts.h"

namespace ana {
  const eScaleMuLArSyst keScaleMuLArSyst;
  const EnergyScaleMuSystND kEnergyScaleMuSystND;
  const EnergyScaleESyst kEnergyScaleESyst;
  const ChargedHadCorrSyst kChargedHadCorrSyst;
  const ChargedHadUncorrFDSyst kChargedHadUncorrFDSyst;
  const ChargedHadUncorrNDSyst kChargedHadUncorrNDSyst;
  const NUncorrNDSyst kNUncorrNDSyst;  
  const NUncorrFDSyst kNUncorrFDSyst;  
  const Pi0CorrSyst kEnergyScalePi0Syst;
  const Pi0UncorrNDSyst kPi0UncorrNDSyst;
  const Pi0UncorrFDSyst kPi0UncorrFDSyst;
  const ChargedHadAnticorrSyst kChargedHadAnticorrSyst;
  const Pi0AnticorrSyst kPi0AnticorrSyst;

  const UncorrNDHadLinSyst kUncorrNDHadLinSyst;
  const UncorrNDPi0LinSyst kUncorrNDPi0LinSyst;
  const UncorrNDNLinSyst kUncorrNDNLinSyst;
  const UncorrNDHadSqrtSyst kUncorrNDHadSqrtSyst;
  const UncorrNDPi0SqrtSyst kUncorrNDPi0SqrtSyst;
  const UncorrNDNSqrtSyst kUncorrNDNSqrtSyst;

  EnergySystVector GetEnergySysts()
  {
    EnergySystVector vec;
    vec.push_back(&keScaleMuLArSyst);
    vec.push_back(&kEnergyScaleMuSystND);
    vec.push_back(&kEnergyScaleESyst);
    vec.push_back(&kChargedHadCorrSyst);
    //    vec.push_back(&kChargedHadUncorrFDSyst);
    //    vec.push_back(&kChargedHadUncorrNDSyst);
    vec.push_back(&kNUncorrFDSyst);
    vec.push_back(&kNUncorrNDSyst);
    vec.push_back(&kEnergyScalePi0Syst);
    //    vec.push_back(&kPi0UncorrFDSyst);
    //    vec.push_back(&kPi0UncorrNDSyst);
    vec.push_back(&kPi0AnticorrSyst);
    vec.push_back(&kChargedHadAnticorrSyst);
    vec.push_back(&kUncorrNDHadLinSyst);
    vec.push_back(&kUncorrNDPi0LinSyst);
    vec.push_back(&kUncorrNDNLinSyst);
    vec.push_back(&kUncorrNDHadSqrtSyst);
    vec.push_back(&kUncorrNDPi0SqrtSyst);
    vec.push_back(&kUncorrNDNSqrtSyst);

    return vec;
  }
} // namespace
