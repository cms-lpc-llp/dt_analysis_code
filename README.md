# dt_analysis_code

<PRE>
cmsrel CMSSW_10_2_18
cd CMSSW_10_2_18
cd src
cmsenv
git cms-init
git clone git@github.com:dildick/dt_analysis_code.git
</PRE>

Running the signal analysis

<PRE>
root -l -q -b analyzeSignal_ABCD.C++
</PRE>

Running the data analysis

<PRE>
root -l -q -b analyzeData_ABCD.C++
</PRE>
