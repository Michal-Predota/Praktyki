#include "Kratta.h"
#include "Plastic.h"
#include "Stat.h"
#include <algorithm>
#include "Scaler.h"
//#include "Wave.h"
#include "TTree.h"
#include "TCutG.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TText.h"

#include "time.h"

int funny_sign_count=0;

bool czy_deuteron(int arr[30])
{
	bool ret = false;
	for(int i=0; i<30; i++)
	{
		if(arr[i]==1)
			ret = true;
	}
	return ret;
}

int gdzie(int arr[30], int a)
{
	int ret=-1;
	for(int i=0;i<30;i++)
	{
		if(arr[i]==a)
			ret = i;
	}
	return ret;
}

int gdzie_max(int arr[30])
{
	int n = sizeof(arr) / sizeof(arr[0]);
	int max = *max_element(arr,arr+n);
	int index = find(arr, arr+n, max) - arr;
	return index;
}

int largest(int arr[30])
{
    
     
    int max = arr[0];
 
    for (int i = 1; i < 30; i++)
        if (arr[i] > max)
            max = arr[i];
 
    return max;
}


void Counting(ULong64_t ent){
	if(ent%100000==0)
		{

	switch (funny_sign_count%4)
		{
	case 0:
		printf("  | \t");
		 break;
	case 1:
		printf("  / \t");
		break;
	case 2:
		printf("  --\t");
		break;
	case 3:
		printf("  \\ \t");
		break;
	}
		printf("Event_num=%lld\r",ent);
		fflush(stdout);
		funny_sign_count++;
	}
}



void analyze1(TTree * tree){
//cout<<"aaaa"<<endl;
TH2F *wykresy[30][30];
TH2F *wykresy_Pd1Pd0[30][30];
char nazwa_detektora[30];
char nazwa_detektora1[30];

for(int h=0; h<30; h++)
{
	for(int j=0; j<30; j++)
	{
		sprintf(nazwa_detektora, "det_%d_hkrPd1Pd2Amp_%d", h, j);
		sprintf(nazwa_detektora1, "det_%d_hkrPd0Pd1Amp_%d", h, j);
		wykresy[h][j] = new TH2F("","",250,0,2500,250,0,2500);
		wykresy_Pd1Pd0[h][j] = new TH2F("","",250,0,2500,250,0,2500);
		//cout<<h<<"  "<<j<<endl;
		wykresy[h][j]->SetTitle(nazwa_detektora);
		wykresy[h][j] ->SetMarkerSize(3);
		wykresy_Pd1Pd0[h][j] ->SetMarkerSize(3);
		wykresy[h][j] ->SetTitleSize(3);
		wykresy_Pd1Pd0[h][j] ->SetTitleSize(3);
	}
}

  clock_t fbegin;
  clock_t fend;
fbegin = clock(); //Start clock
printf("************** Analyze START **************\n");

//
Float_t norm=1.69/3900.0*15.8;

Float_t AllTime=133200.0;
Float_t GoodTime=79200.0;
Float_t PreScalFactor=128.0;
//Float_t norm=1;
    Plastic * plastic = new Plastic;
    Kratta *  kratta = new Kratta;
    Scaler *  scaler = new Scaler;

int detekcje[32];//tablica w której na każdym miejscu jedynką zaznaczone będzie wykrycie cząsteczki, 1 - deuteron, 2 - coś innego
memset(detekcje, 0, sizeof(detekcje));

char dir [100]= "./Pics/New/";

		char katyL[5][20] = {
			"37#circ",
			"43#circ",
			"49#circ",
			"55#circ",
			"61#circ"
		};

		char katyR[5][20] = {
			"61#circ",
			"55#circ",
			"49#circ",
			"43#circ",
			"37#circ"
		};

		char level[3][20] = {
			"Bottom",
			"Middle",
			"Top"
		};


    TH2F * cor_kratta_plastic = new TH2F("cor_kratta_plastic","cor_kratta_plastic",120,0,120,32,0,32);
    TH2F * pl_xy = new TH2F("pl_xy","pl_xy",20, -0.5, 9.5, 8, -0.5, 4.5);
		//TH2F * pl_xy_t = new TH2F("pl_xy_t","pl_xy_t",100, -20, 20, 100, -20, 20);
    TH1F *htBit= new TH1F("htBit","htBit",10,0,10);
    TH1F *hkr_id= new TH1F("hkr_id","hkr_id",30,0,30);
    TH1F *hpl_id= new TH1F("hpl_id","hpl_id",120,0,120);
    TH1F *hkrMult= new TH1F("hkrMult","hkrMult",30,0,30);
    TH1F *hplMult= new TH1F("hplMult","hplMult",20,0,20);
    TH1F *hplMultMod= new TH1F("hplMultMod","hplMultMod",30,0,30);
    TH1F *hfullModMult= new TH1F("hfullModMult","hfullModMult",30,0,30);
    TH2F *coinc_all = new TH2F("coinc_all","coinc_all",30, 0, 30, 30, 0, 30);


		TH1F *hkrPd0AmpAll= new TH1F("hkrPd0AmpAll","hkrPd0AmpAll",100,0,1000);
		TH1F *hkrPd1AmpAll= new TH1F("hkrPd1AmpAll","hkrPd1AmpAll",100,0,2500);
		TH1F *hkrPd2AmpAll= new TH1F("hkrPd2AmpAll","hkrPd2AmpAll",100,0,1500);

    TH2F *coinc_37LR = new TH2F("coinc_37LR","Coinc. 37#circ LEFT #minus RIGHT",5, 0.5, 5.5, 3, 0.5, 3.5);
    TH2F *coinc_37RL = new TH2F("coinc_37RL","Coinc. 37#circ RIGHT #minus LEFT",5, 0.5, 5.5, 3, 0.5, 3.5);
coinc_37LR->SetStats(0);
coinc_37RL->SetStats(0);

  //  TH1F *hplTime[130];
    TH1F *hkrattaTimePD0[35];
    TH1F *hkrattaTimePD1[35];
    TH1F *hkrattaTimePD2[35];


		TH2F *hplTime1Time2_37L[35];
		TH2F *hplTime1Time2_37R[35];

		TH1F *hkrPd0Amp[35];
		TH1F *hkrPd1Amp[35];
		TH1F *hkrPd2Amp[35];

		TH2F *hkrPd0Pd1Amp[35];
		TH2F *hkrPd1Pd2Amp[35];

		TH2F *hplTime1Time2_all[35][35];

		//TH2F *hplpl_all[130][130];


    char name[200];
    char name1[200];

    // TNtuple *ntuple = new TNtuple("ntuple","data","pd0Am:pd1Am:pd2Am");

    // for (int i=0;i<130;i++){
		//
    //   sprintf(name,"hplTime_%d",i);
    //   hplTime[i]= new TH1F(name,name,500,500,2000);
		//
		//
    // }
	
	
	TFile *Cuts = new TFile("Cuts_Coinc_All.root");
	char nazwa_cut[100];
	TCutG *Cut = new TCutG();

    for (int i=0;i<35;i++){

      sprintf(name,"hkrattaTimePD0_%d",i);
      hkrattaTimePD0[i]= new TH1F(name,name,500,0,1000);

      sprintf(name,"hkrattaTimePD1_%d",i);
      hkrattaTimePD1[i]= new TH1F(name,name,500,0,1000);

      sprintf(name,"hkrattaTimePD2_%d",i);
      hkrattaTimePD2[i]= new TH1F(name,name,500,0,1000);

			sprintf(name,"hplTime1Time2_37L_%d",i);
			hplTime1Time2_37L[i]=new TH2F(name,name,250,1000,1250,250,1000,1250);

			sprintf(name,"hplTime1Time2_37R_%d",i);
			hplTime1Time2_37R[i]=new TH2F(name,name,250,1000,1250,250,1000,1250);

			sprintf(name,"hkrPd0Amp_%d",i);
			hkrPd0Amp[i]=new TH1F(name,name,100,0,1000);

			sprintf(name,"hkrPd1Amp_%d",i);
			hkrPd1Amp[i]=new TH1F(name,name,100,0,2500);

			sprintf(name,"hkrPd2Amp_%d",i);
			hkrPd2Amp[i]=new TH1F(name,name,100,0,1500);

			sprintf(name,"hkrPd0Pd1Amp_%d",i);
			//hkrPd0Pd1Amp[i]=new TH2F(name,name,500,0,2500,500,0,1500);
			hkrPd0Pd1Amp[i]=new TH2F(name,name,250,0,3000,250,0,1500);

			hkrPd0Pd1Amp[i]->GetXaxis()->SetTitleSize(0.05);
			hkrPd0Pd1Amp[i]->GetXaxis()->SetLabelSize(0.04);
			hkrPd0Pd1Amp[i]->GetYaxis()->SetTitleSize(0.05);
			hkrPd0Pd1Amp[i]->GetYaxis()->SetLabelSize(0.04);
			hkrPd0Pd1Amp[i]->GetXaxis()->SetTitleOffset(0.9);
			hkrPd0Pd1Amp[i]->GetYaxis()->SetTitleOffset(0.97);
			hkrPd0Pd1Amp[i]->GetXaxis()->SetTitle("Pd1 Amplitude [ch]");
			hkrPd0Pd1Amp[i]->GetYaxis()->SetTitle("Pd0 Amplitude [ch]");

			sprintf(name,"hkrPd1Pd2Amp_%d",i);
			//hkrPd1Pd2Amp[i]=new TH2F(name,name,500,0,2500,500,0,2500);
			hkrPd1Pd2Amp[i]=new TH2F(name,name,250,0,2500,250,0,2500);

			 hkrPd1Pd2Amp[i]->GetXaxis()->SetTitleSize(0.05);
			 hkrPd1Pd2Amp[i]->GetXaxis()->SetLabelSize(0.04);
			 hkrPd1Pd2Amp[i]->GetYaxis()->SetTitleSize(0.05);
			 hkrPd1Pd2Amp[i]->GetYaxis()->SetLabelSize(0.04);
			 hkrPd1Pd2Amp[i]->GetXaxis()->SetTitleOffset(0.9);
			 hkrPd1Pd2Amp[i]->GetYaxis()->SetTitleOffset(0.97);
			 hkrPd1Pd2Amp[i]->GetXaxis()->SetTitle("Pd2 Amplitude [ch]");
			 hkrPd1Pd2Amp[i]->GetYaxis()->SetTitle("Pd1 Amplitude [ch]");


			for (int j=0;j<35;j++){
				sprintf(name,"hplTime1Time2_%d_%d",i,j);
				hplTime1Time2_all[i][j]=new TH2F(name,name,250,0,1500,250,0,1500);
			}
    }

		// for (int i=0;i<130;i++){
		// 	for (int j=0;j<130;j++){
		// 		sprintf(name,"hplpl_%d_%d",i,j);
		// 		hplpl_all[i][j]=new TH2F(name,name,250,1000,1250,250,1000,1250);
		// 	}
		// }



    struct {
    int nrun;
    int id;
    int trig;
    int mult;
    } info;


    tree->SetBranchAddress("scaler", &scaler);
    tree->SetBranchAddress("plastic", &plastic);
    tree->SetBranchAddress("kratta", &kratta);
    tree->SetBranchAddress("info", &info);




    //TLeaf *ampl1 = kratta->GetLeaf("det.pd1.ampl");

    int Nev = tree->GetEntries();

    for(int iev=0; iev<Nev; iev++){ // Loop over events

      tree->GetEntry(iev);        // Gets a new event

      Counting(iev);



	htBit->Fill(info.trig);

	// if(info.trig>2) continue; //trigger selection

	for(int j=0; j< plastic->mult(); j++){

	  int pl=plastic->det[j].id;
	  float pltime= plastic->det[j].time;

	 // hplTime[pl]->Fill(pltime);
	}


      for(int i=0; i< plastic->mult(); i++){

	pl_xy->Fill(plastic->det[i].x(), plastic->det[i].y());

      }

      for(int j=0; j< kratta->mult(); j++){

	hkr_id->Fill(kratta->det[j].id);

	//cout<<iev<<" kratta_id: "<<kratta->det[j].id<<endl;
      }

      int plMultmod[32]={0};



    //  for(int i=0; i< plastic->mult(); i++)hpl_id->Fill(plastic->det[i].id);

      for(int i=0; i< plastic->mult(); i++){
	hpl_id->Fill(plastic->det[i].id);
	//if(plastic->det[i].intime())
	for(int j=0; j< kratta->mult(); j++){
	  //if(kratta->det[j].pd0pd1())
	  //if(kratta->det[j].pd1pd2())
	  cor_kratta_plastic->Fill(plastic->det[i].id,kratta->det[j].id);
          plMultmod[j]++;
	}
      }

      hkrMult->Fill(kratta->mult());
      hplMult->Fill(plastic->mult());

      for(int j=0; j< kratta->mult(); j++) hplMultMod->Fill(plMultmod[j]);//plastic mult per module



      int fullModMult=0;
      int plid=-1;
      int krm[32]={0};
      int kk=0;

      int kr4_37=0, kr14_37=0, kr24_37=0;
      int krR[32]={0};

	if(plastic->mult()>1){
      for(int j=0; j< plastic->mult(); j++){

	int krid=plastic->det[j].kratta();

	if(krid<0 || krid>31) continue;


	// cout<<iev<<" kratta id from pl: "<<krid<<endl;
	// cout<<" >>>>>> "<<kratta->det[krid].pd1pd2()<<endl;
	// cout<<j<<" "<<plastic->det[j].intime()<<endl;
	//if(plastic->det[j].intime() && kratta->det[krid].pd1pd2()) krm[krid]++;
	int pl=plastic->det[j].id;
	float pltime= plastic->det[j].time;
	int pl_intime=0;

	if(pl<0 || pl>130) continue;
	//if(pltime>1150 && pltime<1250)pl_intime=1;
	if(pltime>1000 && pltime<1250)pl_intime=1;

	int kr_iter=-999;
	for(int k=0; k< kratta->mult(); k++){
		if(krid == kratta->det[k].id) kr_iter=k;

	}




	if(kr_iter<0 || kr_iter>31) continue;

	float krpd0time=kratta->det[kr_iter].pd0.time;
	float krpd1time=kratta->det[kr_iter].pd1.time;
	float krpd2time=kratta->det[kr_iter].pd2.time;

	float krpd0Amp=kratta->det[kr_iter].pd0.ampl;
	float krpd1Amp=kratta->det[kr_iter].pd1.ampl;
	float krpd2Amp=kratta->det[kr_iter].pd2.ampl;

int amp_flag=0;
	if(krpd0Amp>10 && krpd1Amp>10 ) amp_flag=1;

	/************************************************************Nowe rzeczy***************************************************************************/
	int cut_flag = 0;
	sprintf(nazwa_cut, "hkrPd0Pd1Amp_%d_cut", kratta->det[kr_iter].id);
	//cout<<kr_iter<<endl;
	if(Cuts->GetListOfKeys()->Contains(nazwa_cut))
	{
		//cout<<nazwa_cut<<endl;
		Cut = (TCutG*)Cuts->Get(nazwa_cut);
		if(Cut->IsInside(krpd1Amp, krpd0Amp))
			cut_flag=1;
			//cout<<"jestem"<<endl;
	}

	//if (krid==25)cout<<krpd1time<<endl;
	int kr_PD0intime=0;
	if(krpd0time>460)kr_PD0intime=1;
	int kr_PD1intime=0;
	if(krpd1time>180)kr_PD1intime=1;



if(info.trig==1) PreScalFactor=128;
else PreScalFactor=1;

	int time_flag=1;
	 if (pl_intime &&  kr_PD0intime && kr_PD1intime)time_flag=1;
	if(time_flag) krR[krid]++;

	if(time_flag && amp_flag && cut_flag) {
		//cout<<"deuteron"<<endl;
		detekcje[kratta->det[kr_iter].id] = 1;

		hkrPd0Pd1Amp[krid]->Fill(krpd1Amp, krpd0Amp, PreScalFactor);
		hkrPd0AmpAll->Fill(krpd0Amp);
		hkrPd1AmpAll->Fill(krpd1Amp);
		hkrPd0Amp[krid]->Fill(krpd0Amp);
		hkrPd1Amp[krid]->Fill(krpd1Amp);

		if(krpd2Amp>10){
			hkrPd1Pd2Amp[krid]->Fill(krpd2Amp, krpd1Amp, PreScalFactor);
			hkrPd2AmpAll->Fill(krpd2Amp);
			hkrPd2Amp[krid]->Fill(krpd2Amp);
			}


	}
	
	else if(time_flag && amp_flag && !cut_flag && ((krpd0Amp>20 && krpd1Amp>20) || (krpd1Amp>20 && krpd0Amp>20))
	{
		//cout<<kratta->det[kr_iter].id<<endl;
		detekcje[kratta->det[kr_iter].id] = 2;
	}
	
	/*cout<<"ile  "<<plastic->mult()<<endl;
	for(int d=0; d<30; d++)
	{
		cout<<detekcje[d]<<"  ";
	}
	cout<<endl;*/
	if(czy_deuteron(detekcje))
	{
		//cout<<"jest"<<endl;
		for(int wyk=0; wyk<30; wyk++)
		{
		//if(detekcje[wyk]==1)
		//{
			//cout<<"if"<<endl;
			
				int tmpp;
				tmpp = gdzie(detekcje, 1);
			//cout<<"tmpp: "<<tmpp<<endl;
				if(tmpp<0)
				{
					continue;
				}
				for(int d=0; d<30; d++)
				{
				//cout<<detekcje[d]<<"  ";
				//cout<<wyk<<"   "<<d<<endl;
					if(detekcje[d]==2 &&tmpp>=0 && tmpp<30)
					{
					//cout<<"a"<<endl;
						wykresy[tmpp][d]->Fill(krpd2Amp, krpd1Amp);
						wykresy_Pd1Pd0[tmpp][d]->Fill(krpd1Amp, krpd0Amp);
					}
				}
				tmpp=0;
			//cout<<endl;
		//}
		}
	}
	
	
      }//koniec petli po j
		}

	memset(detekcje, 0, sizeof(detekcje));
	//cout<<"koniec"<<endl;




		if(plastic->mult()>1)	{
			for(int i=0; i< plastic->mult(); i++){
				if(plastic->det[i].time>1000 && plastic->det[i].time<1250){
					for(int j=i+1; j< plastic->mult(); j++){
						if(plastic->det[j].time>1000 && plastic->det[j].time<1250){
							hplTime1Time2_all[plastic->det[i].kratta()][plastic->det[j].kratta()]->Fill(plastic->det[i].time,plastic->det[j].time);
				//			hplpl_all[plastic->det[i].id][plastic->det[j].id]->Fill(plastic->det[i].time,plastic->det[j].time);
				}
				}
			}
			}
		}




      //cout<<kr4_37<<endl;

      if(krR[4] && krR[25] ){
				coinc_37LR->Fill(1,1,norm);
			}
      if(krR[4] && krR[26] ){
				coinc_37LR->Fill(2,1,norm);
			}
      if(krR[4] && krR[27] ){
				coinc_37LR->Fill(3,1,norm);
			}
      if(krR[4] && krR[28] ){
				coinc_37LR->Fill(4,1,norm);
			}
      if(krR[4] && krR[29] ){
				coinc_37LR->Fill(5,1,norm);
			}

      if(krR[14] && krR[15] ){
				coinc_37LR->Fill(1,2,norm);
			}
      if(krR[14] && krR[16] ){
				coinc_37LR->Fill(2,2,norm);
			}
      if(krR[14] && krR[17] ){
				coinc_37LR->Fill(3,2,norm);
			}
      if(krR[14] && krR[18] ){
				coinc_37LR->Fill(4,2,norm);
			}
      if(krR[14] && krR[19] ){
				coinc_37LR->Fill(5,2,norm);
			}

      if(krR[24] && krR[5] ){
				coinc_37LR->Fill(1,3,norm);
			}
      if(krR[24] && krR[6] ){
				coinc_37LR->Fill(2,3,norm);
			}
      if(krR[24] && krR[7] ){
				coinc_37LR->Fill(3,3,norm);
			}
      if(krR[24] && krR[8] ){
				coinc_37LR->Fill(4,3,norm);
			}
      if(krR[24] && krR[9] ){
				coinc_37LR->Fill(5,3,norm);
			}






			// if(krR[5] && krR[24] ){
			// 	coinc_37RL->Fill(1,1);
			// }
			// if(krR[5] && krR[23] ){
			// 	coinc_37RL->Fill(2,1);
			// }
			// if(krR[5] && krR[22] ){
			// 	coinc_37RL->Fill(3,1);
			// }
			// if(krR[5] && krR[21] ){
			// 	coinc_37RL->Fill(4,1);
			// }
			// if(krR[5] && krR[20] ){
			// 	coinc_37RL->Fill(5,1);
			// }
			//
			// if(krR[15] && krR[14] ){
			// 	coinc_37RL->Fill(1,2);
			// }
			// if(krR[15] && krR[13] ){
			// 	coinc_37RL->Fill(2,2);
			// }
			// if(krR[15] && krR[12] ){
			// 	coinc_37RL->Fill(3,2);
			// }
			// if(krR[15] && krR[11] ){
			// 	coinc_37RL->Fill(4,2);
			// }
			// if(krR[15] && krR[10] ){
			// 	coinc_37RL->Fill(5,2);
			// }
			//
			// if(krR[25] && krR[4] ){
			// 	coinc_37RL->Fill(1,3);
			// }
			// if(krR[25] && krR[3] ){
			// 	coinc_37RL->Fill(2,3);
			// }
			// if(krR[25] && krR[2] ){
			// 	coinc_37RL->Fill(3,3);
			// }
			// if(krR[25] && krR[1] ){
			// 	coinc_37RL->Fill(4,3);
			// }
			// if(krR[25] && krR[0] ){
			// 	coinc_37RL->Fill(5,3);
			// }

			if(krR[5] && krR[20] ){
				coinc_37RL->Fill(1,1,norm);
			}
			if(krR[5] && krR[21] ){
				coinc_37RL->Fill(2,1,norm);
			}
			if(krR[5] && krR[22] ){
				coinc_37RL->Fill(3,1,norm);
			}
			if(krR[5] && krR[23] ){
				coinc_37RL->Fill(4,1,norm);
			}
			if(krR[5] && krR[24] ){
				coinc_37RL->Fill(5,1,norm);
			}

			if(krR[15] && krR[10] ){
				coinc_37RL->Fill(1,2,norm);
			}
			if(krR[15] && krR[11] ){
				coinc_37RL->Fill(2,2,norm);
			}
			if(krR[15] && krR[12] ){
				coinc_37RL->Fill(3,2,norm);
			}
			if(krR[15] && krR[13] ){
				coinc_37RL->Fill(4,2,norm);
			}
			if(krR[15] && krR[14] ){
				coinc_37RL->Fill(5,2,norm);
			}

			if(krR[25] && krR[0] ){
				coinc_37RL->Fill(1,3,norm);
			}
			if(krR[25] && krR[1] ){
				coinc_37RL->Fill(2,3,norm);
			}
			if(krR[25] && krR[2] ){
				coinc_37RL->Fill(3,3,norm);
			}
			if(krR[25] && krR[3] ){
				coinc_37RL->Fill(4,3,norm);
			}
			if(krR[25] && krR[4] ){
				coinc_37RL->Fill(5,3,norm);
			}



			// if(kr4_37 && krR[25] )coinc_37LR->Fill(1,1);
			// if(kr4_37 && krR[26] )coinc_37LR->Fill(2,1);
			// if(kr4_37 && krR[27] )coinc_37LR->Fill(3,1);
			// if(kr4_37 && krR[28] )coinc_37LR->Fill(4,1);
			// if(kr4_37 && krR[29] )coinc_37LR->Fill(5,1);
			//
			// if(kr14_37 && krR[15] )coinc_37LR->Fill(1,2);
			// if(kr14_37 && krR[16] )coinc_37LR->Fill(2,2);
			// if(kr14_37 && krR[17] )coinc_37LR->Fill(3,2);
			// if(kr14_37 && krR[18] )coinc_37LR->Fill(4,2);
			// if(kr14_37 && krR[19] )coinc_37LR->Fill(5,2);
			//
			// if(kr24_37 && krR[5] )coinc_37LR->Fill(1,3);
			// if(kr24_37 && krR[6] )coinc_37LR->Fill(2,3);
			// if(kr24_37 && krR[7] )coinc_37LR->Fill(3,3);
			// if(kr24_37 && krR[8] )coinc_37LR->Fill(4,3);
			// if(kr24_37 && krR[9] )coinc_37LR->Fill(5,3);


  //     for(int j=0; j< kratta->mult(); j++)
	// {
	//   if(krm[j])fullModMult++;
	// }
	//
  //     hfullModMult->Fill(fullModMult);
	//
  //     for(int j=0; j< kratta->mult(); j++){
	// for(int k=0; k< kratta->mult(); k++){
	//     if(krm[j] && krm[k])coinc_all->Fill(j,k);
	// }
  //     }






      //for(int j=0; j< kratta->mult(); j++){
      //for(int k=0; k<4; k++){
      //plid=kratta->det[j].id*4+k;
      //if(plastic->det[i].id==plid && plastic->det[i].intime() && kratta->det[j].pd1pd2())plmult++;
      //	}
      //}



      ///***********************************************

        for(int j=0; j< kratta->mult(); j++){
          int knb=kratta->det[j].id;

	  if(kratta->det[j].pd0.ok()) hkrattaTimePD0[knb]->Fill(kratta->det[j].pd0.time);
	  if(kratta->det[j].pd1.ok()) hkrattaTimePD1[knb]->Fill(kratta->det[j].pd1.time);
	  if(kratta->det[j].pd2.ok()) hkrattaTimePD2[knb]->Fill(kratta->det[j].pd2.time);
	}






      //cout<<"::::: "<<iev<<endl;


      //if(plastic->det[i].intime())
      //if(kratta->det[j].pd0pd1())


      //for(int j=0; j< kratta->mult(); j++){
      //cout<<"kr: "<<kratta->det[j].id<<endl;;
      //for(int i=0; i< plastic->mult(); i++)
      //if(plastic->det[i].id>=68 && plastic->det[i].id<=71)
      //cout<<"pl: "<<plastic->det[i].id<<" "<<plastic->det[i].kratta()<<endl;;

      //    }






      /*
	for(int j=0; j< plastic->mult(); j++){
	//cout<<plastic->det[j].time<<endl;

	float pltime= plastic->det[j].time;
	int idpl=plastic->det[j].id;
	int idkr=plastic->det[j].kratta();

      //if(idkr==2)cout<<"---> "<<j<<" "<<idpl<<" "<<idkr<<endl;

      hpl_id->Fill(idpl);
      hplTime[idpl]->Fill(pltime);


      //cout<<idpl<<endl;
      }
      */



    } // End loop over events iev


    TCanvas *c[20];
cout<<"test_End\n";
    c[0]=new TCanvas ("coinc_37LR","coinc_37LR");
		c[1]=new TCanvas ("coinc_37RL","coinc_37RL");
		c[2]=new TCanvas ("pl_xh_hits","pl_xh_hits");
		c[3]=new TCanvas ("plTime1Time2_37L_17R","plTime1Time2_37L_17R");
		c[4]=new TCanvas ("AmplPd0","AmplPd0");
		c[5]=new TCanvas ("AmplPd1","AmplPd1");
		c[6]=new TCanvas ("AmplPd2","AmplPd2");
    char name3[200];
    char name3a[200];
    TText *t,*t1;
		TString st[16]={"37L4-R25","37L4-R26","37L4-R27","37L4-R28","37L4-R29","37L14-R15","37L14-R16","37L14-R17","37L14-R18","37L14-R19","37L24-R5","37L24-R6","37L24-R7","37L24-R8","37L24-R9"};
		TString stL[16]={"37R5-L20","37R5-L21","37R5-L22","37R5-L23","37R5-L24","37R15-L10","37R15-L11","37R15-L12","37R15-L13","37R15-L14","37R25-L0","37R25-L1","37R25-L2","37R25-L3","37R25-L4"};
    //TString stL[15]={"37L4-25R","37L4-26R","37L4-27R","37L4-28R","37L4-29R","37L14-15R","37L14-16R","37L14-17R","37L14-18R","37L14-19R","37L24-5R","37L24-6R","37L24-7R","37L24-8R","37L24-9R"};
    //TString stR[16]={"37R5-24L","37R5-23L","37R5-22L","37R5-21L","37R5-20L","37R15-14L","37R15-13L","37R15-12L","37R15-11L","37R15-10L","37R25-4L","37R25-3L","37R25-2L","37R25-1L","37R25-0L"};

    TFile *f = new TFile("output.root","recreate");
    f->cd();

    c[0]->cd();
    htBit->Write();
		htBit->Draw();
		sprintf(name,"%s/htBit.png",dir);
		c[0]->SaveAs(name);
    cor_kratta_plastic->Write();
    pl_xy->Write();
		pl_xy->Draw("colz");
		sprintf(name,"%s/pl_xy.png",dir);
		c[0]->SaveAs(name);

    hkr_id->Write();
    hpl_id->Write();
    hkrMult->Write();
		hkrMult->Draw();
		sprintf(name,"%s/hkrMult.png",dir);
		c[0]->SaveAs(name);
    hplMult->Write();
		hplMult->Draw();
		sprintf(name,"%s/hplMult.png",dir);
		c[0]->SaveAs(name);
    hplMultMod->Write();
    hfullModMult->Write();

		// c[0]->cd();
		// hkrPd0AmpAll->Write();
		// hkrPd0AmpAll->Draw("colz");
		// sprintf(name,"%s/Amp/hkrPd0AmpAll.png",dir);
		// c[0]->SaveAs(name);
		// hkrPd1AmpAll->Write();
		// hkrPd1AmpAll->Draw("colz");
		// sprintf(name,"%s/Amp/hkrPd1AmpAll.png",dir);
		// c[0]->SaveAs(name);
		// hkrPd2AmpAll->Write();
		// hkrPd2AmpAll->Draw("colz");
		// sprintf(name,"%s/Amp/hkrPd2AmpAll.png",dir);
		// c[0]->SaveAs(name);


    // coinc_all->Write();
		// coinc_all->Draw("colz");
		// sprintf(name,"%s/coinc_all.png",dir);
		// c[0]->SaveAs(name);

    coinc_37LR->Write();


    c[0]->cd();
    int k=0;
		for (int j=1; j<=3; j++) {
			coinc_37LR->GetYaxis()->SetBinLabel(j, level[j-1]);
			for (int i=1; i<=5; i++) {
				coinc_37LR->GetXaxis()->SetBinLabel(i, katyL[i-1]);
	}
}
	coinc_37LR->SetLabelSize(0.07,"X");
	coinc_37LR->SetLabelSize(0.06,"Y");
    coinc_37LR->Draw("colY+");

      for (int j=1; j<=3; j++) {
	for (int i=1; i<=5; i++) {
	k++;
auto	t = new TText(coinc_37LR->GetXaxis()->GetBinCenter(i), coinc_37LR->GetYaxis()->GetBinCenter(j),st[k-1]);
auto	t1 = new TText(coinc_37LR->GetXaxis()->GetBinCenter(i), coinc_37LR->GetYaxis()->GetBinCenter(j)-0.14,Form("%4.1f Hz",coinc_37LR->GetBinContent(i,j)));
auto	t2 = new TText(coinc_37LR->GetXaxis()->GetBinCenter(i), coinc_37LR->GetYaxis()->GetBinCenter(j)-0.28,Form("(%4.f)",coinc_37LR->GetBinContent(i,j)*AllTime));
	//cout<<coinc_37LR->GetYaxis()->GetBinCenter(j)<<endl;
	//TString s=st[k-1]+Form(":%4.1f",coinc_37LR->GetBinContent(i,j));
	//cout<<s<<endl;
	t->SetTextAlign(21);
	t1->SetTextAlign(21);
	t2->SetTextAlign(21);
	t->SetTextSize(0.028);
	t1->SetTextSize(0.028);
	t2->SetTextSize(0.028);
	t->Draw("same");
	t1->Draw("same");
	t2->Draw("same");

      }
   }


    c[0]->Write();
		sprintf(name,"%s/coinc_37LR.png",dir);
		c[0]->SaveAs(name);


		c[1]->cd();
		k=0;
		for (int j=1; j<=3; j++) {
			coinc_37RL->GetYaxis()->SetBinLabel(j, level[j-1]);
			for (int i=1; i<=5; i++) {
				coinc_37RL->GetXaxis()->SetBinLabel(i, katyR[i-1]);
	}
}
	coinc_37RL->SetLabelSize(0.07,"X");
	coinc_37RL->SetLabelSize(0.06,"Y");
		coinc_37RL->Draw("col");

			for (int j=1; j<=3; j++) {
	for (int i=1; i<=5; i++) {
	k++;
auto	t = new TText(coinc_37RL->GetXaxis()->GetBinCenter(i), coinc_37RL->GetYaxis()->GetBinCenter(j),stL[k-1]);
auto	t1 = new TText(coinc_37RL->GetXaxis()->GetBinCenter(i), coinc_37RL->GetYaxis()->GetBinCenter(j)-0.14,Form("%4.1f Hz",coinc_37RL->GetBinContent(i,j)));
auto	t2 = new TText(coinc_37RL->GetXaxis()->GetBinCenter(i), coinc_37RL->GetYaxis()->GetBinCenter(j)-0.28,Form("(%4.f)",coinc_37RL->GetBinContent(i,j)*AllTime));

	//cout<<coinc_37LR->GetYaxis()->GetBinCenter(j)<<endl;
	//TString s=st[k-1]+Form(":%4.1f",coinc_37LR->GetBinContent(i,j));
	//cout<<s<<endl;
	t->SetTextAlign(21);
	t1->SetTextAlign(21);
	t2->SetTextAlign(21);
	t->SetTextSize(0.028);
	t1->SetTextSize(0.028);
	t2->SetTextSize(0.028);
	t->Draw("same");
	t1->Draw("same");
	t2->Draw("same");

			}
	 }


		c[1]->Write();
		sprintf(name,"%s/coinc_37RL.png",dir);
		c[1]->SaveAs(name);

	 c[2]->cd();
	 pl_xy->Draw("colz");
	 c[2]->Write();


	 c[3]->cd();
	 hplTime1Time2_37L[17]->Draw("colz");
	 c[3]->Write();




   // for(int j=0; j< 130; j++){
	 //
   //    hplTime[j]->Write();
   //  }


   for(int j=0; j< 32; j++){

     // hkrattaTimePD0[j]->Write();
     // hkrattaTimePD1[j]->Write();
     // hkrattaTimePD2[j]->Write();
		 //
		 // hkrPd0Amp[j]->Write();
		 // hkrPd1Amp[j]->Write();
		 // hkrPd2Amp[j]->Write();
		 //
		 // hkrPd0Amp[j]->Draw("colz");
		 // sprintf(name,"%s/Amp/hkrPd0Amp_%dL.png",dir,j);
 		 // c[3]->SaveAs(name);
		 //
		 // hkrPd1Amp[j]->Draw("colz");
		 // sprintf(name,"%s/Amp/hkrPd1Amp_%dL.png",dir,j);
		 // c[3]->SaveAs(name);
		 //
		 // hkrPd2Amp[j]->Draw("colz");
		 // sprintf(name,"%s/Amp/hkrPd2Amp_%dL.png",dir,j);
		 // c[3]->SaveAs(name);

		/* c[3]->cd();
	  	hkrPd0Pd1Amp[j]->Write();
		 hkrPd0Pd1Amp[j]->Draw("colz");
		 sprintf(name,"%s/Amp/hkrPd0Pd1Amp%dL.png",dir,j);
		 c[3]->SaveAs(name);

		 c[3]->cd();
			hkrPd1Pd2Amp[j]->Write();
		 hkrPd1Pd2Amp[j]->Draw("colz");
		 sprintf(name,"%s/Amp/hkrPd1Pd2Amp%dL.png",dir,j);
		 c[3]->SaveAs(name);*/

	// 	 hplTime1Time2_37R[j]->Write();
	// 	 hplTime1Time2_37R[j]->Draw("colz");
	// 	 if(hplTime1Time2_37R[j]->GetEntries()>100){
	// 		sprintf(name,"%s/hplTime1Time2_37R_%dL.png",j);
	// 	 c[3]->SaveAs(name);
	//  }
	// 	 hplTime1Time2_37L[j]->Write();
	// 	 hplTime1Time2_37L[j]->Draw("colz");
	// 	 if(hplTime1Time2_37L[j]->GetEntries()>100){
	// 	 sprintf(name,"%s/hplTime1Time2_37L_%dR.png",j);
	// 	c[3]->SaveAs(name);
	// }

		/*for(int k=0;k<32;k++){
			if(hplTime1Time2_all[j][k]->GetEntries()>100){
			hplTime1Time2_all[j][k]->Draw("colz");
		hplTime1Time2_all[j][k]->Write();
			sprintf(name,"%s/AllTime/hplTime1Time2_all_%d_%d.png",dir,j,k);
		 c[3]->SaveAs(name);
	 			}
		 }*/

   }
 //   for(int j=0; j< 130; j++){
	// 	 for(int k=0;k<130;k++){
	// 		 if(hplpl_all[j][k]->GetEntries()>10){
	// 		 hplpl_all[j][k]->Draw("colz");
	// 		 sprintf(name,"%s/AllPl/hplpl_all_%d_%d.png",dir,j,k);
	// 		c[3]->SaveAs(name);
	// 	 }
	//  }
 // }



    f->Write();
    f->Close();



  fend = clock();
  double time_spent;
  time_spent = (double)(fend - fbegin) / CLOCKS_PER_SEC;
  printf("************** Analyze END, Time =%f s **************\n",time_spent);
  
	TFile *File = new TFile("Protons_Pd2Pd1.root", "RECREATE");
	TFile *File1 = new TFile("Protons_Pd1Pd0.root", "RECREATE");
	TCanvas *na_canvasy[30];
	TCanvas *na_canvasy1[30];
	char nazwa_canvas[30];
	char nazwa_canvas1[30];
	char nazwa_det[30];
	int ile_wejsc[30];
	int ile_wejsc1[30];
	memset(ile_wejsc, 0, sizeof(ile_wejsc));
	memset(ile_wejsc1, 0, sizeof(ile_wejsc1));
	TLatex *latex = new TLatex();
	latex->SetTextSize(0.08);
	TLatex *maxx = new TLatex();
	maxx->SetTextSize(0.08);
	TLatex *maxx1 = new TLatex();
	maxx1->SetTextSize(0.08);
	
	for(int det=0; det<30; det++)
	{
		sprintf(nazwa_canvas, "detector_%d_Pd2Pd1", det);
		sprintf(nazwa_canvas1, "detector_%d_Pd1Pd0", det);
		sprintf(nazwa_cut, "hkrPd0Pd1Amp_%d_cut", det);
		
		cout<<nazwa_canvas<<endl;
		if(Cuts->GetListOfKeys()->Contains(nazwa_cut))
		{
			na_canvasy[det] = new TCanvas(nazwa_canvas, nazwa_canvas, 3000, 1000);
			na_canvasy1[det] = new TCanvas(nazwa_canvas1, nazwa_canvas1, 3000, 1000);
			na_canvasy[det]->Divide(10, 3);
			na_canvasy1[det]->Divide(10, 3);
			
			for(int asd=0; asd<30; asd++)
			{
				ile_wejsc[asd]=wykresy[det][asd]->GetEntries();
				ile_wejsc1[asd]=wykresy_Pd1Pd0[det][asd]->GetEntries();
			}
			
			int boxPd2Pd1 = gdzie(ile_wejsc, largest(ile_wejsc));
			int boxPd1Pd0 = gdzie(ile_wejsc1, largest(ile_wejsc1));
			std::stringstream stream;
			stream << std::fixed << boxPd2Pd1;
			std::string s = stream.str();
			const char *c = s.c_str();
			
			
			
			/*TBox *box = new TBox(0,0,1,1);
			box->SetFillColor(1);
			na_canvasy[det]->cd(boxPd2Pd1);
			box->Draw("SAME");
			na_canvasy1[det]->cd(boxPd1Pd0);
			box->Draw("SAME");*/
			
			
			/*wykresy[det][boxPd2Pd1]->SetTitleSize(2);
			na_canvasy[det]->cd(boxPd2Pd1);
			wykresy[det][boxPd2Pd1]->DrawCopy("colz");
			wykresy_Pd1Pd0[det][boxPd1Pd0]->DrawCopy("colz");
			wykresy_Pd1Pd0[det][boxPd1Pd0]->SetTitleSize(2);
			na_canvasy1[det]->cd(boxPd1Pd0);
			wykresy_Pd1Pd0[det][boxPd1Pd0]->DrawCopy("colz");*/
			
			
			for(int z=0; z<30; z++)
			{
			na_canvasy[det]->cd(z+1);
			gPad->SetLogz(0);
			sprintf(nazwa_det, "detector %d", z);
			sprintf(nazwa_cut, "hkrPd0Pd1Amp_%d_cut", z);
				if(det!=z)
				{
				wykresy[det][z]->SetTitle(nazwa_det);
				wykresy[det][z]->DrawCopy("colz");
				cout<<wykresy[det][z]->GetTitle()<<"	"<<wykresy[det][z]->GetEntries()<<endl;
				}
				else
				{
					latex->DrawLatex(0.1, 0.7, "maximum in detector");
					maxx->DrawLatex(0.5, 0.6, c);
				}
				
			na_canvasy1[det]->cd(z+1);
			gPad->SetLogz(0);
			
			s="";
			c="";
			stream.str("");
			
			stream << std::fixed << boxPd1Pd0;
			string s = stream.str();
			c = s.c_str();
			
			sprintf(nazwa_cut, "hkrPd0Pd1Amp_%d_cut", z);
				if(det!=z)
				{
				wykresy_Pd1Pd0[det][z]->SetTitle(nazwa_det);
				wykresy_Pd1Pd0[det][z]->DrawCopy("colz");
				//cout<<wykresy[det][z]->GetTitle()<<"	"<<wykresy[det][z]->GetEntries()<<endl;
				}
				else
				{
					latex->DrawLatex(0.1, 0.7, "maximum in detector");
					maxx1->DrawLatex(0.5, 0.6, c);
				}
			}
			
			for(int counter=0; counter<30; counter++)
			{
				cout<<ile_wejsc[counter]<<"  ";
			}
			cout<<endl;
		//	cout<<boxPd2Pd1<<endl;
			
			
			
			memset(ile_wejsc, 0, sizeof(ile_wejsc));
			memset(ile_wejsc1, 0, sizeof(ile_wejsc1));
			s="";
			c="";
			stream.str("");
			
			
			File->cd();
			na_canvasy[det]->Write();
			File1->cd();
			na_canvasy1[det]->Write();
		}
		
	}
  
}
