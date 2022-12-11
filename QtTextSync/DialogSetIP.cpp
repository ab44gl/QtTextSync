#include "stdafx.h"
#include "DialogSetIP.h"

DialogSetIP::DialogSetIP(QWidget* parent)
	: QDialog(parent){
	ui.setupUi(this);
	setWindowTitle("Set IP");
	QObject::connect(ui.pushButton, &QPushButton::clicked, [this]()
	{
		if(ok != nullptr)
		{
			ok(ui.lineEdit->text());
		}
	accept();
	});
}

void DialogSetIP::setCurrentIP(QString ip){
	this->currentIP = ip;
	ui.lineEdit->setText(currentIP);
}

void DialogSetIP::setOnOkListener(std::function<void(QString)> f){
	this->ok = f;
}

DialogSetIP::~DialogSetIP(){
}

