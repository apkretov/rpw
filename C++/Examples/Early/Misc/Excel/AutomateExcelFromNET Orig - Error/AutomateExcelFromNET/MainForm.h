#pragma once

namespace AutomateExcelFromNET {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Microsoft::Office::Interop::Excel;
	#define Excel Microsoft::Office::Interop::Excel

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  cmdRunExcel;
	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->cmdRunExcel = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// cmdRunExcel
			// 
			this->cmdRunExcel->Location = System::Drawing::Point(197, 12);
			this->cmdRunExcel->Name = L"cmdRunExcel";
			this->cmdRunExcel->Size = System::Drawing::Size(75, 23);
			this->cmdRunExcel->TabIndex = 0;
			this->cmdRunExcel->Text = L"Run Excel";
			this->cmdRunExcel->UseVisualStyleBackColor = true;
			this->cmdRunExcel->Click += gcnew System::EventHandler(this, &MainForm::cmdRunExcel_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 80);
			this->Controls->Add(this->cmdRunExcel);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: 
		System::Collections::SortedList^ slTonsRcvd;
      System::Collections::SortedList^ slByDayNYProjected;
      System::Collections::SortedList^ slByDayNYActual;

		System::Void cmdRunExcel_Click(System::Object^ sender, System::EventArgs^ e);
		void RunExcel();
		void LoadData();
		//ERROR void MakeBarChart(Worksheet^ ws, int row, int col);
		//ERROR void MakeLineChart(Worksheet^ ws, int row, int col);
	};
}
