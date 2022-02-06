#include "analizator.h"

analizator::analizator()
{

}

QStringList analizator::zrobListe(QString str)
{
    QStringList list;
    list = str.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    return list;
}

int analizator::ileLiter()
{
    int licznik =0;
    for (int i=0; i<str.size(); i++)
    {
        if ((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z') || str[i]==u'ż' ||
                str[i]==u'ó' || str[i]==u'ł' || str[i]==u'ć' || str[i]==u'ę' || str[i]==u'ś' ||
                str[i]==u'ą' || str[i]==u'ź' || str[i]==u'ń' || str[i]==u'Ż' || str[i]==u'Ó' ||
                str[i]==u'Ł' || str[i]==u'Ć' || str[i]==u'Ę' || str[i]==u'Ś' || str[i]==u'Ą' ||
                str[i]==u'Ź' || str[i]==u'Ń') licznik++;
    }
    return licznik;
}

int analizator::ileSlowJednoliter(QStringList list)
{
    int licznik = 0;

    for (int i=0; i<list.size(); i++)
    {
        if (list[i].size()==1) licznik++;
    }

    return licznik;
}
