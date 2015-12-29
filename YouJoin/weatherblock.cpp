#include "weatherblock.h"

YJ_Weather_Block::YJ_Weather_Block(QWidget *parent /* = 0 */)
: QWidget(parent)
{
	ui.setupUi(this);

	//去除标题栏
	this->setWindowFlags(Qt::FramelessWindowHint);
	//固定大小
	this->setFixedSize(176, 56);
	//背景透明
	setAttribute(Qt::WA_TranslucentBackground);

	ui.weather_label->setFont(QFont(QString::fromLocal8Bit("微软雅黑"), 14));
	ui.weather_label->setStyleSheet(
		"color:white"
		);
	ui.weather_label->setText(QString("21.548"));

	ui.pic_label->setPixmap(QPixmap(":/YouJoin/Resources/sun.png"));

	networker = NetWorker::instance();

	connect(networker, &NetWorker::finished, [=](QNetworkReply *reply) {
		QJsonParseError error;
		QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll(), &error);
		if (error.error == QJsonParseError::NoError) {
			if (!(jsonDocument.isNull() || jsonDocument.isEmpty()) && jsonDocument.isObject()) {
				QVariantMap data = jsonDocument.toVariant().toMap();
				YJ_Weather_Info weather;
				weather.setCityName(data[QLatin1String("name")].toString());
				QDateTime dateTime;
				dateTime.setTime_t(data[QLatin1String("dt")].toLongLong());
				weather.setDateTime(dateTime);
				QVariantMap main = data[QLatin1String("main")].toMap();
				weather.setTemperature(main[QLatin1String("temp")].toFloat());
				weather.setPressure(main[QLatin1String("pressure")].toFloat());
				weather.setHumidity(main[QLatin1String("humidity")].toFloat());
				QVariantList detailList = data[QLatin1String("weather")].toList();

				//ui.pic_label->setText(weather.cityName());
				if (weather.temperature() > 0)
				ui.weather_label->setText(QString("%1").arg(weather.temperature()));
			}
		}
		reply->deleteLater();
	});

	yj_fetch_weather(QString("Guangzhou,cn"));

}

YJ_Weather_Block::~YJ_Weather_Block()
{

}

void YJ_Weather_Block::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	p.drawPixmap(0, 0, QPixmap(":/YouJoin/Resources/weather-block-background.png"));
}

void YJ_Weather_Block::yj_fetch_weather(const QString &city_name) const
{
	networker->get(QString("http://api.openweathermap.org/data/2.5/weather?q=%1&mode=json&units=metric&lang=zh_cn").arg(city_name));
}