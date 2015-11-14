#include "kfiresaversetup.h"

KFireSaverSetup::KFireSaverSetup( QWidget* parent)
    : QDialog( parent )
{
  ui_.setupUi(this);

    // signals and slots connections
    /*connect( PushButton5, SIGNAL( clicked() ), this, SLOT( reject() ) );
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
    */
}
