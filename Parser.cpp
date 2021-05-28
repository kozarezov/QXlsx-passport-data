#include "Parser.hpp"

Parser::Parser(QString str) : _value(str)
{
	_data["FullName"] = "";
	_data["Bithday"] = "";
	_data["PassportDate"] = "";
	_data["Issued"] = "";
	_data["Series"] = "";
	_data["Number"] = "";
    _data["Remainder"] = "";
    _nameCount = 0;
	parse_value();
}

Parser::~Parser()
{
}

std::map<QString, QString> & Parser::getData()
{
	return (_data);
}

QString	Parser::getFullName()
{
	return(_data["FullName"]);
}

QString	Parser::getBithday()
{
	return(_data["Bithday"]);
}

QString	Parser::getPassportDate()
{
	return(_data["PassportDate"]);
}

QString	Parser::getIssued()
{
	return(_data["Issued"]);
}

QString	Parser::getRemainder()
{
    return(_data["Remainder"]);
}

int		Parser::getSeries()
{
    return(_data["Series"].toInt());
}

int		Parser::getNumber()
{
    return(_data["Number"].toInt());
}

void	Parser::parse_value()
{
	setlocale(LC_ALL, "Russian");

    QStringList vctr = _value.split(" ");

    QStringList::iterator beg = vctr.begin();
    QStringList::iterator end = vctr.end();

	while (beg != end)
	{
		QString tmp = *beg;
		if (isDate(tmp))
            vctr.removeOne(*beg);
		else if (isNumber(tmp))
            vctr.removeOne(*beg);
		else if (isIssued(tmp))
            vctr.removeOne(*beg);
        ++beg;
	}
    for (QStringList::iterator it = vctr.begin(); it != end; ++it)
        _data["Remainder"].push_back(*beg);
}

bool	dateCmp(const QString &date1, const QString &date2)
{
	int nbr1, nbr2;

    QStringList list1 = date1.split(".");
    QStringList list2 = date2.split(".");

    nbr1 = list1[0].toInt() * 10000 + list1[1].toInt() * 100 + list1[2].toInt();
    nbr2 = list2[0].toInt() * 10000 + list2[1].toInt() * 100 + list2[2].toInt();

	return (nbr1 < nbr2);

}

bool	Parser::isDate(const QString &str)
{
    if (_data["PassportDate"] != "" && _data["Bithday"] != "")
        return (false);
    if ( str[0].isNumber() && str.indexOf('.') >= 0)
	{
        if (_data["PassportDate"] == "")
			_data["PassportDate"] = str;
		else
		{
			if (dateCmp(_data["PassportDate"], str))
			{
				_data["Bithday"] = _data["PassportDate"];
				_data["PassportDate"] = str;
			}
			else
				_data["Bithday"] = str;
		}
		return (true);
	}
	return (false);
}

bool	Parser::isNumber(const QString &str)
{
    if (_data["Series"].length() >= 4 && _data["Number"].length() >= 6)
        return (false);
    if (str[0].isNumber())
	{
        if (str.length() == 4)
			_data["Series"] = str;
        else if (str.length() == 2)
			_data["Series"] += str;
        else if (str.length() == 6)
			_data["Number"] = str;
        else if (str.length() == 3)
            _data["Number"] += str;
        else
        {
            _data["Series"] = str.mid(0, 4);
            _data["Number"] = str.mid(4);
        }
		return (true);
	}
	return (false);
}

bool	Parser::isIssued(const QString &str)
{
    if (str[0].isUpper() && _nameCount < 3)
    {
        _data["FullName"] += str + ' ';
        _nameCount++;
        return (true);
    }
    else
    {
        _data["Issued"] = str + ' ';
        return (true);
    }
    return (false);
}
