#include "CAFAna/Systs/NuOnESysts.h"

namespace ana {
  const NuOnECCBkgSyst kNuOnECCBkgSyst;
  const NuOnENCBkgSyst kNuOnENCBkgSyst;
  const NuOnERecoEffSyst kNuOnERecoEffSyst;

  NuOnESystVector GetNuOnESysts()
  {
    NuOnESystVector vec;
    vec.push_back(&kNuOnECCBkgSyst);
    vec.push_back(&kNuOnENCBkgSyst);
    vec.push_back(&kNuOnERecoEffSyst);
    return vec;
  }

}
