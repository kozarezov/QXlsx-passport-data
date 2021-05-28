#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <clocale>
#include "mainwindow.h"
#include <QChar>

class Parser
{
private:

	QString 						_value;
	std::map<QString, QString>	_data;
    int                         _nameCount;

public:
	Parser(QString str);
	~Parser();
	std::map<QString, QString> &	getData();
	QString								getFullName();
	QString								getBithday();
	QString								getPassportDate();
	QString								getIssued();
    QString                             getRemainder();
	int										getSeries();
	int										getNumber();
	void									parse_value();
	bool									isDate(const QString &str);
	bool									isNumber(const QString &str);
	bool									isIssued(const QString &str);
};

#endif

