#include <string>
#include <vector>
#include <map>

#include "TH1D.h"
#include "TFile.h"
#include "TH2D.h"
#include "TFile.h"

#include "TMath.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include "TTreeReader.h"
#include <map>
#include <string>
#include "TString.h"

std::map<std::string, std::vector<std::string> > signalfiles = {
  {"MC_Summer16", {
      "ggH_HToSSTobbbb_MH-125_MS-15_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root",
      "ggH_HToSSTobbbb_MH-125_MS-40_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root",
      "ggH_HToSSTobbbb_MH-125_MS-55_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root"
    }
  },
  {"MC_Fall17", {
      "ggH_HToSSTobbbb_MH-125_MS-15_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root",
      "ggH_HToSSTobbbb_MH-125_MS-40_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root",
      "ggH_HToSSTobbbb_MH-125_MS-55_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root"
    }
  },
  {"MC_Fall18", {
      "ggH_HToSSTobbbb_MH-125_MS-15_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root",
      "ggH_HToSSTobbbb_MH-125_MS-40_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root",
      "ggH_HToSSTobbbb_MH-125_MS-55_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root"
    }
  }
};

std::map<std::string, std::vector<std::string > > skimsignalfiles = {
  {"MC_Summer16", {
      "ggH_HToSSTobbbb_MH-125_MS-15_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.skim.root",
      "ggH_HToSSTobbbb_MH-125_MS-40_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.skim.root",
      "ggH_HToSSTobbbb_MH-125_MS-55_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.skim.root"
    }
  },
  {"MC_Fall17", {
      "ggH_HToSSTobbbb_MH-125_MS-15_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.skim.root",
      "ggH_HToSSTobbbb_MH-125_MS-40_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.skim.root",
      "ggH_HToSSTobbbb_MH-125_MS-55_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.skim.root"
    }
  },
  {"MC_Fall18", {
      "ggH_HToSSTobbbb_MH-125_MS-15_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.skim.root",
      "ggH_HToSSTobbbb_MH-125_MS-40_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.skim.root",
      "ggH_HToSSTobbbb_MH-125_MS-55_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.skim.root"
    }
  }
};
