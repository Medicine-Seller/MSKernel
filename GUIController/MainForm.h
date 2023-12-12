#pragma once
#include "Util.hpp"
#include "MSKernelInterface.hpp"

MSKernelInterface MSKernel;
#define DRIVER "MSKernel"

namespace GUIController {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

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
	private: System::Windows::Forms::ComboBox^ comboBox1;

	private: System::Windows::Forms::Button^ button1;

	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::CheckedListBox^ checkedListBox1;


	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			this->SuspendLayout();
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(9, 25);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(212, 21);
			this->comboBox1->Sorted = true;
			this->comboBox1->TabIndex = 0;
			this->comboBox1->DropDown += gcnew System::EventHandler(this, &MainForm::comboBox1_DropDown);
			this->comboBox1->SelectionChangeCommitted += gcnew System::EventHandler(this, &MainForm::comboBox1_SelectionChangeCommitted);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(457, 25);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(120, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Set Access Mask";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(12, 250);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(560, 135);
			this->richTextBox1->TabIndex = 4;
			this->richTextBox1->Text = L"";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 234);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(28, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Log:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(9, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(28, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"PID:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(224, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(94, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Access Mask: 0x0";
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->CheckOnClick = true;
			this->checkedListBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->Location = System::Drawing::Point(227, 25);
			this->checkedListBox1->Name = L"checkedListBox1";
			this->checkedListBox1->Size = System::Drawing::Size(225, 199);
			this->checkedListBox1->TabIndex = 8;
			this->checkedListBox1->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &MainForm::checkedListBox1_ItemCheck);
			// 
			// MainForm
			// 
			this->AllowDrop = true;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(584, 397);
			this->Controls->Add(this->checkedListBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->comboBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"MSKernel GUI IO Controller";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		if (!IsServiceExists(DRIVER)) {
			richTextBox1->AppendText(DRIVER + " service can not be found, creating service...\n");
			String^ programDirectory = System::IO::Path::GetDirectoryName(System::Reflection::Assembly::GetEntryAssembly()->Location);
			String^ driverPath = System::IO::Path::Combine(programDirectory, DRIVER + ".sys");
			richTextBox1->AppendText("Driver Directory: " + driverPath + "\n");
			CreateDriverService(DRIVER, driverPath);
		}

		if (IsServiceExists(DRIVER)) {
			richTextBox1->AppendText(DRIVER + " service found, starting " + DRIVER + "...\n");
			ExecuteCmdCommand("sc start " + DRIVER);
		}

		MSKernel.SetDriver("\\\\.\\" DRIVER);

		if (MSKernel.Initialize())
			richTextBox1->AppendText(DRIVER + " initialized!\n");
		else
			richTextBox1->AppendText(DRIVER + " is not initialized!\n");
			
		checkedListBox1->Items->AddRange(AccessMask::Instance()->GetAccessRights()->ToArray());
	}
	private: System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		printf("MSKernel.Close - %d\n", MSKernel.Close());
		ExecuteCmdCommand("sc stop " + DRIVER);
	}
	private: System::Void comboBox1_DropDown(System::Object^ sender, System::EventArgs^ e) {
		comboBox1->Items->Clear();
		comboBox1->Items->AddRange(GetProcessList()->ToArray());
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (comboBox1->SelectedItem == nullptr)
			return;

		BOOL result = 0;

		result = MSKernel.SetAccessMask(AccessMask::Instance()->GetMask());
		richTextBox1->AppendText(DRIVER + ".SetAccessMask result: " + (result ? "Success" : "Failed") + "\n");

		ProcessEntryWrapper^ process = safe_cast<ProcessEntryWrapper^>(comboBox1->SelectedItem);
		result = MSKernel.SetPID(process->GetProcessId());
		richTextBox1->AppendText(DRIVER + ".SetPID result: " + (result ? "Success" : "Failed") + "\n");
	}

	private: System::Void comboBox1_SelectionChangeCommitted(System::Object^ sender, System::EventArgs^ e) {
		if (comboBox1->SelectedItem == nullptr)
		{
			label2->Text = "PID:";
			return;
		}

		ProcessEntryWrapper^ process = safe_cast<ProcessEntryWrapper^>(comboBox1->SelectedItem);
		label2->Text = "PID: " + process->GetProcessId();
	}

	private: System::Void checkedListBox1_ItemCheck(System::Object^ sender, System::Windows::Forms::ItemCheckEventArgs^ e) {
		AccessMask^ accessMask = AccessMask::Instance();
		accessMask->ResetMask();

		for each (AccessRight ^ mask in checkedListBox1->Items) {
			int index = checkedListBox1->Items->IndexOf(mask);

			if (e->Index == index)
			{
				if (e->NewValue == CheckState::Checked)
					accessMask->OperationOrMask(mask->GetAccess());

				continue;
			}

			if (checkedListBox1->GetItemChecked(index))
				accessMask->OperationOrMask(mask->GetAccess());
		}

		System::String^ hexString = String::Format("{0:X}", accessMask->GetMask());
		label3->Text = "Access Mask: 0x" + hexString;
	}

};
}
