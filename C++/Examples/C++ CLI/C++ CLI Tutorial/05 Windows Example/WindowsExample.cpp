#include "Form1.h" //C++/CLI Tutorial @ http://asawicki.info/Download/Productions/Publications/CPP_CLI_tutorial.pdf
using namespace System;
using namespace System::Windows::Forms;
#define Application_t System::Windows::Forms::Application

[STAThread] /*KTB [STAThreadAttribute]*/ void main(array<String^>^ args) {
	Application_t::EnableVisualStyles();
	Application_t::SetCompatibleTextRenderingDefault(false);
	WindowsExample::Form1 frmMain;
	Application_t::Run(%frmMain); 
}
