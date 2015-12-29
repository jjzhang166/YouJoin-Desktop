//天气信息类

#ifndef WEATHER_INFO_H
#define WEATHER_INFO_H

#include <QString>
#include <QList>
#include <QDateTime>

class YJ_Weather_Info{
public :
	YJ_Weather_Info()
	{

	}
	~YJ_Weather_Info(){}

	QString desc() const
	{
		return _desc;
	}
	void setDesc(const QString &desc)
	{
		_desc = desc;
	}

	QString icon() const
	{
		return _icon;
	}
	void setIcon(const QString &icon)
	{
		_icon = icon;
	}

	QString cityName() const
	{
		return _cityname;
	}
	void setCityName(const QString &cityName)
	{
		_cityname = cityName;
	}

	quint32 id() const
	{
		return _id;
	}
	void setId(quint32 id)
	{
		_id = id;
	}

	QDateTime dateTime() const
	{
		return _datetime;
	}
	void setDateTime(const QDateTime &dateTime)
	{
		_datetime = dateTime;
	}

	float temperature() const
	{
		return _temperature;
	}
	void setTemperature(float temperature)
	{
		_temperature = temperature;
	}

	float humidity() const
	{
		return _humidity;
	}
	void setHumidity(float humidity)
	{
		_humidity = humidity;
	}

	float pressure() const
	{
		return _pressure;
	}
	void setPressure(float pressure)
	{
		_pressure = pressure;
	}
private:
	QString _cityname;
	QString _desc;
	QString _icon;
	quint32 _id;
	QDateTime _datetime;
	float _temperature;
	float _humidity;
	float _pressure;
};

#endif //WEATHER_INFO_H