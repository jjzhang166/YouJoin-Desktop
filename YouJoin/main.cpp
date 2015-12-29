#include <QtWidgets/QApplication>
#include <QResource>

#include "help.h"
#include "formmain.h"
#include "formlogin.h"

#include "forminfocollect.h"
#include "locationpicker.h"
#include "sidebar.h"
//#include "userblock.h"
//#include "musicblock.h"
//#include "weatherblock.h"
#include "friendblock.h"
#include "recommandblock.h"
#include "moreblock.h"
#include "userinfocard.h"
#include "userinfo.h"
#include "searchbar.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//加载资源文件
	QResource::registerResource("youjoin.rcc");
	YJ_Help help;

	//YJ_Main_Form w3;
	//w3.show();

	/*user_info info;
	YJ_User_Info_Card card(info);
	card.show();*/

// 	YJ_Recommand_Block w;
// 	w.show();

	//YJ_More_Block w;
	//w.show();
// 	YJ_InfoCollection_Form infocollection;
// 	infocollection.show();

// 	YJ_Location_Picker picker;
// 	picker.show();
	
	//YJ_Login_Form w;
	//w.show();
	//YJ_Sidebar w2;
	//w2.show();


	//YJ_Friend_Block w7;
	//w7.show();
	//YJ_User_Block w4(true, QString("freedomzzq"));
	//w4.show();
	//YJ_Music_Block w5;
	//w5.show();
	//YJ_Weather_Block w6;
	//w6.show();
	return a.exec();
}
