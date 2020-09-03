#include <iostream>
#include <fstream>
#include <string>

#define N_DATA 61 // data gathered during charging/discharging
#define N_EXPERIMENTS 50 // numbers of time the experiment was repeted

struct CapacitorData // structure containing data to be plotted
{
    Double_t avg_voltages[N_DATA]; // Y axis
    Double_t avg_times[N_DATA]; // X axis
    int experiment_counter = 0;

};

void readChargingData(std::ifstream &f,CapacitorData &c){
    Double_t time, voltage;
    std::string line;
    for(int i=0;i<N_DATA; i++){
        std::getline(f, line);
        std::istringstream iss(line);
        iss >> time >> voltage;
        
        c.avg_times[i] = ((c.avg_times[i]*c.experiment_counter) + time/1000)/(c.experiment_counter+1);
        c.avg_voltages[i] = ((c.avg_voltages[i]*c.experiment_counter)+ voltage)/(c.experiment_counter+1);
        
    }
    c.experiment_counter++;
}
void readDischargingData(std::ifstream &f,CapacitorData &d){
    Double_t time, voltage;
    std::string line;
    for(int i=0;i<N_DATA;i++){
        std::getline(f, line);
        std::istringstream iss(line);
        iss >> time >> voltage;
        
        d.avg_times[i] = ((d.avg_times[i]*d.experiment_counter) + time/1000)/(d.experiment_counter+1);
        d.avg_voltages[i] = ((d.avg_voltages[i]*d.experiment_counter)+ voltage)/(d.experiment_counter+1);
        
    }
    d.experiment_counter++;

}

void readFile(string fileName, CapacitorData &c, CapacitorData &d){    
    std::ifstream dataFile;
    string line;
    dataFile.open(fileName);
    if(!dataFile){
        std::cerr<<"Unable to open file: "<< fileName <<std::endl;
        exit(1);
    }
    for(int i=0;i < 2; i++){
        std::getline(dataFile, line); // read "Experiment n. #"
        readChargingData(dataFile, c);
        std::getline(dataFile, line); // read "Discharging..."
        readDischargingData(dataFile, d);
    }
    
}
void analysis() {
    CapacitorData charging;
    CapacitorData discharging;
    readFile("capacitor_data.txt", charging, discharging); // read data and fill charging/discharging structures
    TCanvas *c = new TCanvas("c", "Capacitor data over time", 200, 200, 950,700); // create canvas
    TGraph *graphFromData = new TGraph(N_DATA,charging.avg_times,charging.avg_voltages);
    graphFromData->Draw();  // draw graph of charging
    TF1 *expectedGraph = new TF1("expectedGraph","5*(1-e^(-x/1))",0,6);
    expectedGraph->Draw("same"); //draw expected graph
    TLegend *legend = new TLegend(.1,.7,.3,.9);     //adding legend
    legend->AddEntry(graphFromData,"d.d.p over time","l");
    legend->AddEntry(expectedGraph,"Expected result","l");
    legend->Draw();
}