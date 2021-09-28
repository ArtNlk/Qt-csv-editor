#include "csvio.h"

#include <stdexcept>

//cg1: quoted field value, cg2: unquoted field value
QRegularExpression CsvIO::validLineRegex = QRegularExpression("(?<=,|^)(?:(?:(?:\"((?:[^\"\r\n]|\"\")+)\")|([^,\r\n]*))(?:,|\r|\n|$))");

CsvIO::CsvIO(QObject *parent) :
    QObject(parent),
    file(),
    fileStream(),
    headerSize(-1)
{

}

void CsvIO::open(const QString &fileName)
{
    file.setFileName(fileName);
    file.open(QFile::ReadOnly);
    fileStream.setDevice(&file);
}

bool CsvIO::parseNext(QStringList &outputList)
{
    if(fileStream.atEnd()) {return false;}
    QString line = fileStream.readLine();
    QRegularExpressionMatchIterator iter = validLineRegex.globalMatch(line);
    QStringList output;
    QString temp;
    QRegularExpressionMatch tempMatch;
    int fieldCount = 0;
    while(iter.hasNext())
    {
        tempMatch = iter.next();
        temp = tempMatch.captured(1).isEmpty() ? tempMatch.captured(2) : tempMatch.captured(1);
        temp.replace("\"\"","\"");
        output.append(temp);
        fieldCount++;
    }
    if(headerSize == -1)
    {
        headerSize = fieldCount;
    }
    if(fieldCount != headerSize)
    {
        throw std::runtime_error("Record size mismatch!");
    }
    outputList = output;

    return true;
}

void CsvIO::save(QList<QStringList> records)
{
    file.close();
    file.open(QFile::WriteOnly);
    QString tempLine;
    for(auto& record : records)
    {
        for(auto& field : record)
        {
            field.replace("\"","\"\"");
            tempLine.append(QString("\"%1\",").arg(field));
        }
        tempLine.append('\n');
        file.write(tempLine.toUtf8());
    }
    file.close();
    open(file.fileName());
}

void CsvIO::saveModel(const QStandardItemModel &model)
{
    file.close();
    file.open(QFile::WriteOnly);
    QString tempLine;
    QString temp;

    for(int col = 0; col < model.columnCount(); col++)
    {
        temp = model.headerData(col,Qt::Horizontal).toString();
        tempLine.append(temp);
        if(col != model.columnCount() - 1)
        {
        tempLine.append(',');
        }
    }
    tempLine.append('\n');
    file.write(tempLine.toUtf8());

    for(int row = 0; row < model.rowCount(); row++)
    {
        tempLine = "";
        for(int col = 0; col < model.columnCount(); col++)
        {
            temp = model.item(row,col)->text();
            qDebug() << temp;
            temp.replace("\"","\"\"");
            tempLine.append(QString("\"%1\"").arg(temp));
            if(col != model.columnCount() - 1)
            {
            tempLine.append(',');
            }
        }
        if(row != model.rowCount() - 1)
        {
        tempLine.append('\n');
        }
        file.write(tempLine.toUtf8());
    }
    file.close();
    open(file.fileName());
}
