#include "forminfocollect.h"

YJ_InfoCollection_Form::YJ_InfoCollection_Form(QWidget *parent /* = 0 */)
: QWidget(parent)
{
	ui.setupUi(this);

	yj_init_ui();
	yj_init_connections();
	yj_init_show_info();
}

YJ_InfoCollection_Form::~YJ_InfoCollection_Form()
{

}

void YJ_InfoCollection_Form::yj_init_ui()
{
	locationPicker = new YJ_Location_Picker(this);
	locationPicker->setGeometry(QRect(90, 260, 145, 100));

	QStringList workList;
	workList.append(QString::fromLocal8Bit("请选择您的职业"));
	workList.append(QString::fromLocal8Bit("学生"));
	workList.append(QString::fromLocal8Bit("程序员"));
	workList.append(QString::fromLocal8Bit("教师"));
	workList.append(QString::fromLocal8Bit("医生"));
	workList.append(QString::fromLocal8Bit("护士"));
	workList.append(QString::fromLocal8Bit("销售员"));
	workList.append(QString::fromLocal8Bit("编辑"));
	workList.append(QString::fromLocal8Bit("作家"));
	workList.append(QString::fromLocal8Bit("画家"));
	workList.append(QString::fromLocal8Bit("运动员"));

	ui.workBox->addItems(workList);

	sexRadioGroup.addButton(ui.sex_man, 0);
	sexRadioGroup.addButton(ui.sex_woman, 1);

	hobbiesCheckGroup.addButton(ui.hobby_sport, YJ_CONSTANTS::HOBBIES::SPORT);
	hobbiesCheckGroup.addButton(ui.hobby_tour, YJ_CONSTANTS::HOBBIES::TOUR);
	hobbiesCheckGroup.addButton(ui.hobby_carton, YJ_CONSTANTS::HOBBIES::CARTON);
	hobbiesCheckGroup.addButton(ui.hobby_photo, YJ_CONSTANTS::HOBBIES::PHOTO);
	hobbiesCheckGroup.addButton(ui.hobby_movie, YJ_CONSTANTS::HOBBIES::MOVIE);
	hobbiesCheckGroup.addButton(ui.hobby_science, YJ_CONSTANTS::HOBBIES::SCIENCE);
	hobbiesCheckGroup.addButton(ui.hobby_digit, YJ_CONSTANTS::HOBBIES::DIGIT);
	hobbiesCheckGroup.setExclusive(false);

	QIcon icon_okButton;
	icon_okButton.addFile(":/YouJoin/Resources/save.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.okButton->setIcon(icon_okButton);
	ui.okButton->setFlat(true);
	ui.okButton->setFocusPolicy(Qt::NoFocus);
	ui.okButton->setIconSize(QSize(117, 60));

	QFont font(QString::fromLocal8Bit("微软雅黑"), 14);
	ui.sex_man->setFont(font);
	ui.sex_man->setStyleSheet("color:lightgray;");
	ui.sex_woman->setFont(font);
	ui.sex_woman->setStyleSheet("color:lightgray;");
	ui.hobby_carton->setFont(font);
	ui.hobby_carton->setStyleSheet("color:lightgray;");
	ui.hobby_digit->setFont(font);
	ui.hobby_digit->setStyleSheet("color:lightgray;");
	ui.hobby_movie->setFont(font);
	ui.hobby_movie->setStyleSheet("color:lightgray;");
	ui.hobby_photo->setFont(font);
	ui.hobby_photo->setStyleSheet("color:lightgray;");
	ui.hobby_science->setFont(font);
	ui.hobby_science->setStyleSheet("color:lightgray;");
	ui.hobby_sport->setFont(font);
	ui.hobby_sport->setStyleSheet("color:lightgray;");
	ui.hobby_tour->setFont(font);
	ui.hobby_tour->setStyleSheet("color:lightgray;");


}

void YJ_InfoCollection_Form::yj_init_connections()
{
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(yj_ok_button_clicked()));

}

void YJ_InfoCollection_Form::yj_ok_button_clicked()
{
 	user_detail de;
 
 	if (sexRadioGroup.checkedId() == 0)
 		de.set_sex(QString::fromLocal8Bit("男"));
 	else de.set_sex(QString::fromLocal8Bit("女"));
 
 	QList<QAbstractButton *> checks = hobbiesCheckGroup.buttons();
 	for (int i = 0; i < checks.size(); i++){
 		if (checks[i]->isChecked())
 			de.get_hobbies_ptr()->append(checks[i]->text());
 	}
 
 	de.set_work(ui.workBox->currentText());
 	de.set_birthyear(ui.dateEdit->text());
 	de.set_location_city(locationPicker->YJ_Get_Location());

	setDetail(de);
 
 	emit YJ_Detail_Update();
}

void YJ_InfoCollection_Form::setDetail(user_detail d)
{
	detail = d;
}

user_detail YJ_InfoCollection_Form::getDetail()
{
	return detail;
}

void YJ_InfoCollection_Form::yj_init_show_info()
{
	if (detail.get_sex() == QString::fromLocal8Bit("男"))
		ui.sex_man->setChecked(true);
	else if (detail.get_sex() == QString::fromLocal8Bit("女"))
		ui.sex_woman->setChecked(true);
}