R__LOAD_LIBRARY(libTreePlayer)

#include "helpers.h"
#include "signalfiles.h"
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
#include "TString.h"

void analyzeSignal_ABCD(){

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

  char name[50];
  char title[100];
  char mX[3][10] = {"15","40","55"};
  char ctau[10] = "1000";
  char years[3][20] = {"MC_Fall18","MC_Fall17","MC_Summer16"};
  TString dir(fsPreFix + "/store/group/phys_exotica/delayedjets/displacedJetMuonAnalyzer/driftTube/V1p17/");
  TFile *_ofile = TFile::Open("outSig_ABCD.root","RECREATE");

  TH1D *h_dtRechitClusterSize_signalRegion[4];
  TH1D *h_dtRechitClusterSize_fullSelection_rpcCR[4];
  TH1D *h_dtRechitClusterSize_fullSelection_clusterMETCR[4];

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
  TH1D *h_nStations1_100hits_clusterMETCR[4];
  TH1D *h_nStations1_150hits_clusterMETCR[4];
  TH1D *h_nStations25_50hits_clusterMETCR[4];
  TH1D *h_nStations25_100hits_clusterMETCR[4];
  TH1D *h_nStations25_150hits_clusterMETCR[4];
  TH1D *h_nStations50_50hits_clusterMETCR[4];
  TH1D *h_nStations50_100hits_clusterMETCR[4];
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
  Int_t totalNum = 0;

  Bool_t passMuon = false;
  Bool_t passMuon_alt = false;
  Bool_t passMB1 = false;
  Bool_t passJet = false;
  Double_t hoMatchedEnergy = 0.0;

  Bool_t passClusterCR = false;
  Bool_t passNoVeto_clusterCR = false;
  Bool_t passFullVeto_clusterCR = false;
  Bool_t passRPCMatch_clusterCR = false;
  Bool_t passRPCSpread_clusterCR = false;
  Bool_t passRPCBx_clusterCR = false;
  Bool_t passMaxStation_clusterCR = false;
  Bool_t passLepton_clusterCR = false;
  Bool_t pass50Hits_clusterCR = false;
  Bool_t pass25Hits_clusterCR = false;

  Bool_t passNoVeto = false;
  Bool_t passFullVeto_rpcCR = false;
  Bool_t passRPCCR = false;
  Bool_t passClusterMET_rpcCR = false;
  Bool_t passMaxStation_rpcCR = false;
  Bool_t passJetMET_rpcCR = false;
  Bool_t passLepton_rpcCR = false;
  Bool_t pass50Hits_rpcCR = false;
  Bool_t pass25Hits_rpcCR = false;
  Bool_t passFullPlus = false;

  Int_t nPassClusterCR = 0;
  Int_t nPassNoVeto_clusterCR = 0;
  Int_t nPassFullVeto_clusterCR = 0;
  Int_t nPassRPCMatch_clusterCR = 0;
  Int_t nPassRPCSpread_clusterCR = 0;
  Int_t nPassRPCBx_clusterCR = 0;
  Int_t nPassMaxStation_clusterCR = 0;
  Int_t nPassLepton_clusterCR = 0;
  Int_t nPass50Hits_clusterCR = 0;
  Int_t nPass25Hits_clusterCR = 0;

  Int_t nPassNoVeto = 0;
  Int_t nPassFullVeto_rpcCR = 0;
  Int_t nPassRPCCR = 0;
  Int_t nPassClusterMET_rpcCR = 0;
  Int_t nPassMaxStation_rpcCR = 0;
  Int_t nPassFullPlus = 0;
  Int_t nPassJetMET_rpcCR = 0;
  Int_t nPassLepton_rpcCR = 0;
  Int_t nPass50Hits_rpcCR = 0;
  Int_t nPass25Hits_rpcCR = 0;

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

  for(Int_t itr_mX=0; itr_mX<3; itr_mX++){

    sprintf(name,"h_dtRechitClusterSize_signalRegion_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSize_signalRegion[itr_mX] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_fullSelection_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSize_fullSelection_clusterMETCR[itr_mX] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSize_fullSelection_rpcCR_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSize_fullSelection_rpcCR[itr_mX] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_nRPCMatched_fullVeto_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatched_fullVeto_clusterMETCR[itr_mX] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_rpcSpread_fullVeto_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_rpcSpread_fullVeto_clusterMETCR[itr_mX] = new TH1D(name,"",10,0,10);

    sprintf(name,"h_rpcBx_fullVeto_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_rpcBx_fullVeto_clusterMETCR[itr_mX] = new TH1D(name,"",10,-4.5,5.5);

    sprintf(name,"h_dPhiJetMET_fullVeto_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMET_fullVeto_clusterMETCR[itr_mX] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dtRechitClusterMaxStation_fullVeto_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterMaxStation_fullVeto_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCMatched_Nminus1_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatched_Nminus1_clusterMETCR[itr_mX] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_rpcSpread_Nminus1_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_rpcSpread_Nminus1_clusterMETCR[itr_mX] = new TH1D(name,"",10,0,10);

    sprintf(name,"h_rpcBx_Nminus1_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_rpcBx_Nminus1_clusterMETCR[itr_mX] = new TH1D(name,"",10,-4.5,5.5);

    sprintf(name,"h_dPhiJetMET_Nminus1_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMET_Nminus1_clusterMETCR[itr_mX] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dtRechitClusterMaxStation_Nminus1_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterMaxStation_Nminus1_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dPhiClusterMET_fullVeto_rpcCR_%s_%s",mX[itr_mX],ctau);
    h_dPhiClusterMET_fullVeto_rpcCR[itr_mX] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dPhiJetMET_fullVeto_rpcCR_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMET_fullVeto_rpcCR[itr_mX] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dtRechitClusterMaxStation_fullVeto_rpcCR_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterMaxStation_fullVeto_rpcCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dPhiClusterMET_Nminus1_rpcCR_%s_%s",mX[itr_mX],ctau);
    h_dPhiClusterMET_Nminus1_rpcCR[itr_mX] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dPhiJetMET_Nminus1_rpcCR_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMET_Nminus1_rpcCR[itr_mX] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dtRechitClusterMaxStation_Nminus1_rpcCR_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterMaxStation_Nminus1_rpcCR[itr_mX] = new TH1D(name,"",5,0,5);



    sprintf(name,"h_nStations1_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nStations1_50hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations1_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nStations1_100hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations1_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nStations1_150hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations25_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nStations25_50hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations25_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nStations25_100hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations25_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nStations25_150hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations50_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nStations50_50hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations50_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nStations50_100hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations50_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nStations50_150hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nWheels1_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nWheels1_50hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels1_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nWheels1_100hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels1_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nWheels1_150hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels25_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nWheels25_50hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels25_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nWheels25_100hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels25_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nWheels25_150hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels50_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nWheels50_50hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels50_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nWheels50_100hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels50_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nWheels50_150hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);


    sprintf(name,"h_nRPCStations1_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCStations1_50hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations1_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCStations1_100hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations1_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCStations1_150hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations5_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCStations5_50hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations5_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCStations5_100hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations5_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCStations5_150hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations10_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCStations10_50hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations10_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCStations10_100hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations10_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCStations10_150hits_clusterMETCR[itr_mX] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCWheels1_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCWheels1_50hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels1_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCWheels1_100hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels1_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCWheels1_150hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels5_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCWheels5_50hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels5_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCWheels5_100hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels5_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCWheels5_150hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels10_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCWheels10_50hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels10_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCWheels10_100hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels10_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau);
    h_nRPCWheels10_150hits_clusterMETCR[itr_mX] = new TH1D(name,"",6,0,6);

    nPassClusterCR = 0;
    nPassNoVeto_clusterCR = 0;
    nPassFullVeto_clusterCR = 0;
    nPassRPCMatch_clusterCR = 0;
    nPassRPCSpread_clusterCR = 0;
    nPassRPCBx_clusterCR = 0;
    nPassMaxStation_clusterCR = 0;
    nPassLepton_clusterCR = 0;
    nPass50Hits_clusterCR = 0;
    nPass25Hits_clusterCR = 0;

    nPassNoVeto = 0;
    nPassFullVeto_rpcCR = 0;
    nPassRPCCR = 0;
    nPassClusterMET_rpcCR = 0;
    nPassMaxStation_rpcCR = 0;
    nPassFullPlus = 0;
    nPassJetMET_rpcCR = 0;
    nPassLepton_rpcCR = 0;
    nPass50Hits_rpcCR = 0;
    nPass25Hits_rpcCR = 0;

    evtNum = 0;
    totalNum = 0;

    cout << mX[itr_mX] << "_" << ctau << endl;
    for(Int_t itr_year = 0; itr_year<3; itr_year++){
      cout << "  " << years[itr_year] << endl;

      TFile *_file;
      if(strcmp(years[itr_year],"MC_Summer16")==0){
        _file = TFile::Open(dir+years[itr_year]+"/v1/v3/normalized/ggH_HToSSTobbbb_MH-125_MS-"+mX[itr_mX]+"_ctau-"+ctau+"_TuneCUETP8M1_13TeV-powheg-pythia8_1pb_weighted.root");
        cout << dir+years[itr_year]+"/v1/v3/normalized/ggH_HToSSTobbbb_MH-125_MS-"+mX[itr_mX]+"_ctau-"+ctau+"_TuneCUETP8M1_13TeV-powheg-pythia8\
_1pb_weighted.root" << endl;
      }
      else{
        // _file = TFile::Open(dir+years[itr_year]+"/v1/v3/normalized/ggH_HToSSTobbbb_MH-125_MS-"+mX[itr_mX]+"_ctau-"+ctau+"_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root");
        cout << dir+years[itr_year]+"/v1/v3/normalized/ggH_HToSSTobbbb_MH-125_MS-"+mX[itr_mX]+"_ctau-"+ctau+"_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root" << endl;
        //        cout << "Opening " << TString(skimsignalfiles[itr_year]) << endl;
        //        _file = TFile::Open(TString(skimsignalfiles[itr_year]));
      }
      continue;

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
      //TTreeReaderArray<float> jetRechitT(treeReader,"jetRechitT");
      //TTreeReaderArray<float> jetRechitT_rms(treeReader,"jetRechitT_rms");
      //TTreeReaderArray<float> jetElectronEnergyFraction(treeReader,"jetElectronEnergyFraction");
      //TTreeReaderArray<float> jetPhotonEnergyFraction(treeReader,"jetPhotonEnergyFraction");
      //TTreeReaderArray<float> jetNeutralHadronEnergyFraction(treeReader,"jetNeutralHadronEnergyFraction");
      //TTreeReaderArray<float> jetChargedHadronEnergyFraction(treeReader,"jetChargedHadronEnergyFraction");
      //TTreeReaderArray<float> jetMuonEnergyFraction(treeReader,"jetMuonEnergyFraction");

      TTreeReaderValue<int> nRPCRechits(treeReader,"nRpc");
      TTreeReaderArray<float> RPCRechitX(treeReader,"rpcX");
      TTreeReaderArray<float> RPCRechitY(treeReader,"rpcY");
      TTreeReaderArray<float> RPCRechitZ(treeReader,"rpcZ");
      TTreeReaderArray<float> RPCRechitPhi(treeReader,"rpcPhi");
      TTreeReaderArray<int> RPCRechitBx(treeReader,"rpcBx");

      /*TTreeReaderValue<int> nHORechits(treeReader,"nHORechits");
        TTreeReaderArray<float> hoRechitX(treeReader,"hoRechit_X");
        TTreeReaderArray<float> hoRechitY(treeReader,"hoRechit_Y");
        TTreeReaderArray<float> hoRechitZ(treeReader,"hoRechit_Z");
        TTreeReaderArray<float> hoRechitEta(treeReader,"hoRechit_Eta");
        TTreeReaderArray<float> hoRechitPhi(treeReader,"hoRechit_Phi");
        TTreeReaderArray<float> hoRechitE(treeReader,"hoRechit_E");
        TTreeReaderArray<float> hoRechitT(treeReader,"hoRechit_T");
      */
      TTreeReaderValue<int> nLeptons(treeReader,"nLeptons");
      //TTreeReaderValue<int> nMuons(treeReader,"nMuons");

      _ofile->cd();
      totalNum += treeReader.GetEntries(1);
      cout << "Processing " <<  totalNum << " entries" << endl;
      while(treeReader.Next()){
        if(evtNum%100000==0){ cout << evtNum << " of " << totalNum << endl; }
        passFullVeto_clusterCR = false;
        passRPCMatch_clusterCR = false;
        passRPCSpread_clusterCR = false;
        passRPCBx_clusterCR = false;
        passMaxStation_clusterCR = false;
        passLepton_clusterCR = false;
        pass50Hits_clusterCR = false;
        pass25Hits_clusterCR = false;
        passFullVeto_rpcCR = false;
        passRPCCR = false;
        passClusterMET_rpcCR = false;
        passMaxStation_rpcCR = false;
        passJetMET_rpcCR = false;
        passLepton_rpcCR = false;
        pass50Hits_rpcCR = false;
        pass25Hits_rpcCR = false;
        nWheels1=0;
        nWheels25=0;
        nWheels50=0;
        nStations1=0;
        nStations25=0;
        nStations50=0;
        hitStation1=0;
        hitStation2=0;
        hitStation3=0;
        hitStation4=0;
        hitWheelm2=0;
        hitWheelm1=0;
        hitWheel0=0;
        hitWheel1=0;
        hitWheel2=0;

        nRPCWheels1=0;
        nRPCWheels5=0;
        nRPCWheels10=0;
        nRPCStations1=0;
        nRPCStations5=0;
        nRPCStations10=0;
        hitRPCStation1=0;
        hitRPCStation2=0;
        hitRPCStation3=0;
        hitRPCStation4=0;
        hitRPCWheelm2=0;
        hitRPCWheelm1=0;
        hitRPCWheel0=0;
        hitRPCWheel1=0;
        hitRPCWheel2=0;

        maxClusterSize=0;

        if(*MET > 200) {
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
          if(fabs(dPhiClusterMET)<1.0){ nPassClusterCR+=1; }

          for(Int_t itr_clust=0; itr_clust<*nDtRechitClusters; itr_clust++){
            if(dtRechitClusterSize[itr_clust]>50){
              passMuon=false;
              passMuon_alt=false;
              passJet=false;
              rpcBx.clear();
              rpcSpread = 99;
              rpcMedian = 99;
              dPhiClusterRPC = -0.1;
              dZClusterRPC = -1.;
              nStations25 = 0;
              nStations50 = 0;
              hoMatchedEnergy = 0.;

              dPhiClusterMET = dtRechitClusterPhi[itr_clust] - *METphi;
              if(dPhiClusterMET > TMath::Pi()){ dPhiClusterMET -= 2*TMath::Pi(); }
              if(dPhiClusterMET < -1.0*TMath::Pi()){ dPhiClusterMET += 2*TMath::Pi(); }

              if(dtRechitClusterJetVetoPt[itr_clust]<20.){ passJet = true; }
              if(dtRechitClusterMuonVetoPt[itr_clust]<10.){ passMuon = true; }
              if(*nLeptons==0){ passMuon_alt = true; }

              /*passMB1 = false;
                for(Int_t itr_ho = 0; itr_ho<*nHORechits; itr_ho++){
                dPhi_tmp = hoRechitPhi[itr_ho] - dtRechitClusterPhi[itr_clust];
                if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
                if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
                if(sqrt(pow(dPhi_tmp,2)+pow(hoRechitEta[itr_ho]-dtRechitClusterEta[itr_clust],2))<0.5){
                hoMatchedEnergy+=hoRechitE[itr_ho];
                }
                }
                if(hoMatchedEnergy>40.0){ passMB1 = true; }
              */
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
                /*if(itr_clust==0 && *nDtRechits<750){
                  dtStation=getStation(dtRechitX[itr_dt],dtRechitY[itr_dt]);
                  dtWheel=getWheel(dtRechitZ[itr_dt]);
                  if(dtStation==1){ hitStation1+=1; }
                  else if(dtStation==2){ hitStation2+=1; }
                  else if(dtStation==3){ hitStation3+=1; }
                  else if(dtStation==4){ hitStation4+=1; }
                  if(dtWheel==-2){ hitWheelm2+=1; }
                  else if(dtWheel==-1){ hitWheelm1+=1; }
                  else if(dtWheel==0){ hitWheel0+=1; }
                  else if(dtWheel==1){ hitWheel1+=1; }
                  else if(dtWheel==2){ hitWheel2+=1; }
                  }*/
              }
              if(itr_clust==0){
                if(hitStation1>0){
                  nStations1+=1;
                  if(hitStation1>25){
                    nStations25+=1;
                    if(hitStation1>50){
                      nStations50+=1;
                    }
                  }
                }
                if(hitStation2>0){
                  nStations1+=1;
                  if(hitStation2>25){
                    nStations25+=1;
                    if(hitStation2>50){
                      nStations50+=1;
                    }
                  }
                }
                if(hitStation3>0){
                  nStations1+=1;
                  if(hitStation3>25){
                    nStations25+=1;
                    if(hitStation3>50){
                      nStations50+=1;
                    }
                  }
                }
                if(hitStation4>0){
                  nStations1+=1;
                  if(hitStation4>25){
                    nStations25+=1;
                    if(hitStation4>50){
                      nStations50+=1;
                    }
                  }
                }
                if(hitWheel1>0){
                  nWheels1+=1;
                  if(hitWheel1>25){
                    nWheels25+=1;
                    if(hitWheel1>50){
                      nWheels50+=1;
                    }
                  }
                }
                if(hitWheel2>0){
                  nWheels1+=1;
                  if(hitWheel2>25){
                    nWheels25+=1;
                    if(hitWheel2>50){
                      nWheels50+=1;
                    }
                  }
                }
                if(hitWheel0>0){
                  nWheels1+=1;
                  if(hitWheel0>25){
                    nWheels25+=1;
                    if(hitWheel0>50){
                      nWheels50+=1;
                    }
                  }
                }
                if(hitWheelm1>0){
                  nWheels1+=1;
                  if(hitWheelm1>25){
                    nWheels25+=1;
                    if(hitWheelm1>50){
                      nWheels50+=1;
                    }
                  }
                }
                if(hitWheelm2>0){
                  nWheels1+=1;
                  if(hitWheelm2>25){
                    nWheels25+=1;
                    if(hitWheelm2>50){
                      nWheels50+=1;
                    }
                  }
                }
              }
              /*if(*nDtRechits>=750){
                nStations1=4;
                nStations25=4;
                nStations50=4;
                nWheels1=5;
                nWheels25=5;
                nWheels50=5;
                }*/
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
                /*if(itr_clust==0 && *nRPCRechits<500){
                  rpcStation=getRPCLayer(RPCRechitX[itr_rpc],RPCRechitY[itr_rpc]);
                  rpcWheel=getWheel(RPCRechitZ[itr_rpc]);
                  if(abs(rpcWheel)<=2){
                  if(rpcStation==1 || rpcStation==2){ hitRPCStation1+=1; }
                  else if(rpcStation==3 || rpcStation==4){ hitRPCStation2+=1; }
                  else if(rpcStation==5){ hitRPCStation3+=1; }
                  else if(rpcStation==6){ hitRPCStation4+=1; }
                  if(rpcWheel==-2){ hitRPCWheelm2+=1; }
                  else if(rpcWheel==-1){ hitRPCWheelm1+=1; }
                  else if(rpcWheel==0){ hitRPCWheel0+=1; }
                  else if(rpcWheel==1){ hitRPCWheel1+=1; }
                  else if(rpcWheel==2){ hitRPCWheel2+=1; }
                  }
                  }*/
              }
              if(!rpcBx.empty()){
                rpcSpread = max_element(rpcBx.begin(), rpcBx.end()) - min_element(rpcBx.begin(), rpcBx.end());
                if(rpcBx.size()%2 == 0){ rpcMedian = float(rpcBx[rpcBx.size()/2 - 1] + rpcBx[rpcBx.size()/2]) / 2.0; }
                else{ rpcMedian = rpcBx[rpcBx.size()/2]; }
              }
              if(!rpcBx.empty() && rpcSpread>0){ passRPCCR=true; }
              if(itr_clust==0){
                if(hitRPCStation1>0){
                  nRPCStations1+=1;
                  if(hitRPCStation1>5){
                    nRPCStations5+=1;
                    if(hitRPCStation1>10){
                      nRPCStations10+=1;
                    }
                  }
                }
                if(hitRPCStation2>0){
                  nRPCStations1+=1;
                  if(hitRPCStation2>5){
                    nRPCStations5+=1;
                    if(hitRPCStation2>10){
                      nRPCStations10+=1;
                    }
                  }
                }
                if(hitRPCStation3>0){
                  nRPCStations1+=1;
                  if(hitRPCStation3>5){
                    nRPCStations5+=1;
                    if(hitRPCStation3>10){
                      nRPCStations10+=1;
                    }
                  }
                }
                if(hitRPCStation4>0){
                  nRPCStations1+=1;
                  if(hitRPCStation4>5){
                    nRPCStations5+=1;
                    if(hitRPCStation4>10){
                      nRPCStations10+=1;
                    }
                  }
                }
                if(hitRPCWheel1>0){
                  nRPCWheels1+=1;
                  if(hitRPCWheel1>5){
                    nRPCWheels5+=1;
                    if(hitRPCWheel1>10){
                      nRPCWheels10+=1;
                    }
                  }
                }
                if(hitRPCWheel2>0){
                  nRPCWheels1+=1;
                  if(hitRPCWheel2>5){
                    nRPCWheels5+=1;
                    if(hitRPCWheel2>10){
                      nRPCWheels10+=1;
                    }
                  }
                }
                if(hitRPCWheel0>0){
                  nRPCWheels1+=1;
                  if(hitRPCWheel0>5){
                    nRPCWheels5+=1;
                    if(hitRPCWheel0>10){
                      nRPCWheels10+=1;
                    }
                  }
                }
                if(hitRPCWheelm1>0){
                  nRPCWheels1+=1;
                  if(hitRPCWheelm1>5){
                    nRPCWheels5+=1;
                    if(hitRPCWheelm1>10){
                      nRPCWheels10+=1;
                    }
                  }
                }
                if(hitRPCWheelm2>0){
                  nRPCWheels1+=1;
                  if(hitRPCWheelm2>5){
                    nRPCWheels5+=1;
                    if(hitRPCWheelm2>10){
                      nRPCWheels10+=1;
                    }
                  }
                }
              }
              /*if(*nRPCRechits>750){
                nRPCStations1=4;
                nRPCStations5=4;
                nRPCStations10=4;
                nRPCWheels1=5;
                nRPCWheels5=5;
                nRPCWheels10=5;
                }*/

              if(passJet && passMB1){

                if(fabs(dPhiClusterMET)<1.0 && passMuon){
                  passFullVeto_clusterCR=true;
                  h_nRPCMatched_fullVeto_clusterMETCR[itr_mX]->Fill(rpcBx.size());
                  h_rpcSpread_fullVeto_clusterMETCR[itr_mX]->Fill(rpcSpread);
                  h_rpcBx_fullVeto_clusterMETCR[itr_mX]->Fill(rpcMedian);
                  h_dPhiJetMET_fullVeto_clusterMETCR[itr_mX]->Fill(fabs(dPhi_min));
                  h_dtRechitClusterMaxStation_fullVeto_clusterMETCR[itr_mX]->Fill(dtRechitClusterMaxStation[itr_clust]);

                  if(dtRechitClusterMaxStation[itr_clust]>2){
                    passMaxStation_clusterCR=true;
                    if(!rpcBx.empty()){
                      passRPCMatch_clusterCR=true;
                      if(rpcSpread==0){
                        passRPCSpread_clusterCR=true;
                        if(rpcMedian>=0.){
                          passRPCBx_clusterCR=true;
                          if(*nLeptons==0){
                            passLepton_clusterCR=true;
                            if(nStations50<3 && nWheels50<3){
                              pass50Hits_clusterCR=true;
                              if(nStations25<3 && nWheels25<3){
                                pass25Hits_clusterCR=true;
                              }
                            }
                          }
                        }
                      }
                    }
                  }

                  if(!rpcBx.empty() && rpcSpread==0 && rpcMedian>=0.){ h_dtRechitClusterMaxStation_Nminus1_clusterMETCR[itr_mX]->Fill(dtRechitClusterMaxStation[itr_clust]); }
                  if(!rpcBx.empty() && rpcSpread==0 && rpcMedian>=0.){ h_dPhiJetMET_Nminus1_clusterMETCR[itr_mX]->Fill(fabs(dPhi_min)); }
                  if(!rpcBx.empty() && rpcSpread==0 && dtRechitClusterMaxStation[itr_clust]>2){ h_rpcBx_Nminus1_clusterMETCR[itr_mX]->Fill(rpcMedian); }
                  if(!rpcBx.empty() && rpcMedian>=0. && dtRechitClusterMaxStation[itr_clust]>2){ h_rpcSpread_Nminus1_clusterMETCR[itr_mX]->Fill(rpcSpread); }
                  if(dtRechitClusterMaxStation[itr_clust]>2){ h_nRPCMatched_Nminus1_clusterMETCR[itr_mX]->Fill(rpcBx.size()); }
                }

                if(!rpcBx.empty() && rpcSpread==0 && passMuon){
                  passFullVeto_rpcCR=true;
                  h_dPhiClusterMET_fullVeto_rpcCR[itr_mX]->Fill(fabs(dPhiClusterMET));
                  h_dPhiJetMET_fullVeto_rpcCR[itr_mX]->Fill(fabs(dPhi_min));
                  h_dtRechitClusterMaxStation_fullVeto_rpcCR[itr_mX]->Fill(dtRechitClusterMaxStation[itr_clust]);

                  if(dtRechitClusterMaxStation[itr_clust]>2){
                    passMaxStation_rpcCR=true;
                    h_dPhiClusterMET_Nminus1_rpcCR[itr_mX]->Fill(fabs(dPhiClusterMET));
                    h_dPhiJetMET_Nminus1_rpcCR[itr_mX]->Fill(fabs(dPhi_min));
                    if(fabs(dPhiClusterMET)<1.0){
                      passClusterMET_rpcCR=true;
                      if(fabs(dPhi_min)>0.6){
                        passJetMET_rpcCR=true;
                        if(*nLeptons==0){
                          passLepton_rpcCR=true;
                          if(nStations50<3 && nWheels50<3){
                            pass50Hits_rpcCR=true;
                            if(nStations25<4 && nWheels25<3){
                              pass25Hits_rpcCR=true;
                            }
                          }
                        }
                      }
                    }
                  }
                  if(fabs(dPhiClusterMET)<1.0){
                    h_dtRechitClusterMaxStation_Nminus1_rpcCR[itr_mX]->Fill(dtRechitClusterMaxStation[itr_clust]);
                  }
                }

                if(passMuon){
                  if(!rpcBx.empty() && rpcSpread==0){
                    if(rpcMedian>=0.){
                      if(dtRechitClusterMaxStation[itr_clust]>2){
                        if(fabs(dPhi_min)>0.6){
                          if(fabs(dPhiClusterMET)<1.0){
                            if(*nLeptons==0){
                              if(nStations50<3 && nWheels50<3){
                                if(nStations25<4 && nWheels25<3){
                                  h_dtRechitClusterSize_signalRegion[itr_mX]->Fill(dtRechitClusterSize[itr_clust]);
                                  h_dtRechitClusterSize_fullSelection_rpcCR[itr_mX]->Fill(dtRechitClusterSize[itr_clust]);
                                  h_dtRechitClusterSize_fullSelection_clusterMETCR[itr_mX]->Fill(dtRechitClusterSize[itr_clust]);
                                }
                              }
                            }
                          }
                        }
                      }
                    }
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
        if(passMaxStation_clusterCR){
          nPassMaxStation_clusterCR+=1;
          if(maxClusterSize>150){
            h_nStations1_150hits_clusterMETCR[itr_mX]->Fill(nStations1);
            h_nStations25_150hits_clusterMETCR[itr_mX]->Fill(nStations25);
            h_nStations50_150hits_clusterMETCR[itr_mX]->Fill(nStations50);
            h_nWheels1_150hits_clusterMETCR[itr_mX]->Fill(nWheels1);
            h_nWheels25_150hits_clusterMETCR[itr_mX]->Fill(nWheels25);
            h_nWheels50_150hits_clusterMETCR[itr_mX]->Fill(nWheels50);

            h_nRPCStations1_150hits_clusterMETCR[itr_mX]->Fill(nRPCStations1);
            h_nRPCStations5_150hits_clusterMETCR[itr_mX]->Fill(nRPCStations5);
            h_nRPCStations10_150hits_clusterMETCR[itr_mX]->Fill(nRPCStations10);
            h_nRPCWheels1_150hits_clusterMETCR[itr_mX]->Fill(nRPCWheels1);
            h_nRPCWheels5_150hits_clusterMETCR[itr_mX]->Fill(nRPCWheels5);
            h_nRPCWheels10_150hits_clusterMETCR[itr_mX]->Fill(nRPCWheels10);
          }
          else if(maxClusterSize>100){
            h_nStations1_100hits_clusterMETCR[itr_mX]->Fill(nStations1);
            h_nStations25_100hits_clusterMETCR[itr_mX]->Fill(nStations25);
            h_nStations50_100hits_clusterMETCR[itr_mX]->Fill(nStations50);
            h_nWheels1_100hits_clusterMETCR[itr_mX]->Fill(nWheels1);
            h_nWheels25_100hits_clusterMETCR[itr_mX]->Fill(nWheels25);
            h_nWheels50_100hits_clusterMETCR[itr_mX]->Fill(nWheels50);

            h_nRPCStations1_100hits_clusterMETCR[itr_mX]->Fill(nRPCStations1);
            h_nRPCStations5_100hits_clusterMETCR[itr_mX]->Fill(nRPCStations5);
            h_nRPCStations10_100hits_clusterMETCR[itr_mX]->Fill(nRPCStations10);
            h_nRPCWheels1_100hits_clusterMETCR[itr_mX]->Fill(nRPCWheels1);
            h_nRPCWheels5_100hits_clusterMETCR[itr_mX]->Fill(nRPCWheels5);
            h_nRPCWheels10_100hits_clusterMETCR[itr_mX]->Fill(nRPCWheels10);
          }
          else{
            h_nStations1_50hits_clusterMETCR[itr_mX]->Fill(nStations1);
            h_nStations25_50hits_clusterMETCR[itr_mX]->Fill(nStations25);
            h_nStations50_50hits_clusterMETCR[itr_mX]->Fill(nStations50);
            h_nWheels1_50hits_clusterMETCR[itr_mX]->Fill(nWheels1);
            h_nWheels25_50hits_clusterMETCR[itr_mX]->Fill(nWheels25);
            h_nWheels50_50hits_clusterMETCR[itr_mX]->Fill(nWheels50);

            h_nRPCStations1_50hits_clusterMETCR[itr_mX]->Fill(nRPCStations1);
            h_nRPCStations5_50hits_clusterMETCR[itr_mX]->Fill(nRPCStations5);
            h_nRPCStations10_50hits_clusterMETCR[itr_mX]->Fill(nRPCStations10);
            h_nRPCWheels1_50hits_clusterMETCR[itr_mX]->Fill(nRPCWheels1);
            h_nRPCWheels5_50hits_clusterMETCR[itr_mX]->Fill(nRPCWheels5);
            h_nRPCWheels10_50hits_clusterMETCR[itr_mX]->Fill(nRPCWheels10);
          }
        }
        if(passLepton_clusterCR){ nPassLepton_clusterCR+=1; }
        if(pass50Hits_clusterCR){ nPass50Hits_clusterCR+=1; }
        if(pass25Hits_clusterCR){ nPass25Hits_clusterCR+=1; }

        if(passRPCCR){ nPassRPCCR+=1; }
        if(passFullVeto_rpcCR){ nPassFullVeto_rpcCR+=1; }
        if(passClusterMET_rpcCR){ nPassClusterMET_rpcCR+=1; }
        if(passMaxStation_rpcCR){ nPassMaxStation_rpcCR+=1; }
        if(passJetMET_rpcCR){ nPassJetMET_rpcCR+=1; }
        if(passLepton_rpcCR){ nPassLepton_rpcCR+=1; }
        if(pass50Hits_rpcCR){ nPass50Hits_rpcCR+=1; }
        if(pass25Hits_rpcCR){ nPass25Hits_rpcCR+=1; }
        evtNum+=1;
      }
    }

    cout << "nPassNoVeto: " << nPassNoVeto << endl;
    cout << " " << endl;
    cout << "nPassClusterCR: " << nPassClusterCR << endl;
    cout << "nPassFullVeto_clusterCR: " << nPassFullVeto_clusterCR << endl;
    cout << "nPassMaxStation_clusterCR: " << nPassMaxStation_clusterCR << endl;
    cout << "nPassRPCMatch_clusterCR: " << nPassRPCMatch_clusterCR << endl;
    cout << "nPassRPCSpread_clusterCR: " << nPassRPCSpread_clusterCR << endl;
    cout << "nPassRPCBx_clusterCR: " << nPassRPCBx_clusterCR << endl;
    cout << "nPassLepton_clusterCR: " << nPassLepton_clusterCR << endl;
    cout << "nPass50Hits_clusterCR: " << nPass50Hits_clusterCR << endl;
    cout << "nPass25Hits_clusterCR: " << nPass25Hits_clusterCR << endl;
    cout << " " << endl;
    cout << "nPassRPCCR: " << nPassRPCCR << endl;
    cout << "nPassFullVeto_rpcCR: " << nPassFullVeto_rpcCR << endl;
    cout << "nPassMaxStation_rpcCR: " << nPassMaxStation_rpcCR << endl;
    cout << "nPassClusterMET_rpcCR: " << nPassClusterMET_rpcCR << endl;
    cout << "nPassJetMET_rpcCR: " << nPassJetMET_rpcCR << endl;
    cout << "nPassLepton_rpcCR: " << nPassLepton_rpcCR << endl;
    cout << "nPass50Hits_rpcCR: " << nPass50Hits_rpcCR << endl;
    cout << "nPass25Hits_rpcCR: " << nPass25Hits_rpcCR << endl;

  }

  _ofile->Write();
  _ofile->Close();

}
