#include <iostream>
#include <fstream>
#include <ostream>
#include <TCanvas.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TMath.h>
#include <algorithm>
#include <TGraph.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <algorithm>

int katy[30] = {61, 55, 49, 43, 37, 37, 43, 49, 55, 61, 61, 55, 49, 43, 37, 37, 43, 49, 55, 61, 61, 55, 49, 43, 37, 37, 43, 49, 55, 61};

char nazwa[100];
char nazwa_cut[100];
char nazwa_cutt[100];
char nazwa_px[100];
char nazwa_py[100];

TH2D *histogramy[30];
TCutG *Cuty[30];
TH1D *projX[30];
TH1D *projY[30];
TF1 *funX[30];
TF1 *funY[30];

TFile *Cuts = new TFile("Cuts_Coinc_All.root");
TFile *Output = new TFile("output_Coinc_All.root");




double getmean(vector<double> vec) 
{
	if(vec.empty())
			return -1;
	else
	{
		double ret = 0;
		for(int i=0; i<vec.size(); i++)
			ret+=vec.at(i);
	
		return ret/vec.size();
	}
}




double standard_deviation(vector<double> vec)
{
	if(vec.empty())
	{
		return -1;
	}
	
	else{
		double mean = getmean(vec);
		vector<double> tmp;
		for(int i=0;i<vec.size();i++)
		{
			tmp.push_back(TMath::Power(vec.at(i), 2));
		}
		double mean_square = getmean(tmp);
		if(vec.size()>1)
			return TMath::Sqrt(vec.size()/(vec.size()-1)*(mean_square-TMath::Power(mean, 2)));
		else
			return TMath::Sqrt(vec.at(0));
	}
}



double kat_lab_prot(double th_cm, double m1, double m2)
{
	double ret;
	ret =  TMath::ATan(TMath::Sin(th_cm)/(TMath::Cos(th_cm)+m1/m2));
	
	if(ret<0)
	{
		return ret+TMath::Pi();
	}
	else
		return ret;
}



std::ifstream& GotoLine(std::ifstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}


int gdzie(vector<double> vec, double th)
{
	int ret;
	for(int i=0;i<vec.size();i++)
	{
		if(vec.at(i)==th)
			ret = i;
	}
	return ret;
}


double min_L(vector<double>x, vector<double> wartosci, vector<double> niepewnosci, TGraph *teoria)
{
	vector<double> Ls;
	vector<double> Chi2;
	double L_p = 0.00001;
	double L_k = 0.001;
	
	for(double i=L_p; i<L_k; i+=(L_k-L_p)/1000)
	{
		double tmp=0;
		for(int j=0;j<wartosci.size();j++)
		{
			tmp+=TMath::Power(((teoria->Eval(x[j])-wartosci[j]*i)/niepewnosci[j]), 2);
		}
		Chi2.push_back(tmp);
		cout<<i<<"	"<<tmp<<endl;
		Ls.push_back(i);
	}
	cout<<"gdzie: "<<gdzie(Chi2, *min_element(Chi2.begin(), Chi2.end()))<<endl;
	return Ls.at(gdzie(Chi2, *min_element(Chi2.begin(), Chi2.end())));
}







int rozklad_tr(void)
{
	TCanvas *c1 = new TCanvas(nazwa, nazwa, 800, 800);
	c1->Divide(1, 3);
	TGraphErrors *g1 = new TGraphErrors();
	TGraphErrors *g2 = new TGraphErrors();
	TGraphErrors *g3 = new TGraphErrors();
	
	TFile *File = new TFile("rozklad_duza_statystyka.root", "RECREATE");
	
	gStyle->SetTitleFontSize(0.07);
	
	ifstream inFile;
	inFile.open("pd_200_kin2.dat");
	
	if (!inFile) {
    cerr << "Unable to open file pd_200_kin2.dat"<<endl;
    exit(1);   // call system to stop
	}
	
	
	
	fstream fileee;
	fileee.open("200cdb+tm.dat");
	
	if (!fileee) {
	cerr << "Unable to open file 200cdb+tm.dat"<<endl;
	exit(1);   // call system to stop
	}
	double kat1, pc1;
	vector<double> katy1;
	vector<double> przekroje1;
	vector<double> przekroje_tr1;
	vector<double> lab1;
	
	for(int i = 0; i < 73; i++)
	{
		fileee>>kat1>>pc1;
		//cout<<kat<<"	"<<pc<<endl;
		katy1.push_back(kat1);
		przekroje1.push_back(pc1);
	}
	
	TGraph *g2eeee = new TGraph();
	
	for(int i=0; i<73; i++)
	{
		g2eeee->SetPoint(i, katy1.at(i), przekroje1.at(i));
	}
		
		
	vector<double> xy, wartosci, niepewnosci;
	
	
	
	
	GotoLine(inFile, 30);
	
	double kat_cm_prot, kat_lab_prot, n1, n2, n3, kat_lab_deut, kat_cm_deut;
	vector<double> kat_cm_vec_prot;
	vector<double> kat_lab_vec_prot;
	vector<double> kat_lab_vec_deut;
	vector<double> kat_cm_vec_deut;
	string line;
	
	for(int k=0; k<=180;k++)
	{
		inFile>>kat_lab_prot>>kat_cm_prot>>n1>>n2>>n3>>kat_lab_deut>>kat_cm_deut;
		kat_lab_vec_prot.push_back(kat_lab_prot);
		kat_cm_vec_prot.push_back(kat_cm_prot);
		kat_lab_vec_deut.push_back(kat_lab_deut);
		kat_cm_vec_deut.push_back(kat_cm_deut);
		getline(inFile, line);
	}
	
	/*for(int k=0; k<=180;k++)
	{
		cout<<kat_lab_vec_prot.at(k)<<"	"<<kat_cm_vec_prot.at(k)<<"		"<<kat_lab_vec_deut.at(k)<<"	"<<kat_cm_vec_deut.at(k)<<endl;
		
	}*/
	
	TGraph *lab_na_cm_prot = new TGraph();
	
	for(int i=0; i<kat_lab_vec_prot.size(); i++)
	{
		lab_na_cm_prot->SetPoint(i, kat_lab_vec_prot.at(i), kat_cm_vec_prot.at(i));
	}
	
	TGraph *lab_na_cm_deut = new TGraph();
	
	for(int i=0; i<kat_lab_vec_deut.size(); i++)
	{
		lab_na_cm_deut->SetPoint(i, kat_lab_vec_deut.at(i), 180-kat_cm_vec_deut.at(i));
	}
	
	//cout<<lab_na_cm_deut->Eval(katy[0], nullptr,"S")<<endl;
	
	TGraph *cm_na_lab_prot = new TGraph();
	
	for(int i=0; i<kat_lab_vec_deut.size(); i++)
	{
		cm_na_lab_prot->SetPoint(i, 180-kat_cm_vec_prot.at(i), kat_lab_vec_prot.at(i));
	}
	
	TGraph *cm_na_lab_deut = new TGraph();
	
	for(int i=0; i<kat_lab_vec_deut.size(); i++)
	{
		cm_na_lab_deut->SetPoint(i, kat_cm_vec_deut.at(i), kat_lab_vec_deut.at(i));
	}
	
	
	c1->cd(1);
	int counter = 0;
	for(int i=0;i<=29;i++)
	{
		sprintf(nazwa, "hkrPd0Pd1Amp_%d", i);
		sprintf(nazwa_cut, "hkrPd0Pd1Amp_%d_cut", i);
		sprintf(nazwa_cutt, "[hkrPd0Pd1Amp_%d_cut]", i);
		
		if(Cuts->GetListOfKeys()->Contains(nazwa_cut))
		{
			TH2D * hkrPd0Pd1Amp = new TH2D();	
			hkrPd0Pd1Amp = (TH2D*)Output->Get(nazwa);
			hkrPd0Pd1Amp->SetStats(000);
			
			histogramy[i] = hkrPd0Pd1Amp;
	
			TCutG *hkrPd0Pd1Amp_cut = new TCutG();
			hkrPd0Pd1Amp_cut = (TCutG*)Cuts->Get(nazwa_cut);
			
			Cuty[i] = hkrPd0Pd1Amp_cut;
			
			sprintf(nazwa_py, "hkrPd0Pd1Amp_%d-py", i);
	
			TH1D *projectionY_cut = hkrPd0Pd1Amp->ProjectionY("",0,-1,nazwa_cutt);
			projectionY_cut->SetTitle(nazwa_py);
			TF1 *fit_gaussY = new TF1("fit_gaussY", "gaus");
			projectionY_cut->Fit("fit_gaussY", "LQN");
			
			funY[i] = fit_gaussY;
			projY[i] = (TH1D*)projectionY_cut->Clone();
			
			sprintf(nazwa_px, "hkrPd0Pd1Amp_%d-px", i);
	
			TH1D *projectionX_cut = hkrPd0Pd1Amp->ProjectionX("",0,-1, nazwa_cutt);
			projectionX_cut->SetTitle(nazwa_px);

			TF1 *fit_gaussX = new TF1("fit_gaussx", "gaus");
			projectionX_cut->Fit("fit_gaussx", "LQN");
			
			funX[i] = fit_gaussX;
			projX[i] = (TH1D*)projectionX_cut->Clone();
			
			g1->SetPoint(counter, katy[i], projectionX_cut->Integral(0, -1));
			g1->SetPointError(counter, 0, TMath::Sqrt(projectionX_cut->Integral(0, -1)));
			
			g2->SetPoint(counter, katy[i], fit_gaussX->Integral((int)(fit_gaussX->GetParameter(1)-3*fit_gaussX->GetParameter(2)), (int)(fit_gaussX->GetParameter(1)+3*fit_gaussX->GetParameter(2)))/projectionX_cut->GetBinWidth(1));
			g2->SetPointError(counter, 0, fit_gaussX->GetParameter(2));
			
			g3->SetPoint(counter, katy[i], fit_gaussY->Integral((int)(fit_gaussY->GetParameter(1)-3*fit_gaussY->GetParameter(2)), (int)(fit_gaussY->GetParameter(1)+3*fit_gaussY->GetParameter(2)))/projectionY_cut->GetBinWidth(1));
			g3->SetPointError(counter, 0, fit_gaussY->GetParameter(2));
			
			counter++;
		}	
	}
	
	c1->cd(1);
	g1->SetTitle("Integral hist;angle lab [#circ];Integral");
	g1->SetMarkerSize(0.55);
	g1->SetMarkerStyle(20);
	g1->GetXaxis()->SetTitleSize(0.05);
	g1->GetXaxis()->SetTitleOffset(0.8);
	g1->GetXaxis()->CenterTitle(true);
	g1->GetYaxis()->SetTitleSize(0.05);
	g1->GetYaxis()->SetTitleOffset(0.6);
	g1->GetYaxis()->CenterTitle(true);
	g1->Draw("APE");	
	
	c1->cd(2);
	g2->SetTitle("pd1 fit;angle lab [#circ];Integral");
	g2->SetMarkerSize(0.55);
	g2->SetMarkerStyle(20);
	g2->GetXaxis()->SetTitleSize(0.05);
	g2->GetXaxis()->SetTitleOffset(0.8);
	g2->GetXaxis()->CenterTitle(true);
	g2->GetYaxis()->SetTitleSize(0.05);
	g2->GetYaxis()->SetTitleOffset(0.6);
	g2->GetYaxis()->CenterTitle(true);
	g2->Draw("APE");
	
	c1->cd(3);
	g3->SetTitle("pd0 fit;angle lab [#circ];Integral");
	g3->SetMarkerSize(0.55);
	g3->SetMarkerStyle(20);
	g3->GetXaxis()->SetTitleSize(0.05);
	g3->GetXaxis()->SetTitleOffset(0.8);
	g3->GetXaxis()->CenterTitle(true);
	g3->GetYaxis()->SetTitleSize(0.05);
	g3->GetYaxis()->SetTitleOffset(0.6);
	g3->GetYaxis()->CenterTitle(true);
	g3->Draw("APE");
	
	c1->SaveAs("Wartosci.root");
	
	
	TCanvas *c2 = new TCanvas("c2", "c2", 800, 800);
	c2->Divide(1, 3);
	
	TGraphErrors *gauss = new TGraphErrors();
	TGraphErrors *gausspx = new TGraphErrors();
	TGraphErrors *gausspy = new TGraphErrors();
	
	TGraph *pomocniczy = new TGraph();
	TGraph *pomocniczypx = new TGraph();
	TGraph *pomocniczypy = new TGraph();
	
	vector<double> vec_hist;
	vector<double> vec_px;
	vector<double> vec_py;
	
	counter = 0;
	
	/*for(int h=0; h<=29; h++)
	{
		sprintf(nazwa_cut, "hkrPd0Pd1Amp_%d_cut", h);
		if(Cuts->GetListOfKeys()->Contains(nazwa_cut))
		{
			cout<<h<<"    "<<projY[h]->GetTitle()<<endl;
		}
	}*/
	
	for(int i=0;i<=5;i++)
	{
		//cout<<"kat_lab "<<katy[i]<<endl;
		//cout<<"kat_cm "<<lab_na_cm_deut->Eval(katy[i], nullptr, "S")<<endl;
		for(int j=0;j<=29;j++)
		{
			sprintf(nazwa_cut, "hkrPd0Pd1Amp_%d_cut", j);
			sprintf(nazwa_cutt, "[hkrPd0Pd1Amp_%d_cut]", j);
			//cout<<"j = "<<j<<endl;
			if(katy[j]==katy[i]&&Cuts->GetListOfKeys()->Contains(nazwa_cut))
			{
				if(katy[i]==43)
				{
					continue;
					
				}
					
				//else
				//{
					//cout<<"else"<<endl;
					//cout<<j<<endl;
					vec_hist.push_back(projX[j]->Integral(0, -1));
					vec_px.push_back(funX[j]->Integral((int)(funX[j]->GetParameter(1)-3*funX[j]->GetParameter(2)), (int)(funX[j]->GetParameter(1)+3*funX[j]->GetParameter(2)))/projX[j]->GetBinWidth(1));
					vec_py.push_back(funY[j]->Integral((int)(funY[j]->GetParameter(1)-3*funY[j]->GetParameter(2)), (int)(funY[j]->GetParameter(1)+3*funY[j]->GetParameter(2)))/projX[j]->GetBinWidth(1));
					
				//}
			}
		}
		
		
		if(getmean(vec_hist)!=-1)
		{
			xy.push_back(lab_na_cm_deut->Eval(katy[i], nullptr,"S"));
			wartosci.push_back(getmean(vec_hist)/(4*TMath::Cos(TMath::Pi()/180*lab_na_cm_deut->Eval(katy[i], nullptr,"S")/2)));
			niepewnosci.push_back(standard_deviation(vec_hist)/(4*TMath::Cos(TMath::Pi()/180*lab_na_cm_deut->Eval(katy[i], nullptr,"S")/2)));
		}
		
		
		vec_hist.clear();
		vec_px.clear();
		vec_py.clear();
	}
	
	double L = min_L(xy, wartosci, niepewnosci, g2eeee);
	cout<<"L  "<<L<<endl;
	
	//L=0.00025;
	
	
	
	for(int i=0;i<=5;i++)
	{
		for(int j=0;j<=29;j++)
		{
			sprintf(nazwa_cut, "hkrPd0Pd1Amp_%d_cut", j);
			sprintf(nazwa_cutt, "[hkrPd0Pd1Amp_%d_cut]", j);
			//cout<<"j = "<<j<<endl;
			if(katy[j]==katy[i]&&Cuts->GetListOfKeys()->Contains(nazwa_cut))
			{
				if(katy[i]==43)
				{
					continue;
					
				}
					
				//else
				//{
					//cout<<"else"<<endl;
					//cout<<j<<endl;
					vec_hist.push_back(projX[j]->Integral(0, -1));
					vec_px.push_back(funX[j]->Integral((int)(funX[j]->GetParameter(1)-3*funX[j]->GetParameter(2)), (int)(funX[j]->GetParameter(1)+3*funX[j]->GetParameter(2)))/projX[j]->GetBinWidth(1));
					vec_py.push_back(funY[j]->Integral((int)(funY[j]->GetParameter(1)-3*funY[j]->GetParameter(2)), (int)(funY[j]->GetParameter(1)+3*funY[j]->GetParameter(2)))/projX[j]->GetBinWidth(1));
					
				//}
			}
		}
		
		
		//cout<<counter<<endl;
		if(getmean(vec_py)!=-1)	
		{
			gauss->SetPoint(counter, lab_na_cm_deut->Eval(katy[i], nullptr,"S"),getmean(vec_hist)/(4*TMath::Cos(TMath::Pi()/180*lab_na_cm_deut->Eval(katy[i], nullptr,"S")/2))*L);
			gauss->SetPointError(counter, 0, standard_deviation(vec_hist)/(4*TMath::Cos(TMath::Pi()/180*lab_na_cm_deut->Eval(katy[i], nullptr,"S")/2))*L);
		}
		
		//cout<<lab_na_cm_deut->Eval(katy[i], nullptr,"S")<<endl;
		
		if(getmean(vec_px)!=-1)	
		{			
			gausspx->SetPoint(counter, lab_na_cm_deut->Eval(katy[i], nullptr,"S"), getmean(vec_px)/(4*TMath::Cos(TMath::Pi()/180*lab_na_cm_deut->Eval(katy[i], nullptr,"S")/2))*L);
			gausspx->SetPointError(counter, 0, standard_deviation(vec_px)/(4*TMath::Cos(TMath::Pi()/180*lab_na_cm_deut->Eval(katy[i], nullptr,"S")/2))*L);
		}
		
		if(getmean(vec_py)!=-1)	
		{
			gausspy->SetPoint(counter, lab_na_cm_deut->Eval(katy[i], nullptr,"S"),getmean(vec_py)/(4*TMath::Cos(TMath::Pi()/180*lab_na_cm_deut->Eval(katy[i], nullptr,"S")/2))*L);
			gausspy->SetPointError(counter, 0, standard_deviation(vec_py)/(4*TMath::Cos(TMath::Pi()/180*lab_na_cm_deut->Eval(katy[i], nullptr,"S")/2))*L);
			counter++;
		}
		
		//cout<<getmean(vec_hist)<<endl;
		//cout<<getmean(vec_py)<<endl;
		
		
		vec_hist.clear();
		vec_px.clear();
		vec_py.clear();
	}
	
	
	
	
	
	
	c2->cd(1);
	gauss->SetTitle("Integral hist;angle cm [#circ];Integral");
	gauss->SetMarkerSize(0.55);
	gauss->SetMarkerStyle(20);
	gauss->GetXaxis()->SetTitleSize(0.05);
	gauss->GetXaxis()->SetTitleOffset(0.8);
	gauss->GetXaxis()->CenterTitle(true);
	gauss->GetYaxis()->SetTitleSize(0.05);
	gauss->GetYaxis()->SetTitleOffset(0.65);
	gauss->GetYaxis()->CenterTitle(true);
	gauss->Draw("APE");	
		
	
	c2->cd(2);
	gausspx->SetTitle("pd1 fit;angle cm [#circ];Integral");
	gausspx->SetMarkerSize(0.55);
	gausspx->SetMarkerStyle(20);
	gausspx->GetXaxis()->SetTitleSize(0.05);
	gausspx->GetXaxis()->SetTitleOffset(0.8);
	gausspx->GetXaxis()->CenterTitle(true);
	gausspx->GetYaxis()->SetTitleSize(0.05);
	gausspx->GetYaxis()->SetTitleOffset(0.65);
	gausspx->GetYaxis()->CenterTitle(true);
	gausspx->Draw("APE");
	
	c2->cd(3);
	gausspy->SetTitle("pd0 fit;angle cm [#circ];Integral");
	gausspy->SetMarkerSize(0.55);
	gausspy->SetMarkerStyle(20);
	gausspy->GetXaxis()->SetTitleSize(0.05);
	gausspy->GetXaxis()->SetTitleOffset(0.8);
	gausspy->GetXaxis()->CenterTitle(true);
	gausspy->GetYaxis()->SetTitleSize(0.05);
	gausspy->GetYaxis()->SetTitleOffset(0.65);
	gausspy->GetYaxis()->CenterTitle(true);
	gausspy->Draw("APE");
	
	File->cd();
	c1->Write("Wszystkie.png");
	c2->Write("Gauss.png");
	
	
	
	
	
	g2eeee->SetLineColor(2);
	c2->cd(1);
	g2eeee->Draw("same");
	c2->cd(2);
	g2eeee->Draw("same");
	c2->cd(3);
	g2eeee->Draw("same");
	
	c2->SaveAs("Dopasowane_duza_statystyka.root");
	
	return 0;
}