// c++ -o compute spectreThRame.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

double gaussFit (double* x, double* par) {
  	return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

double pol0 (double*x, double* par) {
    return par[0];
}

double totalFit (double* x, double* par) {
    return gaussFit(x, par) + pol0(x, &par[3]); //+ gaussFit(x, &par[4]);
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
    funcFit->SetParName(4,"Amp_PileUp");
    funcFit->SetParName(5,"Mean_PileUp");
    funcFit->SetParName(6,"Std Dev_PileUp");
    funcFit->SetParameter(0, 150);
    funcFit->SetParameter(1, 6685);
    funcFit->SetParameter(2, 5);
    funcFit->SetParameter(3, 5);
    funcFit->SetParameter(4, 2500);
    funcFit->SetParameter(5, 2978);
    funcFit->SetParameter(6, 10);

    //histoSpectre->Fit("funcFit");

    // Calcolo le aree
    TF1* gaussian = new TF1("gaussian", gaussFit, limInf, limSup, 3);
    gaussian->SetParameter(0, funcFit->GetParameter(0));
    gaussian->SetParameter(1, funcFit->GetParameter(1));
    gaussian->SetParameter(2, funcFit->GetParameter(2));
    gaussian->SetParError(0, funcFit->GetParError(0));
    gaussian->SetParError(1, funcFit->GetParError(1));
    gaussian->SetParError(2, funcFit->GetParError(2));

    fstream OutFile;
    OutFile.open("areeThRame.txt", fstream::app);
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
    // TORIO RAME 0.11 cm
    computeHisto ("rame", "torio_rame_011cm", "", 8192, 0, 8192, true, false);
    computeHisto ("rame", "torio_rame_011cm", "", 8192, 0, 8192, true, true);


    // PICCO 1 TORIO RAME 0.11 cm
    //computeHisto ("rame", "torio_rame_011cm", "1", 8192, 510, 570, false, false);
    //computeHisto ("rame", "torio_rame_011cm", "1", 8192, 510, 570, false, true);


    // PICCO 2 TORIO RAME 0.11 cm
    //computeHisto ("rame", "torio_rame_011cm", "2", 8192, 1415, 1450, false, false);
    //computeHisto ("rame", "torio_rame_011cm", "2", 8192, 1415, 1450, false, true);


    // PICCO 3 TORIO RAME 0.11 cm
    //computeHisto ("rame", "torio_rame_011cm", "3", 8192, 6640, 6720, false, false);
    //computeHisto ("rame", "torio_rame_011cm", "3", 8192, 6640, 6720, false, true);




    // TORIO RAME 0.22 cm
    computeHisto ("rame", "torio_rame_022cm", "", 8192, 0, 8192, true, false);
    computeHisto ("rame", "torio_rame_022cm", "", 8192, 0, 8192, true, true);


    // PICCO 1 TORIO RAME 0.22 cm
    //computeHisto ("rame", "torio_rame_022cm", "1", 8192, 510, 570, false, false);
    //computeHisto ("rame", "torio_rame_022cm", "1", 8192, 510, 570, false, true);


    // PICCO 2 TORIO RAME 0.22 cm
    //computeHisto ("rame", "torio_rame_022cm", "2", 8192, 1415, 1450, false, false);
    //computeHisto ("rame", "torio_rame_022cm", "2", 8192, 1415, 1450, false, true);


    // PICCO 3 TORIO RAME 0.22 cm
    //computeHisto ("rame", "torio_rame_022cm", "3", 8192, 6640, 6720, false, false);
    //computeHisto ("rame", "torio_rame_022cm", "3", 8192, 6640, 6720, false, true);




    // TORIO RAME 0.33 cm
    computeHisto ("rame", "torio_rame_033cm", "", 8192, 0, 8192, true, false);
    computeHisto ("rame", "torio_rame_033cm", "", 8192, 0, 8192, true, true);


    // PICCO 1 TORIO RAME 0.33 cm
    //computeHisto ("rame", "torio_rame_033cm", "1", 8192, 510, 570, false, false);
    //computeHisto ("rame", "torio_rame_033cm", "1", 8192, 510, 570, false, true);


    // PICCO 2 TORIO RAME 0.33 cm
    //computeHisto ("rame", "torio_rame_033cm", "2", 8192, 1415, 1450, false, false);
    //computeHisto ("rame", "torio_rame_033cm", "2", 8192, 1415, 1450, false, true);


    // PICCO 3 TORIO RAME 0.33 cm
    //computeHisto ("rame", "torio_rame_033cm", "3", 8192, 6640, 6720, false, false);
    //computeHisto ("rame", "torio_rame_033cm", "3", 8192, 6640, 6720, false, true);




    // TORIO RAME 0.44 cm
    computeHisto ("rame", "torio_rame_044cm", "", 8192, 0, 8192, true, false);
    computeHisto ("rame", "torio_rame_044cm", "", 8192, 0, 8192, true, true);


    // PICCO 1 TORIO RAME 0.44 cm
    //computeHisto ("rame", "torio_rame_044cm", "1", 8192, 510, 570, false, false);
    //computeHisto ("rame", "torio_rame_044cm", "1", 8192, 510, 570, false, true);


    // PICCO 2 TORIO RAME 0.44 cm
    //computeHisto ("rame", "torio_rame_044cm", "2", 8192, 1415, 1450, false, false);
    //computeHisto ("rame", "torio_rame_044cm", "2", 8192, 1415, 1450, false, true);


    // PICCO 3 TORIO RAME 0.44 cm
    //computeHisto ("rame", "torio_rame_044cm", "3", 8192, 6640, 6720, false, false);
    //computeHisto ("rame", "torio_rame_044cm", "3", 8192, 6640, 6720, false, true);




    // TORIO RAME 0.54 cm
    computeHisto ("rame", "torio_rame_054cm", "", 8192, 0, 8192, true, false);
    computeHisto ("rame", "torio_rame_054cm", "", 8192, 0, 8192, true, true);


    // PICCO 1 TORIO RAME 0.54 cm
    //computeHisto ("rame", "torio_rame_054cm", "1", 8192, 510, 570, false, false);
    //computeHisto ("rame", "torio_rame_054cm", "1", 8192, 510, 570, false, true);


    // PICCO 2 TORIO RAME 0.54 cm
    //computeHisto ("rame", "torio_rame_054cm", "2", 8192, 1415, 1450, false, false);
    //computeHisto ("rame", "torio_rame_054cm", "2", 8192, 1415, 1450, false, true);


    // PICCO 3 TORIO RAME 0.54 cm
    //computeHisto ("rame", "torio_rame_054cm", "3", 8192, 6640, 6720, false, false);
    //computeHisto ("rame", "torio_rame_054cm", "3", 8192, 6640, 6720, false, true);
}
