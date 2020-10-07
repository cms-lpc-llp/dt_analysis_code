#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <algorithm>    // std::max
#include <stdlib.h>

void skim()
{
  std::vector<std::string> signalfiles = {
    "ggH_HToSSTobbbb_MH-125_MS-15_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted",
    "ggH_HToSSTobbbb_MH-125_MS-40_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted",
    "ggH_HToSSTobbbb_MH-125_MS-55_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted"
  };

  for (unsigned i = 0; i < signalfiles.size(); i++) {
   TChain* chain = new TChain("MuonSystem");
   chain->Add(TString(signalfiles[i]) + ".root");

   TFile* newFile = TFile::Open(TString(signalfiles[i]) + "_skim.root", "RECREATE");
   TTree* newChain = chain->CopyTree("met>=200");
   newChain->AutoSave();
   newFile->Close();
  }
}
