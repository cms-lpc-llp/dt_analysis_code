import ROOT as r
from collections import defaultdict 
import os
r.gROOT.SetBatch(1)
r.gStyle.SetOptStat(0)
inputFile = r.TFile("outSig_ABCD_new.root")
# inputFile = r.TFile("outSig_ABCD_skim.root")
outputHistDict = defaultdict(dict)
colours = {"15":r.kBlack,"40":r.kRed,"55":r.kBlue}
denomHistNames = ["noVeto","clusterReco"]
numHistNames = ["clusterReco","clusterReco_signalRegionEq2","clusterReco_signalRegionGt2","clusterReco_signalRegion"]
outDir = "effPlots_newSR/"
for plot in ["Radius","Z"]:
    for mass in ["15","40","55"]:
        numHists = {}
        denomHists = {}
        for hist in denomHistNames:
            denomHist = inputFile.Get("h_decayVertex{}_{}_{}_10000".format(plot,hist,mass))
            denomHists[hist] = denomHist
        for hist in numHistNames:
            if hist == "clusterReco_signalRegion":continue
            numHist = inputFile.Get("h_decayVertex{}_{}_{}_10000".format(plot,hist,mass))
            numHists[hist] = numHist
        numHists["clusterReco_signalRegion"] = numHists["clusterReco_signalRegionEq2"].Clone()
        numHists["clusterReco_signalRegion"].Add(numHists["clusterReco_signalRegionGt2"])
        # iHistNoVeto = inputFile.Get("h_decayVertex{}_noVeto_{}_10000".format(plot,mass))
        # iHistAtLeastOneCluster = inputFile.Get("h_decayVertex{}_clusterReco_{}_10000".format(plot,mass)) 
        # iHistSignal = inputFile.Get("h_decayVertex{}_clusterReco_signalRegion_{}_10000".format(plot,mass)) 
        for histNum in numHistNames:
            for histDenom in denomHistNames: 
                if histNum == histDenom: continue
                tEff = r.TEfficiency(numHists[histNum],denomHists[histDenom])
                outputHistDict[histNum+"_"+histDenom][mass] = tEff

    if plot == "Radius":
        blankHist = r.TH1D("blankRadius",";Decay radius (cm); Efficiency",800,300,800)
    else:
        blankHist = r.TH1D("blankZ",";Decay Z (cm); Efficiency",800,0,700)
    for plotType,massDict in outputHistDict.items():
        oC = r.TCanvas()
        oC.SetGrid()
        blankHist.Draw()
        blankHist.SetMaximum(1.2)
        blankHist.SetMinimum(0)
        for mass,tEff in massDict.items():
            tEff.SetLineColor(colours[mass])
            tEff.Draw("same")
        if plot == "Radius":
            textRot = r.TLatex()
            textRot.SetTextAngle(90)
            textRot.DrawLatex(350,0.85,"Magnet")
            box1 = r.TBox(320,0,370,1.2)
            box1.SetFillColorAlpha(r.kGray,0.5)
            box1.Draw("same")
            text = r.TLatex()
            text.SetTextSize(0.04)
            text.DrawLatex(400,1.22,"#bf{MB 1}")

            box2 = r.TBox(462,0,490,1.2)
            box2.SetFillColorAlpha(r.kGray,0.5)
            box2.Draw("same")
            text.DrawLatex(500,1.22,"#bf{MB 2}")

            box3 = r.TBox(535,0,597,1.2)
            box3.SetFillColorAlpha(r.kGray,0.5)
            box3.Draw("same")
            text.DrawLatex(600,1.22,"#bf{MB 3}")
            
            box4 = r.TBox(640,0,700,1.2)
            box4.SetFillColorAlpha(r.kGray,0.5)
            box4.Draw("same")
            text.DrawLatex(730,1.22,"#bf{MB 4}")
        if not os.path.exists(outDir):
            os.mkdir(outDir)
        oC.SaveAs(outDir+"/"+plotType+plot+".pdf")
