#ifndef ANALIZATOR_H
#define ANALIZATOR_H

#include <QString>
#include <QStringList>
#include <QRegularExpression>

using namespace std;

class analizator
{

public:
   QString str;
   analizator();

   QStringList zrobListe(QString str);
   int ileLiter();
   int ileSlowJednoliter(QStringList list);
};

#endif // ANALIZATOR_H
