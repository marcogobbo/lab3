// c++ -o compute spectreUW878.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"

using namespace std;

double gaussFit (double* x, double* par) {
  	return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

double pol0 (double*x, double* par) {
    return par[0];
}

double totalFit (double* x, double* par) {
    return gaussFit(x, par) + pol0(x, &par[3]);
}



int main() {
    Analyzer UW878;
    string fileName = "data/Calibration/UW878.txt";

    // Creo il vettore dove salvare i dati, min e max
    vector<double> data;
    double min, max;

    // Carico i dati controllando che non via siano errori
    if (UW878.loadData(fileName, data, min, max) == false) {
        cout << "Errore nel caricare il file: " << fileName.c_str() << endl;
    };

    //gStyle->SetOptFit(1112);
    gStyle->SetOptStat("");

    TH1D* histoUW878 = new TH1D("Data", "UW878", 16384, 0, 16384);

    for (unsigned int i = 0; i < data.size(); i++) {
        histoUW878->SetBinContent(i, data[i]);
    }

    TCanvas* canvasSource = new TCanvas("canvasSource", "canvasSource", 0, 0, 800, 500);

    canvasSource->cd();

    histoUW878->Draw();
    histoUW878->SetFillColor(kYellow-10);
    histoUW878->GetXaxis()->SetTitle("Channels [mV]");
    histoUW878->GetYaxis()->SetTitle("Counts");
    histoUW878->GetXaxis()->SetRangeUser(210, 300);

    TF1* funcFit = new TF1("funcFit", totalFit, 210, 300, 4);
    funcFit->SetParName(0,"Amp");
    funcFit->SetParName(1,"Mean");
    funcFit->SetParName(2,"Std Dev");
    funcFit->SetParName(3,"Noise");
    funcFit->SetParameter(0, 8000);
    funcFit->SetParameter(1, 251);
    funcFit->SetParameter(2, 15);
    funcFit->SetParameter(3, 200);

    histoUW878->Fit("funcFit");
    cout << "AREA: " << histoUW878->Integral(245, 265) << endl;
    //canvasSource->SetLogy();
    canvasSource->Print("graphsNoData/spectreUW878/graph_UW878_peak1.pdf");

    // Libero la memoria
    delete histoUW878;
    delete funcFit;
    delete canvasSource;
}
