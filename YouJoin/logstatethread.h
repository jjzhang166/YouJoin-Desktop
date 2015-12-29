//////////////////////////////////////////////////////////////////////////
// 文件名：logstatethread.h
// 类名：YJ_Log_State_Thread
// 类简介：用户在线状态数据发送线程
// 作者：ZZQ
//////////////////////////////////////////////////////////////////////////

#ifndef LOG_STATE_THREAD_H
#define LOG_STATE_THREAD_H

#include <QThread>
#include <QtNetwork>
#include "constants.h"

class YJ_Log_State_Thread : public QThread{

	Q_OBJECT

public:

	YJ_Log_State_Thread(int userID, QObject *parent);

	void run();

signals:

	void error(int socketError, const QString &message);

private:

	QTcpSocket tcpSocket;

	int userID;

};

#endif //LOG_STATE_THREAD_H