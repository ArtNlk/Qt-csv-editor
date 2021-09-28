#ifndef CSVIO_H
#define CSVIO_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QStandardItemModel>

class CsvIO : public QObject
{
    Q_OBJECT
public:
    explicit CsvIO(QObject *parent = nullptr);
    static QRegularExpression validLineRegex;

    void open(const QString& fileName);
    bool parseNext(QStringList& outputList);
    void save(QList<QStringList> records);
    void saveModel(const QStandardItemModel& model);

protected:
    QFile file;
    QTextStream fileStream;
    int headerSize;

};

#endif // CSVIO_H
