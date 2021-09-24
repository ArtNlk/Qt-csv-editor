#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <QObject>

class CsvParser : public QObject
{
    Q_OBJECT
public:
    explicit CsvParser(QObject *parent = nullptr);
    static const QString validLineRegexString;

signals:

};

#endif // CSVPARSER_H
