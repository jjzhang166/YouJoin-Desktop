#include "locationpicker.h"

YJ_Location_Picker::YJ_Location_Picker(QWidget *parent /* = 0 */)
: QWidget(parent)
{
	ui.setupUi(this);
	yj_init_ui();
	yj_init_connections();
	yj_init_data();
	
}

YJ_Location_Picker::~YJ_Location_Picker()
{
}

void YJ_Location_Picker::yj_init_ui()
{
	//去除标题栏
	this->setWindowFlags(Qt::FramelessWindowHint);
	//固定大小
	this->setFixedSize(145, 100);
	//背景透明
	setAttribute(Qt::WA_TranslucentBackground);
}

void YJ_Location_Picker::yj_init_connections()
{
	connect(ui.provinceBox, SIGNAL(currentIndexChanged(int)), this, SLOT(yj_province_changed(int)));
}

void YJ_Location_Picker::yj_init_data()
{
	QString file_name = "area.json";
	// 打开文件
	QFile file(file_name);
	if (!file.open(QIODevice::ReadOnly)) {
		return;
	}
	QByteArray temp = file.readAll();
	file.close();

	QString str(temp);
	QString json_data;

	for (int i = 1; i < str.length(); i++){
		if (str[i] == ' ')
			continue;

		if (str[i] == '\''){
			json_data.append('\"');
			continue;
		}

		json_data.append(str[i]);
	}

	QJsonDocument jsonDocument = QJsonDocument::fromJson(json_data.toUtf8());
	locationMap = jsonDocument.toVariant().toMap();

	QVariantMap provinceMap = locationMap[QLatin1String("area0")].toMap();

	provinceNumList = provinceMap.keys();
	
	
	for (int i = 0; i < provinceMap.size(); i++){
		provinceList.append(provinceMap[provinceNumList[i]].toString());
	}

	ui.provinceBox->addItems(provinceList);
	ui.provinceBox->setCurrentIndex(0);

}

void YJ_Location_Picker::yj_province_changed(int index)
{
	cityList.clear();
	cityNumList.clear();
	QVariantMap tempMap = locationMap[QLatin1String("area1")].toMap();
	//QVariantMap cityMap = tempMap.find("120000").toMap();

	QVariantList cityVList = tempMap[provinceNumList[index]].toList();

	for (int i = 0; i < cityVList.size(); i++){
		QVariantList tempList = cityVList[i].toList();
		cityList.append(tempList[0].toString());
		cityNumList.append(tempList[1].toString());
	}
	
	ui.cityBox->clear();
	ui.cityBox->addItems(cityList);

}

QString YJ_Location_Picker::YJ_Get_Location()
{
	return ui.provinceBox->currentText() + ui.cityBox->currentText();
}
