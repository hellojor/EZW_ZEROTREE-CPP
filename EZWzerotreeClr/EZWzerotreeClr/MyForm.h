#pragma once
#define _USE_MATH_DEFINES 
#include <cmath>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <fstream>

#include "ZeroTree.h"
#include "CStatus.h"

using std::cout;
using std::endl;
using std::vector;
using std::queue;
using std::string;
using std::setw;

namespace EZWzerotreeClr {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
	using namespace System::Drawing::Design;

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

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container^ components;
	private: System::Windows::Forms::Button^ OpenFile_btn;
	private: System::Windows::Forms::Button^ DWT_btn;

	private: System::Windows::Forms::Button^ IDWT_btn;


	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox3;


	private:
		//定義影像類別(點陣圖(.bmp)，無壓縮，資訊較多)
		Bitmap^ ori_image, ^ comp_image;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->OpenFile_btn = (gcnew System::Windows::Forms::Button());
			this->DWT_btn = (gcnew System::Windows::Forms::Button());
			this->IDWT_btn = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			// 
			// OpenFile_btn
			// 
			this->OpenFile_btn->Location = System::Drawing::Point(28, 29);
			this->OpenFile_btn->Name = L"OpenFile_btn";
			this->OpenFile_btn->Size = System::Drawing::Size(75, 23);
			this->OpenFile_btn->TabIndex = 0;
			this->OpenFile_btn->Text = L"open";
			this->OpenFile_btn->UseVisualStyleBackColor = true;
			this->OpenFile_btn->Click += gcnew System::EventHandler(this, &MyForm::OpenFile_btn_Click);
			// 
			// DWT_btn
			// 
			this->DWT_btn->Location = System::Drawing::Point(571, 29);
			this->DWT_btn->Name = L"DWT_btn";
			this->DWT_btn->Size = System::Drawing::Size(103, 23);
			this->DWT_btn->TabIndex = 1;
			this->DWT_btn->Text = L"DWT";
			this->DWT_btn->UseVisualStyleBackColor = true;
			this->DWT_btn->Click += gcnew System::EventHandler(this, &MyForm::DWT_btn_Click);
			// 
			// IDWT_btn
			// 
			this->IDWT_btn->Location = System::Drawing::Point(1121, 29);
			this->IDWT_btn->Name = L"IDWT_btn";
			this->IDWT_btn->Size = System::Drawing::Size(103, 23);
			this->IDWT_btn->TabIndex = 2;
			this->IDWT_btn->Text = L"IDWT";
			this->IDWT_btn->UseVisualStyleBackColor = true;
			this->IDWT_btn->Click += gcnew System::EventHandler(this, &MyForm::IDWT_btn_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(28, 69);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(512, 512);
			this->pictureBox1->TabIndex = 3;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(571, 69);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(512, 512);
			this->pictureBox2->TabIndex = 4;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Location = System::Drawing::Point(1121, 69);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(512, 512);
			this->pictureBox3->TabIndex = 5;
			this->pictureBox3->TabStop = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1675, 671);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->IDWT_btn);
			this->Controls->Add(this->DWT_btn);
			this->Controls->Add(this->OpenFile_btn);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void OpenFile_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->FileName = "";
		ofd->Filter = "All Files(*.*)|*.*";
		ofd->FilterIndex = 1;
		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK && ofd->FileName != "") {
			// read lena img
			Bitmap^ buff = gcnew Bitmap(ofd->FileName);

			ori_image = gcnew Bitmap(buff->Width, buff->Height, buff->PixelFormat);

			// Lock Memory
			BitmapData^ bd_ori = ori_image->LockBits(Rectangle(0, 0, ori_image->Width, ori_image->Height), ImageLockMode::ReadWrite, ori_image->PixelFormat);
			BitmapData^ bd_buff = buff->LockBits(Rectangle(0, 0, buff->Width, buff->Height), ImageLockMode::ReadWrite, buff->PixelFormat);

			int ori_byteskip = bd_ori->Stride - bd_ori->Width * 3;
			int buff_byteskip = bd_buff->Stride - bd_buff->Width * 3;

			Byte* ori_ptr = (Byte*)((void*)bd_ori->Scan0);
			Byte* buff_ptr = (Byte*)((void*)bd_buff->Scan0);

			// rgb to gray
			for (int y = 0; y < bd_ori->Height; y++) {
				for (int x = 0; x < bd_ori->Width; x++) {
					int B = (int)buff_ptr[0];
					int G = (int)buff_ptr[1];
					int R = (int)buff_ptr[2];

					int gray = (R + G + B) / 3;

					ori_ptr[0] = gray;
					ori_ptr[1] = gray;
					ori_ptr[2] = gray;

					ori_ptr += 3;
					buff_ptr += 3;
				}

				ori_ptr += ori_byteskip;
				buff_ptr += buff_byteskip;
			}


			// Unlock Memory
			ori_image->UnlockBits(bd_ori);
			buff->UnlockBits(bd_buff);
			pictureBox1->Image = ori_image;
		}
	}

	private: System::Void DWT_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (ori_image == nullptr) {
			return;
		}
		comp_image = gcnew Bitmap(ori_image->Width, ori_image->Height, ori_image->PixelFormat);
		// Lock Memory
		BitmapData^ bd_ori = ori_image->LockBits(Rectangle(0, 0, ori_image->Width, ori_image->Height), ImageLockMode::ReadWrite, ori_image->PixelFormat);
		BitmapData^ bd_comp = comp_image->LockBits(Rectangle(0, 0, comp_image->Width, comp_image->Height), ImageLockMode::ReadWrite, comp_image->PixelFormat);

		int ori_byteskip = bd_ori->Stride - bd_ori->Width * 3;
		int comp_byteskip = bd_comp->Stride - bd_comp->Width * 3;

		Byte* ori_ptr = (Byte*)((void*)bd_ori->Scan0);
		Byte* comp_ptr = (Byte*)((void*)bd_comp->Scan0);

		int freq = 3; // the freq of compression

		int** img = new int* [ori_image->Height];
		int** buff = new int* [ori_image->Height];
		for (int i = 0; i < ori_image->Height; i++) {
			img[i] = new int[ori_image->Width];
			buff[i] = new int[ori_image->Width];
		}

		for (int y = 0; y < bd_ori->Height; y++) {
			for (int x = 0; x < bd_ori->Width; x++) {
				img[y][x] = (int)ori_ptr[0];
				ori_ptr += 3;
			}
			ori_ptr += ori_byteskip;
		}


		for (int n = 1; n <= freq; n++) {
			int height = (int)bd_ori->Height / n;
			int width = (int)bd_ori->Width / n;

			// row
			for (int scany = 0; scany < height; scany++) {
				for (int scanx = 0; scanx < width; scanx += 2) {
					int gray1 = img[scany][scanx];
					int gray2 = img[scany][scanx + 1];

					buff[scany][(int)(scanx / 2)] = round((float)(gray1 + gray2) / 2);
					buff[scany][(int)(scanx / 2) + (int)(width / 2)] = round((float)(gray1 - gray2) / 2);
				}
			}

			// column
			for (int scany = 0; scany < height; scany += 2) {
				for (int scanx = 0; scanx < width; scanx++) {
					int gray1 = buff[scany][scanx];
					int gray2 = buff[scany + 1][scanx];

					int avg = round((float)(gray1 + gray2) / 2);

					img[(int)(scany / 2)][scanx] = round((float)(gray1 + gray2) / 2);
					img[(int)(scany / 2) + (int)(height / 2)][scanx] = round((float)(gray1 - gray2) / 2);
				}
			}
		}

		for (int y = 0; y < bd_comp->Height; y++) {
			for (int x = 0; x < bd_comp->Width; x++) {

				int gray = img[y][x];

				//if (gray < 0) gray = 0;
				//if (gray > 255) gray = 255;

				comp_ptr[0] = gray;
				comp_ptr[1] = gray;
				comp_ptr[2] = gray;

				comp_ptr += 3;
			}
			comp_ptr += comp_byteskip;
		}

		int maxVal = 0;
		string S1 = "", Z1 = "";
		string S2 = "", D2 = "", Z2 = "";

		EZW_encode(img, bd_ori->Height, bd_ori->Width, maxVal, S1, Z1, S2, D2, Z2);

		cout << "maxval:" << maxVal << endl;
		cout << "S1:" << S1 << endl;
		cout << "Z1:" << Z1 << endl;
		cout << "S2:" << S2 << endl;
		cout << "D2:" << D2 << endl;
		cout << "Z2:" << Z2 << endl;
		cout << "============================" << endl;

		std::ofstream fout("data.txt");
		fout << maxVal << endl;
		fout << S1 << endl;
		fout << Z1 << endl;
		fout << S2 << endl;
		fout << D2 << endl;
		fout << Z2 << endl;
		fout.close();

		// free memory
		for (int i = 0; i < ori_image->Height; i++) {
			delete img[i];
			delete buff[i];
		}

		// Unlock Memory
		ori_image->UnlockBits(bd_ori);
		comp_image->UnlockBits(bd_comp);
		pictureBox2->Image = comp_image;
	}

	private: System::Void IDWT_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (comp_image == nullptr) {
			return;
		}

		Bitmap^ output = gcnew Bitmap(comp_image->Width, comp_image->Height, comp_image->PixelFormat);
		// Lock Memory
		BitmapData^ bd_comp = comp_image->LockBits(Rectangle(0, 0, comp_image->Width, comp_image->Height), ImageLockMode::ReadWrite, comp_image->PixelFormat);
		BitmapData^ bd_output = output->LockBits(Rectangle(0, 0, output->Width, output->Height), ImageLockMode::ReadWrite, output->PixelFormat);

		int comp_byteskip = bd_comp->Stride - bd_comp->Width * 3;
		int output_byteskip = bd_output->Stride - bd_output->Width * 3;

		Byte* comp_ptr = (Byte*)((void*)bd_comp->Scan0);
		Byte* output_ptr = (Byte*)((void*)bd_output->Scan0);

		int freq = 3; // the freq of compression

		int** img = new int* [ori_image->Height];
		int** buff = new int* [ori_image->Height];
		for (int i = 0; i < ori_image->Height; i++) {
			img[i] = new int[ori_image->Width];
			buff[i] = new int[ori_image->Width];
		}

		int maxVal = 0;
		string S1 = "", Z1 = "";
		string S2 = "", D2 = "", Z2 = "";

		std::ifstream fin("data.txt");
		string s;
		std::getline(fin, s);
		maxVal = stoi(s);
		std::getline(fin, S1);
		std::getline(fin, Z1);
		std::getline(fin, S2);
		std::getline(fin, D2);
		std::getline(fin, Z2);
		cout << "maxval:" << maxVal << endl;
		cout << "S1:" << S1 << endl;
		cout << "Z1:" << Z1 << endl;
		cout << "S2:" << S2 << endl;
		cout << "D2:" << D2 << endl;
		cout << "Z2:" << Z2 << endl;
		fin.close();

		EZW_decode(img, ori_image->Height, ori_image->Width, maxVal, S1, Z1, S2, D2, Z2);


		for (int n = freq; n >= 1; n--) {
			int height = (int)bd_comp->Height / n;
			int width = (int)bd_comp->Width / n;

			// column
			for (int scany = 0; scany < height; scany += 2) {
				for (int scanx = 0; scanx < width; scanx++) {
					int gray1 = img[(int)(scany / 2)][scanx];
					int gray2 = img[(int)(scany / 2) + (int)(height / 2)][scanx];

					buff[scany][scanx] = gray1 + gray2;
					buff[scany + 1][scanx] = gray1 - gray2;
				}
			}

			// row
			for (int scany = 0; scany < height; scany++) {
				for (int scanx = 0; scanx < width; scanx += 2) {
					int gray1 = buff[scany][(int)(scanx / 2)];
					int gray2 = buff[scany][(int)(scanx / 2) + (int)(width / 2)];

					img[scany][scanx] = gray1 + gray2;
					img[scany][scanx + 1] = gray1 - gray2;
				}
			}
		}

		for (int y = 0; y < bd_output->Height; y++) {
			for (int x = 0; x < bd_output->Width; x++) {

				int gray = img[y][x];

				//if (gray < 0) gray = 0;
				//if (gray > 255) gray = 255;

				output_ptr[0] = gray;
				output_ptr[1] = gray;
				output_ptr[2] = gray;

				output_ptr += 3;
			}
			output_ptr += output_byteskip;
		}

		// free memory
		for (int i = 0; i < ori_image->Height; i++) {
			delete img[i];
			delete buff[i];
		}

		// Unlock Memory
		comp_image->UnlockBits(bd_comp);
		output->UnlockBits(bd_output);
		pictureBox3->Image = output;
	}

	private: float ceil_float2(float f) {
		if ((float)(round)(f * 10) / 10 == -0) return 0; // avoid "-0"
		else return (float)(round)(f * 10) / 10;
	}

	private: void DWT(float** img, int org_ratio, int ratio) {

		float** buff = new float* [org_ratio];
		for (int i = 0; i < org_ratio; i++) {
			buff[i] = new float[org_ratio];
		}

		int height = ratio;
		int width = ratio;

		// copy 
		for (int scany = 0; scany < height; scany++) {
			for (int scanx = 0; scanx < width; scanx++) {
				buff[scany][scanx] = img[scany][scanx];
			}
		}

		// row
		for (int scany = 0; scany < height; scany++) {
			for (int scanx = 0; scanx < width; scanx += 2) {
				float gray1 = ceil_float2((float)img[scany][scanx]);
				float gray2 = ceil_float2((float)img[scany][scanx + 1]);

				float avg = ceil_float2(((float)gray1 + (float)gray2) / 2);

				buff[scany][(int)(scanx / 2)] = ceil_float2((float)avg);
				buff[scany][(int)(scanx / 2) + (int)(width / 2)] = ceil_float2((float)avg - (float)gray2);
			}
		}

		// col
		for (int scany = 0; scany < height; scany += 2) {
			for (int scanx = 0; scanx < width; scanx++) {
				float gray1 = ceil_float2((float)buff[scany][scanx]);
				float gray2 = ceil_float2((float)buff[scany + 1][scanx]);

				float avg = ceil_float2(((float)gray1 + (float)gray2) / 2);

				img[(int)(scany / 2)][scanx] = ceil_float2((float)avg);
				img[(int)(scany / 2) + (int)(height / 2)][scanx] = ceil_float2((float)avg - (float)gray2);
			}
		}

		for (int i = 0; i < org_ratio; i++) {
			delete buff[i];
		}

	}

	private: void IDWT(float** img, int org_ratio, int ratio) {

		float** buff = new float* [org_ratio];
		for (int i = 0; i < org_ratio; i++) {
			buff[i] = new float[org_ratio];
		}

		int height = ratio;
		int width = ratio;

		// copy 
		for (int scany = 0; scany < height; scany++) {
			for (int scanx = 0; scanx < width; scanx++) {
				buff[scany][scanx] = img[scany][scanx];
			}
		}

		// col
		for (int scany = 0; scany < height; scany += 2) {
			for (int scanx = 0; scanx < width; scanx++) {
				float gray1 = (float)img[(int)(scany / 2)][scanx];
				float gray2 = (float)img[(int)(scany / 2) + (int)(height / 2)][scanx]; // avg

				buff[scany][scanx] = ceil_float2((float)gray1 + (float)gray2);
				buff[scany + 1][scanx] = ceil_float2((float)gray1 - (float)gray2);
			}
		}

		// row
		for (int scany = 0; scany < height; scany++) {
			for (int scanx = 0; scanx < width; scanx += 2) {
				float gray1 = (float)buff[scany][(int)(scanx / 2)];
				float gray2 = (float)buff[scany][(int)(scanx / 2) + (int)(width / 2)];

				img[scany][scanx] = ceil_float2((float)gray1 + (float)gray2);
				img[scany][scanx + 1] = ceil_float2((float)gray1 - (float)gray2);
			}
		}

		for (int i = 0; i < org_ratio; i++) {
			delete buff[i];
		}
	}

	private: int check_beside(int* FORM1, int FORM_count, int val) {
		for (int i = 1; i < FORM_count; i += 2) {
			if (val >= FORM1[i - 1] && val <= FORM1[i + 1]) {
				return FORM1[i];
			}
		}
	}
	
	private: int find_index(int* arr, int len, int num) {
		for (int i = 0; i < len; i++) {
			if (arr[i] == num) return i;
		}
		return -1;
	}

	private: const queue<string> split(const string str, const char delimiter) {
		queue<string> result;
		std::stringstream ss(str);
		std::string tok;

		while (std::getline(ss, tok, delimiter)) {
			result.push(tok);
		}
		return result;
	}

	private: void EZW_encode(int** img, int height, int width, int& maxVal, string& S1, string& Z1, string& S2, string& D2, string& Z2) {
		// ==> initial <==
		// init the status table
		CSTATUS** status = new CSTATUS * [height];	// record the CSTATUS of img
		for (int i = 0; i < height; i++) {
			status[i] = new CSTATUS[width];
			for (int j = 0; j < width; j++) {
				status[i][j] = CSTATUS::NONE;
			}
		}

		// build the zero-tree for record the coordinate of the img table
		tree_pointer root = new tnode(0, 0);
		root->child_2 = new tnode(0, 1);
		root->child_3 = new tnode(1, 0);
		root->child_4 = new tnode(1, 1);

		derivative(root->child_2, height / 2);
		derivative(root->child_3, height / 2);
		derivative(root->child_4, height / 2);
		//print_tree(root, img);

		// STEP 1: Convert IMG from Time Domain to Freq Domain

		// ==> START EZW encode <==

		// ==> First time <==

		// STEP 2: setting thershold T0
		// T0 = 2 ^ M
		// M = floor(log2(max(wij)))
		int T0, R0;
		int M;

		//maxVal = findmax(img, height, width);
		maxVal = img[0][0]; // always at the left up most of the img
		M = floor(log2(double(maxVal)));
		T0 = pow(2, M);

		// STEP 3: setting Rebuild Value R0
		// R0 = (max(wij) + T0) / 2
		R0 = (maxVal + T0) / 2;

		// STEP 4: scan with Z-shape and find out all the status of zero-tree
		check_all(root, img, status, T0, S1);

		/*for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cout << setw(3) << GET_CSTATUS_NAME(status[i][j]) << "\t";
			}
			cout << endl;
		}*/

		// STEP 5: Refining the Rebuild Value table and find out Z1
		// i.e. [32, 46, 60] -> [32, 39, 46, 53, 60]

		int* RVtable1, * buff;
		int RVtable1_count = 3;

		RVtable1 = new int[RVtable1_count];
		RVtable1[0] = T0;
		RVtable1[1] = R0;
		RVtable1[2] = maxVal;

		buff = new int[RVtable1_count];
		for (int i = 0; i < RVtable1_count; i++) {
			buff[i] = RVtable1[i];
		}
		delete[]RVtable1;
		RVtable1_count = RVtable1_count * 2 - 1;
		RVtable1 = new int[RVtable1_count];
		for (int i = 0; i < RVtable1_count; i += 2) {
			RVtable1[i] = buff[i / 2];
		}
		for (int i = 1; i < RVtable1_count; i += 2) {
			RVtable1[i] = round(((float)RVtable1[i - 1] + (float)RVtable1[i + 1]) / 2);
		}
		delete[]buff;
		/*for (int i = 0; i < RVtable1_count; i++) {
			cout << RVtable1[i] << ' ';
		}
		cout << endl;*/

		// STEP 6: Refining the Rebuild Value table
		// D1 = NULL , cause first time

		// STEP 7: reset the POS and NEG value 
		// wij <- wij - the Rebuild Value of wij after refining

		// W1 will record the node for refining again in second time
		vector<int> W1;

		queue<tree_pointer> q;
		q.push(root);
		while (q.empty() == false) {
			tree_pointer node = q.front();
			if (!(node->x == -1 && node->y == -1)) {
				if (status[node->y][node->x] == CSTATUS::POS || status[node->y][node->x] == CSTATUS::NEG) {
					W1.push_back(img[node->y][node->x]);
					Z1 = abs(img[node->y][node->x]) >= RVtable1[int(RVtable1_count / 2)] ? Z1 + "1" : Z1 + "0";

					if (status[node->y][node->x] == CSTATUS::POS) {
						int minus = check_beside(RVtable1, RVtable1_count, abs(img[node->y][node->x]));
						img[node->y][node->x] = img[node->y][node->x] - minus;
					}
					else {
						int minus = check_beside(RVtable1, RVtable1_count, abs(img[node->y][node->x]));
						img[node->y][node->x] = img[node->y][node->x] + minus;
					}
				}
			}
			q.pop();
			if (node->child_1 != nullptr)
				q.push(node->child_1);
			if (node->child_2 != nullptr)
				q.push(node->child_2);
			if (node->child_3 != nullptr)
				q.push(node->child_3);
			if (node->child_4 != nullptr)
				q.push(node->child_4);
		}

		/*for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cout << setw(3) << img[i][j] << "\t";
			}
			cout << endl;
		}*/

		// ==> Second time <==

		// clean the status table
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				status[i][j] = CSTATUS::NONE;
			}
		}

		// STEP 2: setting thershold T1
		// T1 = T0 / 2
		int T1;
		T1 = round((float)T0 / 2);

		// STEP 3: setting Rebuild Value R1
		// R1 = R0 / 2
		int R1;
		R1 = round((float)R0 / 2);

		// STEP 4: scan with Z-shape and find out all the status of zero-tree
		check_all(root, img, status, T1, S2);

		/*for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cout << setw(3) << GET_CSTATUS_NAME(status[i][j]) << "\t";
			}
			cout << endl;
		}*/

		// STEP 5: Refining the Rebuild Value table and find out Z1
		// i.e. [32, 46, 60] -> [32, 39, 46, 53, 60]

		int* RVtable2;
		int RVtable2_count = 3;

		RVtable2 = new int[RVtable2_count];
		RVtable2[0] = T1;
		RVtable2[1] = R1;
		RVtable2[2] = T0;

		for (int i = 0; i < 1; i++) {
			buff = new int[RVtable2_count];
			for (int i = 0; i < RVtable2_count; i++) {
				buff[i] = RVtable2[i];
			}
			delete[]RVtable2;
			RVtable2_count += 2;
			RVtable2 = new int[RVtable2_count];
			for (int i = 0; i < RVtable2_count; i += 2) {
				RVtable2[i] = buff[i / 2];
			}
			for (int i = 1; i < RVtable2_count; i += 2) {
				RVtable2[i] = round(((float)RVtable2[i - 1] + (float)RVtable2[i + 1]) / 2);
			}
			delete[]buff;
			/*for (int i = 0; i < RVtable2_count; i++) {
				cout << RVtable2[i] << ' ';
			}
			cout << endl;*/
		}

		// STEP 6: Refining the Rebuild Value table RVtable and get D2

		buff = new int[RVtable1_count];
		for (int i = 0; i < RVtable1_count; i++) {
			buff[i] = RVtable1[i];
		}
		delete[]RVtable1;
		RVtable1_count = RVtable1_count * 2 - 1;
		RVtable1 = new int[RVtable1_count];
		for (int i = 0; i < RVtable1_count; i += 2) {
			RVtable1[i] = buff[i / 2];
		}
		for (int i = 1; i < RVtable1_count; i += 2) {
			RVtable1[i] = round(((float)RVtable1[i - 1] + (float)RVtable1[i + 1]) / 2);
		}
		delete[]buff;
		/*for (int i = 0; i < RVtable1_count; i++) {
			cout << RVtable1[i] << ' ';
		}
		cout << endl;*/

		string::iterator its = Z1.begin();

		for (vector<int>::iterator it = W1.begin(); it != W1.end(); it++) {
			int n = *it;
			int minus = check_beside(RVtable1, RVtable1_count, abs(n));
			if (*its == '0') {
				D2 = abs(n) >= RVtable1[int(RVtable1_count / 4)] ? D2 + "1" : D2 + "0";
			}
			else {
				D2 = abs(n) >= RVtable1[int(RVtable1_count * 3 / 4)] ? D2 + "1" : D2 + "0";
			}
		}

		// STEP 7: find out Z2

		// clear queue
		while (!q.empty()) {
			q.pop();
		};
		q.push(root);
		while (q.empty() == false) {
			tree_pointer node = q.front();
			if (!(node->x == -1 && node->y == -1)) {
				if (status[node->y][node->x] == CSTATUS::POS || status[node->y][node->x] == CSTATUS::NEG) {
					Z2 = abs(img[node->y][node->x]) > RVtable2[int(RVtable2_count / 2)] ? Z2 + "1" : Z2 + "0";
				}
			}
			q.pop();
			if (node->child_1 != nullptr)
				q.push(node->child_1);
			if (node->child_2 != nullptr)
				q.push(node->child_2);
			if (node->child_3 != nullptr)
				q.push(node->child_3);
			if (node->child_4 != nullptr)
				q.push(node->child_4);
		}

		//for (int i = 0; i < height; i++) {
		//	for (int j = 0; j < width; j++) {
		//		cout << setw(3) << img[i][j] << "\t";
		//	}
		//	cout << endl;
		//}

		// free memory
		delete[] RVtable1;
		delete[] RVtable2;
		for (int i = 0; i < height; i++) {
			delete status[i];
		}
	}

	private: void EZW_decode(int** img, int height, int width, int maxVal, string S1, string Z1, string S2, string D2, string Z2) {
		// initial

		// init the status table
		CSTATUS** status = new CSTATUS * [height];	// record the CSTATUS of img
		for (int i = 0; i < height; i++) {
			status[i] = new CSTATUS[width];
			for (int j = 0; j < width; j++) {
				status[i][j] = CSTATUS::NONE;
			}
		}
		// build the zero-tree for record the coordinate of the img table
		tree_pointer root = new tnode(0, 0);
		root->child_2 = new tnode(0, 1);
		root->child_3 = new tnode(1, 0);
		root->child_4 = new tnode(1, 1);

		derivative(root->child_2, height / 2);
		derivative(root->child_3, height / 2);
		derivative(root->child_4, height / 2);
		//print_tree(root, img);

		// ==> first time <==

		// STEP 1: init img with zero
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				img[i][j] = 0;
			}
		}

		// STEP 2: find out thershold T0
		int T0;
		int M;

		M = floor(log2(double(maxVal)));
		T0 = pow(2, M);

		// STEP 3: find out the Rebuild Value table
		int R0;
		R0 = (maxVal + T0) / 2;
		int* RVtable1, * buff;
		int RVtable1_count = 3;

		RVtable1 = new int[RVtable1_count];
		RVtable1[0] = T0;
		RVtable1[1] = R0;
		RVtable1[2] = maxVal;

		buff = new int[RVtable1_count];
		for (int i = 0; i < RVtable1_count; i++) {
			buff[i] = RVtable1[i];
		}
		delete[]RVtable1;
		RVtable1_count = RVtable1_count * 2 - 1;
		RVtable1 = new int[RVtable1_count];
		for (int i = 0; i < RVtable1_count; i += 2) {
			RVtable1[i] = buff[i / 2];
		}
		for (int i = 1; i < RVtable1_count; i += 2) {
			RVtable1[i] = round(((float)RVtable1[i - 1] + (float)RVtable1[i + 1]) / 2);
		}
		delete[]buff;

		// STEP 4: Scan the img with S1
		queue<string> queueS1 = split(S1, ' ');

		//// if print out, queue will become NULL
		//while (!queueS1.empty()) {
		//	cout << queueS1.front() << endl;
		//	queueS1.pop();
		//}

		check_all_decode(root, img, status, queueS1, R0);

		// STEP 5: refining with Z1
		string::iterator its = Z1.begin();

		// record the node for refining again
		vector<tree_pointer> Wz1;

		queue<tree_pointer> q;
		q.push(root);
		while (q.empty() == false && its != Z1.end()) {
			tree_pointer node = q.front();
			if (status[node->y][node->x] == CSTATUS::POS || status[node->y][node->x] == CSTATUS::NEG) {
				Wz1.push_back(node);
				char c = *its;
				int num;
				if (c == '1') {
					num = RVtable1[int(RVtable1_count / 2) + 1];
				}
				else {
					num = RVtable1[int(RVtable1_count / 2) - 1];
				}
				img[node->y][node->x] = img[node->y][node->x] > 0 ? num : -1 * num;
				its++;
			}
			q.pop();
			if (node != nullptr) {
				if (node->child_1 != nullptr)
					q.push(node->child_1);
				if (node->child_2 != nullptr)
					q.push(node->child_2);
				if (node->child_3 != nullptr)
					q.push(node->child_3);
				if (node->child_4 != nullptr)
					q.push(node->child_4);
			}
		}

		// STEP 6: process with D1
		// But D1 = NULL, SKIP

		// ==> second time <==

		// clear the status table
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				status[i][j] = CSTATUS::NONE;
			}
		}

		// STEP 2: find out thershold T1
		int T1;

		T1 = floor((float)T0 / 2);

		// STEP 3: find out the Rebuild Value table
		int R1;
		R1 = floor((float)R0 / 2);
		int* RVtable2;
		int RVtable2_count = 3;

		RVtable2 = new int[RVtable2_count];
		RVtable2[0] = T1;
		RVtable2[1] = R1;
		RVtable2[2] = T0;

		buff = new int[RVtable2_count];
		for (int i = 0; i < RVtable2_count; i++) {
			buff[i] = RVtable2[i];
		}
		delete[]RVtable2;
		RVtable2_count = RVtable2_count * 2 - 1;
		RVtable2 = new int[RVtable2_count];
		for (int i = 0; i < RVtable2_count; i += 2) {
			RVtable2[i] = buff[i / 2];
		}
		for (int i = 1; i < RVtable2_count; i += 2) {
			RVtable2[i] = round(((float)RVtable2[i - 1] + (float)RVtable2[i + 1]) / 2);
		}
		delete[]buff;

		// STEP 4: Scan the img with S2
		queue<string> queueS2 = split(S2, ' ');

		//// if print out, queue will become NULL
		//while (!queueS2.empty()) {
		//	cout << queueS2.front() << endl;
		//	queueS2.pop();
		//}

		check_all_decode(root, img, status, queueS2, R1);

		// STEP 5: refining with Z2
		its = Z2.begin();

		// clear queue
		while (!q.empty()) {
			q.pop();
		};
		q.push(root);
		while (q.empty() == false && its != Z2.end()) {
			tree_pointer node = q.front();
			if (status[node->y][node->x] == CSTATUS::POS || status[node->y][node->x] == CSTATUS::NEG) {
				char c = *its;
				int num;
				if (c == '1') {
					num = RVtable2[int(RVtable2_count / 2) + 1];
				}
				else {
					num = RVtable2[int(RVtable2_count / 2) - 1];
				}
				img[node->y][node->x] = img[node->y][node->x] > 0 ? num : -1 * num;
				its++;
			}
			q.pop();
			if (node != nullptr) {
				if (node->child_1 != nullptr)
					q.push(node->child_1);
				if (node->child_2 != nullptr)
					q.push(node->child_2);
				if (node->child_3 != nullptr)
					q.push(node->child_3);
				if (node->child_4 != nullptr)
					q.push(node->child_4);
			}
		}

		// STEP 6: refining with D2
		its = D2.begin();

		for (vector<tree_pointer>::iterator it = Wz1.begin(); it != Wz1.end(); it++) {
			tree_pointer node = *it;
			char c = *its;
			int index = find_index(RVtable1, RVtable1_count, abs(img[node->y][node->x]));
			if (c == '1') {
				if (img[node->y][node->x] > 0) img[node->y][node->x] = round(((float)RVtable1[index] + (float)RVtable1[index + 1]) / 2);
				else img[node->y][node->x] = -1 * round(((float)RVtable1[index] + (float)RVtable1[index + 1]) / 2);
			}
			else {
				if (img[node->y][node->x] > 0) img[node->y][node->x] = round(((float)RVtable1[index] + (float)RVtable1[index - 1]) / 2);
				else img[node->y][node->x] = -1 * round(((float)RVtable1[index] + (float)RVtable1[index - 1]) / 2);
			}
			its++;
		}

		// free memory
		delete[] RVtable1;
		delete[] RVtable2;
		for (int i = 0; i < height; i++) {
			delete status[i];
		}

	}

	};
}
