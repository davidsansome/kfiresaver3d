//     This file is part of KFireSaver.

//     KFireSaver is free software; you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation; either version 2 of the License, or
//     (at your option) any later version.

//     KFireSaver is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.

//     You should have received a copy of the GNU General Public License
//     along with KFireSaver; if not, write to the Free Software
//     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


//     Author: David Sansome
//     Email:  me@davidsansome.com

#include "kfiresaverkss.h"
#include "kfiresaver.h"

KFireSaverKSS::KFireSaverKSS(WId id)
	: KScreenSaver( id )
{
	setBackgroundColor( black );
	erase();
	saver = new KFireSaver;
	embed(saver);
	saver->show();
}

KFireSaverKSS::~KFireSaverKSS()
{
	delete saver;
}
