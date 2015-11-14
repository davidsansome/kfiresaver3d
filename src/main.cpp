//     This file is part of KFireSaver3D.

//     KFireSaver3D is free software; you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation; either version 2 of the License, or
//     (at your option) any later version.

//     KFireSaver3D is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.

//     You should have received a copy of the GNU General Public License
//     along with KFireSaver3D; if not, write to the Free Software
//     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


//     Author: Enrico Ros, based on the great work of David Sansome (kfiresaver)
//     Email:  asy@libero.it

#include "kfiresaver.h"

#include <QApplication>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  app.setOrganizationName("David Sansome");
  app.setOrganizationDomain("www.davidsansome.com");
  app.setApplicationName("kfiresaver3d");

  KFireSaver fs;
  fs.show();

  return app.exec();
}
