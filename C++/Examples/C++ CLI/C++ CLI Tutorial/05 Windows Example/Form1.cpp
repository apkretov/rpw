#include "Form1.h"

System::Void WindowsExample::Form1::button1_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		double a = double::Parse(textBox1->Text);
		double b = double::Parse(textBox2->Text);
		double c = a + b;
		textBox3->Text = c.ToString();
		System::Text::StringBuilder sb;
		sb.AppendFormat(L"{0} + {1} = {2}", a, b, c);
		listBox1->Items->Add(sb.ToString());
	}
	catch (System::Exception ^ex) {
		MessageBox::Show(this, ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	return System::Void();
}
