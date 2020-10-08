R__LOAD_LIBRARY(libTreePlayer)

#include "helpers.h"
#include "datafiles.h"

void analyzeData_ABCD(){

  const bool useHDFS(false);
  const bool useCERN(false);
  TString fsPreFix;
  if (useHDFS) {
    fsPreFix = "/mnt/hadoop";
  }
  else {
    fsPreFix = "root://cmsxrootd.fnal.gov/";
    if (useCERN) fsPreFix = "root://cms-xrd-global.cern.ch//";
  }

  fsPreFix += "/store/user/dildick/delayedjetsanalysis/Data/";

  char name[50];
  char title[100];
  char years[4][10] = {"2018","2017","2016"};
  char runNames[3][20] = {"17Sept2018_Run2018","Run2017","Run2016"};
  char dates[3][20] = {"17Sep2018","17Nov2017","07Aug17"};
  TString dir(fsPreFix + "/store/group/phys_exotica/delayedjets/displacedJetMuonAnalyzer/driftTube/V1p17/Data");
  TFile *_ofile = TFile::Open("outData_ABCD.root","RECREATE");

  TH1D *h_dtRechitClusterSize_dPhiJetMETLow_rpcCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_dPhiJetMETHigh_rpcCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_dPhiJetMETLow_rpcCRnoLepton[4];
  TH1D *h_dtRechitClusterSize_dPhiJetMETHigh_rpcCRnoLepton[4];
  TH1D *h_dtRechitClusterSize_dPhiClusterMETLow_rpcCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_dPhiClusterMETHigh_rpcCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_dPhiClusterMETLow_rpcSpreadCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_dPhiClusterMETHigh_rpcSpreadCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_dPhiClusterMETLow_rpcCRnoLepton[4];
  TH1D *h_dtRechitClusterSize_dPhiClusterMETHigh_rpcCRnoLepton[4];

  TH1D *h_dtRechitClusterSize_rpcMatch_jetMETCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_rpcNoMatch_jetMETCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_dPhiClusterMETLow_jetMETCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_dPhiClusterMETHigh_jetMETCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_rpcMatch_jetMETCRnoLepton[4];
  TH1D *h_dtRechitClusterSize_rpcNoMatch_jetMETCRnoLepton[4];
  TH1D *h_dtRechitClusterSize_dPhiClusterMETLow_jetMETCRnoLepton[4];
  TH1D *h_dtRechitClusterSize_dPhiClusterMETHigh_jetMETCRnoLepton[4];

  TH1D *h_dtRechitClusterSize_rpcGood_clusterMETCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_rpcBad_clusterMETCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_rpcMatch_clusterMETCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_rpcNoMatch_clusterMETCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_rpcSpread_clusterMETCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_rpcNoSpread_clusterMETCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_rpcNegativeSpread_clusterMETCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_rpcNegativeNoSpread_clusterMETCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_dPhiJetMETLow_clusterMETCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_dPhiJetMETHigh_clusterMETCRmuonVeto[4];
  TH1D *h_dtRechitClusterSize_rpcMatch_clusterMETCRnoLepton[4];
  TH1D *h_dtRechitClusterSize_rpcNoMatch_clusterMETCRnoLepton[4];
  TH1D *h_dtRechitClusterSize_dPhiJetMETLow_clusterMETCRnoLepton[4];
  TH1D *h_dtRechitClusterSize_dPhiJetMETHigh_clusterMETCRnoLepton[4];

  TH1D *h_dPhiClusterRPC_fullVeto[4];
  TH1D *h_dZClusterRPC_fullVeto[4];
  TH1D *h_rpcSpread_invertedJetVeto[4];
  TH1D *h_rpcSpread_invertedJetVeto_muonVeto[4];
  TH1D *h_rpcSpread_fullVeto[4];
  TH1D *h_rpcSpread_fullVeto_negBx[4];

  TH1D *h_nRPCMatched_fullVeto_clusterMETCR[4];
  TH1D *h_rpcSpread_fullVeto_clusterMETCR[4];
  TH1D *h_rpcBx_fullVeto_clusterMETCR[4];
  TH1D *h_dPhiJetMET_fullVeto_clusterMETCR[4];
  TH1D *h_dtRechitClusterMaxStation_fullVeto_clusterMETCR[4];

  TH1D *h_nRPCMatched_Nminus1_clusterMETCR[4];
  TH1D *h_rpcSpread_Nminus1_clusterMETCR[4];
  TH1D *h_rpcBx_Nminus1_clusterMETCR[4];
  TH1D *h_dPhiJetMET_Nminus1_clusterMETCR[4];
  TH1D *h_dtRechitClusterMaxStation_Nminus1_clusterMETCR[4];

  TH1D *h_dPhiClusterMET_fullVeto_rpcCR[4];
  TH1D *h_dPhiJetMET_fullVeto_rpcCR[4];
  TH1D *h_dtRechitClusterMaxStation_fullVeto_rpcCR[4];

  TH1D *h_dPhiClusterMET_Nminus1_rpcCR[4];
  TH1D *h_dPhiJetMET_Nminus1_rpcCR[4];
  TH1D *h_dtRechitClusterMaxStation_Nminus1_rpcCR[4];

  TH1D *h_nStations1_50hits_clusterMETCR[4];
  TH1D *h_nStations25_50hits_clusterMETCR[4];
  TH1D *h_nStations50_50hits_clusterMETCR[4];
  TH1D *h_nStations1_100hits_clusterMETCR[4];
  TH1D *h_nStations25_100hits_clusterMETCR[4];
  TH1D *h_nStations50_100hits_clusterMETCR[4];
  TH1D *h_nStations1_150hits_clusterMETCR[4];
  TH1D *h_nStations25_150hits_clusterMETCR[4];
  TH1D *h_nStations50_150hits_clusterMETCR[4];

  TH1D *h_nWheels1_50hits_clusterMETCR[4];
  TH1D *h_nWheels25_50hits_clusterMETCR[4];
  TH1D *h_nWheels50_50hits_clusterMETCR[4];
  TH1D *h_nWheels1_100hits_clusterMETCR[4];
  TH1D *h_nWheels25_100hits_clusterMETCR[4];
  TH1D *h_nWheels50_100hits_clusterMETCR[4];
  TH1D *h_nWheels1_150hits_clusterMETCR[4];
  TH1D *h_nWheels25_150hits_clusterMETCR[4];
  TH1D *h_nWheels50_150hits_clusterMETCR[4];

  TH1D *h_nRPCStations1_50hits_clusterMETCR[4];
  TH1D *h_nRPCStations5_50hits_clusterMETCR[4];
  TH1D *h_nRPCStations10_50hits_clusterMETCR[4];
  TH1D *h_nRPCStations1_100hits_clusterMETCR[4];
  TH1D *h_nRPCStations5_100hits_clusterMETCR[4];
  TH1D *h_nRPCStations10_100hits_clusterMETCR[4];
  TH1D *h_nRPCStations1_150hits_clusterMETCR[4];
  TH1D *h_nRPCStations5_150hits_clusterMETCR[4];
  TH1D *h_nRPCStations10_150hits_clusterMETCR[4];

  TH1D *h_nRPCWheels1_50hits_clusterMETCR[4];
  TH1D *h_nRPCWheels5_50hits_clusterMETCR[4];
  TH1D *h_nRPCWheels10_50hits_clusterMETCR[4];
  TH1D *h_nRPCWheels1_100hits_clusterMETCR[4];
  TH1D *h_nRPCWheels5_100hits_clusterMETCR[4];
  TH1D *h_nRPCWheels10_100hits_clusterMETCR[4];
  TH1D *h_nRPCWheels1_150hits_clusterMETCR[4];
  TH1D *h_nRPCWheels5_150hits_clusterMETCR[4];
  TH1D *h_nRPCWheels10_150hits_clusterMETCR[4];

  Double_t dPhi_tmp = 0.0;
  Double_t dPhi_min = 0.0;
  Double_t dPhiClusterRPC = 0.0;
  Double_t dZClusterRPC = 0.0;
  Double_t dPhiClusterMET_max = 0.0;
  Double_t dPhiClusterMET = 0.0;
  vector<Int_t> rpcBx = {};
  Int_t rpcSpread = 0;
  Double_t rpcMedian = 0;

  Int_t evtNum = 0;

  Bool_t passMuon = false;
  Bool_t passMuon_alt = false;
  Bool_t passMB1 = false;
  Bool_t passJet = false;

  Bool_t passClusterCR = false;
  Bool_t passNoVeto_clusterCR = false;
  Bool_t passFullVeto_clusterCR = false;
  Bool_t passRPCMatch_clusterCR = false;
  Bool_t passRPCSpread_clusterCR = false;
  Bool_t passRPCBx_clusterCR = false;
  Bool_t passMaxStation_clusterCR = false;

  Bool_t passNoVeto = false;
  Bool_t passFullVeto_rpcCR = false;
  Bool_t passRPCCR = false;
  Bool_t passClusterMET_rpcCR = false;
  Bool_t passMaxStation_rpcCR = false;
  Bool_t passFullPlus = false;

  Int_t nPassClusterCR = 0;
  Int_t nPassNoVeto_clusterCR = 0;
  Int_t nPassFullVeto_clusterCR = 0;
  Int_t nPassRPCMatch_clusterCR = 0;
  Int_t nPassRPCSpread_clusterCR = 0;
  Int_t nPassRPCBx_clusterCR = 0;
  Int_t nPassMaxStation_clusterCR = 0;

  Int_t nPassNoVeto = 0;
  Int_t nPassFullVeto_rpcCR = 0;
  Int_t nPassRPCCR = 0;
  Int_t nPassClusterMET_rpcCR = 0;
  Int_t nPassMaxStation_rpcCR = 0;
  Int_t nPassFullPlus = 0;

  ofstream eventListRPC;
  eventListRPC.open("events/rpcCR_tailEvents.txt");
  Int_t event100_rpc = 0;
  Int_t event150_rpc = 0;
  ofstream eventListClusterMET;
  eventListClusterMET.open("events/clusterMETCR_tailEvents.txt");
  Int_t event100_clusterMET = 0;
  Int_t event150_clusterMET = 0;

  Int_t nStations1 = 0;
  Int_t nStations25 = 0;
  Int_t nStations50 = 0;
  Int_t hitStation1 = 0;
  Int_t hitStation2 = 0;
  Int_t hitStation3 = 0;
  Int_t hitStation4 = 0;

  Int_t nWheels1 = 0;
  Int_t nWheels25 = 0;
  Int_t nWheels50 = 0;
  Int_t hitWheelm1 = 0;
  Int_t hitWheelm2 = 0;
  Int_t hitWheel0 = 0;
  Int_t hitWheel1 = 0;
  Int_t hitWheel2 = 0;

  Int_t nRPCStations1 = 0;
  Int_t nRPCStations5 = 0;
  Int_t nRPCStations10 = 0;
  Int_t hitRPCStation1 = 0;
  Int_t hitRPCStation2 = 0;
  Int_t hitRPCStation3 = 0;
  Int_t hitRPCStation4 = 0;

  Int_t nRPCWheels1 = 0;
  Int_t nRPCWheels5 = 0;
  Int_t nRPCWheels10 = 0;
  Int_t hitRPCWheelm1 = 0;
  Int_t hitRPCWheelm2 = 0;
  Int_t hitRPCWheel0 = 0;
  Int_t hitRPCWheel1 = 0;
  Int_t hitRPCWheel2 = 0;

  Int_t rpcStation = 99;
  Int_t rpcWheel = 99;
  Int_t dtStation = 99;
  Int_t dtWheel = 99;
  Int_t maxClusterSize = 0;

  for(Int_t itr_year=0; itr_year<3; itr_year++){

    sprintf(name,"h_dtRechitClusterSize_dPhiJetMETLow_rpcCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiJetMETLow_rpcCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_dPhiJetMETHigh_rpcCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiJetMETHigh_rpcCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_dPhiClusterMETLow_rpcCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiClusterMETLow_rpcCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_dPhiClusterMETHigh_rpcCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiClusterMETHigh_rpcCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_dPhiClusterMETLow_rpcSpreadCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiClusterMETLow_rpcSpreadCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_dPhiClusterMETHigh_rpcSpreadCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiClusterMETHigh_rpcSpreadCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_dPhiJetMETLow_rpcCRnoLepton_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiJetMETLow_rpcCRnoLepton[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_dPhiJetMETHigh_rpcCRnoLepton_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiJetMETHigh_rpcCRnoLepton[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_dPhiClusterMETLow_rpcCRnoLepton_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiClusterMETLow_rpcCRnoLepton[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_dPhiClusterMETHigh_rpcCRnoLepton_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiClusterMETHigh_rpcCRnoLepton[itr_year] = new TH1D(name,"",50,0,500);



    sprintf(name,"h_dtRechitClusterSize_dPhiClusterMETLow_jetMETCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiClusterMETLow_jetMETCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_dPhiClusterMETHigh_jetMETCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiClusterMETHigh_jetMETCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_rpcMatch_jetMETCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_rpcMatch_jetMETCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_rpcNoMatch_jetMETCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_rpcNoMatch_jetMETCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_dPhiClusterMETLow_jetMETCRnoLepton_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiClusterMETLow_jetMETCRnoLepton[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_dPhiClusterMETHigh_jetMETCRnoLepton_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiClusterMETHigh_jetMETCRnoLepton[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_rpcMatch_jetMETCRnoLepton_%s",years[itr_year]);
    h_dtRechitClusterSize_rpcMatch_jetMETCRnoLepton[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_rpcNoMatch_jetMETCRnoLepton_%s",years[itr_year]);
    h_dtRechitClusterSize_rpcNoMatch_jetMETCRnoLepton[itr_year] = new TH1D(name,"",50,0,500);



    sprintf(name,"h_dtRechitClusterSize_dPhiJetMETLow_clusterMETCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiJetMETLow_clusterMETCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_dPhiJetMETHigh_clusterMETCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiJetMETHigh_clusterMETCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_rpcGood_clusterMETCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_rpcGood_clusterMETCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_rpcBad_clusterMETCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_rpcBad_clusterMETCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_rpcMatch_clusterMETCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_rpcMatch_clusterMETCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_rpcNoMatch_clusterMETCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_rpcNoMatch_clusterMETCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_rpcSpread_clusterMETCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_rpcSpread_clusterMETCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_rpcNoSpread_clusterMETCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_rpcNoSpread_clusterMETCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_rpcNegativeSpread_clusterMETCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_rpcNegativeSpread_clusterMETCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_rpcNegativeNoSpread_clusterMETCRmuonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_rpcNegativeNoSpread_clusterMETCRmuonVeto[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_dPhiJetMETLow_clusterMETCRnoLepton_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiJetMETLow_clusterMETCRnoLepton[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_dPhiJetMETHigh_clusterMETCRnoLepton_%s",years[itr_year]);
    h_dtRechitClusterSize_dPhiJetMETHigh_clusterMETCRnoLepton[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_rpcMatch_clusterMETCRnoLepton_%s",years[itr_year]);
    h_dtRechitClusterSize_rpcMatch_clusterMETCRnoLepton[itr_year] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_rpcNoMatch_clusterMETCRnoLepton_%s",years[itr_year]);
    h_dtRechitClusterSize_rpcNoMatch_clusterMETCRnoLepton[itr_year] = new TH1D(name,"",50,0,500);



    sprintf(name,"h_dPhiClusterRPC_fullVeto_%s",years[itr_year]);
    h_dPhiClusterRPC_fullVeto[itr_year] = new TH1D(name,"",73,-0.15,3.5);

    sprintf(name,"h_dZClusterRPC_fullVeto_%s",years[itr_year]);
    h_dZClusterRPC_fullVeto[itr_year] = new TH1D(name,"",101,-5,500);

    sprintf(name,"h_rpcSpread_invertedJetVeto_%s",years[itr_year]);
    h_rpcSpread_invertedJetVeto[itr_year] = new TH1D(name,"",10,0,10);

    sprintf(name,"h_rpcSpread_invertedJetVeto_muonVeto_%s",years[itr_year]);
    h_rpcSpread_invertedJetVeto_muonVeto[itr_year] = new TH1D(name,"",10,0,10);

    sprintf(name,"h_rpcSpread_fullVeto_%s",years[itr_year]);
    h_rpcSpread_fullVeto[itr_year] = new TH1D(name,"",10,0,10);

    sprintf(name,"h_rpcSpread_fullVeto_negBx_%s",years[itr_year]);
    h_rpcSpread_fullVeto_negBx[itr_year] = new TH1D(name,"",10,0,10);



    sprintf(name,"h_nRPCMatched_fullVeto_clusterMETCR_%s",years[itr_year]);
    h_nRPCMatched_fullVeto_clusterMETCR[itr_year] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_rpcSpread_fullVeto_clusterMETCR_%s",years[itr_year]);
    h_rpcSpread_fullVeto_clusterMETCR[itr_year] = new TH1D(name,"",10,0,10);

    sprintf(name,"h_rpcBx_fullVeto_clusterMETCR_%s",years[itr_year]);
    h_rpcBx_fullVeto_clusterMETCR[itr_year] = new TH1D(name,"",10,-4.5,5.5);

    sprintf(name,"h_dPhiJetMET_fullVeto_clusterMETCR_%s",years[itr_year]);
    h_dPhiJetMET_fullVeto_clusterMETCR[itr_year] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dtRechitClusterMaxStation_fullVeto_clusterMETCR_%s",years[itr_year]);
    h_dtRechitClusterMaxStation_fullVeto_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCMatched_Nminus1_clusterMETCR_%s",years[itr_year]);
    h_nRPCMatched_Nminus1_clusterMETCR[itr_year] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_rpcSpread_Nminus1_clusterMETCR_%s",years[itr_year]);
    h_rpcSpread_Nminus1_clusterMETCR[itr_year] = new TH1D(name,"",10,0,10);

    sprintf(name,"h_rpcBx_Nminus1_clusterMETCR_%s",years[itr_year]);
    h_rpcBx_Nminus1_clusterMETCR[itr_year] = new TH1D(name,"",10,-4.5,5.5);

    sprintf(name,"h_dPhiJetMET_Nminus1_clusterMETCR_%s",years[itr_year]);
    h_dPhiJetMET_Nminus1_clusterMETCR[itr_year] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dtRechitClusterMaxStation_Nminus1_clusterMETCR_%s",years[itr_year]);
    h_dtRechitClusterMaxStation_Nminus1_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dPhiClusterMET_fullVeto_rpcCR_%s",years[itr_year]);
    h_dPhiClusterMET_fullVeto_rpcCR[itr_year] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dPhiJetMET_fullVeto_rpcCR_%s",years[itr_year]);
    h_dPhiJetMET_fullVeto_rpcCR[itr_year] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dtRechitClusterMaxStation_fullVeto_rpcCR_%s",years[itr_year]);
    h_dtRechitClusterMaxStation_fullVeto_rpcCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dPhiClusterMET_Nminus1_rpcCR_%s",years[itr_year]);
    h_dPhiClusterMET_Nminus1_rpcCR[itr_year] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dPhiJetMET_Nminus1_rpcCR_%s",years[itr_year]);
    h_dPhiJetMET_Nminus1_rpcCR[itr_year] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dtRechitClusterMaxStation_Nminus1_rpcCR_%s",years[itr_year]);
    h_dtRechitClusterMaxStation_Nminus1_rpcCR[itr_year] = new TH1D(name,"",5,0,5);



    sprintf(name,"h_nStations1_50hits_clusterMETCR_%s",years[itr_year]);
    h_nStations1_50hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations1_100hits_clusterMETCR_%s",years[itr_year]);
    h_nStations1_100hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations1_150hits_clusterMETCR_%s",years[itr_year]);
    h_nStations1_150hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations25_50hits_clusterMETCR_%s",years[itr_year]);
    h_nStations25_50hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations25_100hits_clusterMETCR_%s",years[itr_year]);
    h_nStations25_100hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations25_150hits_clusterMETCR_%s",years[itr_year]);
    h_nStations25_150hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations50_50hits_clusterMETCR_%s",years[itr_year]);
    h_nStations50_50hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations50_100hits_clusterMETCR_%s",years[itr_year]);
    h_nStations50_100hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations50_150hits_clusterMETCR_%s",years[itr_year]);
    h_nStations50_150hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nWheels1_50hits_clusterMETCR_%s",years[itr_year]);
    h_nWheels1_50hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels1_100hits_clusterMETCR_%s",years[itr_year]);
    h_nWheels1_100hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels1_150hits_clusterMETCR_%s",years[itr_year]);
    h_nWheels1_150hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels25_50hits_clusterMETCR_%s",years[itr_year]);
    h_nWheels25_50hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels25_100hits_clusterMETCR_%s",years[itr_year]);
    h_nWheels25_100hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels25_150hits_clusterMETCR_%s",years[itr_year]);
    h_nWheels25_150hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels50_50hits_clusterMETCR_%s",years[itr_year]);
    h_nWheels50_50hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels50_100hits_clusterMETCR_%s",years[itr_year]);
    h_nWheels50_100hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels50_150hits_clusterMETCR_%s",years[itr_year]);
    h_nWheels50_150hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);


    sprintf(name,"h_nRPCStations1_50hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCStations1_50hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations1_100hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCStations1_100hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations1_150hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCStations1_150hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations5_50hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCStations5_50hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations5_100hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCStations5_100hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations5_150hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCStations5_150hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations10_50hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCStations10_50hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations10_100hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCStations10_100hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations10_150hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCStations10_150hits_clusterMETCR[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCWheels1_50hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCWheels1_50hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels1_100hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCWheels1_100hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels1_150hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCWheels1_150hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels5_50hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCWheels5_50hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels5_100hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCWheels5_100hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels5_150hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCWheels5_150hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels10_50hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCWheels10_50hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels10_100hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCWheels10_100hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels10_150hits_clusterMETCR_%s",years[itr_year]);
    h_nRPCWheels10_150hits_clusterMETCR[itr_year] = new TH1D(name,"",6,0,6);


    TFile *_file;
    if(strcmp(years[itr_year],"All")==0){
      _file = TFile::Open(dir+years[itr_year]+"/v4/v4/normalized/Run2_displacedJetMuonNtupler_V1p15_Data2016_Data2017_Data2018-HighMET_goodLumi.root");
    }
    else{
      cout << "Opening " << fsPreFix + TString(datafiles[itr_year]) << endl;
      _file = TFile::Open(fsPreFix + TString(datafiles[itr_year]));
    }

    TTreeReader treeReader("MuonSystem",_file);

    TTreeReaderValue<unsigned int> runNum(treeReader,"runNum");
    TTreeReaderValue<unsigned int> lumiSec(treeReader,"lumiSec");
    TTreeReaderValue<unsigned int> eventNum(treeReader,"evtNum");
    TTreeReaderValue<float> MET(treeReader,"met");
    TTreeReaderValue<float> METphi(treeReader,"metPhi");

    TTreeReaderValue<int> nDtRechitClusters(treeReader,"nDtRechitClusters");
    TTreeReaderArray<float> dtRechitClusterX(treeReader,"dtRechitClusterX");
    TTreeReaderArray<float> dtRechitClusterY(treeReader,"dtRechitClusterY");
    TTreeReaderArray<float> dtRechitClusterZ(treeReader,"dtRechitClusterZ");
    TTreeReaderArray<float> dtRechitClusterPhi(treeReader,"dtRechitClusterPhi");
    TTreeReaderArray<float> dtRechitClusterEta(treeReader,"dtRechitClusterEta");
    TTreeReaderArray<float> dtRechitClusterXSpread(treeReader,"dtRechitClusterXSpread");
    TTreeReaderArray<float> dtRechitClusterYSpread(treeReader,"dtRechitClusterYSpread");
    TTreeReaderArray<float> dtRechitClusterZSpread(treeReader,"dtRechitClusterZSpread");
    TTreeReaderArray<float> dtRechitClusterPhiSpread(treeReader,"dtRechitClusterPhiSpread");
    TTreeReaderArray<float> dtRechitClusterEtaSpread(treeReader,"dtRechitClusterEtaSpread");
    TTreeReaderArray<float> dtRechitClusterJetVetoPt(treeReader,"dtRechitClusterJetVetoPt");
    TTreeReaderArray<float> dtRechitClusterMuonVetoPt(treeReader,"dtRechitClusterMuonVetoPt");
    TTreeReaderArray<int> dtRechitClusterSize(treeReader,"dtRechitClusterSize");
    TTreeReaderArray<int> dtRechitClusterNSegmentStation1(treeReader,"dtRechitClusterNSegmentStation1");
    TTreeReaderArray<int> dtRechitClusterNSegmentStation2(treeReader,"dtRechitClusterNSegmentStation2");
    TTreeReaderArray<int> dtRechitClusterNSegmentStation3(treeReader,"dtRechitClusterNSegmentStation3");
    TTreeReaderArray<int> dtRechitClusterNSegmentStation4(treeReader,"dtRechitClusterNSegmentStation4");
    TTreeReaderArray<int> dtRechitClusterMaxStation(treeReader,"dtRechitClusterMaxStation");
    TTreeReaderArray<int> dtRechitClusterNStation(treeReader,"dtRechitClusterNStation");
    TTreeReaderArray<int> dtRechitClusterMaxChamber(treeReader,"dtRechitClusterMaxChamber");
    TTreeReaderArray<int> dtRechitClusterNChamber(treeReader,"dtRechitClusterNChamber");

    TTreeReaderValue<int> nDtRechits(treeReader,"nDtRechits");
    TTreeReaderArray<float> dtRechitX(treeReader,"dtRechitX");
    TTreeReaderArray<float> dtRechitY(treeReader,"dtRechitY");
    TTreeReaderArray<float> dtRechitZ(treeReader,"dtRechitZ");
    TTreeReaderArray<float> dtRechitEta(treeReader,"dtRechitEta");
    TTreeReaderArray<float> dtRechitPhi(treeReader,"dtRechitPhi");
    TTreeReaderArray<int> dtRechitStation(treeReader,"dtRechitStation");
    TTreeReaderArray<int> dtRechitWheel(treeReader,"dtRechitWheel");

    TTreeReaderValue<int> nJets(treeReader,"nJets");
    TTreeReaderArray<float> jetPt(treeReader,"jetPt");
    TTreeReaderArray<float> jetEta(treeReader,"jetEta");
    TTreeReaderArray<float> jetPhi(treeReader,"jetPhi");
    TTreeReaderArray<float> jetRechitT(treeReader,"jetRechitT");
    TTreeReaderArray<float> jetRechitT_rms(treeReader,"jetRechitT_rms");
    TTreeReaderArray<float> jetElectronEnergyFraction(treeReader,"jetElectronEnergyFraction");
    TTreeReaderArray<float> jetPhotonEnergyFraction(treeReader,"jetPhotonEnergyFraction");
    TTreeReaderArray<float> jetNeutralHadronEnergyFraction(treeReader,"jetNeutralHadronEnergyFraction");
    TTreeReaderArray<float> jetChargedHadronEnergyFraction(treeReader,"jetChargedHadronEnergyFraction");
    TTreeReaderArray<float> jetMuonEnergyFraction(treeReader,"jetMuonEnergyFraction");

    TTreeReaderValue<int> nRPCRechits(treeReader,"nRpc");
    TTreeReaderArray<float> RPCRechitX(treeReader,"rpcX");
    TTreeReaderArray<float> RPCRechitY(treeReader,"rpcY");
    TTreeReaderArray<float> RPCRechitZ(treeReader,"rpcZ");
    TTreeReaderArray<float> RPCRechitPhi(treeReader,"rpcPhi");
    TTreeReaderArray<int> RPCRechitBx(treeReader,"rpcBx");

    TTreeReaderValue<int> nLeptons(treeReader,"nLeptons");

    _ofile->cd();
    evtNum = 0;
    event100_rpc = 0;
    event150_rpc = 0;
    event100_clusterMET = 0;
    event150_clusterMET = 0;

    cout << "Data" << years[itr_year] << endl;
    while(treeReader.Next()){
      if(evtNum%100000==0){ cout << evtNum << " of " << treeReader.GetEntries(1) << endl; }
      passFullVeto_clusterCR = false;
      passRPCMatch_clusterCR = false;
      passRPCSpread_clusterCR = false;
      passRPCBx_clusterCR = false;
      passMaxStation_clusterCR = false;
      passFullVeto_rpcCR = false;
      passRPCCR = false;
      passClusterMET_rpcCR = false;
      passMaxStation_rpcCR = false;
      maxClusterSize=0;

      if(*MET > 200){
        dPhi_min = 999.;
        dPhiClusterMET = 0.0;
        dPhiClusterMET_max = 0.0;
        if(*nDtRechitClusters>0){
          nPassNoVeto+=1;
          for(Int_t itr_clust = 0; itr_clust<*nDtRechitClusters; itr_clust++){
            dPhiClusterMET = dtRechitClusterPhi[itr_clust] - *METphi;
            if(dPhiClusterMET > TMath::Pi()){ dPhiClusterMET -= 2*TMath::Pi(); }
            if(dPhiClusterMET < -1.0*TMath::Pi()){ dPhiClusterMET += 2*TMath::Pi(); }
            if(fabs(dPhiClusterMET)>dPhiClusterMET_max){ dPhiClusterMET_max=fabs(dPhiClusterMET); }
            if(dtRechitClusterSize[itr_clust]>maxClusterSize){ maxClusterSize = dtRechitClusterSize[itr_clust]; }
          }
          for(Int_t itr_jet = 0; itr_jet<*nJets; itr_jet++){
            if(fabs(jetEta[itr_jet])<3.0 && jetPt[itr_jet]>30.0){
              dPhi_tmp = jetPhi[itr_jet] - *METphi;
              if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
              if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
              if(fabs(dPhi_tmp) < dPhi_min){
                dPhi_min = fabs(dPhi_tmp);
              }
            }
          }
        }
        if(fabs(dPhiClusterMET)>1.0){ nPassClusterCR+=1; }

        for(Int_t itr_clust=0; itr_clust<*nDtRechitClusters; itr_clust++){

          if(dtRechitClusterSize[itr_clust]>50 && ((dtRechitClusterPhi[itr_clust]<0.4 || dtRechitClusterPhi[itr_clust]>0.6) || (*runNum<275.75e3 || *runNum>275.95e3))){
            passMuon=false;
            passMuon_alt=false;
            passJet=false;
            rpcBx.clear();
            rpcSpread = 99;
            rpcMedian = 99;
            dPhiClusterRPC = -0.1;
            dZClusterRPC = -1.;

            dPhiClusterMET = dtRechitClusterPhi[itr_clust] - *METphi;
            if(dPhiClusterMET > TMath::Pi()){ dPhiClusterMET -= 2*TMath::Pi(); }
            if(dPhiClusterMET < -1.0*TMath::Pi()){ dPhiClusterMET += 2*TMath::Pi(); }

            if(dtRechitClusterJetVetoPt[itr_clust]<20.){ passJet = true; }
            if(dtRechitClusterMuonVetoPt[itr_clust]<10.){ passMuon = true; }
            if(*nLeptons==0){ passMuon_alt = true; }

            passMB1 = true;
            for(Int_t itr_dt = 0; itr_dt<*nDtRechits; itr_dt++){
              if(sqrt(pow(dtRechitX[itr_dt],2)+pow(dtRechitY[itr_dt],2))>400. && sqrt(pow(dtRechitX[itr_dt],2)+pow(dtRechitY[itr_dt],2))<480.){
                dPhi_tmp = dtRechitPhi[itr_dt] - dtRechitClusterPhi[itr_clust];
                if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
                if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
                if(sqrt(pow(dPhi_tmp,2)+pow(dtRechitEta[itr_dt]-dtRechitClusterEta[itr_clust],2))<0.4){
                  passMB1 = false;
                  break;
                }
              }
            }
            if(dtRechitClusterNSegmentStation1[itr_clust]>0){ passMB1 = false; }

            //cout << "doing rpc" << endl;
            for(Int_t itr_rpc=0; itr_rpc<*nRPCRechits; itr_rpc++){
              dPhi_tmp = RPCRechitPhi[itr_rpc] - dtRechitClusterPhi[itr_clust];
              if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
              if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
              if(fabs(dPhi_tmp)<dPhiClusterRPC || dPhiClusterRPC==-0.1){ dPhiClusterRPC=fabs(dPhi_tmp); }
              if(fabs(RPCRechitZ[itr_rpc] - dtRechitClusterZ[itr_clust])<dZClusterRPC || dZClusterRPC==-1.){ dZClusterRPC=fabs(RPCRechitZ[itr_rpc]-dtRechitClusterZ[itr_rpc]); }
              if(fabs(RPCRechitZ[itr_rpc] - dtRechitClusterZ[itr_clust])<5. && fabs(dPhi_tmp)<0.4){
                rpcBx.push_back(RPCRechitBx[itr_rpc]);
              }
            }
            if(!rpcBx.empty()){
              rpcSpread = max_element(rpcBx.begin(), rpcBx.end()) - min_element(rpcBx.begin(), rpcBx.end());
              if(rpcBx.size()%2 == 0){ rpcMedian = float(rpcBx[rpcBx.size()/2 - 1] + rpcBx[rpcBx.size()/2]) / 2.0; }
              else{ rpcMedian = rpcBx[rpcBx.size()/2]; }
            }
            if(rpcBx.empty() || rpcSpread>0){ passRPCCR=true; }

            if(passMB1 && dtRechitClusterMaxStation[itr_clust]>2 && fabs(dPhi_min)<0.6){
              if(!passJet){
                h_rpcSpread_invertedJetVeto[itr_year]->Fill(rpcSpread);
                if(passMuon){
                  h_rpcSpread_invertedJetVeto_muonVeto[itr_year]->Fill(rpcSpread);
                }
              }
              else{
                if(passMuon){
                  h_rpcSpread_fullVeto[itr_year]->Fill(rpcSpread);
                  if(rpcMedian<0){
                    h_rpcSpread_fullVeto_negBx[itr_year]->Fill(rpcSpread);
                  }
                }
              }
            }

            if(passJet && passMB1){

              if(passMuon){
                h_dPhiClusterRPC_fullVeto[itr_year]->Fill(dPhiClusterRPC);
                h_dZClusterRPC_fullVeto[itr_year]->Fill(dZClusterRPC);
              }

              //cout << "doing CRs" << endl;
              if(fabs(dPhi_min)<0.6 && dtRechitClusterMaxStation[itr_clust]>2){
                if(!rpcBx.empty() && rpcSpread==0){
                  if(fabs(dPhiClusterMET)<1.0){
                    if(passMuon){
                      h_dtRechitClusterSize_dPhiClusterMETLow_jetMETCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]);
                      h_dtRechitClusterSize_rpcMatch_jetMETCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]);
                    }
                    if(passMuon_alt){
                      h_dtRechitClusterSize_dPhiClusterMETLow_jetMETCRnoLepton[itr_year]->Fill(dtRechitClusterSize[itr_clust]);
                      h_dtRechitClusterSize_rpcMatch_jetMETCRnoLepton[itr_year]->Fill(dtRechitClusterSize[itr_clust]);
                    }
                  }
                  else{
                    if(passMuon){ h_dtRechitClusterSize_dPhiClusterMETHigh_jetMETCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]); }
                    if(passMuon_alt){ h_dtRechitClusterSize_dPhiClusterMETHigh_jetMETCRnoLepton[itr_year]->Fill(dtRechitClusterSize[itr_clust]); }
                  }
                }
                else{
                  if(fabs(dPhiClusterMET)<1.0){
                    if(passMuon){ h_dtRechitClusterSize_rpcNoMatch_jetMETCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]); }
                    if(passMuon_alt){ h_dtRechitClusterSize_rpcNoMatch_jetMETCRnoLepton[itr_year]->Fill(dtRechitClusterSize[itr_clust]); }
                  }
                }
              }


              if(fabs(dPhiClusterMET)>1.0 && dtRechitClusterMaxStation[itr_clust]>2){
                if(!rpcBx.empty() && rpcSpread==0){
                  if(fabs(dPhi_min)>0.6){
                    if(passMuon){
                      h_dtRechitClusterSize_dPhiJetMETHigh_clusterMETCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]);
                      h_dtRechitClusterSize_rpcGood_clusterMETCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]);
                      if(event100_clusterMET<4 && dtRechitClusterSize[itr_clust]>100 && dtRechitClusterSize[itr_clust]<150){
                        eventListClusterMET << *runNum << ":" << *lumiSec << ":" << *eventNum << endl;
                        event100_clusterMET+=1;
                      }
                      else if(event150_clusterMET<4 && dtRechitClusterSize[itr_clust]>150){
                        eventListClusterMET << *runNum << ":" << *lumiSec << ":" << *eventNum << endl;
                        event150_clusterMET+=1;
                      }
                    }
                    if(passMuon_alt){
                      h_dtRechitClusterSize_dPhiJetMETHigh_clusterMETCRnoLepton[itr_year]->Fill(dtRechitClusterSize[itr_clust]);
                      h_dtRechitClusterSize_rpcMatch_clusterMETCRnoLepton[itr_year]->Fill(dtRechitClusterSize[itr_clust]);
                    }
                  }
                  else{
                    if(passMuon){ h_dtRechitClusterSize_dPhiJetMETLow_clusterMETCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]); }
                    if(passMuon_alt){ h_dtRechitClusterSize_dPhiJetMETLow_clusterMETCRnoLepton[itr_year]->Fill(dtRechitClusterSize[itr_clust]); }
                  }
                }
                else{
                  if(fabs(dPhi_min)>0.6){
                    if(passMuon){ h_dtRechitClusterSize_rpcBad_clusterMETCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]); }
                    if(passMuon_alt){ h_dtRechitClusterSize_rpcNoMatch_clusterMETCRnoLepton[itr_year]->Fill(dtRechitClusterSize[itr_clust]); }
                  }
                }
              }


              if(fabs(dPhiClusterMET)>1.0 && dtRechitClusterMaxStation[itr_clust]>2){
                if(fabs(dPhi_min)>0.6){
                  if(passMuon){
                    if(!rpcBx.empty()){
                      h_dtRechitClusterSize_rpcMatch_clusterMETCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]);
                      if(rpcSpread==0){
                        h_dtRechitClusterSize_rpcNoSpread_clusterMETCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]);
                        if(rpcMedian<0.0){
                          h_dtRechitClusterSize_rpcNegativeNoSpread_clusterMETCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]);
                        }
                      }
                      else{
                        h_dtRechitClusterSize_rpcSpread_clusterMETCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]);
                        if(rpcMedian<0.0){
                          h_dtRechitClusterSize_rpcNegativeSpread_clusterMETCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]);
                        }
                      }
                    }
                    else{ h_dtRechitClusterSize_rpcNoMatch_clusterMETCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]); }
                  }
                }
              }


              if(fabs(dPhiClusterMET)>1.0 && passMuon){
                passFullVeto_clusterCR=true;
                h_nRPCMatched_fullVeto_clusterMETCR[itr_year]->Fill(rpcBx.size());
                h_rpcSpread_fullVeto_clusterMETCR[itr_year]->Fill(rpcSpread);
                h_rpcBx_fullVeto_clusterMETCR[itr_year]->Fill(rpcMedian);
                h_dPhiJetMET_fullVeto_clusterMETCR[itr_year]->Fill(fabs(dPhi_min));
                h_dtRechitClusterMaxStation_fullVeto_clusterMETCR[itr_year]->Fill(dtRechitClusterMaxStation[itr_clust]);

                if(dtRechitClusterMaxStation[itr_clust]>2){
                  passMaxStation_clusterCR=true;
                  if(!rpcBx.empty()){
                    passRPCMatch_clusterCR=true;
                    if(rpcSpread==0){
                      passRPCSpread_clusterCR=true;
                      if(rpcMedian>=0.){
                        passRPCBx_clusterCR=true;
                      }
                    }
                  }
                }

                if(!rpcBx.empty() && rpcSpread==0 && rpcMedian>=0.){ h_dtRechitClusterMaxStation_Nminus1_clusterMETCR[itr_year]->Fill(dtRechitClusterMaxStation[itr_clust]); }
                if(!rpcBx.empty() && rpcSpread==0 && rpcMedian>=0.){ h_dPhiJetMET_Nminus1_clusterMETCR[itr_year]->Fill(fabs(dPhi_min)); }
                if(!rpcBx.empty() && rpcSpread==0 && dtRechitClusterMaxStation[itr_clust]>2){ h_rpcBx_Nminus1_clusterMETCR[itr_year]->Fill(rpcMedian); }
                if(!rpcBx.empty() && rpcMedian>=0. && dtRechitClusterMaxStation[itr_clust]>2){ h_rpcSpread_Nminus1_clusterMETCR[itr_year]->Fill(rpcSpread); }
                if(dtRechitClusterMaxStation[itr_clust]>2){ h_nRPCMatched_Nminus1_clusterMETCR[itr_year]->Fill(rpcBx.size()); }
              }

              //cout << "doing rpc CRs" << endl;
              if((rpcBx.empty() || rpcSpread>0) && dtRechitClusterMaxStation[itr_clust]>2){
                if(fabs(dPhi_min)>0.6){
                  if(passMuon){
                    h_dtRechitClusterSize_dPhiJetMETHigh_rpcCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]);
                    if(fabs(dPhiClusterMET<1.0)){
                      h_dtRechitClusterSize_dPhiClusterMETLow_rpcCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]);
                      if(dtRechitClusterSize[itr_clust]>100 && dtRechitClusterSize[itr_clust]<150 && event100_rpc<5){
                        eventListRPC << *runNum << ":" << *lumiSec << ":" << *eventNum << endl;
                        event100_rpc+=1;
                      }
                      else if(dtRechitClusterSize[itr_clust]>150 && event150_rpc<5){
                        eventListRPC << *runNum << ":" << *lumiSec << ":" << *eventNum << endl;
                        event150_rpc+=1;
                      }
                    }
                    else{ h_dtRechitClusterSize_dPhiClusterMETHigh_rpcCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]); }
                  }
                  if(passMuon_alt){
                    h_dtRechitClusterSize_dPhiJetMETHigh_rpcCRnoLepton[itr_year]->Fill(dtRechitClusterSize[itr_clust]);
                    if(fabs(dPhiClusterMET<1.0)){ h_dtRechitClusterSize_dPhiClusterMETLow_rpcCRnoLepton[itr_year]->Fill(dtRechitClusterSize[itr_clust]); }
                    else{ h_dtRechitClusterSize_dPhiClusterMETHigh_rpcCRnoLepton[itr_year]->Fill(dtRechitClusterSize[itr_clust]); }
                  }
                }
                else{
                  if(passMuon){ h_dtRechitClusterSize_dPhiJetMETLow_rpcCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]); }
                  if(passMuon_alt){ h_dtRechitClusterSize_dPhiJetMETLow_rpcCRnoLepton[itr_year]->Fill(dtRechitClusterSize[itr_clust]); }
                }
              }

              //cout << "rpc Spread CR" << endl;
              if(rpcSpread>0 && rpcSpread<99 && dtRechitClusterMaxStation[itr_clust]>2){
                if(fabs(dPhi_min)>0.6){
                  if(passMuon){
                    if(fabs(dPhiClusterMET<1.0)){ h_dtRechitClusterSize_dPhiClusterMETLow_rpcSpreadCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]); }
                    else{ h_dtRechitClusterSize_dPhiClusterMETHigh_rpcSpreadCRmuonVeto[itr_year]->Fill(dtRechitClusterSize[itr_clust]); }
                  }
                }
              }


              if((rpcBx.empty() || rpcSpread>0) && passMuon){
                passFullVeto_rpcCR=true;
                h_dPhiClusterMET_fullVeto_rpcCR[itr_year]->Fill(fabs(dPhiClusterMET));
                h_dPhiJetMET_fullVeto_rpcCR[itr_year]->Fill(fabs(dPhi_min));
                h_dtRechitClusterMaxStation_fullVeto_rpcCR[itr_year]->Fill(dtRechitClusterMaxStation[itr_clust]);

                if(dtRechitClusterMaxStation[itr_clust]>2){
                  passMaxStation_rpcCR=true;
                  h_dPhiClusterMET_Nminus1_rpcCR[itr_year]->Fill(fabs(dPhiClusterMET));
                  h_dPhiJetMET_Nminus1_rpcCR[itr_year]->Fill(fabs(dPhi_min));
                  if(fabs(dPhiClusterMET)<1.0){
                    passClusterMET_rpcCR=true;
                  }
                }
                if(fabs(dPhiClusterMET)<1.0){
                  h_dtRechitClusterMaxStation_Nminus1_rpcCR[itr_year]->Fill(dtRechitClusterMaxStation[itr_clust]);
                }
              }


            }
          }
        }
      }
      if(passFullVeto_clusterCR){ nPassFullVeto_clusterCR+=1; }
      if(passRPCMatch_clusterCR){ nPassRPCMatch_clusterCR+=1; }
      if(passRPCSpread_clusterCR){ nPassRPCSpread_clusterCR+=1; }
      if(passRPCBx_clusterCR){ nPassRPCBx_clusterCR+=1; }
      if(passMaxStation_clusterCR){ nPassMaxStation_clusterCR+=1; }

      if(passRPCCR){ nPassRPCCR+=1; }
      if(passFullVeto_rpcCR){ nPassFullVeto_rpcCR+=1; }
      if(passClusterMET_rpcCR){ nPassClusterMET_rpcCR+=1; }
      if(passMaxStation_rpcCR){ nPassMaxStation_rpcCR+=1; }
      evtNum+=1;
    }
  }

  /*cout << "nPassNoVeto: " << nPassNoVeto << endl;
    cout << " " << endl;
    cout << "nPassClusterCR: " << nPassClusterCR << endl;
    cout << "nPassFullVeto_clusterCR: " << nPassFullVeto_clusterCR << endl;
    cout << "nPassMaxStation_clusterCR: " << nPassMaxStation_clusterCR << endl;
    cout << "nPassRPCMatch_clusterCR: " << nPassRPCMatch_clusterCR << endl;
    cout << "nPassRPCSpread_clusterCR: " << nPassRPCSpread_clusterCR << endl;
    cout << "nPassRPCBx_clusterCR: " << nPassRPCBx_clusterCR << endl;
    cout << " " << endl;
    cout << "nPassRPCCR: " << nPassRPCCR << endl;
    cout << "nPassFullVeto_rpcCR: " << nPassFullVeto_rpcCR << endl;
    cout << "nPassMaxStation_rpcCR: " << nPassMaxStation_rpcCR << endl;
    cout << "nPassClusterMET_rpcCR: " << nPassClusterMET_rpcCR << endl;
  */
  _ofile->Write();
  _ofile->Close();
  eventListRPC.close();
  eventListClusterMET.close();

}
