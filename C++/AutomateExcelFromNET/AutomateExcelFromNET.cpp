#include "AutomateExcelFromNET.h"
#include "main.h"

#define Application_t System::Windows::Forms::Application
using namespace Microsoft::Office::Interop::Excel;
#define EXCEL Microsoft::Office::Interop::Excel
#define Worksheet_t EXCEL::Worksheet
#define Range_t EXCEL::Range

[STAThread] /*KTB [STAThreadAttribute]*/ void main(array<String^>^ args) {
	Application_t::EnableVisualStyles();
	Application_t::SetCompatibleTextRenderingDefault(false);
	AutomateExcelFromNET::main frmMain;
	Application_t::Run(%frmMain); 
	//TEST AutomateExcelFromNET::main^ frmMain2 = gcnew AutomateExcelFromNET::main();
	//TEST frmMain2->ShowDialog();
}
