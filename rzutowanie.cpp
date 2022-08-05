#include <iostream>
#include <fstream>
#include <ostream>
#include <TCanvas.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TMath.h>
#include <algorithm>
#include <TGraph.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>



void Fill(TCutG *cut, TH2D *h2d, TH1D *h1d)
{
	int x, y;
	int suma = 0;
	
	int xmax = h2d->GetXaxis()->GetNbins()+1;
	int ymax = h2d->GetYaxis()->GetNbins()+1;
	
	for(x = 1; x<xmax; x++)
	{
		for(y=1; y<ymax; y++)
		{
			if(cut->IsInside(h2d->GetXaxis()->GetBinCenter(x), h2d->GetYaxis()->GetBinCenter(y)))
			{
				suma+=h2d->GetBinContent(x, y);
			}
		}
	}
}

TH2D *h2;
TH1D * projh2X;
TH1D * projh2Y;
TPad *right_pad, *top_pad, *text_pad;

int rzutowanie(void)
{
	gStyle->SetOptStat(0);
	TLatex latex;
	latex.SetNDC();
	latex.SetTextSize(0.015);
	
	
	TFile *Cuts = new TFile("Cuts_Coinc_All.root");
	TFile *Output = new TFile("output_Coinc_All.root");
	TFile *Projections = new TFile("Rzuty_output_Coinc_All.root", "RECREATE");
		
	char nazwa[100];
	char nazwa_cut[100];
	char nazwa_cutt[100];
	char nazwa_px[100];
	char nazwa_py[100];
	
	
	
	for(int  i =0; i<=29; i++)
	{
		sprintf(nazwa, "hkrPd0Pd1Amp_%d", i);
		sprintf(nazwa_cut, "hkrPd0Pd1Amp_%d_cut", i);
		sprintf(nazwa_cutt, "[hkrPd0Pd1Amp_%d_cut]", i);
		sprintf(nazwa_px, "hkrPd0Pd1Amp_%d-px", i);
		sprintf(nazwa_py, "hkrPd0Pd1Amp_%d-py", i);
		
		
		if(Cuts->GetListOfKeys()->Contains(nazwa_cut) )
		{
			cout<<nazwa<<endl;
			
			TCanvas *c1 = new TCanvas(nazwa, nazwa, 800, 800);
			gPad->SetLogz();
			
			TPad *center_pad = new TPad("center_pad", "center_pad",0.0,0.0,0.6,0.6);
			center_pad->Draw();

			right_pad = new TPad("right_pad", "right_pad",0.55,0.0,1.0,0.6);
			right_pad->Draw();
			
			text_pad = new TPad("top_pad", "top_pad",0.0,0.55,0.6,0.6);
			text_pad->Draw();
			
			top_pad = new TPad("top_pad", "top_pad",0.0,0.55,0.6,1.0);
			top_pad->Draw();
	
			h2 = new TH2D();	
			h2 = (TH2D*)Output->Get(nazwa);
			h2->GetXaxis()->SetTitle("");
			h2->GetYaxis()->SetTitle("");
			h2->SetStats(000);
	
			TCutG *cut = new TCutG();
			cut = (TCutG*)Cuts->Get(nazwa_cut);
			
			right_pad->cd();
	
			projh2Y = h2->ProjectionY("",0,-1,nazwa_cutt);
			projh2Y->SetTitle(nazwa_py);
			projh2Y->SetFillColor(kBlue-2);
			projh2Y->GetXaxis()->SetTitle("");
			projh2Y->GetYaxis()->SetTitle("");
			TF1 *fit_gaussY = new TF1("fit_gaussY", "gaus");
			projh2Y->Fit("fit_gaussY", "L");
			projh2Y->DrawCopy("hbar");
	
	
	
			TGraph *g1 = new TGraph();
			for(int i = 0; i<projh2Y->GetNbinsX()*projh2Y->GetBinWidth(1); i++)
			{
				g1->SetPoint(i, fit_gaussY->Eval(i), i);
			}
			g1->SetLineColor(2);
			g1->SetLineWidth(2);
	
			g1->Draw("sameL");
	
	
	
	
			center_pad->cd();
	
			h2->Draw("colz");
			cut->Draw("same");
	
	
			top_pad->cd();
			
			
	
			projh2X = h2->ProjectionX("",0,-1, nazwa_cutt);
			projh2X->SetTitle(nazwa_px);
			projh2X->GetXaxis()->SetTitle("");
			projh2X->GetYaxis()->SetTitle("");
			projh2X->SetFillColor(kBlue+1);

			TF1 *fit_gaussX = new TF1("fit_gaussx", "gaus");
			projh2X->Fit("fit_gaussx", "L");
			projh2X->DrawCopy("bar");
	
	
	
	
			c1->cd();
	
			latex.DrawLatex(.6,.95,"pd1: ");
	
			std::stringstream stream;
			stream << std::fixed << std::setprecision(2) << fit_gaussX->GetParameter(0);
			std::string s = stream.str();
			const char *c = s.c_str();
	
			latex.DrawLatex(.6,.93,"Constant: ");
			latex.DrawLatex(.67, .93, c);
			s="";
			c="";
			stream.str("");
	
			stream << std::fixed << std::setprecision(2) << fit_gaussX->GetParameter(1);
			s = stream.str();
			c = s.c_str();
		
			latex.DrawLatex(.6,.9,"Mean: ");
			latex.DrawLatex(.65, .9, c);
			s="";
			c="";
			stream.str("");
	
			stream << std::fixed << std::setprecision(2) << fit_gaussX->GetParameter(2);
			s = stream.str();
			c = s.c_str();
	
			latex.DrawLatex(.6,.87,"Sigma: ");
			latex.DrawLatex(.66, .87, c);
			s="";
			c="";
			stream.str("");
	
		
			stream << std::fixed << std::setprecision(2) << fit_gaussX->Integral((int)(fit_gaussX->GetParameter(1)-3*fit_gaussX->GetParameter(2)), (int)(fit_gaussX->GetParameter(1)+3*fit_gaussX->GetParameter(2)))/projh2X->GetBinWidth(1);	
			s = stream.str();
			c = s.c_str();
			cout<<"Integral px: "<<s<<endl;
			latex.DrawLatex(.6,.84,"Integral: ");
			latex.DrawLatex(.67, .84, c);
			s="";
			c="";
			stream.str("");
	
	
			stream << std::fixed << std::setprecision(2) << projh2X->Integral(0, -1);
			s = stream.str();
			c = s.c_str();
			latex.DrawLatex(.6,.81,"Integral hist: ");
			latex.DrawLatex(.7, .81, c);
			s="";
			c="";
			stream.str("");
		
	
	
			latex.DrawLatex(.6,.78,"pd0: ");
	
			stream << std::fixed << std::setprecision(2) << fit_gaussY->GetParameter(0);
			s = stream.str();
			c = s.c_str();
	
			latex.DrawLatex(.6,.75,"Constant: ");
			latex.DrawLatex(.67, .75, c);
			s="";
			c="";
			stream.str("");
	
			stream << std::fixed << std::setprecision(2) << fit_gaussY->GetParameter(1);
			s = stream.str();
			c = s.c_str();
	
			latex.DrawLatex(.6,.72,"Mean: ");
			latex.DrawLatex(.65, .72, c);
			s="";
			c="";
			stream.str("");
	
			stream << std::fixed << std::setprecision(2) << fit_gaussY->GetParameter(2);
			s = stream.str();
			c = s.c_str();
	
			latex.DrawLatex(.6,.69,"Sigma: ");
			latex.DrawLatex(.66, .69, c);
			s="";
			c="";
			stream.str("");
	
	
			stream << std::fixed << std::setprecision(2) << fit_gaussY->Integral((fit_gaussY->GetParameter(1)-3*fit_gaussY->GetParameter(2)), (fit_gaussY->GetParameter(1)+3*fit_gaussY->GetParameter(2)))/projh2Y->GetBinWidth(1);
			s = stream.str();
			c = s.c_str();
			cout<<"Integral py: "<<s<<endl;
			latex.DrawLatex(.6,.66,"Integral: ");
			latex.DrawLatex(.67, .66, c);
			s="";
			c="";
			stream.str("");
	
			stream << std::fixed << std::setprecision(2) << projh2Y->Integral(0, -1);
			s = stream.str();
			c = s.c_str();
			cout<<"Integral hist: "<<s<<endl;
			latex.DrawLatex(.6,.63,"Integral hist: ");
			latex.DrawLatex(.7, .63, c);
			s="";
			c="";
			stream.str("");
			
			auto ex = new TExec("zoom","ZoomExec()");
			h2->GetListOfFunctions()->Add(ex);
			
			Projections->cd();
			c1->Write();
		}
	
	}
	
	return 0;
}




void ZoomExec()
{
	int xfirst = h2->GetXaxis()->GetFirst();
	int xlast = h2->GetXaxis()->GetLast();
	double xmin = h2->GetXaxis()->GetBinLowEdge(xfirst);
	double xmax = h2->GetXaxis()->GetBinUpEdge(xlast);
	projh2X->GetXaxis()->SetRangeUser(xmin, xmax);
	top_pad->Modified();

	int yfirst = h2->GetYaxis()->GetFirst();
	int ylast = h2->GetYaxis()->GetLast();
	double ymin = h2->GetYaxis()->GetBinLowEdge(yfirst);
	double ymax = h2->GetYaxis()->GetBinUpEdge(ylast);
	projh2Y->GetXaxis()->SetRangeUser(ymin, ymax);
	right_pad->Modified();
}