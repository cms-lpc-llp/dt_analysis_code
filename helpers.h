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
