/*     This file is part of KFireSaver3D.
 *
 *     KFireSaver3D is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 *
 *     KFireSaver3D is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with KFireSaver3D; if not, write to the Free Software
 *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 *     Authors:
 *       David Sansome <me@davidsansome.com>
 *       KoRaL <asy@libero.it>
 *
 *     (see the changelog for more information)
 */

#include <qcheckbox.h>
#include <kconfig.h>
#include <klocale.h>
#include <unistd.h>

void KFireSaverSetup::init()
{
	readConfig();
	fireSaverWidget = NULL;
	previewAttached = true;
	previewLabel->hide();
	updatePreview(false);
}

void KFireSaverSetup::updatePreview( bool save )
{	
    if (save)
	writeConfig();
    if ( fireSaverWidget != NULL )
	delete fireSaverWidget;
    usleep(500000);
    if (previewAttached) {
	fireSaverWidget = new KFireSaver( PreviewKFSFrame );
	fireSaverWidget->move(1,1);
	fireSaverWidget->resize(200,150);
    } else {
	fireSaverWidget = new KFireSaver(NULL);
	fireSaverWidget->resize(640,480);
    }
    fireSaverWidget->show();
}

void KFireSaverSetup::okButton_clicked()
{
    writeConfig();
    if (fireSaverWidget != NULL)
	delete fireSaverWidget;
/*    int xx = x(), yy = y(), hh = height();
    while ( yy > -height ) {
	yy--;
	move ( xx, yy );
	repaint();
    }
*/
    accept();
}


void KFireSaverSetup::updateButton_clicked()
{
    updatePreview( true );
}

void KFireSaverSetup::writeConfig()
{
	KConfig config("kfiresaverrc",false,false);

	/* fireworks */
	config.writeEntry("enableNoFW", fire0Box->isChecked());
	config.writeEntry("enableSphere", fire1Box->isChecked());
	config.writeEntry("enableSplitter", fire2Box->isChecked());
	config.writeEntry("enableCircle", fire3Box->isChecked());
	config.writeEntry("enableBiCircle", fire4Box->isChecked());
	config.writeEntry("enableCascade", fire5Box->isChecked());
	config.writeEntry("enableFountain", fire6Box->isChecked());
	config.writeEntry("enableNova", fire7Box->isChecked());
	config.writeEntry("enableDaisy", fire8Box->isChecked());
	config.writeEntry("enableLove", fire9Box->isChecked());
	config.writeEntry("fireworksFrequency",fireworkFrequencySlider->value());
	/* colors */
	if ((!redBox->isChecked()) && (!orangeBox->isChecked()) &&
	    (!greenBox->isChecked()) && (!blueBox->isChecked())	&&
	    (!whiteBox->isChecked()) && (!purpleBox->isChecked()) &&
	    (!seagreenBox->isChecked()))
		whiteBox->setChecked(true);
	config.writeEntry("enableRed",redBox->isChecked());
	config.writeEntry("enableOrange",orangeBox->isChecked());
	config.writeEntry("enableGreen",greenBox->isChecked());
	config.writeEntry("enableBlue",blueBox->isChecked());
	config.writeEntry("enableWhite",whiteBox->isChecked());
	config.writeEntry("enablePurple",purpleBox->isChecked());
	config.writeEntry("enableDeepGreen",seagreenBox->isChecked());
	config.writeEntry("enableCombos",allowCombos->isChecked());
	config.writeEntry("enableSparkle",allowSparkle->isChecked());
	
	/* misc */
	config.writeEntry("showType",showTypeList->currentItem());
	config.writeEntry("enableStars",starsBox->isChecked());
	config.writeEntry("enableStarsFlickering",starsFlickerBox->isChecked());
	config.writeEntry("enableStarsGradient",starsGradientBox->isChecked());
	config.writeEntry("enableFlash",flashesBox->isChecked());
	config.writeEntry("enableBottomFire",bottomFireBox->isChecked());
	config.writeEntry("enableFade",fadeBox->isChecked());
	config.writeEntry("enableMegaFlares",flaresBox->isChecked());
	config.writeEntry("enableClouds",cloudsBox->isChecked());
	config.writeEntry("enableLightingClouds",cloudsLightenBox->isChecked());
	config.writeEntry("enableSphereLight",sphLightBox->isChecked());
	config.writeEntry("enableSound",soundBox->isChecked());
	config.writeEntry("enableTrails",trailsBox->isChecked());
	config.writeEntry("enableTux",tuxBox->isChecked());
	config.writeEntry("enableKdeLogo",kdeBox->isChecked());
	config.writeEntry("enableReduceLogo",reduceLogoBox->isChecked());
	config.writeEntry("enableRealtime",realtimeBox->isChecked());
	 config.writeEntry("megaFlares",flaresSlider->value());
	 config.writeEntry("starsNumber",starNumberSlider->value());
	 config.writeEntry("fadeAmount",fadingSlider->value());
	 config.writeEntry("logoFrequency",logosFrequencySlider->value());
	 config.writeEntry("bottomFireColour",bottomFireColourList->currentItem());
}

void KFireSaverSetup::readConfig()
{
	KConfig config("kfiresaverrc",true,false);
	
	/* fireworks */
	fire0Box->setChecked(config.readBoolEntry("enableNoFW",false));
	fire1Box->setChecked(config.readBoolEntry("enableSphere",true));
	fire2Box->setChecked(config.readBoolEntry("enableSplitter",false));
	fire3Box->setChecked(config.readBoolEntry("enableCircle",false));
	fire4Box->setChecked(config.readBoolEntry("enableBiCircle",false));
	fire5Box->setChecked(config.readBoolEntry("enableCascade",false));
	fire6Box->setChecked(config.readBoolEntry("enableFountain",false));
	fire7Box->setChecked(config.readBoolEntry("enableNova",false));
	fire8Box->setChecked(config.readBoolEntry("enableDaisy",false));
	fire9Box->setChecked(config.readBoolEntry("enableLove",false));
	fireworkFrequencySlider->setValue(config.readNumEntry("fireworksFrequency",15));
	/* colors */
	redBox->setChecked(config.readBoolEntry("enableRed",false));
	orangeBox->setChecked(config.readBoolEntry("enableOrange",true));
	greenBox->setChecked(config.readBoolEntry("enableGreen",false));
	blueBox->setChecked(config.readBoolEntry("enableBlue",false));
	whiteBox->setChecked(config.readBoolEntry("enableWhite",true));
	purpleBox->setChecked(config.readBoolEntry("enablePurple",false));
	seagreenBox->setChecked(config.readBoolEntry("enableDeepGreen",true));
	allowCombos->setChecked(config.readBoolEntry("enableCombos",true));
	allowSparkle->setChecked(config.readBoolEntry("enableSparkle",true));
	/* misc */
	showTypeList->setCurrentItem(config.readNumEntry("showType",0));
	starsBox->setChecked(config.readBoolEntry("enableStars",true));
	starsFlickerBox->setChecked(config.readBoolEntry("enableStarsFlickering",false));
	starsGradientBox->setChecked(config.readBoolEntry("enableStarsGradient",true));
	flashesBox->setChecked(config.readBoolEntry("enableFlash",false));
	flaresBox->setChecked(config.readBoolEntry("enableMegaFlares",false));
	sphLightBox->setChecked(config.readBoolEntry("enableSphereLight",true));
	cloudsBox->setChecked(config.readBoolEntry("enableClouds",false));
	cloudsLightenBox->setChecked(config.readBoolEntry("enableLightingClouds",false));
	bottomFireBox->setChecked(config.readBoolEntry("enableBottomFire",true));
	fadeBox->setChecked(config.readBoolEntry("enableFade",false));
	soundBox->setChecked(config.readBoolEntry("enableSound",true));
	trailsBox->setChecked(config.readBoolEntry("enableTrails",false));
	tuxBox->setChecked(config.readBoolEntry("enableTux",false));
	kdeBox->setChecked(config.readBoolEntry("enableKdeLogo",false));
	reduceLogoBox->setChecked(config.readBoolEntry("enableReduceLogo",true));
	realtimeBox->setChecked(config.readBoolEntry("enableRealtime",false));
	flaresSlider->setValue(config.readNumEntry("megaFlares",17));
	 starNumberSlider->setValue(config.readNumEntry("starsNumber",4));
	 fadingSlider->setValue(config.readNumEntry("fadeAmount",3));
	 logosFrequencySlider->setValue(config.readNumEntry("logoFrequency",5));
	 bottomFireColourList->setCurrentItem(config.readNumEntry("bottomFireColour",1));
}


void KFireSaverSetup::bottomFireBox_stateChanged( int state )
{
    bool action = true;
    if (state == 0)
	action = false;
    bottomFireColourList->setEnabled( action );
    colourLabel->setEnabled( action );   
}


void KFireSaverSetup::starsBox_stateChanged( int state )
{
    bool action = true;
    if (state == 0)
	action = false;
    lessStarsLabel->setEnabled( action );
    moreStarsLabel->setEnabled( action );
    starNumberSlider->setEnabled( action );
    starsFlickerBox->setEnabled( action );
    starsGradientBox->setEnabled( action );
}


void KFireSaverSetup::fadeBox_stateChanged( int state )
{
    bool action = true;
    if (state == 0)
	action = false;
    amountLabel->setEnabled( action );
    smallFadingLabel->setEnabled( action );
    psychoticFadingLabel->setEnabled( action );
    fadingSlider->setEnabled( action );
}


void KFireSaverSetup::logosT_stateChanged( int state )
{
    bool action = true;
    if (state == 0 && !kdeBox->isChecked())
	action = false;
    reduceLogoBox->setEnabled( action );
    frequencyLabel->setEnabled( action );
    neverLabel->setEnabled( action );
    logosFrequencySlider->setEnabled( action );
    oftenLabel->setEnabled( action );
}


void KFireSaverSetup::logosK_stateChanged( int state )
{
    bool action = true;
    if (state == 0 && !tuxBox->isChecked())
	action = false;
    reduceLogoBox->setEnabled( action );
    frequencyLabel->setEnabled( action );
    neverLabel->setEnabled( action );
    logosFrequencySlider->setEnabled( action );
    oftenLabel->setEnabled( action );
}


void KFireSaverSetup::flaresBox_stateChanged( int state )
{
    bool action = true;
    if (state == 0)
	action = false;
    flaresLessLabel->setEnabled( action );
    flaresMoreLabel->setEnabled( action );
    flaresSlider->setEnabled( action );
}


void KFireSaverSetup::cloudsBox_stateChanged( int state )
{
    cloudsLightenBox->setEnabled( state != 0 );
}


void KFireSaverSetup::togglePreviewState_clicked()
{ 
    previewAttached = !previewAttached;
    if (previewAttached) {
	detachButton->setText("Detach");
	previewLabel->hide();
    }else {
	detachButton->setText("Attach");
	previewLabel->show();
    }
    updatePreview( false );
}


void KFireSaverSetup::applyButton_clicked()
{
    int ci = presetsBox->currentItem();
    ci = ci < 0 ? 0 : ci > 4 ? 4 : ci;
    showTypeList->setCurrentItem(3);
    reduceLogoBox->setChecked(true);
    soundBox->setChecked(true);
    realtimeBox->setChecked(true);
    flashesBox->setChecked(false);
    switch (ci){
    case 0:
	showTypeList->setCurrentItem(0);
	fire0Box->setChecked(true);
	fire1Box->setChecked(true);
	fire2Box->setChecked(false);
	fire3Box->setChecked(false);
	fire4Box->setChecked(false);
	fire5Box->setChecked(false);
	fireworkFrequencySlider->setValue(8);
	bottomFireBox->setChecked(false);
	redBox->setChecked(true);
	orangeBox->setChecked(false);
	greenBox->setChecked(true);
	purpleBox->setChecked(false);
	seagreenBox->setChecked(false);
	blueBox->setChecked(true);
	whiteBox->setChecked(true);
	allowSparkle->setChecked(false);
	allowCombos->setChecked(false);
	tuxBox->setChecked(true);
	kdeBox->setChecked(true);
	logosFrequencySlider->setValue(2);
	starsBox->setChecked(false);
	starsFlickerBox->setChecked(false);
	starsGradientBox->setChecked(false);
	realtimeBox->setChecked(false);
	fadeBox->setChecked(false);
	flaresBox->setChecked(false);
	sphLightBox->setChecked(false);
	break;
    case 1:
	fire0Box->setChecked(true);
	fire1Box->setChecked(true);
	fire2Box->setChecked(true);
	fire3Box->setChecked(true);
	fire4Box->setChecked(false);
	fire5Box->setChecked(true);
	fireworkFrequencySlider->setValue(14);
	bottomFireBox->setChecked(true);
	bottomFireColourList->setCurrentItem(1);
	redBox->setChecked(true);
	orangeBox->setChecked(true);
	greenBox->setChecked(true);
	purpleBox->setChecked(false);
	seagreenBox->setChecked(false);
	blueBox->setChecked(true);
	whiteBox->setChecked(true);
	allowSparkle->setChecked(true);
	allowCombos->setChecked(false);
	tuxBox->setChecked(true);
	kdeBox->setChecked(false);
	logosFrequencySlider->setValue(4);
	starsBox->setChecked(true);
	starsFlickerBox->setChecked(false);
	starsGradientBox->setChecked(false);
	starNumberSlider->setValue(3);
	fadeBox->setChecked(false);
	flaresBox->setChecked(false);
	sphLightBox->setChecked(true);
	break;
    case 2:
	fire0Box->setChecked(true);
	fire1Box->setChecked(true);
	fire2Box->setChecked(true);
	fire3Box->setChecked(true);
	fire4Box->setChecked(true);
	fire5Box->setChecked(true);
	fireworkFrequencySlider->setValue(16);
	bottomFireBox->setChecked(true);
	bottomFireColourList->setCurrentItem(2);
	redBox->setChecked(true);
	orangeBox->setChecked(true);
	greenBox->setChecked(true);
	purpleBox->setChecked(true);
	seagreenBox->setChecked(true);
	blueBox->setChecked(true);
	whiteBox->setChecked(true);
	allowSparkle->setChecked(true);
	allowCombos->setChecked(true);
	tuxBox->setChecked(true);
	kdeBox->setChecked(false);
	logosFrequencySlider->setValue(2);
	starsBox->setChecked(true);
	starsFlickerBox->setChecked(true);
	starsGradientBox->setChecked(true);
	starNumberSlider->setValue(5);
	fadeBox->setChecked(true);
	fadingSlider->setValue(3);
	flaresBox->setChecked(false);
	sphLightBox->setChecked(false);
	break;
    case 3:
	fire0Box->setChecked(true);
	fire1Box->setChecked(true);
	fire2Box->setChecked(true);
	fire3Box->setChecked(true);
	fire4Box->setChecked(true);
	fire5Box->setChecked(true);
	fireworkFrequencySlider->setValue(18);
	bottomFireBox->setChecked(true);
	bottomFireColourList->setCurrentItem(3);
	redBox->setChecked(true);
	orangeBox->setChecked(true);
	greenBox->setChecked(true);
	purpleBox->setChecked(true);
	seagreenBox->setChecked(true);
	blueBox->setChecked(true);
	whiteBox->setChecked(true);
	allowSparkle->setChecked(true);
	allowCombos->setChecked(true);
	tuxBox->setChecked(false);
	kdeBox->setChecked(false);
	logosFrequencySlider->setValue(5);
	starsBox->setChecked(true);
	starsFlickerBox->setChecked(true);
	starsGradientBox->setChecked(true);
	starNumberSlider->setValue(8);
	fadeBox->setChecked(true);
	fadingSlider->setValue(7);
	flaresBox->setChecked(true);
	flaresSlider->setValue(22);
	sphLightBox->setChecked(false);
	break;
    case 4:
	showTypeList->setCurrentItem(0);
	fire0Box->setChecked(false);
	fire1Box->setChecked(true);
	fire2Box->setChecked(false);
	fire3Box->setChecked(false);
	fire4Box->setChecked(false);
	fire5Box->setChecked(false);
	fireworkFrequencySlider->setValue(17);
	bottomFireBox->setChecked(true);
	bottomFireColourList->setCurrentItem(2);
	redBox->setChecked(false);
	orangeBox->setChecked(true);
	greenBox->setChecked(false);
	purpleBox->setChecked(false);
	seagreenBox->setChecked(true);
	blueBox->setChecked(false);
	whiteBox->setChecked(true);
	allowSparkle->setChecked(true);
	allowCombos->setChecked(true);
	tuxBox->setChecked(false);
	kdeBox->setChecked(false);
	starsBox->setChecked(true);
	starsFlickerBox->setChecked(false);
	starsGradientBox->setChecked(true);
	starNumberSlider->setValue(3);
	fadeBox->setChecked(false);
	flaresBox->setChecked(true);
	flaresSlider->setValue(17);
	sphLightBox->setChecked(true);
	realtimeBox->setChecked(false);
	break;
    }
    updatePreview( true );
}
