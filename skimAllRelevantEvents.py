import ROOT as r
import pickle
import os
import sys
r.gROOT.SetBatch(True)
r.gStyle.SetOptStat(0)

def makeSkim(inputFile,outputFile,cutString,test=False):
    if inputFile == outputFile:
        print "DON'T OVERWRITE THE INPUT!"
        exit()
    inputFile = r.TFile.Open(inputFile)
    tree = inputFile.Get("MuonSystem")
    if test:
        tree.Draw(">>eList",cutString,"entryList",1000);
    else:
        tree.Draw(">>eList",cutString,"entryList",);
    eList = r.gDirectory.Get("eList");
    tree.SetEntryList(eList);
    newFile = r.TFile(outputFile,"RECREATE");
    newTree = tree.CloneTree(0)
    for i in range(eList.GetN()):
        iEntry = eList.GetEntry(i)
        tree.GetEntry(iEntry)
        newTree.Fill()

    newTree.AutoSave()
    oHist = inputFile.Get("NEvents")
    newFile.cd()
    oHist.Write()

if __name__ == "__main__":
    defaultCutString = "nDtRechitClusters>0"
    if len(sys.argv) < 3:
        print "usage python skimAllRelevantEvents.py <inputFile> <outputFile> <optional: cut string>"
        exit()
    inputFile = sys.argv[1]
    outputFile = sys.argv[2]
    if len(sys.argv) == 4:
        cutString = sys.argv[3]
    else:
        cutString = defaultCutString
    makeSkim(inputFile,outputFile,cutString)
