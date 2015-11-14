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

#include <cmath>
#include <cstdlib>
#include <iostream>
#include "particle.h"
#include "kfiresaver.h"

void Particle :: setDefaultValues (
	ParticleType pt,
	int cs,
	Particle* leader,
	GLfloat powermin, GLfloat powermax,
	bool flickers,
	GLfloat *displace )
//note:	this function is called when a particle needs a set of default parameters.
//	these depends on the ParticleType that is the first parameter passed to that
//	function:
//	-- FireParticle
//		born in a rectangle centered in { 0, 0, -9.9 }
//		speed 3-6 [m/s] blue/cyan colored
//		this is only done at the beginning or when a particle dies
//	-- FireWorkLeaderParticle
//		they start in a rectangle at the same height but
//		with different power and the same 'orange' colour
//	-- FireWorkDebrisParticle
//		parameters are randomized for a 'spherical' explosion.
//		power{min,max}, flickers and displace applies only for that
//		kind of ParticleType.
{
	//current color scheme		 red  orng grn  blue w  m  c
	const GLfloat c_red_min[7] =   { 0.4, 0.9,   0,   0, 1, 0, 0 };
	const GLfloat c_red_max[7] =   {   1,   1,   0,   0, 1, 1, 0 };
	const GLfloat c_green_min[7] = {   0, 0.4, 0.4,   0, 1, 0, 0 };
	const GLfloat c_green_max[7] = {   0, 0.5,   1, 0.5, 1, 0, 1 };
	const GLfloat c_blue_min[7] =  {   0, 0.1,   0, 0.5, 1, 0, 0 };
	const GLfloat c_blue_max[7] =  {   0, 0.2,   0,   1, 1, 1, 1 };

	particleType = pt;
	fireworkType = NoFW;

	//if flickers is set the current visible delay is randomized
	flicker = flickers ?
		(int) ((DRAND * 2.0 - 1.0) * (float)FLICKER_FRAMES_DELAY) : 0;

	switch (particleType)
	{
	    case FireParticle:
		zpos = -9.9;
		zspeed = DRAND * 3.0 + 3.0;
		zacc = -9.807;

		xpos = DRAND * FIELDXWIDTH - FIELDX_2;
		xspeed = DRAND * 4.0 - 2.0;

		ypos = DRAND - 2.0;
		yspeed = DRAND * 2.0;

		if (cs != -1) {
			//randomize the color choosing on current palette
			colour[0] = c_red_min[cs] + (c_red_max[cs]-c_red_min[cs]) * DRAND;
			colour[1] = c_green_min[cs] + (c_green_max[cs]-c_green_min[cs]) * DRAND;
			colour[2] = c_blue_min[cs] + (c_blue_max[cs]-c_blue_min[cs]) * DRAND;
		}
		
		useLife = false;
		pixelSize = 2.0 + DRAND * 2.0;

		break;

	    case FireWorkLeaderParticle:
		zpos = -9.9;
		zspeed = 18.0 + DRAND * 6.5;
		zacc = -9.807;

		xpos = DRAND * 14.0 - 7.0;
		xspeed = DRAND * 8.0 - 4.0 - (xpos / 2.0)*DRAND;

		ypos = DRAND * 2.0 - 1.0;
		yspeed = DRAND * 8.0 - 4.0;

		colour[0] = 1.0;
		colour[1] = DRAND * 0.6;
		colour[2] = 0.0;

		useLife = false;
		pixelSize = 5;

		break;

	    case KdeLogoParticle:
		//cout << "KFireSaver3d:particle.cpp >> can't reach that point!\n" << endl;
		break;

	    case Star:
		colour[0] = DRAND * 0.2 + 0.5;
		colour[1] = DRAND * 0.2 + 0.5;
		colour[2] = DRAND * 0.2 + 0.5;
		
		{bool accepted = false;
		while (!accepted) {
			float module = 30,
			      theta = DRAND * M_PI * 2.0,
			      u = DRAND * 2.0 - 1.0,
			      root = sqrt( 1 - u*u );
			xpos = module * root * cos(theta);
			ypos = fabs(module * root * sin(theta)) - 10.0;
			zpos = fabs(module * u);
        
			float sfactor = 256.0 / (256.0 + PERSP_MAG_FACTOR*ypos);
			xpos *= sfactor;
			ypos = zpos * sfactor - 12.0;

			pixelSize = 2.0 + 3.0*DRAND;
			pixelSize *= sfactor;

			accepted = xpos > -FIELDX_2 && xpos < FIELDX_2 &&
				   ypos > -FIELDY_2 && ypos < FIELDY_2;
		}}
		break;

	    case FireWorkDebrisParticle:
	
		//same origin of the dead leader
		xpos = leader->xpos;
		ypos = leader->ypos;
		zpos = leader->zpos;

		//true spherical randomization
		float module = powermin + DRAND * (powermax - powermin),
		      theta = DRAND * M_PI * 2.0,
		      u = DRAND * 2.0 - 1.0,
		      root = sqrt( 1 - u*u );
		xspeed = leader->xspeed + module * root * cos(theta) * (1.0 + DRAND/3.0);
		yspeed = leader->yspeed + module * root * sin(theta) * (1.0 + DRAND/3.0);
		zspeed = module * u * (1.0 + DRAND/3.0);	//was 0.9 + DRAND/3

		//if set add a displace to speed
		if (displace != NULL) {
			xspeed += displace[0];
			yspeed += displace[1];
			zspeed += displace[2];
		}

		//randomize the color choosing on current palette
		colour[0] = c_red_min[cs] + (c_red_max[cs]-c_red_min[cs]) * DRAND;
		colour[1] = c_green_min[cs] + (c_green_max[cs]-c_green_min[cs]) * DRAND;
		colour[2] = c_blue_min[cs] + (c_blue_max[cs]-c_blue_min[cs]) * DRAND;

		pixelSize = DRAND * 2.0 + 2.0;
		zacc = -9.807 / (6.0 - pixelSize);

		useLife = true;
		life = startLife = pixelSize / 2.0;
		break;
	}
}


void Particle :: updateParameters( double deltaTime )
//note:	this procedure uses a reduced set of parameters
//	x and y axis acceleration is removed in this version
//	the only external iterations are:
//	- the g force
//	- a sort of air friction that limits speed in x,y and
//	  acceleration on z
{
	xpos += xspeed * deltaTime;
	ypos += yspeed * deltaTime;
	zpos += zspeed * deltaTime + (zacc * deltaTime*deltaTime) /2;

	zspeed += zacc * deltaTime;

	xspeed *= 0.998;
	yspeed *= 0.998;
	zspeed *= 0.999;

	if (useLife)
	    life -= deltaTime;
}
