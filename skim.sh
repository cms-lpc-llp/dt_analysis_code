#!/usr/bin/bash

## script to skim all MC for MET > 200 GeV
cutstring='met>200'

runTest=false
prefix="root://cmseos.fnal.gov/"
signalpath="/store/user/dildick/delayedjetsanalysis/"
alias eosls="eos root://cmseos.fnal.gov ls"

output=$(eos root://cmseos.fnal.gov ls $signalpath | grep MC_Summer16)
echo $output

for x in $output;
do
    echo $signalpath/$x
    fileoutput=$(eos root://cmseos.fnal.gov ls $signalpath/$x)
    for y in $fileoutput;
    do
        fullpath=$signalpath/$x
        ## replace root with skim.root
        firstString=".root"
        secondString=".skim.root"
        newy=${y/$firstString/$secondString}

        if [ "$runTest" = true ] ; then
            echo Running Test
            echo python skimAllRelevantEvents.py $prefix$fullpath/$y $newy $cutstring;
            echo xrdcp $newy $prefix$fullpath/;
            echo rm $newy;
        else
            echo Skimming Files
            python skimAllRelevantEvents.py $prefix$fullpath/$y $newy $cutstring;
            xrdcp $newy $prefix$fullpath/;
            rm $newy;
        fi
    done;
done;
