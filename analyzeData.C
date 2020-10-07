R__LOAD_LIBRARY(libTreePlayer)

#include "helpers.h"

void analyzeData(){

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
  char years[4][10] = {"2018","2017","2016"};
  char runNames[3][20] = {"17Sept2018_Run2018","Run2017","Run2016"};
  char dates[3][20] = {"17Sep2018","17Nov2017_v2","07Aug17"};
  TString dir(fsPreFix + "/store/group/phys_exotica/delayedjets/displacedJetMuonAnalyzer/driftTube/V1p15/Data");
  TFile *_ofile = TFile::Open("outData_altTest4.root","RECREATE");

  TH1D *h_dPhiJetMET[4];
  TH1D *h_dPhiJetMET_noVeto[4];
  TH1D *h_dPhiJetMET_jetVeto[4];
  TH1D *h_dPhiJetMET_muonVeto[4];
  TH1D *h_dPhiJetMET_MB1Veto[4];
  TH1D *h_dPhiJetMET_noMB1Veto[4];
  TH1D *h_dPhiJetMET_fullVeto[4];
  TH1D *h_dPhiJetMET_fullHOVeto[4];
  TH1D *h_jetMet_dPhiMin4[4];
  TH1D *h_MET[4];
  TH1D *h_jetPt[4];

  TH1D *h_nDtRechitClusters_noVeto[4];
  TH1D *h_dtRechitClusterSize_noVeto[4];
  TH1D *h_nTotalClusteredRechits_noVeto[4];
  TH1D *h_dtRechitClusterMaxStation_noVeto[4];
  TH1D *h_dtRechitClusterNStation_noVeto[4];
  TH1D *h_dPhiClusterMET_noVeto[4];
  TH1D *h_dtRechitClusterXSpread_noVeto[4];
  TH1D *h_dtRechitClusterYSpread_noVeto[4];
  TH1D *h_dtRechitClusterZSpread_noVeto[4];
  TH1D *h_dtRechitClusterEtaSpread_noVeto[4];
  TH1D *h_dtRechitClusterPhiSpread_noVeto[4];
  TH1D *h_nRPCMatched_noVeto[4];
  TH1D *h_RPCMatchedBx_noVeto[4];
  TH1D *h_RPCMatchedBxSpread_noVeto[4];
  TH1D *h_RPCMatchedBx_Spread0_noVeto[4];
  TH1D *h_nRPCMatched_Spread0_noVeto[4];

  TH1D *h_nDtRechitClusters_muonVeto[4];
  TH1D *h_dtRechitClusterSize_muonVeto[4];
  TH1D *h_nTotalClusteredRechits_muonVeto[4];
  TH1D *h_dtRechitClusterMaxStation_muonVeto[4];
  TH1D *h_dtRechitClusterNStation_muonVeto[4];
  TH1D *h_dPhiClusterMET_muonVeto[4];
  TH1D *h_dtRechitClusterXSpread_muonVeto[4];
  TH1D *h_dtRechitClusterYSpread_muonVeto[4];
  TH1D *h_dtRechitClusterZSpread_muonVeto[4];
  TH1D *h_dtRechitClusterEtaSpread_muonVeto[4];
  TH1D *h_dtRechitClusterPhiSpread_muonVeto[4];
  TH1D *h_nRPCMatched_muonVeto[4];
  TH1D *h_RPCMatchedBx_muonVeto[4];
  TH1D *h_RPCMatchedBxSpread_muonVeto[4];
  TH1D *h_RPCMatchedBx_Spread0_muonVeto[4];
  TH1D *h_nRPCMatched_Spread0_muonVeto[4];

  TH1D *h_nDtRechitClusters_jetVeto[4];
  TH1D *h_dtRechitClusterSizeBarrel_jetVeto[4];
  TH1D *h_dtRechitClusterSizeMagnet_jetVeto[4];
  TH1D *h_dtRechitClusterSizeAll_jetVeto[4];
  TH1D *h_dtRechitClusterSize_jetVeto[4];
  TH1D *h_nTotalClusteredRechits_jetVeto[4];
  TH1D *h_dtRechitClusterMaxStation_jetVeto[4];
  TH1D *h_dtRechitClusterNStation_jetVeto[4];
  TH1D *h_dPhiClusterMET_jetVeto[4];
  TH1D *h_dtRechitClusterXSpread_jetVeto[4];
  TH1D *h_dtRechitClusterYSpread_jetVeto[4];
  TH1D *h_dtRechitClusterZSpread_jetVeto[4];
  TH1D *h_dtRechitClusterEtaSpread_jetVeto[4];
  TH1D *h_dtRechitClusterPhiSpread_jetVeto[4];
  TH1D *h_nRPCMatched_jetVeto[4];
  TH1D *h_nRPCMatchedLayer1_jetVeto[4];
  TH1D *h_nRPCMatchedLayer2_jetVeto[4];
  TH1D *h_nRPCMatchedLayer3_jetVeto[4];
  TH1D *h_nRPCMatchedLayer4_jetVeto[4];
  TH1D *h_nRPCMatchedLayer1_fullHOVeto[4];
  TH1D *h_nRPCMatchedLayer2_fullHOVeto[4];
  TH1D *h_nRPCMatchedLayer3_fullHOVeto[4];
  TH1D *h_nRPCMatchedLayer4_fullHOVeto[4];
  TH1D *h_RPCMatchedBx_jetVeto[4];
  TH1D *h_RPCMatchedBxSpread_jetVeto[4];
  TH1D *h_RPCMatchedBx_Spread0_jetVeto[4];
  TH1D *h_nRPCMatched_Spread0_jetVeto[4];

  TH1D *h_nDtRechitClusters_MB1Veto[4];
  TH1D *h_dtRechitClusterSizeBarrel_MB1Veto[4];
  TH1D *h_dtRechitClusterSizeMagnet_MB1Veto[4];
  TH1D *h_dtRechitClusterSizeAll_MB1Veto[4];
  TH1D *h_dtRechitClusterSize_MB1Veto[4];
  TH1D *h_nTotalClusteredRechits_MB1Veto[4];
  TH1D *h_nTotalClusteredRechits_noMB1Veto[4];
  TH1D *h_dtRechitClusterMaxStation_MB1Veto[4];
  TH1D *h_dtRechitClusterNStation_MB1Veto[4];
  TH1D *h_dPhiClusterMET_MB1Veto[4];
  TH1D *h_dtRechitClusterXSpread_MB1Veto[4];
  TH1D *h_dtRechitClusterYSpread_MB1Veto[4];
  TH1D *h_dtRechitClusterZSpread_MB1Veto[4];
  TH1D *h_dtRechitClusterEtaSpread_MB1Veto[4];
  TH1D *h_dtRechitClusterPhiSpread_MB1Veto[4];
  TH1D *h_nRPCMatched_MB1Veto[4];
  TH1D *h_RPCMatchedBx_MB1Veto[4];
  TH1D *h_RPCMatchedBxSpread_MB1Veto[4];
  TH1D *h_nRPCMatched_Spread0_MB1Veto[4];
  TH1D *h_RPCMatchedBx_Spread0_MB1Veto[4];

  TH1D *h_nDtRechitClusters_fullVeto[4];
  TH1D *h_dtRechitClusterSizeBarrel_fullVeto[4];
  TH1D *h_dtRechitClusterSizeMagnet_fullVeto[4];
  TH1D *h_dtRechitClusterSizeAll_fullVeto[4];
  TH1D *h_dtRechitClusterSize_fullVeto[4];
  TH1D *h_nTotalClusteredRechits_fullVeto[4];
  TH1D *h_dtRechitClusterMaxStation_fullVeto[4];
  TH1D *h_dtRechitClusterMaxStation_fullHOVeto[4];
  TH1D *h_dtRechitClusterNStation_fullVeto[4];
  TH1D *h_dtRechitClusterNStationUnclustered_fullVeto[4];
  TH1D *h_dtRechitClusterNThreshStation_fullVeto[4];
  TH1D *h_dtRechitClusterNThreshStationUnclustered_fullVeto[4];
  TH1D *h_dtRechitClusterNThreshLowStation_fullVeto[4];
  TH1D *h_dtRechitClusterNThreshLowStationUnclustered_fullVeto[4];
  TH1D *h_dPhiClusterMET_fullVeto[4];
  TH1D *h_dPhiClusterMET_fullHOVeto[4];
  TH1D *h_dtRechitClusterXSpread_fullVeto[4];
  TH1D *h_dtRechitClusterYSpread_fullVeto[4];
  TH1D *h_dtRechitClusterZSpread_fullVeto[4];
  TH1D *h_dtRechitClusterEtaSpread_fullVeto[4];
  TH1D *h_dtRechitClusterPhiSpread_fullVeto[4];
  TH1D *h_nRPCMatched_fullVeto[4];
  TH1D *h_nRPCMatched_fullHOVeto[4];
  TH1D *h_RPCMatchedBx_fullVeto[4];
  TH1D *h_RPCMatchedBxSpread_fullVeto[4];
  TH1D *h_RPCMatchedBxSpread_fullHOVeto[4];
  TH1D *h_nRPCMatched_Spread0_fullVeto[4];
  TH1D *h_RPCMatchedBx_Spread0_fullVeto[4];

  TH1D *h_dtRechitClusterEta_fullVeto[4];
  TH1D *h_dtRechitClusterPhi_fullVeto[4];
  TH1D *h_dtRechitClusterR_fullVeto[4];
  TH1D *h_dtRechitClusterZ_fullVeto[4];
  TH2D *h_dtRechitClusterRZ_fullVeto[4];
  TH2D *h_dtRechitClusterRZFine_fullVeto[4];
  TH2D *h_dtRechitClusterEtaPhi_fullVeto[4];
  TH2D *h_dtRechitClusterEtaPhiFine_fullVeto[4];
  TH1D *h_dtRechitClusterNWheels50_fullVeto[4];
  TH1D *h_dtRechitClusterNWheels25_fullVeto[4];
  TH1D *h_dtRechitClusterNWheels1_fullVeto[4];
  TH1D *h_dtRechitClusterMaxWheel_fullVeto[4];
  TH2D *h_npv_nDtRechitClusters_fullVeto[4];
  TH2D *h_npv_nDtRechitClusters_noVeto[4];

  TH1D *h_nHOMatched_fullVeto[4];
  TH1D *h_HOMatchedEnergy_fullVeto[4];
  TH1D *h_HOMatchedTime_fullVeto[4];
  TH2D *h_HOMatchedTime_RPCMatchedBx_fullVeto[4];
  TH1D *h_nHOMatched_invertedJetVeto[4];
  TH1D *h_HOMatchedEnergy_invertedJetVeto[4];
  TH1D *h_HOMatchedTime_invertedJetVeto[4];
  TH2D *h_HOMatchedTime_RPCMatchedBx_invertedJetVeto[4];
  TH1D *h_nHOMatched_noMB1Veto[4];
  TH1D *h_HOMatchedEnergy_noMB1Veto[4];
  TH1D *h_HOMatchedEnergyCluster280_noMB1Veto[4];
  TH1D *h_HOMatchedTime_noMB1Veto[4];
  TH2D *h_HOMatchedTime_RPCMatchedBx_noMB1Veto[4];
  TH1D *h_nHOMatched_invertedJet_noMB1Veto[4];
  TH1D *h_HOMatchedEnergy_invertedJet_noMB1Veto[4];
  TH1D *h_HOMatchedTime_invertedJet_noMB1Veto[4];
  TH2D *h_HOMatchedTime_RPCMatchedBx_invertedJet_noMB1Veto[4];

  TH1D *h_RPCMatchedBx_invertedJetVeto[4];
  TH1D *h_RPCMatchedBx_invertedMuonVeto[4];
  TH1D *h_RPCMatchedBx_invertedMuJetVeto[4];

  TH1D *h_dtRechitClusterSize_noMB1Veto[4];
  TH1D *h_dtRechitClusterNStation_noMB1Veto[4];
  TH1D *h_dtRechitClusterNRechitsMB1_noMB1Veto[4];
  TH1D *h_dtRechitClusterPercentRechitsMB1_noMB1Veto[4];
  TH1D *h_nRPCMatched_noMB1Veto[4];
  TH1D *h_nRPCMatchedLayer1_noMB1Veto[4];
  TH1D *h_nRPCMatchedLayer2_noMB1Veto[4];
  TH1D *h_nRPCMatchedLayer12_noMB1Veto[4];
  TH1D *h_RPCMatchedBxSpread_noMB1Veto[4];

  TH1D *h_dtRechitClusterSize_HOVeto[4];
  TH1D *h_nTotalClusteredRechits_HOVeto[4];
  TH1D *h_nTotalClusteredRechits_fullHOVeto[4];
  TH1D *h_nTotalClusteredRechits_fullHOVetoPlus[4];
  TH1D *h_dtRechitClusterSize_fullHOVeto[4];
  TH1D *h_dtRechitClusterSize_RPCMatch[4];
  TH1D *h_dtRechitClusterSize_RPCSpread0[4];

  TH1D *h_nTotalClusteredRechits_fullVetoPlus[4];
  TH1D *h_dtRechitClusterXSpread_fullVetoPlus[4];
  TH1D *h_dtRechitClusterYSpread_fullVetoPlus[4];
  TH1D *h_dtRechitClusterZSpread_fullVetoPlus[4];
  TH1D *h_dtRechitClusterEtaSpread_fullVetoPlus[4];
  TH1D *h_dtRechitClusterPhiSpread_fullVetoPlus[4];
  TH1D *h_dtRechitClusterEta_fullVetoPlus[4];
  TH1D *h_dtRechitClusterPhi_fullVetoPlus[4];
  TH2D *h_dtRechitClusterEtaPhi_fullVetoPlus[4];
  TH1D *h_dtRechitClusterNStation_fullVetoPlus[4];
  TH1D *h_dtRechitClusterNWheel_fullVetoPlus[4];
  TH1D *h_dtRechitClusterSizeRatio_fullVetoPlus[4];
  TH1D *h_dtRechitClusterSizeRatio_fullVetoMinus[4];

  TH1D *h_dtRechitClusterEta_fullHOVetoPlus[4];
  TH1D *h_dtRechitClusterPhi_fullHOVetoPlus[4];
  TH2D *h_dtRechitClusterEtaPhi_fullHOVetoPlus[4];
  TH1D *h_dtRechitClusterNStation_fullHOVetoPlus[4];
  TH1D *h_dtRechitClusterNWheel_fullHOVetoPlus[4];

  TH1D *h_HOTime_fullHOVeto[4];

  TH1D *h_muonPt_jetMB1Veto[4];
  TH1D *h_jetPt_muonMB1Veto[4];
  TH1D *h_MB1Rechits_jetMuonVeto[4];
  TH1D *h_muonPt_jetHOVeto[4];
  TH1D *h_jetPt_muonHOVeto[4];
  TH1D *h_HOEnergy_jetMuonVeto[4];

  TH1D *h_HOEnergy_jetVeto[4];

  TH1D *h_muonDR_fullVeto[4];
  TH1D *h_muonDR_RPCMatch[4];
  TH1D *h_muonDR_RPCSpread0[4];
  TH1D *h_jetDR_fullVeto[4];
  TH1D *h_jetDR_RPCMatch[4];
  TH1D *h_jetDR_RPCSpread0[4];
  TH1D *h_muonDR_fullHOVeto[4];
  TH1D *h_muonDR_HORPCMatch[4];
  TH1D *h_muonDR_HORPCSpread0[4];
  TH1D *h_jetDR_fullHOVeto[4];
  TH1D *h_jetDR_HORPCMatch[4];
  TH1D *h_jetDR_HORPCSpread0[4];
  TH1D *h_jetDR_minDR_fullHOVetoPlus[4];
  TH1D *h_jetPt_minDR_fullHOVetoPlus[4];
  TH1D *h_jetEta_minDR_fullHOVetoPlus[4];
  TH1D *h_jetPhi_minDR_fullHOVetoPlus[4];
  TH1D *h_jetChargedEMEnergyFraction_minDR_fullHOVetoPlus[4];
  TH1D *h_jetNeutralEMEnergyFraction_minDR_fullHOVetoPlus[4];
  TH1D *h_jetNeutralHadronEnergyFraction_minDR_fullHOVetoPlus[4];
  TH1D *h_jetChargedHadronEnergyFraction_minDR_fullHOVetoPlus[4];
  TH1D *h_jetMuonEnergyFraction_minDR_fullHOVetoPlus[4];
  TH1D *h_jetDR_minDR_fullHOVetoMinus[4];
  TH1D *h_jetPt_minDR_fullHOVetoMinus[4];
  TH1D *h_jetEta_minDR_fullHOVetoMinus[4];
  TH1D *h_jetPhi_minDR_fullHOVetoMinus[4];
  TH1D *h_jetChargedEMEnergyFraction_minDR_fullHOVetoMinus[4];
  TH1D *h_jetNeutralEMEnergyFraction_minDR_fullHOVetoMinus[4];
  TH1D *h_jetNeutralHadronEnergyFraction_minDR_fullHOVetoMinus[4];
  TH1D *h_jetChargedHadronEnergyFraction_minDR_fullHOVetoMinus[4];
  TH1D *h_jetMuonEnergyFraction_minDR_fullHOVetoMinus[4];
  TH1D *h_jetDR_minDR_vetoJet[4];
  TH1D *h_jetPt_minDR_vetoJet[4];
  TH1D *h_jetEta_minDR_vetoJet[4];
  TH1D *h_jetPhi_minDR_vetoJet[4];
  TH1D *h_jetChargedEMEnergyFraction_minDR_vetoJet[4];
  TH1D *h_jetNeutralEMEnergyFraction_minDR_vetoJet[4];
  TH1D *h_jetNeutralHadronEnergyFraction_minDR_vetoJet[4];
  TH1D *h_jetChargedHadronEnergyFraction_minDR_vetoJet[4];
  TH1D *h_jetMuonEnergyFraction_minDR_vetoJet[4];

  TH1D *h_dPhiJetMET_noRPCMatch_nRechitsLow[4];
  TH1D *h_dPhiJetMET_noRPCMatch_nRechitsHigh[4];
  TH1D *h_dtRechitClusterSize_noRPCMatch_dPhiLow[4];
  TH1D *h_dtRechitClusterSize_noRPCMatch_dPhiHigh[4];

  TH1D *h_nWheels1_noCluster[4];
  TH1D *h_nWheels10_noCluster[4];
  TH1D *h_nWheels20_noCluster[4];
  TH1D *h_nWheels30_noCluster[4];
  TH1D *h_nWheels50_noCluster[4];
  TH1D *h_nWheels150_noCluster[4];
  TH1D *h_nWheels1_noVeto[4];
  TH1D *h_nWheels1_fullVetoPlus[4];
  TH1D *h_nWheels1_fullVetoMinus[4];
  TH1D *h_nWheels10_noVeto[4];
  TH1D *h_nWheels10_fullVetoPlus[4];
  TH1D *h_nWheels10_fullVetoMinus[4];
  TH1D *h_nWheels20_noVeto[4];
  TH1D *h_nWheels20_fullVetoPlus[4];
  TH1D *h_nWheels20_fullVetoMinus[4];
  TH1D *h_nWheels30_noVeto[4];
  TH1D *h_nWheels30_fullVetoPlus[4];
  TH1D *h_nWheels30_fullVetoMinus[4];
  TH1D *h_nWheels50_noVeto[4];
  TH1D *h_nWheels50_fullVetoPlus[4];
  TH1D *h_nWheels50_fullVetoMinus[4];
  TH1D *h_nWheels150_noVeto[4];
  TH1D *h_nWheels150_fullVetoPlus[4];
  TH1D *h_nWheels150_fullVetoMinus[4];

  TH1D *h_jetPtMax_noVeto[4];
  TH1D *h_jetPtMax_fullVeto[4];
  TH1D *h_jetPtMax_fullVetoPlus[4];
  TH1D *h_jetPtMax_fullVetoMinus[4];
  TH1D *h_jetPtMET_noVeto[4];
  TH1D *h_jetPtMET_fullVeto[4];
  TH1D *h_jetPtMET_fullVetoPlus[4];
  TH1D *h_jetPtMET_fullVetoMinus[4];

  TH1D *h_jetPtMET_noVeto_rpcCR[4];
  TH1D *h_jetPtMET_fullVeto_rpcCR[4];
  TH1D *h_jetPtMET_fullVetoPlus_rpcCR[4];
  TH1D *h_dtRechitClusterPhiStation2_fullVeto_rpcCR[4];
  TH1D *h_dtRechitClusterPhiStation3_fullVeto_rpcCR[4];
  TH1D *h_dtRechitClusterPhiStation4_fullVeto_rpcCR[4];

  TH1D *h_runNum_phi = new TH1D("h_runNum_phi","",80,270e3,350e3);
  TH1D *h_runNum_eta = new TH1D("h_runNum_eta","",80,270e3,350e3);
  TH1D *h_runNum_etaphi = new TH1D("h_runNum_etaphi","",80,270e3,350e3);
  TH1D *h_badRun_lumiSec = new TH1D("h_badRun_lumiSec","",3500,0,3500);
  TH1D *h_badRun_dtRechitClusterSize = new TH1D("h_badRun_dtRechitClusterSize","",100,0,1000);
  TH1D *h_badRun_dtRechitClusterNStation = new TH1D("h_badRun_dtRechitClusterNStation","",5,0,5);
  TH1D *h_badRun_dtRechitClusterXSpread = new TH1D("h_badRun_dtRechitClusterXSpread","",40,0,400);
  TH1D *h_badRun_dtRechitClusterYSpread = new TH1D("h_badRun_dtRechitClusterYSpread","",40,0,400);
  TH1D *h_badRun_dtRechitClusterPhiSpread = new TH1D("h_badRun_dtRechitClusterPhiSpread","",40,0,2);
  TH1D *h_badRun_dtRechitClusterNWheel = new TH1D("h_badRun_dtRechitClusterNWheel","",40,0,2);

  Int_t rechitCount[5];
  Int_t stationCount[4];
  Int_t rechitWheel = -99;
  Int_t rechitStation = -99;
  Int_t hitWheels1 = -1;
  Int_t hitWheels10 = -1;
  Int_t hitWheels20 = -1;
  Int_t hitWheels30 = -1;
  Int_t hitWheels50 = -1;
  Int_t hitWheels150 = -1;
  Int_t nStationUnclustered = -1;
  Int_t nThreshStation = -1;
  Int_t nThreshLowStation = -1;
  Int_t nThreshStationUnclustered = -1;
  Int_t nThreshLowStationUnclustered = -1;

  Double_t dPhi_tmp = 0.0;
  Double_t dPhiClusterMET = 0.0;
  Double_t dPhiClusterMET_max = -1.0;
  Double_t dPhi_min = 999.;
  Double_t dPhi_minTop4 = 999.;
  Double_t dPhi_min20 = 999.;
  Double_t dPhi_min30 = 999.;
  Double_t dPhi_min50 = 999.;
  Double_t clustSizeMax = 0.;
  Double_t dPhi_clust = 999.;
  Double_t jetPt_tmp = 0.0;
  Double_t jetPt_max = 0.0;
  Double_t jetDR_min = 0.0;
  Double_t muonPt_max = 0.0;
  Double_t muonDR_min = 0.0;
  Int_t jetDR_index = -1;
  Int_t muonDR_index = -1;

  vector<Int_t> muStatus = {};
  Double_t dR_tmp = 0.0;
  Int_t nMatched = 0;
  vector<Int_t> goodStatus = {1,44,51,52,91};
  vector<Int_t> rpcBx = {};
  vector<Int_t> rpcLayer = {};
  Int_t rpcSpread = 0;
  Float_t rpcMedian = 0;

  Int_t evtNum = 0;
  Bool_t goodEvt = false;
  Int_t itr_file = 0;
  Int_t goodJets = 0;
  Bool_t matchJet = false;
  Bool_t matchMuon = false;
  Int_t match = 0;
  Int_t matchLayer1 = 0;
  Int_t matchLayer2 = 0;
  Int_t matchLayer3 = 0;
  Int_t matchLayer4 = 0;
  Int_t matchHO = 0;
  Float_t sumE = 0;
  Float_t weightT = 0;
  Float_t totalSumE = 0;

  Bool_t passMuon = false;
  Bool_t passJet = false;
  Bool_t passMB1 = false;
  Bool_t passMB1_alt = false;
  Bool_t passMuon_alt = false;
  Bool_t passHO = false;
  Bool_t passInvertedJet = false;
  Bool_t passInvertedMuon = false;
  Bool_t passInvertedMuJet = false;
  Int_t nPassMuon = 0;
  Int_t nPassMuon_std = 0;
  Int_t nPassMB1_std = 0;
  Int_t nPassMuon_alt = 0;
  Int_t nPassMB1_alt = 0;
  Int_t nPassJet = 0;
  Int_t nPassJetMuon = 0;
  Int_t nPassMB1 = 0;
  Int_t nPassHO = 0;
  Int_t nPassJetMuon_std = 0;
  Int_t nPassJetMB1_std = 0;
  Int_t nPassFull = 0;
  Int_t nPassFull_std = 0;
  Int_t nPassFull_altMuon = 0;
  Int_t nPassFull_altMB1 = 0;
  Int_t nPassFull_altMuonMB1 = 0;
  Int_t nPassFullPlus = 0;
  Int_t nPassFullPlus_rpcCR = 0;
  Int_t nPassFullMinus = 0;
  Int_t nPassFullDT = 0;
  Int_t nPassFullDTPlus_noMuon = 0;
  Int_t nPassFullDTPlus_noMB1 = 0;
  Int_t nPassFullDTPlus_std = 0;
  Int_t nPassFullDTPlus_altMuon = 0;
  Int_t nPassFullDTPlus_altMB1 = 0;
  Int_t nPassFullDTPlus_altMuonMB1 = 0;
  Int_t nPassFullHO = 0;
  Int_t nPassNone = 0;
  Int_t totalClusteredNone = 0;
  Int_t totalClusteredJet = 0;
  Int_t totalClusteredMB1 = 0;
  Int_t totalClusteredNoMB1 = 0;
  Int_t totalClusteredHO = 0;
  Int_t totalClusteredFull = 0;
  Int_t totalClusteredFullHO = 0;

  Int_t totalClusteredFullPlus = 0;
  Int_t totalClusteredFullHOPlus = 0;

  Int_t nPassMET = 0;
  Int_t nPassDecayDT = 0;
  Int_t nPassDecayHO = 0;
  Bool_t failJetMET = false;
  Bool_t failJetMET_20 = false;
  Bool_t failJetMET_30 = false;
  Bool_t failJetMET_50 = false;
  Bool_t failJetMET_top4 = false;
  Int_t nPassJetMET = 0;
  Int_t nFailJetMET = 0;
  Int_t nFailJetMET_top4 = 0;
  Int_t nFailJetMET_20 = 0;
  Int_t nFailJetMET_30 = 0;
  Int_t nFailJetMET_50 = 0;
  Int_t nPassCluster = 0;
  Int_t nPassMaxStation_dt = 0;
  Int_t nPassDeltaPhi_dt = 0;
  Int_t nPassRPCMatch_dt = 0;
  Int_t nPassRPCSpread_dt = 0;
  Int_t nPassDeltaPhi_ho = 0;
  Int_t nPassRPCMatch_ho = 0;
  Int_t nPassRPCSpread_ho = 0;

  ofstream eventList;
  eventList.open("events/fullHOVetoPlusEvents.txt");

  for(Int_t itr_year=0; itr_year<3; itr_year++){
    sprintf(name,"h_jetMet_dPhiMin4_%s",years[itr_year]);
    h_jetMet_dPhiMin4[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMET_%s",years[itr_year]);
    h_dPhiJetMET[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMET_noVeto_%s",years[itr_year]);
    h_dPhiJetMET_noVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMET_jetVeto_%s",years[itr_year]);
    h_dPhiJetMET_jetVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMET_muonVeto_%s",years[itr_year]);
    h_dPhiJetMET_muonVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMET_MB1Veto_%s",years[itr_year]);
    h_dPhiJetMET_MB1Veto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMET_noMB1Veto_%s",years[itr_year]);
    h_dPhiJetMET_noMB1Veto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMET_fullVeto_%s",years[itr_year]);
    h_dPhiJetMET_fullVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMET_fullHOVeto_%s",years[itr_year]);
    h_dPhiJetMET_fullHOVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_MET_%s",years[itr_year]);
    h_MET[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_jetPt_%s",years[itr_year]);
    h_jetPt[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nDtRechitClusters_noVeto_%s",years[itr_year]);
    h_nDtRechitClusters_noVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterSize_noVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_noVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechits_noVeto_%s",years[itr_year]);
    h_nTotalClusteredRechits_noVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterMaxStation_noVeto_%s",years[itr_year]);
    h_dtRechitClusterMaxStation_noVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNStation_noVeto_%s",years[itr_year]);
    h_dtRechitClusterNStation_noVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dPhiClusterMET_noVeto_%s",years[itr_year]);
    h_dPhiClusterMET_noVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dtRechitClusterXSpread_noVeto_%s",years[itr_year]);
    h_dtRechitClusterXSpread_noVeto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterYSpread_noVeto_%s",years[itr_year]);
    h_dtRechitClusterYSpread_noVeto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterZSpread_noVeto_%s",years[itr_year]);
    h_dtRechitClusterZSpread_noVeto[itr_file] = new TH1D(name,"",30,0,150);

    sprintf(name,"h_dtRechitClusterEtaSpread_noVeto_%s",years[itr_year]);
    h_dtRechitClusterEtaSpread_noVeto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_dtRechitClusterPhiSpread_noVeto_%s",years[itr_year]);
    h_dtRechitClusterPhiSpread_noVeto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_RPCMatchedBx_noVeto_%s",years[itr_year]);
    h_RPCMatchedBx_noVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_noVeto_%s",years[itr_year]);
    h_nRPCMatched_noVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBxSpread_noVeto_%s",years[itr_year]);
    h_RPCMatchedBxSpread_noVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBx_Spread0_noVeto_%s",years[itr_year]);
    h_RPCMatchedBx_Spread0_noVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_Spread0_noVeto_%s",years[itr_year]);
    h_nRPCMatched_Spread0_noVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_nDtRechitClusters_muonVeto_%s",years[itr_year]);
    h_nDtRechitClusters_muonVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterSize_muonVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_muonVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechits_muonVeto_%s",years[itr_year]);
    h_nTotalClusteredRechits_muonVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterMaxStation_muonVeto_%s",years[itr_year]);
    h_dtRechitClusterMaxStation_muonVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNStation_muonVeto_%s",years[itr_year]);
    h_dtRechitClusterNStation_muonVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dPhiClusterMET_muonVeto_%s",years[itr_year]);
    h_dPhiClusterMET_muonVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dtRechitClusterXSpread_muonVeto_%s",years[itr_year]);
    h_dtRechitClusterXSpread_muonVeto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterYSpread_muonVeto_%s",years[itr_year]);
    h_dtRechitClusterYSpread_muonVeto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterZSpread_muonVeto_%s",years[itr_year]);
    h_dtRechitClusterZSpread_muonVeto[itr_file] = new TH1D(name,"",30,0,150);

    sprintf(name,"h_dtRechitClusterEtaSpread_muonVeto_%s",years[itr_year]);
    h_dtRechitClusterEtaSpread_muonVeto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_dtRechitClusterPhiSpread_muonVeto_%s",years[itr_year]);
    h_dtRechitClusterPhiSpread_muonVeto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_RPCMatchedBx_muonVeto_%s",years[itr_year]);
    h_RPCMatchedBx_muonVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_muonVeto_%s",years[itr_year]);
    h_nRPCMatched_muonVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBxSpread_muonVeto_%s",years[itr_year]);
    h_RPCMatchedBxSpread_muonVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBx_Spread0_muonVeto_%s",years[itr_year]);
    h_RPCMatchedBx_Spread0_muonVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_Spread0_muonVeto_%s",years[itr_year]);
    h_nRPCMatched_Spread0_muonVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_nDtRechitClusters_jetVeto_%s",years[itr_year]);
    h_nDtRechitClusters_jetVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterSize_jetVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_jetVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechits_jetVeto_%s",years[itr_year]);
    h_nTotalClusteredRechits_jetVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterMaxStation_jetVeto_%s",years[itr_year]);
    h_dtRechitClusterMaxStation_jetVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNStation_jetVeto_%s",years[itr_year]);
    h_dtRechitClusterNStation_jetVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dPhiClusterMET_jetVeto_%s",years[itr_year]);
    h_dPhiClusterMET_jetVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dtRechitClusterXSpread_jetVeto_%s",years[itr_year]);
    h_dtRechitClusterXSpread_jetVeto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterYSpread_jetVeto_%s",years[itr_year]);
    h_dtRechitClusterYSpread_jetVeto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterZSpread_jetVeto_%s",years[itr_year]);
    h_dtRechitClusterZSpread_jetVeto[itr_file] = new TH1D(name,"",30,0,150);

    sprintf(name,"h_dtRechitClusterEtaSpread_jetVeto_%s",years[itr_year]);
    h_dtRechitClusterEtaSpread_jetVeto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_dtRechitClusterPhiSpread_jetVeto_%s",years[itr_year]);
    h_dtRechitClusterPhiSpread_jetVeto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_RPCMatchedBx_jetVeto_%s",years[itr_year]);
    h_RPCMatchedBx_jetVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_jetVeto_%s",years[itr_year]);
    h_nRPCMatched_jetVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_nRPCMatchedLayer1_jetVeto_%s",years[itr_year]);
    h_nRPCMatchedLayer1_jetVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_nRPCMatchedLayer2_jetVeto_%s",years[itr_year]);
    h_nRPCMatchedLayer2_jetVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_nRPCMatchedLayer3_jetVeto_%s",years[itr_year]);
    h_nRPCMatchedLayer3_jetVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_nRPCMatchedLayer4_jetVeto_%s",years[itr_year]);
    h_nRPCMatchedLayer4_jetVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_nRPCMatchedLayer1_fullHOVeto_%s",years[itr_year]);
    h_nRPCMatchedLayer1_fullHOVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_nRPCMatchedLayer2_fullHOVeto_%s",years[itr_year]);
    h_nRPCMatchedLayer2_fullHOVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_nRPCMatchedLayer3_fullHOVeto_%s",years[itr_year]);
    h_nRPCMatchedLayer3_fullHOVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_nRPCMatchedLayer4_fullHOVeto_%s",years[itr_year]);
    h_nRPCMatchedLayer4_fullHOVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_RPCMatchedBxSpread_jetVeto_%s",years[itr_year]);
    h_RPCMatchedBxSpread_jetVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBx_Spread0_jetVeto_%s",years[itr_year]);
    h_RPCMatchedBx_Spread0_jetVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_Spread0_jetVeto_%s",years[itr_year]);
    h_nRPCMatched_Spread0_jetVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_nDtRechitClusters_MB1Veto_%s",years[itr_year]);
    h_nDtRechitClusters_MB1Veto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterSize_MB1Veto_%s",years[itr_year]);
    h_dtRechitClusterSize_MB1Veto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechits_MB1Veto_%s",years[itr_year]);
    h_nTotalClusteredRechits_MB1Veto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechits_noMB1Veto_%s",years[itr_year]);
    h_nTotalClusteredRechits_noMB1Veto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterMaxStation_MB1Veto_%s",years[itr_year]);
    h_dtRechitClusterMaxStation_MB1Veto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNStation_MB1Veto_%s",years[itr_year]);
    h_dtRechitClusterNStation_MB1Veto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dPhiClusterMET_MB1Veto_%s",years[itr_year]);
    h_dPhiClusterMET_MB1Veto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dtRechitClusterXSpread_MB1Veto_%s",years[itr_year]);
    h_dtRechitClusterXSpread_MB1Veto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterYSpread_MB1Veto_%s",years[itr_year]);
    h_dtRechitClusterYSpread_MB1Veto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterZSpread_MB1Veto_%s",years[itr_year]);
    h_dtRechitClusterZSpread_MB1Veto[itr_file] = new TH1D(name,"",30,0,150);

    sprintf(name,"h_dtRechitClusterEtaSpread_MB1Veto_%s",years[itr_year]);
    h_dtRechitClusterEtaSpread_MB1Veto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_dtRechitClusterPhiSpread_MB1Veto_%s",years[itr_year]);
    h_dtRechitClusterPhiSpread_MB1Veto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_RPCMatchedBx_MB1Veto_%s",years[itr_year]);
    h_RPCMatchedBx_MB1Veto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_MB1Veto_%s",years[itr_year]);
    h_nRPCMatched_MB1Veto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBxSpread_MB1Veto_%s",years[itr_year]);
    h_RPCMatchedBxSpread_MB1Veto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBx_Spread0_MB1Veto_%s",years[itr_year]);
    h_RPCMatchedBx_Spread0_MB1Veto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_Spread0_MB1Veto_%s",years[itr_year]);
    h_nRPCMatched_Spread0_MB1Veto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_nDtRechitClusters_fullVeto_%s",years[itr_year]);
    h_nDtRechitClusters_fullVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterSize_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_fullVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechits_fullVeto_%s",years[itr_year]);
    h_nTotalClusteredRechits_fullVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterMaxStation_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterMaxStation_fullVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterMaxStation_fullHOVeto_%s",years[itr_year]);
    h_dtRechitClusterMaxStation_fullHOVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNStation_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterNStation_fullVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNStationUnclustered_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterNStationUnclustered_fullVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNThreshStation_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterNThreshStation_fullVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNThreshLowStation_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterNThreshLowStation_fullVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNThreshStationUnclustered_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterNThreshStationUnclustered_fullVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNThreshLowStationUnclustered_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterNThreshLowStationUnclustered_fullVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dPhiClusterMET_fullVeto_%s",years[itr_year]);
    h_dPhiClusterMET_fullVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiClusterMET_fullHOVeto_%s",years[itr_year]);
    h_dPhiClusterMET_fullHOVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dtRechitClusterXSpread_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterXSpread_fullVeto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterYSpread_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterYSpread_fullVeto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterZSpread_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterZSpread_fullVeto[itr_file] = new TH1D(name,"",30,0,150);

    sprintf(name,"h_dtRechitClusterEtaSpread_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterEtaSpread_fullVeto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_dtRechitClusterPhiSpread_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterPhiSpread_fullVeto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_RPCMatchedBx_fullVeto_%s",years[itr_year]);
    h_RPCMatchedBx_fullVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_fullVeto_%s",years[itr_year]);
    h_nRPCMatched_fullVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_nRPCMatched_fullHOVeto_%s",years[itr_year]);
    h_nRPCMatched_fullHOVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBxSpread_fullVeto_%s",years[itr_year]);
    h_RPCMatchedBxSpread_fullVeto[itr_file] = new TH1D(name,"",10,0,10);

    sprintf(name,"h_RPCMatchedBxSpread_fullHOVeto_%s",years[itr_year]);
    h_RPCMatchedBxSpread_fullHOVeto[itr_file] = new TH1D(name,"",10,0,10);

    sprintf(name,"h_RPCMatchedBx_Spread0_fullVeto_%s",years[itr_year]);
    h_RPCMatchedBx_Spread0_fullVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_Spread0_fullVeto_%s",years[itr_year]);
    h_nRPCMatched_Spread0_fullVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_dtRechitClusterEta_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterEta_fullVeto[itr_file] = new TH1D(name,"",60,-3,3);

    sprintf(name,"h_dtRechitClusterPhi_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterPhi_fullVeto[itr_file] = new TH1D(name,"",70,-3.5,3.5);

    sprintf(name,"h_dtRechitClusterR_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterR_fullVeto[itr_file] = new TH1D(name,"",40,0,800);

    sprintf(name,"h_dtRechitClusterZ_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterZ_fullVeto[itr_file] = new TH1D(name,"",120,-600,600);

    sprintf(name,"h_dtRechitClusterRZ_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterRZ_fullVeto[itr_file] = new TH2D(name,"",120,-600,600,40,400,800);

    sprintf(name,"h_dtRechitClusterRZFine_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterRZFine_fullVeto[itr_file] = new TH2D(name,"",1200,-600,600,400,400,800);

    sprintf(name,"h_dtRechitClusterEtaPhi_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterEtaPhi_fullVeto[itr_file] = new TH2D(name,"",16,-2,2,70,-3.5,3.5);

    sprintf(name,"h_dtRechitClusterEtaPhiFine_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterEtaPhiFine_fullVeto[itr_file] = new TH2D(name,"",16,-2,2,140,-3.5,3.5);

    sprintf(name,"h_dtRechitClusterNWheels50_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterNWheels50_fullVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_dtRechitClusterNWheels25_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterNWheels25_fullVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_dtRechitClusterNWheels1_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterNWheels1_fullVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_dtRechitClusterMaxWheel_fullVeto_%s",years[itr_year]);
    h_dtRechitClusterMaxWheel_fullVeto[itr_file] = new TH1D(name,"",6,-3,3);

    sprintf(name,"h_npv_nDtRechitClusters_fullVeto_%s",years[itr_year]);
    h_npv_nDtRechitClusters_fullVeto[itr_file] = new TH2D(name,"",50,0,100,5,0,5);

    sprintf(name,"h_nHOMatched_fullVeto_%s",years[itr_year]);
    h_nHOMatched_fullVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_HOMatchedEnergy_fullVeto_%s",years[itr_year]);
    h_HOMatchedEnergy_fullVeto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_HOMatchedTime_fullVeto_%s",years[itr_year]);
    h_HOMatchedTime_fullVeto[itr_file] = new TH1D(name,"",60,-60,60);

    sprintf(name,"h_HOMatchedTime_RPCMatchedBx_fullVeto_%s",years[itr_year]);
    h_HOMatchedTime_RPCMatchedBx_fullVeto[itr_file] = new TH2D(name,"",60,-60,60,13,-6.5,6.5);

    sprintf(name,"h_nHOMatched_invertedJetVeto_%s",years[itr_year]);
    h_nHOMatched_invertedJetVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_HOMatchedEnergy_invertedJetVeto_%s",years[itr_year]);
    h_HOMatchedEnergy_invertedJetVeto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_HOMatchedTime_invertedJetVeto_%s",years[itr_year]);
    h_HOMatchedTime_invertedJetVeto[itr_file] = new TH1D(name,"",60,-60,60);

    sprintf(name,"h_HOMatchedTime_RPCMatchedBx_invertedJetVeto_%s",years[itr_year]);
    h_HOMatchedTime_RPCMatchedBx_invertedJetVeto[itr_file] = new TH2D(name,"",60,-60,60,13,-6.5,6.5);

    sprintf(name,"h_nHOMatched_noMB1Veto_%s",years[itr_year]);
    h_nHOMatched_noMB1Veto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_HOMatchedEnergy_noMB1Veto_%s",years[itr_year]);
    h_HOMatchedEnergy_noMB1Veto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_HOMatchedEnergyCluster280_noMB1Veto_%s",years[itr_year]);
    h_HOMatchedEnergyCluster280_noMB1Veto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_HOMatchedTime_noMB1Veto_%s",years[itr_year]);
    h_HOMatchedTime_noMB1Veto[itr_file] = new TH1D(name,"",60,-60,60);

    sprintf(name,"h_HOMatchedTime_RPCMatchedBx_noMB1Veto_%s",years[itr_year]);
    h_HOMatchedTime_RPCMatchedBx_noMB1Veto[itr_file] = new TH2D(name,"",60,-60,60,13,-6.5,6.5);

    sprintf(name,"h_nHOMatched_invertedJet_noMB1Veto_%s",years[itr_year]);
    h_nHOMatched_invertedJet_noMB1Veto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_HOMatchedEnergy_invertedJet_noMB1Veto_%s",years[itr_year]);
    h_HOMatchedEnergy_invertedJet_noMB1Veto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_HOMatchedTime_invertedJet_noMB1Veto_%s",years[itr_year]);
    h_HOMatchedTime_invertedJet_noMB1Veto[itr_file] = new TH1D(name,"",60,-60,60);

    sprintf(name,"h_HOMatchedTime_RPCMatchedBx_invertedJet_noMB1Veto_%s",years[itr_year]);
    h_HOMatchedTime_RPCMatchedBx_invertedJet_noMB1Veto[itr_file] = new TH2D(name,"",60,-60,60,13,-6.5,6.5);

    sprintf(name,"h_npv_nDtRechitClusters_noVeto_%s",years[itr_year]);
    h_npv_nDtRechitClusters_noVeto[itr_file] = new TH2D(name,"",50,0,100,5,0,5);

    sprintf(name,"h_RPCMatchedBx_invertedJetVeto_%s",years[itr_year]);
    h_RPCMatchedBx_invertedJetVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_RPCMatchedBx_invertedMuonVeto_%s",years[itr_year]);
    h_RPCMatchedBx_invertedMuonVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_RPCMatchedBx_invertedMuJetVeto_%s",years[itr_year]);
    h_RPCMatchedBx_invertedMuJetVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_dtRechitClusterSize_noMB1Veto_%s",years[itr_year]);
    h_dtRechitClusterSize_noMB1Veto[itr_file] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterNStation_noMB1Veto_%s",years[itr_year]);
    h_dtRechitClusterNStation_noMB1Veto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNRechitsMB1_noMB1Veto_%s",years[itr_year]);
    h_dtRechitClusterNRechitsMB1_noMB1Veto[itr_file] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterPercentRechitsMB1_noMB1Veto_%s",years[itr_year]);
    h_dtRechitClusterPercentRechitsMB1_noMB1Veto[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_nRPCMatched_noMB1Veto_%s",years[itr_year]);
    h_nRPCMatched_noMB1Veto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_nRPCMatchedLayer1_noMB1Veto_%s",years[itr_year]);
    h_nRPCMatchedLayer1_noMB1Veto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_nRPCMatchedLayer2_noMB1Veto_%s",years[itr_year]);
    h_nRPCMatchedLayer2_noMB1Veto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_nRPCMatchedLayer12_noMB1Veto_%s",years[itr_year]);
    h_nRPCMatchedLayer12_noMB1Veto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBxSpread_noMB1Veto_%s",years[itr_year]);
    h_RPCMatchedBxSpread_noMB1Veto[itr_file] = new TH1D(name,"",10,0,10);

    sprintf(name,"h_dtRechitClusterSize_HOVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_HOVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSize_fullHOVeto_%s",years[itr_year]);
    h_dtRechitClusterSize_fullHOVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechits_HOVeto_%s",years[itr_year]);
    h_nTotalClusteredRechits_HOVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechits_fullHOVeto_%s",years[itr_year]);
    h_nTotalClusteredRechits_fullHOVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechits_fullVetoPlus_%s",years[itr_year]);
    h_nTotalClusteredRechits_fullVetoPlus[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechits_fullHOVetoPlus_%s",years[itr_year]);
    h_nTotalClusteredRechits_fullHOVetoPlus[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterXSpread_fullVetoPlus_%s",years[itr_year]);
    h_dtRechitClusterXSpread_fullVetoPlus[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterYSpread_fullVetoPlus_%s",years[itr_year]);
    h_dtRechitClusterYSpread_fullVetoPlus[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterZSpread_fullVetoPlus_%s",years[itr_year]);
    h_dtRechitClusterZSpread_fullVetoPlus[itr_file] = new TH1D(name,"",30,0,150);

    sprintf(name,"h_dtRechitClusterEtaSpread_fullVetoPlus_%s",years[itr_year]);
    h_dtRechitClusterEtaSpread_fullVetoPlus[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_dtRechitClusterPhiSpread_fullVetoPlus_%s",years[itr_year]);
    h_dtRechitClusterPhiSpread_fullVetoPlus[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_dtRechitClusterEta_fullVetoPlus_%s",years[itr_year]);
    h_dtRechitClusterEta_fullVetoPlus[itr_file] = new TH1D(name,"",60,-3,3);

    sprintf(name,"h_dtRechitClusterPhi_fullVetoPlus_%s",years[itr_year]);
    h_dtRechitClusterPhi_fullVetoPlus[itr_file] = new TH1D(name,"",70,-3.5,3.5);

    sprintf(name,"h_dtRechitClusterEtaPhi_fullVetoPlus_%s",years[itr_year]);
    h_dtRechitClusterEtaPhi_fullVetoPlus[itr_file] = new TH2D(name,"",70,-3.5,3.5,60,-3,3);

    sprintf(name,"h_dtRechitClusterNStation_fullVetoPlus_%s",years[itr_year]);
    h_dtRechitClusterNStation_fullVetoPlus[itr_file] = new TH1D(name,"",4,0,4);

    sprintf(name,"h_dtRechitClusterNWheel_fullVetoPlus_%s",years[itr_year]);
    h_dtRechitClusterNWheel_fullVetoPlus[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNWheel_fullHOVetoPlus_%s",years[itr_year]);
    h_dtRechitClusterNWheel_fullHOVetoPlus[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterSizeRatio_fullVetoPlus_%s",years[itr_year]);
    h_dtRechitClusterSizeRatio_fullVetoPlus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_dtRechitClusterSizeRatio_fullVetoMinus_%s",years[itr_year]);
    h_dtRechitClusterSizeRatio_fullVetoMinus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_dtRechitClusterEta_fullHOVetoPlus_%s",years[itr_year]);
    h_dtRechitClusterEta_fullHOVetoPlus[itr_file] = new TH1D(name,"",60,-3,3);

    sprintf(name,"h_dtRechitClusterPhi_fullHOVetoPlus_%s",years[itr_year]);
    h_dtRechitClusterPhi_fullHOVetoPlus[itr_file] = new TH1D(name,"",70,-3.5,3.5);

    sprintf(name,"h_dtRechitClusterEtaPhi_fullHOVetoPlus_%s",years[itr_year]);
    h_dtRechitClusterEtaPhi_fullHOVetoPlus[itr_file] = new TH2D(name,"",70,-3.5,3.5,60,-3,3);

    sprintf(name,"h_dtRechitClusterNStation_fullHOVetoPlus_%s",years[itr_year]);
    h_dtRechitClusterNStation_fullHOVetoPlus[itr_file] = new TH1D(name,"",4,0,4);

    sprintf(name,"h_dtRechitClusterSize_RPCMatch_%s",years[itr_year]);
    h_dtRechitClusterSize_RPCMatch[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSize_RPCSpread0_%s",years[itr_year]);
    h_dtRechitClusterSize_RPCSpread0[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_HOTime_fullHOVeto_%s",years[itr_year]);
    h_HOTime_fullHOVeto[itr_file] = new TH1D(name,"",60,-60,60);

    sprintf(name,"h_muonPt_jetMB1Veto_%s",years[itr_year]);
    h_muonPt_jetMB1Veto[itr_file] = new TH1D(name,"",50,0,100);

    sprintf(name,"h_jetPt_muonMB1Veto_%s",years[itr_year]);
    h_jetPt_muonMB1Veto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_MB1Rechits_jetMuonVeto_%s",years[itr_year]);
    h_MB1Rechits_jetMuonVeto[itr_file] = new TH1D(name,"",200,0,200);

    sprintf(name,"h_muonPt_jetHOVeto_%s",years[itr_year]);
    h_muonPt_jetHOVeto[itr_file] = new TH1D(name,"",50,0,100);

    sprintf(name,"h_jetPt_muonHOVeto_%s",years[itr_year]);
    h_jetPt_muonHOVeto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_HOEnergy_jetMuonVeto_%s",years[itr_year]);
    h_HOEnergy_jetMuonVeto[itr_file] = new TH1D(name,"",40,0,200);

    sprintf(name,"h_HOEnergy_jetVeto_%s",years[itr_year]);
    h_HOEnergy_jetVeto[itr_file] = new TH1D(name,"",40,0,200);

    sprintf(name,"h_muonDR_fullVeto_%s",years[itr_year]);
    h_muonDR_fullVeto[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_muonDR_RPCMatch_%s",years[itr_year]);
    h_muonDR_RPCMatch[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_muonDR_RPCSpread0_%s",years[itr_year]);
    h_muonDR_RPCSpread0[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetDR_fullVeto_%s",years[itr_year]);
    h_jetDR_fullVeto[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetDR_RPCMatch_%s",years[itr_year]);
    h_jetDR_RPCMatch[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetDR_RPCSpread0_%s",years[itr_year]);
    h_jetDR_RPCSpread0[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_muonDR_fullHOVeto_%s",years[itr_year]);
    h_muonDR_fullHOVeto[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_muonDR_HORPCMatch_%s",years[itr_year]);
    h_muonDR_HORPCMatch[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_muonDR_HORPCSpread0_%s",years[itr_year]);
    h_muonDR_HORPCSpread0[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetDR_fullHOVeto_%s",years[itr_year]);
    h_jetDR_fullHOVeto[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetDR_HORPCMatch_%s",years[itr_year]);
    h_jetDR_HORPCMatch[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetDR_HORPCSpread0_%s",years[itr_year]);
    h_jetDR_HORPCSpread0[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetDR_minDR_fullHOVetoPlus_%s",years[itr_year]);
    h_jetDR_minDR_fullHOVetoPlus[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetPt_minDR_fullHOVetoPlus_%s",years[itr_year]);
    h_jetPt_minDR_fullHOVetoPlus[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetEta_minDR_fullHOVetoPlus_%s",years[itr_year]);
    h_jetEta_minDR_fullHOVetoPlus[itr_file] = new TH1D(name,"",60,-3,3);

    sprintf(name,"h_jetPhi_minDR_fullHOVetoPlus_%s",years[itr_year]);
    h_jetPhi_minDR_fullHOVetoPlus[itr_file] = new TH1D(name,"",70,-3.5,3.5);

    sprintf(name,"h_jetChargedEMEnergyFraction_minDR_fullHOVetoPlus_%s",years[itr_year]);
    h_jetChargedEMEnergyFraction_minDR_fullHOVetoPlus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetNeutralEMEnergyFraction_minDR_fullHOVetoPlus_%s",years[itr_year]);
    h_jetNeutralEMEnergyFraction_minDR_fullHOVetoPlus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetChargedHadronEnergyFraction_minDR_fullHOVetoPlus_%s",years[itr_year]);
    h_jetChargedHadronEnergyFraction_minDR_fullHOVetoPlus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetNeutralHadronEnergyFraction_minDR_fullHOVetoPlus_%s",years[itr_year]);
    h_jetNeutralHadronEnergyFraction_minDR_fullHOVetoPlus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetMuonEnergyFraction_minDR_fullHOVetoPlus_%s",years[itr_year]);
    h_jetMuonEnergyFraction_minDR_fullHOVetoPlus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetDR_minDR_fullHOVetoMinus_%s",years[itr_year]);
    h_jetDR_minDR_fullHOVetoMinus[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetPt_minDR_fullHOVetoMinus_%s",years[itr_year]);
    h_jetPt_minDR_fullHOVetoMinus[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetEta_minDR_fullHOVetoMinus_%s",years[itr_year]);
    h_jetEta_minDR_fullHOVetoMinus[itr_file] = new TH1D(name,"",60,-3,3);

    sprintf(name,"h_jetPhi_minDR_fullHOVetoMinus_%s",years[itr_year]);
    h_jetPhi_minDR_fullHOVetoMinus[itr_file] = new TH1D(name,"",70,-3.5,3.5);

    sprintf(name,"h_jetChargedEMEnergyFraction_minDR_fullHOVetoMinus_%s",years[itr_year]);
    h_jetChargedEMEnergyFraction_minDR_fullHOVetoMinus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetNeutralEMEnergyFraction_minDR_fullHOVetoMinus_%s",years[itr_year]);
    h_jetNeutralEMEnergyFraction_minDR_fullHOVetoMinus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetChargedHadronEnergyFraction_minDR_fullHOVetoMinus_%s",years[itr_year]);
    h_jetChargedHadronEnergyFraction_minDR_fullHOVetoMinus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetNeutralHadronEnergyFraction_minDR_fullHOVetoMinus_%s",years[itr_year]);
    h_jetNeutralHadronEnergyFraction_minDR_fullHOVetoMinus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetMuonEnergyFraction_minDR_fullHOVetoMinus_%s",years[itr_year]);
    h_jetMuonEnergyFraction_minDR_fullHOVetoMinus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetDR_minDR_vetoJet_%s",years[itr_year]);
    h_jetDR_minDR_vetoJet[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetPt_minDR_vetoJet_%s",years[itr_year]);
    h_jetPt_minDR_vetoJet[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetEta_minDR_vetoJet_%s",years[itr_year]);
    h_jetEta_minDR_vetoJet[itr_file] = new TH1D(name,"",60,-3,3);

    sprintf(name,"h_jetPhi_minDR_vetoJet_%s",years[itr_year]);
    h_jetPhi_minDR_vetoJet[itr_file] = new TH1D(name,"",70,-3.5,3.5);

    sprintf(name,"h_jetChargedEMEnergyFraction_minDR_vetoJet_%s",years[itr_year]);
    h_jetChargedEMEnergyFraction_minDR_vetoJet[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetNeutralEMEnergyFraction_minDR_vetoJet_%s",years[itr_year]);
    h_jetNeutralEMEnergyFraction_minDR_vetoJet[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetChargedHadronEnergyFraction_minDR_vetoJet_%s",years[itr_year]);
    h_jetChargedHadronEnergyFraction_minDR_vetoJet[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetNeutralHadronEnergyFraction_minDR_vetoJet_%s",years[itr_year]);
    h_jetNeutralHadronEnergyFraction_minDR_vetoJet[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetMuonEnergyFraction_minDR_vetoJet_%s",years[itr_year]);
    h_jetMuonEnergyFraction_minDR_vetoJet[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_dPhiJetMET_noRPCMatch_nRechitsLow_%s",years[itr_year]);
    h_dPhiJetMET_noRPCMatch_nRechitsLow[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMET_noRPCMatch_nRechitsHigh_%s",years[itr_year]);
    h_dPhiJetMET_noRPCMatch_nRechitsHigh[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dtRechitClusterSize_noRPCMatch_dPhiLow_%s",years[itr_year]);
    h_dtRechitClusterSize_noRPCMatch_dPhiLow[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSize_noRPCMatch_dPhiHigh_%s",years[itr_year]);
    h_dtRechitClusterSize_noRPCMatch_dPhiHigh[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nWheels1_noCluster_%s",years[itr_year]);
    h_nWheels1_noCluster[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels10_noCluster_%s",years[itr_year]);
    h_nWheels10_noCluster[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels20_noCluster_%s",years[itr_year]);
    h_nWheels20_noCluster[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels30_noCluster_%s",years[itr_year]);
    h_nWheels30_noCluster[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels50_noCluster_%s",years[itr_year]);
    h_nWheels50_noCluster[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels150_noCluster_%s",years[itr_year]);
    h_nWheels150_noCluster[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels1_noVeto_%s",years[itr_year]);
    h_nWheels1_noVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels1_fullVetoPlus_%s",years[itr_year]);
    h_nWheels1_fullVetoPlus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels1_fullVetoMinus_%s",years[itr_year]);
    h_nWheels1_fullVetoMinus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels10_noVeto_%s",years[itr_year]);
    h_nWheels10_noVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels10_fullVetoPlus_%s",years[itr_year]);
    h_nWheels10_fullVetoPlus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels10_fullVetoMinus_%s",years[itr_year]);
    h_nWheels10_fullVetoMinus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels20_noVeto_%s",years[itr_year]);
    h_nWheels20_noVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels20_fullVetoPlus_%s",years[itr_year]);
    h_nWheels20_fullVetoPlus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels20_fullVetoMinus_%s",years[itr_year]);
    h_nWheels20_fullVetoMinus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels30_noVeto_%s",years[itr_year]);
    h_nWheels30_noVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels30_fullVetoPlus_%s",years[itr_year]);
    h_nWheels30_fullVetoPlus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels30_fullVetoMinus_%s",years[itr_year]);
    h_nWheels30_fullVetoMinus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels50_noVeto_%s",years[itr_year]);
    h_nWheels50_noVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels50_fullVetoPlus_%s",years[itr_year]);
    h_nWheels50_fullVetoPlus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels50_fullVetoMinus_%s",years[itr_year]);
    h_nWheels50_fullVetoMinus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels150_noVeto_%s",years[itr_year]);
    h_nWheels150_noVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels150_fullVetoPlus_%s",years[itr_year]);
    h_nWheels150_fullVetoPlus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels150_fullVetoMinus_%s",years[itr_year]);
    h_nWheels150_fullVetoMinus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_jetPtMax_noVeto_%s",years[itr_year]);
    h_jetPtMax_noVeto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetPtMax_fullVeto_%s",years[itr_year]);
    h_jetPtMax_fullVeto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetPtMax_fullVetoPlus_%s",years[itr_year]);
    h_jetPtMax_fullVetoPlus[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetPtMax_fullVetoMinus_%s",years[itr_year]);
    h_jetPtMax_fullVetoMinus[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetPtMET_noVeto_%s",years[itr_year]);
    h_jetPtMET_noVeto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetPtMET_fullVeto_%s",years[itr_year]);
    h_jetPtMET_fullVeto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetPtMET_fullVetoPlus_%s",years[itr_year]);
    h_jetPtMET_fullVetoPlus[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetPtMET_fullVetoMinus_%s",years[itr_year]);
    h_jetPtMET_fullVetoMinus[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetPtMET_noVeto_rpcCR_%s",years[itr_year]);
    h_jetPtMET_noVeto_rpcCR[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetPtMET_fullVeto_rpcCR_%s",years[itr_year]);
    h_jetPtMET_fullVeto_rpcCR[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetPtMET_fullVetoPlus_rpcCR_%s",years[itr_year]);
    h_jetPtMET_fullVetoPlus_rpcCR[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_dtRechitClusterPhiStation2_fullVeto_rpcCR_%s",years[itr_year]);
    h_dtRechitClusterPhiStation2_fullVeto_rpcCR[itr_file] = new TH1D(name,"",70,-3.5,3.5);

    sprintf(name,"h_dtRechitClusterPhiStation3_fullVeto_rpcCR_%s",years[itr_year]);
    h_dtRechitClusterPhiStation3_fullVeto_rpcCR[itr_file] = new TH1D(name,"",70,-3.5,3.5);

    sprintf(name,"h_dtRechitClusterPhiStation4_fullVeto_rpcCR_%s",years[itr_year]);
    h_dtRechitClusterPhiStation4_fullVeto_rpcCR[itr_file] = new TH1D(name,"",70,-3.5,3.5);

    TFile *_file;
    if(strcmp(years[itr_year],"All")==0){
      _file = TFile::Open(dir+years[itr_year]+"/v4/v4/normalized/Run2_displacedJetMuonNtupler_V1p15_Data2016_Data2017_Data2018-HighMET_goodLumi.root");
    }
    else{
      _file = TFile::Open(dir+years[itr_year]+"/v5/normalized/Run2_displacedJetMuonNtupler_V1p15_Data"+years[itr_year]+"_"+runNames[itr_year]+"-HighMET-"+dates[itr_year]+"_goodLumi.root");
    }

    TTreeReader treeReader("MuonSystem",_file);

    TTreeReaderValue<unsigned int> runNum(treeReader,"runNum");
    TTreeReaderValue<unsigned int> lumiSec(treeReader,"lumiSec");
    TTreeReaderValue<unsigned int> eventNum(treeReader,"evtNum");
    TTreeReaderValue<unsigned int> npv(treeReader,"npv");
    TTreeReaderValue<float> MET(treeReader,"met");
    TTreeReaderValue<float> METphi(treeReader,"metPhi");
    TTreeReaderValue<float> jetMet_dPhiMin4(treeReader,"jetMet_dPhiMin4");

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
    TTreeReaderArray<float> jetChargedEMEnergyFraction(treeReader,"jetChargedEMEnergyFraction");
    TTreeReaderArray<float> jetNeutralEMEnergyFraction(treeReader,"jetNeutralEMEnergyFraction");
    TTreeReaderArray<float> jetNeutralHadronEnergyFraction(treeReader,"jetNeutralHadronEnergyFraction");
    TTreeReaderArray<float> jetChargedHadronEnergyFraction(treeReader,"jetChargedHadronEnergyFraction");
    //TTreeReaderArray<float> jetMuonEnergyFraction(treeReader,"jetMuonEnergyFraction");

    TTreeReaderValue<int> nLeptons(treeReader,"nLeptons");
    TTreeReaderArray<bool> lepPassLooseIso(treeReader,"lepPassLooseIso");
    TTreeReaderValue<int> nMuons(treeReader,"nMuons");
    TTreeReaderArray<float> muonEta(treeReader,"muonEta");
    TTreeReaderArray<float> muonPhi(treeReader,"muonPhi");
    TTreeReaderArray<float> muonPt(treeReader,"muonPt");

    TTreeReaderValue<int> nRPCRechits(treeReader,"nRpc");
    TTreeReaderArray<float> RPCRechitX(treeReader,"rpcX");
    TTreeReaderArray<float> RPCRechitY(treeReader,"rpcY");
    TTreeReaderArray<float> RPCRechitZ(treeReader,"rpcZ");
    TTreeReaderArray<float> RPCRechitPhi(treeReader,"rpcPhi");
    TTreeReaderArray<int> RPCRechitBx(treeReader,"rpcBx");

    TTreeReaderValue<int> nHORechits(treeReader,"nHORechits");
    TTreeReaderArray<float> HORechitE(treeReader,"hoRechit_E");
    TTreeReaderArray<float> HORechitT(treeReader,"hoRechit_T");
    TTreeReaderArray<float> HORechitEta(treeReader,"hoRechit_Eta");
    TTreeReaderArray<float> HORechitPhi(treeReader,"hoRechit_Phi");

    _ofile->cd();
    evtNum = 0;
    cout << "Data" << years[itr_year] << endl;
    while(treeReader.Next()){
      fill_n(rechitCount, 5, 0);
      hitWheels1 = 0;
      hitWheels10 = 0;
      hitWheels20 = 0;
      hitWheels30 = 0;
      hitWheels50 = 0;
      hitWheels150 = 0;
      goodEvt = false;
      clustSizeMax = 0.;
      failJetMET = false;
      failJetMET_20 = false;
      failJetMET_30 = false;
      failJetMET_50 = false;
      failJetMET_top4 = false;
      dPhi_min = 999.;
      dPhi_minTop4 = 999.;
      dPhi_min20 = 999.;
      dPhi_min30 = 999.;
      dPhi_min50 = 999.;
      jetPt_tmp = 0.0;
      nPassMuon = 0;
      nPassJet = 0;
      nPassJetMuon = 0;
      nPassMB1 = 0;
      nPassHO = 0;
      nPassFull = 0;
      nPassFullPlus = 0;
      nPassFullMinus = 0;
      //nPassFullHO = 0;
      nPassNone = 0;
      totalSumE = 0.0;
      totalClusteredNone = 0;
      totalClusteredJet = 0;
      totalClusteredMB1 = 0;
      totalClusteredNoMB1 = 0;
      totalClusteredHO = 0;
      totalClusteredFull = 0;
      totalClusteredFullHO = 0;
      totalClusteredFullPlus = 0;
      totalClusteredFullHOPlus = 0;
      if(evtNum%100000==0){ cout << evtNum << " of " << treeReader.GetEntries(1) << endl; }

      if(*MET > 200){
	nPassMET+=1;
	h_jetMet_dPhiMin4[itr_file]->Fill(*jetMet_dPhiMin4);
	dPhiClusterMET_max = -1.;
	for(Int_t itr_clust = 0; itr_clust<*nDtRechitClusters; itr_clust++){
	  dPhiClusterMET = dtRechitClusterPhi[itr_clust] - *METphi;
	  if(dPhiClusterMET > TMath::Pi()){ dPhiClusterMET -= 2*TMath::Pi(); }
	  if(dPhiClusterMET < -1.0*TMath::Pi()){ dPhiClusterMET += 2*TMath::Pi(); }
	  if(fabs(dPhiClusterMET)>dPhiClusterMET_max){ dPhiClusterMET_max=fabs(dPhiClusterMET); }
	}
	if(*nJets>0){
	  goodJets=0;
	  for(Int_t itr_jet = 0; itr_jet<*nJets; itr_jet++){
	    if(fabs(jetEta[itr_jet])<3.0){
	      dPhi_tmp = jetPhi[itr_jet] - *METphi;
	      if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
	      if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
	      if(fabs(dPhi_tmp) < dPhi_min){
		dPhi_min = fabs(dPhi_tmp);
		jetPt_tmp = jetPt[itr_jet];
		if(goodJets<4){ dPhi_minTop4 = fabs(dPhi_tmp); }
		if(jetPt[itr_jet]>50.0){ dPhi_min50 = fabs(dPhi_tmp); }
		if(jetPt[itr_jet]>30.0){ dPhi_min30 = fabs(dPhi_tmp); }
		if(jetPt[itr_jet]>20.0){ dPhi_min20 = fabs(dPhi_tmp); }
	      }
	      goodJets+=1;
	      //if(goodJets==4){ break; }
	    }
	  }
	}
	if(fabs(dPhi_min)>0.6 && fabs(dPhi_min)<999.){ failJetMET += true; }
	if(fabs(dPhi_minTop4)>0.6 && fabs(dPhi_minTop4)<999.){ failJetMET_top4 += true; }
	if(fabs(dPhi_min50)>0.6 && fabs(dPhi_min50)<999.){ failJetMET_50 += true; }
	if(fabs(dPhi_min30)>0.6 && fabs(dPhi_min30)<999.){ failJetMET_30 += true; }
	if(fabs(dPhi_min20)>0.6 && fabs(dPhi_min20)<999.){ failJetMET_20 += true; }

	dPhi_min=dPhi_minTop4;
	if(dPhi_min!=999.){ h_dPhiJetMET[itr_file]->Fill(fabs(dPhi_min)); }
	if(fabs(dPhi_min)<0.6){
	  //if(fabs(dPhiClusterMET_max)>1.0){
	  nPassJetMET+=1;
	  h_MET[itr_file]->Fill(*MET);
	  h_jetPt[itr_file]->Fill(jetPt_tmp);
	  //cout << "starting counting";
	  //for(int i=0; i<sizeof(rechitCount)/sizeof(rechitCount[0]); i++){
	  //  cout << " " << rechitCount[i];
	  //}
	  //cout << " " << *nDtRechits << endl;
	  if(*nDtRechits<750){
	    for(Int_t itr_dt = 0; itr_dt<*nDtRechits; itr_dt++){
	      rechitWheel = getWheel(dtRechitZ[itr_dt]);
	      rechitWheel+=2;
	      if(rechitWheel>=0 && rechitWheel<5){
		rechitCount[rechitWheel] += 1;
	      }
	    }
	  }
	  else{
	    fill_n(rechitCount, 5, 150);
	  }
	  //cout << "done counting";
	  //for(int i=0; i<sizeof(rechitCount)/sizeof(rechitCount[0]); i++){
	  //  cout << " " << rechitCount[i];
	  //}
	  //cout << " " << *nDtRechits << endl;
	  for(Int_t itr_wheel = 0; itr_wheel<5; itr_wheel++){
	    if(rechitCount[itr_wheel] > 0){ hitWheels1 += 1; }
	    if(rechitCount[itr_wheel] > 9){ hitWheels10 += 1; }
	    if(rechitCount[itr_wheel] > 19){ hitWheels20 += 1; }
	    if(rechitCount[itr_wheel] > 29){ hitWheels30 += 1; }
	    if(rechitCount[itr_wheel] > 49){ hitWheels50 += 1; }
	    if(rechitCount[itr_wheel] > 149){ hitWheels150 += 1; }
	  }
	  h_nWheels1_noCluster[itr_file]->Fill(hitWheels1);
	  h_nWheels10_noCluster[itr_file]->Fill(hitWheels10);
	  h_nWheels20_noCluster[itr_file]->Fill(hitWheels20);
	  h_nWheels30_noCluster[itr_file]->Fill(hitWheels30);
	  h_nWheels50_noCluster[itr_file]->Fill(hitWheels50);
	  h_nWheels150_noCluster[itr_file]->Fill(hitWheels150);

	  for(Int_t itr_clust = 0; itr_clust<*nDtRechitClusters; itr_clust++){
	    match = 0;
	    matchLayer1 = 0;
	    matchLayer2 = 0;
	    matchLayer3 = 0;
	    matchLayer4 = 0;
	    fill_n(stationCount, 4, 0);
	    nStationUnclustered = 0;
	    nThreshStation = 0;
	    nThreshLowStation = 0;
	    nThreshStationUnclustered = 0;
	    nThreshLowStationUnclustered = 0;
	    matchHO = 0;
	    sumE = 0.0;
	    weightT = 0.0;
	    rpcBx.clear();
	    rpcLayer.clear();
	    matchJet = false;
	    matchMuon = false;
	    goodEvt = true;
	    passMuon = false;
	    passJet = false;
	    passMB1 = false;
	    passMB1_alt = false;
	    passMuon_alt = false;
	    passHO = false;
	    passInvertedJet = false;
	    passInvertedMuon = false;
	    passInvertedMuJet = false;

	    dPhiClusterMET = dtRechitClusterPhi[itr_clust] - *METphi;
	    if(dPhiClusterMET > TMath::Pi()){ dPhiClusterMET -= 2*TMath::Pi(); }
	    if(dPhiClusterMET < -1.0*TMath::Pi()){ dPhiClusterMET += 2*TMath::Pi(); }

	    /*passJet = true;
	    for(Int_t itr_jet = 0; itr_jet<*nJets; itr_jet++){
	      if(jetPt[itr_jet]>20.){
		dPhi_tmp = RPCRechitPhi[itr_jet] - dtRechitClusterPhi[itr_clust];
		if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
		if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
		if(sqrt(pow(dPhi_tmp,2)+pow(jetEta[itr_jet]-dtRechitClusterEta[itr_clust],2))<0.5){
		  passJet = false;
		  break;
		}
	      }
	    }
	    if(!passJet){ passInvertedJet = true; }
	    */
	    if(dtRechitClusterJetVetoPt[itr_clust]<20.){ passJet = true; }
	    else{ passInvertedJet = true; }
	    if(dtRechitClusterMuonVetoPt[itr_clust]<10.){ passMuon = true; }
	    else{ passInvertedMuon = true; }
	    if(dtRechitClusterNSegmentStation1[itr_clust]==0){ passMB1 = true; }

	    passMB1_alt = true;
	    for(Int_t itr_dt = 0; itr_dt<*nDtRechits; itr_dt++){
	      if(sqrt(pow(dtRechitX[itr_dt],2)+pow(dtRechitY[itr_dt],2))>400. && sqrt(pow(dtRechitX[itr_dt],2)+pow(dtRechitY[itr_dt],2))<480.){
		dPhi_tmp = dtRechitPhi[itr_dt] - dtRechitClusterPhi[itr_clust];
		if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
		if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
		if(sqrt(pow(dPhi_tmp,2)+pow(dtRechitEta[itr_dt]-dtRechitClusterEta[itr_clust],2))<0.4){
		  passMB1_alt = false;
		  break;
		}
	      }
	    }
	    passMuon_alt = true;
	    for(Int_t itr_lep = 0; itr_lep<*nLeptons; itr_lep++){
	      if(lepPassLooseIso[itr_lep]){
		passMuon_alt = false;
		break;
	      }
	    }
	    //if(*nLeptons==0){ passMuon_alt = true; }

	    if(dtRechitClusterSize[itr_clust]>50 && ((dtRechitClusterPhi[itr_clust]<0.4 || dtRechitClusterPhi[itr_clust]>0.6) || (*runNum<275.75e3 || *runNum>275.95e3))){

	      nPassNone+=1;
	      totalClusteredNone+=dtRechitClusterSize[itr_clust];

	      for(Int_t itr_rpc=0; itr_rpc<*nRPCRechits; itr_rpc++){
		dPhi_tmp = RPCRechitPhi[itr_rpc] - dtRechitClusterPhi[itr_clust];
		if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
		if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
		if(fabs(RPCRechitZ[itr_rpc] - dtRechitClusterZ[itr_clust])<5. && fabs(dPhi_tmp)<0.4){
		  match+=1;
		  rpcBx.push_back(RPCRechitBx[itr_rpc]);
		  rpcLayer.push_back(getRPCLayer(RPCRechitX[itr_rpc],RPCRechitY[itr_rpc]));
		}
	      }
	      if(!rpcLayer.empty()){
		for(Int_t itr = 0; itr<rpcLayer.size(); itr++){
		  if(rpcLayer[itr]==1 || rpcLayer[itr]==2){ matchLayer1+=1; }
		  else if(rpcLayer[itr]==3 || rpcLayer[itr]==4){ matchLayer2+=1; }
		  else if(rpcLayer[itr]==5){ matchLayer3+=1; }
		  else if(rpcLayer[itr]==6){ matchLayer4+=1; }
		}
	      }

	      if(dtRechitClusterNSegmentStation2[itr_clust]>12){ nThreshStation+=1; }
	      if(dtRechitClusterNSegmentStation3[itr_clust]>12){ nThreshStation+=1; }
	      if(dtRechitClusterNSegmentStation4[itr_clust]>8){ nThreshStation+=1; }

	      if(dtRechitClusterNSegmentStation2[itr_clust]>4){ nThreshLowStation+=1; }
	      if(dtRechitClusterNSegmentStation3[itr_clust]>4){ nThreshLowStation+=1; }
	      if(dtRechitClusterNSegmentStation4[itr_clust]>2){ nThreshLowStation+=1; }

	      for(Int_t itr_ho = 0; itr_ho<*nHORechits; itr_ho++){
		dPhi_tmp = HORechitPhi[itr_ho] - dtRechitClusterPhi[itr_clust];
		if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
		if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
		if(sqrt(pow(dPhi_tmp,2)+pow(HORechitEta[itr_ho]-dtRechitClusterEta[itr_clust],2))<0.5){
		  matchHO+=1;
		  sumE += HORechitE[itr_ho];
		  weightT += HORechitT[itr_ho]*HORechitE[itr_ho];
		}
	      }
	      if(passJet){
		h_HOEnergy_jetVeto[itr_file]->Fill(sumE);
	      }
	      if(sumE>40.){ passHO = true; }

	      muonPt_max = 0.0;
	      muonDR_min = 999.0;
	      for(Int_t itr=0; itr<*nMuons; itr++){
		dPhi_tmp = muonPhi[itr] - dtRechitClusterPhi[itr_clust];
		if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
		if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
		if(sqrt(pow(dPhi_tmp,2)+pow(muonEta[itr]-dtRechitClusterEta[itr_clust],2))<0.4){
		  if(muonPt[itr]>muonPt_max){
		    muonPt_max=muonPt[itr];
		  }
		}
		if(muonPt[itr]>10.&&sqrt(pow(dPhi_tmp,2)+pow(muonEta[itr]-dtRechitClusterEta[itr_clust],2))<muonDR_min){
		  muonDR_min=sqrt(pow(dPhi_tmp,2)+pow(muonEta[itr]-dtRechitClusterEta[itr_clust],2));
		}
	      }

	      jetPt_max = 0.0;
	      jetDR_min = 999.0;
	      for(Int_t itr=0; itr<*nJets; itr++){
		dPhi_tmp = jetPhi[itr] - dtRechitClusterPhi[itr_clust];
		if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
		if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
		if(sqrt(pow(dPhi_tmp,2)+pow(jetEta[itr]-dtRechitClusterEta[itr_clust],2))<0.4){
		  if(jetPt[itr]>jetPt_max){
		    jetPt_max=jetPt[itr];
		  }
		}
		if(jetPt[itr]>20.&&sqrt(pow(dPhi_tmp,2)+pow(jetEta[itr]-dtRechitClusterEta[itr_clust],2))<jetDR_min){
		  jetDR_min=sqrt(pow(dPhi_tmp,2)+pow(jetEta[itr]-dtRechitClusterEta[itr_clust],2));
		  jetDR_index = itr;
		}
		if(sqrt(pow(dPhi_tmp,2)+pow(jetEta[itr]-dtRechitClusterEta[itr_clust],2))<0.4){
		  h_jetDR_minDR_vetoJet[itr_file]->Fill(sqrt(pow(dPhi_tmp,2)+pow(jetEta[itr]-dtRechitClusterEta[itr_clust],2)));
		  h_jetPt_minDR_vetoJet[itr_file]->Fill(jetPt[itr]);
		  h_jetEta_minDR_vetoJet[itr_file]->Fill(jetEta[itr]);
		  h_jetPhi_minDR_vetoJet[itr_file]->Fill(jetPhi[itr]);
		  h_jetChargedEMEnergyFraction_minDR_vetoJet[itr_file]->Fill(jetChargedEMEnergyFraction[itr]);
		  h_jetNeutralEMEnergyFraction_minDR_vetoJet[itr_file]->Fill(jetNeutralEMEnergyFraction[itr]);
		  h_jetChargedHadronEnergyFraction_minDR_vetoJet[itr_file]->Fill(jetChargedHadronEnergyFraction[itr]);
		  h_jetNeutralHadronEnergyFraction_minDR_vetoJet[itr_file]->Fill(jetNeutralHadronEnergyFraction[itr]);
		  //h_jetMuonEnergyFraction_minDR_vetoJet[itr_file]->Fill(jetMuonEnergyFraction[itr]);
		}
	      }

	      h_dtRechitClusterSize_noVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
	      h_dtRechitClusterMaxStation_noVeto[itr_file]->Fill(dtRechitClusterMaxStation[itr_clust]);
	      h_dtRechitClusterNStation_noVeto[itr_file]->Fill(dtRechitClusterNStation[itr_clust]);
	      h_dPhiClusterMET_noVeto[itr_file]->Fill(fabs(dPhiClusterMET));
	      h_dtRechitClusterXSpread_noVeto[itr_file]->Fill(dtRechitClusterXSpread[itr_clust]);
	      h_dtRechitClusterYSpread_noVeto[itr_file]->Fill(dtRechitClusterYSpread[itr_clust]);
	      h_dtRechitClusterZSpread_noVeto[itr_file]->Fill(dtRechitClusterZSpread[itr_clust]);
	      h_dtRechitClusterEtaSpread_noVeto[itr_file]->Fill(dtRechitClusterEtaSpread[itr_clust]);
	      h_dtRechitClusterPhiSpread_noVeto[itr_file]->Fill(dtRechitClusterPhiSpread[itr_clust]);
	      h_nRPCMatched_noVeto[itr_file]->Fill(match);
	      if(!rpcBx.empty()){
		rpcSpread = max_element(rpcBx.begin(), rpcBx.end()) - min_element(rpcBx.begin(), rpcBx.end());
		for(Int_t itr = 0; itr<rpcBx.size(); itr++){
		  h_RPCMatchedBx_noVeto[itr_file]->Fill(rpcBx[itr]);
		  if(rpcSpread==0){ h_RPCMatchedBx_Spread0_noVeto[itr_file]->Fill(rpcBx[itr]); }
		}
		h_RPCMatchedBxSpread_noVeto[itr_file]->Fill(rpcSpread);
		if(rpcSpread==0){ h_nRPCMatched_Spread0_noVeto[itr_file]->Fill(match); }
	      }

	      if(passMuon){
		nPassMuon+=1;
		h_dtRechitClusterSize_muonVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		h_dtRechitClusterMaxStation_muonVeto[itr_file]->Fill(dtRechitClusterMaxStation[itr_clust]);
		h_dtRechitClusterNStation_muonVeto[itr_file]->Fill(dtRechitClusterNStation[itr_clust]);
		h_dPhiClusterMET_muonVeto[itr_file]->Fill(fabs(dPhiClusterMET));
		h_dtRechitClusterXSpread_muonVeto[itr_file]->Fill(dtRechitClusterXSpread[itr_clust]);
		h_dtRechitClusterYSpread_muonVeto[itr_file]->Fill(dtRechitClusterYSpread[itr_clust]);
		h_dtRechitClusterZSpread_muonVeto[itr_file]->Fill(dtRechitClusterZSpread[itr_clust]);
		h_dtRechitClusterEtaSpread_muonVeto[itr_file]->Fill(dtRechitClusterEtaSpread[itr_clust]);
		h_dtRechitClusterPhiSpread_muonVeto[itr_file]->Fill(dtRechitClusterPhiSpread[itr_clust]);
		h_nRPCMatched_muonVeto[itr_file]->Fill(match);
		if(!rpcBx.empty()){
		  rpcSpread = max_element(rpcBx.begin(), rpcBx.end()) - min_element(rpcBx.begin(), rpcBx.end());
		  for(Int_t itr = 0; itr<rpcBx.size(); itr++){
		    h_RPCMatchedBx_muonVeto[itr_file]->Fill(rpcBx[itr]);
		    if(rpcSpread==0){ h_RPCMatchedBx_Spread0_muonVeto[itr_file]->Fill(rpcBx[itr]); }
		  }
		  h_RPCMatchedBxSpread_muonVeto[itr_file]->Fill(rpcSpread);
		  if(rpcSpread==0){ h_nRPCMatched_Spread0_muonVeto[itr_file]->Fill(match); }
		}
	      }

	      if(passJet){
		nPassJet+=1;
		totalClusteredJet+=dtRechitClusterSize[itr_clust];
		h_dtRechitClusterSize_jetVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		h_dtRechitClusterMaxStation_jetVeto[itr_file]->Fill(dtRechitClusterMaxStation[itr_clust]);
		h_dtRechitClusterNStation_jetVeto[itr_file]->Fill(dtRechitClusterNStation[itr_clust]);
		h_dPhiClusterMET_jetVeto[itr_file]->Fill(fabs(dPhiClusterMET));
		h_dtRechitClusterXSpread_jetVeto[itr_file]->Fill(dtRechitClusterXSpread[itr_clust]);
		h_dtRechitClusterYSpread_jetVeto[itr_file]->Fill(dtRechitClusterYSpread[itr_clust]);
		h_dtRechitClusterZSpread_jetVeto[itr_file]->Fill(dtRechitClusterZSpread[itr_clust]);
		h_dtRechitClusterEtaSpread_jetVeto[itr_file]->Fill(dtRechitClusterEtaSpread[itr_clust]);
		h_dtRechitClusterPhiSpread_jetVeto[itr_file]->Fill(dtRechitClusterPhiSpread[itr_clust]);
		h_nRPCMatched_jetVeto[itr_file]->Fill(match);

		h_nRPCMatchedLayer1_jetVeto[itr_file]->Fill(matchLayer1);
		h_nRPCMatchedLayer2_jetVeto[itr_file]->Fill(matchLayer2);
		h_nRPCMatchedLayer3_jetVeto[itr_file]->Fill(matchLayer3);
		h_nRPCMatchedLayer4_jetVeto[itr_file]->Fill(matchLayer4);

		if(!rpcBx.empty()){
		  rpcSpread = max_element(rpcBx.begin(), rpcBx.end()) - min_element(rpcBx.begin(), rpcBx.end());
		  for(Int_t itr = 0; itr<rpcBx.size(); itr++){
		    h_RPCMatchedBx_jetVeto[itr_file]->Fill(rpcBx[itr]);
		    if(rpcSpread==0){ h_RPCMatchedBx_Spread0_jetVeto[itr_file]->Fill(rpcBx[itr]); }
		  }
		  h_RPCMatchedBxSpread_jetVeto[itr_file]->Fill(rpcSpread);
		  if(rpcSpread==0){ h_nRPCMatched_Spread0_jetVeto[itr_file]->Fill(match); }
		}
	      }

	      if(passMB1){
		nPassMB1+=1;
		totalClusteredMB1+=dtRechitClusterSize[itr_clust];
		h_dtRechitClusterSize_MB1Veto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		h_dtRechitClusterMaxStation_MB1Veto[itr_file]->Fill(dtRechitClusterMaxStation[itr_clust]);
		h_dtRechitClusterNStation_MB1Veto[itr_file]->Fill(dtRechitClusterNStation[itr_clust]);
		h_dPhiClusterMET_MB1Veto[itr_file]->Fill(fabs(dPhiClusterMET));
		h_dtRechitClusterXSpread_MB1Veto[itr_file]->Fill(dtRechitClusterXSpread[itr_clust]);
		h_dtRechitClusterYSpread_MB1Veto[itr_file]->Fill(dtRechitClusterYSpread[itr_clust]);
		h_dtRechitClusterZSpread_MB1Veto[itr_file]->Fill(dtRechitClusterZSpread[itr_clust]);
		h_dtRechitClusterEtaSpread_MB1Veto[itr_file]->Fill(dtRechitClusterEtaSpread[itr_clust]);
		h_dtRechitClusterPhiSpread_MB1Veto[itr_file]->Fill(dtRechitClusterPhiSpread[itr_clust]);
		h_nRPCMatched_MB1Veto[itr_file]->Fill(match);
		if(!rpcBx.empty()){
		  rpcSpread = max_element(rpcBx.begin(), rpcBx.end()) - min_element(rpcBx.begin(), rpcBx.end());
		  for(Int_t itr = 0; itr<rpcBx.size(); itr++){
		    h_RPCMatchedBx_MB1Veto[itr_file]->Fill(rpcBx[itr]);
		    if(rpcSpread==0){ h_RPCMatchedBx_Spread0_MB1Veto[itr_file]->Fill(rpcBx[itr]); }
		  }
		  h_RPCMatchedBxSpread_MB1Veto[itr_file]->Fill(rpcSpread);
		  if(rpcSpread==0){ h_nRPCMatched_Spread0_MB1Veto[itr_file]->Fill(match); }
		}
	      }

	      /*	      if(!passMB1){
		if(!rpcBx.empty()){
		  if(rpcBx.size()%2 == 0){ rpcMedian = float(rpcBx[rpcBx.size()/2 - 1] + rpcBx[rpcBx.size()/2]) / 2.0; }
		  else{ rpcMedian = rpcBx[rpcBx.size()/2]; }
		}
		h_nHOMatched_noMB1Veto[itr_file]->Fill(matchHO);
		if(sumE>20.){
		  h_HOMatchedEnergy_noMB1Veto[itr_file]->Fill(sumE);
		  h_HOMatchedTime_noMB1Veto[itr_file]->Fill(weightT/sumE);
		  if(!rpcBx.empty()){
		    h_HOMatchedTime_RPCMatchedBx_noMB1Veto[itr_file]->Fill(weightT/sumE,rpcMedian);
		  }
		}
		}*/

	      if(passInvertedJet && !passMB1){
		if(!rpcBx.empty()){
		  if(rpcBx.size()%2 == 0){ rpcMedian = float(rpcBx[rpcBx.size()/2 - 1] + rpcBx[rpcBx.size()/2]) / 2.0; }
		  else{ rpcMedian = rpcBx[rpcBx.size()/2]; }
		}
		h_nHOMatched_invertedJet_noMB1Veto[itr_file]->Fill(matchHO);
		if(sumE>20.){
		  h_HOMatchedEnergy_invertedJet_noMB1Veto[itr_file]->Fill(sumE);
		  h_HOMatchedTime_invertedJet_noMB1Veto[itr_file]->Fill(weightT/sumE);
		  if(!rpcBx.empty()){
		    h_HOMatchedTime_RPCMatchedBx_invertedJet_noMB1Veto[itr_file]->Fill(weightT/sumE,rpcMedian);
		  }
		}
	      }

	      if(passInvertedJet && passMB1){
		if(!rpcBx.empty()){
		  if(rpcBx.size()%2 == 0){ rpcMedian = float(rpcBx[rpcBx.size()/2 - 1] + rpcBx[rpcBx.size()/2]) / 2.0; }
		  else{ rpcMedian = rpcBx[rpcBx.size()/2]; }
		  for(Int_t itr = 0; itr<rpcBx.size(); itr++){
		    h_RPCMatchedBx_invertedJetVeto[itr_file]->Fill(rpcBx[itr]);
		  }
		}
		h_nHOMatched_invertedJetVeto[itr_file]->Fill(matchHO);
		if(sumE>20.){
		  h_HOMatchedEnergy_invertedJetVeto[itr_file]->Fill(sumE);
		  h_HOMatchedTime_invertedJetVeto[itr_file]->Fill(weightT/sumE);
		  if(!rpcBx.empty()){
		    h_HOMatchedTime_RPCMatchedBx_invertedJetVeto[itr_file]->Fill(weightT/sumE,rpcMedian);
		  }
		}
	      }

	      if(passInvertedMuon && passMB1){
		if(!rpcBx.empty()){
		  for(Int_t itr = 0; itr<rpcBx.size(); itr++){
		    h_RPCMatchedBx_invertedMuonVeto[itr_file]->Fill(rpcBx[itr]);
		  }
		}
	      }

	      if(passInvertedMuon && passInvertedJet && passMB1){
		if(!rpcBx.empty()){
		  for(Int_t itr = 0; itr<rpcBx.size(); itr++){
		    h_RPCMatchedBx_invertedMuJetVeto[itr_file]->Fill(rpcBx[itr]);
		  }
		}
	      }

	      if(passMuon && passJet){
		nPassJetMuon+=1;
		totalClusteredNoMB1+=dtRechitClusterSize[itr_clust];
		h_dtRechitClusterSize_noMB1Veto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		h_dtRechitClusterNRechitsMB1_noMB1Veto[itr_file]->Fill(dtRechitClusterNSegmentStation1[itr_clust]);
		h_dtRechitClusterPercentRechitsMB1_noMB1Veto[itr_file]->Fill(float(dtRechitClusterNSegmentStation1[itr_clust]) / dtRechitClusterSize[itr_clust]);
		h_dtRechitClusterNStation_noMB1Veto[itr_file]->Fill(dtRechitClusterNStation[itr_clust]);
		h_MB1Rechits_jetMuonVeto[itr_file]->Fill(dtRechitClusterNSegmentStation1[itr_clust]);
		h_HOEnergy_jetMuonVeto[itr_file]->Fill(sumE);
		h_nRPCMatched_noMB1Veto[itr_file]->Fill(match);
		if(!rpcLayer.empty()){
		  h_RPCMatchedBxSpread_noMB1Veto[itr_file]->Fill(max_element(rpcBx.begin(),rpcBx.end()) - min_element(rpcBx.begin(),rpcBx.end()));
		  for(Int_t itr = 0; itr<rpcLayer.size(); itr++){
		    if(rpcLayer[itr]==1){ matchLayer1+=1; }
		    else if(rpcLayer[itr]==2){ matchLayer2+=1; }
		  }
		}
		h_nRPCMatchedLayer1_noMB1Veto[itr_file]->Fill(matchLayer1);
		h_nRPCMatchedLayer2_noMB1Veto[itr_file]->Fill(matchLayer2);
		h_nRPCMatchedLayer12_noMB1Veto[itr_file]->Fill(matchLayer1+matchLayer2);
		if(dtRechitClusterSize[itr_clust]>=280){
		  totalSumE+=sumE;
		}
	      }

	      if(passMuon && passJet && passMB1){
		nPassFull+=1;

		if(*nDtRechits<1000){
		  for(Int_t itr_dt = 0; itr_dt<*nDtRechits; itr_dt++){
		    dPhi_tmp = dtRechitPhi[itr_dt] - dtRechitClusterPhi[itr_clust];
		    if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
		    if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
		    if(sqrt(pow(dPhi_tmp,2)+pow(dtRechitEta[itr_dt]-dtRechitClusterEta[itr_clust],2))<0.5){
		      rechitStation = getStation(dtRechitX[itr_dt],dtRechitY[itr_dt]);
		      if(rechitStation>-1){
			stationCount[rechitStation-1] += 1;
		      }
		    }
		  }
		}
		else{
		  fill_n(stationCount, 4, 150);
		}
		for(Int_t itr_station=0; itr_station<4; itr_station++){
		  if(stationCount[itr_station]>0){ nStationUnclustered+=1; }
		  if(itr_station<3){
		    if(stationCount[itr_station]>12){ nThreshStationUnclustered+=1; }
		    if(stationCount[itr_station]>4){ nThreshLowStationUnclustered+=1; }
		  }
		  else{
		    if(stationCount[itr_station]>8){ nThreshStationUnclustered+=1; }
		    if(stationCount[itr_station]>2){ nThreshLowStationUnclustered+=1; }
		  }
		}

		totalClusteredFull+=dtRechitClusterSize[itr_clust];
		h_dtRechitClusterSize_fullVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		h_dtRechitClusterMaxStation_fullVeto[itr_file]->Fill(dtRechitClusterMaxStation[itr_clust]);
		h_dtRechitClusterNStation_fullVeto[itr_file]->Fill(dtRechitClusterNStation[itr_clust]);
		h_dtRechitClusterNThreshStation_fullVeto[itr_file]->Fill(nThreshStation);

		h_dtRechitClusterNStation_fullVeto[itr_file]->Fill(dtRechitClusterNStation[itr_clust]);
		h_dtRechitClusterNStationUnclustered_fullVeto[itr_file]->Fill(nStationUnclustered);
		h_dtRechitClusterNThreshStation_fullVeto[itr_file]->Fill(nThreshStation);
		h_dtRechitClusterNThreshLowStation_fullVeto[itr_file]->Fill(nThreshLowStation);
		h_dtRechitClusterNThreshStationUnclustered_fullVeto[itr_file]->Fill(nThreshStationUnclustered);
		h_dtRechitClusterNThreshLowStationUnclustered_fullVeto[itr_file]->Fill(nThreshLowStationUnclustered);
		h_dPhiClusterMET_fullVeto[itr_file]->Fill(fabs(dPhiClusterMET));
		h_dtRechitClusterXSpread_fullVeto[itr_file]->Fill(dtRechitClusterXSpread[itr_clust]);
		h_dtRechitClusterYSpread_fullVeto[itr_file]->Fill(dtRechitClusterYSpread[itr_clust]);
		h_dtRechitClusterZSpread_fullVeto[itr_file]->Fill(dtRechitClusterZSpread[itr_clust]);
		h_dtRechitClusterEtaSpread_fullVeto[itr_file]->Fill(dtRechitClusterEtaSpread[itr_clust]);
		h_dtRechitClusterPhiSpread_fullVeto[itr_file]->Fill(dtRechitClusterPhiSpread[itr_clust]);
		h_nRPCMatched_fullVeto[itr_file]->Fill(match);

		h_dtRechitClusterEta_fullVeto[itr_file]->Fill(dtRechitClusterEta[itr_clust]);
		h_dtRechitClusterPhi_fullVeto[itr_file]->Fill(dtRechitClusterPhi[itr_clust]);
		h_dtRechitClusterR_fullVeto[itr_file]->Fill(sqrt(pow(dtRechitClusterX[itr_clust],2)+pow(dtRechitClusterY[itr_clust],2)));
		h_dtRechitClusterZ_fullVeto[itr_file]->Fill(dtRechitClusterZ[itr_clust]);
		h_dtRechitClusterRZ_fullVeto[itr_file]->Fill(dtRechitClusterZ[itr_clust],sqrt(pow(dtRechitClusterX[itr_clust],2)+pow(dtRechitClusterY[itr_clust],2)));
		h_dtRechitClusterRZFine_fullVeto[itr_file]->Fill(dtRechitClusterZ[itr_clust],sqrt(pow(dtRechitClusterX[itr_clust],2)+pow(dtRechitClusterY[itr_clust],2)));
		h_dtRechitClusterEtaPhi_fullVeto[itr_file]->Fill(dtRechitClusterEta[itr_clust],dtRechitClusterPhi[itr_clust]);
		h_dtRechitClusterEtaPhiFine_fullVeto[itr_file]->Fill(dtRechitClusterEta[itr_clust],dtRechitClusterPhi[itr_clust]);

		if(dtRechitClusterPhi[itr_clust]>0.4 && dtRechitClusterPhi[itr_clust]<0.6){
		  h_runNum_phi->Fill(*runNum);
		  if(dtRechitClusterEta[itr_clust]>0.5 && dtRechitClusterEta[itr_clust]<0.6){
		    h_runNum_etaphi->Fill(*runNum);
		  }
		  if(*runNum>275.75e3&&*runNum<275.95e3){
		    //eventList << *runNum << ":" << *lumiSec << ":" << *eventNum << endl;
		    h_badRun_lumiSec->Fill(*lumiSec);
		    h_badRun_dtRechitClusterSize->Fill(dtRechitClusterSize[itr_clust]);
		    h_badRun_dtRechitClusterNStation->Fill(dtRechitClusterNStation[itr_clust]);
		    h_badRun_dtRechitClusterNWheel->Fill(dtRechitClusterNChamber[itr_clust]);
		    h_badRun_dtRechitClusterXSpread->Fill(dtRechitClusterXSpread[itr_clust]);
		    h_badRun_dtRechitClusterYSpread->Fill(dtRechitClusterYSpread[itr_clust]);
		    h_badRun_dtRechitClusterPhiSpread->Fill(dtRechitClusterPhiSpread[itr_clust]);
		  }
		}
		if(dtRechitClusterEta[itr_file]>0.5 && dtRechitClusterEta[itr_file]<0.6){
		  h_runNum_eta->Fill(*runNum);
		}

		h_dtRechitClusterNWheels1_fullVeto[itr_file]->Fill(dtRechitClusterNChamber[itr_clust]);
		h_dtRechitClusterMaxWheel_fullVeto[itr_file]->Fill(dtRechitClusterMaxChamber[itr_clust]);
		if(!rpcBx.empty()){
		  if(rpcBx.size()%2 == 0){ rpcMedian = float(rpcBx[rpcBx.size()/2 - 1] + rpcBx[rpcBx.size()/2]) / 2.0; }
		  else{ rpcMedian = rpcBx[rpcBx.size()/2]; }
		  rpcSpread = max_element(rpcBx.begin(), rpcBx.end()) - min_element(rpcBx.begin(), rpcBx.end());
		  for(Int_t itr = 0; itr<rpcBx.size(); itr++){
		    h_RPCMatchedBx_fullVeto[itr_file]->Fill(rpcBx[itr]);
		    if(rpcSpread==0){ h_RPCMatchedBx_Spread0_fullVeto[itr_file]->Fill(rpcBx[itr]); }
		  }
		  h_RPCMatchedBxSpread_fullVeto[itr_file]->Fill(rpcSpread);
		  if(rpcSpread==0){ h_nRPCMatched_Spread0_fullVeto[itr_file]->Fill(match); }
		}

		h_nHOMatched_fullVeto[itr_file]->Fill(matchHO);
		if(sumE>20.){
		  h_HOMatchedEnergy_fullVeto[itr_file]->Fill(sumE);
		  h_HOMatchedTime_fullVeto[itr_file]->Fill(weightT/sumE);
		  if(!rpcBx.empty()){
		    h_HOMatchedTime_RPCMatchedBx_fullVeto[itr_file]->Fill(weightT/sumE,rpcMedian);
		  }
		}

		h_muonDR_fullVeto[itr_file]->Fill(muonDR_min);
		h_jetDR_fullVeto[itr_file]->Fill(jetDR_min);

		if(!rpcBx.empty()){
		  nPassRPCMatch_dt+=1;
		  h_dtRechitClusterSize_RPCMatch[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		  h_muonDR_RPCMatch[itr_file]->Fill(muonDR_min);
		  h_jetDR_RPCMatch[itr_file]->Fill(jetDR_min);
		  if(rpcSpread==0){
		    nPassRPCSpread_dt+=1;
		    h_dtRechitClusterSize_RPCSpread0[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		    h_muonDR_RPCSpread0[itr_file]->Fill(muonDR_min);
		    h_jetDR_RPCSpread0[itr_file]->Fill(jetDR_min);
		    if(dtRechitClusterMaxStation[itr_clust]>2){
		      nPassMaxStation_dt+=1;
		      if(fabs(dPhiClusterMET)<1 && fabs(dPhi_min)<0.6){
			nPassFullPlus+=1;
			nPassDeltaPhi_dt+=1;
			totalClusteredFullPlus+=dtRechitClusterSize[itr_clust];
			h_dtRechitClusterXSpread_fullVetoPlus[itr_file]->Fill(dtRechitClusterXSpread[itr_clust]);
			h_dtRechitClusterYSpread_fullVetoPlus[itr_file]->Fill(dtRechitClusterYSpread[itr_clust]);
			h_dtRechitClusterZSpread_fullVetoPlus[itr_file]->Fill(dtRechitClusterZSpread[itr_clust]);
			h_dtRechitClusterEtaSpread_fullVetoPlus[itr_file]->Fill(dtRechitClusterEtaSpread[itr_clust]);
			h_dtRechitClusterPhiSpread_fullVetoPlus[itr_file]->Fill(dtRechitClusterPhiSpread[itr_clust]);
			h_dtRechitClusterSizeRatio_fullVetoPlus[itr_file]->Fill(dtRechitClusterSize[itr_clust] / float(*nDtRechits));
			//cout << "DT decay: jet DR = " << jetDR_min << ", muon DR = " << muonDR_min << endl;
			//eventList << *runNum << ":" << *lumiSec << ":" << *eventNum << endl;
		      }
		    }
		  }
		}
		else{
		  if(fabs(dPhi_min)<0.6){
		    h_dtRechitClusterSize_noRPCMatch_dPhiLow[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		  }
		  else{
		    h_dtRechitClusterSize_noRPCMatch_dPhiHigh[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		  }
		  if(dtRechitClusterSize[itr_clust]<100){
		    h_dPhiJetMET_noRPCMatch_nRechitsLow[itr_file]->Fill(fabs(dPhi_min));
		  }
		  else{
		    h_dPhiJetMET_noRPCMatch_nRechitsHigh[itr_file]->Fill(fabs(dPhi_min));
		  }
		}

		if(dtRechitClusterMaxStation[itr_clust]>2 && fabs(dPhi_min)<0.6){
		  if(fabs(dPhiClusterMET)<1 && (rpcBx.empty() || rpcSpread>0)){
		    nPassFullMinus+=1;
		    h_dtRechitClusterEta_fullVetoPlus[itr_file]->Fill(dtRechitClusterEta[itr_clust]);
		    h_dtRechitClusterPhi_fullVetoPlus[itr_file]->Fill(dtRechitClusterPhi[itr_clust]);
		    h_dtRechitClusterEtaPhi_fullVetoPlus[itr_file]->Fill(dtRechitClusterPhi[itr_clust],dtRechitClusterEta[itr_clust]);
		    h_dtRechitClusterNStation_fullVetoPlus[itr_file]->Fill(dtRechitClusterNStation[itr_clust]);
		    h_dtRechitClusterNWheel_fullVetoPlus[itr_file]->Fill(dtRechitClusterNChamber[itr_clust]);
		    h_dtRechitClusterSizeRatio_fullVetoMinus[itr_file]->Fill(dtRechitClusterSize[itr_clust] / float(*nDtRechits));
		  }
		}

	      }

	      if(passMuon && passJet){
		nPassJetMuon_std+=1;
		if(passMB1_alt){
		  nPassFull_altMB1+=1;
		}
		if(!rpcBx.empty() && rpcSpread==0 && dtRechitClusterMaxStation[itr_clust]>2 && fabs(dPhiClusterMET)<1 && fabs(dPhi_min)<0.6){
		  nPassFullDTPlus_noMB1+=1;
		  if(passMB1_alt){
		    nPassFullDTPlus_altMB1+=1;
		  }
		}
	      }

	      if(passMB1 && passJet){
		nPassJetMB1_std+=1;
		if(passMuon_alt){
		  nPassFull_altMuon+=1;
		}
		if(!rpcBx.empty() && rpcSpread==0 && dtRechitClusterMaxStation[itr_clust]>2 && fabs(dPhiClusterMET)<1 && fabs(dPhi_min)<0.6){
		  nPassFullDTPlus_noMuon+=1;
		  if(passMuon_alt){
		    nPassFullDTPlus_altMuon+=1;
		  }
		}
	      }

	      if(passMuon_alt){
		nPassMuon_alt+=1;
		if(passJet && passMB1_alt){
		  nPassFull_altMuonMB1+=1;
		  if(!rpcBx.empty()){
		    if(rpcSpread==0){
		      if(dtRechitClusterMaxStation[itr_clust]>2){
			if(fabs(dPhiClusterMET)<1 && fabs(dPhi_min)<0.6){
			  nPassFullDTPlus_altMuonMB1+=1;
			}
		      }
		    }
		  }
		}
	      }
	      if(passMB1_alt){
		nPassMB1_alt+=1;
	      }
	      if(passMuon){
		nPassMuon_std+=1;
	      }
	      if(passMB1){
		nPassMB1_std+=1;
		if(passJet && passMuon){
		  nPassFull_std+=1;
		  if(!rpcBx.empty()){
		    if(rpcSpread==0){
		      if(dtRechitClusterMaxStation[itr_clust]>2){
			if(fabs(dPhiClusterMET)<1 && fabs(dPhi_min)<0.6){
			  nPassFullDTPlus_std+=1;
			}
		      }
		    }
		  }
		}
	      }

	      if(passHO){
		nPassHO+=1;
		totalClusteredHO+=dtRechitClusterSize[itr_clust];
		h_dtRechitClusterSize_HOVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
	      }
	      if(passJet && passMuon && passHO){
		nPassFullHO+=1;
		totalClusteredFullHO+=dtRechitClusterSize[itr_clust];
		h_dtRechitClusterSize_fullHOVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		h_dtRechitClusterMaxStation_fullHOVeto[itr_file]->Fill(dtRechitClusterMaxStation[itr_clust]);
		h_dPhiClusterMET_fullHOVeto[itr_file]->Fill(fabs(dPhiClusterMET));
		h_nRPCMatched_fullHOVeto[itr_file]->Fill(match);
		h_RPCMatchedBxSpread_fullHOVeto[itr_file]->Fill(rpcSpread);
		h_HOTime_fullHOVeto[itr_file]->Fill(weightT/sumE);

		h_muonDR_fullHOVeto[itr_file]->Fill(muonDR_min);
		h_jetDR_fullHOVeto[itr_file]->Fill(jetDR_min);

		h_nRPCMatchedLayer1_fullHOVeto[itr_file]->Fill(matchLayer1);
		h_nRPCMatchedLayer2_fullHOVeto[itr_file]->Fill(matchLayer2);
		h_nRPCMatchedLayer3_fullHOVeto[itr_file]->Fill(matchLayer3);
		h_nRPCMatchedLayer4_fullHOVeto[itr_file]->Fill(matchLayer4);

		if(!rpcBx.empty()){
		  nPassRPCMatch_ho+=1;
		  h_muonDR_HORPCMatch[itr_file]->Fill(muonDR_min);
		  h_jetDR_HORPCMatch[itr_file]->Fill(jetDR_min);
		  if(rpcSpread==0){
		    nPassRPCSpread_ho+=1;
		    h_muonDR_HORPCSpread0[itr_file]->Fill(muonDR_min);
		    h_jetDR_HORPCSpread0[itr_file]->Fill(jetDR_min);
		    if(fabs(dPhiClusterMET)<1){
		      nPassDeltaPhi_ho+=1;
		      totalClusteredFullHOPlus+=dtRechitClusterSize[itr_clust];
		      //cout << "HO decay: jet DR = " << jetDR_min << ", muon DR = " << muonDR_min << endl;
		      //eventList << *runNum << ":" << *lumiSec << ":" << *eventNum << endl;
		      h_jetDR_minDR_fullHOVetoPlus[itr_file]->Fill(jetDR_min);
		      h_jetPt_minDR_fullHOVetoPlus[itr_file]->Fill(jetPt[jetDR_index]);
		      h_jetEta_minDR_fullHOVetoPlus[itr_file]->Fill(jetEta[jetDR_index]);
		      h_jetPhi_minDR_fullHOVetoPlus[itr_file]->Fill(jetPhi[jetDR_index]);
		      if(jetDR_min<0.6){
			h_jetChargedEMEnergyFraction_minDR_fullHOVetoPlus[itr_file]->Fill(jetChargedEMEnergyFraction[jetDR_index]);
			h_jetNeutralEMEnergyFraction_minDR_fullHOVetoPlus[itr_file]->Fill(jetNeutralEMEnergyFraction[jetDR_index]);
			h_jetChargedHadronEnergyFraction_minDR_fullHOVetoPlus[itr_file]->Fill(jetChargedHadronEnergyFraction[jetDR_index]);
			h_jetNeutralHadronEnergyFraction_minDR_fullHOVetoPlus[itr_file]->Fill(jetNeutralHadronEnergyFraction[jetDR_index]);
			//h_jetMuonEnergyFraction_minDR_fullHOVetoPlus[itr_file]->Fill(jetMuonEnergyFraction[jetDR_index]);
		      }
		    }
		  }
		}
		if((rpcBx.empty() || rpcSpread>0) && fabs(dPhiClusterMET)<1){
		  h_dtRechitClusterEta_fullHOVetoPlus[itr_file]->Fill(dtRechitClusterEta[itr_clust]);
		  h_dtRechitClusterPhi_fullHOVetoPlus[itr_file]->Fill(dtRechitClusterPhi[itr_clust]);
		  h_dtRechitClusterEtaPhi_fullHOVetoPlus[itr_file]->Fill(dtRechitClusterPhi[itr_clust],dtRechitClusterEta[itr_clust]);
		  h_dtRechitClusterNStation_fullHOVetoPlus[itr_file]->Fill(dtRechitClusterPhi[itr_clust]);
		  h_dtRechitClusterNWheel_fullHOVetoPlus[itr_file]->Fill(dtRechitClusterNChamber[itr_clust]);
		  h_jetDR_minDR_fullHOVetoMinus[itr_file]->Fill(jetDR_min);
		  h_jetPt_minDR_fullHOVetoMinus[itr_file]->Fill(jetPt[jetDR_index]);
		  h_jetEta_minDR_fullHOVetoMinus[itr_file]->Fill(jetEta[jetDR_index]);
		  h_jetPhi_minDR_fullHOVetoMinus[itr_file]->Fill(jetPhi[jetDR_index]);
		  if(jetDR_min<0.6){
		    h_jetChargedEMEnergyFraction_minDR_fullHOVetoMinus[itr_file]->Fill(jetChargedEMEnergyFraction[jetDR_index]);
		    h_jetNeutralEMEnergyFraction_minDR_fullHOVetoMinus[itr_file]->Fill(jetNeutralEMEnergyFraction[jetDR_index]);
		    h_jetChargedHadronEnergyFraction_minDR_fullHOVetoMinus[itr_file]->Fill(jetChargedHadronEnergyFraction[jetDR_index]);
		    h_jetNeutralHadronEnergyFraction_minDR_fullHOVetoMinus[itr_file]->Fill(jetNeutralHadronEnergyFraction[jetDR_index]);
		    //h_jetMuonEnergyFraction_minDR_fullHOVetoMinus[itr_file]->Fill(jetMuonEnergyFraction[jetDR_index]);
		  }
		}
	      }

	      if(passMuon && passMB1){
		h_jetPt_muonMB1Veto[itr_file]->Fill(jetPt_max);
	      }

	      if(passJet && passMB1){
		h_muonPt_jetMB1Veto[itr_file]->Fill(muonPt_max);
	      }

	      if(passJet && passHO){
		h_muonPt_jetHOVeto[itr_file]->Fill(muonPt_max);
	      }

	      if(passMuon && passHO){
		h_jetPt_muonHOVeto[itr_file]->Fill(jetPt_max);
	      }

	    }
	  }
	  h_nDtRechitClusters_noVeto[itr_file]->Fill(nPassNone);
	  h_nDtRechitClusters_muonVeto[itr_file]->Fill(nPassMuon);
	  h_nDtRechitClusters_jetVeto[itr_file]->Fill(nPassJet);
	  h_nDtRechitClusters_MB1Veto[itr_file]->Fill(nPassMB1);
	  h_nDtRechitClusters_fullVeto[itr_file]->Fill(nPassFull);

	  if(nPassNone>0){
	    nPassCluster+=1;
	    h_dPhiJetMET_noVeto[itr_file]->Fill(dPhi_min);
	    h_nWheels1_noVeto[itr_file]->Fill(hitWheels1);
	    h_nWheels10_noVeto[itr_file]->Fill(hitWheels10);
	    h_nWheels20_noVeto[itr_file]->Fill(hitWheels20);
	    h_nWheels30_noVeto[itr_file]->Fill(hitWheels30);
	    h_nWheels50_noVeto[itr_file]->Fill(hitWheels50);
	    h_nWheels150_noVeto[itr_file]->Fill(hitWheels150);
	    h_jetPtMET_noVeto[itr_file]->Fill(jetPt_tmp);
	    h_jetPtMax_noVeto[itr_file]->Fill(jetPt[0]);
	  }
	  if(nPassMuon>0){ h_dPhiJetMET_muonVeto[itr_file]->Fill(dPhi_min); }
	  if(nPassJet>0){ h_dPhiJetMET_jetVeto[itr_file]->Fill(dPhi_min); }
	  if(nPassMB1>0){ h_dPhiJetMET_MB1Veto[itr_file]->Fill(dPhi_min); }
	  if(nPassJetMuon>0){ h_dPhiJetMET_noMB1Veto[itr_file]->Fill(dPhi_min); }
	  if(nPassFull>0){
	    nPassFullDT+=1;
	    h_dPhiJetMET_fullVeto[itr_file]->Fill(dPhi_min);
	    h_jetPtMET_fullVeto[itr_file]->Fill(jetPt_tmp);
	    h_jetPtMax_fullVeto[itr_file]->Fill(jetPt[0]);
	  }
	  if(nPassFullPlus>0){
	    h_nWheels1_fullVetoPlus[itr_file]->Fill(hitWheels1);
	    h_nWheels10_fullVetoPlus[itr_file]->Fill(hitWheels10);
	    h_nWheels20_fullVetoPlus[itr_file]->Fill(hitWheels20);
	    h_nWheels30_fullVetoPlus[itr_file]->Fill(hitWheels30);
	    h_nWheels50_fullVetoPlus[itr_file]->Fill(hitWheels50);
	    h_nWheels150_fullVetoPlus[itr_file]->Fill(hitWheels150);
	    h_jetPtMET_fullVetoPlus[itr_file]->Fill(jetPt_tmp);
	    h_jetPtMax_fullVetoPlus[itr_file]->Fill(jetPt[0]);
	  }
	  if(nPassFullMinus>0){
	    h_nWheels1_fullVetoMinus[itr_file]->Fill(hitWheels1);
	    h_nWheels10_fullVetoMinus[itr_file]->Fill(hitWheels10);
	    h_nWheels20_fullVetoMinus[itr_file]->Fill(hitWheels20);
	    h_nWheels30_fullVetoMinus[itr_file]->Fill(hitWheels30);
	    h_nWheels50_fullVetoMinus[itr_file]->Fill(hitWheels50);
	    h_nWheels150_fullVetoMinus[itr_file]->Fill(hitWheels150);
	    h_jetPtMET_fullVetoMinus[itr_file]->Fill(jetPt_tmp);
	    h_jetPtMax_fullVetoMinus[itr_file]->Fill(jetPt[0]);
	  }

	  h_npv_nDtRechitClusters_noVeto[itr_file]->Fill(*npv,nPassNone);
	  h_npv_nDtRechitClusters_fullVeto[itr_file]->Fill(*npv,nPassFull);

	  h_nTotalClusteredRechits_noVeto[itr_file]->Fill(totalClusteredNone);
	  h_nTotalClusteredRechits_jetVeto[itr_file]->Fill(totalClusteredJet);
	  h_nTotalClusteredRechits_MB1Veto[itr_file]->Fill(totalClusteredMB1);
	  h_nTotalClusteredRechits_HOVeto[itr_file]->Fill(totalClusteredHO);
	  h_nTotalClusteredRechits_noMB1Veto[itr_file]->Fill(totalClusteredNoMB1);
	  h_nTotalClusteredRechits_fullVeto[itr_file]->Fill(totalClusteredFull);
	  h_nTotalClusteredRechits_fullHOVeto[itr_file]->Fill(totalClusteredFullHO);

	  h_nTotalClusteredRechits_fullVetoPlus[itr_file]->Fill(totalClusteredFullPlus);
	  h_nTotalClusteredRechits_fullHOVetoPlus[itr_file]->Fill(totalClusteredFullHOPlus);

	  h_HOMatchedEnergyCluster280_noMB1Veto[itr_file]->Fill(totalSumE);
	}

	for(Int_t itr_clust = 0; itr_clust<*nDtRechitClusters; itr_clust++){
	  match = 0;
	  matchLayer1 = 0;
	  matchLayer2 = 0;
	  matchLayer3 = 0;
	  matchLayer4 = 0;
	  matchHO = 0;
	  sumE = 0.0;
	  weightT = 0.0;
	  rpcBx.clear();
	  rpcLayer.clear();
	  rpcSpread = -99;
	  matchJet = false;
	  matchMuon = false;
	  goodEvt = true;
	  passMuon = false;
	  passJet = false;
	  passMB1 = false;
	  passMB1_alt = false;
	  passMuon_alt = false;
	  passHO = false;
	  passInvertedJet = false;
	  passInvertedMuon = false;
	  passInvertedMuJet = false;

	  if(dtRechitClusterJetVetoPt[itr_clust]<20.){ passJet = true; }
	  else{ passInvertedJet = true; }
	  if(dtRechitClusterMuonVetoPt[itr_clust]<10.){ passMuon = true; }
	  else{ passInvertedMuon = true; }
	  if(dtRechitClusterNSegmentStation1[itr_clust]==0){ passMB1 = true; }

	  if(dtRechitClusterSize[itr_clust]>50 && ((dtRechitClusterPhi[itr_clust]<0.4 || dtRechitClusterPhi[itr_clust]>0.6) || (*runNum<275.75e3 || *runNum>275.95e3))){

	    dPhiClusterMET = dtRechitClusterPhi[itr_clust] - *METphi;
	    if(dPhiClusterMET > TMath::Pi()){ dPhiClusterMET -= 2*TMath::Pi(); }
	    if(dPhiClusterMET < -1.0*TMath::Pi()){ dPhiClusterMET += 2*TMath::Pi(); }

	    for(Int_t itr_rpc=0; itr_rpc<*nRPCRechits; itr_rpc++){
	      dPhi_tmp = RPCRechitPhi[itr_rpc] - dtRechitClusterPhi[itr_clust];
	      if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
	      if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
	      if(fabs(RPCRechitZ[itr_rpc] - dtRechitClusterZ[itr_clust])<5. && fabs(dPhi_tmp)<0.4){
		match+=1;
		rpcBx.push_back(RPCRechitBx[itr_rpc]);
		rpcLayer.push_back(getRPCLayer(RPCRechitX[itr_rpc],RPCRechitY[itr_rpc]));
	      }
	    }
	    if(!rpcBx.empty()){
	      rpcSpread = max_element(rpcBx.begin(), rpcBx.end()) - min_element(rpcBx.begin(), rpcBx.end());
	    }

	    if(rpcBx.empty() || rpcSpread>0){
	      nPassNone+=1;
	      if(passJet && passMuon && passMB1){
		nPassFull+=1;
		if(dtRechitClusterMaxStation[itr_clust]==2){
		  h_dtRechitClusterPhiStation2_fullVeto_rpcCR[itr_file]->Fill(dtRechitClusterPhi[itr_clust]);
		}
		if(dtRechitClusterMaxStation[itr_clust]==3){
		  h_dtRechitClusterPhiStation3_fullVeto_rpcCR[itr_file]->Fill(dtRechitClusterPhi[itr_clust]);
		}
		if(dtRechitClusterMaxStation[itr_clust]==4){
		  h_dtRechitClusterPhiStation4_fullVeto_rpcCR[itr_file]->Fill(dtRechitClusterPhi[itr_clust]);
		}
		if(dtRechitClusterMaxStation[itr_clust]>2 && fabs(dPhiClusterMET)<1.0){
		  nPassFullPlus_rpcCR+=1;
		  if(failJetMET){ nFailJetMET += 1; }
		  if(failJetMET_20){ nFailJetMET_20 += 1; }
		  if(failJetMET_30){ nFailJetMET_30 += 1; }
		  if(failJetMET_50){ nFailJetMET_50 += 1; }
		  if(failJetMET_top4){ nFailJetMET_top4 += 1; }
		}
	      }
	    }
	  }
	}
	if(nPassNone>0){ h_jetPtMET_noVeto_rpcCR[itr_file]->Fill(jetPt_tmp); }
	if(nPassFull>0){ h_jetPtMET_fullVeto_rpcCR[itr_file]->Fill(jetPt_tmp); }
	if(nPassFullPlus>0){ h_jetPtMET_fullVetoPlus_rpcCR[itr_file]->Fill(jetPt_tmp); }
      }
      evtNum+=1;
    }
    itr_file+=1;



  cout << "MET > 200: " << nPassMET << endl;
  cout << "full Plus RPC CR: " << nPassFullPlus_rpcCR << endl;
  cout << "min dPhi(jet,MET) > 0.6: " << nFailJetMET << endl;
  cout << "min dPhi(jet [Top 4],MET) > 0.6: " << nFailJetMET_top4 << endl;
  cout << "min dPhi(jet [20 GeV],MET) > 0.6: " << nFailJetMET_20 << endl;
  cout << "min dPhi(jet [30 GeV],MET) > 0.6: " << nFailJetMET_30 << endl;
  cout << "min dPhi(jet [50 GeV],MET) > 0.6: " << nFailJetMET_50 << endl;
  cout << "min dPhi(jet,MET) < 0.6: " << nPassJetMET << endl;
  cout << "DT cluster: " << nPassCluster << endl;
  cout << " " << endl;

  cout << "Full DT Veto: " << nPassFullDT << endl;
  cout << "nRPC Matched > 0: " << nPassRPCMatch_dt << endl;
  cout << "RPC Spread = 0: " << nPassRPCSpread_dt << endl;
  cout << "Max Station > 2: " << nPassMaxStation_dt << endl;
  cout << "dPhi(Cluster,MET) < 1: " << nPassDeltaPhi_dt << endl;
  cout << " " << endl;

  cout << "Full HO Veto: " << nPassFullHO << endl;
  cout << "nRPC Matched > 0: " << nPassRPCMatch_ho << endl;
  cout << "RPC Spread = 0: " << nPassRPCSpread_ho << endl;
  cout << "dPhi(Cluster,MET) < 1: " << nPassDeltaPhi_ho << endl;

  cout << " " << endl;
  cout << "DT cluster: " << nPassCluster << endl;
  cout << " " << endl;
  cout << "Muon veto: " << nPassMuon_std << endl;
  cout << "MB1 veto: " << nPassMB1_std << endl;
  cout << "Jet+Muon veto: " << nPassJetMuon_std << endl;
  cout << "Jet+MB1 veto: " << nPassJetMB1_std << endl;
  cout << "Full DT Veto: " << nPassFull_std << endl;
  cout << " " << endl;
  cout << "Alt Muon veto: " << nPassMuon_alt << endl;
  cout << "Alt MB1 veto: " << nPassMB1_alt << endl;
  cout << "Alt Muon Full DT veto: " << nPassFull_altMuon << endl;
  cout << "Alt MB1 Full DT veto: " << nPassFull_altMB1 << endl;
  cout << "Alt Muon MB1 Full DT veto: " << nPassFull_altMuonMB1 << endl;
  cout << " " << endl;
  cout << "Full DT Selection No Muon: " << nPassFullDTPlus_noMuon << endl;
  cout << "Full DT Selection No MB1: " << nPassFullDTPlus_noMB1 << endl;
  cout << "Full DT Selection: " << nPassFullDTPlus_std << endl;
  cout << "Alt Muon Full DT Selection: " << nPassFullDTPlus_altMuon << endl;
  cout << "Alt MB1 Full DT Selection: " << nPassFullDTPlus_altMB1 << endl;
  cout << "Alt Muon MB1 Full DT Selection: " << nPassFullDTPlus_altMuonMB1 << endl;

  }

  _ofile->Write();
  _ofile->Close();
  eventList.close();

}
