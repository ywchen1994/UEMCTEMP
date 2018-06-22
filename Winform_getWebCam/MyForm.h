#pragma once
#define _USE_MATH_DEFINES
#include"math.h"
#include"../DeviceEnum/DeviceEnumerator.h"
#include"cv.h"
#include"highgui.h"
#include<fstream>
#include <time.h>
#include"Pt.h"
#include <algorithm>
typedef unsigned int uint;
namespace Winform_getWebCam {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace cv;
	using namespace std;
	RNG rng(12345);
	bool f_SS = false;
	VideoCapture cap;

	std::map<int, Device> devices;
	double CarSpeed;
	vector<Pt>Pt_oldClusterRefPoint;
	fstream fp;
	time_t t1;
	uint tt2 = 0;
	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
			timer1->Interval = 100;
			fp.open("AllSensor291033.txt", ios::in);
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}


	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label1;

	private: System::ComponentModel::IContainer^  components;
	protected:


	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// chart1
			// 
			chartArea1->AxisX->Interval = 100;
			chartArea1->AxisX->Maximum = 1300;
			chartArea1->AxisX->Minimum = -1300;
			chartArea1->AxisY->Interval = 100;
			chartArea1->AxisY->Maximum = 8000;
			chartArea1->AxisY->Minimum = 0;
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(2, 1);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series1->Color = System::Drawing::Color::Khaki;
			series1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			series1->LabelForeColor = System::Drawing::Color::YellowGreen;
			series1->Legend = L"Legend1";
			series1->Name = L"Series_LiDAR";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series2->Color = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			series2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			series2->Legend = L"Legend1";
			series2->MarkerColor = System::Drawing::Color::Blue;
			series2->MarkerSize = 10;
			series2->Name = L"Series_LiDAR_CLOSE";
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastPoint;
			series3->Color = System::Drawing::Color::ForestGreen;
			series3->Legend = L"Legend1";
			series3->MarkerSize = 10;
			series3->Name = L"Series_Radar_Angle";
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series4->Legend = L"Legend1";
			series4->MarkerColor = System::Drawing::SystemColors::MenuHighlight;
			series4->MarkerSize = 10;
			series4->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Star4;
			series4->Name = L"Series_TBox_LRadar";
			series5->ChartArea = L"ChartArea1";
			series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series5->Color = System::Drawing::Color::Black;
			series5->Legend = L"Legend1";
			series5->MarkerSize = 10;
			series5->Name = L"Series_TBox_RRadar";
			this->chart1->Series->Add(series1);
			this->chart1->Series->Add(series2);
			this->chart1->Series->Add(series3);
			this->chart1->Series->Add(series4);
			this->chart1->Series->Add(series5);
			this->chart1->Size = System::Drawing::Size(1271, 692);
			this->chart1->TabIndex = 9;
			this->chart1->Text = L"圖";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(1053, 158);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 10;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(1053, 200);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 11;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(1082, 288);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(33, 12);
			this->label1->TabIndex = 12;
			this->label1->Text = L"label1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1331, 686);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->chart1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		if (!f_SS)
		{

			timer1->Enabled = true;
			timer1->Start();
		}
		else
		{
			timer1->Enabled = false;
		}
		f_SS = !f_SS;
	}
	private:Pt LeastSquare(const vector<Pt>& P)
	{
		Pt AB;//y=Ax+B
		double t1 = 0, t2 = 0, t3 = 0, t4 = 0;
		for (int i = 0; i < P.size(); ++i)
		{
			t1 += P[i].x * P[i].x;
			t2 += P[i].x;
			t3 += P[i].x * P[i].y;
			t4 += P[i].y;
		}
		AB.x = (t3*P.size() - t2*t4) / (t1*P.size() - t2*t2);
		AB.y = (t1*t4 - t2*t3) / (t1*P.size() - t2*t2);
		return AB;
	}


	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		chart1->Series["Series_LiDAR"]->Points->Clear();
		chart1->Series["Series_LiDAR_CLOSE"]->Points->Clear();
		vector<Pt> LiDARPt;
		char line[10000];

		fp.getline(line, sizeof(line), '\n');
		System::String^ str = gcnew System::String(line);
		cli::array<System::String^> ^StringArray = str->Split(' ');

		if (StringArray->Length == 723)
		{
			tt2++;
			for (uint i = 0; i < 722; i++)
			{

				if (i % 2 == 1)
				{ 
					double Xreader = System::Convert::ToDouble(StringArray[i - 1]);
					double Yreader = System::Convert::ToDouble(StringArray[i]);
					if(-1300<Xreader && Xreader<1300 && Yreader<7000)
					LiDARPt.push_back(Pt(Xreader, Yreader));
				}
					
			}
			CarSpeed = System::Convert::ToDouble(StringArray[722]);
			label1->Text = CarSpeed.ToString();

			vector<Pt>Pt_newClusterRefPt;
			vector<int >lab;
			int nObj = partition(LiDARPt, lab);
			vector<vector<Pt>> Pt_ClusterList = Cluster2List(LiDARPt, lab, nObj, 5);
			Pt_newClusterRefPt.resize(Pt_ClusterList.size());
			//vector<Pt>Pt_newCluster = CaculateMediumPoint(LiDARPt, lab, nObj, 10);

			int index = 0;
			for (uint16_t i = 0; i < Pt_ClusterList.size(); i++)
			{
				double  minX = 8000;
				double minY = 8000;
				Pt min;
				Color color = Color::FromArgb(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
				for (uint j = 0; j < Pt_ClusterList[i].size(); j++)
				{
					if (abs(Pt_ClusterList[i][j].x) < minX)
					{
						min.x = Pt_ClusterList[i][j].x;
						minX = abs(Pt_ClusterList[i][j].x);
					}
					if (abs(Pt_ClusterList[i][j].y) < minY)
					{
						minY = abs(Pt_ClusterList[i][j].y);
						min.y = Pt_ClusterList[i][j].y;
					}
					chart1->Series["Series_LiDAR"]->Points->AddXY(Pt_ClusterList[i][j].x, Pt_ClusterList[i][j].y);
					chart1->Series["Series_LiDAR"]->Points[index]->Color = color;
					index++;
				}
				Pt_newClusterRefPt[i] = min;

			}
			if (Pt_oldClusterRefPoint.size() == 0)Pt_oldClusterRefPoint.resize(Pt_newClusterRefPt.size());

			/*time_t t2 = clock();
			float time = (float)(t2 - t1) / CLK_TCK;*/
			double time = (double)(tt2)*0.04;
			tt2 = 0;
			FindClosePoint(Pt_newClusterRefPt, Pt_oldClusterRefPoint, time);
			for (uint i = 0; i < Pt_newClusterRefPt.size(); i++)
			{
				chart1->Series[1]->Points->AddXY(Pt_newClusterRefPt[i].x, Pt_newClusterRefPt[i].y);
				chart1->Series[1]->Points[i]->Label = "(" + Math::Round(Pt_newClusterRefPt[i].x, 2).ToString() + " , " + Math::Round(Pt_newClusterRefPt[i].y, 2).ToString() + " , " + Math::Round(Pt_newClusterRefPt[i].velcity/100*3.6, 2).ToString() + ")";
			}
			chart1->Refresh();
			Pt_oldClusterRefPoint = Pt_newClusterRefPt;
		}
		if (StringArray->Length == 1)
		{
			tt2++;
		}
	}


	private:void FindMaxWeight(vector<vector<Pt>> newCluster, vector<vector<Pt>> oldCluster, double timeinv)
	{
		for (uint i = 0; i < newCluster.size(); i++)
		{
			for (uint j = 0; j < oldCluster.size(); j++)
			{
			}
		}
	}
	private:vector<vector<Pt>>Cluster2List(vector<Pt>&XYcord, vector<int> &PointLab, int NoObj, int minPoint)
	{
		vector<vector<Pt> >ListTemp;
		ListTemp.resize(NoObj);
		for (uint i = 0; i < XYcord.size(); i++)
		{
			ListTemp[PointLab[i]].push_back(XYcord[i]);
		}
		for (uint i = 0; i < ListTemp.size(); i++)
		{
			if (ListTemp[i].size() < minPoint)
			{
				ListTemp.erase(ListTemp.begin() + i);
				i--;
			}
		}

		return 	ListTemp;

	}
	private:vector<Pt>CaculateMediumPoint(vector<Pt>&XYcord, vector<int> &PointLab, int NoObj, int minPointN)
	{
		vector<vector<Pt> >MediumPoint;
		vector<Pt>res_MediumPoint;
		MediumPoint.resize(NoObj);
		for (uint i = 0; i < XYcord.size(); i++)
		{
			MediumPoint[PointLab[i]].push_back(XYcord[i]);
		}
		for (uint i = 0; i < NoObj; i++)
		{
			double temp = 0;
			for (uint k = 0; k < MediumPoint[i].size(); k++) {
				for (uint j = k; j < MediumPoint[i].size(); j++) {
					if (MediumPoint[i][j].x < MediumPoint[i][k].x)
					{
						temp = MediumPoint[i][j].x;
						MediumPoint[i][j].x = MediumPoint[i][k].x;
						MediumPoint[i][k].x = temp;
					}
					if (MediumPoint[i][j].y < MediumPoint[i][k].y)
					{
						temp = MediumPoint[i][j].y;
						MediumPoint[i][j].y = MediumPoint[i][k].y;
						MediumPoint[i][k].y = temp;
					}
				}
			}
			if (MediumPoint[i].size() > minPointN)
			{
				if (MediumPoint[i].size() % 2 != 0)
				{
					res_MediumPoint.push_back(MediumPoint[i][MediumPoint[i].size() / 2]);

				}
				else
				{
					Pt mean;
					mean.x = (MediumPoint[i][MediumPoint[i].size() / 2].x + MediumPoint[i][MediumPoint[i].size() / 2 - 1].x) / 2;
					mean.y = (MediumPoint[i][MediumPoint[i].size() / 2].y + MediumPoint[i][MediumPoint[i].size() / 2 - 1].y) / 2;
					res_MediumPoint.push_back(mean);

				}
			}
		}


		return res_MediumPoint;
	}
	private:vector<Pt> CaculateAveragePoint(vector<Pt>&XYcord, vector<int> &PointLab, int NoObj, int minPointN)
	{
		vector<Pt>averagePoint;
		vector<int>ClusterPointNum;
		vector<Pt> sumPoint;
		ClusterPointNum.resize(NoObj);
		sumPoint.resize(NoObj);
		for (uint i = 0; i < XYcord.size(); i++)
		{
			ClusterPointNum[PointLab[i]]++;
			sumPoint[PointLab[i]].x += XYcord[i].x;
			sumPoint[PointLab[i]].y += XYcord[i].y;
		}
		for (uint i = 0; i < NoObj; i++)
		{
			sumPoint[i].x /= ClusterPointNum[i];
			sumPoint[i].y /= ClusterPointNum[i];
			if (ClusterPointNum[i] > minPointN)
			{
				averagePoint.push_back(sumPoint[i]);
			}
		}

		return averagePoint;
	}
	private:bool predicate(Pt P1, Pt P2)
	{
		double distant = Math::Sqrt(Math::Pow((P1.x - P2.x), 2) + Math::Pow((P1.y - P2.y), 2));
		return  distant <= 200;
	}
	private:int partition(cv::vector<Pt>& _vec, cv::vector<int>& labels)
	{
		int i, j, N = _vec.size();
		const Pt* vec = &_vec[0];

		const int PARENT = 0;
		const int RANK = 1;

		cv::vector<int> _nodes(N * 2);
		int(*nodes)[2] = (int(*)[2])&_nodes[0];

		for (i = 0; i < N; i++)
		{
			nodes[i][PARENT] = -1;
			nodes[i][RANK] = 0;
		}
		for (i = 0; i < N; i++)
		{
			int root = i;

			// find root
			while (nodes[root][PARENT] >= 0)
				root = nodes[root][PARENT];

			for (j = 0; j < N; j++)
			{
				if (i == j || !predicate(vec[i], vec[j]))
					continue;
				int root2 = j;

				while (nodes[root2][PARENT] >= 0)
					root2 = nodes[root2][PARENT];

				if (root2 != root)
				{
					// unite both trees
					int rank = nodes[root][RANK], rank2 = nodes[root2][RANK];
					if (rank > rank2)
						nodes[root2][PARENT] = root;
					else
					{
						nodes[root][PARENT] = root2;
						nodes[root2][RANK] += rank == rank2;
						root = root2;
					}
					//assert(nodes[root][PARENT] < 0);

					int k = j, parent;

					// compress the path from node2 to root
					while ((parent = nodes[k][PARENT]) >= 0)
					{
						nodes[k][PARENT] = root;
						k = parent;
					}

					// compress the path from node to root
					k = i;
					while ((parent = nodes[k][PARENT]) >= 0)
					{
						nodes[k][PARENT] = root;
						k = parent;
					}
				}
			}
		}
		for (unsigned int i = 0; i < N; i++)
			labels.push_back(0);
		int nclasses = 0;

		for (i = 0; i < N; i++)
		{
			int root = i;
			while (nodes[root][PARENT] >= 0)
				root = nodes[root][PARENT];
			if (nodes[root][RANK] >= 0)
				nodes[root][RANK] = ~nclasses++;
			labels[i] = ~nodes[root][RANK];
		}
		return nclasses;
	}
	private:void FindClosePoint(vector<Pt>&NewPoints, vector<Pt>&oldPoints, double timeInterval)
	{
		double Ylim = 90.0f*(1000.0f / 36.0f)*timeInterval;
		double Xlim =100* timeInterval;
		for (uint16_t i = 0; i < NewPoints.size(); i++)
		{
			double minDistant = 8000;
			double distant;
		
			uint oldPointIndex = 0;
			for (uint16_t j = 0; j < oldPoints.size(); j++)
			{
				distant = sqrt(pow((NewPoints[i].x - oldPoints[j].x), 2) + pow((NewPoints[i].y - oldPoints[j].y), 2));
				if ((distant < minDistant))
				{
					oldPointIndex = j;
					minDistant = distant;
				}
			}
			if (abs(NewPoints[i].x - oldPoints[oldPointIndex].x) < Xlim &&   abs(NewPoints[i].y - oldPoints[oldPointIndex].y) <Ylim)
			{
				NewPoints[i].velcity = minDistant / timeInterval;
				if (NewPoints[i].y - oldPoints[oldPointIndex].y > 0)
					NewPoints[i].velcity = -NewPoints[i].velcity;

			}
			else
			{
				NewPoints[i].velcity = 0;
			}
			
		}

	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		vector<Pt> po;
		po.push_back(Pt(1100, 24));
		po.push_back(Pt(11, 23));
		po.push_back(Pt(10, 20));
		po.push_back(Pt(11, 24));
		po.push_back(Pt(11, 22));
		po.push_back(Pt(1101, 24));

		po.push_back(Pt(1102, 24));
		vector<int >lab;
		int nObj = partition(po, lab);
		vector<Pt>Pt_newCluster = CaculateMediumPoint(po, lab, nObj, 1);
		int a = 99;
	}
	};
}
