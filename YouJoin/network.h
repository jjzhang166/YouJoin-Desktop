//网络模块，实现网络功能
//使用单例模式，封装网络接口
//使用instance()获取唯一的NetWorker对象
//使用内部类Private封装私有变量


#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>

class NetWorker : public QObject{
	
	Q_OBJECT

public:
	
	//获取唯一实例
	static NetWorker *instance();
	
	~NetWorker();

	//向url发送get请求
	void get(const QString &url);

	//向url发送post请求
	void post(const QString &url);

signals:
	//操作完成后发射finished信号
	void finished(QNetworkReply *reply);

	//post请求完成后发射该信号,参数为服务器返回的json数据
	void onPostFinished(QByteArray data);

private slots:
	void onFinished();

private:
	class Private;
	friend class Private;
	Private *d;

	//使用单例模式，类的构造函数，复制构造函数和赋值运算符都声明为私有
	//若编译器支持c++ 11，Q_DECL_EQ_DELETE宏替换为 =delete
	explicit NetWorker(QObject *parent = 0);
	NetWorker(const NetWorker &) Q_DECL_EQ_DELETE;
	NetWorker &operator=(NetWorker rhs) Q_DECL_EQ_DELETE;
};


#endif //NETWORK_H
