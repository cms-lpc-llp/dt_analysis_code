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

void analyzeSignal_ABCD(){

  char name[50];
  char title[100];
  //char mX[1][20] = {"photon_m_10"};
  char mX[3][10] = {"15","40","55"};
  //char mX[5][20] = {"vector_m_2","vector_m_5","vector_m_10","vector_m_15","vector_m_20"};
  //char mX[4][20] = {"photon_m_7","photon_m_10","photon_m_15","photon_m_20"};
  //char mX[5][20] = {"higgs_m_4","higgs_m_5","higgs_m_10","higgs_m_15","higgs_m_20"};
  //char mX[4][20] = {"gluon_m_6","gluon_m_10","gluon_m_15","gluon_m_20"};
  //char mX[5][20] = {"darkphoton_m_2","darkphoton_m_5","darkphoton_m_10","darkphoton_m_15","darkphoton_m_20"};
  //char mX[2][10] = {"450"};
  //char ctau[2][20] = {"1m","10m"};
  //char ctau[6][20] = {"1","10","100","1000","10000","100000"};
  char ctau[4][20] = {"100","1000","10000","100000"};
  //char ctau[4][20] = {"500mm_xi_1","1000mm_xi_1","5000mm_xi_1","10000mm_xi_1"};
  //char ctau[8][25] = {"500mm_xi_1","1000mm_xi_1","5000mm_xi_1","10000mm_xi_1","500mm_xi_2p5","1000mm_xi_2p5","5000mm_xi_2p5","10000mm_xi_2p5"};
  //char ctau[4][20] = {"500_xi_1","500_xi_2p5","1000_xi_1","1000_xi_2p5"};
  Float_t lifetime = 10000;
  //Float_t lifetime[2] = {1000,10000};
  char years[3][20] = {"MC_Fall18","MC_Fall17","MC_Summer16"};
  //char years[3][20] = {"2016","2017","2018"};
  Float_t lumi[3] = {59.74,41.53,35.92};
  Double_t weight = 1.0;
  Float_t decay1 = 0.0;
  Float_t decay2 = 0.0;
  Float_t ctau1 = 0.0;
  Float_t ctau2 = 0.0;

  TString dir("/mnt/hadoop/store/group/phys_exotica/delayedjets/displacedJetMuonAnalyzer/driftTube/V1p17/");
  //TString dir("/mnt/hadoop/store/group/phys_exotica/delayedjets/displacedJetMuonAnalyzer/driftTube/V1p15/");
  //TString dir("/storage/user/mcitron/hvHaddedFiles/");
  TFile *_ofile = TFile::Open("outSig_ABCD_new.root","RECREATE");

  TH1D *h_dtRechitClusterSize_signalRegion[5][6];
  TH1D *h_dtRechitClusterSize_signalRegionNew[5][6];
  TH1D *h_dtRechitClusterSizeTotal_signalRegionNew[5][6];
  TH1D *h_dtRechitClusterSize_fullSelection_rpcCR[5][6];
  TH1D *h_dtRechitClusterSize_fullSelection_clusterMETCR[5][6];

  TH1D *h_nRPCMatched_fullVeto_clusterMETCR[5][6];
  TH1D *h_rpcSpread_fullVeto_clusterMETCR[5][6];
  TH1D *h_rpcBx_fullVeto_clusterMETCR[5][6];
  TH1D *h_dPhiJetMET_fullVeto_clusterMETCR[5][6];
  TH1D *h_dtRechitClusterMaxStation_fullVeto_clusterMETCR[5][6];

  TH1D *h_nRPCMatched_Nminus1_clusterMETCR[5][6];
  TH1D *h_rpcSpread_Nminus1_clusterMETCR[5][6];
  TH1D *h_rpcBx_Nminus1_clusterMETCR[5][6];
  TH1D *h_dPhiJetMET_Nminus1_clusterMETCR[5][6];
  TH1D *h_dtRechitClusterMaxStation_Nminus1_clusterMETCR[5][6];

  TH1D *h_dPhiClusterMET_fullVeto_rpcCR[5][6];
  TH1D *h_dPhiJetMET_fullVeto_rpcCR[5][6];
  TH1D *h_dtRechitClusterMaxStation_fullVeto_rpcCR[5][6];

  TH1D *h_dPhiClusterMET_Nminus1_rpcCR[5][6];
  TH1D *h_dPhiJetMET_Nminus1_rpcCR[5][6];
  TH1D *h_dtRechitClusterMaxStation_Nminus1_rpcCR[5][6];

  TH1D *h_nStations1_50hits_clusterMETCR[5][6];
  TH1D *h_nStations1_100hits_clusterMETCR[5][6];
  TH1D *h_nStations1_150hits_clusterMETCR[5][6];
  TH1D *h_nStations25_50hits_clusterMETCR[5][6];
  TH1D *h_nStations25_100hits_clusterMETCR[5][6];
  TH1D *h_nStations25_150hits_clusterMETCR[5][6];
  TH1D *h_nStations50_50hits_clusterMETCR[5][6];
  TH1D *h_nStations50_100hits_clusterMETCR[5][6];
  TH1D *h_nStations50_150hits_clusterMETCR[5][6];

  TH1D *h_nWheels1_50hits_clusterMETCR[5][6];
  TH1D *h_nWheels25_50hits_clusterMETCR[5][6];
  TH1D *h_nWheels50_50hits_clusterMETCR[5][6];
  TH1D *h_nWheels1_100hits_clusterMETCR[5][6];
  TH1D *h_nWheels25_100hits_clusterMETCR[5][6];
  TH1D *h_nWheels50_100hits_clusterMETCR[5][6];
  TH1D *h_nWheels1_150hits_clusterMETCR[5][6];
  TH1D *h_nWheels25_150hits_clusterMETCR[5][6];
  TH1D *h_nWheels50_150hits_clusterMETCR[5][6];

  TH1D *h_nRPCStations1_50hits_clusterMETCR[5][6];
  TH1D *h_nRPCStations5_50hits_clusterMETCR[5][6];
  TH1D *h_nRPCStations10_50hits_clusterMETCR[5][6];
  TH1D *h_nRPCStations1_100hits_clusterMETCR[5][6];
  TH1D *h_nRPCStations5_100hits_clusterMETCR[5][6];
  TH1D *h_nRPCStations10_100hits_clusterMETCR[5][6];
  TH1D *h_nRPCStations1_150hits_clusterMETCR[5][6];
  TH1D *h_nRPCStations5_150hits_clusterMETCR[5][6];
  TH1D *h_nRPCStations10_150hits_clusterMETCR[5][6];

  TH1D *h_nRPCWheels1_50hits_clusterMETCR[5][6];
  TH1D *h_nRPCWheels5_50hits_clusterMETCR[5][6];
  TH1D *h_nRPCWheels10_50hits_clusterMETCR[5][6];
  TH1D *h_nRPCWheels1_100hits_clusterMETCR[5][6];
  TH1D *h_nRPCWheels5_100hits_clusterMETCR[5][6];
  TH1D *h_nRPCWheels10_100hits_clusterMETCR[5][6];
  TH1D *h_nRPCWheels1_150hits_clusterMETCR[5][6];
  TH1D *h_nRPCWheels5_150hits_clusterMETCR[5][6];
  TH1D *h_nRPCWheels10_150hits_clusterMETCR[5][6];

  TH1D *h_dtRechitClusterJetVetoPt[5][6];
  TH1D *h_dtRechitClusterMuonVetoPt[5][6];
  TH1D *h_dtRechitClusterMB1Veto[5][6];

  TH1D *h_efficiency[5][6];
  TH1D *h_efficiency_MB1CR[5][6];
  
  TH1D *h_nDtRechitClusters_dPhiJetMET[5][6];
  TH1D *h_nDtRechitClustersVeto_dPhiJetMET[5][6];
  TH1D *h_dtRechitClustersDR_dPhiJetMET[5][6];
  TH1D *h_dtRechitClustersVetoDR_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterNSegmentStation2_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterNSegmentStation3_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterNSegmentStation4_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterMaxStationRatio_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterNStation_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterMaxStation_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterMaxChamberRatio_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterNChamber_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterMaxChamber_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterX_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterY_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterZ_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterEta_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterPhi_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterTime_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterXSpread_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterYSpread_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterZSpread_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterEtaSpread_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterPhiSpread_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterTimeSpread_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterMajorAxis_dPhiJetMET[5][6];
  TH1D *h_dtRechitClusterMinorAxis_dPhiJetMET[5][6];
  
  TH1D *h_nRB1Match_dPhiJetMET[5][6];
  TH1D *h_nRB1Match_MB1Veto_dPhiJetMET[5][6];
  TH1D *h_nMB1MatchAdjacent_dPhiJetMET[5][6];
  TH1D *h_nMB1MatchAdjacent_MB1Veto_dPhiJetMET[5][6];
  TH1D *h_nMB1MatchAdjacent_dPhiClusterMET[5][6];
  TH1D *h_nMB1MatchAdjacent_MB1Veto_dPhiClusterMET[5][6];
  TH1D *h_nMB1MatchAdjacentPi2_dPhiClusterMET[5][6];
  TH1D *h_nMB1MatchAdjacentPi2_MB1Veto_dPhiClusterMET[5][6];
  TH1D *h_nMB1MatchAdjacent0p8_dPhiClusterMET[5][6];
  TH1D *h_nMB1MatchAdjacent0p8_MB1Veto_dPhiClusterMET[5][6];
  TH1D *h_nMB1MatchAdjacent0p8Pi2_dPhiClusterMET[5][6];
  TH1D *h_nMB1MatchAdjacent0p8Pi2_MB1Veto_dPhiClusterMET[5][6];
  
  TH1D *h_jetChargedHadronicEnergyFraction_SR[5][6];
  TH1D *h_jetNeutralHadronicEnergyFraction_SR[5][6];
  TH1D *h_jetNeutralEMEnergyFraction_SR[5][6];
  TH1D *h_jetChargedEMEnergyFraction_SR[5][6];
  TH1D *h_leadingJetChargedHadronicEnergyFraction_SR[5][6];
  TH1D *h_leadingJetNeutralHadronicEnergyFraction_SR[5][6];
  TH1D *h_leadingJetNeutralEMEnergyFraction_SR[5][6];
  TH1D *h_leadingJetChargedEMEnergyFraction_SR[5][6];
  
  Double_t chargedHadFraction_mindPhi = 0.0;
  Double_t chargedEMFraction_mindPhi = 0.0;
  Double_t neutralHadFraction_mindPhi = 0.0;
  Double_t neutralEMFraction_mindPhi = 0.0;

  Double_t dPhi_tmp = 0.0;
  Double_t dPhi_min = 0.0;
  Double_t dPhiClusterRPC = 0.0;
  Double_t dZClusterRPC = 0.0;
  Double_t dPhiClusterMET_max = 0.0;
  Double_t dPhiClusterMET = 0.0;
  vector<Int_t> rpcBx = {};
  Int_t rpcSpread = 0;
  Double_t rpcMedian = 0;

  vector<Double_t> clusterEta = {};
  vector<Double_t> clusterPhi = {};
  vector<Int_t> clusterSize = {};
  Int_t clusterSizeTotal = 0;
  Int_t nClustersVeto_dPhiJetMET = 0;

  Int_t evtNum = 0;
  Int_t totalNum = 0;

  Bool_t passMuon = false;
  Bool_t passMuonLoose = false;
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

  Bool_t passMET = false;
  Bool_t passOneJet = false;
  Bool_t passNHFJet = false;
  Bool_t passJetMET = false;
  Bool_t passStations25 = false;
  Bool_t passWheels25 = false;
  Bool_t passJetVeto = false;
  Bool_t passMuonVeto = false;
  Bool_t passMB1Veto = false;
  Bool_t passMaxStation = false;
  Bool_t passClusterMET = false;
  Bool_t passRPCMatch = false;
  Bool_t passRPCSpread = false;
  Bool_t passRPCBx = false;
  Bool_t passNoVetoCluster = false;
  Bool_t passClusterSize = false;
  Bool_t passAdjacentMB1 = false;
  Bool_t passAdjacent0p8MB1 = false;
  Bool_t passOtherStations = false;

  Bool_t passMB1CR = false;
  Bool_t passJetVetoMB1CR = false;
  Bool_t passMuonVetoMB1CR = false;
  Bool_t passMuonVetoLooseMB1CR = false;
  Bool_t passRpcMatchMB1CR = false;
  Bool_t passClusterMETMB1CR = false;
  Bool_t passClusterSizeMB1CR = false;

  Bool_t passMB2CR = false;
  Bool_t passMB2CRwithAdjacent = false;
  Bool_t passMB2CRwithAdjacent0p8 = false;
  Bool_t passMB2CRwithOther = false;
  Bool_t passMB2CRwithNHF = false;
  Double_t nPassMB2CR = 0;
  Double_t nPassMB2CRwithAdjacent = 0;
  Double_t nPassMB2CRwithAdjacent0p8 = 0;
  Double_t nPassMB2CRwithOther = 0;
  Double_t nPassMB2CRwithNHF = 0;

  Bool_t passSignalRegion = false;
  Double_t nPassSignalRegion = 0;

  Double_t nPassClusterCR = 0;
  Double_t nPassNoVeto_clusterCR = 0;
  Double_t nPassFullVeto_clusterCR = 0;
  Double_t nPassRPCMatch_clusterCR = 0;
  Double_t nPassRPCSpread_clusterCR = 0;
  Double_t nPassRPCBx_clusterCR = 0;
  Double_t nPassMaxStation_clusterCR = 0;
  Double_t nPassLepton_clusterCR = 0;
  Double_t nPass50Hits_clusterCR = 0;
  Double_t nPass25Hits_clusterCR = 0;

  Double_t nPassNoVeto = 0;  
  Double_t nPassFullVeto_rpcCR = 0;
  Double_t nPassRPCCR = 0;
  Double_t nPassClusterMET_rpcCR = 0;
  Double_t nPassMaxStation_rpcCR = 0;
  Double_t nPassFullPlus = 0;
  Double_t nPassJetMET_rpcCR = 0;
  Double_t nPassLepton_rpcCR = 0;
  Double_t nPass50Hits_rpcCR = 0;
  Double_t nPass25Hits_rpcCR = 0;

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

  Float_t dtR = 0.0;
  Int_t rpcStation = 99;
  Int_t rpcWheel = 99;
  Int_t dtStation = 99;
  Int_t dtWheel = 99;
  Int_t maxClusterSize = 0;
  Int_t maxClusterSizeMB1CR = 0;
  Int_t hitsMB1 = 0;
  Int_t nMB1MatchClusterAdjacentPlus = 0;
  Int_t nMB1MatchClusterAdjacentMinus = 0;
  Int_t nMB1MatchPi2AdjacentPlus = 0;
  Int_t nMB1MatchPi2AdjacentMinus = 0;
  Int_t nMB1MatchClusterAdjacent0p8Plus = 0;
  Int_t nMB1MatchClusterAdjacent0p8Minus = 0;
  Int_t nMB1MatchPi2Adjacent0p8Plus = 0;
  Int_t nMB1MatchPi2Adjacent0p8Minus = 0;
  Int_t nRB1MatchCluster = 0;

  Int_t nMB2MatchCluster = 0;
  Int_t nMB3MatchCluster = 0;
  Int_t nMB4MatchCluster = 0;

  TRandom3 *rand = new TRandom3();
  Int_t pmRand = 0;

  for(Int_t itr_mX=0; itr_mX<3; itr_mX++){
    for(Int_t itr_ctau=0; itr_ctau<4; itr_ctau++){
      sprintf(name,"h_nDtRechitClusters_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_nDtRechitClusters_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);
      
      sprintf(name,"h_nDtRechitClustersVeto_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_nDtRechitClustersVeto_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);
      
      sprintf(name,"h_dtRechitClustersDR_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClustersDR_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",50,0,2);
      
      sprintf(name,"h_dtRechitClustersVetoDR_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClustersVetoDR_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",50,0,2);
      
      sprintf(name,"h_dtRechitClusterNSegmentStation2_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterNSegmentStation2_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",50,0,500);
      
      sprintf(name,"h_dtRechitClusterNSegmentStation3_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterNSegmentStation3_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",50,0,500);
      
      sprintf(name,"h_dtRechitClusterNSegmentStation4_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterNSegmentStation4_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",50,0,500);

      sprintf(name,"h_dtRechitClusterMaxStation_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterMaxStation_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

      sprintf(name,"h_dtRechitClusterNStation_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterNStation_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

      sprintf(name,"h_dtRechitClusterMaxStationRatio_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterMaxStationRatio_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",50,0,1);

      sprintf(name,"h_dtRechitClusterMaxChamberRatio_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterMaxChamberRatio_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",50,0,1);
      
      sprintf(name,"h_dtRechitClusterNChamber_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterNChamber_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

      sprintf(name,"h_dtRechitClusterMaxChamber_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterMaxChamber_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

      sprintf(name,"h_dtRechitClusterX_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterX_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",100,-800,800);

      sprintf(name,"h_dtRechitClusterY_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterY_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",100,-800,800);

      sprintf(name,"h_dtRechitClusterZ_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterZ_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",100,-600,600);

      sprintf(name,"h_dtRechitClusterEta_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterEta_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",50,-1.5,1.5);

      sprintf(name,"h_dtRechitClusterPhi_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterPhi_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",100,-3.5,3.5);

      sprintf(name,"h_dtRechitClusterTime_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterTime_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",50,300,800);

      sprintf(name,"h_dtRechitClusterXSpread_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterXSpread_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",100,0,500);

      sprintf(name,"h_dtRechitClusterYSpread_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterYSpread_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",100,0,500);

      sprintf(name,"h_dtRechitClusterZSpread_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterZSpread_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",100,0,140);

      sprintf(name,"h_dtRechitClusterEtaSpread_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterEtaSpread_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",50,0,0.5);

      sprintf(name,"h_dtRechitClusterPhiSpread_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterPhiSpread_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",50,0,1);

      sprintf(name,"h_dtRechitClusterTimeSpread_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterTimeSpread_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",100,0,150);

      sprintf(name,"h_dtRechitClusterMajorAxis_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterMajorAxis_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",50,0,1);

      sprintf(name,"h_dtRechitClusterMinorAxis_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterMinorAxis_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",50,0,1);
      
      sprintf(name,"h_dtRechitClusterSize_signalRegion_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterSize_signalRegion[itr_mX][itr_ctau] = new TH1D(name,"",250,0,500);

      sprintf(name,"h_dtRechitClusterSize_signalRegionNew_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterSize_signalRegionNew[itr_mX][itr_ctau] = new TH1D(name,"",250,0,500);

      sprintf(name,"h_dtRechitClusterSizeTotal_signalRegionNew_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterSizeTotal_signalRegionNew[itr_mX][itr_ctau] = new TH1D(name,"",250,0,500);
      
      sprintf(name,"h_dtRechitClusterSize_fullSelection_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_dtRechitClusterSize_fullSelection_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",250,0,500);


      sprintf(name,"h_nRB1Match_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_nRB1Match_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",30,0,30);
      
      sprintf(name,"h_nRB1Match_MB1Veto_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_nRB1Match_MB1Veto_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",30,0,30);
      
      sprintf(name,"h_nMB1MatchAdjacent_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_nMB1MatchAdjacent_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",50,0,50);
      
      sprintf(name,"h_nMB1MatchAdjacent_MB1Veto_dPhiJetMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_nMB1MatchAdjacent_MB1Veto_dPhiJetMET[itr_mX][itr_ctau] = new TH1D(name,"",30,0,30);

      sprintf(name,"h_nMB1MatchAdjacent_dPhiClusterMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_nMB1MatchAdjacent_dPhiClusterMET[itr_mX][itr_ctau] = new TH1D(name,"",50,0,50);
      
      sprintf(name,"h_nMB1MatchAdjacent_MB1Veto_dPhiClusterMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_nMB1MatchAdjacent_MB1Veto_dPhiClusterMET[itr_mX][itr_ctau] = new TH1D(name,"",30,0,30);

      sprintf(name,"h_nMB1MatchAdjacentPi2_dPhiClusterMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_nMB1MatchAdjacentPi2_dPhiClusterMET[itr_mX][itr_ctau] = new TH1D(name,"",50,0,50);
      
      sprintf(name,"h_nMB1MatchAdjacentPi2_MB1Veto_dPhiClusterMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_nMB1MatchAdjacentPi2_MB1Veto_dPhiClusterMET[itr_mX][itr_ctau] = new TH1D(name,"",30,0,30);

      sprintf(name,"h_nMB1MatchAdjacent0p8_dPhiClusterMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_nMB1MatchAdjacent0p8_dPhiClusterMET[itr_mX][itr_ctau] = new TH1D(name,"",50,0,50);
      
      sprintf(name,"h_nMB1MatchAdjacent0p8_MB1Veto_dPhiClusterMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_nMB1MatchAdjacent0p8_MB1Veto_dPhiClusterMET[itr_mX][itr_ctau] = new TH1D(name,"",30,0,30);

      sprintf(name,"h_nMB1MatchAdjacent0p8Pi2_dPhiClusterMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_nMB1MatchAdjacent0p8Pi2_dPhiClusterMET[itr_mX][itr_ctau] = new TH1D(name,"",50,0,50);
      
      sprintf(name,"h_nMB1MatchAdjacent0p8Pi2_MB1Veto_dPhiClusterMET_%s_%s",mX[itr_mX],ctau[itr_ctau]);
      h_nMB1MatchAdjacent0p8Pi2_MB1Veto_dPhiClusterMET[itr_mX][itr_ctau] = new TH1D(name,"",30,0,30);


    sprintf(name,"h_dtRechitClusterSize_fullSelection_rpcCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_dtRechitClusterSize_fullSelection_rpcCR[itr_mX][itr_ctau] = new TH1D(name,"",250,0,500);

    sprintf(name,"h_nRPCMatched_fullVeto_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCMatched_fullVeto_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_rpcSpread_fullVeto_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_rpcSpread_fullVeto_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",10,0,10);

    sprintf(name,"h_rpcBx_fullVeto_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_rpcBx_fullVeto_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",10,-4.5,5.5);

    sprintf(name,"h_dPhiJetMET_fullVeto_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_dPhiJetMET_fullVeto_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dtRechitClusterMaxStation_fullVeto_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_dtRechitClusterMaxStation_fullVeto_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCMatched_Nminus1_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCMatched_Nminus1_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_rpcSpread_Nminus1_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_rpcSpread_Nminus1_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",10,0,10);

    sprintf(name,"h_rpcBx_Nminus1_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_rpcBx_Nminus1_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",10,-4.5,5.5);

    sprintf(name,"h_dPhiJetMET_Nminus1_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_dPhiJetMET_Nminus1_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dtRechitClusterMaxStation_Nminus1_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_dtRechitClusterMaxStation_Nminus1_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);
    
    sprintf(name,"h_dPhiClusterMET_fullVeto_rpcCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_dPhiClusterMET_fullVeto_rpcCR[itr_mX][itr_ctau] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dPhiJetMET_fullVeto_rpcCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_dPhiJetMET_fullVeto_rpcCR[itr_mX][itr_ctau] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dtRechitClusterMaxStation_fullVeto_rpcCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_dtRechitClusterMaxStation_fullVeto_rpcCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_dPhiClusterMET_Nminus1_rpcCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_dPhiClusterMET_Nminus1_rpcCR[itr_mX][itr_ctau] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dPhiJetMET_Nminus1_rpcCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_dPhiJetMET_Nminus1_rpcCR[itr_mX][itr_ctau] = new TH1D(name,"",35,0,3.5);

    sprintf(name,"h_dtRechitClusterMaxStation_Nminus1_rpcCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_dtRechitClusterMaxStation_Nminus1_rpcCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);



    sprintf(name,"h_nStations1_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nStations1_50hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations1_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nStations1_100hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations1_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nStations1_150hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations25_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nStations25_50hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations25_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nStations25_100hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations25_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nStations25_150hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations50_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nStations50_50hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations50_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nStations50_100hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStations50_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nStations50_150hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nWheels1_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nWheels1_50hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels1_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nWheels1_100hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels1_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nWheels1_150hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels25_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nWheels25_50hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels25_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nWheels25_100hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels25_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nWheels25_150hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels50_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nWheels50_50hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels50_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nWheels50_100hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheels50_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nWheels50_150hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);


    sprintf(name,"h_nRPCStations1_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCStations1_50hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations1_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCStations1_100hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations1_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCStations1_150hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations5_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCStations5_50hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations5_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCStations5_100hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations5_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCStations5_150hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations10_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCStations10_50hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations10_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCStations10_100hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCStations10_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCStations10_150hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nRPCWheels1_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCWheels1_50hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels1_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCWheels1_100hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels1_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCWheels1_150hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels5_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCWheels5_50hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels5_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCWheels5_100hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels5_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCWheels5_150hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels10_50hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCWheels10_50hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels10_100hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCWheels10_100hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nRPCWheels10_150hits_clusterMETCR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_nRPCWheels10_150hits_clusterMETCR[itr_mX][itr_ctau] = new TH1D(name,"",6,0,6);

    
    sprintf(name,"h_dtRechitClusterJetVetoPt_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_dtRechitClusterJetVetoPt[itr_mX][itr_ctau] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_dtRechitClusterMuonVetoPt_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_dtRechitClusterMuonVetoPt[itr_mX][itr_ctau] = new TH1D(name,"",20,0,200);

    sprintf(name,"h_dtRechitClusterMB1Veto_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_dtRechitClusterMB1Veto[itr_mX][itr_ctau] = new TH1D(name,"",60,0,60);


    sprintf(name,"h_jetNeutralEMEnergyFraction_SR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_jetNeutralEMEnergyFraction_SR[itr_mX][itr_ctau] = new TH1D(name,"",50,0,1);

    sprintf(name,"h_jetChargedEMEnergyFraction_SR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_jetChargedEMEnergyFraction_SR[itr_mX][itr_ctau] = new TH1D(name,"",50,0,1);

    sprintf(name,"h_jetNeutralHadronicEnergyFraction_SR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_jetNeutralHadronicEnergyFraction_SR[itr_mX][itr_ctau] = new TH1D(name,"",50,0,1);

    sprintf(name,"h_jetChargedHadronicEnergyFraction_SR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_jetChargedHadronicEnergyFraction_SR[itr_mX][itr_ctau] = new TH1D(name,"",50,0,1);

    sprintf(name,"h_leadingJetNeutralEMEnergyFraction_SR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_leadingJetNeutralEMEnergyFraction_SR[itr_mX][itr_ctau] = new TH1D(name,"",50,0,1);

    sprintf(name,"h_leadingJetChargedEMEnergyFraction_SR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_leadingJetChargedEMEnergyFraction_SR[itr_mX][itr_ctau] = new TH1D(name,"",50,0,1);

    sprintf(name,"h_leadingJetNeutralHadronicEnergyFraction_SR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_leadingJetNeutralHadronicEnergyFraction_SR[itr_mX][itr_ctau] = new TH1D(name,"",50,0,1);

    sprintf(name,"h_leadingJetChargedHadronicEnergyFraction_SR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_leadingJetChargedHadronicEnergyFraction_SR[itr_mX][itr_ctau] = new TH1D(name,"",50,0,1);


    sprintf(name,"h_efficiency_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_efficiency[itr_mX][itr_ctau] = new TH1D(name,"",20,0,20);

    sprintf(name,"h_efficiency_MB1CR_%s_%s",mX[itr_mX],ctau[itr_ctau]);
    h_efficiency_MB1CR[itr_mX][itr_ctau] = new TH1D(name,"",20,0,20);

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
   
    nPassMB2CR = 0;
    nPassMB2CRwithAdjacent = 0;
    nPassMB2CRwithAdjacent0p8 = 0;
    nPassMB2CRwithOther = 0;
    nPassMB2CRwithNHF = 0;
    nPassSignalRegion = 0;

    evtNum = 0;
    totalNum = 0;

    cout << mX[itr_mX] << "_" << ctau[itr_ctau] << endl;
    for(Int_t itr_year = 0; itr_year<3; itr_year++){
      cout << "  " << years[itr_year] << endl;

      evtNum = 0;
      
      TFile *_file;
      
      if(strcmp(years[itr_year],"MC_Summer16")==0){
	_file = TFile::Open(dir+years[itr_year]+"/v1/v3/normalized/ggH_HToSSTobbbb_MH-125_MS-"+mX[itr_mX]+"_ctau-"+ctau[itr_ctau]+"_TuneCUETP8M1_13TeV-powheg-pythia8_1pb_weighted.root");
	//_file = TFile::Open(dir+years[itr_year]+"/v3/v5/normalized/ggH_HToSSTobbbb_MH-125_MS-"+mX[itr_mX]+"_ctau-"+ctau[itr_ctau]+"_TuneCUETP8M1_13TeV-powheg-pythia8_1pb_weighted.root");
      }
      else{
	_file = TFile::Open(dir+years[itr_year]+"/v1/v3/normalized/ggH_HToSSTobbbb_MH-125_MS-"+mX[itr_mX]+"_ctau-"+ctau[itr_ctau]+"_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root");
	//_file = TFile::Open(dir+years[itr_year]+"/v3/v5/normalized/ggH_HToSSTobbbb_MH-125_MS-"+mX[itr_mX]+"_ctau-"+ctau[itr_ctau]+"_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root");
      }
      
      //_file = TFile::Open(dir+"signalPointsGGHWithRPCWithFlags/signal_1000_"+mX[itr_mX]+"_"+ctau[itr_ctau]+".root");
      //_file = TFile::Open(dir+"signalPointsGenFilter/HiddenValleyGenFilter_"+mX[itr_mX]+"_ctau_"+ctau[itr_ctau]+".py_privateMC_102X_LLPNTUPLE_v2_generationGenFilter_forHV_2018_MS.root");
      //_file = TFile::Open(dir+years[itr_year]+"/HV_params_"+mX[itr_mX]+"_ctau_"+ctau[itr_ctau]+"_LLPNTUPLE_v0_filter.root");

      TTreeReader treeReader("MuonSystem",_file);
      //TTreeReader treeReader("ntuples/llp",_file);

      TTreeReaderValue<unsigned int> runNum(treeReader,"runNum");
      //TTreeReaderValue<unsigned int> lumiSec(treeReader,"lumiSec");
      //TTreeReaderValue<unsigned int> eventNum(treeReader,"evtNum");
      
      TTreeReaderValue<float> MET(treeReader,"met");
      TTreeReaderValue<float> METphi(treeReader,"metPhi");
     
      //TTreeReaderValue<float> MET(treeReader,"metType1Pt");
      //TTreeReaderValue<float> METphi(treeReader,"metType1Phi");
 
      //TTreeReaderArray<float> gLLP_ctau(treeReader,"gLLP_ctau");
      TTreeReaderArray<float> gLLP_beta(treeReader,"gLLP_beta");
      TTreeReaderArray<float> gLLP_decay_vertex_x(treeReader,"gLLP_decay_vertex_x");
      TTreeReaderArray<float> gLLP_decay_vertex_y(treeReader,"gLLP_decay_vertex_y");
      TTreeReaderArray<float> gLLP_decay_vertex_z(treeReader,"gLLP_decay_vertex_z");

      TTreeReaderValue<int> nDtRechitClusters(treeReader,"nDtRechitClusters");
      TTreeReaderArray<float> dtRechitClusterX(treeReader,"dtRechitClusterX");
      TTreeReaderArray<float> dtRechitClusterY(treeReader,"dtRechitClusterY");
      TTreeReaderArray<float> dtRechitClusterZ(treeReader,"dtRechitClusterZ");
      TTreeReaderArray<float> dtRechitClusterPhi(treeReader,"dtRechitClusterPhi");
      TTreeReaderArray<float> dtRechitClusterEta(treeReader,"dtRechitClusterEta");
      TTreeReaderArray<float> dtRechitClusterTime(treeReader,"dtRechitClusterTime");
      TTreeReaderArray<float> dtRechitClusterXSpread(treeReader,"dtRechitClusterXSpread");
      TTreeReaderArray<float> dtRechitClusterYSpread(treeReader,"dtRechitClusterYSpread");
      TTreeReaderArray<float> dtRechitClusterZSpread(treeReader,"dtRechitClusterZSpread");
      TTreeReaderArray<float> dtRechitClusterPhiSpread(treeReader,"dtRechitClusterPhiSpread");
      TTreeReaderArray<float> dtRechitClusterEtaSpread(treeReader,"dtRechitClusterEtaSpread");
      TTreeReaderArray<float> dtRechitClusterTimeSpread(treeReader,"dtRechitClusterTimeSpread");
      TTreeReaderArray<float> dtRechitClusterJetVetoPt(treeReader,"dtRechitClusterJetVetoPt");
      TTreeReaderArray<float> dtRechitClusterMuonVetoPt(treeReader,"dtRechitClusterMuonVetoPt");
      TTreeReaderArray<int> dtRechitClusterSize(treeReader,"dtRechitClusterSize");
      TTreeReaderArray<int> dtRechitClusterNSegmentStation1(treeReader,"dtRechitClusterNSegmentStation1");
      TTreeReaderArray<int> dtRechitClusterNSegmentStation2(treeReader,"dtRechitClusterNSegmentStation2");
      TTreeReaderArray<int> dtRechitClusterNSegmentStation3(treeReader,"dtRechitClusterNSegmentStation3");
      TTreeReaderArray<int> dtRechitClusterNSegmentStation4(treeReader,"dtRechitClusterNSegmentStation4");
      TTreeReaderArray<int> dtRechitClusterMaxStation(treeReader,"dtRechitClusterMaxStation");
      TTreeReaderArray<float> dtRechitClusterMaxStationRatio(treeReader,"dtRechitClusterMaxStationRatio");
      TTreeReaderArray<int> dtRechitClusterNStation(treeReader,"dtRechitClusterNStation");
      TTreeReaderArray<int> dtRechitClusterMaxChamber(treeReader,"dtRechitClusterMaxChamber");
      TTreeReaderArray<float> dtRechitClusterMaxChamberRatio(treeReader,"dtRechitClusterMaxChamberRatio");
      TTreeReaderArray<int> dtRechitClusterNChamber(treeReader,"dtRechitClusterNChamber");
      TTreeReaderArray<float> dtRechitClusterMajorAxis(treeReader,"dtRechitClusterMajorAxis");
      TTreeReaderArray<float> dtRechitClusterMinorAxis(treeReader,"dtRechitClusterMinorAxis");
      
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
      TTreeReaderArray<float> jetElectronEnergyFraction(treeReader,"jetElectronEnergyFraction");
      TTreeReaderArray<float> jetPhotonEnergyFraction(treeReader,"jetPhotonEnergyFraction");
      TTreeReaderArray<float> jetNeutralHadronEnergyFraction(treeReader,"jetNeutralHadronEnergyFraction");
      TTreeReaderArray<float> jetChargedHadronEnergyFraction(treeReader,"jetChargedHadronEnergyFraction");
      //TTreeReaderArray<float> jetMuonEnergyFraction(treeReader,"jetMuonEnergyFraction");
      
      TTreeReaderValue<int> nRPCRechits(treeReader,"nRpc");
      TTreeReaderArray<float> RPCRechitX(treeReader,"rpcX");
      TTreeReaderArray<float> RPCRechitY(treeReader,"rpcY");
      TTreeReaderArray<float> RPCRechitZ(treeReader,"rpcZ");
      TTreeReaderArray<float> RPCRechitPhi(treeReader,"rpcPhi");
      TTreeReaderArray<float> RPCRechitEta(treeReader,"rpcEta");
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
      TTreeReaderValue<int> nMuons(treeReader,"nMuons");
      TTreeReaderArray<int> lepPdgId(treeReader,"lepPdgId");
      TTreeReaderArray<float> lepPhi(treeReader,"lepPhi");
      TTreeReaderArray<float> lepEta(treeReader,"lepEta");
      TTreeReaderArray<float> lepPt(treeReader,"lepPt");

      _ofile->cd();
      totalNum += treeReader.GetEntries(1);
      weight = 48.58*1000*0.01*lumi[itr_year]/treeReader.GetEntries(1);
      //weight = 48.58*1000*0.01*lumi[itr_year]/1E6;
      //weight = 48.58*1000*0.01*137/500000;
      //weight = 0.1845*1000*1.00*137/treeReader.GetEntries(1);
      while(treeReader.Next()){
       	//weight = 100.;
	//weight = weight*exp((gLLP_ctau[itr_ctau][0]+gLLP_ctau[itr_ctau][1])*(10./lifetime - 100./lifetime));
	//weight = weight*lumi[itr_year]/treeReader.GetEntries(1);
	/*decay1 = sqrt(pow(gLLP_decay_vertex_x[0],2)+pow(gLLP_decay_vertex_y[0],2)+pow(gLLP_decay_vertex_z[0],2));
	decay2 = sqrt(pow(gLLP_decay_vertex_x[1],2)+pow(gLLP_decay_vertex_y[1],2)+pow(gLLP_decay_vertex_z[1],2));
	ctau[itr_ctau]1 = decay1 / (gLLP_beta[0]*(1.0/sqrt(1-gLLP_beta[0]*gLLP_beta[0])));
	ctau[itr_ctau]1 = decay2 / (gLLP_beta[1]*(1.0/sqrt(1-gLLP_beta[1]*gLLP_beta[1])));
	weight = weight*exp((ctau[itr_ctau]1+ctau[itr_ctau]2)*(10./lifetime[itr_mX] - 100./(3*lifetime[itr_mX])));
	*/
	if(evtNum%100000==0){ cout << evtNum << " of " << treeReader.GetEntries(1) << endl; }
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
	passSignalRegion = false;
	passMB2CR = false;
	passMB2CRwithAdjacent = false;
	passMB2CRwithAdjacent0p8 = false;
	passMB2CRwithOther = false;
	passMB2CRwithNHF = false;
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
	maxClusterSizeMB1CR=0;

	passMET = false;
	passOneJet = false;
	passNHFJet = true;
	passJetMET = false;
	passStations25 = false;
	passWheels25 = false;
	passJetVeto = false;
	passMuonVeto = false;
	passMB1Veto = false;
	passMaxStation = false;
	passClusterMET = false;
	passRPCMatch = false;
	passRPCSpread = false;
	passRPCBx = false;
	passNoVetoCluster = false;
	passClusterSize = false;
	passAdjacentMB1 = false;
	passAdjacent0p8MB1 = false;
	passOtherStations = false;

	passMB1CR = false;
	passJetVetoMB1CR = false;
	passMuonVetoMB1CR = false;
	passMuonVetoLooseMB1CR = false;
	passRpcMatchMB1CR = false;
	passClusterMETMB1CR = false;
	passClusterSizeMB1CR = false;

	nClustersVeto_dPhiJetMET = 0;
	clusterEta.clear();
	clusterPhi.clear();
	clusterSize.clear();
	clusterSizeTotal = 0;

	nMB1MatchClusterAdjacentPlus = 0;
	nMB1MatchClusterAdjacentMinus = 0;
	nMB1MatchPi2AdjacentPlus = 0;
	nMB1MatchPi2AdjacentMinus = 0;
	nMB1MatchClusterAdjacent0p8Plus = 0;
	nMB1MatchClusterAdjacent0p8Minus = 0;
	nMB1MatchPi2Adjacent0p8Plus = 0;
	nMB1MatchPi2Adjacent0p8Minus = 0;
	nRB1MatchCluster = 0;
	
	if(rand->Uniform()<0.5){ pmRand = -1; }
	else{ pmRand = 1; }
	
	if(*MET > 200){
	  passMET = true;
	  dPhi_min = 999.;
	  dPhiClusterMET = 0.0;
	  dPhiClusterMET_max = 0.0;
	  chargedHadFraction_mindPhi = -1.0;
	  chargedEMFraction_mindPhi = -1.0;
	  neutralHadFraction_mindPhi = -1.0;
	  neutralEMFraction_mindPhi = -1.0;
	  if(*nDtRechitClusters>0){
	    nPassNoVeto+=1;
	    for(Int_t itr_clust = 0; itr_clust<*nDtRechitClusters; itr_clust++){
	      dPhiClusterMET = dtRechitClusterPhi[itr_clust] - *METphi;
	      if(dPhiClusterMET > TMath::Pi()){ dPhiClusterMET -= 2*TMath::Pi(); }
	      if(dPhiClusterMET < -1.0*TMath::Pi()){ dPhiClusterMET += 2*TMath::Pi(); }
	      if(fabs(dPhiClusterMET)>dPhiClusterMET_max){ dPhiClusterMET_max=fabs(dPhiClusterMET); }
	      if(dtRechitClusterSize[itr_clust]>maxClusterSize){ maxClusterSize = dtRechitClusterSize[itr_clust]; }
	    }
	  }
	  if(fabs(dPhiClusterMET)<1.0){ nPassClusterCR+=1; }

	  for(Int_t itr_jet = 0; itr_jet<*nJets; itr_jet++){
	    if(fabs(jetEta[itr_jet])<3.0 && jetPt[itr_jet]>30.0){
	      passOneJet = true;
	      if(jetNeutralHadronEnergyFraction[itr_jet]>=0.9 && fabs(jetEta[itr_jet])<2.4 && jetPt[itr_jet]>50.0){ passNHFJet = false; }
	      dPhi_tmp = jetPhi[itr_jet] - *METphi;
	      if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
	      if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
	      if(fabs(dPhi_tmp) < dPhi_min){ 
		dPhi_min = fabs(dPhi_tmp); 
		chargedHadFraction_mindPhi = jetChargedHadronEnergyFraction[itr_jet];
		chargedEMFraction_mindPhi = jetElectronEnergyFraction[itr_jet];
		neutralHadFraction_mindPhi = jetNeutralHadronEnergyFraction[itr_jet];
		neutralEMFraction_mindPhi = jetPhotonEnergyFraction[itr_jet];
	      }
	    }
	  }
	  if(fabs(dPhi_min)>0.6){ 
	    passJetMET = true; 
	    h_nDtRechitClusters_dPhiJetMET[itr_mX][itr_ctau]->Fill(*nDtRechitClusters,weight);
	  }
	  

	  for(Int_t itr_dt = 0; itr_dt<*nDtRechits; itr_dt++){
	    dtR = sqrt(pow(dtRechitX[itr_dt],2)+pow(dtRechitY[itr_dt],2));
	    if(dtR>400. && dtR<480.){ hitStation1+=1; }
	    else if(dtR>485. && dtR<560.){ hitStation2+=1; }
	    else if(dtR>590. && dtR<650.){ hitStation3+=1; }
	    else if(dtR>690. && dtR<800.){ hitStation4+=1; }
	    if(dtRechitZ[itr_dt]>-661. && dtRechitZ[itr_dt]<-395.){ hitWheelm2+=1; }
	    else if(dtRechitZ[itr_dt]>-395. && dtRechitZ[itr_dt]<-127.){ hitWheelm1+=1; }
	    else if(fabs(dtRechitZ[itr_dt]<127.)){ hitWheel0+=1; }
	    else if(dtRechitZ[itr_dt]<395.){ hitWheel1+=1; }
	    else if(dtRechitZ[itr_dt]<661.){ hitWheel2+=1; }
	  }
	  
	  if(hitStation1>25){ nStations25+=1; }
	  if(hitStation2>25){ nStations25+=1; }
	  if(hitStation3>25){ nStations25+=1; }
	  if(hitStation4>25){ nStations25+=1; }
	  if(hitWheelm2>25){ nWheels25+=1; }
	  if(hitWheelm1>25){ nWheels25+=1; }
	  if(hitWheel0>25){ nWheels25+=1; }
	  if(hitWheel1>25){ nWheels25+=1; }
	  if(hitWheel2>25){ nWheels25+=1; }
	  
	  if(nStations25<3){ passStations25=true; }
	  if(nWheels25<3){ passWheels25=true; }
	  if(*nDtRechitClusters>0){ passNoVetoCluster=true; }

	  for(Int_t itr_clust=0; itr_clust<*nDtRechitClusters; itr_clust++){
	    if(dtRechitClusterSize[itr_clust]>50){  
	      passMuon=false;
	      passMuonLoose=false;
	      passMuon_alt=false;
	      passJet=false;
	      rpcBx.clear();
	      rpcSpread = 99;
	      rpcMedian = 99;
	      dPhiClusterRPC = -0.1;
	      dZClusterRPC = -1.;
	      //nStations25 = 0;
	      //nStations50 = 0;
	      hoMatchedEnergy = 0.;
	      hitsMB1 = 0;
	      
	      dPhiClusterMET = dtRechitClusterPhi[itr_clust] - *METphi;
	      if(dPhiClusterMET > TMath::Pi()){ dPhiClusterMET -= 2*TMath::Pi(); }
	      if(dPhiClusterMET < -1.0*TMath::Pi()){ dPhiClusterMET += 2*TMath::Pi(); }
	      
	      h_dtRechitClusterJetVetoPt[itr_mX][itr_ctau]->Fill(dtRechitClusterJetVetoPt[itr_clust],weight);
	      h_dtRechitClusterMuonVetoPt[itr_mX][itr_ctau]->Fill(dtRechitClusterMuonVetoPt[itr_clust],weight);
	      if(dtRechitClusterJetVetoPt[itr_clust]<20.){ passJet = true; } 
	      if(dtRechitClusterMuonVetoPt[itr_clust]<10.){ passMuon = true; } 
	      
	      passMuonLoose=true;
	      for(Int_t itr_lep=0; itr_lep<*nLeptons; itr_lep++){
		if(abs(lepPdgId[itr_lep])==13){
		  dPhi_tmp = lepPhi[itr_lep] - dtRechitClusterPhi[itr_clust];
		  if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
		  if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
		  if(sqrt(pow(dPhi_tmp,2)+pow(lepEta[itr_lep]-dtRechitClusterEta[itr_clust],2))<0.4){
		    if(lepPt[itr_lep]>10.0){
		      passMuonLoose=false;
		      break;
		    }
		  }
		}
	      }

	      //if(*nLeptons==0){ passMuon_alt = true; }
	    
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

	      nMB2MatchCluster=0;
	      nMB3MatchCluster=0;
	      nMB4MatchCluster=0;
	      passMB1 = true;
	      for(Int_t itr_dt = 0; itr_dt<*nDtRechits; itr_dt++){
		dPhi_tmp = dtRechitPhi[itr_dt] - dtRechitClusterPhi[itr_clust];
		if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
		if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
		if(sqrt(pow(dPhi_tmp,2)+pow(dtRechitEta[itr_dt]-dtRechitClusterEta[itr_clust],2))<0.4){
		  if(dtRechitStation[itr_dt]==1){ hitsMB1+=1; }
		  if(dtRechitStation[itr_dt]==2){ nMB2MatchCluster+=1; }
		  if(dtRechitStation[itr_dt]==3){ nMB3MatchCluster+=1; }
		  if(dtRechitStation[itr_dt]==4){ nMB4MatchCluster+=1; }
		    //break;
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
	      /*if(itr_clust==0){
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
	      if(*nDtRechits>=750){
		nStations1=4;
		nStations25=4;
		nStations50=4;
		nWheels1=5;
		nWheels25=5;
		nWheels50=5;
		}*/
	      if(hitsMB1>1 || dtRechitClusterNSegmentStation1[itr_clust]>0){ passMB1 = false; } 
	      h_dtRechitClusterMB1Veto[itr_mX][itr_ctau]->Fill(hitsMB1,weight);
	      
	      
	      if(fabs(dPhi_min)>0.6 && dtRechitClusterJetVetoPt[itr_clust]<20.0 && dtRechitClusterMuonVetoPt[itr_clust]<10.0){
		nClustersVeto_dPhiJetMET+=1;
		h_dtRechitClusterNSegmentStation2_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterNSegmentStation2[itr_clust],weight);
		h_dtRechitClusterNSegmentStation3_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterNSegmentStation3[itr_clust],weight);
		h_dtRechitClusterNSegmentStation4_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterNSegmentStation4[itr_clust],weight);
		h_dtRechitClusterMaxStationRatio_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterMaxStationRatio[itr_clust],weight);
		h_dtRechitClusterMaxStation_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterMaxStation[itr_clust],weight);
		h_dtRechitClusterNStation_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterNStation[itr_clust],weight);
		h_dtRechitClusterMaxChamberRatio_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterMaxChamberRatio[itr_clust],weight);
		h_dtRechitClusterNChamber_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterNChamber[itr_clust],weight);
		h_dtRechitClusterMaxChamber_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterMaxChamber[itr_clust],weight);
		h_dtRechitClusterX_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterX[itr_clust],weight);
		h_dtRechitClusterY_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterY[itr_clust],weight);
		h_dtRechitClusterZ_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterZ[itr_clust],weight);
		h_dtRechitClusterEta_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterEta[itr_clust],weight);
		h_dtRechitClusterPhi_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterPhi[itr_clust],weight);
		h_dtRechitClusterTime_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterTime[itr_clust],weight);
		h_dtRechitClusterXSpread_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterXSpread[itr_clust],weight);
		h_dtRechitClusterYSpread_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterYSpread[itr_clust],weight);
		h_dtRechitClusterZSpread_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterZSpread[itr_clust],weight);
		h_dtRechitClusterEtaSpread_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterEtaSpread[itr_clust],weight);
		h_dtRechitClusterPhiSpread_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterPhiSpread[itr_clust],weight);
		h_dtRechitClusterTimeSpread_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterTimeSpread[itr_clust],weight);
		h_dtRechitClusterMajorAxis_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterMajorAxis[itr_clust],weight);
		h_dtRechitClusterMinorAxis_dPhiJetMET[itr_mX][itr_ctau]->Fill(dtRechitClusterMinorAxis[itr_clust],weight);
		if(passStations25 && passWheels25 && dtRechitClusterMaxStation[itr_clust]>2){
		  nRB1MatchCluster=0;
		  for(Int_t itr_rpc=0; itr_rpc<*nRPCRechits; itr_rpc++){
		    if(sqrt(pow(RPCRechitX[itr_rpc],2)+pow(RPCRechitY[itr_rpc],2))<475.){
		      dPhi_tmp = dtRechitClusterPhi[itr_clust] - RPCRechitPhi[itr_rpc];
		      if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
		      if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
		      if(sqrt(pow(dPhi_tmp,2)+pow(dtRechitClusterEta[itr_clust] - RPCRechitEta[itr_rpc],2))<0.4){
			nRB1MatchCluster+=1;
		      }
		    }
		  }
		  nMB1MatchClusterAdjacentPlus = 0;
		  nMB1MatchClusterAdjacentMinus = 0;
		  for(Int_t itr_dt=0; itr_dt<*nDtRechits; itr_dt++){
		    if(dtRechitStation[itr_dt]==1){
		      dPhi_tmp = dtRechitClusterPhi[itr_clust] - dtRechitPhi[itr_dt];
		      if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
		      if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
		      if(fabs(dPhi_tmp)<0.4){
			if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]+1){ nMB1MatchClusterAdjacentPlus+=1; }
			if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]-1){ nMB1MatchClusterAdjacentMinus+=1; }
		      }
		    }
		  }
		  h_nRB1Match_dPhiJetMET[itr_mX][itr_ctau]->Fill(nRB1MatchCluster);
		  if(dtRechitClusterMaxChamber[itr_clust]==-2){ h_nMB1MatchAdjacent_dPhiJetMET[itr_mX][itr_ctau]->Fill(nMB1MatchClusterAdjacentPlus); }
		  else if(dtRechitClusterMaxChamber[itr_clust]==2){ h_nMB1MatchAdjacent_dPhiJetMET[itr_mX][itr_ctau]->Fill(nMB1MatchClusterAdjacentMinus); }
		  else{
		    h_nMB1MatchAdjacent_dPhiJetMET[itr_mX][itr_ctau]->Fill(nMB1MatchClusterAdjacentPlus);
		    h_nMB1MatchAdjacent_dPhiJetMET[itr_mX][itr_ctau]->Fill(nMB1MatchClusterAdjacentMinus); 
		  }
		  if(passMB1){
		    h_nRB1Match_MB1Veto_dPhiJetMET[itr_mX][itr_ctau]->Fill(nRB1MatchCluster);
		    if(dtRechitClusterMaxChamber[itr_clust]==-2){ h_nMB1MatchAdjacent_MB1Veto_dPhiJetMET[itr_mX][itr_ctau]->Fill(nMB1MatchClusterAdjacentPlus); }
		    else if(dtRechitClusterMaxChamber[itr_clust]==2){ h_nMB1MatchAdjacent_MB1Veto_dPhiJetMET[itr_mX][itr_ctau]->Fill(nMB1MatchClusterAdjacentMinus); }
		    else{
		      h_nMB1MatchAdjacent_MB1Veto_dPhiJetMET[itr_mX][itr_ctau]->Fill(nMB1MatchClusterAdjacentPlus);
		      h_nMB1MatchAdjacent_MB1Veto_dPhiJetMET[itr_mX][itr_ctau]->Fill(nMB1MatchClusterAdjacentMinus); 
		    }
		  }
		}
	      }
	      
	      
	      if(!rpcBx.empty() && rpcSpread>0){ passRPCCR=true; }
	      /*if(itr_clust==0){
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
	      if(*nRPCRechits>750){
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
		  h_nRPCMatched_fullVeto_clusterMETCR[itr_mX][itr_ctau]->Fill(rpcBx.size(),weight);
		  h_rpcSpread_fullVeto_clusterMETCR[itr_mX][itr_ctau]->Fill(rpcSpread,weight);
		  h_rpcBx_fullVeto_clusterMETCR[itr_mX][itr_ctau]->Fill(rpcMedian,weight);
		  h_dPhiJetMET_fullVeto_clusterMETCR[itr_mX][itr_ctau]->Fill(fabs(dPhi_min),weight);
		  h_dtRechitClusterMaxStation_fullVeto_clusterMETCR[itr_mX][itr_ctau]->Fill(dtRechitClusterMaxStation[itr_clust],weight);
		  
		  if(dtRechitClusterMaxStation[itr_clust]>2 && !rpcBx.empty() && nStations25<3 && nWheels25<3){
		    nMB1MatchClusterAdjacentPlus = 0;
		    nMB1MatchClusterAdjacentMinus = 0;
		    nMB1MatchPi2AdjacentPlus = 0;
		    nMB1MatchPi2AdjacentMinus = 0;
		    nMB1MatchClusterAdjacent0p8Plus = 0;
		    nMB1MatchClusterAdjacent0p8Minus = 0;
		    nMB1MatchPi2Adjacent0p8Plus = 0;
		    nMB1MatchPi2Adjacent0p8Minus = 0;
		    for(Int_t itr_dt=0; itr_dt<*nDtRechits; itr_dt++){
		      if(dtRechitStation[itr_dt]==1){
			dPhi_tmp = dtRechitClusterPhi[itr_clust] - dtRechitPhi[itr_dt];
			if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
			if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
			if(fabs(dPhi_tmp)<0.4){
			  if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]+1){ nMB1MatchClusterAdjacentPlus+=1; }
			  if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]-1){ nMB1MatchClusterAdjacentMinus+=1; }
			}
			if(fabs(dPhi_tmp)<TMath::Pi()/4.0){
			  if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]+1){ nMB1MatchClusterAdjacent0p8Plus+=1; }
			  if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]-1){ nMB1MatchClusterAdjacent0p8Minus+=1; }
			}
			dPhi_tmp = dtRechitClusterPhi[itr_clust] - dtRechitPhi[itr_dt] + pmRand*TMath::Pi()/2.0;
			if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
			if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
			if(fabs(dPhi_tmp)<0.4){
			  if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]+1){ nMB1MatchPi2AdjacentPlus+=1; }
			  if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]-1){ nMB1MatchPi2AdjacentMinus+=1; }
			}
			if(fabs(dPhi_tmp)<TMath::Pi()/4.0){
			  if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]+1){ nMB1MatchPi2Adjacent0p8Plus+=1; }
			  if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]-1){ nMB1MatchPi2Adjacent0p8Minus+=1; }
			}
		      }
		    }
		    if(dtRechitClusterMaxChamber[itr_clust]==-2){ 
		      h_nMB1MatchAdjacent_dPhiClusterMET[itr_mX][itr_ctau]->Fill(nMB1MatchClusterAdjacentPlus); 
		      h_nMB1MatchAdjacentPi2_dPhiClusterMET[itr_mX][itr_ctau]->Fill(nMB1MatchPi2AdjacentPlus); 
		      h_nMB1MatchAdjacent0p8_dPhiClusterMET[itr_mX][itr_ctau]->Fill(nMB1MatchClusterAdjacent0p8Plus); 
		      h_nMB1MatchAdjacent0p8Pi2_dPhiClusterMET[itr_mX][itr_ctau]->Fill(nMB1MatchPi2Adjacent0p8Plus); 
		    }
		    else if(dtRechitClusterMaxChamber[itr_clust]==2){ 
		      h_nMB1MatchAdjacent_dPhiClusterMET[itr_mX][itr_ctau]->Fill(nMB1MatchClusterAdjacentMinus); 
		      h_nMB1MatchAdjacentPi2_dPhiClusterMET[itr_mX][itr_ctau]->Fill(nMB1MatchPi2AdjacentMinus); 
		      h_nMB1MatchAdjacent0p8_dPhiClusterMET[itr_mX][itr_ctau]->Fill(nMB1MatchClusterAdjacent0p8Minus); 
		      h_nMB1MatchAdjacent0p8Pi2_dPhiClusterMET[itr_mX][itr_ctau]->Fill(nMB1MatchPi2Adjacent0p8Minus); 
		    }
		    else{
		      h_nMB1MatchAdjacent_dPhiClusterMET[itr_mX][itr_ctau]->Fill(nMB1MatchClusterAdjacentPlus);
		      h_nMB1MatchAdjacent_dPhiClusterMET[itr_mX][itr_ctau]->Fill(nMB1MatchClusterAdjacentMinus); 
		      h_nMB1MatchAdjacentPi2_dPhiClusterMET[itr_mX][itr_ctau]->Fill(nMB1MatchPi2AdjacentPlus);
		      h_nMB1MatchAdjacentPi2_dPhiClusterMET[itr_mX][itr_ctau]->Fill(nMB1MatchPi2AdjacentMinus); 
		      h_nMB1MatchAdjacent0p8_dPhiClusterMET[itr_mX][itr_ctau]->Fill(nMB1MatchClusterAdjacent0p8Plus);
		      h_nMB1MatchAdjacent0p8_dPhiClusterMET[itr_mX][itr_ctau]->Fill(nMB1MatchClusterAdjacent0p8Minus); 
		      h_nMB1MatchAdjacent0p8Pi2_dPhiClusterMET[itr_mX][itr_ctau]->Fill(nMB1MatchPi2Adjacent0p8Plus);
		      h_nMB1MatchAdjacent0p8Pi2_dPhiClusterMET[itr_mX][itr_ctau]->Fill(nMB1MatchPi2Adjacent0p8Minus); 
		    }
		  }
		  
		  if(dtRechitClusterMaxStation[itr_clust]>2){
		    passMaxStation_clusterCR=true;
		    if(!rpcBx.empty()){
		      passRPCMatch_clusterCR=true;
		      if(rpcSpread==0){
			passRPCSpread_clusterCR=true;
			if(rpcMedian>=0.){
			  passRPCBx_clusterCR=true;
			  if(0==0){
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
		  
		  if(!rpcBx.empty() && rpcSpread==0 && rpcMedian>=0.){ h_dtRechitClusterMaxStation_Nminus1_clusterMETCR[itr_mX][itr_ctau]->Fill(dtRechitClusterMaxStation[itr_clust],weight); }
		  if(!rpcBx.empty() && rpcSpread==0 && rpcMedian>=0.){ h_dPhiJetMET_Nminus1_clusterMETCR[itr_mX][itr_ctau]->Fill(fabs(dPhi_min),weight); }
		  if(!rpcBx.empty() && rpcSpread==0 && dtRechitClusterMaxStation[itr_clust]>2){ h_rpcBx_Nminus1_clusterMETCR[itr_mX][itr_ctau]->Fill(rpcMedian,weight); }
		  if(!rpcBx.empty() && rpcMedian>=0. && dtRechitClusterMaxStation[itr_clust]>2){ h_rpcSpread_Nminus1_clusterMETCR[itr_mX][itr_ctau]->Fill(rpcSpread,weight); }
		  if(dtRechitClusterMaxStation[itr_clust]>2){ h_nRPCMatched_Nminus1_clusterMETCR[itr_mX][itr_ctau]->Fill(rpcBx.size(),weight); }
		}

		if(!rpcBx.empty() && rpcSpread==0 && passMuon){
		  passFullVeto_rpcCR=true;
		  h_dPhiClusterMET_fullVeto_rpcCR[itr_mX][itr_ctau]->Fill(fabs(dPhiClusterMET),weight);
		  h_dPhiJetMET_fullVeto_rpcCR[itr_mX][itr_ctau]->Fill(fabs(dPhi_min),weight);
		  h_dtRechitClusterMaxStation_fullVeto_rpcCR[itr_mX][itr_ctau]->Fill(dtRechitClusterMaxStation[itr_clust],weight);
		  
		  if(dtRechitClusterMaxStation[itr_clust]>2){
		    passMaxStation_rpcCR=true;
		    h_dPhiClusterMET_Nminus1_rpcCR[itr_mX][itr_ctau]->Fill(fabs(dPhiClusterMET),weight);
		    h_dPhiJetMET_Nminus1_rpcCR[itr_mX][itr_ctau]->Fill(fabs(dPhi_min),weight);
		    if(fabs(dPhiClusterMET)<1.0){ 
		      passClusterMET_rpcCR=true;
		      if(fabs(dPhi_min)>0.6){
			passJetMET_rpcCR=true;
			if(0==0){
			  passLepton_rpcCR=true;
			  if(nStations50<3 && nWheels50<3){
			    pass50Hits_rpcCR=true;
			    if(nStations25<3 && nWheels25<3){
			      pass25Hits_rpcCR=true;
			    }
			  }
			}
		      }
		    }
		  }
		  if(fabs(dPhiClusterMET)<1.0){
		    h_dtRechitClusterMaxStation_Nminus1_rpcCR[itr_mX][itr_ctau]->Fill(dtRechitClusterMaxStation[itr_clust],weight); 
		  }
		}
		
		if(passMuon){
		  if(!rpcBx.empty() && rpcSpread==0){
		    if(rpcMedian>=0.){
		      if(dtRechitClusterMaxStation[itr_clust]>2){
			if(fabs(dPhi_min)>0.6){
			  if(fabs(dPhiClusterMET)<1.0){
			    if(0==0){
			      if(nStations50<3 && nWheels50<3){
				if(nStations25<3 && nWheels25<3){
				  h_dtRechitClusterSize_signalRegion[itr_mX][itr_ctau]->Fill(dtRechitClusterSize[itr_clust],weight);
				  h_dtRechitClusterSize_fullSelection_rpcCR[itr_mX][itr_ctau]->Fill(dtRechitClusterSize[itr_clust],weight);
				  h_dtRechitClusterSize_fullSelection_clusterMETCR[itr_mX][itr_ctau]->Fill(dtRechitClusterSize[itr_clust],weight);
				  if(dtRechitClusterSize[itr_clust]>100){
				    passSignalRegion=true;
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

		if(passMuon){
		  if(!rpcBx.empty()){
		    if(dtRechitClusterMaxStation[itr_clust]==2){
		      if(fabs(dPhi_min)>0.6){
			if(passMET && passOneJet && passJetMET && nStations25<3 && nWheels25<3){
			  if(dtRechitClusterSize[itr_clust]>=100){
			    if(fabs(dPhiClusterMET)<1.0){
			      passMB2CR = true;
			      nMB1MatchClusterAdjacentPlus = 0;
			      nMB1MatchClusterAdjacentMinus = 0;
			      nMB1MatchClusterAdjacent0p8Plus = 0;
			      nMB1MatchClusterAdjacent0p8Minus = 0;
			      for(Int_t itr_dt=0; itr_dt<*nDtRechits; itr_dt++){
				if(dtRechitStation[itr_dt]==1){
				  dPhi_tmp = dtRechitClusterPhi[itr_clust] - dtRechitPhi[itr_dt];
				  if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
				  if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
				  if(fabs(dPhi_tmp)<0.4){
				    if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]+1){ nMB1MatchClusterAdjacentPlus+=1; }
				    if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]-1){ nMB1MatchClusterAdjacentMinus+=1; }
				  }
				  if(fabs(dPhi_tmp)<TMath::Pi()/4.0){
				    if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]+1){ nMB1MatchClusterAdjacent0p8Plus+=1; }
				    if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]-1){ nMB1MatchClusterAdjacent0p8Minus+=1; }
				  }
				}
			      }
			      if(nMB1MatchClusterAdjacentPlus<5 && nMB1MatchClusterAdjacentMinus<5){
				passMB2CRwithAdjacent = true;
			      }
			      if(nMB1MatchClusterAdjacent0p8Plus<8 && nMB1MatchClusterAdjacent0p8Minus<8){
				passMB2CRwithAdjacent0p8 = true;
			      }
			      if(nMB3MatchCluster<5 && nMB4MatchCluster<5){
				passMB2CRwithOther = true;
			      }
			      if(passNHFJet){
				passMB2CRwithNHF = true;
			      }
			    }
			  }
			}
		      }
		    }
		  }
		}
		
	      }
	    
	      if(passJet && passMET && passOneJet && passJetMET && passStations25 && passWheels25){
		passJetVeto = true;
		if(passMuon){
		  passMuonVeto = true;
		  if(passMB1){
		    passMB1Veto = true;
		    if(dtRechitClusterMaxStation[itr_clust]>2){
		      passMaxStation = true;
		      if(!rpcBx.empty()){
			passRPCMatch = true;
			if(0==0){
			  passRPCSpread = true;
			  if(1>=0){
			    passRPCBx = true;
			    if(fabs(dPhiClusterMET)<1.0){
			      passClusterMET = true;
			      if(dtRechitClusterSize[itr_clust]>=100){
				passClusterSize = true;
				
				h_jetChargedHadronicEnergyFraction_SR[itr_mX][itr_ctau]->Fill(chargedHadFraction_mindPhi);
				h_jetChargedEMEnergyFraction_SR[itr_mX][itr_ctau]->Fill(chargedEMFraction_mindPhi);
				h_jetNeutralHadronicEnergyFraction_SR[itr_mX][itr_ctau]->Fill(neutralHadFraction_mindPhi);
				h_jetNeutralEMEnergyFraction_SR[itr_mX][itr_ctau]->Fill(neutralEMFraction_mindPhi);
				h_leadingJetChargedHadronicEnergyFraction_SR[itr_mX][itr_ctau]->Fill(jetChargedHadronEnergyFraction[0]);
				h_leadingJetChargedEMEnergyFraction_SR[itr_mX][itr_ctau]->Fill(jetElectronEnergyFraction[0]);
				h_leadingJetNeutralHadronicEnergyFraction_SR[itr_mX][itr_ctau]->Fill(jetNeutralHadronEnergyFraction[0]);
				h_leadingJetNeutralEMEnergyFraction_SR[itr_mX][itr_ctau]->Fill(jetPhotonEnergyFraction[0]);
				nMB1MatchClusterAdjacentPlus = 0;
				nMB1MatchClusterAdjacentMinus = 0;
				nMB1MatchClusterAdjacent0p8Plus = 0;
				nMB1MatchClusterAdjacent0p8Minus = 0;
				for(Int_t itr_dt=0; itr_dt<*nDtRechits; itr_dt++){
				  if(dtRechitStation[itr_dt]==1){
				    dPhi_tmp = dtRechitClusterPhi[itr_clust] - dtRechitPhi[itr_dt];
				    if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
				    if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
				    if(fabs(dPhi_tmp)<0.4){
				      if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]+1){ nMB1MatchClusterAdjacentPlus+=1; }
				      if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]-1){ nMB1MatchClusterAdjacentMinus+=1; }
				    }
				    if(fabs(dPhi_tmp)<TMath::Pi()/4.0){
				      if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]+1){ nMB1MatchClusterAdjacent0p8Plus+=1; }
				      if(dtRechitWheel[itr_dt]==dtRechitClusterMaxChamber[itr_clust]-1){ nMB1MatchClusterAdjacent0p8Minus+=1; }
				    }
				  }
				}
				if(nMB1MatchClusterAdjacentPlus<5 && nMB1MatchClusterAdjacentMinus<5){
				  passAdjacentMB1 = true;
				}
				if(nMB1MatchClusterAdjacent0p8Plus<8 && nMB1MatchClusterAdjacent0p8Minus<8){
				  passAdjacent0p8MB1 = true;
				}
				if((dtRechitClusterMaxStation[itr_clust]==3 && nMB2MatchCluster<5 && nMB4MatchCluster<5) || (dtRechitClusterMaxStation[itr_clust]==4 && nMB2MatchCluster<5 && nMB3MatchCluster<5)){
				  passOtherStations = true;
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
	      
	      if(dtRechitClusterNSegmentStation1[itr_clust]==0 && dtRechitClusterMaxStation[itr_clust]>2 && passMET && passOneJet && passJetMET && passStations25 && passWheels25){
		passMB1CR = true;
		if(passJet){
		  passJetVetoMB1CR = true;
		  if(passMuon){
		    passMuonVetoMB1CR = true;
		    if(passMuonLoose){ passMuonVetoLooseMB1CR = true; }
		    if(!rpcBx.empty()){
		      passRpcMatchMB1CR = true;
		      if(fabs(dPhiClusterMET)<1.0){
			passClusterMETMB1CR = true;
			clusterEta.push_back(dtRechitClusterEta[itr_clust]);
			clusterPhi.push_back(dtRechitClusterPhi[itr_clust]);
			clusterSize.push_back(dtRechitClusterSize[itr_clust]);
			if(dtRechitClusterSize[itr_clust]>maxClusterSizeMB1CR){
			    maxClusterSizeMB1CR=dtRechitClusterSize[itr_clust];
			}
			if(dtRechitClusterSize[itr_clust]>100){
			  passClusterSizeMB1CR = true;
			}
		      }
		    }
		  }
		}
	      }
	      
	    }
	  }
	}
	if(passFullVeto_clusterCR){ nPassFullVeto_clusterCR+=weight; }
	if(passRPCMatch_clusterCR){ nPassRPCMatch_clusterCR+=weight; }
	if(passRPCSpread_clusterCR){ nPassRPCSpread_clusterCR+=weight; }
	if(passRPCBx_clusterCR){ nPassRPCBx_clusterCR+=weight; }
	if(passMaxStation_clusterCR){ 
	  nPassMaxStation_clusterCR+=weight; 
	  if(maxClusterSize>150){
	    h_nStations1_150hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nStations1,weight);
	    h_nStations25_150hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nStations25,weight);
	    h_nStations50_150hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nStations50,weight);
	    h_nWheels1_150hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nWheels1,weight);
	    h_nWheels25_150hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nWheels25,weight);
	    h_nWheels50_150hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nWheels50,weight);
	    
	    h_nRPCStations1_150hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCStations1,weight);
	    h_nRPCStations5_150hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCStations5,weight);
	    h_nRPCStations10_150hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCStations10,weight);
	    h_nRPCWheels1_150hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCWheels1,weight);
	    h_nRPCWheels5_150hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCWheels5,weight);
	    h_nRPCWheels10_150hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCWheels10,weight);
	  }
	  else if(maxClusterSize>100){
	    h_nStations1_100hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nStations1,weight);
	    h_nStations25_100hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nStations25,weight);
	    h_nStations50_100hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nStations50,weight);
	    h_nWheels1_100hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nWheels1,weight);
	    h_nWheels25_100hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nWheels25,weight);
	    h_nWheels50_100hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nWheels50,weight);
	    
	    h_nRPCStations1_100hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCStations1,weight);
	    h_nRPCStations5_100hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCStations5,weight);
	    h_nRPCStations10_100hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCStations10,weight);
	    h_nRPCWheels1_100hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCWheels1,weight);
	    h_nRPCWheels5_100hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCWheels5,weight);
	    h_nRPCWheels10_100hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCWheels10,weight);
	  }
	  else{
	    h_nStations1_50hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nStations1,weight);
	    h_nStations25_50hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nStations25,weight);
	    h_nStations50_50hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nStations50,weight);
	    h_nWheels1_50hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nWheels1,weight);
	    h_nWheels25_50hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nWheels25,weight);
	    h_nWheels50_50hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nWheels50,weight);
	    
	    h_nRPCStations1_50hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCStations1,weight);
	    h_nRPCStations5_50hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCStations5,weight);
	    h_nRPCStations10_50hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCStations10,weight);
	    h_nRPCWheels1_50hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCWheels1,weight);
	    h_nRPCWheels5_50hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCWheels5,weight);
	    h_nRPCWheels10_50hits_clusterMETCR[itr_mX][itr_ctau]->Fill(nRPCWheels10,weight);
	  }
	}
	if(passLepton_clusterCR){ nPassLepton_clusterCR+=weight; }
	if(pass50Hits_clusterCR){ nPass50Hits_clusterCR+=weight; }
	if(pass25Hits_clusterCR){ nPass25Hits_clusterCR+=weight; }
	
	if(passRPCCR){ nPassRPCCR+=weight; }
	if(passFullVeto_rpcCR){ nPassFullVeto_rpcCR+=weight; }
	if(passClusterMET_rpcCR){ nPassClusterMET_rpcCR+=weight; }
	if(passMaxStation_rpcCR){ nPassMaxStation_rpcCR+=weight; }
	if(passJetMET_rpcCR){ nPassJetMET_rpcCR+=weight; }
	if(passLepton_rpcCR){ nPassLepton_rpcCR+=weight; }
	if(pass50Hits_rpcCR){ nPass50Hits_rpcCR+=weight; }
	if(pass25Hits_rpcCR){ nPass25Hits_rpcCR+=weight; }
	if(passSignalRegion){ nPassSignalRegion+=weight; }
	if(passMB2CR){ nPassMB2CR+=weight; }
	if(passMB2CRwithAdjacent){ nPassMB2CRwithAdjacent+=weight; }
	if(passMB2CRwithAdjacent0p8){ nPassMB2CRwithAdjacent0p8+=weight; }
	if(passMB2CRwithOther){ nPassMB2CRwithOther+=weight; }
	if(passMB2CRwithNHF){ nPassMB2CRwithNHF+=weight; }

	h_nDtRechitClustersVeto_dPhiJetMET[itr_mX][itr_ctau]->Fill(nClustersVeto_dPhiJetMET,weight);
	if(clusterPhi.size()>1){
	  for(Int_t i=0; i<clusterPhi.size()-1; i++){
	    for(Int_t j=i+1; j<clusterPhi.size(); j++){
	      dPhi_tmp = clusterPhi[i] - clusterPhi[j];
	      if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
	      if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
	      h_dtRechitClustersVetoDR_dPhiJetMET[itr_mX][itr_ctau]->Fill(sqrt(pow(dPhi_tmp,2)+pow(clusterEta[i]-clusterEta[j],2)),weight);
	      if(sqrt(pow(dPhi_tmp,2)+pow(clusterEta[i]-clusterEta[j],2))<0.6){
		clusterSizeTotal+=clusterSize[i];
		clusterSizeTotal+=clusterSize[j];
		break;
	      }
	    }
	  }
	}
	
	if(passMET){
	  h_efficiency[itr_mX][itr_ctau]->Fill(0.0,weight);
	  h_efficiency_MB1CR[itr_mX][itr_ctau]->Fill(0.0,weight);
	  if(passOneJet){
	    h_efficiency[itr_mX][itr_ctau]->Fill(1,weight);
	    h_efficiency_MB1CR[itr_mX][itr_ctau]->Fill(1,weight);
	    if(passJetMET){
	      h_efficiency[itr_mX][itr_ctau]->Fill(2,weight);
	      h_efficiency_MB1CR[itr_mX][itr_ctau]->Fill(2,weight);
	      if(passStations25){
		h_efficiency[itr_mX][itr_ctau]->Fill(3,weight);
		h_efficiency_MB1CR[itr_mX][itr_ctau]->Fill(3,weight);
		if(passWheels25){
		  h_efficiency[itr_mX][itr_ctau]->Fill(4,weight);
		  h_efficiency_MB1CR[itr_mX][itr_ctau]->Fill(4,weight);
		  if(passNoVetoCluster){
		    h_efficiency[itr_mX][itr_ctau]->Fill(5,weight);
		    h_efficiency_MB1CR[itr_mX][itr_ctau]->Fill(5,weight);
		  }
		}
	      }
	    }
	  }
	}
	if(passJetVeto){ h_efficiency[itr_mX][itr_ctau]->Fill(6,weight); }
	if(passMuonVeto){ h_efficiency[itr_mX][itr_ctau]->Fill(7,weight); }
	if(passMB1Veto){ h_efficiency[itr_mX][itr_ctau]->Fill(8,weight); }
	if(passMaxStation){ h_efficiency[itr_mX][itr_ctau]->Fill(9,weight); }
	if(passRPCMatch){ h_efficiency[itr_mX][itr_ctau]->Fill(10,weight); }
	if(passRPCSpread){ h_efficiency[itr_mX][itr_ctau]->Fill(11,weight); }
	if(passRPCBx){ h_efficiency[itr_mX][itr_ctau]->Fill(12,weight); }
	if(passClusterMET){ h_efficiency[itr_mX][itr_ctau]->Fill(13,weight); }
	if(passClusterSize){ h_efficiency[itr_mX][itr_ctau]->Fill(14,weight); }
	if(passAdjacentMB1){ h_efficiency[itr_mX][itr_ctau]->Fill(15,weight); }
	if(passAdjacent0p8MB1){
	  h_efficiency[itr_mX][itr_ctau]->Fill(17,weight); 
	  if(passNHFJet){ h_efficiency[itr_mX][itr_ctau]->Fill(18,weight); }
	}
	if(passOtherStations){ h_efficiency[itr_mX][itr_ctau]->Fill(16,weight); }

	if(passMB1CR){ h_efficiency_MB1CR[itr_mX][itr_ctau]->Fill(6,weight); }
	if(passJetVetoMB1CR){ h_efficiency_MB1CR[itr_mX][itr_ctau]->Fill(7,weight); }
	if(passMuonVetoMB1CR){ h_efficiency_MB1CR[itr_mX][itr_ctau]->Fill(8,weight); }
	if(passRpcMatchMB1CR){ h_efficiency_MB1CR[itr_mX][itr_ctau]->Fill(9,weight); }
	if(passClusterMETMB1CR){ 
	  h_efficiency_MB1CR[itr_mX][itr_ctau]->Fill(10,weight); 
	  h_dtRechitClusterSize_signalRegionNew[itr_mX][itr_ctau]->Fill(maxClusterSizeMB1CR,weight);
	  h_dtRechitClusterSizeTotal_signalRegionNew[itr_mX][itr_ctau]->Fill(max(maxClusterSizeMB1CR,clusterSizeTotal),weight);
	}
	if(passClusterSizeMB1CR){ h_efficiency_MB1CR[itr_mX][itr_ctau]->Fill(11,weight); }
	if(passMuonVetoLooseMB1CR){ h_efficiency_MB1CR[itr_mX][itr_ctau]->Fill(12,weight); }

	evtNum+=1;	
      }
    }
    for(int i=1; i<20; i++){
      if(i > 1){
	if(h_efficiency[itr_mX][itr_ctau]->GetBinContent(i-1)>0){
	  cout << h_efficiency[itr_mX][itr_ctau]->GetBinContent(i) << " (" << h_efficiency[itr_mX][itr_ctau]->GetBinContent(i) / h_efficiency[itr_mX][itr_ctau]->GetBinContent(i-1) << ")" << endl;
	}
	else{
	  cout << h_efficiency[itr_mX][itr_ctau]->GetBinContent(i) << endl;
	}
      }
      else{
	cout << h_efficiency[itr_mX][itr_ctau]->GetBinContent(i) << " (" << h_efficiency[itr_mX][itr_ctau]->GetBinContent(i) / (1000*0.01*48.58*(59.74+41.53+35.92)) << ")" << endl;
      }
    }
    cout << " " << endl;
    cout << "nPassMB2CR: " << nPassMB2CR << endl;
    cout << "nPassMB2CRwithAdjacent: " << nPassMB2CRwithAdjacent << endl;
    cout << "nPassMB2CRwithAdjacent0p8: " << nPassMB2CRwithAdjacent0p8 << endl;
    cout << "nPassMB2CRwithOther: " << nPassMB2CRwithOther << endl;
    cout << "nPassMB2CRwithNHF: " << nPassMB2CRwithNHF << endl;
    cout << " " << endl;
    /*cout << "nPassNoVeto: " << nPassNoVeto << endl;
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
    cout << "nPassSignalRegion: " << nPassSignalRegion << endl;
    */
    }
  }

  _ofile->Write();
  _ofile->Close();

}
    

  
  
