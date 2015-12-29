//////////////////////////////////////////////////////////////////////////
// �ļ�����logstatethread.h
// ������YJ_Log_State_Thread
// ���飺�û�����״̬���ݷ����߳�
// ���ߣ�ZZQ
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