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

void analyzeData_beamHalo(){

  char name[50];
  char title[100];
  char years[4][10] = {"2018","2017","2016"};
  char runNames[3][20] = {"17Sept2018_Run2018","Run2017","Run2016"};
  char dates[3][20] = {"17Sep2018","17Nov2017","07Aug17"};
  TString dir("/mnt/hadoop/store/group/phys_exotica/delayedjets/displacedJetMuonAnalyzer/driftTube/V1p17/Data");
  TFile *_ofile = TFile::Open("outData_beamHalo.root","RECREATE");

  TH2D *h_jetRechitT_jetEta[4];
  TH1D *h_jetPhi[4];
  TH1D *h_nRpcRechits[4];
  TH1D *h_nDtRechits[4];
  TH1D *h_nDtRechits_MB1[4];
  TH1D *h_nDtRechits_MB2[4];
  TH1D *h_nDtRechits_MB3[4];
  TH1D *h_nDtRechits_MB4[4];
  TH1D *h_nDtRechits_Wheelm2[4];
  TH1D *h_nDtRechits_Wheelm1[4];
  TH1D *h_nDtRechits_Wheel0[4];
  TH1D *h_nDtRechits_Wheel1[4];
  TH1D *h_nDtRechits_Wheel2[4];
  TH1D *h_nRpcRechits_Wheelm2[4];
  TH1D *h_nRpcRechits_Wheelm1[4];
  TH1D *h_nRpcRechits_Wheel0[4];
  TH1D *h_nRpcRechits_Wheel1[4];
  TH1D *h_nRpcRechits_Wheel2[4];
  TH1D *h_nRpcRechits_Layer1[4];
  TH1D *h_nRpcRechits_Layer2[4];
  TH1D *h_nRpcRechits_Layer3[4];
  TH1D *h_nRpcRechits_Layer4[4];
  TH1D *h_nRpcRechits_Layer5[4];  
  TH1D *h_nRpcRechits_Layer6[4];
  TH1D *h_nStation[4];
  TH1D *h_nStationLowThresh[4];
  TH1D *h_nStationThresh[4];
  TH1D *h_nWheel[4];
  TH1D *h_nWheelLowThresh[4];
  TH1D *h_nWheelThresh[4];
  TH2D *h_dtRechitX_dtRechitY[4];
  TH2D *h_dtRechitZ_dtRechitR[4];
  TH2D *h_rpcRechitX_rpcRechitY[4];
  TH2D *h_rpcRechitZ_rpcRechitR[4];
  TH1D *h_nDtRechitClusters_noVeto[4];
  TH1D *h_nDtRechitClusters_fullVeto[4];
  TH1D *h_nDtRechitClusters_fullVetoPlus[4];

  Int_t wheelCount[5];
  Int_t stationCount[4];
  Int_t rpcLayerCount[6];
  Int_t rpcWheelCount[5];
  Int_t rechitWheel = -99;
  Int_t rechitStation = -99;
  Int_t rpcWheel = -99;
  Int_t rpcLayer = -99;
  Int_t nWheel = -1;
  Int_t nWheelLowThresh = -1;
  Int_t nWheelThresh = 1;
  Int_t nStation = -1;
  Int_t nStationLowThresh = -1;
  Int_t nStationThresh = -1;
 
  Double_t dPhi_tmp = 0.0;
  Double_t dPhi_min = 0.0;
  Double_t dPhiClusterMET = 0.0;
  vector<Int_t> rpcBx = {};
  Int_t rpcSpread = 0;

  Int_t evtNum = 0;
  Int_t itr_file = 0;

  Bool_t passCR = false;
  Bool_t passMuon = false;
  Bool_t passMB1 = false;
  Bool_t passJet = false;
  Int_t nPassNoVeto = 0;
  Int_t nPassFull = 0;
  Int_t nPassFullPlus = 0;

  for(Int_t itr_year=0; itr_year<3; itr_year++){

    sprintf(name,"h_jetRechitT_jetEta_%s",years[itr_year]);
    h_jetRechitT_jetEta[itr_year] = new TH2D(name,"",300,-15,15,150,-1.5,1.5);

    sprintf(name,"h_jetPhi_%s",years[itr_year]);
    h_jetPhi[itr_year] = new TH1D(name,"",70,-3.5,3.5);

    sprintf(name,"h_nDtRechits_%s",years[itr_year]);
    h_nDtRechits[itr_year] = new TH1D(name,"",500,0,5000);

    sprintf(name,"h_nRpcRechits_%s",years[itr_year]);
    h_nRpcRechits[itr_year] = new TH1D(name,"",250,0,500);

    sprintf(name,"h_nDtRechits_MB1_%s",years[itr_year]);
    h_nDtRechits_MB1[itr_year] = new TH1D(name,"",250,0,2500);

    sprintf(name,"h_nDtRechits_MB2_%s",years[itr_year]);
    h_nDtRechits_MB2[itr_year] = new TH1D(name,"",250,0,2500);

    sprintf(name,"h_nDtRechits_MB3_%s",years[itr_year]);
    h_nDtRechits_MB3[itr_year] = new TH1D(name,"",250,0,2500);

    sprintf(name,"h_nDtRechits_MB4_%s",years[itr_year]);
    h_nDtRechits_MB4[itr_year] = new TH1D(name,"",250,0,2500);

    sprintf(name,"h_nDtRechits_Wheelm2_%s",years[itr_year]);
    h_nDtRechits_Wheelm2[itr_year] = new TH1D(name,"",250,0,2500);

    sprintf(name,"h_nDtRechits_Wheelm1_%s",years[itr_year]);
    h_nDtRechits_Wheelm1[itr_year] = new TH1D(name,"",250,0,2500);

    sprintf(name,"h_nDtRechits_Wheel0_%s",years[itr_year]);
    h_nDtRechits_Wheel0[itr_year] = new TH1D(name,"",250,0,2500);

    sprintf(name,"h_nDtRechits_Wheel1_%s",years[itr_year]);
    h_nDtRechits_Wheel1[itr_year] = new TH1D(name,"",250,0,2500);

    sprintf(name,"h_nDtRechits_Wheel2_%s",years[itr_year]);
    h_nDtRechits_Wheel2[itr_year] = new TH1D(name,"",250,0,2500);

    sprintf(name,"h_nRpcRechits_Wheelm2_%s",years[itr_year]);
    h_nRpcRechits_Wheelm2[itr_year] = new TH1D(name,"",500,0,2500);

    sprintf(name,"h_nRpcRechits_Wheelm1_%s",years[itr_year]);
    h_nRpcRechits_Wheelm1[itr_year] = new TH1D(name,"",500,0,2500);

    sprintf(name,"h_nRpcRechits_Wheel0_%s",years[itr_year]);
    h_nRpcRechits_Wheel0[itr_year] = new TH1D(name,"",500,0,2500);

    sprintf(name,"h_nRpcRechits_Wheel1_%s",years[itr_year]);
    h_nRpcRechits_Wheel1[itr_year] = new TH1D(name,"",500,0,2500);

    sprintf(name,"h_nRpcRechits_Wheel2_%s",years[itr_year]);
    h_nRpcRechits_Wheel2[itr_year] = new TH1D(name,"",500,0,2500);

    sprintf(name,"h_nRpcRechits_Layer1_%s",years[itr_year]);
    h_nRpcRechits_Layer1[itr_year] = new TH1D(name,"",500,0,2500);

    sprintf(name,"h_nRpcRechits_Layer2_%s",years[itr_year]);
    h_nRpcRechits_Layer2[itr_year] = new TH1D(name,"",500,0,2500);

    sprintf(name,"h_nRpcRechits_Layer3_%s",years[itr_year]);
    h_nRpcRechits_Layer3[itr_year] = new TH1D(name,"",500,0,2500);

    sprintf(name,"h_nRpcRechits_Layer4_%s",years[itr_year]);
    h_nRpcRechits_Layer4[itr_year] = new TH1D(name,"",500,0,2500);

    sprintf(name,"h_nRpcRechits_Layer5_%s",years[itr_year]);
    h_nRpcRechits_Layer5[itr_year] = new TH1D(name,"",500,0,2500);

    sprintf(name,"h_nRpcRechits_Layer6_%s",years[itr_year]);
    h_nRpcRechits_Layer6[itr_year] = new TH1D(name,"",500,0,2500);

    sprintf(name,"h_nStation_%s",years[itr_year]);
    h_nStation[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStationLowThresh_%s",years[itr_year]);
    h_nStationLowThresh[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nStationThresh_%s",years[itr_year]);
    h_nStationThresh[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nWheel_%s",years[itr_year]);
    h_nWheel[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheelLowThresh_%s",years[itr_year]);
    h_nWheelLowThresh[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_nWheelThresh_%s",years[itr_year]);
    h_nWheelThresh[itr_year] = new TH1D(name,"",6,0,6);

    sprintf(name,"h_dtRechitX_dtRechitY_%s",years[itr_year]);
    h_dtRechitX_dtRechitY[itr_year] = new TH2D(name,"",320,-800,800,320,-800,800);

    sprintf(name,"h_rpcRechitX_rpcRechitY_%s",years[itr_year]);
    h_rpcRechitX_rpcRechitY[itr_year] = new TH2D(name,"",320,-800,800,320,-800,800);
  
    sprintf(name,"h_dtRechitZ_dtRechitR_%s",years[itr_year]);
    h_dtRechitZ_dtRechitR[itr_year] = new TH2D(name,"",240,-600,600,80,400,800);

    sprintf(name,"h_rpcRechitZ_rpcRechitR_%s",years[itr_year]);
    h_rpcRechitZ_rpcRechitR[itr_year] = new TH2D(name,"",240,-600,600,80,400,800);

    sprintf(name,"h_nDtRechitClusters_noVeto_%s",years[itr_year]);
    h_nDtRechitClusters_noVeto[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nDtRechitClusters_fullVeto_%s",years[itr_year]);
    h_nDtRechitClusters_fullVeto[itr_year] = new TH1D(name,"",5,0,5);

    sprintf(name,"h_nDtRechitClusters_fullVetoPlus_%s",years[itr_year]);
    h_nDtRechitClusters_fullVetoPlus[itr_year] = new TH1D(name,"",5,0,5);

    TFile *_file;
    if(strcmp(years[itr_year],"All")==0){
      _file = TFile::Open(dir+years[itr_year]+"/v4/v4/normalized/Run2_displacedJetMuonNtupler_V1p15_Data2016_Data2017_Data2018-HighMET_goodLumi.root");
    }
    else{
      _file = TFile::Open(dir+years[itr_year]+"/v1/v3/normalized/Run2_displacedJetMuonNtupler_V1p17_Data"+years[itr_year]+"_"+runNames[itr_year]+"-HighMET-"+dates[itr_year]+"_goodLumi.root");
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

    _ofile->cd();
    evtNum = 0;
    cout << "Data" << years[itr_year] << endl;
    while(treeReader.Next()){
      fill_n(wheelCount, 5, 0);
      fill_n(stationCount, 4, 0);
      fill_n(rpcLayerCount, 6, 0);
      fill_n(rpcWheelCount, 5, 0);
      nWheel = 0;
      nWheelLowThresh = 0;
      nWheelThresh = 0;
      nStation = 0;
      nStationLowThresh = 0;
      nStationThresh = 0;
      passCR = false;
      nPassNoVeto = 0;
      nPassFull = 0;
      nPassFullPlus = 0;
      dPhi_min = 999.;
      if(evtNum%100000==0){ cout << evtNum << " of " << treeReader.GetEntries(1) << endl; }
      
      if(*MET > 200){
	
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
	if(fabs(dPhi_min)<0.6){ passCR = true; }

	if(passCR){

	  if(*nDtRechits<750){
	    for(Int_t itr_dt = 0; itr_dt<*nDtRechits; itr_dt++){
	      h_dtRechitX_dtRechitY[itr_year]->Fill(dtRechitX[itr_dt],dtRechitY[itr_dt]);
	      h_dtRechitZ_dtRechitR[itr_year]->Fill(dtRechitZ[itr_dt],sqrt(pow(dtRechitX[itr_dt],2)+pow(dtRechitY[itr_dt],2)));
	      rechitWheel = getWheel(dtRechitZ[itr_dt]);
	      rechitWheel+=2;
	      if(rechitWheel>=0 && rechitWheel<5){
		wheelCount[rechitWheel] += 1;
	      }
	      rechitStation = getStation(dtRechitX[itr_dt],dtRechitY[itr_dt]);
	      if(rechitStation>-1){
		stationCount[rechitStation-1] += 1;
	      }
	    }
	  }
	  else{
	    fill_n(wheelCount, 5, 150);
	    fill_n(stationCount, 4, 150);
	  }
	  for(Int_t itr_wheel = 0; itr_wheel<5; itr_wheel++){
	    if(wheelCount[itr_wheel] > 0){ nWheel += 1; }
	    if(wheelCount[itr_wheel] > 4){ nWheelLowThresh += 1; }
	    if(wheelCount[itr_wheel] > 12){ nWheelThresh += 1; }
	  }
	  for(Int_t itr_station = 0; itr_station<4; itr_station++){
	    if(stationCount[itr_station]>0){ nStation += 1; }
	    if(itr_station<3){
	      if(stationCount[itr_station]>12){ nStationThresh += 1; }
	      if(stationCount[itr_station]>4){ nStationLowThresh += 1; }
	    }
	    else{
	      if(stationCount[itr_station]>8){ nStationThresh += 1; }
	      if(stationCount[itr_station]>2){ nStationLowThresh += 1; }
	    }
	  }

	  h_nDtRechits[itr_year]->Fill(*nDtRechits);
	  h_nRpcRechits[itr_year]->Fill(*nRPCRechits);
	  h_nDtRechits_MB1[itr_year]->Fill(stationCount[0]);
	  h_nDtRechits_MB2[itr_year]->Fill(stationCount[1]);
	  h_nDtRechits_MB3[itr_year]->Fill(stationCount[2]);
	  h_nDtRechits_MB4[itr_year]->Fill(stationCount[3]);
	  h_nDtRechits_Wheelm2[itr_year]->Fill(wheelCount[0]);
	  h_nDtRechits_Wheelm1[itr_year]->Fill(wheelCount[1]);
	  h_nDtRechits_Wheel0[itr_year]->Fill(wheelCount[2]);
	  h_nDtRechits_Wheel1[itr_year]->Fill(wheelCount[3]);
	  h_nDtRechits_Wheel2[itr_year]->Fill(wheelCount[4]);
	  h_nStation[itr_year]->Fill(nStation);
	  h_nStationLowThresh[itr_year]->Fill(nStationLowThresh);
	  h_nStationThresh[itr_year]->Fill(nStationThresh);
	  h_nWheel[itr_year]->Fill(nWheel);
	  h_nWheelLowThresh[itr_year]->Fill(nWheelLowThresh);
	  h_nWheelThresh[itr_year]->Fill(nWheelThresh);

	  for(Int_t itr_jet = 0; itr_jet<*nJets; itr_jet++){
	    h_jetRechitT_jetEta[itr_year]->Fill(jetRechitT[itr_jet],jetEta[itr_jet]);
	    h_jetPhi[itr_year]->Fill(jetPhi[itr_jet]);
	  }

	  for(Int_t itr_rpc = 0; itr_rpc<*nRPCRechits; itr_rpc++){
	    if(RPCRechitZ[itr_rpc]<661.){
	      h_rpcRechitX_rpcRechitY[itr_year]->Fill(RPCRechitX[itr_rpc],RPCRechitY[itr_rpc]);
	      h_rpcRechitZ_rpcRechitR[itr_year]->Fill(RPCRechitZ[itr_rpc],sqrt(pow(RPCRechitX[itr_rpc],2)+pow(RPCRechitY[itr_rpc],2)));
	      rpcLayer = getRPCLayer(RPCRechitX[itr_rpc],RPCRechitY[itr_rpc]);
	      if(rpcLayer>-1){
		rpcLayerCount[rpcLayer-1]+=1;
	      }
	      rpcWheel = getWheel(RPCRechitZ[itr_rpc]);
	      rpcWheel+=2;
	      if(rpcWheel>=0 && rpcWheel<5){
		rpcWheelCount[rpcWheel] += 1;
	      }
	    }
	  }
	
	  h_nRpcRechits_Layer1[itr_year]->Fill(rpcLayerCount[0]);
	  h_nRpcRechits_Layer2[itr_year]->Fill(rpcLayerCount[1]);
	  h_nRpcRechits_Layer3[itr_year]->Fill(rpcLayerCount[2]);
	  h_nRpcRechits_Layer4[itr_year]->Fill(rpcLayerCount[3]);
	  h_nRpcRechits_Layer5[itr_year]->Fill(rpcLayerCount[4]);
	  h_nRpcRechits_Layer6[itr_year]->Fill(rpcLayerCount[5]);
	  h_nRpcRechits_Wheelm2[itr_year]->Fill(rpcWheelCount[0]);
	  h_nRpcRechits_Wheelm1[itr_year]->Fill(rpcWheelCount[1]);
	  h_nRpcRechits_Wheel0[itr_year]->Fill(rpcWheelCount[2]);
	  h_nRpcRechits_Wheel1[itr_year]->Fill(rpcWheelCount[3]);
	  h_nRpcRechits_Wheel2[itr_year]->Fill(rpcWheelCount[4]);

	  for(Int_t itr_clust = 0; itr_clust<*nDtRechitClusters; itr_clust++){
	    rpcBx.clear();
	    passJet = false;
	    passMuon = false;
	    passMB1 = false;
	    if(dtRechitClusterJetVetoPt[itr_clust]<20.){ passJet = true; }
	    if(dtRechitClusterMuonVetoPt[itr_clust]<10.){ passMuon = true; }
	    if(dtRechitClusterNSegmentStation1[itr_clust]==0){ passMB1 = true; }

	    dPhiClusterMET = dtRechitClusterPhi[itr_clust] - *METphi;
	    if(dPhiClusterMET > TMath::Pi()){ dPhiClusterMET -= 2*TMath::Pi(); }
	    if(dPhiClusterMET < -1.0*TMath::Pi()){ dPhiClusterMET += 2*TMath::Pi(); }

	    if(dtRechitClusterSize[itr_clust]>50 && ((dtRechitClusterPhi[itr_clust]<0.4 || dtRechitClusterPhi[itr_clust]>0.6) || (*runNum<275.75e3 || *runNum>275.95e3))){
	      nPassNoVeto += 1;

	      for(Int_t itr_rpc=0; itr_rpc<*nRPCRechits; itr_rpc++){
		dPhi_tmp = RPCRechitPhi[itr_rpc] - dtRechitClusterPhi[itr_clust];
		if(dPhi_tmp > TMath::Pi()){ dPhi_tmp -= 2*TMath::Pi(); }
		if(dPhi_tmp < -1.0*TMath::Pi()){ dPhi_tmp += 2*TMath::Pi(); }
		if(fabs(RPCRechitZ[itr_rpc] - dtRechitClusterZ[itr_clust])<5. && fabs(dPhi_tmp)<0.4){
		  rpcBx.push_back(RPCRechitBx[itr_rpc]);
		}
	      }
	      if(!rpcBx.empty()){
		rpcSpread = max_element(rpcBx.begin(), rpcBx.end()) - min_element(rpcBx.begin(), rpcBx.end());
	      }

	      if(passJet && passMuon && passMB1){
		nPassFull += 1;
		
		if(!rpcBx.empty()){
		  if(rpcSpread==0){
		    if(dtRechitClusterMaxStation[itr_clust]>2){
		      if(fabs(dPhiClusterMET)<1.0){
			nPassFullPlus += 1;
		      }
		    }
		  }
		}
	      }
	    }
	  }

	  h_nDtRechitClusters_noVeto[itr_year]->Fill(nPassNoVeto);
	  h_nDtRechitClusters_fullVeto[itr_year]->Fill(nPassFull);
	  h_nDtRechitClusters_fullVetoPlus[itr_year]->Fill(nPassFullPlus);

	}
      }
      evtNum+=1;
    }
  }

  _ofile->Write();
  _ofile->Close();

}
