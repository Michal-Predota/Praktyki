#include <iostream>
#include <fstream>
#include <ostream>
#include <TCanvas.h>
#include <TH2D.h>
#include <TMath.h>
#include <algorithm>
#include <TGraph.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>


int Integral(TCutG *cut, TH2D *h2d)
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
	return suma;
	
}
int Rysunki(void)
{
	
	/*TChain *Cuts = new TChain("Cuts");
	Chain->Add("Cuts.root");
	
	TChain *Output = new TChain("Output");
	Chain->Add("output_allTrig.root");	*/
	
	TCanvas *c1 = new TCanvas("c1", "canvas1", 1500, 500);
	c1->SetGrid();
	c1->SetBottomMargin(0);
	c1->SetTopMargin(0.15);
	c1->Divide(11, 3);
	
	TFile *Cuts = new TFile("Cuts.root");
	TFile *Output = new TFile("output_allTrig.root");
	
	gStyle->SetTitleH(0.4);
	
	
	
	//Detector 0
	c1->cd(1);
	
	TH2D * hkrPd0Pd1Amp_0 = new TH2D();	
	hkrPd0Pd1Amp_0 = (TH2D*)Output->Get("hkrPd0Pd1Amp_0");
	hkrPd0Pd1Amp_0->SetTitle("61 #circ Detector 0");
	hkrPd0Pd1Amp_0->SetTitleSize(0.5);
	hkrPd0Pd1Amp_0->SetTitleSize(0.25, "t");
	
	
	hkrPd0Pd1Amp_0->SetStats(000);
	
	TCutG *hkrPd0Pd1Amp_0_cut = new TCutG();
	hkrPd0Pd1Amp_0_cut = (TCutG*)Cuts->Get("hkrPd0Pd1Amp_0_cut");
	hkrPd0Pd1Amp_0_cut->SetLineWidth(2);
	hkrPd0Pd1Amp_0_cut->SetLineColor(2);
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_0->Draw("colz");
	//hkrPd0Pd1Amp_0_cut->Draw("same");
	
	//Detector 1
	c1->cd(2);
	TH2D * hkrPd0Pd1Amp_1 = new TH2D();	
	hkrPd0Pd1Amp_1 = (TH2D*)Output->Get("hkrPd0Pd1Amp_1");
	hkrPd0Pd1Amp_1->SetTitle("55^{ o} Detector 1	");
	hkrPd0Pd1Amp_1->SetStats(000);
	hkrPd0Pd1Amp_1->SetTitleSize(0.25);
	
	TCutG *hkrPd0Pd1Amp_1_cut = new TCutG();
	hkrPd0Pd1Amp_1_cut = (TCutG*)Cuts->Get("hkrPd0Pd1Amp_1_cut");
	hkrPd0Pd1Amp_1_cut->SetLineWidth(2);
	hkrPd0Pd1Amp_1_cut->SetLineColor(2);
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_1->Draw("colz");
	//hkrPd0Pd1Amp_1_cut->Draw("same");
	
	//Detector 2
	c1->cd(3);
	
	
	TLatex *   tex = new TLatex(0.25,0.87,"49^{ o} Detector 2");
	tex->SetNDC();
	tex->SetTextSize(0.11);
	tex->Draw();
	
	
	TLatex *   det2 = new TLatex(0.45,0.45,"X");
	det2->SetNDC();
	det2->SetTextSize(0.2);
	det2->Draw();

	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	
	//Detector 3
	c1->cd(4);
	TH2D * hkrPd0Pd1Amp_3 = new TH2D();	
	hkrPd0Pd1Amp_3 = (TH2D*)Output->Get("hkrPd0Pd1Amp_3");
	hkrPd0Pd1Amp_3->SetTitle("43^{ o} Detector 3	");
	hkrPd0Pd1Amp_3->SetStats(000);
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_3->SetTitleSize(0.25);
	
	hkrPd0Pd1Amp_3->Draw("colz");
	
	//Detector 4
	c1->cd(5);
	TH2D * hkrPd0Pd1Amp_4 = new TH2D();	
	hkrPd0Pd1Amp_4 = (TH2D*)Output->Get("hkrPd0Pd1Amp_4");
	hkrPd0Pd1Amp_4->SetTitle("37^{ o} Detector 4	");
	hkrPd0Pd1Amp_4->SetTitleSize(0.25);
	hkrPd0Pd1Amp_4->SetStats(000);
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_4->Draw("colz");
	
	//Target
	c1->cd(6);
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	
	//Detector 5
	c1->cd(7);
	TH2D * hkrPd0Pd1Amp_5 = new TH2D();	
	hkrPd0Pd1Amp_5 = (TH2D*)Output->Get("hkrPd0Pd1Amp_5");
	hkrPd0Pd1Amp_5->SetTitle("37^{ o} Detector 5	");
	hkrPd0Pd1Amp_5->SetTitleSize(0.25);
	hkrPd0Pd1Amp_5->SetStats(000);
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_5->Draw("colz");
	
	//Detector 6
	c1->cd(8);
	TH2D * hkrPd0Pd1Amp_6 = new TH2D();	
	hkrPd0Pd1Amp_6 = (TH2D*)Output->Get("hkrPd0Pd1Amp_6");
	hkrPd0Pd1Amp_6->SetTitle("43^{ o} Detector 6	");
	hkrPd0Pd1Amp_6->SetTitleSize(0.25);
	hkrPd0Pd1Amp_6->SetStats(000);
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_6->Draw("colz");
	
	//Detector 7
	c1->cd(9);
	TH2D * hkrPd0Pd1Amp_7 = new TH2D();	
	hkrPd0Pd1Amp_7 = (TH2D*)Output->Get("hkrPd0Pd1Amp_7");
	hkrPd0Pd1Amp_7->SetTitle("49^{ o} Detector 7	");
	hkrPd0Pd1Amp_7->SetTitleSize(0.25);
	hkrPd0Pd1Amp_7->SetStats(000);
	
	TCutG *hkrPd0Pd1Amp_7_cut = new TCutG();
	hkrPd0Pd1Amp_7_cut = (TCutG*)Cuts->Get("hkrPd0Pd1Amp_7_cut");
	hkrPd0Pd1Amp_7_cut->SetLineWidth(2);
	hkrPd0Pd1Amp_7_cut->SetLineColor(2);
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_7->Draw("colz");
	//hkrPd0Pd1Amp_7_cut->Draw("same");
	
	//Detector 8
	c1->cd(10);
	TH2D * hkrPd0Pd1Amp_8 = new TH2D();	
	hkrPd0Pd1Amp_8 = (TH2D*)Output->Get("hkrPd0Pd1Amp_8");
	hkrPd0Pd1Amp_8->SetTitle("55^{ o} Detector 8	");
	hkrPd0Pd1Amp_8->SetTitleSize(0.25);
	hkrPd0Pd1Amp_8->SetStats(000);
	
	TCutG *hkrPd0Pd1Amp_8_cut = new TCutG();
	hkrPd0Pd1Amp_8_cut = (TCutG*)Cuts->Get("hkrPd0Pd1Amp_8_cut");
	hkrPd0Pd1Amp_8_cut->SetLineWidth(2);
	hkrPd0Pd1Amp_8_cut->SetLineColor(2);
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_8->Draw("colz");
	//hkrPd0Pd1Amp_8_cut->Draw("same");
	
	//Detector 9
	c1->cd(11);
	TH2D * hkrPd0Pd1Amp_9 = new TH2D();	
	hkrPd0Pd1Amp_9 = (TH2D*)Output->Get("hkrPd0Pd1Amp_9");
	hkrPd0Pd1Amp_9->SetTitle("61^{ o} Detector 9	");
	hkrPd0Pd1Amp_9->SetTitleSize(0.25);
	hkrPd0Pd1Amp_9->SetStats(000);
		
	TCutG *hkrPd0Pd1Amp_9_cut = new TCutG();
	hkrPd0Pd1Amp_9_cut = (TCutG*)Cuts->Get("hkrPd0Pd1Amp_9_cut");
	hkrPd0Pd1Amp_9_cut->SetLineWidth(2);
	hkrPd0Pd1Amp_9_cut->SetLineColor(2);
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_9->Draw("colz");
	//hkrPd0Pd1Amp_9_cut->Draw("same");
	
	
	
	gStyle->SetTitleH(0.2);
	
	//Detector 10
	c1->cd(12);
	TH2D * hkrPd0Pd1Amp_10 = new TH2D();	
	hkrPd0Pd1Amp_10 = (TH2D*)Output->Get("hkrPd0Pd1Amp_10");
	hkrPd0Pd1Amp_10->SetTitle("Detector 10");
	hkrPd0Pd1Amp_10->SetStats(000);
		
	TCutG *hkrPd0Pd1Amp_10_cut = new TCutG();
	hkrPd0Pd1Amp_10_cut = (TCutG*)Cuts->Get("hkrPd0Pd1Amp_10_cut");
	hkrPd0Pd1Amp_10_cut->SetLineWidth(2);
	hkrPd0Pd1Amp_10_cut->SetLineColor(2);
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_10->Draw("colz");
	//hkrPd0Pd1Amp_10_cut->Draw("same");
	
	//Detector 11
	c1->cd(13);
	TH2D * hkrPd0Pd1Amp_11 = new TH2D();	
	hkrPd0Pd1Amp_11 = (TH2D*)Output->Get("hkrPd0Pd1Amp_11");
	hkrPd0Pd1Amp_11->SetTitle("Detector 11");
	hkrPd0Pd1Amp_11->SetStats(000);
		
	TCutG *hkrPd0Pd1Amp_11_cut = new TCutG();
	hkrPd0Pd1Amp_11_cut = (TCutG*)Cuts->Get("hkrPd0Pd1Amp_11_cut");
	hkrPd0Pd1Amp_11_cut->SetLineWidth(2);
	hkrPd0Pd1Amp_11_cut->SetLineColor(2);
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_11->Draw("colz");
	//hkrPd0Pd1Amp_11_cut->Draw("same");
	
	//Detector 12
	c1->cd(14);
	TH2D * hkrPd0Pd1Amp_12 = new TH2D();	
	hkrPd0Pd1Amp_12 = (TH2D*)Output->Get("hkrPd0Pd1Amp_12");
	hkrPd0Pd1Amp_12->SetTitle("Detector 12");
	hkrPd0Pd1Amp_12->SetStats(000);
		
	TCutG *hkrPd0Pd1Amp_12_cut = new TCutG();
	hkrPd0Pd1Amp_12_cut = (TCutG*)Cuts->Get("hkrPd0Pd1Amp_12_cut");
	hkrPd0Pd1Amp_12_cut->SetLineWidth(2);
	hkrPd0Pd1Amp_12_cut->SetLineColor(2);
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_12->Draw("colz");
	//hkrPd0Pd1Amp_12_cut->Draw("same");
	
	//Detector 13
	c1->cd(15);
	TH2D * hkrPd0Pd1Amp_13 = new TH2D();	
	hkrPd0Pd1Amp_13 = (TH2D*)Output->Get("hkrPd0Pd1Amp_13");
	hkrPd0Pd1Amp_13->SetTitle("Detector 13");
	hkrPd0Pd1Amp_13->SetStats(000);
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_13->Draw("colz");
	
	//Detector 14
	c1->cd(16);
	TH2D * hkrPd0Pd1Amp_14 = new TH2D();	
	hkrPd0Pd1Amp_14 = (TH2D*)Output->Get("hkrPd0Pd1Amp_14");
	hkrPd0Pd1Amp_14->SetTitle("Detector 14");
	hkrPd0Pd1Amp_14->SetStats(000);
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_14->Draw("colz");
	
	//Target
	c1->cd(17);
	
	TLatex *   Target = new TLatex(0.3,0.4,"Target");
	Target->SetNDC();
	Target->SetTextSize(0.2);
	Target->Draw();
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	
	//Detector 15
	c1->cd(18);
	TH2D * hkrPd0Pd1Amp_15 = new TH2D();	
	hkrPd0Pd1Amp_15 = (TH2D*)Output->Get("hkrPd0Pd1Amp_15");
	hkrPd0Pd1Amp_15->SetTitle("Detector 15");
	hkrPd0Pd1Amp_15->SetStats(000);
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_15->Draw("colz");
	
	//Detector 16
	c1->cd(19);
	TH2D * hkrPd0Pd1Amp_16 = new TH2D();	
	hkrPd0Pd1Amp_16 = (TH2D*)Output->Get("hkrPd0Pd1Amp_16");
	hkrPd0Pd1Amp_16->SetTitle("Detector 16");
	hkrPd0Pd1Amp_16->SetStats(000);
		
	TCutG *hkrPd0Pd1Amp_16_cut = new TCutG();
	hkrPd0Pd1Amp_16_cut = (TCutG*)Cuts->Get("hkrPd0Pd1Amp_16_cut");
	hkrPd0Pd1Amp_16_cut->SetLineWidth(2);
	hkrPd0Pd1Amp_16_cut->SetLineColor(2);
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_16->Draw("colz");
	//hkrPd0Pd1Amp_16_cut->Draw("same");
	
	//Detector 17
	c1->cd(20);
	TH2D * hkrPd0Pd1Amp_17 = new TH2D();	
	hkrPd0Pd1Amp_17 = (TH2D*)Output->Get("hkrPd0Pd1Amp_17");
	hkrPd0Pd1Amp_17->SetTitle("Detector 17");
	hkrPd0Pd1Amp_17->SetStats(000);
		
	TCutG *hkrPd0Pd1Amp_17_cut = new TCutG();
	hkrPd0Pd1Amp_17_cut = (TCutG*)Cuts->Get("hkrPd0Pd1Amp_17_cut");
	hkrPd0Pd1Amp_17_cut->SetLineWidth(2);
	hkrPd0Pd1Amp_17_cut->SetLineColor(2);
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_17->Draw("colz");
	//hkrPd0Pd1Amp_17_cut->Draw("same");
	
	//Detector 18
	c1->cd(21);
	TH2D * hkrPd0Pd1Amp_18 = new TH2D();	
	hkrPd0Pd1Amp_18 = (TH2D*)Output->Get("hkrPd0Pd1Amp_18");
	hkrPd0Pd1Amp_18->SetTitle("Detector 18");
	hkrPd0Pd1Amp_18->SetStats(000);
		
	TCutG *hkrPd0Pd1Amp_18_cut = new TCutG();
	hkrPd0Pd1Amp_18_cut = (TCutG*)Cuts->Get("hkrPd0Pd1Amp_18_cut");
	hkrPd0Pd1Amp_18_cut->SetLineWidth(2);
	hkrPd0Pd1Amp_18_cut->SetLineColor(2);
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_18->Draw("colz");
	//hkrPd0Pd1Amp_18_cut->Draw("same");
	
	//Detector 19
	c1->cd(22);
	
	TLatex *   tex1 = new TLatex(0.25,0.87,"Detector 19");
	tex1->SetNDC();
	tex1->SetTextSize(0.11);
	tex1->Draw();
	
	TLatex *   det19 = new TLatex(0.45,0.45,"X");
	det19->SetNDC();
	det19->SetTextSize(0.2);
	det19->Draw();
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	
	//Detector 20
	c1->cd(23);
	TH2D * hkrPd0Pd1Amp_20 = new TH2D();	
	hkrPd0Pd1Amp_20 = (TH2D*)Output->Get("hkrPd0Pd1Amp_20");
	hkrPd0Pd1Amp_20->SetTitle("Detector 20");
	hkrPd0Pd1Amp_20->SetStats(000);
		
	TCutG *hkrPd0Pd1Amp_20_cut = new TCutG();
	hkrPd0Pd1Amp_20_cut = (TCutG*)Cuts->Get("hkrPd0Pd1Amp_20_cut");
	hkrPd0Pd1Amp_20_cut->SetLineWidth(2);
	hkrPd0Pd1Amp_20_cut->SetLineColor(2);
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_20->Draw("colz");
	//hkrPd0Pd1Amp_20_cut->Draw("same");
	
	//Detector 21
	c1->cd(24);
	TH2D * hkrPd0Pd1Amp_21 = new TH2D();	
	hkrPd0Pd1Amp_21 = (TH2D*)Output->Get("hkrPd0Pd1Amp_21");
	hkrPd0Pd1Amp_21->SetTitle("Detector 21");
	hkrPd0Pd1Amp_21->SetStats(000);
		
	TCutG *hkrPd0Pd1Amp_21_cut = new TCutG();
	hkrPd0Pd1Amp_21_cut = (TCutG*)Cuts->Get("hkrPd0Pd1Amp_21_cut");
	hkrPd0Pd1Amp_21_cut->SetLineWidth(2);
	hkrPd0Pd1Amp_21_cut->SetLineColor(2);
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_21->Draw("colz");
	//hkrPd0Pd1Amp_21_cut->Draw("same");
	
	//Detector 22
	c1->cd(25);
	TH2D * hkrPd0Pd1Amp_22 = new TH2D();	
	hkrPd0Pd1Amp_22 = (TH2D*)Output->Get("hkrPd0Pd1Amp_22");
	hkrPd0Pd1Amp_22->SetTitle("Detector 22");
	hkrPd0Pd1Amp_22->SetStats(000);
		
	TCutG *hkrPd0Pd1Amp_22_cut = new TCutG();
	hkrPd0Pd1Amp_22_cut = (TCutG*)Cuts->Get("hkrPd0Pd1Amp_22_cut");
	hkrPd0Pd1Amp_22_cut->SetLineWidth(2);
	hkrPd0Pd1Amp_22_cut->SetLineColor(2);
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_22->Draw("colz");
	//hkrPd0Pd1Amp_22_cut->Draw("same");
	
	//Detector 23
	c1->cd(26);
	TH2D * hkrPd0Pd1Amp_23 = new TH2D();	
	hkrPd0Pd1Amp_23 = (TH2D*)Output->Get("hkrPd0Pd1Amp_23");
	hkrPd0Pd1Amp_23->SetTitle("Detector 23");
	hkrPd0Pd1Amp_23->SetStats(000);
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_23->Draw("colz");
	
	//Detector 24
	c1->cd(27);
	TH2D * hkrPd0Pd1Amp_24 = new TH2D();	
	hkrPd0Pd1Amp_24 = (TH2D*)Output->Get("hkrPd0Pd1Amp_24");
	hkrPd0Pd1Amp_24->SetTitle("Detector 24");
	hkrPd0Pd1Amp_24->SetStats(000);
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_24->Draw("colz");
	
	//Target
	c1->cd(28);
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	
	//Detector 25
	c1->cd(29);
	TH2D * hkrPd0Pd1Amp_25 = new TH2D();	
	hkrPd0Pd1Amp_25 = (TH2D*)Output->Get("hkrPd0Pd1Amp_25");
	hkrPd0Pd1Amp_25->SetTitle("Detector 25");
	hkrPd0Pd1Amp_25->SetStats(000);
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_25->Draw("colz");
	
	//Detector 26
	c1->cd(30);
	
	TLatex *   tex2 = new TLatex(0.25,0.87,"Detector 26");
	tex2->SetNDC();
	tex2->SetTextSize(0.11);
	tex2->Draw();
	
	TLatex *   det26 = new TLatex(0.45,0.45,"X");
	det26->SetNDC();
	det26->SetTextSize(0.2);
	det26->Draw();
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	
	
	//Detector 27
	c1->cd(31);
	TH2D * hkrPd0Pd1Amp_27 = new TH2D();	
	hkrPd0Pd1Amp_27 = (TH2D*)Output->Get("hkrPd0Pd1Amp_27");
	hkrPd0Pd1Amp_27->SetTitle("Detector 27");
	hkrPd0Pd1Amp_27->SetStats(000);
		
	TCutG *hkrPd0Pd1Amp_27_cut = new TCutG();
	hkrPd0Pd1Amp_27_cut = (TCutG*)Cuts->Get("hkrPd0Pd1Amp_27_cut");
	hkrPd0Pd1Amp_27_cut->SetLineWidth(2);
	hkrPd0Pd1Amp_27_cut->SetLineColor(2);
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_27->Draw("colz");
	//hkrPd0Pd1Amp_27_cut->Draw("same");
	
	//Detector 28
	c1->cd(32);
	TH2D * hkrPd0Pd1Amp_28 = new TH2D();	
	hkrPd0Pd1Amp_28 = (TH2D*)Output->Get("hkrPd0Pd1Amp_28");
	hkrPd0Pd1Amp_28->SetTitle("Detector 28");
	hkrPd0Pd1Amp_28->SetStats(000);
		
	TCutG *hkrPd0Pd1Amp_28_cut = new TCutG();
	hkrPd0Pd1Amp_28_cut = (TCutG*)Cuts->Get("hkrPd0Pd1Amp_28_cut");
	hkrPd0Pd1Amp_28_cut->SetLineWidth(2);
	hkrPd0Pd1Amp_28_cut->SetLineColor(2);
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_28->Draw("colz");
	//hkrPd0Pd1Amp_28_cut->Draw("same");
	
	//Detector 29
	c1->cd(33);
	TH2D * hkrPd0Pd1Amp_29 = new TH2D();	
	hkrPd0Pd1Amp_29 = (TH2D*)Output->Get("hkrPd0Pd1Amp_29");
	hkrPd0Pd1Amp_29->SetTitle("Detector 29");
	hkrPd0Pd1Amp_29->SetStats(000);
		
	TCutG *hkrPd0Pd1Amp_29_cut = new TCutG();
	hkrPd0Pd1Amp_29_cut = (TCutG*)Cuts->Get("hkrPd0Pd1Amp_29_cut");
	hkrPd0Pd1Amp_29_cut->SetLineWidth(2);
	hkrPd0Pd1Amp_29_cut->SetLineColor(2);
	
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.05);
	hkrPd0Pd1Amp_29->Draw("colz");
	//hkrPd0Pd1Amp_29_cut->Draw("same");
	
	//c1->SaveAs("Cuty graficzne.root");
	
	c1->SaveAs("Schemat.png");
	
	cout<<"IntegralHist0 = "<<hkrPd0Pd1Amp_0_cut->IntegralHist(hkrPd0Pd1Amp_0)<<endl;
	cout<<"IntegralHist1 = "<<hkrPd0Pd1Amp_1_cut->IntegralHist(hkrPd0Pd1Amp_1)<<endl;
	cout<<"IntegralHist7 = "<<hkrPd0Pd1Amp_7_cut->IntegralHist(hkrPd0Pd1Amp_7)<<endl;
	
	
	
	
	
	
	
	
	
	
	/*Zliczenia w cutach*/
	
	TCanvas *c2 = new TCanvas("c2", "canvas2", 1500, 500);
	c2->SetGrid();
	c2->SetBottomMargin(0);
	c2->SetTopMargin(0.15);
	c2->Divide(11, 3);
	
	//Detector 0
	c2->cd(1);
	
	TBox *box = new TBox(0.3, 0.3, 1, 0.9);
	box->Draw();
	
	TLatex *   dete0 = new TLatex(0.45,0.75,"Detector 0");
	dete0->SetNDC();
	dete0->SetTextSize(0.1);
	dete0->Draw();
	
	double d = hkrPd0Pd1Amp_0_cut->IntegralHist(hkrPd0Pd1Amp_0);

	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << d;
	std::string s = stream.str();
	const char *c = s.c_str();
	
	TLatex *   zliczenia0 = new TLatex(0.5,0.45,c);
	zliczenia0->SetNDC();
	zliczenia0->SetTextSize(0.1);
	zliczenia0->Draw();
	s="";
	c="";
	stream.str("");
	
	
	
	//Detector 1
	c2->cd(2);
	box->Draw();

	
	TLatex *   dete1 = new TLatex(0.45,0.75,"Detector 1");
	dete1->SetNDC();
	dete1->SetTextSize(0.1);
	dete1->Draw();
	
	d = hkrPd0Pd1Amp_1_cut->IntegralHist(hkrPd0Pd1Amp_1);

	stream << std::fixed << std::setprecision(0) << d;
	s = stream.str();
	c = s.c_str();
	
	TLatex *   zliczenia1 = new TLatex(0.55,0.45,c);
	zliczenia1->SetNDC();
	zliczenia1->SetTextSize(0.1);
	zliczenia1->Draw();
	s="";
	c="";
	stream.str("");
	
	
	
	//Detector 2
	c2->cd(3);
	box->Draw();
	
	TLatex *   dete2 = new TLatex(0.4,0.75,"Detector 2");
	dete2->SetNDC();
	dete2->SetTextSize(0.1);
	dete2->Draw();
	
	TLatex *   zliczenia2 = new TLatex(0.6,0.45,"X");
	zliczenia2->SetNDC();
	zliczenia2->SetTextSize(0.1);
	zliczenia2->Draw();
	
	//Detector 3
	c2->cd(4);
	box->Draw();
	
	TLatex *   dete3 = new TLatex(0.4,0.75,"Detector 3");
	dete3->SetNDC();
	dete3->SetTextSize(0.1);
	dete3->Draw();
	
	TLatex *   zliczenia3 = new TLatex(0.6,0.45,"X");
	zliczenia3->SetNDC();
	zliczenia3->SetTextSize(0.1);
	zliczenia3->Draw();
	
	//Detector 4
	c2->cd(5);
	box->Draw();
	
	TLatex *   dete4 = new TLatex(0.45,0.75,"Detector 4");
	dete4->SetNDC();
	dete4->SetTextSize(0.1);
	dete4->Draw();
	
	TLatex *   zliczenia4 = new TLatex(0.65,0.45,"X");
	zliczenia4->SetNDC();
	zliczenia4->SetTextSize(0.1);
	zliczenia4->Draw();
	
	//Target
	c2->cd(6);
	
	//Detector 5
	c2->cd(7);
	box->Draw();
	
	TLatex *   dete5 = new TLatex(0.45,0.75,"Detector 5");
	dete5->SetNDC();
	dete5->SetTextSize(0.1);
	dete5->Draw();
	
	TLatex *   zliczenia5 = new TLatex(0.65,0.45,"X");
	zliczenia5->SetNDC();
	zliczenia5->SetTextSize(0.1);
	zliczenia5->Draw();
	
	//Detector 6
	c2->cd(8);
	box->Draw();
	
	TLatex *   dete6 = new TLatex(0.45,0.75,"Detector 6");
	dete6->SetNDC();
	dete6->SetTextSize(0.1);
	dete6->Draw();
	
	TLatex *   zliczenia6 = new TLatex(0.6,0.45,"X");
	zliczenia6->SetNDC();
	zliczenia6->SetTextSize(0.1);
	zliczenia6->Draw();
	
	//Detector 7
	c2->cd(9);
	box->Draw();
	
	TLatex *   dete7 = new TLatex(0.45,0.75,"Detector 7");
	dete7->SetNDC();
	dete7->SetTextSize(0.1);
	dete7->Draw();
	
	d = hkrPd0Pd1Amp_7_cut->IntegralHist(hkrPd0Pd1Amp_7);

	stream << std::fixed << std::setprecision(0) << d;
	s = stream.str();
	c = s.c_str();
	
	TLatex *   zliczenia7 = new TLatex(0.6,0.45,c);
	zliczenia7->SetNDC();
	zliczenia7->SetTextSize(0.1);
	zliczenia7->Draw();
	s="";
	c="";
	stream.str("");
	
	//Detector 8
	c2->cd(10);
	box->Draw();
	
	TLatex *   dete8 = new TLatex(0.45,0.75,"Detector 8");
	dete8->SetNDC();
	dete8->SetTextSize(0.1);
	dete8->Draw();
	
	d = hkrPd0Pd1Amp_8_cut->IntegralHist(hkrPd0Pd1Amp_8);

	stream << std::fixed << std::setprecision(0) << d;
	s = stream.str();
	c = s.c_str();
	
	TLatex *   zliczenia8 = new TLatex(0.55,0.45,c);
	zliczenia8->SetNDC();
	zliczenia8->SetTextSize(0.1);
	zliczenia8->Draw();
	s="";
	c="";
	stream.str("");
	
	
	//Detector 9
	c2->cd(11);
	box->Draw();
	
	TLatex *   dete9 = new TLatex(0.4,0.75,"Detector 9");
	dete9->SetNDC();
	dete9->SetTextSize(0.1);
	dete9->Draw();
	
	d = hkrPd0Pd1Amp_9_cut->IntegralHist(hkrPd0Pd1Amp_9);

	stream << std::fixed << std::setprecision(0) << d;
	s = stream.str();
	c = s.c_str();
	
	TLatex *   zliczenia9 = new TLatex(0.55,0.45,c);
	zliczenia9->SetNDC();
	zliczenia9->SetTextSize(0.1);
	zliczenia9->Draw();
	s="";
	c="";
	stream.str("");
	
	//Detector 10
	c2->cd(12);
	box->Draw();
	
	TLatex *   dete10 = new TLatex(0.4,0.75,"Detector 10");
	dete10->SetNDC();
	dete10->SetTextSize(0.1);
	dete10->Draw();
	
	d = hkrPd0Pd1Amp_10_cut->IntegralHist(hkrPd0Pd1Amp_10);

	stream << std::fixed << std::setprecision(0) << d;
	s = stream.str();
	c = s.c_str();
	
	TLatex *   zliczenia10 = new TLatex(0.55,0.45,c);
	zliczenia10->SetNDC();
	zliczenia10->SetTextSize(0.1);
	zliczenia10->Draw();
	s="";
	c="";
	stream.str("");
	
	//Detector 11
	c2->cd(13);
	box->Draw();
	
	TLatex *   dete11 = new TLatex(0.4,0.75,"Detector 11");
	dete11->SetNDC();
	dete11->SetTextSize(0.1);
	dete11->Draw();
	
	d = hkrPd0Pd1Amp_11_cut->IntegralHist(hkrPd0Pd1Amp_11);

	stream << std::fixed << std::setprecision(0) << d;
	s = stream.str();
	c = s.c_str();
	
	TLatex *   zliczenia11 = new TLatex(0.55,0.45,c);
	zliczenia11->SetNDC();
	zliczenia11->SetTextSize(0.1);
	zliczenia11->Draw();
	s="";
	c="";
	stream.str("");
	
	//Detector 12
	c2->cd(14);
	box->Draw();
	
	TLatex *   dete12 = new TLatex(0.4,0.75,"Detector 12");
	dete12->SetNDC();
	dete12->SetTextSize(0.1);
	dete12->Draw();
	
	d = hkrPd0Pd1Amp_12_cut->IntegralHist(hkrPd0Pd1Amp_12);

	stream << std::fixed << std::setprecision(0) << d;
	s = stream.str();
	c = s.c_str();
	
	TLatex *   zliczenia12 = new TLatex(0.55,0.45,c);
	zliczenia12->SetNDC();
	zliczenia12->SetTextSize(0.1);
	zliczenia12->Draw();
	s="";
	c="";
	stream.str("");
	
	//Detector 13
	c2->cd(15);
	box->Draw();
	
	TLatex *   dete13 = new TLatex(0.4,0.75,"Detector 13");
	dete13->SetNDC();
	dete13->SetTextSize(0.1);
	dete13->Draw();
	
	TLatex *   zliczenia13 = new TLatex(0.6,0.45,"X");
	zliczenia13->SetNDC();
	zliczenia13->SetTextSize(0.1);
	zliczenia13->Draw();
	
	//Detector 14
	c2->cd(16);
	box->Draw();
	
	TLatex *   dete14 = new TLatex(0.4,0.75,"Detector 14");
	dete14->SetNDC();
	dete14->SetTextSize(0.1);
	dete14->Draw();
	
	TLatex *   zliczenia14 = new TLatex(0.6,0.45,"X");
	zliczenia14->SetNDC();
	zliczenia14->SetTextSize(0.1);
	zliczenia13->Draw();
	
	//Target
	c2->cd(17);
	
	Target->Draw();
	
	//Detector 15
	c2->cd(18);
	box->Draw();
	
	TLatex *   dete15 = new TLatex(0.4,0.75,"Detector 15");
	dete15->SetNDC();
	dete15->SetTextSize(0.1);
	dete15->Draw();
	
	TLatex *   zliczenia15 = new TLatex(0.6,0.45,"X");
	zliczenia15->SetNDC();
	zliczenia15->SetTextSize(0.1);
	zliczenia15->Draw();
	
	//Detector 16
	c2->cd(19);
	box->Draw();
	
	TLatex *   dete16 = new TLatex(0.4,0.75,"Detector 16");
	dete16->SetNDC();
	dete16->SetTextSize(0.1);
	dete16->Draw();
	
	d = hkrPd0Pd1Amp_16_cut->IntegralHist(hkrPd0Pd1Amp_16);

	stream << std::fixed << std::setprecision(0) << d;
	s = stream.str();
	c = s.c_str();
	
	TLatex *   zliczenia16 = new TLatex(0.55,0.45,c);
	zliczenia16->SetNDC();
	zliczenia16->SetTextSize(0.1);
	zliczenia16->Draw();
	s="";
	c="";
	stream.str("");
	
	//Detector 17
	c2->cd(20);
	box->Draw();
	
	TLatex *   dete17 = new TLatex(0.4,0.75,"Detector 17");
	dete17->SetNDC();
	dete17->SetTextSize(0.1);
	dete17->Draw();
	
	d = hkrPd0Pd1Amp_17_cut->IntegralHist(hkrPd0Pd1Amp_17);

	stream << std::fixed << std::setprecision(0) << d;
	s = stream.str();
	c = s.c_str();
	
	TLatex *   zliczenia17 = new TLatex(0.55,0.45,c);
	zliczenia17->SetNDC();
	zliczenia17->SetTextSize(0.1);
	zliczenia17->Draw();
	s="";
	c="";
	stream.str("");
	
	//Detector 18
	c2->cd(21);
	box->Draw();
	
	TLatex *   dete18 = new TLatex(0.4,0.75,"Detector 18");
	dete18->SetNDC();
	dete18->SetTextSize(0.1);
	dete18->Draw();
	
	d = hkrPd0Pd1Amp_18_cut->IntegralHist(hkrPd0Pd1Amp_18);

	stream << std::fixed << std::setprecision(0) << d;
	s = stream.str();
	c = s.c_str();
	
	TLatex *   zliczenia18 = new TLatex(0.55,0.45,c);
	zliczenia18->SetNDC();
	zliczenia18->SetTextSize(0.1);
	zliczenia18->Draw();
	s="";
	c="";
	stream.str("");
	
	//Detector 19
	c2->cd(22);
	box->Draw();
	
	TLatex *   dete19 = new TLatex(0.4,0.75,"Detector 19");
	dete19->SetNDC();
	dete19->SetTextSize(0.1);
	dete19->Draw();
	
	TLatex *   zliczenia19 = new TLatex(0.6,0.45,"X");
	zliczenia19->SetNDC();
	zliczenia19->SetTextSize(0.1);
	zliczenia19->Draw();
	
	//Detector 20
	c2->cd(23);
	box->Draw();
	
	TLatex *   dete20 = new TLatex(0.4,0.75,"Detector 20");
	dete20->SetNDC();
	dete20->SetTextSize(0.1);
	dete20->Draw();
	
	d = hkrPd0Pd1Amp_20_cut->IntegralHist(hkrPd0Pd1Amp_20);

	stream << std::fixed << std::setprecision(0) << d;
	s = stream.str();
	c = s.c_str();
	
	TLatex *   zliczenia20 = new TLatex(0.5,0.45,c);
	zliczenia20->SetNDC();
	zliczenia20->SetTextSize(0.1);
	zliczenia20->Draw();
	s="";
	c="";
	stream.str("");
	
	//Detector 21
	c2->cd(24);
	box->Draw();
	
	TLatex *   dete21 = new TLatex(0.4,0.75,"Detector 21");
	dete21->SetNDC();
	dete21->SetTextSize(0.1);
	dete21->Draw();
	
	d = hkrPd0Pd1Amp_21_cut->IntegralHist(hkrPd0Pd1Amp_21);

	stream << std::fixed << std::setprecision(0) << d;
	s = stream.str();
	c = s.c_str();
	
	TLatex *   zliczenia21 = new TLatex(0.55,0.45,c);
	zliczenia21->SetNDC();
	zliczenia21->SetTextSize(0.1);
	zliczenia21->Draw();
	s="";
	c="";
	stream.str("");
	
	//Detector 22
	c2->cd(25);
	box->Draw();
	
	TLatex *   dete22 = new TLatex(0.4,0.75,"Detector 22");
	dete22->SetNDC();
	dete22->SetTextSize(0.1);
	dete22->Draw();
	
	d = hkrPd0Pd1Amp_22_cut->IntegralHist(hkrPd0Pd1Amp_22);

	stream << std::fixed << std::setprecision(0) << d;
	s = stream.str();
	c = s.c_str();
	
	TLatex *   zliczenia22 = new TLatex(0.55,0.45,c);
	zliczenia22->SetNDC();
	zliczenia22->SetTextSize(0.1);
	zliczenia22->Draw();
	s="";
	c="";
	stream.str("");
	
	//Detector 23
	c2->cd(26);
	box->Draw();
	
	TLatex *   dete23 = new TLatex(0.4,0.75,"Detector 23");
	dete23->SetNDC();
	dete23->SetTextSize(0.1);
	dete23->Draw();
	
	TLatex *   zliczenia23 = new TLatex(0.6,0.45,"X");
	zliczenia23->SetNDC();
	zliczenia23->SetTextSize(0.1);
	zliczenia23->Draw();
	
	//Detector 24
	c2->cd(27);
	box->Draw();
	
	TLatex *   dete24 = new TLatex(0.4,0.75,"Detector 24");
	dete24->SetNDC();
	dete24->SetTextSize(0.1);
	dete24->Draw();
	
	TLatex *   zliczenia24 = new TLatex(0.6,0.45,"X");
	zliczenia24->SetNDC();
	zliczenia24->SetTextSize(0.1);
	zliczenia24->Draw();
	
	//Target
	c2->cd(28);
	
	//Detector 25
	c2->cd(29);
	box->Draw();
	
	TLatex *   dete25 = new TLatex(0.4,0.75,"Detector 25");
	dete25->SetNDC();
	dete25->SetTextSize(0.1);
	dete25->Draw();
	
	TLatex *   zliczenia25 = new TLatex(0.6,0.45,"X");
	zliczenia25->SetNDC();
	zliczenia25->SetTextSize(0.1);
	zliczenia25->Draw();
	
	//Detector 26
	c2->cd(30);
	box->Draw();
	
	TLatex *   dete26 = new TLatex(0.4,0.75,"Detector 26");
	dete26->SetNDC();
	dete26->SetTextSize(0.1);
	dete26->Draw();
	
	TLatex *   zliczenia26 = new TLatex(0.6,0.45,"X");
	zliczenia26->SetNDC();
	zliczenia26->SetTextSize(0.1);
	zliczenia26->Draw();
	
	//Detector 27
	c2->cd(31);
	box->Draw();
	
	TLatex *   dete27 = new TLatex(0.4,0.75,"Detector 27");
	dete27->SetNDC();
	dete27->SetTextSize(0.1);
	dete27->Draw();
	
	d = hkrPd0Pd1Amp_27_cut->IntegralHist(hkrPd0Pd1Amp_27);

	stream << std::fixed << std::setprecision(0) << d;
	s = stream.str();
	c = s.c_str();
	
	TLatex *   zliczenia27 = new TLatex(0.55,0.45,c);
	zliczenia27->SetNDC();
	zliczenia27->SetTextSize(0.1);
	zliczenia27->Draw();
	s="";
	c="";
	stream.str("");
	
	//Detector 28
	c2->cd(32);
	box->Draw();
	
	TLatex *   dete28 = new TLatex(0.4,0.75,"Detector 28");
	dete28->SetNDC();
	dete28->SetTextSize(0.1);
	dete28->Draw();
	
	d = hkrPd0Pd1Amp_28_cut->IntegralHist(hkrPd0Pd1Amp_28);

	stream << std::fixed << std::setprecision(0) << d;
	s = stream.str();
	c = s.c_str();
	
	TLatex *   zliczenia28 = new TLatex(0.55,0.45,c);
	zliczenia28->SetNDC();
	zliczenia28->SetTextSize(0.1);
	zliczenia28->Draw();
	s="";
	c="";
	stream.str("");
	
	//Detector 29
	c2->cd(33);
	box->Draw();
	
	TLatex *   dete29 = new TLatex(0.4,0.75,"Detector 29");
	dete29->SetNDC();
	dete29->SetTextSize(0.1);
	dete29->Draw();
	
	d = hkrPd0Pd1Amp_29_cut->IntegralHist(hkrPd0Pd1Amp_29);

	stream << std::fixed << std::setprecision(0) << d;
	s = stream.str();
	c = s.c_str();
	
	TLatex *   zliczenia29 = new TLatex(0.5,0.45,c);
	zliczenia29->SetNDC();
	zliczenia29->SetTextSize(0.1);
	zliczenia29->Draw();
	s="";
	c="";
	stream.str("");
	
	c2->SaveAs("Zliczenia.png");
	c2->SaveAs("Zliczenia.root");
	
	return 0;
}
