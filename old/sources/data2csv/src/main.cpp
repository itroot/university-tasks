/***************************************************************************
 *   Copyright (C) 2008 by Ivan A. Tolstosheyev   *
 *   ivan.tolstosheyev@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include <QCoreApplication>
#include <QtCore>



int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);
  //
  QFile res("res.txt");
  
  if (!res.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug("Failed to open res file.");
    return 1;
  }

  QFile csv("res.csv");
  if (!csv.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qDebug("Failed to open csv file.");
    return 1;
  }
  QTextStream out(&csv);
  
  QList<QByteArray> str_list;
  
  while (!res.atEnd()) {
    QByteArray line = res.readLine();
    str_list.push_back(line.trimmed());
    //line.remove(0,5);
    //line=line.trimmed();
    //out << line << ";" << endl;
    //qDebug(str_list.last());
  }
  
  const double vect[]={0.25,5.25,0.25,2.25,0.0};

  while (!str_list.isEmpty()) {
    double min_value=10000000000.0;
    int min_pos=0;
    for(int i=0;i<str_list.size();++i) {
      double value=
            sqrt(((str_list[i].mid(0,1).toDouble()-vect[0])*(str_list[i].mid(0,1).toDouble()-vect[0]))+
            ((str_list[i].mid(1,1).toDouble()-vect[1])*(str_list[i].mid(1,1).toDouble()-vect[1]))+
            ((str_list[i].mid(2,1).toDouble()-vect[2])*(str_list[i].mid(2,1).toDouble()-vect[2]))+
            ((str_list[i].mid(3,1).toDouble()-vect[3])*(str_list[i].mid(3,1).toDouble()-vect[3]))+
            ((str_list[i].mid(4,1).toDouble()-vect[4])*(str_list[i].mid(4,1).toDouble()-vect[4])));
      if (value<min_value) {
        min_value=value;
        min_pos=i;
      }
    }
    out << str_list[min_pos].remove(0,5).trimmed() << ";" << endl;
    str_list.removeAt(min_pos);
  }

  out.flush();
  res.close();
  csv.close();
  return 0;
}

