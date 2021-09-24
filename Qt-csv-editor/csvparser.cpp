#include "csvparser.h"

//cg1: quoted field value, cg2: unquoted field value
const QString CsvParser::validLineRegexString = "(?:(?:\"([^\"\r\n]+)\")|([^,\r\n]*))(?:,|\n|(?:\r\n)|$)";

CsvParser::CsvParser(QObject *parent) : QObject(parent)
{

}
