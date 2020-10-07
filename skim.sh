#!/usr/bin/bash

python skimAllRelevantEvents.py ggH_HToSSTobbbb_MH-125_MS-15_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root ggH_HToSSTobbbb_MH-125_MS-15_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.skim.root 'met>200'

python skimAllRelevantEvents.py ggH_HToSSTobbbb_MH-125_MS-40_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root ggH_HToSSTobbbb_MH-125_MS-40_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.skim.root 'met>200'

python skimAllRelevantEvents.py ggH_HToSSTobbbb_MH-125_MS-55_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root ggH_HToSSTobbbb_MH-125_MS-55_ctau-1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.skim.root 'met>200'
