#pragma once

#include <QDialog>
#include "ui_DialogSetIP.h"
#include<functional>

class DialogSetIP : public QDialog
{
	Q_OBJECT
		std::function<void(QString)> ok = nullptr;
	QString currentIP = "";
public:
	DialogSetIP(QWidget* parent = nullptr);
	void setCurrentIP(QString ip);
	void setOnOkListener(std::function<void(QString)> f);
	~DialogSetIP();

private:
	Ui::DialogSetIP ui;
};
