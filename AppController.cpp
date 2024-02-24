#include "AppController.h"

Q_INVOKABLE void AppController::openFile(const QUrl& filepath)
{
	openFile(filepath.toLocalFile());
}

void AppController::openFile(const QString& filepath)
{
	m_filename = filepath;
	QList<Line> logs = parser.parse(filepath.toStdString());
	model.reset(logs);
}

Model& AppController::logmodel()
{
	return model;
}

Q_INVOKABLE void AppController::setRegex(const QString& regex) 
{
	parser.setRegex(regex.toStdString());
	openFile(m_filename);
}