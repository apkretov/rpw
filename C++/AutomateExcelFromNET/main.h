#pragma once
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::wstring;
#include <map>
using std::map;
#include "AutomateExcelFromNET.h"
#include "timberDB.h"

namespace AutomateExcelFromNET {
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Data;
	using namespace System::Drawing;
	typedef System::Windows::Forms::DataGridViewCellCollection DataGridViewCellCollection_t;
	//OFF using namespace System::Diagnostics;

	using namespace Microsoft::Office::Interop::Excel;
	#define EXCEL Microsoft::Office::Interop::Excel
	typedef EXCEL::Worksheet Worksheet_t;
	typedef EXCEL::Range Range_t;

	/// <summary>
	/// Summary for main
	/// </summary>

	public ref class main : public System::Windows::Forms::Form { 
	public:
		main(void);
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~main();
	private:
		System::Windows::Forms::Button^ cmdRunExcel;
		System::Windows::Forms::Button^ cmdInsertData;
		System::Windows::Forms::Button^ cmdDeleteData;






	private: System::Windows::Forms::CheckedListBox^ lstCountrySheets;










	private: System::Windows::Forms::DataGridView^ grdYears;

	private: System::Windows::Forms::Label^ lblYears;

	private: System::Windows::Forms::DataGridView^ grdTables;


	private: System::Windows::Forms::Label^ lblTables;















	private: System::Windows::Forms::Label^ lblSheetCountries;

	private: System::Windows::Forms::ComboBox^ cbxSheetCountry;
	private: System::Windows::Forms::Label^ lblSheetDim;
	private: System::Windows::Forms::ComboBox^ cbxSheetDim;






	private: System::Windows::Forms::GroupBox^ grpCountries;

	private: System::Windows::Forms::TextBox^ txtCountryNames;

	private: System::Windows::Forms::Label^ lblCountryNames;

	private: System::Windows::Forms::TextBox^ txtCountryCodes;
	private: System::Windows::Forms::Label^ lblCountryCodes;
	private: System::Windows::Forms::GroupBox^ grpDim;







	private: System::Windows::Forms::TextBox^  txtColDim;



	private: System::Windows::Forms::Label^  lblColDim;



	private: System::Windows::Forms::TextBox^ txtRowCountry1;
	private: System::Windows::Forms::Label^ lblRowCountry1;
	private: System::Windows::Forms::GroupBox^ grpSQLServer;
	private: System::Windows::Forms::Label^ lblDatabase;



	private: System::Windows::Forms::Label^ lblPWD;

	private: System::Windows::Forms::Label^ lblUID;

	private: System::Windows::Forms::Label^ lblDSN;
	private: System::Windows::Forms::TextBox^ txtDatabase;


	private: System::Windows::Forms::TextBox^ txtPWD;

	private: System::Windows::Forms::TextBox^ txtUID;

	private: System::Windows::Forms::TextBox^ txtDSN;

	private: System::Windows::Forms::TextBox^ txtServer;

	private: System::Windows::Forms::Label^ lblServer;

	private: System::Windows::Forms::Label^ lblCountrySheets;
private: System::Windows::Forms::Label^  lblTable;
private: System::Windows::Forms::TextBox^  txtTable;
private: System::Windows::Forms::Label^  lblNonNum;
private: System::Windows::Forms::DataGridView^  grdNonNum;











private: System::Windows::Forms::DataGridViewTextBoxColumn^  colYears;


















private: System::Windows::Forms::DataGridViewTextBoxColumn^  colNonNum;
private: System::Windows::Forms::DataGridViewCheckBoxColumn^  colActive;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  colDescription;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  colRange;
private: System::Windows::Forms::DataGridViewComboBoxColumn^  colYearsOrder;
private: System::Windows::Forms::DataGridViewComboBoxColumn^  colYearsAlign;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  colTopics;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  colGroups;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  colSubgroups;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  colRowDim1;





















































































































































































				/// <summary>
				/// Required designer variable.
				/// </summary>
				System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
				/// <summary>
				/// Required method for Designer support - do not modify	the contents of this method with the code editor.
				/// </summary>
				void InitializeComponent(void) {
					System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(main::typeid));
					this->cmdRunExcel = (gcnew System::Windows::Forms::Button());
					this->cmdInsertData = (gcnew System::Windows::Forms::Button());
					this->cmdDeleteData = (gcnew System::Windows::Forms::Button());
					this->lstCountrySheets = (gcnew System::Windows::Forms::CheckedListBox());
					this->grdYears = (gcnew System::Windows::Forms::DataGridView());
					this->colYears = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
					this->lblYears = (gcnew System::Windows::Forms::Label());
					this->grdTables = (gcnew System::Windows::Forms::DataGridView());
					this->colActive = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
					this->colDescription = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
					this->colRange = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
					this->colYearsOrder = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
					this->colYearsAlign = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
					this->colTopics = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
					this->colGroups = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
					this->colSubgroups = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
					this->colRowDim1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
					this->lblTables = (gcnew System::Windows::Forms::Label());
					this->lblSheetCountries = (gcnew System::Windows::Forms::Label());
					this->cbxSheetCountry = (gcnew System::Windows::Forms::ComboBox());
					this->lblSheetDim = (gcnew System::Windows::Forms::Label());
					this->cbxSheetDim = (gcnew System::Windows::Forms::ComboBox());
					this->grpCountries = (gcnew System::Windows::Forms::GroupBox());
					this->lblCountrySheets = (gcnew System::Windows::Forms::Label());
					this->txtRowCountry1 = (gcnew System::Windows::Forms::TextBox());
					this->lblRowCountry1 = (gcnew System::Windows::Forms::Label());
					this->txtCountryNames = (gcnew System::Windows::Forms::TextBox());
					this->lblCountryNames = (gcnew System::Windows::Forms::Label());
					this->txtCountryCodes = (gcnew System::Windows::Forms::TextBox());
					this->lblCountryCodes = (gcnew System::Windows::Forms::Label());
					this->grpDim = (gcnew System::Windows::Forms::GroupBox());
					this->txtColDim = (gcnew System::Windows::Forms::TextBox());
					this->lblColDim = (gcnew System::Windows::Forms::Label());
					this->grpSQLServer = (gcnew System::Windows::Forms::GroupBox());
					this->lblTable = (gcnew System::Windows::Forms::Label());
					this->lblDatabase = (gcnew System::Windows::Forms::Label());
					this->lblPWD = (gcnew System::Windows::Forms::Label());
					this->lblUID = (gcnew System::Windows::Forms::Label());
					this->lblDSN = (gcnew System::Windows::Forms::Label());
					this->txtTable = (gcnew System::Windows::Forms::TextBox());
					this->txtDatabase = (gcnew System::Windows::Forms::TextBox());
					this->txtPWD = (gcnew System::Windows::Forms::TextBox());
					this->txtUID = (gcnew System::Windows::Forms::TextBox());
					this->txtDSN = (gcnew System::Windows::Forms::TextBox());
					this->txtServer = (gcnew System::Windows::Forms::TextBox());
					this->lblServer = (gcnew System::Windows::Forms::Label());
					this->lblNonNum = (gcnew System::Windows::Forms::Label());
					this->grdNonNum = (gcnew System::Windows::Forms::DataGridView());
					this->colNonNum = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
					(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grdYears))->BeginInit();
					(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grdTables))->BeginInit();
					this->grpCountries->SuspendLayout();
					this->grpDim->SuspendLayout();
					this->grpSQLServer->SuspendLayout();
					(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grdNonNum))->BeginInit();
					this->SuspendLayout();
					// 
					// cmdRunExcel
					// 
					this->cmdRunExcel->Location = System::Drawing::Point(1091, 36);
					this->cmdRunExcel->Name = L"cmdRunExcel";
					this->cmdRunExcel->Size = System::Drawing::Size(222, 23);
					this->cmdRunExcel->TabIndex = 1;
					this->cmdRunExcel->Text = L"&Open Excel file with countries";
					this->cmdRunExcel->UseVisualStyleBackColor = true;
					this->cmdRunExcel->Click += gcnew System::EventHandler(this, &main::cmdRunExcel_Click);
					// 
					// cmdInsertData
					// 
					this->cmdInsertData->Location = System::Drawing::Point(1102, 594);
					this->cmdInsertData->Name = L"cmdInsertData";
					this->cmdInsertData->Size = System::Drawing::Size(114, 23);
					this->cmdInsertData->TabIndex = 21;
					this->cmdInsertData->Text = L"&Upload data";
					this->cmdInsertData->UseVisualStyleBackColor = true;
					this->cmdInsertData->Click += gcnew System::EventHandler(this, &main::cmdInsertData_Click);
					// 
					// cmdDeleteData
					// 
					this->cmdDeleteData->DialogResult = System::Windows::Forms::DialogResult::Cancel;
					this->cmdDeleteData->Location = System::Drawing::Point(1221, 594);
					this->cmdDeleteData->Name = L"cmdDeleteData";
					this->cmdDeleteData->Size = System::Drawing::Size(114, 23);
					this->cmdDeleteData->TabIndex = 22;
					this->cmdDeleteData->Text = L"&Delete data";
					this->cmdDeleteData->UseVisualStyleBackColor = true;
					this->cmdDeleteData->Click += gcnew System::EventHandler(this, &main::cmdDeleteData_Click);
					// 
					// lstCountrySheets
					// 
					this->lstCountrySheets->FormattingEnabled = true;
					this->lstCountrySheets->HorizontalScrollbar = true;
					this->lstCountrySheets->Location = System::Drawing::Point(6, 36);
					this->lstCountrySheets->MultiColumn = true;
					this->lstCountrySheets->Name = L"lstCountrySheets";
					this->lstCountrySheets->Size = System::Drawing::Size(1066, 154);
					this->lstCountrySheets->TabIndex = 2;
					// 
					// grdYears
					// 
					this->grdYears->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
					this->grdYears->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1) { this->colYears });
					this->grdYears->Location = System::Drawing::Point(12, 246);
					this->grdYears->Name = L"grdYears";
					this->grdYears->Size = System::Drawing::Size(143, 371);
					this->grdYears->TabIndex = 7;
					// 
					// colYears
					// 
					this->colYears->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
					this->colYears->HeaderText = L"Year";
					this->colYears->Name = L"colYears";
					this->colYears->Resizable = System::Windows::Forms::DataGridViewTriState::False;
					// 
					// lblYears
					// 
					this->lblYears->AutoSize = true;
					this->lblYears->Location = System::Drawing::Point(12, 230);
					this->lblYears->Name = L"lblYears";
					this->lblYears->Size = System::Drawing::Size(109, 13);
					this->lblYears->TabIndex = 12;
					this->lblYears->Text = L"Years of Excel tables:";
					// 
					// grdTables
					// 
					this->grdTables->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
					this->grdTables->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(9) {
						this->colActive,
							this->colDescription, this->colRange, this->colYearsOrder, this->colYearsAlign, this->colTopics, this->colGroups, this->colSubgroups,
							this->colRowDim1
					});
					this->grdTables->Location = System::Drawing::Point(161, 246);
					this->grdTables->Name = L"grdTables";
					this->grdTables->Size = System::Drawing::Size(713, 371);
					this->grdTables->TabIndex = 8;
					// 
					// colActive
					// 
					this->colActive->HeaderText = L"Active";
					this->colActive->Name = L"colActive";
					this->colActive->Width = 51;
					// 
					// colDescription
					// 
					this->colDescription->HeaderText = L"Description";
					this->colDescription->Name = L"colDescription";
					this->colDescription->Width = 88;
					// 
					// colRange
					// 
					this->colRange->HeaderText = L"Range";
					this->colRange->Name = L"colRange";
					this->colRange->Resizable = System::Windows::Forms::DataGridViewTriState::True;
					this->colRange->Width = 88;
					// 
					// colYearsOrder
					// 
					this->colYearsOrder->HeaderText = L"Years ordered";
					this->colYearsOrder->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Ascending", L"Descending", L"Latest" });
					this->colYearsOrder->Name = L"colYearsOrder";
					this->colYearsOrder->Width = 94;
					// 
					// colYearsAlign
					// 
					this->colYearsAlign->HeaderText = L"Years aligned";
					this->colYearsAlign->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Horizontally", L"Vertically", L"-" });
					this->colYearsAlign->Name = L"colYearsAlign";
					this->colYearsAlign->Resizable = System::Windows::Forms::DataGridViewTriState::True;
					this->colYearsAlign->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Automatic;
					this->colYearsAlign->Width = 94;
					// 
					// colTopics
					// 
					this->colTopics->HeaderText = L"Topics";
					this->colTopics->Name = L"colTopics";
					this->colTopics->Width = 65;
					// 
					// colGroups
					// 
					this->colGroups->HeaderText = L"Groups";
					this->colGroups->Name = L"colGroups";
					this->colGroups->Width = 65;
					// 
					// colSubgroups
					// 
					this->colSubgroups->HeaderText = L"Subgroups";
					this->colSubgroups->Name = L"colSubgroups";
					this->colSubgroups->Width = 60;
					// 
					// colRowDim1
					// 
					this->colRowDim1->HeaderText = L"1D row";
					this->colRowDim1->Name = L"colRowDim1";
					this->colRowDim1->Width = 65;
					// 
					// lblTables
					// 
					this->lblTables->AutoSize = true;
					this->lblTables->Location = System::Drawing::Point(158, 230);
					this->lblTables->Name = L"lblTables";
					this->lblTables->Size = System::Drawing::Size(135, 13);
					this->lblTables->TabIndex = 15;
					this->lblTables->Text = L"Parameters of Excel tables:";
					// 
					// lblSheetCountries
					// 
					this->lblSheetCountries->AutoSize = true;
					this->lblSheetCountries->Location = System::Drawing::Point(1089, 82);
					this->lblSheetCountries->Name = L"lblSheetCountries";
					this->lblSheetCountries->Size = System::Drawing::Size(83, 13);
					this->lblSheetCountries->TabIndex = 16;
					this->lblSheetCountries->Text = L"Countries sheet:";
					// 
					// cbxSheetCountry
					// 
					this->cbxSheetCountry->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->cbxSheetCountry->FormattingEnabled = true;
					this->cbxSheetCountry->Location = System::Drawing::Point(1214, 79);
					this->cbxSheetCountry->Name = L"cbxSheetCountry";
					this->cbxSheetCountry->Size = System::Drawing::Size(100, 21);
					this->cbxSheetCountry->TabIndex = 3;
					// 
					// lblSheetDim
					// 
					this->lblSheetDim->AutoSize = true;
					this->lblSheetDim->Location = System::Drawing::Point(6, 26);
					this->lblSheetDim->Name = L"lblSheetDim";
					this->lblSheetDim->Size = System::Drawing::Size(93, 13);
					this->lblSheetDim->TabIndex = 16;
					this->lblSheetDim->Text = L"Dimensions sheet:";
					// 
					// cbxSheetDim
					// 
					this->cbxSheetDim->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->cbxSheetDim->FormattingEnabled = true;
					this->cbxSheetDim->Location = System::Drawing::Point(123, 23);
					this->cbxSheetDim->Name = L"cbxSheetDim";
					this->cbxSheetDim->Size = System::Drawing::Size(100, 21);
					this->cbxSheetDim->TabIndex = 11;
					// 
					// grpCountries
					// 
					this->grpCountries->Controls->Add(this->lblCountrySheets);
					this->grpCountries->Controls->Add(this->cbxSheetCountry);
					this->grpCountries->Controls->Add(this->lblSheetCountries);
					this->grpCountries->Controls->Add(this->txtRowCountry1);
					this->grpCountries->Controls->Add(this->lblRowCountry1);
					this->grpCountries->Controls->Add(this->txtCountryNames);
					this->grpCountries->Controls->Add(this->lblCountryNames);
					this->grpCountries->Controls->Add(this->txtCountryCodes);
					this->grpCountries->Controls->Add(this->lblCountryCodes);
					this->grpCountries->Controls->Add(this->lstCountrySheets);
					this->grpCountries->Controls->Add(this->cmdRunExcel);
					this->grpCountries->Location = System::Drawing::Point(12, 12);
					this->grpCountries->Name = L"grpCountries";
					this->grpCountries->Size = System::Drawing::Size(1322, 202);
					this->grpCountries->TabIndex = 0;
					this->grpCountries->TabStop = false;
					this->grpCountries->Text = L"Countries";
					// 
					// lblCountrySheets
					// 
					this->lblCountrySheets->AutoSize = true;
					this->lblCountrySheets->Location = System::Drawing::Point(6, 20);
					this->lblCountrySheets->Name = L"lblCountrySheets";
					this->lblCountrySheets->Size = System::Drawing::Size(155, 13);
					this->lblCountrySheets->TabIndex = 20;
					this->lblCountrySheets->Text = L"Excel country sheets to upload:";
					// 
					// txtRowCountry1
					// 
					this->txtRowCountry1->Location = System::Drawing::Point(1214, 170);
					this->txtRowCountry1->Name = L"txtRowCountry1";
					this->txtRowCountry1->Size = System::Drawing::Size(100, 20);
					this->txtRowCountry1->TabIndex = 6;
					this->txtRowCountry1->Text = L"2";
					// 
					// lblRowCountry1
					// 
					this->lblRowCountry1->AutoSize = true;
					this->lblRowCountry1->Location = System::Drawing::Point(1089, 173);
					this->lblRowCountry1->Name = L"lblRowCountry1";
					this->lblRowCountry1->Size = System::Drawing::Size(82, 13);
					this->lblRowCountry1->TabIndex = 4;
					this->lblRowCountry1->Text = L"1st country row:";
					// 
					// txtCountryNames
					// 
					this->txtCountryNames->Location = System::Drawing::Point(1214, 140);
					this->txtCountryNames->Name = L"txtCountryNames";
					this->txtCountryNames->Size = System::Drawing::Size(100, 20);
					this->txtCountryNames->TabIndex = 5;
					this->txtCountryNames->Text = L"2";
					// 
					// lblCountryNames
					// 
					this->lblCountryNames->AutoSize = true;
					this->lblCountryNames->Location = System::Drawing::Point(1089, 143);
					this->lblCountryNames->Name = L"lblCountryNames";
					this->lblCountryNames->Size = System::Drawing::Size(119, 13);
					this->lblCountryNames->TabIndex = 4;
					this->lblCountryNames->Text = L"Country Names column:";
					// 
					// txtCountryCodes
					// 
					this->txtCountryCodes->Location = System::Drawing::Point(1214, 110);
					this->txtCountryCodes->Name = L"txtCountryCodes";
					this->txtCountryCodes->Size = System::Drawing::Size(100, 20);
					this->txtCountryCodes->TabIndex = 4;
					this->txtCountryCodes->Text = L"1";
					// 
					// lblCountryCodes
					// 
					this->lblCountryCodes->AutoSize = true;
					this->lblCountryCodes->Location = System::Drawing::Point(1089, 113);
					this->lblCountryCodes->Name = L"lblCountryCodes";
					this->lblCountryCodes->Size = System::Drawing::Size(116, 13);
					this->lblCountryCodes->TabIndex = 4;
					this->lblCountryCodes->Text = L"Country Codes column:";
					// 
					// grpDim
					// 
					this->grpDim->Controls->Add(this->cbxSheetDim);
					this->grpDim->Controls->Add(this->lblSheetDim);
					this->grpDim->Controls->Add(this->txtColDim);
					this->grpDim->Controls->Add(this->lblColDim);
					this->grpDim->Location = System::Drawing::Point(1102, 240);
					this->grpDim->Name = L"grpDim";
					this->grpDim->Size = System::Drawing::Size(232, 88);
					this->grpDim->TabIndex = 10;
					this->grpDim->TabStop = false;
					this->grpDim->Text = L"Dimensions";
					// 
					// txtColDim
					// 
					this->txtColDim->Location = System::Drawing::Point(123, 55);
					this->txtColDim->Name = L"txtColDim";
					this->txtColDim->Size = System::Drawing::Size(100, 20);
					this->txtColDim->TabIndex = 12;
					this->txtColDim->Text = L"1";
					// 
					// lblColDim
					// 
					this->lblColDim->AutoSize = true;
					this->lblColDim->Location = System::Drawing::Point(6, 58);
					this->lblColDim->Name = L"lblColDim";
					this->lblColDim->Size = System::Drawing::Size(115, 13);
					this->lblColDim->TabIndex = 4;
					this->lblColDim->Text = L"Dimension IDs column:";
					// 
					// grpSQLServer
					// 
					this->grpSQLServer->Controls->Add(this->lblTable);
					this->grpSQLServer->Controls->Add(this->lblDatabase);
					this->grpSQLServer->Controls->Add(this->lblPWD);
					this->grpSQLServer->Controls->Add(this->lblUID);
					this->grpSQLServer->Controls->Add(this->lblDSN);
					this->grpSQLServer->Controls->Add(this->txtTable);
					this->grpSQLServer->Controls->Add(this->txtDatabase);
					this->grpSQLServer->Controls->Add(this->txtPWD);
					this->grpSQLServer->Controls->Add(this->txtUID);
					this->grpSQLServer->Controls->Add(this->txtDSN);
					this->grpSQLServer->Controls->Add(this->txtServer);
					this->grpSQLServer->Controls->Add(this->lblServer);
					this->grpSQLServer->Location = System::Drawing::Point(1103, 352);
					this->grpSQLServer->Name = L"grpSQLServer";
					this->grpSQLServer->Size = System::Drawing::Size(232, 208);
					this->grpSQLServer->TabIndex = 14;
					this->grpSQLServer->TabStop = false;
					this->grpSQLServer->Text = L"SQL Server";
					// 
					// lblTable
					// 
					this->lblTable->AutoSize = true;
					this->lblTable->Location = System::Drawing::Point(6, 177);
					this->lblTable->Name = L"lblTable";
					this->lblTable->Size = System::Drawing::Size(37, 13);
					this->lblTable->TabIndex = 12;
					this->lblTable->Text = L"Table:";
					// 
					// lblDatabase
					// 
					this->lblDatabase->AutoSize = true;
					this->lblDatabase->Location = System::Drawing::Point(6, 148);
					this->lblDatabase->Name = L"lblDatabase";
					this->lblDatabase->Size = System::Drawing::Size(56, 13);
					this->lblDatabase->TabIndex = 12;
					this->lblDatabase->Text = L"Database:";
					// 
					// lblPWD
					// 
					this->lblPWD->AutoSize = true;
					this->lblPWD->Location = System::Drawing::Point(6, 116);
					this->lblPWD->Name = L"lblPWD";
					this->lblPWD->Size = System::Drawing::Size(56, 13);
					this->lblPWD->TabIndex = 10;
					this->lblPWD->Text = L"Password:";
					// 
					// lblUID
					// 
					this->lblUID->AutoSize = true;
					this->lblUID->Location = System::Drawing::Point(8, 84);
					this->lblUID->Name = L"lblUID";
					this->lblUID->Size = System::Drawing::Size(36, 13);
					this->lblUID->TabIndex = 8;
					this->lblUID->Text = L"Login:";
					// 
					// lblDSN
					// 
					this->lblDSN->AutoSize = true;
					this->lblDSN->Location = System::Drawing::Point(6, 52);
					this->lblDSN->Name = L"lblDSN";
					this->lblDSN->Size = System::Drawing::Size(68, 13);
					this->lblDSN->TabIndex = 6;
					this->lblDSN->Text = L"Data source:";
					// 
					// txtTable
					// 
					this->txtTable->Location = System::Drawing::Point(123, 177);
					this->txtTable->Name = L"txtTable";
					this->txtTable->Size = System::Drawing::Size(100, 20);
					this->txtTable->TabIndex = 20;
					this->txtTable->Text = L"Data";
					// 
					// txtDatabase
					// 
					this->txtDatabase->Location = System::Drawing::Point(123, 145);
					this->txtDatabase->Name = L"txtDatabase";
					this->txtDatabase->Size = System::Drawing::Size(100, 20);
					this->txtDatabase->TabIndex = 19;
					this->txtDatabase->Text = L"timberFO";
					// 
					// txtPWD
					// 
					this->txtPWD->Location = System::Drawing::Point(123, 113);
					this->txtPWD->Name = L"txtPWD";
					this->txtPWD->PasswordChar = '*';
					this->txtPWD->Size = System::Drawing::Size(100, 20);
					this->txtPWD->TabIndex = 18;
					this->txtPWD->Text = L"110502";
					// 
					// txtUID
					// 
					this->txtUID->Location = System::Drawing::Point(123, 81);
					this->txtUID->Name = L"txtUID";
					this->txtUID->Size = System::Drawing::Size(100, 20);
					this->txtUID->TabIndex = 17;
					this->txtUID->Text = L"Alex2";
					// 
					// txtDSN
					// 
					this->txtDSN->Location = System::Drawing::Point(123, 49);
					this->txtDSN->Name = L"txtDSN";
					this->txtDSN->Size = System::Drawing::Size(100, 20);
					this->txtDSN->TabIndex = 16;
					this->txtDSN->Text = L"PCAxis2";
					// 
					// txtServer
					// 
					this->txtServer->Location = System::Drawing::Point(123, 17);
					this->txtServer->Name = L"txtServer";
					this->txtServer->Size = System::Drawing::Size(100, 20);
					this->txtServer->TabIndex = 15;
					this->txtServer->Text = L"KIRILL-HP";
					// 
					// lblServer
					// 
					this->lblServer->AutoSize = true;
					this->lblServer->Location = System::Drawing::Point(6, 20);
					this->lblServer->Name = L"lblServer";
					this->lblServer->Size = System::Drawing::Size(41, 13);
					this->lblServer->TabIndex = 4;
					this->lblServer->Text = L"Server:";
					// 
					// lblNonNum
					// 
					this->lblNonNum->AutoSize = true;
					this->lblNonNum->Location = System::Drawing::Point(880, 230);
					this->lblNonNum->Name = L"lblNonNum";
					this->lblNonNum->Size = System::Drawing::Size(147, 13);
					this->lblNonNum->TabIndex = 12;
					this->lblNonNum->Text = L"Valid non-numeric cell values:";
					// 
					// grdNonNum
					// 
					this->grdNonNum->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
					this->grdNonNum->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1) { this->colNonNum });
					this->grdNonNum->Location = System::Drawing::Point(880, 246);
					this->grdNonNum->Name = L"grdNonNum";
					this->grdNonNum->Size = System::Drawing::Size(204, 371);
					this->grdNonNum->TabIndex = 9;
					// 
					// colNonNum
					// 
					this->colNonNum->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
					this->colNonNum->HeaderText = L"Non-numeric value";
					this->colNonNum->Name = L"colNonNum";
					this->colNonNum->Resizable = System::Windows::Forms::DataGridViewTriState::False;
					// 
					// main
					// 
					this->AcceptButton = this->cmdInsertData;
					this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
					this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					this->AutoScroll = true;
					this->CancelButton = this->cmdDeleteData;
					this->ClientSize = System::Drawing::Size(1346, 629);
					this->Controls->Add(this->grpSQLServer);
					this->Controls->Add(this->grpDim);
					this->Controls->Add(this->grpCountries);
					this->Controls->Add(this->lblTables);
					this->Controls->Add(this->grdTables);
					this->Controls->Add(this->grdNonNum);
					this->Controls->Add(this->grdYears);
					this->Controls->Add(this->lblNonNum);
					this->Controls->Add(this->lblYears);
					this->Controls->Add(this->cmdDeleteData);
					this->Controls->Add(this->cmdInsertData);
					this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
					this->Name = L"main";
					this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
					this->Text = L"Excel to SQL Server Uploader";
					(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grdYears))->EndInit();
					(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grdTables))->EndInit();
					this->grpCountries->ResumeLayout(false);
					this->grpCountries->PerformLayout();
					this->grpDim->ResumeLayout(false);
					this->grpDim->PerformLayout();
					this->grpSQLServer->ResumeLayout(false);
					this->grpSQLServer->PerformLayout();
					(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grdNonNum))->EndInit();
					this->ResumeLayout(false);
					this->PerformLayout();

				}
#pragma endregion
	private:
		typedef map<string, const vector<double>&> mapYears_t;
		typedef System::Windows::Forms::DataGridView DataGridView_t;

		EXCEL::Application^ cxlsApp{};
		Workbook^ cwbkFO{};
		String^ cstrFileName{};

		void addGrdSingleCol(vector<string> vecItems, DataGridView_t^ grd);
		void addGrdTables(bool blnActive, String^ strDesctription, String^ strRange, uint32_t intYearsOrder, uint32_t intYearsAlign, uint32_t intTopics, uint32_t intGroups, uint32_t intSubgroups, uint32_t intRowDim1);

		void enableControls(bool blnEnable);
		void cmdRunExcel_Click_Thread();
		System::Void cmdRunExcel_Click(System::Object^ sender, System::EventArgs^ e);
		wstring cliStringToWstring(String^ strCli);
		const wchar_t* cliStringToWchar(String^ strCli);
		void fillTimberDB(timberDB::timberDB& sttTimberDB);
		System::Void cmdInsertData_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void cmdDeleteData_Click(System::Object^ sender, System::EventArgs^ e);
		
		void quitExcel();
		bool validateNonNum(Range_t^ rngValue); 
		bool uploadTable(const vector<double>& vecYears, const wstring& strCountryCode, Range_t^ rngTable, DataGridViewCellCollection_t^ objTableRowCells, vector<vector<wstring>>& strCountryDim, vector<vector<double>>& dblYearValue);
		wstring getCountryCode(String^ strCountryName);
		bool uploadCountry(Worksheet_t^ shtCountry, const mapYears_t& mapYears, vector<vector<wstring>>& strCountryDim, vector<vector<double>>& dblYearValue);

		string cliStringToString(String^ strCli) { //C++/CLI Tutorial //String Conversions @ http://asawicki.info/Download/Productions/Publications/CPP_CLI_tutorial.pdf
			IntPtr objAnsiStr = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(strCli);
			string strStd = (const char*)objAnsiStr.ToPointer();
			System::Runtime::InteropServices::Marshal::FreeHGlobal(objAnsiStr);
			return strStd;
		}
	};
}
