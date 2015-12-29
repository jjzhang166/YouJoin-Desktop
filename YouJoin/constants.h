//��ų����õ��ĳ���

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>

namespace YJ_CONSTANTS{
	//��¼�������������
	//�û���¼ 0
	//�û�ע�� 1
	const int POST_SIGNIN = 0;
	const int POST_SIGNUP = 1;

	//�û�ע���¼�˿�
	const int PORT_SIGN = 5155;
	//�û�����״̬��֤�˿�
	const int PORT_LOG_STATE = 5156;

	//������udp���ݻ�ȡ�˿�
	const int PORT_GET_DATA_SERVER = 5157;
	//�ͻ���udp���ݻ�ȡ�˿�
	const int PORT_GET_DATA_CLIENT = 5163;

	//�ͻ��˽�����Ϣ���Ͷ˿�
	const int PORT_GET_MSG = 5162;

	//�û����췢����Ϣ�˿�
	const int PORT_CHAT_SEND = 5160;
	//�û����������Ϣ�˿�
	const int PORT_CHAT_RECEIVE = 5161;


	//���ݴ��ͱ�ʶ
	const int GET_DATA_NONE = 0;
	//ͨ��userid��ȡuserinfo
	const int GET_DATA_USERINFO = 1;
	//����userinfo
	const int UPDATE_DATA_USERINFO = 2;
	//ͨ��userid��ȡ�����Ƽ��б�
	const int GET_DATA_RECOMMAND = 3;
	//���useridΪ����
	const int ADD_FRIEND = 4;
	//���Ͷ�̬
	const int POST_PUBLIC_MSG = 5;
	//����˽��
	const int SEND_PRIVATE_MSG = 6;


	//������IP��ַ
	const QString IPADDRESS_LOCALHOST = "127.0.0.1";
	const QString IPADDRESS_REMOTEHOST = "125.216.250.79";

	//������֤��Ϣ
	const QString ONLINE_CHECK_MSG = "online";

	//�ͻ��˷�����֤��Ϣ��ʱ����/���� 60000
	const int PUSH_INTERVAL = 10000;
	//�ͻ��˷�����֤��Ϣ�ĵȴ�ʱ��/����
	const int PUSH_WAIT_INTERVAL = 5000;
	//����������û����ߵ�ʱ����/���� 180000
	const int CHECK_INTERVAL = 30000;


	//������û�����tableˮƽ��ͷ����
	const int TABLE_HEADER_COUNT = 3;
	//������û�����tableˮƽ��ͷ��Ŀö��
	const int USER_ID = 0;
	const int USER_NAME = 1;
	const int USER_IP = 2;

	const QString TABLE_HEADERS_STRING[TABLE_HEADER_COUNT] = {
		QString::fromLocal8Bit("�û�ID"),
		QString::fromLocal8Bit("�û���"),
		QString::fromLocal8Bit("IP��ַ")
	};

	//�����������ļ���
	const char DATA_FILE_NAME[] = "users_information.youjoin";
	//�����������ļ���
	const char INDEX_FILE_NAME[] = "key_and_value.youjoin";
	//������ȫ�û�id�ļ���
	const char USERID_FILE_NAME[] = "alluserid.youjoin";

	enum HOBBIES{
		SPORT, TOUR, CARTON, PHOTO, MOVIE, SCIENCE, DIGIT
	};


}



#endif //CONSTANTS_H