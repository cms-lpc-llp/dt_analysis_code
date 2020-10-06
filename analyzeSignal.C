R__LOAD_LIBRARY(libTreePlayer)

int getStation(float hitX, float hitY){
  float hitR = sqrt(pow(hitX,2)+pow(hitY,2));
  if(hitR > 400. && hitR < 480.){ return 1; }
  else if(hitR > 485. && hitR < 560.){ return 2; }
  else if(hitR > 590. && hitR < 650.){ return 3; }
  else if(hitR > 690. && hitR < 800.){ return 4; }
  else{ return -1; }
}

int getWheel(float hitZ){
  if(hitZ > 0){
    if(hitZ < 127.){ return 0; }
    else if(hitZ < 395.){ return 1; }
    else if(hitZ < 661.){ return 2; }
    else{ return -99; }
  }
  else{
    return -1*getWheel(-1.0*hitZ);
  }
}

int getRPCLayer(float hitX, float hitY){
  float hitR = sqrt(pow(hitX,2)+pow(hitY,2));
  if(hitR > 410. && hitR < 440.){ return 1; }
  else if(hitR > 445. && hitR < 475.){ return 2; }
  else if(hitR > 490. && hitR < 520.){ return 3; }
  else if(hitR > 525. && hitR < 555.){ return 4; }
  else if(hitR > 600. && hitR < 630.){ return 5; }
  else if(hitR > 700. && hitR < 770.){ return 6; }
  else{ return -1; }
}

void analyzeSignal(){

  char name[50];
  char title[100];
  char mX[3][10] = {"15","40","55"};
  //char mX[2][10] = {"25","450"};
  //char ctau[10] = "1m";
  char ctau[10] = "10000";
  char years[3][20] = {"MC_Summer16","MC_Fall17","MC_Fall18"};
  //TString dir("/storage/user/mcitron/signalPointsGGHWithRPCWithFlags/");
  TString dir("/mnt/hadoop/store/group/phys_exotica/delayedjets/displacedJetMuonAnalyzer/driftTube/V1p17/");
  //TString dir("/mnt/hadoop/store/group/phys_exotica/delayedjets/displacedJetMuonAnalyzer/driftTube/V1p15/");
  TFile *_ofile = TFile::Open("outSig_central_V1p17_altTest5.root","RECREATE");
  Float_t lumi[3] = {37.8,44.98,63.67};
  Float_t xSec = 48.58;
  Float_t weight;
  
  TH1D *h_dPhiClusterMET[4];
  TH1D *h_dPhiClusterMETMax[4];
  TH1D *h_dPhiJetMET[4];
  TH1D *h_jetMet_dPhiMin4[4];
  TH1D *h_MET[4];
  TH1D *h_jetPt[4];

  TH1D *h_dPhiJetMETBarrel_noVeto[4];
  TH1D *h_dPhiJetMETBarrel_jetVeto[4];
  TH1D *h_dPhiJetMETBarrel_muonVeto[4];
  TH1D *h_dPhiJetMETBarrel_MB1Veto[4];
  TH1D *h_dPhiJetMETBarrel_noMB1Veto[4];
  TH1D *h_dPhiJetMETBarrel_fullVeto[4];
  TH1D *h_dPhiJetMETMagnet_noVeto[4];
  TH1D *h_dPhiJetMETMagnet_jetVeto[4];
  TH1D *h_dPhiJetMETMagnet_muonVeto[4];
  TH1D *h_dPhiJetMETMagnet_MB1Veto[4];
  TH1D *h_dPhiJetMETMagnet_noMB1Veto[4];
  TH1D *h_dPhiJetMETMagnet_fullVeto[4];
  TH1D *h_dPhiJetMETMagnet_fullHOVeto[4];
  TH1D *h_dPhiJetMETMagnet[4];
  TH1D *h_dPhiJetMETAll_noVeto[4];
  TH1D *h_dPhiJetMETAll_jetVeto[4];
  TH1D *h_dPhiJetMETAll_muonVeto[4];
  TH1D *h_dPhiJetMETAll_MB1Veto[4];
  TH1D *h_dPhiJetMETAll_noMB1Veto[4];
  TH1D *h_dPhiJetMETAll_fullVeto[4];

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
  TH2D *h_npv_nDtRechitClusters_noVeto[4];

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
  TH1D *h_nRPCMatchedMagnet_jetVeto[4];
  TH1D *h_nRPCMatchedMagnetLayer1_jetVeto[4];
  TH1D *h_nRPCMatchedMagnetLayer2_jetVeto[4];
  TH1D *h_nRPCMatchedMagnetLayer3_jetVeto[4];
  TH1D *h_nRPCMatchedMagnetLayer4_jetVeto[4];
  TH1D *h_nRPCMatchedMagnetLayer1_fullHOVeto[4];
  TH1D *h_nRPCMatchedMagnetLayer2_fullHOVeto[4];
  TH1D *h_nRPCMatchedMagnetLayer3_fullHOVeto[4];
  TH1D *h_nRPCMatchedMagnetLayer4_fullHOVeto[4];
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
  TH1D *h_dtRechitClusterNThreshLowStation_fullVeto[4];
  TH1D *h_dtRechitClusterNThreshStationUnclustered_fullVeto[4];
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
  TH1D *h_dtRechitClusterNWheels50_fullVeto[4];
  TH1D *h_dtRechitClusterNWheels25_fullVeto[4];
  TH1D *h_dtRechitClusterNWheels1_fullVeto[4];
  TH1D *h_dtRechitClusterMaxWheel_fullVeto[4];
  TH2D *h_npv_nDtRechitClusters_fullVeto[4];
  TH1D *h_gLLPpt_fullVeto[4];
  TH1D *h_gLLPpt_Bx0_fullVeto[4];
  TH1D *h_gLLPpt_Bx1_fullVeto[4];
  TH1D *h_gLLP_travel_time_fullVeto[4];

  TH1D *h_RPCMatchedBx_invertedJetVeto[4];
  TH1D *h_RPCMatchedBx_invertedMuonVeto[4];
  TH1D *h_RPCMatchedBx_invertedMuJetVeto[4];

  TH1D *h_dtRechitClusterSize_noMB1Veto[4];
  TH1D *h_dtRechitClusterSizeBarrel_noMB1Veto[4];
  TH1D *h_dtRechitClusterSizeMagnet_noMB1Veto[4];
  TH1D *h_dtRechitClusterSizeAll_noMB1Veto[4];
  TH1D *h_dtRechitClusterNStation_noMB1Veto[4];
  TH1D *h_dtRechitClusterNRechitsMB1_noMB1Veto[4];
  TH1D *h_dtRechitClusterPercentRechitsMB1_noMB1Veto[4];
  TH1D *h_nRPCMatched_noMB1Veto[4];
  TH1D *h_nRPCMatchedLayer1_noMB1Veto[4];
  TH1D *h_nRPCMatchedLayer2_noMB1Veto[4];
  TH1D *h_nRPCMatchedLayer12_noMB1Veto[4];
  TH1D *h_RPCMatchedBxSpread_noMB1Veto[4];

  TH1D *h_dtRechitClusterSizeBarrel_HOVeto[4];
  TH1D *h_dtRechitClusterSizeMagnet_HOVeto[4];
  TH1D *h_dtRechitClusterSizeAll_HOVeto[4];

  TH1D *h_dtRechitClusterSizeBarrel_fullHOVeto[4];
  TH1D *h_dtRechitClusterSizeMagnet_fullHOVeto[4];
  TH1D *h_dtRechitClusterSizeAll_fullHOVeto[4];
 
  TH1D *h_nTotalClusteredRechitsBarrel_noVeto[4];
  TH1D *h_nTotalClusteredRechitsMagnet_noVeto[4];
  TH1D *h_nTotalClusteredRechitsAll_noVeto[4];
  TH1D *h_nTotalClusteredRechitsBarrel_jetVeto[4];
  TH1D *h_nTotalClusteredRechitsMagnet_jetVeto[4];
  TH1D *h_nTotalClusteredRechitsAll_jetVeto[4];
  TH1D *h_nTotalClusteredRechitsBarrel_MB1Veto[4];
  TH1D *h_nTotalClusteredRechitsMagnet_MB1Veto[4];
  TH1D *h_nTotalClusteredRechitsAll_MB1Veto[4];
  TH1D *h_nTotalClusteredRechitsBarrel_noMB1Veto[4];
  TH1D *h_nTotalClusteredRechitsMagnet_noMB1Veto[4];
  TH1D *h_nTotalClusteredRechitsAll_noMB1Veto[4];
  TH1D *h_nTotalClusteredRechitsBarrel_HOVeto[4];
  TH1D *h_nTotalClusteredRechitsMagnet_HOVeto[4];
  TH1D *h_nTotalClusteredRechitsAll_HOVeto[4];
  TH1D *h_nTotalClusteredRechitsBarrel_fullVeto[4];
  TH1D *h_nTotalClusteredRechitsMagnet_fullVeto[4];
  TH1D *h_nTotalClusteredRechitsAll_fullVeto[4];
  TH1D *h_nTotalClusteredRechitsBarrel_fullHOVeto[4];
  TH1D *h_nTotalClusteredRechitsMagnet_fullHOVeto[4];
  TH1D *h_nTotalClusteredRechitsAll_fullHOVeto[4];
  
  TH1D *h_dtRechitClusterSize_RPCMatch[4];
  TH1D *h_dtRechitClusterSize_RPCSpread0[4];
  TH1D *h_nTotalClusteredRechits_fullVetoPlus[4];
  TH1D *h_nTotalClusteredRechitsBarrel_fullVetoPlus[4];
  TH1D *h_nTotalClusteredRechitsMagnet_fullHOVetoPlus[4];
  TH1D *h_dtRechitClusterXSpread_fullVetoPlus[4];
  TH1D *h_dtRechitClusterYSpread_fullVetoPlus[4];
  TH1D *h_dtRechitClusterZSpread_fullVetoPlus[4];
  TH1D *h_dtRechitClusterEtaSpread_fullVetoPlus[4];
  TH1D *h_dtRechitClusterPhiSpread_fullVetoPlus[4];
  TH1D *h_dtRechitClusterEta_fullVetoPlus[4];
  TH1D *h_dtRechitClusterPhi_fullVetoPlus[4];
  TH2D *h_dtRechitClusterEtaPhi_fullVetoPlus[4];
  TH1D *h_dtRechitClusterNStation_fullVetoPlus[4];
  TH1D *h_dtRechitClusterSizeRatio_fullVetoPlus[4];
  TH1D *h_dtRechitClusterSizeRatio_fullVetoMinus[4];
  TH1D *h_dtRechitClusterNWheel_fullVetoPlus[4];
  TH1D *h_dtRechitClusterNStation_fullHOVetoPlus[4];
  TH1D *h_dtRechitClusterNWheel_fullHOVetoPlus[4];

  TH1D *h_HOMatchedEnergyCluster280Magnet_noMB1Veto[4];

  TH1D *h_HOTime_fullHOVeto[4];

  TH1D *h_muonPt_jetMB1Veto[4];
  TH1D *h_jetPt_muonMB1Veto[4];
  TH1D *h_MB1Rechits_jetMuonVeto[4];
  TH1D *h_muonPt_jetHOVeto[4];
  TH1D *h_jetPt_muonHOVeto[4];
  TH1D *h_HOEnergy_jetMuonVeto[4];

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

  TH1D *h_decayVertexRadius_noVeto[4];
  TH1D *h_HOEnergy_jetVeto[4];
  TH1D *h_dRClusterRPC_jetVeto[4];
  TH1D *h_dRClusterHO_jetVeto[4];

  TH1D *h_jetDR_minDR_fullHOVetoPlus[4];
  TH1D *h_jetPt_minDR_fullHOVetoPlus[4];
  TH1D *h_jetEta_minDR_fullHOVetoPlus[4];
  TH1D *h_jetPhi_minDR_fullHOVetoPlus[4];
  TH1D *h_jetChargedEMEnergyFraction_minDR_fullHOVetoPlus[4];
  TH1D *h_jetNeutralEMEnergyFraction_minDR_fullHOVetoPlus[4];
  TH1D *h_jetNeutralHadronEnergyFraction_minDR_fullHOVetoPlus[4];
  TH1D *h_jetChargedHadronEnergyFraction_minDR_fullHOVetoPlus[4];
  TH1D *h_jetDR_minDR_vetoJet[4];
  TH1D *h_jetPt_minDR_vetoJet[4];
  TH1D *h_jetEta_minDR_vetoJet[4];
  TH1D *h_jetPhi_minDR_vetoJet[4];
  TH1D *h_jetChargedEMEnergyFraction_minDR_vetoJet[4];
  TH1D *h_jetNeutralEMEnergyFraction_minDR_vetoJet[4];
  TH1D *h_jetNeutralHadronEnergyFraction_minDR_vetoJet[4];
  TH1D *h_jetChargedHadronEnergyFraction_minDR_vetoJet[4];

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

  Double_t dPhi_tmp = 0.0;
  Double_t dPhiClusterMET = 0.0;
  Double_t dPhiClusterMET_max = 0.0;
  Double_t dPhi_min = 999.;
  Double_t clustSizeMax = 0.;
  Double_t dPhi_clust = 999.;
  Double_t jetPt_tmp = 0.0;
  Double_t dPhi_minTop4 = 0.0;
  Double_t dPhi_min20 = 0.0;
  Double_t dPhi_min30 = 0.0;
  Double_t dPhi_min50 = 0.0;
  Double_t muonPt_max = 0.0;
  Double_t muonDR_min = 0.0;
  Double_t jetPt_max = 0.0;
  Double_t jetDR_min = 0.0;
  Int_t jetDR_index = -1;

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

  vector<Int_t> muStatus = {};
  Double_t dR_tmp = 0.0;
  Int_t nMatched = 0;
  vector<Int_t> goodStatus = {1,44,51,52,91};
  vector<Int_t> rpcBx = {};
  vector<Int_t> rpcLayer = {};
  vector<Int_t> zWheel = {};
  Int_t rpcSpread = 0;
  Float_t rpcMean = 0;

  Int_t evtNum = 0;
  Int_t totalNum = 0;
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
  Float_t sumE = 0.0;
  Float_t totalSumE = 0.0;
  Float_t weightT = 0.0;
  Int_t llp_itr = -1;

  Bool_t passMuon = false;
  Bool_t passMuon_alt = false;
  Bool_t passMB1_alt = false;
  Bool_t passJet = false;
  Bool_t passMB1 = false;
  Bool_t passHO = false;
  Bool_t passInvertedJet = false;
  Bool_t passInvertedMuon = false;
  Bool_t passInvertedMuJet = false;
  Int_t nPassMuon = 0;
  Int_t nPassJet = 0;
  Int_t nPassMuon_std = 0;
  Int_t nPassMB1_std = 0;
  Int_t nPassMuon_alt = 0;
  Int_t nPassMB1_alt = 0;
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
  Int_t nPassFullHO = 0;
  Int_t nPassNone = 0;
  Int_t nPassFullPlus = 0;
  Int_t nPassFullDTPlus_noMuon = 0;
  Int_t nPassFullDTPlus_noMB1 = 0;
  Int_t nPassFullDTPlus_std = 0;
  Int_t nPassFullDTPlus_altMuon = 0;
  Int_t nPassFullDTPlus_altMB1 = 0;
  Int_t nPassFullDTPlus_altMuonMB1 = 0;
  Int_t nPassFullMinus = 0;
  Int_t totalBarrelEvents = 0;
  Int_t totalMagnetEvents = 0;
  Int_t totalEvents = 0;
  Int_t totalClusteredNone = 0;
  Int_t totalClusteredNoMB1 = 0;
  Int_t totalClusteredJet = 0;
  Int_t totalClusteredMB1 = 0;
  Int_t totalClusteredHO = 0;
  Int_t totalClusteredFull = 0;
  Int_t totalClusteredFullHO = 0;
  Float_t noEff = 0.0;
  Float_t muonEff = 0.0;
  Float_t jetEff = 0.0;
  Float_t MB1Eff = 0.0;
  Float_t HOEff = 0.0;
  Float_t fullHOEff = 0.0;
  Float_t fullEff = 0.0;
  
  Bool_t goodDecay = false;
  Bool_t magnetDecay = false;

  Bool_t passMuonEvent_std=false;
  Bool_t passMB1Event_std=false;
  Bool_t passMuonEvent_alt=false;
  Bool_t passMB1Event_alt=false;
  Bool_t passJetMB1_std=false;
  Bool_t passJetMuon_std=false;
  Bool_t passFull_std = false;
  Bool_t passFull_altMuon = false;
  Bool_t passFull_altMB1 = false;
  Bool_t passFull_altMuonMB1 = false;
  Bool_t passFullDTPlus_noMuon = false;
  Bool_t passFullDTPlus_noMB1 = false;
  Bool_t passFullDTPlus_std = false;
  Bool_t passFullDTPlus_altMuon = false;
  Bool_t passFullDTPlus_altMB1 = false;
  Bool_t passFullDTPlus_altMuonMB1 = false;	      

  Bool_t passNoVeto = false;
  Bool_t passFullVeto = false;
  Bool_t passRPCMatch = false;
  Bool_t passRPCSpread = false;
  Bool_t passMaxStation = false;
  Bool_t passDeltaPhi = false;
  Bool_t passFullVeto_ho = false;
  Bool_t passRPCMatch_ho = false;
  Bool_t passRPCSpread_ho = false;
  Bool_t passMaxStation_ho = false;
  Bool_t passDeltaPhi_ho = false;
  Bool_t passJetMET = false;
  Bool_t passJetMET_20 = false;
  Bool_t passJetMET_30 = false;
  Bool_t passJetMET_50 = false;
  Bool_t passJetMET_top4 = false;

  Float_t nPassMET = 0;
  Float_t nPassDTDecay = 0;
  Float_t nPassJetMET = 0;
  Float_t nPassJetMET_top4 = 0;
  Float_t nPassJetMET_20 = 0;
  Float_t nPassJetMET_30 = 0;
  Float_t nPassJetMET_50 = 0;
  Float_t nPassNoVeto = 0;
  Float_t nPassFullVeto = 0;
  
  Float_t nPassMaxStation = 0;
  Float_t nPassDeltaPhi = 0;
  Float_t nPassRPCMatch = 0;
  Float_t nPassRPCSpread = 0;
  
  Float_t nPassHODecay = 0;
  Float_t nPassNoVeto_ho = 0;
  Float_t nPassFullVeto_ho = 0;
  Float_t nPassRPCMatch_ho = 0;
  Float_t nPassRPCSpread_ho = 0;
  Float_t nPassDeltaPhi_ho = 0;

  Int_t totalClusteredFullPlus = 0;
  Int_t totalClusteredFullHOPlus = 0;

  for(Int_t itr_mX=0; itr_mX<3; itr_mX++){
    sprintf(name,"h_jetMet_dPhiMin4_%s_%s",mX[itr_mX],ctau);
    h_jetMet_dPhiMin4[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMET_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMET[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMETBarrel_noVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETBarrel_noVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMETBarrel_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETBarrel_jetVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMETBarrel_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETBarrel_muonVeto[itr_file] = new TH1D(name,"",70,0,3.5);
    
    sprintf(name,"h_dPhiJetMETBarrel_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETBarrel_MB1Veto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMETBarrel_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETBarrel_noMB1Veto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMETBarrel_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETBarrel_fullVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMETMagnet_noVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETMagnet_noVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMETMagnet_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETMagnet_jetVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMETMagnet_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETMagnet_muonVeto[itr_file] = new TH1D(name,"",70,0,3.5);
    
    sprintf(name,"h_dPhiJetMETMagnet_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETMagnet_MB1Veto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMETMagnet_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETMagnet_noMB1Veto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMETMagnet_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETMagnet_fullVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMETMagnet_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETMagnet_fullHOVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMETMagnet_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETMagnet[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMETAll_noVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETAll_noVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMETAll_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETAll_jetVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMETAll_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETAll_muonVeto[itr_file] = new TH1D(name,"",70,0,3.5);
    
    sprintf(name,"h_dPhiJetMETAll_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETAll_MB1Veto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMETAll_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETAll_noMB1Veto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiJetMETAll_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiJetMETAll_fullVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiClusterMET_%s_%s",mX[itr_mX],ctau);
    h_dPhiClusterMET[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiClusterMETMax_%s_%s",mX[itr_mX],ctau);
    h_dPhiClusterMETMax[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_MET_%s_%s",mX[itr_mX],ctau);
    h_MET[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_jetPt_%s_%s",mX[itr_mX],ctau);
    h_jetPt[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nDtRechitClusters_noVeto_%s_%s",mX[itr_mX],ctau);
    h_nDtRechitClusters_noVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterSize_noVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSize_noVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechits_noVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechits_noVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterMaxStation_noVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterMaxStation_noVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNStation_noVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNStation_noVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dPhiClusterMET_noVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiClusterMET_noVeto[itr_file] = new TH1D(name,"",70,0,3.5);
    
    sprintf(name,"h_dtRechitClusterXSpread_noVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterXSpread_noVeto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterYSpread_noVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterYSpread_noVeto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterZSpread_noVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterZSpread_noVeto[itr_file] = new TH1D(name,"",30,0,150);

    sprintf(name,"h_dtRechitClusterEtaSpread_noVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterEtaSpread_noVeto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_dtRechitClusterPhiSpread_noVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterPhiSpread_noVeto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_RPCMatchedBx_noVeto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBx_noVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_noVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatched_noVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBxSpread_noVeto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBxSpread_noVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBx_Spread0_noVeto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBx_Spread0_noVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_Spread0_noVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatched_Spread0_noVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_nDtRechitClusters_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_nDtRechitClusters_muonVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterSize_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSize_muonVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechits_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechits_muonVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterMaxStation_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterMaxStation_muonVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNStation_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNStation_muonVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dPhiClusterMET_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiClusterMET_muonVeto[itr_file] = new TH1D(name,"",70,0,3.5);
    
    sprintf(name,"h_dtRechitClusterXSpread_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterXSpread_muonVeto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterYSpread_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterYSpread_muonVeto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterZSpread_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterZSpread_muonVeto[itr_file] = new TH1D(name,"",30,0,150);

    sprintf(name,"h_dtRechitClusterEtaSpread_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterEtaSpread_muonVeto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_dtRechitClusterPhiSpread_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterPhiSpread_muonVeto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_RPCMatchedBx_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBx_muonVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatched_muonVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBxSpread_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBxSpread_muonVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBx_Spread0_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBx_Spread0_muonVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_Spread0_muonVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatched_Spread0_muonVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_nDtRechitClusters_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_nDtRechitClusters_jetVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterSizeBarrel_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeBarrel_jetVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSizeMagnet_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeMagnet_jetVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSizeAll_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeAll_jetVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSize_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSize_jetVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechits_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechits_jetVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterMaxStation_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterMaxStation_jetVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNStation_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNStation_jetVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dPhiClusterMET_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiClusterMET_jetVeto[itr_file] = new TH1D(name,"",70,0,3.5);
    
    sprintf(name,"h_dtRechitClusterXSpread_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterXSpread_jetVeto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterYSpread_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterYSpread_jetVeto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterZSpread_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterZSpread_jetVeto[itr_file] = new TH1D(name,"",30,0,150);

    sprintf(name,"h_dtRechitClusterEtaSpread_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterEtaSpread_jetVeto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_dtRechitClusterPhiSpread_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterPhiSpread_jetVeto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_RPCMatchedBx_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBx_jetVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatched_jetVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_nRPCMatchedMagnet_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatchedMagnet_jetVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_nRPCMatchedMagnetLayer1_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatchedMagnetLayer1_jetVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_nRPCMatchedMagnetLayer2_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatchedMagnetLayer2_jetVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_nRPCMatchedMagnetLayer3_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatchedMagnetLayer3_jetVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_nRPCMatchedMagnetLayer4_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatchedMagnetLayer4_jetVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_nRPCMatchedMagnetLayer1_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatchedMagnetLayer1_fullHOVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_nRPCMatchedMagnetLayer2_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatchedMagnetLayer2_fullHOVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_nRPCMatchedMagnetLayer3_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatchedMagnetLayer3_fullHOVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_nRPCMatchedMagnetLayer4_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatchedMagnetLayer4_fullHOVeto[itr_file] = new TH1D(name,"",30,0,30);

    sprintf(name,"h_RPCMatchedBxSpread_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBxSpread_jetVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBx_Spread0_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBx_Spread0_jetVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_Spread0_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatched_Spread0_jetVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_dtRechitClusterSizeBarrel_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeBarrel_MB1Veto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nDtRechitClusters_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_nDtRechitClusters_MB1Veto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterSizeMagnet_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeMagnet_MB1Veto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSizeAll_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeAll_MB1Veto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSize_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSize_MB1Veto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechits_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechits_MB1Veto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterMaxStation_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterMaxStation_MB1Veto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNStation_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNStation_MB1Veto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dPhiClusterMET_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dPhiClusterMET_MB1Veto[itr_file] = new TH1D(name,"",70,0,3.5);
    
    sprintf(name,"h_dtRechitClusterXSpread_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterXSpread_MB1Veto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterYSpread_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterYSpread_MB1Veto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterZSpread_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterZSpread_MB1Veto[itr_file] = new TH1D(name,"",30,0,150);

    sprintf(name,"h_dtRechitClusterEtaSpread_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterEtaSpread_MB1Veto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_dtRechitClusterPhiSpread_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterPhiSpread_MB1Veto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_RPCMatchedBx_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBx_MB1Veto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatched_MB1Veto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBxSpread_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBxSpread_MB1Veto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBx_Spread0_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBx_Spread0_MB1Veto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_Spread0_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatched_Spread0_MB1Veto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_nDtRechitClusters_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_nDtRechitClusters_fullVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterSizeBarrel_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeBarrel_fullVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSizeMagnet_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeMagnet_fullVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSizeAll_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeAll_fullVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSize_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSize_fullVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechits_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechits_fullVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterMaxStation_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterMaxStation_fullVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterMaxStation_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterMaxStation_fullHOVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNStation_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNStation_fullVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNStationUnclustered_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNStationUnclustered_fullVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNThreshStation_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNThreshStation_fullVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNThreshLowStation_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNThreshLowStation_fullVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNThreshStationUnclustered_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNThreshStationUnclustered_fullVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNThreshLowStationUnclustered_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNThreshLowStationUnclustered_fullVeto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dPhiClusterMET_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiClusterMET_fullVeto[itr_file] = new TH1D(name,"",70,0,3.5);

    sprintf(name,"h_dPhiClusterMET_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_dPhiClusterMET_fullHOVeto[itr_file] = new TH1D(name,"",70,0,3.5);
    
    sprintf(name,"h_dtRechitClusterXSpread_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterXSpread_fullVeto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterYSpread_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterYSpread_fullVeto[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterZSpread_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterZSpread_fullVeto[itr_file] = new TH1D(name,"",30,0,150);

    sprintf(name,"h_dtRechitClusterEtaSpread_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterEtaSpread_fullVeto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_dtRechitClusterPhiSpread_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterPhiSpread_fullVeto[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_RPCMatchedBx_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBx_fullVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatched_fullVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_nRPCMatched_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatched_fullHOVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBxSpread_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBxSpread_fullVeto[itr_file] = new TH1D(name,"",10,0,10);

    sprintf(name,"h_RPCMatchedBxSpread_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBxSpread_fullHOVeto[itr_file] = new TH1D(name,"",10,0,10);

    sprintf(name,"h_RPCMatchedBx_Spread0_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBx_Spread0_fullVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_nRPCMatched_Spread0_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatched_Spread0_fullVeto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_dtRechitClusterEta_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterEta_fullVeto[itr_file] = new TH1D(name,"",60,-3,3);

    sprintf(name,"h_dtRechitClusterPhi_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterPhi_fullVeto[itr_file] = new TH1D(name,"",70,-3.5,3.5);

    sprintf(name,"h_dtRechitClusterR_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterR_fullVeto[itr_file] = new TH1D(name,"",40,0,800);

    sprintf(name,"h_dtRechitClusterZ_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterZ_fullVeto[itr_file] = new TH1D(name,"",120,-600,600);

    sprintf(name,"h_dtRechitClusterRZ_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterRZ_fullVeto[itr_file] = new TH2D(name,"",120,-600,600,40,400,800);

    sprintf(name,"h_dtRechitClusterRZFine_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterRZFine_fullVeto[itr_file] = new TH2D(name,"",1200,-600,600,400,400,800);

    sprintf(name,"h_dtRechitClusterNWheels50_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNWheels50_fullVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_dtRechitClusterNWheels25_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNWheels25_fullVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_dtRechitClusterNWheels1_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNWheels1_fullVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_dtRechitClusterMaxWheel_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterMaxWheel_fullVeto[itr_file] = new TH1D(name,"",6,-3,3);

    sprintf(name,"h_gLLPpt_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_gLLPpt_fullVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_gLLPpt_Bx0_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_gLLPpt_Bx0_fullVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_gLLPpt_Bx1_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_gLLPpt_Bx1_fullVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_gLLP_travel_time_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_gLLP_travel_time_fullVeto[itr_file] = new TH1D(name,"",100,0,10000);

    sprintf(name,"h_npv_nDtRechitClusters_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_npv_nDtRechitClusters_fullVeto[itr_file] = new TH2D(name,"",10,0,10,5,0,5);

    sprintf(name,"h_RPCMatchedBx_invertedJetVeto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBx_invertedJetVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_RPCMatchedBx_invertedMuonVeto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBx_invertedMuonVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);

    sprintf(name,"h_RPCMatchedBx_invertedMuJetVeto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBx_invertedMuJetVeto[itr_file] = new TH1D(name,"",13,-6.5,6.5);
    
    sprintf(name,"h_dtRechitClusterSize_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSize_noMB1Veto[itr_file] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterSizeBarrel_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeBarrel_noMB1Veto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSizeMagnet_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeMagnet_noMB1Veto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSizeAll_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeAll_noMB1Veto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterNStation_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNStation_noMB1Veto[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNRechitsMB1_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNRechitsMB1_noMB1Veto[itr_file] = new TH1D(name,"",50,0,500);

    sprintf(name,"h_dtRechitClusterPercentRechitsMB1_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterPercentRechitsMB1_noMB1Veto[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_nRPCMatched_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatched_noMB1Veto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_nRPCMatchedLayer1_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatchedLayer1_noMB1Veto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_nRPCMatchedLayer2_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatchedLayer2_noMB1Veto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_nRPCMatchedLayer12_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_nRPCMatchedLayer12_noMB1Veto[itr_file] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_RPCMatchedBxSpread_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_RPCMatchedBxSpread_noMB1Veto[itr_file] = new TH1D(name,"",10,0,10);

    sprintf(name,"h_dtRechitClusterSizeBarrel_HOVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeBarrel_HOVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSizeMagnet_HOVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeMagnet_HOVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSizeAll_HOVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeAll_HOVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSizeBarrel_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeBarrel_fullHOVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSizeMagnet_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeMagnet_fullHOVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSizeAll_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeAll_fullHOVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsBarrel_noVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsBarrel_noVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsMagnet_noVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsMagnet_noVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsAll_noVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsAll_noVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsBarrel_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsBarrel_jetVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsMagnet_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsMagnet_jetVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsAll_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsAll_jetVeto[itr_file] = new TH1D(name,"",100,0,1000);
    
    sprintf(name,"h_nTotalClusteredRechitsBarrel_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsBarrel_MB1Veto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsMagnet_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsMagnet_MB1Veto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsAll_MB1Veto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsAll_MB1Veto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsBarrel_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsBarrel_noMB1Veto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsMagnet_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsMagnet_noMB1Veto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsAll_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsAll_noMB1Veto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsBarrel_HOVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsBarrel_HOVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsMagnet_HOVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsMagnet_HOVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsAll_HOVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsAll_HOVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsBarrel_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsBarrel_fullVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsMagnet_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsMagnet_fullVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsAll_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsAll_fullVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsBarrel_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsBarrel_fullHOVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsMagnet_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsMagnet_fullHOVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsAll_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsAll_fullHOVeto[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSize_RPCMatch_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSize_RPCMatch[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_dtRechitClusterSize_RPCSpread0_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSize_RPCSpread0[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsBarrel_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsBarrel_fullVetoPlus[itr_file] = new TH1D(name,"",100,0,1000);

    sprintf(name,"h_nTotalClusteredRechitsMagnet_fullHOVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_nTotalClusteredRechitsMagnet_fullHOVetoPlus[itr_file] = new TH1D(name,"",100,0,1000);
    
    sprintf(name,"h_dtRechitClusterXSpread_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterXSpread_fullVetoPlus[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterYSpread_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterYSpread_fullVetoPlus[itr_file] = new TH1D(name,"",40,0,400);

    sprintf(name,"h_dtRechitClusterZSpread_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterZSpread_fullVetoPlus[itr_file] = new TH1D(name,"",30,0,150);

    sprintf(name,"h_dtRechitClusterEtaSpread_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterEtaSpread_fullVetoPlus[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_dtRechitClusterPhiSpread_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterPhiSpread_fullVetoPlus[itr_file] = new TH1D(name,"",40,0,0.4);

    sprintf(name,"h_dtRechitClusterEta_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterEta_fullVetoPlus[itr_file] = new TH1D(name,"",60,-3,3);

    sprintf(name,"h_dtRechitClusterPhi_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterPhi_fullVetoPlus[itr_file] = new TH1D(name,"",70,-3.5,3.5);

    sprintf(name,"h_dtRechitClusterEtaPhi_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterEtaPhi_fullVetoPlus[itr_file] = new TH2D(name,"",70,-3.5,3.5,60,-3,3);

    sprintf(name,"h_dtRechitClusterNStation_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNStation_fullVetoPlus[itr_file] = new TH1D(name,"",4,0,4);

    sprintf(name,"h_dtRechitClusterNWheel_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNWheel_fullVetoPlus[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterNStation_fullHOVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNStation_fullHOVetoPlus[itr_file] = new TH1D(name,"",4,0,4);

    sprintf(name,"h_dtRechitClusterNWheel_fullHOVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterNWheel_fullHOVetoPlus[itr_file] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dtRechitClusterSizeRatio_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeRatio_fullVetoPlus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_dtRechitClusterSizeRatio_fullVetoMinus_%s_%s",mX[itr_mX],ctau);
    h_dtRechitClusterSizeRatio_fullVetoMinus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_HOMatchedEnergyCluster280Magnet_noMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_HOMatchedEnergyCluster280Magnet_noMB1Veto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_HOTime_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_HOTime_fullHOVeto[itr_file] = new TH1D(name,"",60,-60,60);

    sprintf(name,"h_muonPt_jetMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_muonPt_jetMB1Veto[itr_file] = new TH1D(name,"",50,0,100);

    sprintf(name,"h_jetPt_muonMB1Veto_%s_%s",mX[itr_mX],ctau);
    h_jetPt_muonMB1Veto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_MB1Rechits_jetMuonVeto_%s_%s",mX[itr_mX],ctau);
    h_MB1Rechits_jetMuonVeto[itr_file] = new TH1D(name,"",200,0,200);

    sprintf(name,"h_muonPt_jetHOVeto_%s_%s",mX[itr_mX],ctau);
    h_muonPt_jetHOVeto[itr_file] = new TH1D(name,"",50,0,100);

    sprintf(name,"h_jetPt_muonHOVeto_%s_%s",mX[itr_mX],ctau);
    h_jetPt_muonHOVeto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_HOEnergy_jetMuonVeto_%s_%s",mX[itr_mX],ctau);
    h_HOEnergy_jetMuonVeto[itr_file] = new TH1D(name,"",40,0,200);

    sprintf(name,"h_muonDR_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_muonDR_fullVeto[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_muonDR_RPCMatch_%s_%s",mX[itr_mX],ctau);
    h_muonDR_RPCMatch[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_muonDR_RPCSpread0_%s_%s",mX[itr_mX],ctau);
    h_muonDR_RPCSpread0[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetDR_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_jetDR_fullVeto[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetDR_RPCMatch_%s_%s",mX[itr_mX],ctau);
    h_jetDR_RPCMatch[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetDR_RPCSpread0_%s_%s",mX[itr_mX],ctau);
    h_jetDR_RPCSpread0[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_muonDR_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_muonDR_fullHOVeto[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_muonDR_HORPCMatch_%s_%s",mX[itr_mX],ctau);
    h_muonDR_HORPCMatch[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_muonDR_HORPCSpread0_%s_%s",mX[itr_mX],ctau);
    h_muonDR_HORPCSpread0[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetDR_fullHOVeto_%s_%s",mX[itr_mX],ctau);
    h_jetDR_fullHOVeto[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetDR_HORPCMatch_%s_%s",mX[itr_mX],ctau);
    h_jetDR_HORPCMatch[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetDR_HORPCSpread0_%s_%s",mX[itr_mX],ctau);
    h_jetDR_HORPCSpread0[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_decayVertexRadius_noVeto_%s_%s",mX[itr_mX],ctau);
    h_decayVertexRadius_noVeto[itr_file] = new TH1D(name,"",80,0,800);

    sprintf(name,"h_HOEnergy_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_HOEnergy_jetVeto[itr_file] = new TH1D(name,"",40,0,200);

    sprintf(name,"h_dRClusterRPC_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_dRClusterRPC_jetVeto[itr_file] = new TH1D(name,"",30,0,3);

    sprintf(name,"h_dRClusterHO_jetVeto_%s_%s",mX[itr_mX],ctau);
    h_dRClusterHO_jetVeto[itr_file] = new TH1D(name,"",30,0,3);

    sprintf(name,"h_jetDR_minDR_vetoJet_%s_%s",mX[itr_mX],ctau);
    h_jetDR_minDR_vetoJet[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetPt_minDR_vetoJet_%s_%s",mX[itr_mX],ctau);
    h_jetPt_minDR_vetoJet[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetEta_minDR_vetoJet_%s_%s",mX[itr_mX],ctau);
    h_jetEta_minDR_vetoJet[itr_file] = new TH1D(name,"",60,-3,3);

    sprintf(name,"h_jetPhi_minDR_vetoJet_%s_%s",mX[itr_mX],ctau);
    h_jetPhi_minDR_vetoJet[itr_file] = new TH1D(name,"",70,-3.5,3.5);

    sprintf(name,"h_jetChargedEMEnergyFracion_minDR_vetoJet_%s_%s",mX[itr_mX],ctau);
    h_jetChargedEMEnergyFraction_minDR_vetoJet[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetNeutralEMEnergyFracion_minDR_vetoJet_%s_%s",mX[itr_mX],ctau);
    h_jetNeutralEMEnergyFraction_minDR_vetoJet[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetChargedHadronEnergyFracion_minDR_vetoJet_%s_%s",mX[itr_mX],ctau);
    h_jetChargedHadronEnergyFraction_minDR_vetoJet[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetNeutralHadronEnergyFracion_minDR_vetoJet_%s_%s",mX[itr_mX],ctau);
    h_jetNeutralHadronEnergyFraction_minDR_vetoJet[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetDR_minDR_fullHOVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_jetDR_minDR_fullHOVetoPlus[itr_file] = new TH1D(name,"",20,0,2);

    sprintf(name,"h_jetPt_minDR_fullHOVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_jetPt_minDR_fullHOVetoPlus[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetEta_minDR_fullHOVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_jetEta_minDR_fullHOVetoPlus[itr_file] = new TH1D(name,"",60,-3,3);

    sprintf(name,"h_jetPhi_minDR_fullHOVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_jetPhi_minDR_fullHOVetoPlus[itr_file] = new TH1D(name,"",70,-3.5,3.5);

    sprintf(name,"h_jetChargedEMEnergyFracion_minDR_fullHOVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_jetChargedEMEnergyFraction_minDR_fullHOVetoPlus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetNeutralEMEnergyFracion_minDR_fullHOVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_jetNeutralEMEnergyFraction_minDR_fullHOVetoPlus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetChargedHadronEnergyFracion_minDR_fullHOVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_jetChargedHadronEnergyFraction_minDR_fullHOVetoPlus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_jetNeutralHadronEnergyFracion_minDR_fullHOVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_jetNeutralHadronEnergyFraction_minDR_fullHOVetoPlus[itr_file] = new TH1D(name,"",25,0,1);

    sprintf(name,"h_nWheels1_noCluster_%s_%s",mX[itr_mX],ctau);
    h_nWheels1_noCluster[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels150_noCluster_%s_%s",mX[itr_mX],ctau);
    h_nWheels150_noCluster[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels10_noCluster_%s_%s",mX[itr_mX],ctau);
    h_nWheels10_noCluster[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels20_noCluster_%s_%s",mX[itr_mX],ctau);
    h_nWheels20_noCluster[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels30_noCluster_%s_%s",mX[itr_mX],ctau);
    h_nWheels30_noCluster[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels50_noCluster_%s_%s",mX[itr_mX],ctau);
    h_nWheels50_noCluster[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels1_noVeto_%s_%s",mX[itr_mX],ctau);
    h_nWheels1_noVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels1_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_nWheels1_fullVetoPlus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels1_fullVetoMinus_%s_%s",mX[itr_mX],ctau);
    h_nWheels1_fullVetoMinus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels10_noVeto_%s_%s",mX[itr_mX],ctau);
    h_nWheels10_noVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels10_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_nWheels10_fullVetoPlus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels10_fullVetoMinus_%s_%s",mX[itr_mX],ctau);
    h_nWheels10_fullVetoMinus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels20_noVeto_%s_%s",mX[itr_mX],ctau);
    h_nWheels20_noVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels20_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_nWheels20_fullVetoPlus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels20_fullVetoMinus_%s_%s",mX[itr_mX],ctau);
    h_nWheels20_fullVetoMinus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels30_noVeto_%s_%s",mX[itr_mX],ctau);
    h_nWheels30_noVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels30_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_nWheels30_fullVetoPlus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels30_fullVetoMinus_%s_%s",mX[itr_mX],ctau);
    h_nWheels30_fullVetoMinus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels50_noVeto_%s_%s",mX[itr_mX],ctau);
    h_nWheels50_noVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels50_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_nWheels50_fullVetoPlus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels50_fullVetoMinus_%s_%s",mX[itr_mX],ctau);
    h_nWheels50_fullVetoMinus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels150_noVeto_%s_%s",mX[itr_mX],ctau);
    h_nWheels150_noVeto[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels150_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_nWheels150_fullVetoPlus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels150_fullVetoMinus_%s_%s",mX[itr_mX],ctau);
    h_nWheels150_fullVetoMinus[itr_file] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_jetPtMax_noVeto_%s_%s",mX[itr_mX],ctau);
    h_jetPtMax_noVeto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetPtMax_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_jetPtMax_fullVeto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetPtMax_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_jetPtMax_fullVetoPlus[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetPtMax_fullVetoMinus_%s_%s",mX[itr_mX],ctau);
    h_jetPtMax_fullVetoMinus[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetPtMET_noVeto_%s_%s",mX[itr_mX],ctau);
    h_jetPtMET_noVeto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetPtMET_fullVeto_%s_%s",mX[itr_mX],ctau);
    h_jetPtMET_fullVeto[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetPtMET_fullVetoPlus_%s_%s",mX[itr_mX],ctau);
    h_jetPtMET_fullVetoPlus[itr_file] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_jetPtMET_fullVetoMinus_%s_%s",mX[itr_mX],ctau);
    h_jetPtMET_fullVetoMinus[itr_file] = new TH1D(name,"",20,0,200);

    evtNum = 0;
    totalNum = 0;
    //weight = lumi*xSec*1000/treeReader.GetEntries(1);
    totalEvents=0;
    totalMagnetEvents=0;
    totalBarrelEvents=0;
    noEff=0.0;
    muonEff=0.0;
    jetEff=0.0;
    MB1Eff=0.0;
    HOEff=0.0;
    fullEff=0.0;
    fullHOEff=0.0;
    
    nPassMET=0;
    nPassDTDecay=0;
    nPassJetMET=0;
    nPassJetMET_top4=0;
    nPassJetMET_20=0;
    nPassJetMET_30=0;
    nPassJetMET_50=0;
    nPassNoVeto=0;
    nPassFullVeto=0;

    nPassMaxStation=0;
    nPassDeltaPhi=0;
    nPassRPCMatch=0;
    nPassRPCSpread=0;    
    
    nPassHODecay=0;
    nPassNoVeto_ho=0;
    nPassFullVeto_ho=0;
    nPassDeltaPhi_ho=0;
    nPassRPCMatch_ho=0;
    nPassRPCSpread_ho=0;        

    nPassMuon_std=0;
    nPassMB1_std=0;
    nPassMuon_alt=0;
    nPassMB1_alt=0;
    nPassJetMuon_std = 0;
    nPassJetMB1_std = 0;
    nPassFull_std = 0;
    nPassFull_altMuon = 0;
    nPassFull_altMB1 = 0;
    nPassFull_altMuonMB1 = 0;
    nPassFullDTPlus_noMuon = 0;
    nPassFullDTPlus_noMB1 = 0;
    nPassFullDTPlus_std = 0;
    nPassFullDTPlus_altMuon = 0;
    nPassFullDTPlus_altMB1 = 0;
    nPassFullDTPlus_altMuonMB1 = 0;

    cout << mX[itr_mX] << "_" << ctau << endl;
    for(Int_t itr_year = 0; itr_year<3; itr_year++){
    cout << "  " << years[itr_year] << endl;
         
      TFile *_file;
      if(strcmp(years[itr_year],"MC_Summer16")==0){
	_file = TFile::Open(dir+years[itr_year]+"/v1/v2/normalized/ggH_HToSSTobbbb_MH-125_MS-"+mX[itr_mX]+"_ctau-"+ctau+"_TuneCUETP8M1_13TeV-powheg-pythia8_1pb_weighted.root");
	//_file = TFile::Open(dir+years[itr_year]+"/v3/v5/normalized/ggH_HToSSTobbbb_MH-125_MS-"+mX[itr_mX]+"_ctau-"+ctau+"_TuneCUETP8M1_13TeV-powheg-pythia8_1pb_weighted.root");
      }
      else{
	_file = TFile::Open(dir+years[itr_year]+"/v1/v2/normalized/ggH_HToSSTobbbb_MH-125_MS-"+mX[itr_mX]+"_ctau-"+ctau+"_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root");
	//_file = TFile::Open(dir+years[itr_year]+"/v3/v5/normalized/ggH_HToSSTobbbb_MH-125_MS-"+mX[itr_mX]+"_ctau-"+ctau+"_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root");

      }
      /*if(strcmp(mX[itr_mX],"450")==0){
	_file = TFile::Open(dir+"/signal_1000_"+mX[itr_mX]+"_"+ctau+".root");
      }
      else{
	_file = TFile::Open(dir+"/signal_125_"+mX[itr_mX]+"_"+ctau+".root");
      }

      TTreeReader treeReader("ntuples/llp",_file);
      */
      TTreeReader treeReader("MuonSystem",_file);

      TTreeReaderArray<float> gLLP_dt(treeReader,"gLLP_dt");
      //TTreeReaderArray<bool> gLLP_dt(treeReader,"gLLP_dt");
      //TTreeReaderArray<float> gLLP_pt(treeReader,"gLLP_pt");
      TTreeReaderArray<float> gLLP_decay_vertex_x(treeReader,"gLLP_decay_vertex_x");
      TTreeReaderArray<float> gLLP_decay_vertex_y(treeReader,"gLLP_decay_vertex_y");
      TTreeReaderArray<float> gLLP_decay_vertex_z(treeReader,"gLLP_decay_vertex_z");
      //TTreeReaderArray<float> gLLP_travel_time(treeReader,"gLLP_travel_time");

      //TTreeReaderValue<float> weight(treeReader,"weight");
      //TTreeReaderValue<unsigned int> npv(treeReader,"npv");
      TTreeReaderValue<float> MET(treeReader,"met");
      TTreeReaderValue<float> METphi(treeReader,"metPhi");
      //TTreeReaderValue<float> jetMet_dPhiMin4(treeReader,"jetMet_dPhiMin4");
    
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
      /*TTreeReaderArray<float> jetChargedEMEnergyFraction(treeReader,"jetChargedEMEnergyFraction");
      TTreeReaderArray<float> jetNeutralEMEnergyFraction(treeReader,"jetNeutralEMEnergyFraction");
      TTreeReaderArray<float> jetNeutralHadronEnergyFraction(treeReader,"jetNeutralHadronEnergyFraction");
      TTreeReaderArray<float> jetChargedHadronEnergyFraction(treeReader,"jetChargedHadronEnergyFraction");
      */
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

      totalNum += treeReader.GetEntries(1);
      _ofile->cd();
      while(treeReader.Next()){
	fill_n(rechitCount, 5, 0);
	hitWheels1 = 0;
	hitWheels10 = 0;
	hitWheels20 = 0;
	hitWheels30 = 0;
	hitWheels50 = 0;
	hitWheels150 = 0;
	goodEvt = false;
	goodDecay = false;
	magnetDecay = false;
	clustSizeMax = 0.;
	dPhi_min = -999.;
	jetPt_tmp = 0.0;
	dPhi_minTop4 = -999.;
	dPhi_min20 = -999.;
	dPhi_min30 = -999.;
	dPhi_min50 = -999.;
	if(evtNum%100000==0){ cout << evtNum << " of " << totalNum << endl; }
      
	for(Int_t itr_llp=0; itr_llp<2; itr_llp++){
	  if(gLLP_decay_vertex_z[itr_llp] < 650.){
	    h_decayVertexRadius_noVeto[itr_file]->Fill(sqrt(pow(gLLP_decay_vertex_x[itr_llp],2)+pow(gLLP_decay_vertex_y[itr_llp],2)));
	  }
	}
	if(gLLP_dt[0] || gLLP_dt[1]){ goodDecay = true; }
	else if(sqrt(pow(gLLP_decay_vertex_x[0],2)+pow(gLLP_decay_vertex_y[0],2)) < 400. && sqrt(pow(gLLP_decay_vertex_x[0],2)+pow(gLLP_decay_vertex_y[0],2)) > 300. && abs(gLLP_decay_vertex_z[0]) < 650.){ magnetDecay = true; }
	else if(sqrt(pow(gLLP_decay_vertex_x[1],2)+pow(gLLP_decay_vertex_y[0],2)) < 400. && sqrt(pow(gLLP_decay_vertex_x[1],2)+pow(gLLP_decay_vertex_y[1],2)) > 300. && abs(gLLP_decay_vertex_z[1]) < 650.){ magnetDecay = true; }
	if(*MET > 200){ 
	  //nPassMET += lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1);
	  nPassMET += 1;
	}
	if(*MET > 200){
	  //nPassDTDecay += lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1);
	  nPassDTDecay += 1;
	  passNoVeto = false;
	  passFullVeto = false;
	  passRPCMatch = false;
	  passRPCSpread = false;
	  passMaxStation = false;
	  passDeltaPhi = false;
	  passFullVeto_ho = false;
	  passRPCMatch_ho = false;
	  passRPCSpread_ho = false;
	  passDeltaPhi_ho = false;
	  passMuonEvent_std=false;
	  passMB1Event_std=false;
	  passMuonEvent_alt=false;
	  passMB1Event_alt=false;
	  passJetMB1_std=false;
	  passJetMuon_std=false;
	  passFull_std = false;
	  passFull_altMuon = false;
	  passFull_altMB1 = false;
	  passFull_altMuonMB1 = false;
	  passFullDTPlus_noMuon = false;
	  passFullDTPlus_noMB1 = false;
	  passFullDTPlus_std = false;
	  passFullDTPlus_altMuon = false;
	  passFullDTPlus_altMB1 = false;
	  passFullDTPlus_altMuonMB1 = false;	      
	  passJetMET = false;
	  passJetMET_20 = false;
	  passJetMET_30 = false;
	  passJetMET_50 = false;
	  passJetMET_top4 = false;
	  nPassMuon = 0;
	  nPassJet = 0;
	  nPassJetMuon = 0;
	  nPassMB1 = 0;
	  nPassHO = 0;
	  nPassFull = 0;
	  nPassFullHO = 0;
	  nPassNone = 0;
	  nPassFullPlus = 0;
	  nPassFullMinus = 0;
	  totalSumE=0.0;
	  totalBarrelEvents+=1;
	  totalClusteredNone = 0;
	  totalClusteredNoMB1 = 0;
	  totalClusteredJet = 0;
	  totalClusteredMB1 = 0;
	  totalClusteredHO = 0;
	  totalClusteredFull = 0;
	  totalClusteredFullHO = 0;
	  totalClusteredFullPlus = 0;
	  dPhiClusterMET_max = -1.;
	  for(Int_t itr_clust = 0; itr_clust<*nDtRechitClusters; itr_clust++){
	    dPhiClusterMET = dtRechitClusterPhi[itr_clust] - *METphi;
	    if(dPhiClusterMET > TMath::Pi()){ dPhiClusterMET -= 2*TMath::Pi(); }
	    if(dPhiClusterMET < -1.0*TMath::Pi()){ dPhiClusterMET += 2*TMath::Pi(); }
	    if(fabs(dPhiClusterMET)>dPhiClusterMET_max){ dPhiClusterMET_max=fabs(dPhiClusterMET); }
	  }
	  //h_jetMet_dPhiMin4[itr_file]->Fill(*jetMet_dPhiMin4);
	  if(*nJets>0){
	    goodJets=0;
	    for(Int_t itr_jet = 0; itr_jet<*nJets; itr_jet++){
	      if(fabs(jetEta[itr_jet])<3.0){
		dPhi_tmp = jetPhi[itr_jet] - *METphi;
		if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
		if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
		if(fabs(dPhi_tmp) < fabs(dPhi_min)){ 
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
	  if(fabs(dPhi_minTop4)!=999.){ h_dPhiJetMET[itr_file]->Fill(fabs(dPhi_min)); }
	  if(fabs(dPhi_min)>0.6){ passJetMET += true; }
	  if(fabs(dPhi_min20)>0.6){ passJetMET_20 += true; }
	  if(fabs(dPhi_min30)>0.6){ passJetMET_30 += true; }
	  if(fabs(dPhi_min50)>0.6){ passJetMET_50 += true; }
	  if(fabs(dPhi_minTop4)>0.6){ passJetMET_top4 += true; }
	  if(fabs(dPhi_minTop4)>0.0){
	    //if(fabs(dPhiClusterMET_max)<1.0){
	    //nPassJetMET += lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1); 
	    //nPassJetMET_top4 += 1;
	    h_MET[itr_file]->Fill(*MET);
	    h_jetPt[itr_file]->Fill(jetPt_tmp);

	    if(*nDtRechits<1000){
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

	    if(*nDtRechitClusters > 0){ passNoVeto = true; }
	    for(Int_t itr_clust = 0; itr_clust<*nDtRechitClusters; itr_clust++){
	      match = 0;
	      matchLayer1 = 0;
	      matchLayer2 = 0;
	      matchLayer3 = 0;
	      matchLayer4 = 0;
	      matchHO = 0;
	      fill_n(stationCount, 4, 0);
	      nStationUnclustered = 0;
	      nThreshStation = 0;
	      nThreshLowStation = 0;	      
	      nThreshStationUnclustered = 0;
	      nThreshLowStationUnclustered = 0;	      
	      sumE = 0;
	      weightT = 0;
	      rpcBx.clear();
	      rpcLayer.clear();
	      zWheel.clear();
	      matchJet = false;
	      matchMuon = false;
	      goodEvt = true;
	      passMuon = false;
	      passMuon_alt = false;
	      passMB1_alt = false;
	      passJet = false;
	      passMB1 = false;
	      passHO = false;
	      passInvertedJet = false;
	      passInvertedMuon = false;
	      passInvertedMuJet = false;
	      llp_itr = -1;

	      if(sqrt(pow(gLLP_decay_vertex_x[0]-dtRechitClusterX[itr_clust],2)+pow(gLLP_decay_vertex_y[0]-dtRechitClusterY[itr_clust],2)+pow(gLLP_decay_vertex_z[0]-dtRechitClusterZ[itr_clust],2)) < sqrt(pow(gLLP_decay_vertex_x[1]-dtRechitClusterX[itr_clust],2)+pow(gLLP_decay_vertex_y[1]-dtRechitClusterY[itr_clust],2)+pow(gLLP_decay_vertex_z[1]-dtRechitClusterZ[itr_clust],2))){ llp_itr = 0; }
	      else{ llp_itr = 1; }

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

	      if(dtRechitClusterSize[itr_clust]>50){

		nPassNone+=1;
		noEff+=1.0;
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
		    //h_jetChargedEMEnergyFraction_minDR_vetoJet[itr_file]->Fill(jetChargedEMEnergyFraction[itr]);
		    //h_jetNeutralEMEnergyFraction_minDR_vetoJet[itr_file]->Fill(jetNeutralEMEnergyFraction[itr]);
		    //h_jetChargedHadronEnergyFraction_minDR_vetoJet[itr_file]->Fill(jetChargedHadronEnergyFraction[itr]);
		    //h_jetNeutralHadronEnergyFraction_minDR_vetoJet[itr_file]->Fill(jetNeutralHadronEnergyFraction[itr]);
		  }
		}

		if(dtRechitClusterNSegmentStation2[itr_clust]>12){ nThreshStation+=1; }
		if(dtRechitClusterNSegmentStation3[itr_clust]>12){ nThreshStation+=1; }
		if(dtRechitClusterNSegmentStation4[itr_clust]>8){ nThreshStation+=1; }

		if(dtRechitClusterNSegmentStation2[itr_clust]>4){ nThreshLowStation+=1; }
		if(dtRechitClusterNSegmentStation3[itr_clust]>4){ nThreshLowStation+=1; }
		if(dtRechitClusterNSegmentStation4[itr_clust]>2){ nThreshLowStation+=1; }

		dPhiClusterMET = dtRechitClusterPhi[itr_clust] - *METphi;
		if(dPhiClusterMET > TMath::Pi()){ dPhiClusterMET -= 2*TMath::Pi(); }
		if(dPhiClusterMET < -1.0*TMath::Pi()){ dPhiClusterMET += 2*TMath::Pi(); }
		if(fabs(dPhiClusterMET)>dPhiClusterMET_max){ dPhiClusterMET_max=fabs(dPhiClusterMET); }

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
		  muonEff+=1.0;
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
		  jetEff+=1.0;
		  totalClusteredJet+=dtRechitClusterSize[itr_clust];
		  h_dtRechitClusterSize_jetVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		  h_dtRechitClusterSizeBarrel_jetVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		  h_dtRechitClusterMaxStation_jetVeto[itr_file]->Fill(dtRechitClusterMaxStation[itr_clust]);
		  h_dtRechitClusterNStation_jetVeto[itr_file]->Fill(dtRechitClusterNStation[itr_clust]);
		  h_dPhiClusterMET_jetVeto[itr_file]->Fill(fabs(dPhiClusterMET));
		  h_dtRechitClusterXSpread_jetVeto[itr_file]->Fill(dtRechitClusterXSpread[itr_clust]);
		  h_dtRechitClusterYSpread_jetVeto[itr_file]->Fill(dtRechitClusterYSpread[itr_clust]);
		  h_dtRechitClusterZSpread_jetVeto[itr_file]->Fill(dtRechitClusterZSpread[itr_clust]);
		  h_dtRechitClusterEtaSpread_jetVeto[itr_file]->Fill(dtRechitClusterEtaSpread[itr_clust]);
		  h_dtRechitClusterPhiSpread_jetVeto[itr_file]->Fill(dtRechitClusterPhiSpread[itr_clust]);
		  h_nRPCMatched_jetVeto[itr_file]->Fill(match);
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
		  MB1Eff+=1.0;
		  totalClusteredMB1+=dtRechitClusterSize[itr_clust];
		  h_dtRechitClusterSize_MB1Veto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		  h_dtRechitClusterSizeBarrel_MB1Veto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
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

		if(passInvertedJet && passMB1){
		  if(!rpcBx.empty()){
		    for(Int_t itr = 0; itr<rpcBx.size(); itr++){
		      h_RPCMatchedBx_invertedJetVeto[itr_file]->Fill(rpcBx[itr]);
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

		if(passInvertedJet && passInvertedMuon && passMB1){
		  //cout << "inverted mu jet" << endl;
		  if(!rpcBx.empty()){
		    for(Int_t itr = 0; itr<rpcBx.size(); itr++){
		      h_RPCMatchedBx_invertedMuJetVeto[itr_file]->Fill(rpcBx[itr]);
		    }
		  }
		}
		//cout << "done inverted" << endl;

		if(passMuon && passJet){
		  //cout  << "no MB1" << endl;
		  nPassJetMuon+=1;
		  totalClusteredNoMB1+=dtRechitClusterSize[itr_clust];
		  h_dtRechitClusterSize_noMB1Veto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		  h_dtRechitClusterSizeBarrel_noMB1Veto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		  h_dtRechitClusterNRechitsMB1_noMB1Veto[itr_file]->Fill(dtRechitClusterNSegmentStation1[itr_clust]);
		  h_dtRechitClusterPercentRechitsMB1_noMB1Veto[itr_file]->Fill(float(dtRechitClusterNSegmentStation1[itr_clust]) / dtRechitClusterSize[itr_clust]);
		  h_dtRechitClusterNStation_noMB1Veto[itr_file]->Fill(dtRechitClusterNStation[itr_clust]);
		  h_nRPCMatched_noMB1Veto[itr_file]->Fill(match);
		  h_MB1Rechits_jetMuonVeto[itr_file]->Fill(dtRechitClusterNSegmentStation1[itr_clust]);
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
		}
		//cout << "done no MB1" << endl;

		if(passMuon && passJet && passMB1){
		  passFullVeto = true;
		  nPassFull+=1;
		  fullEff+=1.0;

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
		  h_dtRechitClusterSizeBarrel_fullVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		  h_dtRechitClusterMaxStation_fullVeto[itr_file]->Fill(dtRechitClusterMaxStation[itr_clust]);
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
		
		  h_dtRechitClusterNWheels1_fullVeto[itr_file]->Fill(dtRechitClusterNChamber[itr_clust]);
		  h_dtRechitClusterMaxWheel_fullVeto[itr_file]->Fill(dtRechitClusterMaxChamber[itr_clust]);
		
		  //h_gLLP_travel_time_fullVeto[itr_file]->Fill(gLLP_travel_time[llp_itr]);
		  //h_gLLPpt_fullVeto[itr_file]->Fill(gLLP_pt[llp_itr]);
		  if(!rpcBx.empty()){
		    rpcMean = accumulate(rpcBx.begin(), rpcBx.end(), 0.0) / rpcBx.size();
		    //if(abs(rpcMean)<0.5){ h_gLLPpt_Bx0_fullVeto[itr_file]->Fill(gLLP_pt[llp_itr]); }
		    //else if(rpcMean < 1.5){ h_gLLPpt_Bx1_fullVeto[itr_file]->Fill(gLLP_pt[llp_itr]); }
		    rpcSpread = max_element(rpcBx.begin(), rpcBx.end()) - min_element(rpcBx.begin(), rpcBx.end());
		    for(Int_t itr = 0; itr<rpcBx.size(); itr++){
		      h_RPCMatchedBx_fullVeto[itr_file]->Fill(rpcBx[itr]);
		      if(rpcSpread==0){ h_RPCMatchedBx_Spread0_fullVeto[itr_file]->Fill(rpcBx[itr]); }
		    }
		    h_RPCMatchedBxSpread_fullVeto[itr_file]->Fill(rpcSpread);
		    if(rpcSpread==0){ h_nRPCMatched_Spread0_fullVeto[itr_file]->Fill(match); }  
		  }

		  h_muonDR_fullVeto[itr_file]->Fill(muonDR_min);
		  h_jetDR_fullVeto[itr_file]->Fill(jetDR_min);
		
		  if(!rpcBx.empty()){
		    passRPCMatch = true;
		    h_dtRechitClusterSize_RPCMatch[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		    h_muonDR_RPCMatch[itr_file]->Fill(muonDR_min);
		    h_jetDR_RPCMatch[itr_file]->Fill(jetDR_min);
		    if(rpcSpread==0){
		      passRPCSpread = true;
		      h_dtRechitClusterSize_RPCSpread0[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		      h_muonDR_RPCSpread0[itr_file]->Fill(muonDR_min);
		      h_jetDR_RPCSpread0[itr_file]->Fill(jetDR_min);
		      if(dtRechitClusterMaxStation[itr_clust]>2){
			passMaxStation = true;
			if(fabs(dPhiClusterMET)<1){
			  passDeltaPhi = true;
			  nPassFullPlus+=1;
			  nPassFullMinus+=1;
			  totalClusteredFullPlus+=dtRechitClusterSize[itr_clust];
			  h_dtRechitClusterXSpread_fullVetoPlus[itr_file]->Fill(dtRechitClusterXSpread[itr_clust]);
			  h_dtRechitClusterYSpread_fullVetoPlus[itr_file]->Fill(dtRechitClusterYSpread[itr_clust]);
			  h_dtRechitClusterZSpread_fullVetoPlus[itr_file]->Fill(dtRechitClusterZSpread[itr_clust]);
			  h_dtRechitClusterEtaSpread_fullVetoPlus[itr_file]->Fill(dtRechitClusterEtaSpread[itr_clust]);
			  h_dtRechitClusterPhiSpread_fullVetoPlus[itr_file]->Fill(dtRechitClusterPhiSpread[itr_clust]);
			  h_dtRechitClusterPhi_fullVetoPlus[itr_file]->Fill(dtRechitClusterPhi[itr_clust]);
			  h_dtRechitClusterEta_fullVetoPlus[itr_file]->Fill(dtRechitClusterEta[itr_clust]);
			  h_dtRechitClusterEtaPhi_fullVetoPlus[itr_file]->Fill(dtRechitClusterPhi[itr_clust],dtRechitClusterEta[itr_clust]);
			  h_dtRechitClusterNStation_fullVetoPlus[itr_file]->Fill(dtRechitClusterNStation[itr_clust]);		
			  h_dtRechitClusterNWheel_fullVetoPlus[itr_file]->Fill(dtRechitClusterNChamber[itr_clust]);
			  //h_dtRechitClusterSizeRatio_fullVetoPlus[itr_file]->Fill(dtRechitClusterSize[itr_clust] / float(*nDtRechits));
			}
		      }
		    }
		  }

		}

		if(passMuon && passJet){
		  passJetMuon_std=true;
		  if(passMB1_alt){
		    passFull_altMB1=true;
		  }
		  if(!rpcBx.empty() && rpcSpread==0 && dtRechitClusterMaxStation[itr_clust]>2 && fabs(dPhiClusterMET)<1){
		    passFullDTPlus_noMB1=true;
		    if(passMB1_alt){
		      passFullDTPlus_altMB1=true;
		    }
		  }
		}
		if(passMB1 && passJet){
		  passJetMB1_std=true;
		  if(passMuon_alt){
		    passFull_altMuon=true;
		  }
		  if(!rpcBx.empty() && rpcSpread==0 && dtRechitClusterMaxStation[itr_clust]>2 && fabs(dPhiClusterMET)<1){
		    passFullDTPlus_noMuon=true;
		    if(passMuon_alt){
		      passFullDTPlus_altMuon=true;
		    }
		  }
		}
		if(passMuon_alt){
		  passMuonEvent_alt=true;
		  if(passJet && passMB1_alt){
		    passFull_altMuonMB1=true;
		    if(!rpcBx.empty()){
		      if(rpcSpread==0){
			if(dtRechitClusterMaxStation[itr_clust]>2){
			  if(fabs(dPhiClusterMET)<1){
			    passFullDTPlus_altMuonMB1=true;
			  }
			}
		      }
		    }
		  }
		}
		if(passMB1_alt){
		  passMB1Event_alt=true;
		}
		if(passMuon){
		  passMuonEvent_std=true;
		}
		if(passMB1){
		  passMB1Event_std=true;
		  if(passJet && passMuon){
		    passFull_std=true;
		    if(!rpcBx.empty()){
		      if(rpcSpread==0){
			if(dtRechitClusterMaxStation[itr_clust]>2){
			  if(fabs(dPhiClusterMET)<1){
			    passFullDTPlus_std=true;
			  }
			}
		      }
		    }
		  }
		}
		
		if(passHO){ 
		  nPassHO+=1;
		  totalClusteredHO+=dtRechitClusterSize[itr_clust];
		  h_dtRechitClusterSizeBarrel_HOVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		}
		/*if(passMuon && passJet && passHO){ 
		  nPassFullHO+=1; 
		  totalClusteredFullHO+=dtRechitClusterSize[itr_clust];
		  h_dtRechitClusterSizeBarrel_fullHOVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);   
		  }*/

		if(passMuon && passMB1){
		  h_jetPt_muonMB1Veto[itr_file]->Fill(jetPt_max);
		}

		if(passJet && passMB1){
		  h_muonPt_jetMB1Veto[itr_file]->Fill(muonPt_max);
		}
		if(passJet && passMuon && passHO){ 
		  passFullVeto_ho = true;
		  nPassFullHO+=1; 
		  totalClusteredFullHO+=dtRechitClusterSize[itr_clust];
		  h_dtRechitClusterSizeMagnet_fullHOVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);	      
		  h_dtRechitClusterMaxStation_fullHOVeto[itr_file]->Fill(dtRechitClusterMaxStation[itr_clust]);
		  h_nRPCMatched_fullHOVeto[itr_file]->Fill(match);
		  h_RPCMatchedBxSpread_fullHOVeto[itr_file]->Fill(rpcSpread);
		  h_dPhiClusterMET_fullHOVeto[itr_file]->Fill(fabs(dPhiClusterMET));
		  h_HOTime_fullHOVeto[itr_file]->Fill(weightT/sumE);
		
		  h_muonDR_fullHOVeto[itr_file]->Fill(muonDR_min);
		  h_jetDR_fullHOVeto[itr_file]->Fill(jetDR_min);

		  h_nRPCMatchedMagnetLayer1_fullHOVeto[itr_file]->Fill(matchLayer1);
		  h_nRPCMatchedMagnetLayer2_fullHOVeto[itr_file]->Fill(matchLayer2);
		  h_nRPCMatchedMagnetLayer3_fullHOVeto[itr_file]->Fill(matchLayer3);
		  h_nRPCMatchedMagnetLayer4_fullHOVeto[itr_file]->Fill(matchLayer4);

		  if(!rpcBx.empty()){
		    passRPCMatch_ho = true;
		    h_muonDR_HORPCMatch[itr_file]->Fill(muonDR_min);
		    h_jetDR_HORPCMatch[itr_file]->Fill(jetDR_min);
		    if(rpcSpread==0){
		      passRPCSpread_ho = true;
		      h_muonDR_HORPCSpread0[itr_file]->Fill(muonDR_min);
		      h_jetDR_HORPCSpread0[itr_file]->Fill(jetDR_min);
		      if(fabs(dPhiClusterMET)<1){
			passDeltaPhi_ho = true;
			totalClusteredFullHOPlus+=dtRechitClusterSize[itr_clust];
			h_dtRechitClusterNStation_fullHOVetoPlus[itr_file]->Fill(dtRechitClusterNStation[itr_clust]);		
			h_dtRechitClusterNWheel_fullHOVetoPlus[itr_file]->Fill(dtRechitClusterNChamber[itr_clust]);
			h_jetDR_minDR_fullHOVetoPlus[itr_file]->Fill(jetDR_min);
			h_jetPt_minDR_fullHOVetoPlus[itr_file]->Fill(jetPt[jetDR_index]);
			h_jetEta_minDR_fullHOVetoPlus[itr_file]->Fill(jetEta[jetDR_index]);
			h_jetPhi_minDR_fullHOVetoPlus[itr_file]->Fill(jetPhi[jetDR_index]);
			//h_jetChargedEMEnergyFraction_minDR_fullHOVetoPlus[itr_file]->Fill(jetChargedEMEnergyFraction[jetDR_index]);
			//h_jetNeutralEMEnergyFraction_minDR_fullHOVetoPlus[itr_file]->Fill(jetNeutralEMEnergyFraction[jetDR_index]);
			//h_jetChargedHadronEnergyFraction_minDR_fullHOVetoPlus[itr_file]->Fill(jetChargedHadronEnergyFraction[jetDR_index]);
			//h_jetNeutralHadronEnergyFraction_minDR_fullHOVetoPlus[itr_file]->Fill(jetNeutralHadronEnergyFraction[jetDR_index]);
		      }
		    }
		  }
		}
	      }
	    }
	    if(passFullVeto_ho){ nPassFullVeto_ho += 1; }//lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1); }
	    if(passRPCMatch_ho){ nPassRPCMatch_ho += 1; }//lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1); }
	    if(passRPCSpread_ho){ nPassRPCSpread_ho += 1; }//lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1); }
	    if(passDeltaPhi_ho){ nPassDeltaPhi_ho += 1; }//lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1); }

	    if(passNoVeto){ nPassNoVeto += 1; }//lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1); }
	    if(passFullVeto){ nPassFullVeto += 1; }//lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1); }
	    if(passRPCMatch){ nPassRPCMatch += 1; }//lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1); }
	    if(passRPCSpread){ nPassRPCSpread += 1; }//lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1); }
	    if(passMaxStation){ nPassMaxStation += 1; }//lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1); }
	    if(passDeltaPhi){ nPassDeltaPhi += 1; }//lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1); }
	    
	    if(passJetMuon_std){ nPassJetMuon_std += 1; }
	    if(passJetMB1_std){ nPassJetMB1_std += 1; }
	    if(passMuonEvent_std){ nPassMuon_std += 1; }
	    if(passMB1Event_std){ nPassMB1_std += 1; }
	    if(passMuonEvent_alt){ nPassMuon_alt += 1; }
	    if(passMB1Event_alt){ nPassMB1_alt += 1; }
	    if(passFull_std){ nPassFull_std += 1; }
	    if(passFull_altMuon){ nPassFull_altMuon += 1; }
	    if(passFull_altMB1){ nPassFull_altMB1 += 1; }
	    if(passFull_altMuonMB1){ nPassFull_altMuonMB1 += 1; }
	    if(passFullDTPlus_noMuon){ nPassFullDTPlus_noMuon += 1; }
	    if(passFullDTPlus_noMB1){ nPassFullDTPlus_noMB1 += 1; }
	    if(passFullDTPlus_std){ 
	      nPassFullDTPlus_std += 1; 
	      if(passJetMET){ nPassJetMET += 1; }
	      if(passJetMET_20){ nPassJetMET_20 += 1; }
	      if(passJetMET_30){ nPassJetMET_30 += 1; }
	      if(passJetMET_50){ nPassJetMET_50 += 1; }
	      if(passJetMET_top4){ nPassJetMET_top4 += 1; }
	    }
	    if(passFullDTPlus_altMuon){ nPassFullDTPlus_altMuon += 1; }
	    if(passFullDTPlus_altMB1){ nPassFullDTPlus_altMB1 += 1; }
	    if(passFullDTPlus_altMuonMB1){ nPassFullDTPlus_altMuonMB1 += 1; }

	    h_nDtRechitClusters_noVeto[itr_file]->Fill(nPassNone);
	    h_nDtRechitClusters_muonVeto[itr_file]->Fill(nPassMuon);
	    h_nDtRechitClusters_jetVeto[itr_file]->Fill(nPassJet);
	    h_nDtRechitClusters_MB1Veto[itr_file]->Fill(nPassMB1);
	    h_nDtRechitClusters_fullVeto[itr_file]->Fill(nPassFull);
	 
	    if(nPassNone>0){ 
	      h_dPhiJetMETBarrel_noVeto[itr_file]->Fill(dPhi_min); 
	      h_nWheels1_noVeto[itr_file]->Fill(hitWheels1);
	      h_nWheels10_noVeto[itr_file]->Fill(hitWheels10);
	      h_nWheels20_noVeto[itr_file]->Fill(hitWheels20);
	      h_nWheels30_noVeto[itr_file]->Fill(hitWheels30);
	      h_nWheels50_noVeto[itr_file]->Fill(hitWheels50);
	      h_nWheels150_noVeto[itr_file]->Fill(hitWheels150);
	      h_jetPtMET_noVeto[itr_file]->Fill(jetPt_tmp);
	      h_jetPtMax_noVeto[itr_file]->Fill(jetPt[0]);
	    }
	    if(nPassMuon>0){ h_dPhiJetMETBarrel_muonVeto[itr_file]->Fill(dPhi_min); }
	    if(nPassJet>0){ h_dPhiJetMETBarrel_jetVeto[itr_file]->Fill(dPhi_min); }
	    if(nPassMB1>0){ h_dPhiJetMETBarrel_MB1Veto[itr_file]->Fill(dPhi_min); }
	    if(nPassJetMuon>0){ h_dPhiJetMETBarrel_noMB1Veto[itr_file]->Fill(dPhi_min); }
	    if(nPassFull>0){ 
	      h_dPhiJetMETBarrel_fullVeto[itr_file]->Fill(dPhi_min); 
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
	    //h_npv_nDtRechitClusters_noVeto[itr_file]->Fill(*npv,nPassNone);
	    //h_npv_nDtRechitClusters_fullVeto[itr_file]->Fill(*npv,nPassFull);
	    h_nTotalClusteredRechitsBarrel_noVeto[itr_file]->Fill(totalClusteredNone);
	    h_nTotalClusteredRechitsBarrel_jetVeto[itr_file]->Fill(totalClusteredJet);
	    h_nTotalClusteredRechitsBarrel_MB1Veto[itr_file]->Fill(totalClusteredMB1);
	    h_nTotalClusteredRechitsBarrel_noMB1Veto[itr_file]->Fill(totalClusteredNoMB1);
	    h_nTotalClusteredRechitsBarrel_HOVeto[itr_file]->Fill(totalClusteredHO);
	    h_nTotalClusteredRechitsBarrel_fullVeto[itr_file]->Fill(totalClusteredFull);
	    h_nTotalClusteredRechitsBarrel_fullHOVeto[itr_file]->Fill(totalClusteredFullHO);
	  
	    h_dPhiClusterMETMax[itr_file]->Fill(dPhiClusterMET_max);

	    h_nTotalClusteredRechitsBarrel_fullVetoPlus[itr_file]->Fill(totalClusteredFullPlus);
	  }
	}

	/*if(*MET>200 && magnetDecay){
	  nPassHODecay+=1;
	  totalMagnetEvents+=1;
	  passNoVeto = false;
	  passFullVeto = false;
	  passRPCMatch = false;
	  passRPCSpread = false;
	  passMaxStation = false;
	  passDeltaPhi = false;
	  nPassMuon = 0;
	  nPassJet = 0;
	  nPassJetMuon = 0;
	  nPassMB1 = 0;
	  nPassHO = 0;
	  nPassFull = 0;
	  nPassFullHO = 0;
	  nPassNone = 0;
	  goodJets=0;
	  totalSumE=0.0;
	  totalClusteredNone = 0;
	  totalClusteredNoMB1 = 0;
	  totalClusteredJet = 0;
	  totalClusteredMB1 = 0;
	  totalClusteredHO = 0;
	  totalClusteredFull = 0;
	  totalClusteredFullHO = 0;
	  totalClusteredFullHOPlus = 0;
	  dPhiClusterMET_max = -1.;
	  for(Int_t itr_clust = 0; itr_clust<*nDtRechitClusters; itr_clust++){
	    dPhiClusterMET = dtRechitClusterPhi[itr_clust] - *METphi;
	    if(dPhiClusterMET > TMath::Pi()){ dPhiClusterMET -= 2*TMath::Pi(); }
	    if(dPhiClusterMET < -1.0*TMath::Pi()){ dPhiClusterMET += 2*TMath::Pi(); }
	    if(fabs(dPhiClusterMET)>dPhiClusterMET_max){ dPhiClusterMET_max=fabs(dPhiClusterMET); }
	  }
	  for(Int_t itr_jet = 0; itr_jet<*nJets; itr_jet++){
	    if(fabs(jetEta[itr_jet])<3.0 && jetPt[itr_jet]>20.0){
	      dPhi_tmp = jetPhi[itr_jet] - *METphi;
	      if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
	      if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
	      if(fabs(dPhi_tmp) < dPhi_min){ 
		dPhi_min = fabs(dPhi_tmp); 
		jetPt_tmp = jetPt[itr_jet];
	      }
	      goodJets+=1;
	      if(goodJets==4){ break; }
	    }
	  }
	  h_dPhiJetMETMagnet[itr_file]->Fill(fabs(dPhi_min));
	  if(fabs(dPhi_min)>0.6){
	    //if(fabs(dPhiClusterMET_max)<1.0){
	    nPassJetMET+=1;
	    for(Int_t itr_clust = 0; itr_clust<*nDtRechitClusters; itr_clust++){
	      match = 0;
	      matchLayer1 = 0;
	      matchLayer2 = 0;
	      matchLayer3 = 0;
	      matchLayer4 = 0;
	      matchHO = 0;
	      sumE = 0;
	      weightT = 0;
	      rpcBx.clear();
	      rpcLayer.clear();
	      zWheel.clear();
	      matchJet = false;
	      matchMuon = false;
	      goodEvt = true;
	      passMuon = false;
	      passJet = false;
	      passMB1 = false;
	      passHO = false;
	      passInvertedJet = false;
	      passInvertedMuon = false;
	      passInvertedMuJet = false;
	      llp_itr = -1;
	    
	      passNoVeto = true;

	      if(sqrt(pow(gLLP_decay_vertex_x[0]-dtRechitClusterX[itr_clust],2)+pow(gLLP_decay_vertex_y[0]-dtRechitClusterY[itr_clust],2)+pow(gLLP_decay_vertex_z[0]-dtRechitClusterZ[itr_clust],2)) < sqrt(pow(gLLP_decay_vertex_x[1]-dtRechitClusterX[itr_clust],2)+pow(gLLP_decay_vertex_y[1]-dtRechitClusterY[itr_clust],2)+pow(gLLP_decay_vertex_z[1]-dtRechitClusterZ[itr_clust],2))){ llp_itr = 0; }
	      else{ llp_itr = 1; }

	      dPhiClusterMET = dtRechitClusterPhi[itr_clust] - *METphi;
	      if(dPhiClusterMET > TMath::Pi()){ dPhiClusterMET -= 2*TMath::Pi(); }
	      if(dPhiClusterMET < -1.0*TMath::Pi()){ dPhiClusterMET += 2*TMath::Pi(); }
	    
	      if(dtRechitClusterJetVetoPt[itr_clust]<20.){ passJet = true; }
	      else{ passInvertedJet = true; }
	      if(dtRechitClusterMuonVetoPt[itr_clust]<10.){ passMuon = true; }
	      else{ passInvertedMuon = true; }
	      if(dtRechitClusterNSegmentStation1[itr_clust]==0){ passMB1 = true; }
	    
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
	      rpcSpread = max_element(rpcBx.begin(), rpcBx.end()) - min_element(rpcBx.begin(), rpcBx.end());
	      if(!rpcLayer.empty()){
		for(Int_t itr = 0; itr<rpcLayer.size(); itr++){
		  if(rpcLayer[itr]==1 || rpcLayer[itr]==2){ matchLayer1+=1; }
		  else if(rpcLayer[itr]==3 || rpcLayer[itr]==4){ matchLayer2+=1; }
		  else if(rpcLayer[itr]==5){ matchLayer3+=1; }
		  else if(rpcLayer[itr]==6){ matchLayer4+=1; }
		}
	      }
	    
	      for(Int_t itr_ho = 0; itr_ho<*nHORechits; itr_ho++){
		dPhi_tmp = HORechitPhi[itr_ho] - dtRechitClusterPhi[itr_clust];
		if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
		if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
		if(passJet){
		  h_dRClusterHO_jetVeto[itr_file]->Fill(sqrt(pow(dPhi_tmp,2)+pow(HORechitEta[itr_ho]-dtRechitClusterEta[itr_clust],2)));
		}
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
		}
	      }
	    
	      if(dtRechitClusterSize[itr_clust]>50){
	      
		nPassNone+=1;
		totalClusteredNone+=dtRechitClusterSize[itr_clust];

		if(passMuon){
		  nPassMuon+=1;
		}
		if(passJet){ 
		  nPassJet+=1; 
		  totalClusteredJet+=dtRechitClusterSize[itr_clust];
		  h_dtRechitClusterSizeMagnet_jetVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		  h_nRPCMatchedMagnet_jetVeto[itr_file]->Fill(match);

		  h_nRPCMatchedMagnetLayer1_jetVeto[itr_file]->Fill(matchLayer1);
		  h_nRPCMatchedMagnetLayer2_jetVeto[itr_file]->Fill(matchLayer2);
		  h_nRPCMatchedMagnetLayer3_jetVeto[itr_file]->Fill(matchLayer3);
		  h_nRPCMatchedMagnetLayer4_jetVeto[itr_file]->Fill(matchLayer4);
		}
		if(passMB1){ 
		  nPassMB1+=1; 
		  totalClusteredMB1+=dtRechitClusterSize[itr_clust];
		  h_dtRechitClusterSizeMagnet_MB1Veto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		}
		if(passJet && passMuon){
		  nPassJetMuon+=1;
		  totalClusteredNoMB1+=dtRechitClusterSize[itr_clust];
		  h_dtRechitClusterSizeMagnet_noMB1Veto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		  h_HOEnergy_jetMuonVeto[itr_file]->Fill(sumE);
		  if(dtRechitClusterSize[itr_clust]>=280){
		    totalSumE+=sumE;
		  }
		}
		if(passJet && passHO){
		  h_muonPt_jetHOVeto[itr_file]->Fill(muonPt_max);
		}
		if(passMuon && passHO){
		  h_jetPt_muonHOVeto[itr_file]->Fill(jetPt_max);
		}
		if(passJet && passMuon && passMB1){ 
		  nPassFull+=1; 
		  totalClusteredFull+=dtRechitClusterSize[itr_clust];
		  h_dtRechitClusterSizeMagnet_fullVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		}
		if(passHO){
		  nPassHO+=1; 
		  totalClusteredHO+=dtRechitClusterSize[itr_clust];	
		  h_dtRechitClusterSizeMagnet_HOVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		}
		if(passJet && passMuon && passHO){ 
		  passFullVeto = true;
		  nPassFullHO+=1; 
		  totalClusteredFullHO+=dtRechitClusterSize[itr_clust];
		  h_dtRechitClusterSizeMagnet_fullHOVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);	      
		  h_dtRechitClusterMaxStation_fullHOVeto[itr_file]->Fill(dtRechitClusterMaxStation[itr_clust]);
		  h_nRPCMatched_fullHOVeto[itr_file]->Fill(match);
		  h_RPCMatchedBxSpread_fullHOVeto[itr_file]->Fill(rpcSpread);
		  h_dPhiClusterMET_fullHOVeto[itr_file]->Fill(fabs(dPhiClusterMET));
		  h_HOTime_fullHOVeto[itr_file]->Fill(weightT/sumE);
		
		  h_muonDR_fullHOVeto[itr_file]->Fill(muonDR_min);
		  h_jetDR_fullHOVeto[itr_file]->Fill(jetDR_min);

		  h_nRPCMatchedMagnetLayer1_fullHOVeto[itr_file]->Fill(matchLayer1);
		  h_nRPCMatchedMagnetLayer2_fullHOVeto[itr_file]->Fill(matchLayer2);
		  h_nRPCMatchedMagnetLayer3_fullHOVeto[itr_file]->Fill(matchLayer3);
		  h_nRPCMatchedMagnetLayer4_fullHOVeto[itr_file]->Fill(matchLayer4);

		  if(!rpcBx.empty()){
		    passRPCMatch = true;
		    h_muonDR_HORPCMatch[itr_file]->Fill(muonDR_min);
		    h_jetDR_HORPCMatch[itr_file]->Fill(jetDR_min);
		    if(rpcSpread==0){
		      passRPCSpread = true;
		      h_muonDR_HORPCSpread0[itr_file]->Fill(muonDR_min);
		      h_jetDR_HORPCSpread0[itr_file]->Fill(jetDR_min);
		      if(fabs(dPhiClusterMET)<1){
			passDeltaPhi = true;
			totalClusteredFullHOPlus+=dtRechitClusterSize[itr_clust];
		      }
		    }
		  }
		}
	      }
	    }
	    h_HOMatchedEnergyCluster280Magnet_noMB1Veto[itr_file]->Fill(totalSumE);

	    if(passNoVeto){ nPassNoVeto_ho += 1; }//lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1); }
	    if(passFullVeto){ nPassFullVeto_ho += 1; }//lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1); }
	    if(passRPCMatch){ nPassRPCMatch_ho += 1; }//lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1); }
	    if(passRPCSpread){ nPassRPCSpread_ho += 1; }//lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1); }
	    if(passDeltaPhi){ nPassDeltaPhi_ho += 1; }//lumi[itr_year] * 1000. * 48.58 * 0.01 / treeReader.GetEntries(1); }

	    if(nPassNone>0){ h_dPhiJetMETMagnet_noVeto[itr_file]->Fill(dPhi_min); }
	    if(nPassMuon>0){ h_dPhiJetMETMagnet_muonVeto[itr_file]->Fill(dPhi_min); }
	    if(nPassJet>0){ h_dPhiJetMETMagnet_jetVeto[itr_file]->Fill(dPhi_min); }
	    if(nPassMB1>0){ h_dPhiJetMETMagnet_MB1Veto[itr_file]->Fill(dPhi_min); }
	    if(nPassJetMuon>0){ h_dPhiJetMETMagnet_noMB1Veto[itr_file]->Fill(dPhi_min); }
	    if(nPassFull>0){ h_dPhiJetMETMagnet_fullVeto[itr_file]->Fill(dPhi_min); }
	    if(nPassFullHO>0){ h_dPhiJetMETMagnet_fullHOVeto[itr_file]->Fill(dPhi_min); }

	    h_nTotalClusteredRechitsMagnet_noVeto[itr_file]->Fill(totalClusteredNone);
	    h_nTotalClusteredRechitsMagnet_jetVeto[itr_file]->Fill(totalClusteredJet);
	    h_nTotalClusteredRechitsMagnet_MB1Veto[itr_file]->Fill(totalClusteredMB1);
	    h_nTotalClusteredRechitsMagnet_noMB1Veto[itr_file]->Fill(totalClusteredNoMB1);
	    h_nTotalClusteredRechitsMagnet_HOVeto[itr_file]->Fill(totalClusteredHO);
	    h_nTotalClusteredRechitsMagnet_fullVeto[itr_file]->Fill(totalClusteredFull);
	    h_nTotalClusteredRechitsMagnet_fullHOVeto[itr_file]->Fill(totalClusteredFullHO);
	    h_nTotalClusteredRechitsMagnet_fullHOVetoPlus[itr_file]->Fill(totalClusteredFullHOPlus);
	  }
	  }*/
	/*if(*MET>200){
	  totalEvents+=1;
	  nPassMuon = 0;
	  nPassJet = 0;
	  nPassJetMuon = 0;
	  nPassMB1 = 0;
	  nPassHO = 0;
	  nPassFull = 0;
	  nPassFullHO = 0;
	  nPassNone = 0;
	  goodJets=0;
	  totalSumE=0.0;
	  totalClusteredNone = 0;
	  totalClusteredNoMB1 = 0;
	  totalClusteredJet = 0;
	  totalClusteredMB1 = 0;
	  totalClusteredHO = 0;
	  totalClusteredFull = 0;
	  totalClusteredFullHO = 0;
	  dPhiClusterMET_max = -1.;
	  for(Int_t itr_clust = 0; itr_clust<*nDtRechitClusters; itr_clust++){
	    dPhiClusterMET = dtRechitClusterPhi[itr_clust] - *METphi;
	    if(dPhiClusterMET > TMath::Pi()){ dPhiClusterMET -= 2*TMath::Pi(); }
	    if(dPhiClusterMET < -1.0*TMath::Pi()){ dPhiClusterMET += 2*TMath::Pi(); }
	    if(fabs(dPhiClusterMET)>dPhiClusterMET_max){ dPhiClusterMET_max=fabs(dPhiClusterMET); }
	  }
	  for(Int_t itr_jet = 0; itr_jet<*nJets; itr_jet++){
	    if(fabs(jetEta[itr_jet])<3.0 && jetPt[itr_jet]>20.0){
	      dPhi_tmp = jetPhi[itr_jet] - *METphi;
	      if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
	      if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
	      if(fabs(dPhi_tmp) < dPhi_min){ 
		dPhi_min = fabs(dPhi_tmp); 
		jetPt_tmp = jetPt[itr_jet];
	      }
	      goodJets+=1;
	      if(goodJets==4){ break; }
	    }
	  }	
	  if(fabs(dPhi_min)>0.6){
	    //if(fabs(dPhiClusterMET_max)<1.0){
	    for(Int_t itr_clust = 0; itr_clust<*nDtRechitClusters; itr_clust++){
	      match = 0;
	      matchLayer1 = 0;
	      matchLayer2 = 0;
	      matchLayer3 = 0;
	      matchLayer4 = 0;
	      matchHO = 0;
	      sumE = 0;
	      weightT = 0;
	      rpcBx.clear();
	      rpcLayer.clear();
	      zWheel.clear();
	      matchJet = false;
	      matchMuon = false;
	      goodEvt = true;
	      passMuon = false;
	      passJet = false;
	      passMB1 = false;
	      passHO = false;
	      passInvertedJet = false;
	      passInvertedMuon = false;
	      passInvertedMuJet = false;
	      llp_itr = -1;
	    
	      if(sqrt(pow(gLLP_decay_vertex_x[0]-dtRechitClusterX[itr_clust],2)+pow(gLLP_decay_vertex_y[0]-dtRechitClusterY[itr_clust],2)+pow(gLLP_decay_vertex_z[0]-dtRechitClusterZ[itr_clust],2)) < sqrt(pow(gLLP_decay_vertex_x[1]-dtRechitClusterX[itr_clust],2)+pow(gLLP_decay_vertex_y[1]-dtRechitClusterY[itr_clust],2)+pow(gLLP_decay_vertex_z[1]-dtRechitClusterZ[itr_clust],2))){ llp_itr = 0; }
	      else{ llp_itr = 1; }

	      dPhiClusterMET = dtRechitClusterPhi[itr_clust] - *METphi;
	      if(dPhiClusterMET > TMath::Pi()){ dPhiClusterMET -= 2*TMath::Pi(); }
	      if(dPhiClusterMET < -1.0*TMath::Pi()){ dPhiClusterMET += 2*TMath::Pi(); }
	    
	      if(dtRechitClusterJetVetoPt[itr_clust]<20.){ passJet = true; }
	      else{ passInvertedJet = true; }
	      if(dtRechitClusterMuonVetoPt[itr_clust]<10.){ passMuon = true; }
	      else{ passInvertedMuon = true; }
	      if(dtRechitClusterNSegmentStation1[itr_clust]==0){ passMB1 = true; }

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
	      if(sumE>40.){ passHO = true; }

	      if(dtRechitClusterSize[itr_clust]>50){
	      
		nPassNone+=1;
		totalClusteredNone+=dtRechitClusterSize[itr_clust];

		if(passMuon){
		  nPassMuon+=1;
		}
		if(passJet){ 
		  nPassJet+=1;
		  totalClusteredJet+=dtRechitClusterSize[itr_clust];
		  h_dtRechitClusterSizeAll_jetVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		}
		if(passMB1){ 
		  nPassMB1+=1; 
		  totalClusteredMB1+=dtRechitClusterSize[itr_clust];
		  h_dtRechitClusterSizeAll_MB1Veto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		}
		if(passJet && passMuon){
		  nPassJetMuon+=1;
		  totalClusteredNoMB1+=dtRechitClusterSize[itr_clust];
		  h_dtRechitClusterSizeAll_noMB1Veto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		}
		if(passJet && passMuon && passMB1){ 
		  nPassFull+=1; 
		  totalClusteredFull+=dtRechitClusterSize[itr_clust];
		  h_dtRechitClusterSizeAll_fullVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		}
		if(passHO){ 
		  nPassHO+=1;
		  totalClusteredHO+=dtRechitClusterSize[itr_clust];
		  h_dtRechitClusterSizeAll_HOVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		}
		if(passJet && passMuon && passHO){ 
		  nPassFullHO+=1;
		  totalClusteredFullHO+=dtRechitClusterSize[itr_clust];
		  h_dtRechitClusterSizeAll_fullHOVeto[itr_file]->Fill(dtRechitClusterSize[itr_clust]);
		}
	      }
	    }
	    if(nPassNone>0){ h_dPhiJetMETAll_noVeto[itr_file]->Fill(dPhi_min); }
	    if(nPassMuon>0){ h_dPhiJetMETAll_muonVeto[itr_file]->Fill(dPhi_min); }
	    if(nPassJet>0){ h_dPhiJetMETAll_jetVeto[itr_file]->Fill(dPhi_min); }
	    if(nPassMB1>0){ h_dPhiJetMETAll_MB1Veto[itr_file]->Fill(dPhi_min); }
	    if(nPassJetMuon>0){ h_dPhiJetMETAll_noMB1Veto[itr_file]->Fill(dPhi_min); }
	    if(nPassFull>0){ h_dPhiJetMETAll_fullVeto[itr_file]->Fill(dPhi_min); }

	    h_nTotalClusteredRechitsAll_noVeto[itr_file]->Fill(totalClusteredNone);
	    h_nTotalClusteredRechitsAll_jetVeto[itr_file]->Fill(totalClusteredJet);
	    h_nTotalClusteredRechitsAll_MB1Veto[itr_file]->Fill(totalClusteredMB1);
	    h_nTotalClusteredRechitsAll_noMB1Veto[itr_file]->Fill(totalClusteredNoMB1);
	    h_nTotalClusteredRechitsAll_HOVeto[itr_file]->Fill(totalClusteredHO);
	    h_nTotalClusteredRechitsAll_fullVeto[itr_file]->Fill(totalClusteredFull);
	    h_nTotalClusteredRechitsAll_fullHOVeto[itr_file]->Fill(totalClusteredFullHO);
	  }
	  }*/
	evtNum+=1;
      }
      
    }
    //cout << "Total events = " << totalEvents << endl;
    //cout << "Total magnet events = " << totalMagnetEvents << endl;
    //cout << "Total barrel events = " << totalBarrelEvents << endl;

    cout << "MET > 200: " << nPassMET * 137.0 * 1000. * 48.58 * 0.01 << endl;
    //cout << "DT Decay: " << nPassDTDecay * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "dPhi(jet,MET) > 0.6: " << nPassJetMET * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "dPhi(jet [20 GeV],MET) > 0.6: " << nPassJetMET_20 * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "dPhi(jet [30 GeV],MET) > 0.6: " << nPassJetMET_30 * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "dPhi(jet [50 GeV],MET) > 0.6: " << nPassJetMET_50 * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "dPhi(jet [Top 4],MET) > 0.6: " << nPassJetMET_top4 * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "No Veto: " << nPassNoVeto * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "Full Veto: " << nPassFullVeto * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "nRPC Matched > 0: " << nPassRPCMatch * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "RPC Spread = 0: " << nPassRPCSpread * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "Max Station > 2: " << nPassMaxStation * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "dPhi(Cluster,MET) < 1: " << nPassDeltaPhi * 137.0 * 1000. * 48.58 * 0.01 << endl;      
    cout << " " << endl;
    //cout << "HO Decay: " << nPassHODecay * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "dPhi(jet,MET) > 0.6: " << nPassJetMET * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "No Veto: " << nPassNoVeto_ho * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "Full Veto: " << nPassFullVeto_ho * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "nRPC Matched > 0: " << nPassRPCMatch_ho * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "RPC Spread = 0: " << nPassRPCSpread_ho * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "dPhi(Cluster,MET) < 1: " << nPassDeltaPhi_ho * 137.0 * 1000. * 48.58 * 0.01 << endl;      
    cout << "DT cluster: " << nPassNoVeto * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << " " << endl;
    cout << "Muon veto: " << nPassMuon_std * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "MB1 veto: " << nPassMB1_std * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "Jet+Muon veto: " << nPassJetMuon_std * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "Jet+MB1 veto: " << nPassJetMB1_std * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "Full DT Veto: " << nPassFull_std * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << " " << endl;
    cout << "Alt Muon veto: " << nPassMuon_alt * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "Alt MB1 veto: " << nPassMB1_alt * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "Alt Muon Full DT veto: " << nPassFull_altMuon * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "Alt MB1 Full DT veto: " << nPassFull_altMB1 * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "Alt Muon MB1 Full DT veto: " << nPassFull_altMuonMB1 * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << " " << endl;
    cout << "Full DT Selection No Muon: " << nPassFullDTPlus_noMuon * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "Full DT Selection No MB1: " << nPassFullDTPlus_noMB1 * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "Full DT Selection: " << nPassFullDTPlus_std * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "Alt Muon Full DT Selection: " << nPassFullDTPlus_altMuon * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "Alt MB1 Full DT Selection: " << nPassFullDTPlus_altMB1 * 137.0 * 1000. * 48.58 * 0.01 << endl;
    cout << "Alt Muon MB1 Full DT Selection: " << nPassFullDTPlus_altMuonMB1 * 137.0 * 1000. * 48.58 * 0.01 << endl;

    cout << " " << endl;

    itr_file+=1;    
  }

  _ofile->Write();
  _ofile->Close();
  
}
