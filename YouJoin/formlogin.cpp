#include "formlogin.h"
#include "formmain.h"

YJ_Login_Form::YJ_Login_Form(QWidget *parent)
: QWidget(parent)
{
	ui.setupUi(this);
	yj_init_ui();
	yj_init_connections();

	tcpClient = new QTcpSocket(this);

	connect(tcpClient, SIGNAL(connected()), this, SLOT(yj_haved_connected()));
	connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(yj_display_error()));

}

YJ_Login_Form::~YJ_Login_Form()
{

}

void YJ_Login_Form::paintEvent(QPaintEvent *event)
{

	QPainter p(this);
	p.drawPixmap(0, 0, QPixmap(":/YouJoin/Resources/login-background.png"));

}

void YJ_Login_Form::yj_init_ui()
{
	
	//去除标题栏
	this->setWindowFlags(Qt::FramelessWindowHint);
	//窗口拖动
	QWidgetResizeHandler *movewin = new QWidgetResizeHandler(this);
	movewin->setMovingEnabled(true);
	//固定大小
	this->setFixedSize(1025, 600);

	exitButton = new I_PushButton(this);
	QIcon icon_exit_button;
	icon_exit_button.addFile(QStringLiteral(":/YouJoin/Resources/background-guide-x.png"), QSize(), QIcon::Normal, QIcon::Off);
	exitButton->setGeometry(QRect(995, 9, 14, 14));
	exitButton->Set_Button_Icons(icon_exit_button);
	exitButton->setFlat(true);
	exitButton->setFocusPolicy(Qt::NoFocus);

	QIcon icon_min_button;
	icon_min_button.addFile(QStringLiteral(":/YouJoin/Resources/background-guide--.png"), QSize(), QIcon::Normal, QIcon::Off);
	ui.min_button->setIcon(icon_min_button);
	ui.min_button->setFlat(true);
	ui.min_button->setFocusPolicy(Qt::NoFocus);

	QIcon icon_signin_button;
	icon_signin_button.addFile(QStringLiteral(":/YouJoin/Resources/button-login.png"), QSize(), QIcon::Normal, QIcon::Off);
	ui.signin_button->setIcon(icon_signin_button);
	ui.signin_button->setFlat(true);
	ui.signin_button->setFocusPolicy(Qt::NoFocus);
	ui.signin_button->setIconSize(QSize(146, 75));

	QIcon icon_signup_button;
	icon_signup_button.addFile(QStringLiteral(":/YouJoin/Resources/button-signup.png"), QSize(), QIcon::Normal, QIcon::Off);
	ui.signup_button->setIcon(icon_signup_button);
	ui.signup_button->setFlat(true);
	ui.signup_button->setFocusPolicy(Qt::NoFocus);
	ui.signup_button->setIconSize(QSize(65, 17));
}

void YJ_Login_Form::yj_init_connections()
{
	connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.signin_button, SIGNAL(clicked()), this, SLOT(yj_signin_button_clicked()));
	connect(ui.signup_button, SIGNAL(clicked()), this, SLOT(yj_signup_button_clicked()));
	connect(ui.min_button, SIGNAL(clicked()), this, SLOT(showMinimized()));
}

void YJ_Login_Form::yj_signin_button_clicked()
{
	yj_init_send_data(YJ_CONSTANTS::POST_SIGNIN);
}

void YJ_Login_Form::yj_signup_button_clicked()
{
	yj_init_send_data(YJ_CONSTANTS::POST_SIGNUP);
}

void YJ_Login_Form::yj_init_send_data(int data_type)
{
	if (ui.username_edit->toPlainText() == ""){
		QMessageBox::warning(this, tr("YouJoin"),
			QString::fromLocal8Bit("用户名不能为空！"),
			QMessageBox::Cancel);
		return;
	}
	if (ui.password_edit->toPlainText() == ""){
		QMessageBox::warning(this, tr("YouJoin"),
			QString::fromLocal8Bit("密码不能为空！"),
			QMessageBox::Cancel);
		return;
	}

	info.set_username(ui.username_edit->toPlainText());
	info.set_password(ui.password_edit->toPlainText());

	info_map.clear();
	if (data_type == YJ_CONSTANTS::POST_SIGNIN) info_map.insert("type", QString("signin"));
	else if (data_type == YJ_CONSTANTS::POST_SIGNUP) info_map.insert("type", QString("signup"));
	
	info_map.insert("username", info.get_username());
	info_map.insert("password", info.get_password());

	yj_connect_server();
}

void YJ_Login_Form::yj_connect_server()
{
	//tcpClient->connectToHost("125.216.250.79", PORT_SIGN);
	tcpClient->connectToHost(YJ_CONSTANTS::IPADDRESS_LOCALHOST, YJ_CONSTANTS::PORT_SIGN);
}

void YJ_Login_Form::yj_haved_connected()
{
	connect(tcpClient, SIGNAL(readyRead()), this, SLOT(yj_accept_msg()));

	if (info_map.empty()) return;
	QVariantList info_list;
	info_list << info_map;
	QJsonDocument jsonDocument = QJsonDocument::fromVariant(info_list);

	if (tcpClient->state() == QAbstractSocket::ConnectedState){
		yj_send_msg(jsonDocument);
	}

}

void YJ_Login_Form::yj_display_error(QAbstractSocket::SocketError)
{

}

void YJ_Login_Form::yj_accept_msg()
{
	QDataStream in(tcpClient);
	in.setVersion(QDataStream::Qt_5_0);
	blockSize = 0;

	if (blockSize == 0){
		in >> blockSize;
	}

	if (blockSize > 0){
		QByteArray data;
		in >> data;
		yj_parse_json(data);
	}
}

void YJ_Login_Form::yj_parse_json(QByteArray &data)
{
	QString str(data);
	QString json_data;

	for (int i = 1; i < str.length(); i++){
		if (str[i] != ' '){
			json_data.append(str[i]);
		}
	}

	QJsonDocument jsonDocument = QJsonDocument::fromJson(json_data.toUtf8());

	QVariantMap result = jsonDocument.toVariant().toMap();

	QString log_res = result[QLatin1Literal("result")].toString();

	if (log_res == "successfully"){
		tcpClient->deleteLater();
// 		int userid = result[QLatin1Literal("userid")].toInt();
// 		info.set_user_id(userid);
		info = user_info(result[QLatin1Literal("userinfo")].toMap());

		QVariantList friendlist = result[QLatin1Literal("friends")].toList();
		for (int i = 0; i < friendlist.size(); i++){
			friends.push_back(user_info(friendlist.at(i).toMap()));
		}

		emit YJ_Login_Success();
	}
	else if(log_res == "failure"){
		QMessageBox::warning(this, tr("YouJoin"),
			QString::fromLocal8Bit("很遗憾，登陆或注册失败！\n请检查用户名密码是否填写正确。\n请检查网络连接是否正常。"),
			QMessageBox::Cancel);
	}

	tcpClient->disconnectFromHost();
	tcpClient->waitForDisconnected();
}

void YJ_Login_Form::yj_send_msg(QJsonDocument &d)
{
	if (d.isEmpty()) return;

	QString hehe = d.toJson();

	QByteArray data;

	QDataStream out(&data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_0);

	out << quint16(0) << hehe.toUtf8();

	out.device()->seek(0);
	out << quint16(data.size() - sizeof(quint16));
	tcpClient->write(data);

}
