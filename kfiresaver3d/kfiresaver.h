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

#ifndef KFIRESAVER_H
#define KFIRESAVER_H

#define PERSP_MAG_FACTOR 8.0
#define NUMBER_OF_FIREPARTICLES 180

#define MSECPERIOD 16.667	// 1000s / 60fps = 16.667 [ms/frame]
#define FIELDXWIDTH 30.0
#define FIELDYHEIGHT 30.0

#define FIELDX_2 FIELDXWIDTH/2.0
#define FIELDY_2 FIELDYHEIGHT/2.0

#include <qgl.h>
#include <qptrlist.h>
#include <qimage.h>
#include <qstring.h>
#include <qevent.h>

class Particle;

class KFireSaver : public QGLWidget
{
public:
	KFireSaver( QWidget *parent=0, const char *name=0 );

protected:
	void initializeGL();
	void resizeGL( int, int );
	void paintGL();
	void timerEvent( QTimerEvent * );

private:
	int pickColour();
	int pickType();
	void readConfig();
	void explodeFirework(Particle* fireWorkLeaderParticle);
	void burnLogo(QImage image);

	QString	sound_explosion;
//		sound_debris;
//		sound_sparkle;

	QImage	kdeLogo,
		tux,
		particleTexture;
//		starTexture;
//		noveTexture;
//		cometTexture;

	QPtrList<Particle>
		particleList,
		starList;

	float	unitX,
		unitY;

	double	timeStampFrame;

	struct {
	   bool	enableStars,
		enableStarFlickering,
		enableStarGradient,
		enableBottomFire,
		enableFade,
		enableMegaFlares,
		enableSphereLight,
		enableClouds,
		enableCloudsLight,
		enableSound,
		enableFlash,
		enableSparkle,
		enableCombos,
		enableTrails,
		enableTux,
		enableKDElogo,
		enableReduceLogo,
		enableRealtime;
	   bool	enableRed,
		enableOrange,
		enableGreen,
		enableBlue,
		enableWhite,
		enablePurple,
		enableDeepGreen;
	   bool	enableNoFW,
		enableSphere,
		enableSplitter,
		enableCircle,
		enableBiCircle,
		enableCascade,
		enableFountain,
		enableNova,
		enableDaisy,
		enableLove;
	   int	starsNumber,
		fadeAmount,
		megaFlares,
		fireworksFrequency,
		logoFrequency,
		bottomFireColour;
	   int	colorsCount,
		colorsT[8],
		typesCount,
		typesT[11];
	} parameters;
	enum enumShowType {
		Random = 0,
		Monotype = 1,
		Monochrome = 2,
		Show = 3
	};
	struct {
	enumShowType
		ShowType;
	int	colour,
		coloursec,
		type,
		typesec;
	float	powerEnvelope;
	double	timeStamp,
		timeGap;
	bool	forceBicolour,
		forceColour,
		forcePower,
		forceSparkle,
		forceType;
	} showp;
};

#endif
