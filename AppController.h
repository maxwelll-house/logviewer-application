#pragma once

#include <QObject>
#include <QUrl>
#include <QString>

#include "Parser.h"
#include "Model.h"

class AppController : public QObject
{
	Q_OBJECT
public:
	Q_INVOKABLE void openFile(const QUrl& filepath);
	void openFile(const QString& filepath);
	Model& logmodel();
	Q_INVOKABLE void setRegex(const QString& regex);
private:
	Model model;
	Parser parser;
	QString m_filename;
};