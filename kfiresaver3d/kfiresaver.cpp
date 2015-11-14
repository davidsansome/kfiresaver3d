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

#include <qgl.h>
//Added by qt3to4:
#include <QTimerEvent>
#include <kconfig.h>
#include <kaudioplayer.h>
#include <math.h>
#include <kstddirs.h>
#include <klocale.h>
#include <qdatetime.h>
#include <qmessagebox.h>
#include <stdlib.h>
#include <sys/time.h>
#include <iostream.h>
#include "kfiresaver.h"
#include "particle.h"


KFireSaver :: KFireSaver( QWidget *parent, const char *name )
	: QGLWidget( parent, name )
{
	QTime midnight( 0, 0, 0 );
	srand( midnight.secsTo(QTime::currentTime()) );

	readConfig();

	if (parameters.enableKDElogo) {
		kdeLogo.setAlphaBuffer(true);
		kdeLogo.load(locate("data","kfiresaver/kde.png"));
	}
	if (parameters.enableTux) {
		tux.setAlphaBuffer(true);
		tux.load(locate("data","kfiresaver/tux.png"));
	}

	if (parameters.enableStars) {
		int number = parameters.starsNumber + 1;
		number *= 10 * number;
		starList.setAutoDelete(true);
		for (int i=0 ; i<number ; i++)
		{
			Particle * star = new Particle;
			star->setDefaultValues( Particle::Star );
			if (parameters.enableStarGradient)
			{
				GLfloat red = star->colour[0],
					green = star->colour[1],
					blue = star->colour[2],
					tint = 0.5 + star->ypos / FIELDYHEIGHT,
					merge = 0.3 + DRAND*0.7,
					mergen = 1 - merge;
				star->colour[0] = red * merge + (1.0-tint) * mergen;
				star->colour[1] = green * merge + tint * mergen;
				star->colour[2] = blue * merge + tint * mergen;
			}
			starList.append( star );
		}
	}

	particleList.setAutoDelete(true);
	if (parameters.enableBottomFire) {
		for (int i=0 ; i<NUMBER_OF_FIREPARTICLES ; i++)
		{
			const int color_conv_tab[4] = { 3, 1, 5, 0 };
			Particle* particle = new Particle;
			particle->setDefaultValues(
				Particle::FireParticle,
				color_conv_tab[parameters.bottomFireColour] );
			particle->zspeed *= 4.0;
			particleList.append(particle);
		}
	}

	if (parameters.enableSound)
		sound_explosion = locate("data","kfiresaver/fw_explode.wav");

	showp.forceBicolour =
	showp.forceColour =
	showp.forcePower =
	showp.forceSparkle =
	showp.forceType = false;
	showp.timeStamp = 0.0;
	startTimer(MSECPERIOD);
}


void KFireSaver :: initializeGL()
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	glShadeModel( GL_SMOOTH );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );

	// Textures
	QImage buf;
	if (!buf.load(locate("data","kfiresaver/particle.bmp")))
	{
		qWarning("Could not read image-particle file, using single-color instead.");
		QImage dummy(0,0,0);
		dummy.fill( Qt::white.rgb() );
		buf = dummy;
	}
	particleTexture = QGLWidget::convertToGLFormat(buf);  // flipped 32bit RGBA
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glEnable( GL_TEXTURE_2D );
	glTexImage2D( GL_TEXTURE_2D, 0, 3, particleTexture.width(), particleTexture.height(), 0,
		  GL_RGBA, GL_UNSIGNED_BYTE, particleTexture.bits() );

	timeval tv;
	gettimeofday(&tv,NULL);
	timeStampFrame = (double)tv.tv_sec + (double)tv.tv_usec/1000000.0;

	unitX = FIELDXWIDTH / (float)width();
	unitY = FIELDYHEIGHT / (float)height();
}


void KFireSaver :: resizeGL( int width, int height )
{
	glViewport( 0, 0, width, height );

	glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 glOrtho( -FIELDX_2, FIELDX_2, -FIELDY_2, FIELDY_2, 5.0, 60.0 );

	glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
     
	unitX = FIELDXWIDTH / (float)width;
	unitY = FIELDYHEIGHT / (float)height;
}


void KFireSaver :: paintGL ()
/* Main procedure. It does the following:
   - calculate time diff between current and previous frame
   - clear the color buffer
   - simple render of stars
   - advanced render of particles
     - render
     - update physics based on time difference
     - check die/change conditions
       - call to explode_firework if a leader dies
   - if random >>> start a new firework
   - if random >>> explode a penquin or kde logo
*/
{
	/* calculate TIME ELAPSED between current and previous frame */
	timeval tv;
	gettimeofday(&tv,NULL);
	double timeCurrent = (double)tv.tv_sec + (double)tv.tv_usec/1000000.0;
	double timeDiff = 0.016;
	if (parameters.enableRealtime)
	{
		timeDiff = timeCurrent - timeStampFrame;
		timeStampFrame = timeCurrent;
		timeDiff = (timeDiff > 0.5) ? 0.5 : (timeDiff < 0.005) ? 0.005 : timeDiff;
	}

	/* CLEAR SCREEN: to do it there are 2 ways */
	
	if (!parameters.enableFade)
	{	// quick - clear the OpenGL color buffer
		glClear( GL_COLOR_BUFFER_BIT );
	}
	else
	{	// good looking
		/* superpose a semi-transparent black rectangle so we
		   can see a sort of 'tail' for each particle drawn. */
		const GLfloat conv_tab[10] = {
			0.50, 0.40, 0.30, 0.20, 0.16,
			0.13, 0.10, 0.07, 0.05, 0.03 };
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glLoadIdentity();
		  glTranslatef( 0.0,0.0, -50.0f);
		  glColor4f(0.0,0.0,0.0, conv_tab[parameters.fadeAmount]);
		  glBegin( GL_TRIANGLE_STRIP );
		    glVertex2f( FIELDX_2, FIELDY_2 );
		    glVertex2f( -FIELDX_2, FIELDY_2 );
		    glVertex2f( FIELDX_2, -FIELDY_2 );
		    glVertex2f( -FIELDX_2, -FIELDY_2 );
		glEnd();
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	}

	/* render STARS */

	if (parameters.enableStars) {
		bool	flickers = parameters.enableStarFlickering,
			fades =  parameters.enableStarFlickering;
		float	alpha = fades ? 0.5 : 1.0;
		for (int i=0; i<(int)starList.count(); i++) {
			Particle * star = starList.at(i);

			if (fades) {
				if (flickers && DRAND<0.6)
					continue;
			} else {
				if (flickers && DRAND<0.2)
					continue;
			}

			glLoadIdentity();
			glTranslatef( star->xpos, star->ypos, -50.0 );
			GLfloat size = star->pixelSize;
			glScalef( size, size, size );
			glColor4f(star->colour[0], star->colour[1], star->colour[2], alpha);
		
			glBegin( GL_TRIANGLE_STRIP );
			  glTexCoord2d( 1, 1 ); 	/* Top Right */
			  glVertex2f( unitX, unitY );
			  glTexCoord2d( 0, 1 ); 	/* Top Left */
			  glVertex2f( -unitX, unitY );
			  glTexCoord2d( 1, 0 ); 	/* Bottom Right */
			  glVertex2f( unitX, -unitY );
			  glTexCoord2d( 0, 0 ); 	/* Bottom Left */
			  glVertex2f( -unitX, -unitY );
			glEnd();
		}
	}

        /* render FIREWORKS */
	
	for (int i=0 ; i<(int)particleList.count() ; i++)
	{
		Particle * particle = particleList.at(i);

		glLoadIdentity();
		//perspective projection (could be done directly by opengl.. :-)
		if (PERSP_MAG_FACTOR*particle->ypos < -246.0) {
		    particleList.remove( i-- );
		    continue;
		}
		GLfloat	posx, posy,
			sfactor = 256.0 / (256.0 + PERSP_MAG_FACTOR*particle->ypos);
		glTranslatef(	posx = (particle->xpos * sfactor),
				posy = (particle->zpos * sfactor - 4.0),
				-50.0	);
		if (parameters.enableMegaFlares) {
			if ((sfactor=parameters.megaFlares*particle->ypos) < -254.0) {
				particleList.remove( i-- );
				continue;
			}
			sfactor = 256.0 / (256.0 + sfactor);
		}
		GLfloat size = particle->pixelSize * sfactor;
		glScalef( size, size, size );

		//determine brightness (alpha component) for the particle
		if (!particle->useLife) {
			//if particle doesn't use life so brightness (alpha) is 1.0
			glColor4f(particle->colour[0], particle->colour[1],
				particle->colour[2], 1.0 );
		} else {
			//bright changes with the following curve: "2*k - k^2" (or "k(2-k)")
			GLfloat alpha,
				life = particle->life,
				startLife = particle->startLife;
			if ( life > startLife )
				alpha = startLife + 1 - life;
			else
				alpha = life / startLife;
			//apply flickering if enabled
			if (parameters.enableSparkle) {
			    if (particle->flicker < 0) {
				alpha = 0.2;
				if (++particle->flicker >= 0)
					particle->flicker = FLICKER_FRAMES_DELAY;
			    } else if (particle->flicker > 0) {
				if ( life <= startLife )
					alpha = 1.0;
				if (--particle->flicker <= 0)
					particle->flicker = -FLICKER_FRAMES_DELAY;
			    }
			}
			glColor4f(particle->colour[0], particle->colour[1],
				particle->colour[2], alpha * (2 - alpha));
		}

		//at this time parameters are set, so draw the particle
		glBegin( GL_TRIANGLE_STRIP );
		  glTexCoord2d( 1, 1 ); 	/* Top Right */
		  glVertex2f( unitX, unitY );
		  glTexCoord2d( 0, 1 ); 	/* Top Left */
		  glVertex2f( -unitX, unitY );
		  glTexCoord2d( 1, 0 ); 	/* Bottom Right */
		  glVertex2f( unitX, -unitY );
		  glTexCoord2d( 0, 0 ); 	/* Bottom Left */
		  glVertex2f( -unitX, -unitY );
		glEnd();

		particle->updateParameters( timeDiff );

		switch (particle->particleType)
		{
			//a Fireparticle is restarted when in right conditions
		    case Particle::FireParticle:
			if ( posx < -FIELDX_2 || posx > FIELDX_2 ||
				(particle->zpos < -10.0 && posy < -FIELDY_2) )
				particle->setDefaultValues( Particle::FireParticle, -1);
			break;

			//a leader explodes when his z speed drops to zero
			//or, if it uses life, at death
		    case Particle::FireWorkLeaderParticle:
			if ((particle->zspeed <= 0.0f && !particle->useLife) ||
			    (particle->useLife && particle->life <= 0.0) )
			{
				if (parameters.enableSound)
					KAudioPlayer::play(sound_explosion);
				explodeFirework(particle);
				particleList.remove(i--);
			}
			break;

			//remove if dead or outside field
		    case Particle::KdeLogoParticle:
		    case Particle::FireWorkDebrisParticle:
			if (particle->life <= 0.0 || posx<-FIELDX_2 || posx>FIELDX_2)
				particleList.remove(i--);
			break;

			//can't be that case. inserted only to remove warning
		    case Particle::Star:
			break;

		}
	}

	/* generate a new FIREWORK_LEADER */

	int random = (int) ((float)parameters.fireworksFrequency * DRAND);
	if (showp.ShowType == Show)
	{
		//double the chances ('frequency') to raise a new leaderParticle
		//but envelope it under a sine function
		float step = (showp.timeStamp - timeCurrent) / showp.timeGap;
		if (DRAND > sin(M_PI*step))
			random = -1;
		if (showp.type == Particle::AngelHairs && DRAND < 0.5)
			random = -1;
	}
	if ( !random )
	{
		Particle * particle = new Particle;
		particle->setDefaultValues( Particle::FireWorkLeaderParticle );
		particleList.append( particle );
	}

	/* EXPLODE a Tux or Kde image */
	
	if (parameters.enableTux || parameters.enableKDElogo) {
		random = (int) ((float)parameters.logoFrequency * DRAND * 200.0);
		if (random == 0)
		{
			if (parameters.enableFlash) {
				glClearColor( 0.5, 0.5, 0.5, 1.0 );
				glClear( GL_COLOR_BUFFER_BIT );
				glClearColor( 0.0, 0.0, 0.0, 1.0 );
			}
			if (parameters.enableTux && parameters.enableKDElogo)
				random = (int) (DRAND * 2.0);
			else if (parameters.enableTux)
				random = 1;
			else
				random = 0;
			if (random == 1)
				burnLogo(tux);
			else
				burnLogo(kdeLogo);
		}
	}
}


int KFireSaver :: pickColour()
{
	int color = (int) (DRAND * parameters.colorsCount);
	return parameters.colorsT[ color ];
}


int KFireSaver :: pickType()
{
	int type = (int) (DRAND * parameters.typesCount);
	return parameters.typesT[ type ];
}


void KFireSaver :: explodeFirework(Particle* leaderParticle)
{
	bool bicolor = DRAND > 0.95,			// 1/20 is bi-colored
	     flickers = DRAND > 1.00;			// 1/20 flickers
	int cscheme,
	    cscheme2 = 0,
	    number;
	GLfloat power,
		powermin,
		displace[3] = {0.0,0.0,0.0};
	float tmp1 = 0.0, tmp2 = 0.0, tmp3 = 0.0, tmp4 = 0.0, tmp5 = 0.0;
	Particle::FireworkType fwType;

	/* colour of exploded particles */
	cscheme = showp.forceColour ? showp.colour : pickColour();
	bicolor = (bicolor || showp.forceBicolour) && parameters.enableCombos;
	if (bicolor)
		cscheme2 = showp.forceColour ? showp.coloursec : pickColour();

	/* randomize type of exploding firework - see FireworkType in particle.h */
	fwType = !showp.forceType ?
		(enum Particle::FireworkType) pickType() :
		(enum Particle::FireworkType) showp.type;

	/* other options for generated particles */
	number = (int) (DRAND * 150.0 + DRAND * 150.0);
	power = showp.forcePower ?
		showp.powerEnvelope * (0.8 + 0.3*DRAND) :
		DRAND * 11.0 + 2.0;
	powermin = DRAND * power;

	/* now some rules ... */
        //a splitter can't split up again
	if (fwType == Particle::Splitter && leaderParticle->fireworkType == Particle::Splitter) {
		if (parameters.typesCount == 1)
			return;
		if (showp.forceType)
			fwType = (enum Particle::FireworkType) showp.typesec;
		while ( fwType == Particle::Splitter )
			fwType = (enum Particle::FireworkType) pickType();
	}

	if (parameters.enableFlash) {
		if ( fwType != Particle::NoFW ) {
			glClearColor( 0.5, 0.5, 0.5, 1.0 );
			glClear( GL_COLOR_BUFFER_BIT );
			glClearColor( 0.0, 0.0, 0.0, 1.0 );
		}
	}

	/* PRE-ADJUST parameters for selected type of firework */
	switch ( fwType )
	{
		//explosion whithout emitting particles, only a flash
	    case Particle::NoFW:
		flickers = false;
		number = 1;
		power = powermin = 0;
		break;
		
		//no need to handle this. it's the default configuration.
	    case Particle::Sphere:
		break;

		//splits up into 'number' orange pieces. tmp1 holds base_life
	    case Particle::Splitter:
		cscheme = showp.forceColour ? showp.colour : 1;
		flickers = bicolor = false;
		number = 3 + (int) (DRAND * 4);
		power /= 2.0;
		powermin = power / 2.0;
		tmp1 = 0.4 + DRAND * 1.5;
		break;
		
		//randomize a couple of angles (phi - theta) for exploding circle
	    case Particle::BiCircle:
		number *= 2;
	    case Particle::Circle:
		flickers = false;
		power = DRAND * 5.0 + 4.0;
		tmp1 = DRAND * M_PI;
		tmp2 = DRAND * M_PI;
		tmp4 = cos(tmp2);	//c2
		tmp3 = sin(tmp2);	//s2
		tmp2 = cos(tmp1);	//c1
		tmp1 = sin(tmp1);	//s1
		break;

		//cascade of flickering orange particles
	    case Particle::AngelHairs:
		cscheme = showp.forceColour ? showp.colour : 1;
		bicolor = false;
		flickers = true;
		power = 0.8 + DRAND * 1.9;
		powermin = DRAND*0.5;
		number = 100 + (int)(DRAND * 150);
		displace[0] = -leaderParticle->xspeed/2;
		displace[1] = -leaderParticle->yspeed/2;
		displace[2] = power;
		break;

		//not yet implemented
	    case Particle::Fountain:    

	    case Particle::SuperNova:

	    case Particle::Daisy:
    
	    case Particle::Love:
		break;

	    case Particle::NoRender:
		number = 0;
		break;
	}

	for (int i=0 ; i<number ; i++)
	{
		Particle * particle = new Particle;
		particle->setDefaultValues (
			Particle::FireWorkDebrisParticle,
			bicolor && (i>number/2) ? cscheme2 : cscheme,
			leaderParticle, powermin, power,
			flickers, displace );

		// POST-ADJUST particle coefficients adapting to current FireworkType
		switch ( particle->fireworkType = fwType )
		{
			//create a big, white particle, simulating explosion
		    case Particle::NoFW:
			if (!parameters.enableFade)
				particle->startLife = particle->life = 0.075;
			else
				particle->startLife = particle->life = 0.030;
			particle->colour[0]=
			particle->colour[1]=
			particle->colour[2]=1.0;
			particle->pixelSize = 50.0 + 75.0 * DRAND;
			particle->zacc = 0;
			break;

			//default. no need to change parameters
		    case Particle::Sphere:
			if (i==0 && parameters.enableSphereLight) {
				particle->xspeed = leaderParticle->xspeed;
				particle->yspeed = leaderParticle->yspeed;
				particle->zspeed = 0.0;
				particle->colour[0] /= 2.0;
				particle->colour[1] /= 2.0;
				particle->colour[2] /= 2.0;
				float impression = power * (float)number/5.0;
				particle->pixelSize = 25.0 * DRAND + impression;
				if (parameters.enableFade) {
					particle->startLife = particle->life = 0.040;
				} else {
					particle->startLife = 1.3;
					particle->life = 1.8;
				}
			}
			break;

			//
		    case Particle::Splitter:
			particle->particleType = Particle::FireWorkLeaderParticle;
			particle->pixelSize *= 3.0;
			particle->startLife = particle->life = tmp1 * (0.75 + DRAND/3.0);
			if (particle->zspeed < 0)
				particle->zspeed = -particle->zspeed;
			break;

		    case Particle::Circle:
		    case Particle::BiCircle:
			tmp5 = 2 * M_PI * DRAND;
			//MMX can be useful.. if you know how to use it :-)
			if ( fwType == Particle::BiCircle && i > number/2 ) {
				GLfloat ey = cos(tmp5),
					ez = sin(tmp5);
				particle->xspeed = power * (                tmp3*ez );
				particle->yspeed = power * ( tmp2*ey - tmp1*tmp4*ez );
				particle->zspeed = power * ( tmp1*ey + tmp2*tmp4*ez );
			} else {
				GLfloat ex = sin(tmp5),
					ey = cos(tmp5);
				particle->xspeed = power * (       tmp4*ex           );
				particle->yspeed = power * (  tmp1*tmp3*ex + tmp2*ey );
				particle->zspeed = power * ( -tmp2*tmp3*ex + tmp1*ey );
			}
			break;

		    case Particle::AngelHairs:
			particle->zacc = -9.807 * (0.05 + DRAND*0.20);
			particle->life = 2.0 + DRAND*2.5;
			particle->startLife = particle->life - 1;
			if (particle->zspeed < 0)
				particle->zspeed *= -1;
			//particle->pixelSize = 5.0;
			break;

		    case Particle::Fountain:

		    case Particle::SuperNova:

		    case Particle::Daisy:

		    case Particle::Love:
			break;

			//can't be that case. inserted only to remove warning
		    case Particle::NoRender:
			break;
		}
		particleList.append(particle);
	}
}

void KFireSaver :: timerEvent(QTimerEvent*)
{
	timeval tv;
	gettimeofday(&tv,NULL);
	double currentTime = (double)tv.tv_sec + (double)tv.tv_usec/1000000.0;

	bool	chooseType = false,
		chooseColor = false,
		chooseOthers = false,
		updateTimings = false;
	bool	firstTime = showp.timeStamp == 0.0;
	bool	endOfScene = currentTime >= showp.timeStamp;

	if (firstTime)
	switch (showp.ShowType)
	{
	    case Monotype:
		/* first time choose the type, color and attributes will
		   be choosed randomly for every firework which explodes*/
		showp.forceType = true;
		chooseType = true;
		break;

	    case Monochrome:
		/* first time choose the color, type and attributes will
		   be choosed randomly for every firework which explodes*/
		showp.forceColour = true;
		chooseColor =
		chooseOthers = true;
		break;

	    default: break;
	}

	if (endOfScene || firstTime)
	switch (showp.ShowType)
	{
	    case Show:
		/* if a scene ended, randomize global parameters for the
		   whole next scene */
		showp.forceType = true;
		showp.forceColour = true;
		showp.forcePower = true;
		chooseOthers =
		chooseColor =
		chooseType = true;
		updateTimings = true;
		break;

	    default: break;
	}

	if ( chooseType )
	{
		showp.type = pickType();
		if (parameters.typesCount < 2)
			showp.typesec = Particle::NoRender;
		else
			while ((showp.typesec = pickType()) == showp.type);
	}
	if ( chooseColor ) {
		showp.colour = pickColour();
		showp.coloursec = pickColour();
	}
	if ( chooseOthers )
	{
		showp.powerEnvelope = DRAND * 8.0 + 3.0;
		if (DRAND > 0.9)
		{
			showp.forceBicolour = true;
			showp.coloursec = pickColour();
		} else
			showp.forceBicolour = false;
		if (DRAND > 0.9)
			showp.forceSparkle = true;
		else
			showp.forceSparkle = false;
	}
	if ( firstTime || updateTimings )
	{
		if (DRAND < 0.2)
			showp.timeGap = 1.0 + DRAND * 2.0;
		else
			showp.timeGap = 3.0 + DRAND * 10.0;
		showp.timeStamp = currentTime + showp.timeGap;
		showp.timeGap /= 1.5; //hack to introduce delay in sine func
	}

	updateGL();
}

void KFireSaver :: burnLogo(QImage image)
{
	int step = 1;
	if (parameters.enableReduceLogo)
		step = 2;
	for (int y=0 ; y<image.height() ; y+=step)
	{
		for (int x=0 ; x<image.width() ; x+=step)
		{
			if ((qBlue(image.pixel(x,y)) == 255) &&
				(qRed(image.pixel(x,y)) == 0) &&
				(qGreen(image.pixel(x,y)) == 0))
				continue;

			Particle* particle = new Particle;
			particle->xpos = x*unitX + DRAND * 0.2f - 0.1f;
			particle->zpos = y*unitY + DRAND * 0.2f + 2.0f;
			particle->xspeed = 0.1 * (float)(x-(image.width()/2));
			// + DRAND * 0.2f - 0.1f;
			particle->zspeed = 0.1 * (float)(y-(image.height()/2));
			// + DRAND * 0.2f - 0.1f;
			particle->ypos = 0;
			particle->yspeed = DRAND * 8.0f - 4.0f;
			particle->zacc = -9.807f / 5.0f;
			particle->colour[0] = qRed(image.pixel(x,y)) / 255.0f;
			particle->colour[1] = qGreen(image.pixel(x,y)) / 255.0f;
			particle->colour[2] = qBlue(image.pixel(x,y)) / 255.0f;
			particle->useLife = true;
			particle->startLife = particle->life = 2.5f;
			particle->pixelSize = 4;
			particle->flicker = 0;
			particle->particleType = Particle::KdeLogoParticle;
			particleList.append(particle);
		}
	}
}

void KFireSaver :: readConfig ()
{
	KConfig config("kfiresaverrc",true,false);
	/* fireworks */
	parameters.enableNoFW = config.readBoolEntry("enableNoFW",false);
	parameters.enableSphere = config.readBoolEntry("enableSphere",true);
	parameters.enableSplitter = config.readBoolEntry("enableSplitter",false);
	parameters.enableCircle = config.readBoolEntry("enableCircle",false);
	parameters.enableBiCircle = config.readBoolEntry("enableBiCircle",false);
	parameters.enableCascade = config.readBoolEntry("enableCascade",false);
	parameters.enableFountain = config.readBoolEntry("enableFountain",false);
	parameters.enableNova = config.readBoolEntry("enableNova",false);
	parameters.enableDaisy = config.readBoolEntry("enableDaisy",false);
	parameters.enableLove = config.readBoolEntry("enableLove",false);
	parameters.fireworksFrequency = config.readNumEntry("fireworksFrequency",15);
	/* colors */
	parameters.enableRed = config.readBoolEntry("enableRed",false);
	parameters.enableOrange = config.readBoolEntry("enableOrange",true);
	parameters.enableGreen = config.readBoolEntry("enableGreen",false);
	parameters.enableBlue = config.readBoolEntry("enableBlue",false);
	parameters.enableWhite = config.readBoolEntry("enableWhite",true);
	parameters.enablePurple = config.readBoolEntry("enablePurple",false);
	parameters.enableDeepGreen = config.readBoolEntry("enableDeepGreen",true);
	parameters.enableCombos = config.readBoolEntry("enableCombos",true);
	parameters.enableSparkle = config.readBoolEntry("enableSparkle",true);
	/* misc */
	showp.ShowType = (enum enumShowType)config.readNumEntry("showType",0);
	parameters.enableStars = config.readBoolEntry("enableStars",true);
	parameters.enableStarFlickering = config.readBoolEntry("enableStarsFlickering",false);
	parameters.enableStarGradient = config.readBoolEntry("enableStarsGradient",true);
	parameters.enableFlash = config.readBoolEntry("enableFlash",false);
	parameters.enableBottomFire = config.readBoolEntry("enableBottomFire",true);
	parameters.enableFade = config.readBoolEntry("enableFade",false);
	parameters.enableMegaFlares = config.readBoolEntry("enableMegaFlares",true);
	parameters.enableSphereLight = config.readBoolEntry("enableSphereLight",true);
	parameters.enableClouds = config.readBoolEntry("enableClouds",false);
	parameters.enableCloudsLight = config.readBoolEntry("enableLightingClouds",false);
	parameters.enableSound = config.readBoolEntry("enableSound",true);
	parameters.enableTrails = config.readBoolEntry("enableTrails",false);
	parameters.enableTux = config.readBoolEntry("enableTux",false);
	parameters.enableKDElogo = config.readBoolEntry("enableKdeLogo",false);
	parameters.enableReduceLogo = config.readBoolEntry("enableReduceLogo",true);
	parameters.enableRealtime = config.readBoolEntry("enableRealtime",true);
	parameters.starsNumber = config.readNumEntry("starsNumber",4);
	parameters.fadeAmount = config.readNumEntry("fadeAmount",3);
	parameters.megaFlares = config.readNumEntry("megaFlares",17);
	parameters.logoFrequency = config.readNumEntry("logoFrequency",5);
	parameters.bottomFireColour = config.readNumEntry("bottomFireColour",2);

	/* check for correctness of parameters and make some fixes */
	/* check for correctness of parameters and make some fixes */
	
	if (!parameters.logoFrequency)
		parameters.enableTux = parameters.enableKDElogo = false;
	else
		parameters.logoFrequency = 11 - parameters.logoFrequency;

	parameters.fireworksFrequency = 21 - parameters.fireworksFrequency;
	if (parameters.fireworksFrequency < 1)
		parameters.fireworksFrequency = 1;
	if (parameters.fireworksFrequency > 20)
		parameters.fireworksFrequency = 20;
	//good *karl gauss sum* curve ^_^
	parameters.fireworksFrequency *= (parameters.fireworksFrequency + 1);
	parameters.fireworksFrequency /= 2;
		
	if (parameters.bottomFireColour < 0)
		parameters.bottomFireColour = 0;
	if (parameters.bottomFireColour > 3)
		parameters.bottomFireColour = 3;

	if (parameters.fadeAmount < 0)
		parameters.fadeAmount = 0;
	if (parameters.fadeAmount > 9)
		parameters.fadeAmount = 9;

	if (parameters.megaFlares < 10)
		parameters.megaFlares = 10;
	if (parameters.megaFlares > 26)
		parameters.megaFlares = 26;

	parameters.colorsCount = 0;
	if (parameters.enableRed)
		parameters.colorsT[parameters.colorsCount++] = 0;
	if (parameters.enableOrange)
		parameters.colorsT[parameters.colorsCount++] = 1;
	if (parameters.enableGreen)
		parameters.colorsT[parameters.colorsCount++] = 2;
	if (parameters.enableBlue)
		parameters.colorsT[parameters.colorsCount++] = 3;
	if (parameters.enableWhite)
		parameters.colorsT[parameters.colorsCount++] = 4;
	if (parameters.enablePurple)
		parameters.colorsT[parameters.colorsCount++] = 5;
	if (parameters.enableDeepGreen)
		parameters.colorsT[parameters.colorsCount++] = 6;
	if ( !parameters.colorsCount )
	{
		cout << "KFireSaver3D: Warning enable at least one color" << endl;
		cout << "    enabling 'Blinding White'" << endl;
		
		parameters.colorsCount = 1;
		parameters.colorsT[0] = 4;
		KConfig modconfig("kfiresaverrc",false,false);
		modconfig.writeEntry("enableWhite", true);
	}
	parameters.colorsT[ parameters.colorsCount ] =
		parameters.colorsT[ parameters.colorsCount-1 ];

	parameters.typesCount = 0;
	if (parameters.enableNoFW)
		parameters.typesT[parameters.typesCount++] = 0;
	if (parameters.enableSphere)
		parameters.typesT[parameters.typesCount++] = 1;
	if (parameters.enableSplitter)
		parameters.typesT[parameters.typesCount++] = 2;
	if (parameters.enableCircle)
		parameters.typesT[parameters.typesCount++] = 3;
	if (parameters.enableBiCircle)
		parameters.typesT[parameters.typesCount++] = 4;
	if (parameters.enableCascade)
		parameters.typesT[parameters.typesCount++] = 5;
	if (parameters.enableFountain)
		parameters.typesT[parameters.typesCount++] = 6;
	if (parameters.enableNova)
		parameters.typesT[parameters.typesCount++] = 7;
	if (parameters.enableDaisy)
		parameters.typesT[parameters.typesCount++] = 8;
	if (parameters.enableLove)
		parameters.typesT[parameters.typesCount++] = 9;
	if ( !parameters.typesCount ) {
		cout << "KFireSaver3D: Warning, no fireworks enabled in config file" << endl;
		cout << "    enabling 'Classic Spherical'" << endl;

		parameters.typesCount = 1;
		parameters.typesT[0] = 1;
		KConfig modconfig("kfiresaverrc",false,false);
		modconfig.writeEntry("enableSphere", true);
	}
	parameters.typesT[ parameters.typesCount ] =
		parameters.typesT[ parameters.typesCount-1 ];
}
