#include "network.h"

class NetWorker::Private{
public:
	Private(NetWorker *q) : manager(new QNetworkAccessManager(q)){}
	QNetworkAccessManager *manager;
	QNetworkReply *reply;
};

NetWorker *NetWorker::instance()
{
	static NetWorker netWorker;
	return &netWorker;
}

NetWorker::NetWorker(QObject *parent /* = 0 */)
: QObject(parent), d(new NetWorker::Private(this))
{
	connect(d->manager, &QNetworkAccessManager::finished, this,
		&NetWorker::finished);
}

NetWorker::~NetWorker()
{
	delete d;
	d = 0;
}

void NetWorker::get(const QString &url)
{
	d->manager->get(QNetworkRequest(QUrl(url)));
}

void NetWorker::post(const QString &url)
{

	d->manager = new QNetworkAccessManager();
	QNetworkRequest network_request;
	QByteArray post_data;

	//设置发送的数据
	post_data.append("user_name=yy233&");
	post_data.append("user_password=yy233");

	//设置头信息
	network_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	network_request.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());

	//设置url
	network_request.setUrl(QUrl(url));

	//发送请求
	d->reply = d->manager->post(network_request, post_data);
	connect(d->reply, SIGNAL(finished()), this, SLOT(onFinished()));

}

void NetWorker::onFinished()
{
	QString temp = (QString)d->reply->readAll();

	int start = temp.indexOf('{');
	int end = temp.lastIndexOf('}');

	temp.remove(0, start);
	temp.remove(end, temp.size() - end);

	emit onPostFinished(temp.toLatin1());
	d->reply->deleteLater();
}