#include "help.h"


YJ_Help::YJ_Help(QObject *parent /* = 0 */)
: QObject(parent)
{
	yjh_init_login();
	yjh_init_connections();
	yjh_init_timer();

	udpSender = new QUdpSocket(this);
	udpReceiver = new QUdpSocket(this);
	udpReceiver->bind(YJ_CONSTANTS::PORT_GET_DATA_CLIENT, 
		QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
	connect(udpReceiver, SIGNAL(readyRead()), this, SLOT(yjh_udp_receive_data()));
}

YJ_Help::~YJ_Help(){ }

void YJ_Help::yjh_init_login()
{
	loginForm = new YJ_Login_Form();
	loginForm->show();
}

void YJ_Help::yjh_init_connections()
{
	connect(loginForm, SIGNAL(YJ_Login_Success()), this, SLOT(yjh_login_success()));
	connect(&stateTimer, SIGNAL(timeout()), this, SLOT(yjh_push_log_state()));
	//connect(&dataSocket, SIGNAL(connected()), this, SLOT(yjh_request_data()));
	//connect(&dataSocket, SIGNAL(readyRead()), this, SLOT(yjh_receive_data()));

}

// void YJ_Help::yjh_connect_data_server()
// {
// 	if (getDataType == YJ_CONSTANTS::GET_DATA_NONE) 
// 		return;
// 
// 	if (dataSocket.state() != QAbstractSocket::ConnectedState){
// 		dataSocket.connectToHost(
// 			YJ_CONSTANTS::IPADDRESS_LOCALHOST,
// 			YJ_CONSTANTS::PORT_GET_DATA);
// 	}
// 	else {
// 		yjh_request_data();
// 	}
// 
// }

void YJ_Help::yjh_init_timer()
{
	stateTimer.setInterval(YJ_CONSTANTS::PUSH_INTERVAL);
}

void YJ_Help::yjh_login_success()
{
	loginForm->hide();
	userInfo = loginForm->YJ_get_curr_userinfo();
	friends = loginForm->YJ_get_friend_vec();

	//getDataType = YJ_CONSTANTS::GET_DATA_USERINFO;
	//yjh_connect_data_server();
	//yjh_request_data();
	mainForm = new YJ_Main_Form();
	mainForm->show();
	mainForm->YJ_set_user(userInfo, friends);
	isLogin = true;
	connect(mainForm, SIGNAL(YJ_Detail_Update()), this, SLOT(yjh_update_detail()));
	connect(mainForm, SIGNAL(YJ_add_friend(int)), this, SLOT(yjh_add_friend(int)));
	connect(mainForm, SIGNAL(YJ_push_public_msg(QString)), this, SLOT(yjh_push_public_msg(QString)));
	stateTimer.start();
}

void YJ_Help::yjh_request_data(int getDataType, int add_id)
{
	QVariantMap request_map;
	QJsonDocument jsonDocument;

	request_map.insert("type", getDataType);
	request_map.insert("id", userInfo.get_user_id());

	switch (getDataType){
	case YJ_CONSTANTS::GET_DATA_NONE:
		return;
		break;
	case YJ_CONSTANTS::GET_DATA_USERINFO:

		break;
	case YJ_CONSTANTS::UPDATE_DATA_USERINFO:
	
		request_map.insert("info", userInfo.toVariantMap());							  
		break;
	case YJ_CONSTANTS::ADD_FRIEND:

		if (add_id <= 10000000) return;
		request_map.insert("addid", add_id);
		break;
	case YJ_CONSTANTS::POST_PUBLIC_MSG:

		request_map.insert("msg", publictext);
		break;
	default:
		return;
	}

	if (request_map.empty()) return;
// 	QVariantList request_list;
// 	request_list << request_map;
	jsonDocument = QJsonDocument::fromVariant(request_map);

	QByteArray data = QString(jsonDocument.toJson()).toUtf8();
	udpSender->writeDatagram(
		data.data(), data.size(),
		QHostAddress(YJ_CONSTANTS::IPADDRESS_LOCALHOST), 
		YJ_CONSTANTS::PORT_GET_DATA_SERVER
		);

// 	if (dataSocket.state() == QAbstractSocket::ConnectedState){
// 		if (jsonDocument.isEmpty()) return;
// 		QString jsonstr = jsonDocument.toJson();
// 		QByteArray data;
// 		QDataStream out(&data, QIODevice::WriteOnly);
// 		out.setVersion(QDataStream::Qt_5_0);
// 		out << quint16(0) << jsonstr.toUtf8();
// 		out.device()->seek(0);
// 		out << quint16(data.size() - sizeof(quint16));
// 		dataSocket.write(data);
// 	}

}

// void YJ_Help::yjh_receive_data()
// {
// 	QDataStream in(&dataSocket);
// 	in.setVersion(QDataStream::Qt_5_0);
// 	dataBlockSize = 0;
// 
// 	if (dataBlockSize == 0){
// 		in >> dataBlockSize;
// 	}
// 
// 	if (dataBlockSize <= 0) return;
// 	
// 	QByteArray data;
// 	in >> data;
// 	
// 	QString str(data);
// 
// 	QJsonDocument jsonDocument = QJsonDocument::fromJson(str.toUtf8());
// 
// 
// 	if (getDataType == YJ_CONSTANTS::GET_DATA_USERINFO){
// 		user_info info(jsonDocument);
// 		userInfo = info;
// 		if (mainForm != NULL) mainForm->YJ_set_user(userInfo, friends);
// 	}
// 	else if (getDataType == YJ_CONSTANTS::ADD_FRIEND){
// 		
// 	}
// 	else if (getDataType == YJ_CONSTANTS::UPDATE_DATA_USERINFO){
// 		QVariantList result = jsonDocument.toVariant().toList();
// 		QList<user_info> infoList;
// 		for (int i = 0; i < result.size(); i++){
// 			infoList.append(result[i].toMap());
// 		}
// 
// 		if (infoList.size() > 0){
// 			mainForm->YJ_set_recommand_list(infoList);
// 		}
// 	}
// 	
// 
// 	getDataType = YJ_CONSTANTS::GET_DATA_NONE;
// 	dataSocket.disconnectFromHost();
// 	dataSocket.waitForDisconnected();
// }

void YJ_Help::yjh_push_log_state()
{
	YJ_Log_State_Thread *thread = new YJ_Log_State_Thread(userInfo.get_user_id(), this);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
}

void YJ_Help::yjh_update_detail()
{
	//更新本地数据
	userInfo.set_detail(&mainForm->YJ_get_user_detail());

	//以下是发送数据到服务器的代码
	yjh_request_data(YJ_CONSTANTS::UPDATE_DATA_USERINFO);
}
// void YJ_Help::yjh_update_data()
// {
// 	QVariantMap update_map;
// 
// 	update_map.insert("type", getDataType);
// 	update_map.insert("id", userInfo.get_user_id());
// 	update_map.insert("info", userInfo.toVariantMap());
// 
// 	if (update_map.empty()) return;
// 	QVariantList request_list;
// 	request_list << update_map;
// 	QJsonDocument jsonDocument = QJsonDocument::fromVariant(request_list);
// 
// 	if (dataSocket.state() == QAbstractSocket::ConnectedState){
// 		if (jsonDocument.isEmpty()) return;
// 		QString jsonstr = jsonDocument.toJson();
// 		QByteArray data;
// 		QDataStream out(&data, QIODevice::WriteOnly);
// 		out.setVersion(QDataStream::Qt_5_0);
// 		out << quint16(0) << jsonstr.toUtf8();
// 		out.device()->seek(0);
// 		out << quint16(data.size() - sizeof(quint16));
// 		dataSocket.write(data);
// 
// 
// 		//dataSocket.disconnectFromHost();
// 		//dataSocket.waitForDisconnected();
// 	}
// 
// 	//getDataType = YJ_CONSTANTS::GET_DATA_NONE;
// }
void YJ_Help::yjh_add_friend(int userid)
{
	 yjh_request_data(YJ_CONSTANTS::ADD_FRIEND, userid);
}
void YJ_Help::yjh_push_public_msg(QString msg)
{
	publictext = msg;
	yjh_request_data(YJ_CONSTANTS::POST_PUBLIC_MSG);
}

void YJ_Help::yjh_udp_receive_data()
{
	QByteArray data;
	while (isLogin && udpReceiver->hasPendingDatagrams()){
		data.resize(udpReceiver->pendingDatagramSize());
		udpReceiver->readDatagram(data.data(), data.size());
		yjh_parse_data_json(data);
	}

}

void YJ_Help::yjh_parse_data_json(QByteArray &data)
{
	QString str(data);
	QString json_data;
	for (int i = 0; i < str.length(); i++){
		if (str[i] != ' '){
			json_data.append(str[i]);
		}
	}
	QJsonDocument jsonDocument = QJsonDocument::fromJson(json_data.toUtf8());
	QVariantMap result = jsonDocument.toVariant().toMap();

	int userid = result[QLatin1Literal("id")].toInt();
	int getDataType = result[QLatin1Literal("type")].toInt();

	if (userid != userInfo.get_user_id() &&
		getDataType != YJ_CONSTANTS::POST_PUBLIC_MSG)
		return;

	switch (getDataType){
	case YJ_CONSTANTS::GET_DATA_USERINFO:

		userInfo = user_info(result[QLatin1Literal("info")].toMap());
		if (mainForm != NULL) mainForm->YJ_set_user(userInfo, friends);

		break;

	case YJ_CONSTANTS::ADD_FRIEND:
	{
		userInfo = user_info(result[QLatin1Literal("info")].toMap());
		friends.clear();
		QVariantList friendlist = result[QLatin1Literal("friends")].toList();
		for (int i = 0; i < friendlist.size(); i++){
			friends.push_back(user_info(friendlist.at(i).toMap()));
		}
		if (mainForm != NULL) mainForm->YJ_set_user(userInfo, friends);

		break;
									 
	}

	case YJ_CONSTANTS::UPDATE_DATA_USERINFO:
	{
		QVariantList res_list = result[QLatin1Literal("friendlist")].toList();
		QList<user_info> infoList;
		for (int i = 0; i < res_list.size(); i++){
			infoList.append(res_list[i].toMap());
		}

		if (infoList.size() > 0){
			mainForm->YJ_set_recommand_list(infoList);
		}

		break;
											   
	}

	case YJ_CONSTANTS::POST_PUBLIC_MSG:

		mainForm->YJ_receive_msg(result);

		break;

	default:
		return;
	}
}