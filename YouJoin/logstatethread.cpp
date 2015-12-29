#include "logstatethread.h"

YJ_Log_State_Thread::YJ_Log_State_Thread(int userID, QObject *parent)
: QThread(parent),
userID(userID)
{

}

void YJ_Log_State_Thread::run()
{
	tcpSocket.connectToHost(YJ_CONSTANTS::IPADDRESS_LOCALHOST, 
		YJ_CONSTANTS::PORT_LOG_STATE);
	if (!tcpSocket.waitForConnected(YJ_CONSTANTS::PUSH_WAIT_INTERVAL)){
		emit error(tcpSocket.error(), tcpSocket.errorString());
		return;
	}
	
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	out << (quint16)0;
	out << YJ_CONSTANTS::ONLINE_CHECK_MSG;
	out << userID;
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));

	tcpSocket.write(block);
	tcpSocket.disconnectFromHost();
	tcpSocket.waitForDisconnected();
		
}



