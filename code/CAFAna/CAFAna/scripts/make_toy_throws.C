#include "common_fit_definitions.C"

void ParseThrowInstructions(std::string throwString, bool &stats, bool &fake, bool &start){

  std::vector<std::string> instructions = SplitString(throwString, ':');

  stats = false;
  fake  = false;
  start = false;
  
  for (auto & str : instructions){
    if (str == "stat"  || str == "all") stats = true;
    if (str == "fake"  || str == "all") fake = true;
    if (str == "start" || str == "all") start = true;
  }
  return;
}

// Need to accept filename, ND/FD, systs and reload as arguments
void make_toy_throws(std::string stateFname="common_state_mcc11v3.root",
		     std::string outputFname="throws_ndfd_nosyst.root",
		     int nthrows = 100,
		     std::string systSet = "nosyst", std::string sampleString = "ndfd",
		     std::string throwString="fake:start",
		     std::string penaltyString=""){
  
  gROOT->SetBatch(1);

  // Decide what is to be thrown
  bool stats_throw, fake_throw, start_throw;
  ParseThrowInstructions(throwString, stats_throw, fake_throw, start_throw);
  
  // Get the systematics to use
  std::vector<const ISyst*> systlist = GetListOfSysts(systSet);

  RemoveSysts(systlist, {"MFP_N", "MFP_pi"});
  
  // Oscillation parameters to use
  // std::vector<const IFitVar*> oscVars = {&kFitDmSq32Scaled, &kFitSinSqTheta23, &kFitTheta13,
  // 					 &kFitDeltaInPiUnits, &kFitSinSq2Theta12, &kFitDmSq21,
  // 					 &kFitRho};

  // Now with no OA
  std::vector<const IFitVar*> oscVars = {};
  
  // Setup output file
  TFile* fout = new TFile(outputFname.c_str(), "RECREATE");
  fout->cd();
  int hie = 1;

  for (int i=0; i<nthrows;++i){

    std::cout << "Starting throw " << i << std::endl;
    TDirectory* subDir = (TDirectory*) fout->mkdir(("throw_"+std::to_string(i)).c_str());

    // Set up throws for the starting value
    SystShifts fakeThrowSyst;
    osc::IOscCalculatorAdjustable* fakeThrowOsc;    
    if (fake_throw){
      fakeThrowOsc = ThrownNuFitOscCalc(hie, oscVars);    
      for(auto s: systlist) fakeThrowSyst.SetShift(s, GetBoundedGausThrow(s->Min()*0.8, s->Max()*0.8));
    } else {
      fakeThrowSyst = kNoShift;
      fakeThrowOsc = NuFitOscCalc(hie);
    }
    
    // Fit seeds
    SystShifts fitThrowSyst;
    osc::IOscCalculatorAdjustable* fitThrowOsc;
    if (start_throw){
      for(auto s: systlist) fitThrowSyst.SetShift(s, GetBoundedGausThrow(s->Min()*0.8, s->Max()*0.8));
      fitThrowOsc = ThrownNuFitOscCalc(hie, oscVars);
    } else {
      fitThrowSyst = kNoShift;
      fitThrowOsc = NuFitOscCalc(hie);
    }
    Fitter::Precision fitStrategy = Fitter::kNormal|Fitter::kIncludeHesse;
    // Now do a fit with thrown seeds
    std::map<const IFitVar*, std::vector<double>> oscSeeds;
    //oscSeeds[&kFitSinSqTheta23] = {.4, .6}; // try both octants
    //oscSeeds[&kFitDeltaInPiUnits] = {0, 0.5, 1, 1.5}; // Hold CAFAna's hand
    
    IExperiment *penalty = GetPenalty(hie, 1, penaltyString);
    
    double thischisq = RunFitPoint(stateFname, sampleString,
				   fakeThrowOsc, fakeThrowSyst, stats_throw,
				   oscVars, systlist,
				   fitThrowOsc, fitThrowSyst,
				   oscSeeds, penalty,
				   fitStrategy, subDir);
    
    std::cout << "Throw " << i << ": found minimum chi2 = " << thischisq << std::endl;

    fout  ->cd();
    subDir->Write();
    delete subDir;
    // Done with this systematic throw
  }

  // Now close the file
  fout->Close();
}

