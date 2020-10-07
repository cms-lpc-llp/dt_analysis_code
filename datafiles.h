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

std::vector<std::string> datafiles = {
  "/store/user/dildick/delayedjetsanalysis/Data/Run2_displacedJetMuonNtupler_V1p17_Data2018_17Sept2018_Run2018-HighMET-17Sep2018_goodLumi.root",
  "/store/user/dildick/delayedjetsanalysis/Data/Run2_displacedJetMuonNtupler_V1p17_Data2017_Run2017-HighMET-17Nov2017_goodLumi.root",
  "/store/user/dildick/delayedjetsanalysis/Data/Run2_displacedJetMuonNtupler_V1p17_Data2016_Run2016-HighMET-07Aug17_goodLumi.root"
};
