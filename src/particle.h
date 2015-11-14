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

#ifndef PARTICLE_H
#define PARTICLE_H

#define FLICKER_FRAMES_DELAY 8
#define DRAND ((float)rand() / (float)RAND_MAX)  /*random float between 0 and 1*/

class Particle
{
public:

//enum definitions for ParticleType and FireworkType
	enum ParticleType
	{
		FireParticle,
		FireWorkLeaderParticle,
		FireWorkDebrisParticle,
		KdeLogoParticle,
		Star
	};
	enum FireworkType
	{
		NoFW = 0,
		Sphere = 1,
		Splitter = 2,
		Circle = 3,
		BiCircle = 4,
		AngelHairs = 5,
		Fountain = 6,
		SuperNova = 7,
		Daisy = 8,
		Love = 9,
		NoRender = 10
	};

//public methods for setting default parameters and update them using physical interacions
	void setDefaultValues (
		ParticleType pt,
		int color_scheme = 0,
		Particle* leader = NULL,
    float powermin = 5.0,
    float powermax = 10.0,
		bool flickers = false,
    float *displace = NULL );

	void updateParameters ( double dTime );

//public accessible variables of the class	
	ParticleType particleType;
	FireworkType fireworkType;
	
  float	xpos,	ypos,	zpos,
		xspeed,	yspeed,	zspeed,
		zacc;
		
  float colour[3],
		life, startLife,
		pixelSize;
		
	bool useLife;
	int flicker;
};

#endif

