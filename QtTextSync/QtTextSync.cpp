#include"stdafx.h"
#include "QtTextSync.h"
#include<qthread.h>
#include "DialogSetIP.h"
QtTextSync::QtTextSync(QWidget* parent)
	: QMainWindow(parent){
	ui.setupUi(this);


	manager = new QNetworkAccessManager();
	manager->setTransferTimeout(3000);
	UpdateServerUrl(currentIP);
	pullTextAndUpdate();
	//event
	{
		//http request
		QObject::connect(manager, &QNetworkAccessManager::finished,
						 this, [this](QNetworkReply* reply)
		{
			if(reply->error())
			{
				std::cout << "error>" << reply->errorString().toStdString() << std::endl;
				UpdateText("error>" + reply->errorString());
				return;
			}

		QString msg = reply->readAll();
		std::cout << "msg>" << msg.toStdString() << "\n";
		UpdateText(msg);
		}

		);
		//set ip buttton
		QObject::connect(ui.but_set_ip, &QPushButton::clicked, [this]()
		{
			DialogSetIP dialog(this);
		dialog.setCurrentIP(currentIP);
		dialog.setOnOkListener([this](QString ip)
		{
			UpdateServerUrl(ip);
		});
		dialog.exec();
		});
		//refresh buttton
		QObject::connect(ui.but_refresh, &QPushButton::clicked, [this]()
		{
			pullTextAndUpdate();
		});
		//auto checkbox
		QObject::connect(ui.checkbox_auto, &QCheckBox::clicked, [this](bool checked)
		{
			if(checked)
			{
				timer->start(1000);
			}
			else
			{
				timer->stop();
			}
		});
	}


	/*auto id = QThread::currentThreadId();
	std::cout << "main thread id " << id << std::endl;*/

	timer = new QTimer(this);
	QObject::connect(timer, &QTimer::timeout, [this]() {
			pullTextAndUpdate();
		});
	


}

QtTextSync::~QtTextSync(){
}

void QtTextSync::UpdateText(QString newText){
	auto oldText = ui.ptxtedit_msg->toPlainText();
	if(oldText != newText)
	{
		ui.ptxtedit_msg->setPlainText(newText);
	}
}

void QtTextSync::UpdateServerUrl(QString ip){
	currentIP = ip;
	request.setUrl(QUrl(QString("http://") + ip + QString(":8080/")));
	ui.label_current_ip->setText(ip + ":8080");
	pullTextAndUpdate();
}

void QtTextSync::pullTextAndUpdate(){
	auto reply = manager->get(request);
}
