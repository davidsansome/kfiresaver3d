#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './kfiresaversetup.ui'
**
** Created: Mon Sep 9 20:33:29 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "kfiresaversetup.h"

#include <qvariant.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qframe.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qslider.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "kfiresaversetup.ui.h"

/* 
 *  Constructs a KFireSaverSetup which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
KFireSaverSetup::KFireSaverSetup( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "KFireSaverSetup" );
    resize( 440, 250 ); 
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setMinimumSize( QSize( 440, 250 ) );
    setMaximumSize( QSize( 440, 250 ) );
    setBaseSize( QSize( 440, 250 ) );
    setCaption( tr2i18n( "Fireworks setup" ) );

    applyButton = new QPushButton( this, "applyButton" );
    applyButton->setGeometry( QRect( 132, 225, 102, 21 ) ); 
    applyButton->setText( tr2i18n( "Use &Preset" ) );
    QToolTip::add( applyButton, tr2i18n( "quit whithout apply changes" ) );
    QWhatsThis::add( applyButton, tr2i18n( "quit whithout apply changes" ) );

    PushButton4 = new QPushButton( this, "PushButton4" );
    PushButton4->setGeometry( QRect( 386, 225, 44, 21 ) ); 
    PushButton4->setText( tr2i18n( "&OK" ) );
    QToolTip::add( PushButton4, tr2i18n( "save changes and quit" ) );
    QWhatsThis::add( PushButton4, tr2i18n( "save changes and quit" ) );

    PushButton5 = new QPushButton( this, "PushButton5" );
    PushButton5->setGeometry( QRect( 315, 225, 66, 21 ) ); 
    PushButton5->setText( tr2i18n( "&Cancel" ) );
    QToolTip::add( PushButton5, tr2i18n( "quit whithout apply changes" ) );
    QWhatsThis::add( PushButton5, tr2i18n( "quit whithout apply changes" ) );

    presetsBox = new QComboBox( FALSE, this, "presetsBox" );
    presetsBox->insertItem( tr2i18n( "Simple" ) );
    presetsBox->insertItem( tr2i18n( "Real" ) );
    presetsBox->insertItem( tr2i18n( "More than real" ) );
    presetsBox->insertItem( tr2i18n( "Drugged" ) );
    presetsBox->insertItem( tr2i18n( "KoRaL's preset" ) );
    presetsBox->setGeometry( QRect( 11, 225, 115, 20 ) ); 
    presetsBox->setCurrentItem( 4 );
    presetsBox->setAutoCompletion( TRUE );

    TabWidget2 = new QTabWidget( this, "TabWidget2" );
    TabWidget2->setGeometry( QRect( 11, 11, 418, 210 ) ); 

    tab = new QWidget( TabWidget2, "tab" );

    TextLabel1_2 = new QLabel( tab, "TextLabel1_2" );
    TextLabel1_2->setGeometry( QRect( 220, 4, 190, 170 ) ); 
    QFont TextLabel1_2_font(  TextLabel1_2->font() );
    TextLabel1_2_font.setPointSize( 10 );
    TextLabel1_2->setFont( TextLabel1_2_font ); 
    TextLabel1_2->setText( tr2i18n( "KFireSaver 3D - presented by:\n"
"\n"
"Enrico Ros\n"
"   simple 3D engine, graphics effects,\n"
"   different fireworks, sound, timeline..\n"
" <asy@libero.it>\n"
"\n"
"David Sansome\n"
"   initial framework and concept,\n"
"   setup dialog, bottom fire, artwork..\n"
" <me@davidsansome.com>" ) );
    TextLabel1_2->setTextFormat( QLabel::PlainText );
    TextLabel1_2->setScaledContents( FALSE );

    PreviewKFSFrame = new QFrame( tab, "PreviewKFSFrame" );
    PreviewKFSFrame->setGeometry( QRect( 6, 3, 202, 152 ) ); 
    QPalette pal;
    QColorGroup cg;
    cg.setColor( QColorGroup::Foreground, black );
    cg.setColor( QColorGroup::Button, QColor( 218, 226, 255) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, QColor( 236, 240, 255) );
    cg.setColor( QColorGroup::Dark, QColor( 109, 113, 127) );
    cg.setColor( QColorGroup::Mid, QColor( 145, 151, 170) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 230, 230, 230) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 0, 0, 128) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, black );
    cg.setColor( QColorGroup::LinkVisited, black );
    pal.setActive( cg );
    cg.setColor( QColorGroup::Foreground, black );
    cg.setColor( QColorGroup::Button, QColor( 218, 226, 255) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, white );
    cg.setColor( QColorGroup::Dark, QColor( 109, 113, 127) );
    cg.setColor( QColorGroup::Mid, QColor( 145, 151, 170) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 230, 230, 230) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 0, 0, 128) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, QColor( 0, 0, 192) );
    cg.setColor( QColorGroup::LinkVisited, QColor( 128, 0, 128) );
    pal.setInactive( cg );
    cg.setColor( QColorGroup::Foreground, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Button, QColor( 218, 226, 255) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, white );
    cg.setColor( QColorGroup::Dark, QColor( 109, 113, 127) );
    cg.setColor( QColorGroup::Mid, QColor( 145, 151, 170) );
    cg.setColor( QColorGroup::Text, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 230, 230, 230) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 0, 0, 128) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, QColor( 0, 0, 192) );
    cg.setColor( QColorGroup::LinkVisited, QColor( 128, 0, 128) );
    pal.setDisabled( cg );
    PreviewKFSFrame->setPalette( pal );
    PreviewKFSFrame->setFrameShape( QFrame::StyledPanel );
    PreviewKFSFrame->setFrameShadow( QFrame::Sunken );
    QToolTip::add( PreviewKFSFrame, tr2i18n( "preview window" ) );
    QWhatsThis::add( PreviewKFSFrame, tr2i18n( "Here come the preview (if isn't detached)" ) );

    previewLabel = new QLabel( PreviewKFSFrame, "previewLabel" );
    previewLabel->setEnabled( FALSE );
    previewLabel->setGeometry( QRect( 55, 70, 95, 16 ) ); 
    QFont previewLabel_font(  previewLabel->font() );
    previewLabel_font.setItalic( TRUE );
    previewLabel->setFont( previewLabel_font ); 
    previewLabel->setText( tr2i18n( "P R E V I E W" ) );
    previewLabel->setAlignment( int( QLabel::AlignCenter ) );

    detachButton = new QPushButton( tab, "detachButton" );
    detachButton->setGeometry( QRect( 133, 158, 75, 21 ) ); 
    detachButton->setText( tr2i18n( "&Detach" ) );
    QToolTip::add( detachButton, tr2i18n( "still experimental" ) );
    QWhatsThis::add( detachButton, tr2i18n( "Change the size of the preview window detaching or attaching it to the main window" ) );

    updateButton = new QPushButton( tab, "updateButton" );
    updateButton->setGeometry( QRect( 6, 158, 122, 21 ) ); 
    updateButton->setText( tr2i18n( "&Update Preview" ) );
    QToolTip::add( updateButton, tr2i18n( "apply current changes to the running fireworks scene" ) );
    QWhatsThis::add( updateButton, tr2i18n( "apply current changes to the running fireworks scene" ) );
    TabWidget2->insertTab( tab, tr2i18n( "About" ) );

    tab_2 = new QWidget( TabWidget2, "tab_2" );

    frequencyLabel2 = new QLabel( tab_2, "frequencyLabel2" );
    frequencyLabel2->setGeometry( QRect( 10, 160, 70, 16 ) ); 
    frequencyLabel2->setText( tr2i18n( "Frequency:" ) );

    fire9Box = new QCheckBox( tab_2, "fire9Box" );
    fire9Box->setEnabled( FALSE );
    fire9Box->setGeometry( QRect( 210, 135, 190, 19 ) ); 
    fire9Box->setText( tr2i18n( "Love" ) );
    QToolTip::add( fire9Box, tr2i18n( "try me" ) );

    fire8Box = new QCheckBox( tab_2, "fire8Box" );
    fire8Box->setEnabled( FALSE );
    fire8Box->setGeometry( QRect( 210, 110, 190, 19 ) ); 
    fire8Box->setText( tr2i18n( "Daisy" ) );
    QToolTip::add( fire8Box, tr2i18n( "try me" ) );

    fire7Box = new QCheckBox( tab_2, "fire7Box" );
    fire7Box->setEnabled( FALSE );
    fire7Box->setGeometry( QRect( 210, 85, 190, 19 ) ); 
    fire7Box->setText( tr2i18n( "Nova" ) );
    QToolTip::add( fire7Box, tr2i18n( "try me" ) );

    fire6Box = new QCheckBox( tab_2, "fire6Box" );
    fire6Box->setEnabled( FALSE );
    fire6Box->setGeometry( QRect( 210, 60, 190, 19 ) ); 
    fire6Box->setText( tr2i18n( "Fountain" ) );
    QToolTip::add( fire6Box, tr2i18n( "try me" ) );

    showTypeList = new QComboBox( FALSE, tab_2, "showTypeList" );
    showTypeList->insertItem( tr2i18n( "Randomize all" ) );
    showTypeList->insertItem( tr2i18n( "MonoType (color changes)" ) );
    showTypeList->insertItem( tr2i18n( "MonoChrome (type changes)" ) );
    showTypeList->insertItem( tr2i18n( "pseudo Show (hope this is the best one)" ) );
    showTypeList->setGeometry( QRect( 200, 7, 200, 22 ) ); 
    showTypeList->setAutoCompletion( TRUE );
    QToolTip::add( showTypeList, tr2i18n( "experimental. select how the show will proceed. experimental." ) );
    QWhatsThis::add( showTypeList, tr2i18n( "You can change the flow of events. Randm is the default *old* mode, but we know that we can do better than that!!" ) );

    frequencyLabel2_2_2_2 = new QLabel( tab_2, "frequencyLabel2_2_2_2" );
    frequencyLabel2_2_2_2->setGeometry( QRect( 12, 7, 185, 22 ) ); 
    frequencyLabel2_2_2_2->setText( tr2i18n( "Type of the show: (experimental)" ) );

    fire1Box = new QCheckBox( tab_2, "fire1Box" );
    fire1Box->setGeometry( QRect( 15, 60, 190, 19 ) ); 
    fire1Box->setText( tr2i18n( "Classic Spherical" ) );
    fire1Box->setChecked( TRUE );
    QToolTip::add( fire1Box, tr2i18n( "try me" ) );

    QWidget* privateLayoutWidget = new QWidget( tab_2, "Layout3" );
    privateLayoutWidget->setGeometry( QRect( 85, 160, 320, 16 ) ); 
    Layout3 = new QHBoxLayout( privateLayoutWidget, 0, 6, "Layout3"); 

    neverLabel2 = new QLabel( privateLayoutWidget, "neverLabel2" );
    neverLabel2->setText( tr2i18n( "Never" ) );
    QToolTip::add( neverLabel2, tr2i18n( "mmm.. what about a fireworks screensaver whithout fireworks??" ) );
    QWhatsThis::add( neverLabel2, tr2i18n( "mmm.. what about a fireworks screensaver whithout fireworks??" ) );
    Layout3->addWidget( neverLabel2 );

    fireworkFrequencySlider = new QSlider( privateLayoutWidget, "fireworkFrequencySlider" );
    fireworkFrequencySlider->setMinValue( 0 );
    fireworkFrequencySlider->setMaxValue( 20 );
    fireworkFrequencySlider->setValue( 8 );
    fireworkFrequencySlider->setOrientation( QSlider::Horizontal );
    QToolTip::add( fireworkFrequencySlider, tr2i18n( "this sets how often fireworks are released" ) );
    QWhatsThis::add( fireworkFrequencySlider, tr2i18n( "this sets how often fireworks are released" ) );
    Layout3->addWidget( fireworkFrequencySlider );

    oftenLabel2 = new QLabel( privateLayoutWidget, "oftenLabel2" );
    oftenLabel2->setText( tr2i18n( "Often" ) );
    QToolTip::add( oftenLabel2, tr2i18n( "often: yeah, i like it" ) );
    QWhatsThis::add( oftenLabel2, tr2i18n( "if you have enough power you can try this" ) );
    Layout3->addWidget( oftenLabel2 );

    fire0Box = new QCheckBox( tab_2, "fire0Box" );
    fire0Box->setGeometry( QRect( 15, 35, 190, 19 ) ); 
    fire0Box->setText( tr2i18n( "Only Explosion" ) );
    fire0Box->setChecked( TRUE );
    QToolTip::add( fire0Box, tr2i18n( "try me" ) );

    fire2Box = new QCheckBox( tab_2, "fire2Box" );
    fire2Box->setGeometry( QRect( 15, 85, 190, 19 ) ); 
    fire2Box->setText( tr2i18n( "Atomic Splitter" ) );
    fire2Box->setChecked( TRUE );
    QToolTip::add( fire2Box, tr2i18n( "try me" ) );

    fire3Box = new QCheckBox( tab_2, "fire3Box" );
    fire3Box->setGeometry( QRect( 15, 110, 190, 19 ) ); 
    fire3Box->setText( tr2i18n( "Ring of flames" ) );
    fire3Box->setChecked( TRUE );
    QToolTip::add( fire3Box, tr2i18n( "try me" ) );

    fire4Box = new QCheckBox( tab_2, "fire4Box" );
    fire4Box->setGeometry( QRect( 15, 135, 190, 19 ) ); 
    fire4Box->setText( tr2i18n( "World of flames" ) );
    fire4Box->setChecked( TRUE );
    QToolTip::add( fire4Box, tr2i18n( "try me" ) );

    fire5Box = new QCheckBox( tab_2, "fire5Box" );
    fire5Box->setGeometry( QRect( 210, 35, 190, 19 ) ); 
    fire5Box->setText( tr2i18n( "Sparkling Cascade" ) );
    fire5Box->setChecked( TRUE );
    QToolTip::add( fire5Box, tr2i18n( "try me" ) );
    TabWidget2->insertTab( tab_2, tr2i18n( "Fireworks" ) );

    tab_3 = new QWidget( TabWidget2, "tab_3" );

    trailsBox = new QCheckBox( tab_3, "trailsBox" );
    trailsBox->setEnabled( FALSE );
    trailsBox->setGeometry( QRect( 15, 10, 160, 19 ) ); 
    trailsBox->setText( tr2i18n( "Fireworks leave a trail" ) );
    trailsBox->setChecked( FALSE );
    QToolTip::add( trailsBox, tr2i18n( "not yet ported" ) );
    QWhatsThis::add( trailsBox, tr2i18n( "not yet ported" ) );

    Frame4 = new QFrame( tab_3, "Frame4" );
    Frame4->setGeometry( QRect( 145, 155, 255, 19 ) ); 
    Frame4->setPaletteBackgroundColor( QColor( 211, 226, 226 ) );
    Frame4->setFrameShape( QFrame::NoFrame );
    Frame4->setFrameShadow( QFrame::Plain );

    allowSparkle = new QCheckBox( Frame4, "allowSparkle" );
    allowSparkle->setGeometry( QRect( 1, 0, 124, 19 ) ); 
    QFont allowSparkle_font(  allowSparkle->font() );
    allowSparkle_font.setItalic( TRUE );
    allowSparkle->setFont( allowSparkle_font ); 
    allowSparkle->setText( tr2i18n( "Allow sparkling" ) );
    allowSparkle->setChecked( TRUE );
    QToolTip::add( allowSparkle, tr2i18n( "please, turn me on!" ) );
    QWhatsThis::add( allowSparkle, tr2i18n( "This disables the 'flickering' effect of some fireworks. This is useful for example for cascade fireworks" ) );

    allowCombos = new QCheckBox( Frame4, "allowCombos" );
    allowCombos->setGeometry( QRect( 130, 0, 95, 19 ) ); 
    QFont allowCombos_font(  allowCombos->font() );
    allowCombos_font.setItalic( TRUE );
    allowCombos->setFont( allowCombos_font ); 
    allowCombos->setText( tr2i18n( "Multicolor" ) );
    allowCombos->setChecked( TRUE );
    QToolTip::add( allowCombos, tr2i18n( "try bi-colour fireworks" ) );
    QWhatsThis::add( allowCombos, tr2i18n( "This allow a random creation of fireworks that explodes in 2 colors" ) );

    seagreenBox = new QCheckBox( tab_3, "seagreenBox" );
    seagreenBox->setGeometry( QRect( 146, 131, 123, 19 ) ); 
    seagreenBox->setText( tr2i18n( "Deep-sea green" ) );
    seagreenBox->setChecked( TRUE );

    particleColorLabel = new QLabel( tab_3, "particleColorLabel" );
    particleColorLabel->setGeometry( QRect( 10, 85, 130, 16 ) ); 
    particleColorLabel->setText( tr2i18n( "Colors and attributes:" ) );

    Line4 = new QFrame( tab_3, "Line4" );
    Line4->setGeometry( QRect( 135, 85, 265, 16 ) ); 
    Line4->setFrameShape( QFrame::HLine );
    Line4->setFrameShadow( QFrame::Sunken );
    Line4->setFrameShape( QFrame::HLine );

    flashesBox = new QCheckBox( tab_3, "flashesBox" );
    flashesBox->setGeometry( QRect( 15, 35, 245, 19 ) ); 
    flashesBox->setText( tr2i18n( "Flash screen when fireworks explode" ) );
    QToolTip::add( flashesBox, tr2i18n( "enable to see a 'epilectic' flash :-)" ) );
    QWhatsThis::add( flashesBox, tr2i18n( "When a fireworks explodes up in the sky, the explosion light everything up for some hundreds of second." ) );

    colourLabel = new QLabel( tab_3, "colourLabel" );
    colourLabel->setGeometry( QRect( 205, 60, 50, 20 ) ); 
    colourLabel->setText( tr2i18n( "Colour:" ) );

    bottomFireBox = new QCheckBox( tab_3, "bottomFireBox" );
    bottomFireBox->setGeometry( QRect( 15, 60, 140, 20 ) ); 
    bottomFireBox->setText( tr2i18n( "Enable bottom fire" ) );
    bottomFireBox->setChecked( TRUE );
    QToolTip::add( bottomFireBox, tr2i18n( "enables bottom jumping particles" ) );
    QWhatsThis::add( bottomFireBox, tr2i18n( "This enables coloured particles jumping on the bottom of the screen. Can be set to look like a burning fire." ) );

    redBox = new QCheckBox( tab_3, "redBox" );
    redBox->setGeometry( QRect( 16, 106, 90, 19 ) ); 
    redBox->setText( tr2i18n( "Deep red" ) );
    redBox->setChecked( TRUE );

    orangeBox = new QCheckBox( tab_3, "orangeBox" );
    orangeBox->setGeometry( QRect( 146, 106, 95, 19 ) ); 
    orangeBox->setText( tr2i18n( "Hot orange" ) );
    orangeBox->setChecked( TRUE );

    greenBox = new QCheckBox( tab_3, "greenBox" );
    greenBox->setGeometry( QRect( 275, 106, 105, 19 ) ); 
    greenBox->setText( tr2i18n( "Purest green" ) );
    greenBox->setChecked( TRUE );

    blueBox = new QCheckBox( tab_3, "blueBox" );
    blueBox->setGeometry( QRect( 275, 131, 100, 19 ) ); 
    blueBox->setText( tr2i18n( "Boring blue" ) );
    blueBox->setChecked( TRUE );

    purpleBox = new QCheckBox( tab_3, "purpleBox" );
    purpleBox->setGeometry( QRect( 16, 131, 110, 19 ) ); 
    purpleBox->setText( tr2i18n( "Velvet purple" ) );
    purpleBox->setChecked( TRUE );

    whiteBox = new QCheckBox( tab_3, "whiteBox" );
    whiteBox->setGeometry( QRect( 15, 155, 110, 19 ) ); 
    whiteBox->setText( tr2i18n( "Blinding white" ) );
    whiteBox->setChecked( TRUE );

    bottomFireColourList = new QComboBox( FALSE, tab_3, "bottomFireColourList" );
    bottomFireColourList->insertItem( tr2i18n( "Blue" ) );
    bottomFireColourList->insertItem( tr2i18n( "Orange" ) );
    bottomFireColourList->insertItem( tr2i18n( "Purple" ) );
    bottomFireColourList->insertItem( tr2i18n( "Red" ) );
    bottomFireColourList->setGeometry( QRect( 260, 58, 140, 20 ) ); 
    QToolTip::add( bottomFireColourList, tr2i18n( "pick the color you like best" ) );
    QWhatsThis::add( bottomFireColourList, tr2i18n( "Blue, Orange, Purple, Red... many choices here!!" ) );
    TabWidget2->insertTab( tab_3, tr2i18n( "Particles" ) );

    tab_4 = new QWidget( TabWidget2, "tab_4" );

    logosGroup = new QGroupBox( tab_4, "logosGroup" );
    logosGroup->setGeometry( QRect( 10, 5, 395, 65 ) ); 
    logosGroup->setTitle( tr2i18n( "Logos" ) );

    reduceLogoBox = new QCheckBox( logosGroup, "reduceLogoBox" );
    reduceLogoBox->setGeometry( QRect( 200, 16, 90, 19 ) ); 
    reduceLogoBox->setText( tr2i18n( "Low detail" ) );
    reduceLogoBox->setChecked( TRUE );
    QToolTip::add( reduceLogoBox, tr2i18n( "useful for increasing speed" ) );
    QWhatsThis::add( reduceLogoBox, tr2i18n( "This reduces tp 1/4 the amount of generated logo particles." ) );

    frequencyLabel = new QLabel( logosGroup, "frequencyLabel" );
    frequencyLabel->setGeometry( QRect( 11, 41, 68, 16 ) ); 
    frequencyLabel->setText( tr2i18n( "Frequency:" ) );

    QWidget* privateLayoutWidget_2 = new QWidget( logosGroup, "Layout7" );
    privateLayoutWidget_2->setGeometry( QRect( 85, 41, 299, 16 ) ); 
    Layout7 = new QHBoxLayout( privateLayoutWidget_2, 0, 6, "Layout7"); 

    neverLabel = new QLabel( privateLayoutWidget_2, "neverLabel" );
    neverLabel->setText( tr2i18n( "Never" ) );
    Layout7->addWidget( neverLabel );

    logosFrequencySlider = new QSlider( privateLayoutWidget_2, "logosFrequencySlider" );
    logosFrequencySlider->setMinValue( 0 );
    logosFrequencySlider->setMaxValue( 10 );
    logosFrequencySlider->setValue( 5 );
    logosFrequencySlider->setOrientation( QSlider::Horizontal );
    Layout7->addWidget( logosFrequencySlider );

    oftenLabel = new QLabel( privateLayoutWidget_2, "oftenLabel" );
    oftenLabel->setText( tr2i18n( "Often" ) );
    Layout7->addWidget( oftenLabel );

    tuxBox = new QCheckBox( logosGroup, "tuxBox" );
    tuxBox->setEnabled( TRUE );
    tuxBox->setGeometry( QRect( 11, 16, 55, 19 ) ); 
    tuxBox->setText( tr2i18n( "Tux" ) );
    tuxBox->setChecked( TRUE );
    QToolTip::add( tuxBox, tr2i18n( "enables Tux" ) );
    QWhatsThis::add( tuxBox, tr2i18n( "This enables the Random generation of Tux logos" ) );

    kdeBox = new QCheckBox( logosGroup, "kdeBox" );
    kdeBox->setGeometry( QRect( 97, 16, 85, 19 ) ); 
    kdeBox->setText( tr2i18n( "KDE logo" ) );
    kdeBox->setChecked( FALSE );
    QToolTip::add( kdeBox, tr2i18n( "enables KDE" ) );
    QWhatsThis::add( kdeBox, tr2i18n( "This enables the Random generation of Kde logos" ) );

    soundBox = new QCheckBox( tab_4, "soundBox" );
    soundBox->setGeometry( QRect( 15, 150, 175, 20 ) ); 
    soundBox->setText( tr2i18n( "Enable explosions sound" ) );
    soundBox->setChecked( TRUE );
    QToolTip::add( soundBox, tr2i18n( "remember to turn the speakers on!" ) );
    QWhatsThis::add( soundBox, tr2i18n( "This enables the sound. For now isn't well implemented." ) );

    starsGroup = new QGroupBox( tab_4, "starsGroup" );
    starsGroup->setGeometry( QRect( 10, 75, 395, 65 ) ); 
    starsGroup->setTitle( tr2i18n( "Stars" ) );

    starsGradientBox = new QCheckBox( starsGroup, "starsGradientBox" );
    starsGradientBox->setGeometry( QRect( 200, 39, 130, 20 ) ); 
    starsGradientBox->setText( tr2i18n( "Gradient coloring" ) );
    starsGradientBox->setChecked( TRUE );
    QToolTip::add( starsGradientBox, tr2i18n( "emulate horizon coloring" ) );
    QWhatsThis::add( starsGradientBox, tr2i18n( "Gives lower stars a reddish tint." ) );

    starsFlickerBox = new QCheckBox( starsGroup, "starsFlickerBox" );
    starsFlickerBox->setGeometry( QRect( 11, 39, 90, 20 ) ); 
    starsFlickerBox->setText( tr2i18n( "Flickering" ) );
    starsFlickerBox->setChecked( TRUE );
    QToolTip::add( starsFlickerBox, tr2i18n( "enables a natural 'flicker' effect" ) );
    QWhatsThis::add( starsFlickerBox, tr2i18n( "This option produces a sort of vibration in the lightness of the star." ) );

    starsBox = new QCheckBox( starsGroup, "starsBox" );
    starsBox->setGeometry( QRect( 11, 16, 105, 20 ) ); 
    starsBox->setText( tr2i18n( "Enable stars" ) );
    starsBox->setChecked( TRUE );
    QToolTip::add( starsBox, tr2i18n( "what about a sky whithout stars?" ) );
    QWhatsThis::add( starsBox, tr2i18n( "Enable small stars. Can also be set flickering, number of stars and gradient coloring." ) );

    moreStarsLabel = new QLabel( starsGroup, "moreStarsLabel" );
    moreStarsLabel->setGeometry( QRect( 350, 15, 34, 20 ) ); 
    moreStarsLabel->setText( tr2i18n( "More" ) );

    lessStarsLabel = new QLabel( starsGroup, "lessStarsLabel" );
    lessStarsLabel->setGeometry( QRect( 200, 15, 35, 20 ) ); 
    lessStarsLabel->setText( tr2i18n( "Less" ) );

    starNumberSlider = new QSlider( starsGroup, "starNumberSlider" );
    starNumberSlider->setGeometry( QRect( 230, 19, 115, 16 ) ); 
    starNumberSlider->setMinValue( 0 );
    starNumberSlider->setMaxValue( 10 );
    starNumberSlider->setValue( 3 );
    starNumberSlider->setOrientation( QSlider::Horizontal );

    realtimeBox = new QCheckBox( tab_4, "realtimeBox" );
    realtimeBox->setEnabled( TRUE );
    realtimeBox->setGeometry( QRect( 210, 150, 160, 20 ) ); 
    realtimeBox->setText( tr2i18n( "RealTime - (frame skip)" ) );
    realtimeBox->setChecked( TRUE );
    QToolTip::add( realtimeBox, tr2i18n( "disable if you see 'dotted tails' or the action goes too fast." ) );
    QWhatsThis::add( realtimeBox, tr2i18n( "A new feature.. if fps drops skip frames and render in real-time." ) );
    TabWidget2->insertTab( tab_4, tr2i18n( "Specials" ) );

    tab_5 = new QWidget( TabWidget2, "tab_5" );

    fadeTable = new QGroupBox( tab_5, "fadeTable" );
    fadeTable->setGeometry( QRect( 10, 10, 395, 80 ) ); 
    fadeTable->setTitle( QString::null );
    QToolTip::add( fadeTable, tr2i18n( "click on the ? button on the top of the window and then on the checkbox for more info" ) );

    TextLabel2_2 = new QLabel( fadeTable, "TextLabel2_2" );
    TextLabel2_2->setGeometry( QRect( 10, 55, 376, 21 ) ); 
    QFont TextLabel2_2_font(  TextLabel2_2->font() );
    TextLabel2_2_font.setBold( TRUE );
    TextLabel2_2->setFont( TextLabel2_2_font ); 
    TextLabel2_2->setText( tr2i18n( "SO SLOW on machines whithout a powerful 3D accelerator !!" ) );

    QWidget* privateLayoutWidget_3 = new QWidget( fadeTable, "Layout7_2_2" );
    privateLayoutWidget_3->setGeometry( QRect( 68, 35, 315, 16 ) ); 
    Layout7_2_2 = new QHBoxLayout( privateLayoutWidget_3, 0, 6, "Layout7_2_2"); 

    smallFadingLabel = new QLabel( privateLayoutWidget_3, "smallFadingLabel" );
    smallFadingLabel->setText( tr2i18n( "Small" ) );
    QToolTip::add( smallFadingLabel, tr2i18n( "looks like disabling the effect!" ) );
    Layout7_2_2->addWidget( smallFadingLabel );

    fadingSlider = new QSlider( privateLayoutWidget_3, "fadingSlider" );
    fadingSlider->setMinValue( 0 );
    fadingSlider->setMaxValue( 9 );
    fadingSlider->setValue( 3 );
    fadingSlider->setOrientation( QSlider::Horizontal );
    QToolTip::add( fadingSlider, tr2i18n( "adjust fading value" ) );
    QWhatsThis::add( fadingSlider, tr2i18n( "slide to left to reduce 'tail' effect.. to the right you increase it." ) );
    Layout7_2_2->addWidget( fadingSlider );

    psychoticFadingLabel = new QLabel( privateLayoutWidget_3, "psychoticFadingLabel" );
    psychoticFadingLabel->setText( tr2i18n( "Psychotic" ) );
    QToolTip::add( psychoticFadingLabel, tr2i18n( "yeah, right, what's next??" ) );
    Layout7_2_2->addWidget( psychoticFadingLabel );

    amountLabel = new QLabel( fadeTable, "amountLabel" );
    amountLabel->setGeometry( QRect( 10, 35, 55, 16 ) ); 
    amountLabel->setText( tr2i18n( "Amount:" ) );

    fadeBox = new QCheckBox( fadeTable, "fadeBox" );
    fadeBox->setGeometry( QRect( 10, 10, 200, 19 ) ); 
    fadeBox->setText( tr2i18n( "Enable particles fading effect" ) );
    fadeBox->setChecked( TRUE );
    QToolTip::add( fadeBox, tr2i18n( "click on the ? button and then here for more info" ) );
    QWhatsThis::add( fadeBox, tr2i18n( "This changes the way the screen is cleared. If this option is enabled, instead of flooding the buffer whith black color, a semi transparent black 'glass' is superposed on scene. This 'fades down' the lightness of the picture and gives a natural 'tail' effect .. try me :-) !!" ) );

    QWidget* privateLayoutWidget_4 = new QWidget( tab_5, "Layout11" );
    privateLayoutWidget_4->setGeometry( QRect( 210, 100, 190, 20 ) ); 
    Layout11 = new QHBoxLayout( privateLayoutWidget_4, 0, 6, "Layout11"); 

    flaresLessLabel = new QLabel( privateLayoutWidget_4, "flaresLessLabel" );
    flaresLessLabel->setEnabled( FALSE );
    flaresLessLabel->setText( tr2i18n( "Small" ) );
    Layout11->addWidget( flaresLessLabel );

    flaresSlider = new QSlider( privateLayoutWidget_4, "flaresSlider" );
    flaresSlider->setEnabled( FALSE );
    flaresSlider->setMinValue( 10 );
    flaresSlider->setMaxValue( 26 );
    flaresSlider->setLineStep( 2 );
    flaresSlider->setPageStep( 6 );
    flaresSlider->setValue( 16 );
    flaresSlider->setOrientation( QSlider::Horizontal );
    QToolTip::add( flaresSlider, tr2i18n( "i want to slide right!" ) );
    Layout11->addWidget( flaresSlider );

    flaresMoreLabel = new QLabel( privateLayoutWidget_4, "flaresMoreLabel" );
    flaresMoreLabel->setEnabled( FALSE );
    flaresMoreLabel->setText( tr2i18n( "Big" ) );
    Layout11->addWidget( flaresMoreLabel );

    flaresBox = new QCheckBox( tab_5, "flaresBox" );
    flaresBox->setGeometry( QRect( 15, 100, 160, 20 ) ); 
    flaresBox->setText( tr2i18n( "Enable MEGA flares" ) );
    QToolTip::add( flaresBox, tr2i18n( "warning, this can shock your mind :-)" ) );
    QWhatsThis::add( flaresBox, tr2i18n( "Multiplies the scale factor for particles near you, resulting in a colorful experience." ) );

    sphLightBox = new QCheckBox( tab_5, "sphLightBox" );
    sphLightBox->setGeometry( QRect( 15, 125, 240, 20 ) ); 
    sphLightBox->setText( tr2i18n( "Enable light after spherical explosion" ) );
    QToolTip::add( sphLightBox, tr2i18n( "warning, this can shock your mind :-)" ) );
    QWhatsThis::add( sphLightBox, tr2i18n( "Multiplies the scale factor for particles near you, resulting in a colorful experience." ) );

    cloudsLightenBox = new QCheckBox( tab_5, "cloudsLightenBox" );
    cloudsLightenBox->setEnabled( FALSE );
    cloudsLightenBox->setGeometry( QRect( 210, 150, 195, 20 ) ); 
    cloudsLightenBox->setText( tr2i18n( "Enable lighting of clouds" ) );
    QToolTip::add( cloudsLightenBox, tr2i18n( "initial work. not jet available." ) );

    cloudsBox = new QCheckBox( tab_5, "cloudsBox" );
    cloudsBox->setEnabled( FALSE );
    cloudsBox->setGeometry( QRect( 15, 150, 110, 20 ) ); 
    cloudsBox->setText( tr2i18n( "Enable clouds" ) );
    QToolTip::add( cloudsBox, tr2i18n( "only partially done" ) );
    TabWidget2->insertTab( tab_5, tr2i18n( "FX" ) );

    // signals and slots connections
    connect( PushButton5, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( PushButton4, SIGNAL( clicked() ), this, SLOT( okButton_clicked() ) );
    connect( starsBox, SIGNAL( stateChanged(int) ), this, SLOT( starsBox_stateChanged(int) ) );
    connect( bottomFireBox, SIGNAL( stateChanged(int) ), this, SLOT( bottomFireBox_stateChanged(int) ) );
    connect( tuxBox, SIGNAL( stateChanged(int) ), this, SLOT( logosT_stateChanged(int) ) );
    connect( kdeBox, SIGNAL( stateChanged(int) ), this, SLOT( logosK_stateChanged(int) ) );
    connect( fadeBox, SIGNAL( stateChanged(int) ), this, SLOT( fadeBox_stateChanged(int) ) );
    connect( flaresBox, SIGNAL( stateChanged(int) ), this, SLOT( flaresBox_stateChanged(int) ) );
    connect( cloudsBox, SIGNAL( stateChanged(int) ), this, SLOT( cloudsBox_stateChanged(int) ) );
    connect( detachButton, SIGNAL( clicked() ), this, SLOT( togglePreviewState_clicked() ) );
    connect( applyButton, SIGNAL( clicked() ), this, SLOT( applyButton_clicked() ) );
    connect( updateButton, SIGNAL( clicked() ), this, SLOT( updateButton_clicked() ) );

    // tab order
    setTabOrder( PushButton4, PushButton5 );
    setTabOrder( PushButton5, TabWidget2 );
    setTabOrder( TabWidget2, flashesBox );
    setTabOrder( flashesBox, trailsBox );
    setTabOrder( trailsBox, tuxBox );
    setTabOrder( tuxBox, kdeBox );
    setTabOrder( kdeBox, logosFrequencySlider );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
KFireSaverSetup::~KFireSaverSetup()
{
    // no need to delete child widgets, Qt does it all for us
}

#include "kfiresaversetup.moc"
