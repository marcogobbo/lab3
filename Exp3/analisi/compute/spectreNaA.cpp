// c++ -o compute spectreNaA.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

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

void computeHisto (string element, string nameSource, string peak, int bin, double limInf, double limSup, bool logScale, bool noData) {
    Analyzer Spectre;
    string fileName = "../data/materiali/" + element + "/" + nameSource + ".dat";

    vector<double> data;
    double min, max;

    // Carico i dati controllando che non via siano errori
    if (Spectre.loadData(fileName, data, min, max) == false) {
        cout << "Errore nel caricare il file: " << fileName.c_str() << endl;
    };

    // Imposto il numero di bin
    int nBin = bin;

    if (noData) {
        gStyle->SetOptStat("");
    }
    else {
        gStyle->SetOptFit(1112);
    }
    
    TString titleGraph = nameSource;
    TString namePDF;
    if (noData) {
        namePDF = "../graphsNoData/spectre_" + nameSource + peak + "LOG.pdf";
    }
    else {
        namePDF = "../graphs/spectre_" + nameSource + peak + "LOG.pdf"; 
    }
    
    TH1D* histoSpectre = new TH1D("Data", titleGraph, nBin, 0, 8192);

    for (unsigned int i = 0; i < data.size(); i++) {
        histoSpectre->SetBinContent(i, data[i]);
    }

    TCanvas* canvasSpectre = new TCanvas("canvasSpectre", "canvasSpectre", 0, 0, 800, 500);

    canvasSpectre->cd();

    histoSpectre->Draw();
    histoSpectre->SetFillColor(kYellow-10);
    histoSpectre->GetXaxis()->SetTitle("Channels [mV]");
    histoSpectre->GetYaxis()->SetTitle("Counts");
    histoSpectre->GetXaxis()->SetRangeUser(limInf, limSup);

    // Da commentare se si vuole lo spettro totale o da sostituire con il fit corretto presente in compute/codeFit/...
    /*TF1* funcFit = new TF1("funcFit", totalFit, limInf, limSup, 4);
    funcFit->SetParName(0,"Amp");
    funcFit->SetParName(1,"Mean");
    funcFit->SetParName(2,"Std Dev");
    funcFit->SetParName(3,"Noise");
    funcFit->SetParameter(0, 250);
    funcFit->SetParameter(1, 3222);
    funcFit->SetParameter(2, 10);
    funcFit->SetParameter(3, 10);
    funcFit->SetParLimits(0, 200, 400);

    histoSpectre->Fit("funcFit");

    // Calcolo le aree
    TF1* gaussian = new TF1("gaussian", gaussFit, limInf, limSup, 3);
    gaussian->SetParameter(0, funcFit->GetParameter(0));
    gaussian->SetParameter(1, funcFit->GetParameter(1));
    gaussian->SetParameter(2, funcFit->GetParameter(2));
    gaussian->SetParError(0, funcFit->GetParError(0));
    gaussian->SetParError(1, funcFit->GetParError(1));
    gaussian->SetParError(2, funcFit->GetParError(2));

    fstream OutFile;
    OutFile.open("areeNaA.txt", fstream::app);
    OutFile << namePDF <<":\t"<< gaussian->Integral(1230, 1260) << " +/- " << funcFit->IntegralError(1230, 1260) << endl;
    OutFile.close();*/

    if (logScale) {
        canvasSpectre->SetLogy();
    }

    canvasSpectre->Print(namePDF);

    // Libero la memoria
    delete histoSpectre;
    delete canvasSpectre;
}


int main() {
    // SODIO ACQUA 4 cm
    computeHisto ("acqua", "sodio_acqua_04cm", "", 8192, 0, 8192, true, false);
    computeHisto ("acqua", "sodio_acqua_04cm", "", 8192, 0, 8192, true, true);



    // PICCO 1 SODIO ACQUA 4 cm
    //computeHisto ("acqua", "sodio_acqua_04cm", "1", 8192, 1225, 1265, false, false);
    //computeHisto ("acqua", "sodio_acqua_04cm", "1", 8192, 1225, 1265, false, true);



    // PICCO 2 SODIO ACQUA 4 cm
    //computeHisto ("acqua", "sodio_acqua_04cm", "2", 8192, 3200, 3240, false, false);
    //computeHisto ("acqua", "sodio_acqua_04cm", "2", 8192, 3200, 3240, false, true);



    // SODIO ACQUA 8 cm
    computeHisto ("acqua", "sodio_acqua_08cm", "", 8192, 0, 8192, true, false);
    computeHisto ("acqua", "sodio_acqua_08cm", "", 8192, 0, 8192, true, true);



    // PICCO 1 SODIO ACQUA 8 cm
    //computeHisto ("acqua", "sodio_acqua_08cm", "1", 8192, 1225, 1265, false, false);
    //computeHisto ("acqua", "sodio_acqua_08cm", "1", 8192, 1225, 1265, false, true);



    // PICCO 2 SODIO ACQUA 8 cm
    //computeHisto ("acqua", "sodio_acqua_08cm", "2", 8192, 3200, 3240, false, false);
    //computeHisto ("acqua", "sodio_acqua_08cm", "2", 8192, 3200, 3240, false, true);



    // SODIO ACQUA 12 cm
    computeHisto ("acqua", "sodio_acqua_12cm", "", 8192, 0, 8192, true, false);
    computeHisto ("acqua", "sodio_acqua_12cm", "", 8192, 0, 8192, true, true);



    // PICCO 1 SODIO ACQUA 12 cm
    //computeHisto ("acqua", "sodio_acqua_12cm", "1", 8192, 1225, 1265, false, false);
    //computeHisto ("acqua", "sodio_acqua_12cm", "1", 8192, 1225, 1265, false, true);



    // PICCO 2 SODIO ACQUA 12 cm
    //computeHisto ("acqua", "sodio_acqua_12cm", "2", 8192, 3200, 3240, false, false);
    //computeHisto ("acqua", "sodio_acqua_12cm", "2", 8192, 3200, 3240, false, true);



    // SODIO ACQUA 16 cm
    computeHisto ("acqua", "sodio_acqua_16cm", "", 8192, 0, 8192, true, false);
    computeHisto ("acqua", "sodio_acqua_16cm", "", 8192, 0, 8192, true, true);



    // PICCO 1 SODIO ACQUA 16 cm
    //computeHisto ("acqua", "sodio_acqua_16cm", "1", 8192, 1225, 1265, false, false);
    //computeHisto ("acqua", "sodio_acqua_16cm", "1", 8192, 1225, 1265, false, true);



    // PICCO 2 SODIO ACQUA 16 cm
    //computeHisto ("acqua", "sodio_acqua_16cm", "2", 8192, 3200, 3240, false, false);
    //computeHisto ("acqua", "sodio_acqua_16cm", "2", 8192, 3200, 3240, false, true);



    // SODIO ACQUA 20 cm
    computeHisto ("acqua", "sodio_acqua_20cm", "", 8192, 0, 8192, true, false);
    computeHisto ("acqua", "sodio_acqua_20cm", "", 8192, 0, 8192, true, true);



    // PICCO 1 SODIO ACQUA 20 cm
    //computeHisto ("acqua", "sodio_acqua_20cm", "1", 8192, 1225, 1265, false, false);
    //computeHisto ("acqua", "sodio_acqua_20cm", "1", 8192, 1225, 1265, false, true);



    // PICCO 2 SODIO ACQUA 20 cm
    //computeHisto ("acqua", "sodio_acqua_20cm", "2", 8192, 3200, 3240, false, false);
    //computeHisto ("acqua", "sodio_acqua_20cm", "2", 8192, 3200, 3240, false, true);
    


    // PICCO 1460KeV 4 cm
    //computeHisto ("acqua", "sodio_acqua_04cm", "3", 8192, 3650, 3750, false, false);
    //computeHisto ("acqua", "sodio_acqua_04cm", "3", 8192, 3650, 3750, false, true);

    // PICCO 1460KeV 8 cm
    //computeHisto ("acqua", "sodio_acqua_08cm", "3", 8192, 3650, 3750, false, false);
    //computeHisto ("acqua", "sodio_acqua_08cm", "3", 8192, 3650, 3750, false, true);

    // PICCO 1460KeV 12 cm
    //computeHisto ("acqua", "sodio_acqua_12cm", "3", 8192, 3650, 3750, false, false);
    //computeHisto ("acqua", "sodio_acqua_12cm", "3", 8192, 3650, 3750, false, true);

    // PICCO 1460KeV 16 cm
    //computeHisto ("acqua", "sodio_acqua_16cm", "3", 8192, 3650, 3750, false, false);
    //computeHisto ("acqua", "sodio_acqua_16cm", "3", 8192, 3650, 3750, false, true);

    // PICCO 1460KeV 20 cm
    //computeHisto ("acqua", "sodio_acqua_20cm", "3", 8192, 3650, 3750, false, false);
    //computeHisto ("acqua", "sodio_acqua_20cm", "3", 8192, 3650, 3750, false, true);
}
