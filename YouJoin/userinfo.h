//给出用户信息的声明

#ifndef USER_INFO_H
#define USER_INFO_H

#include "mylist.h"
#include <QString>
#include <QJsonDocument>
#include <QVariant>
#include <vector>
using std::vector;

//存储用户的性别/生日/所在地/工作/爱好等详细信息
class user_detail{
public:
	user_detail();

	user_detail(QVariantMap detailMap);

	QVariantMap toVariantMap();

	user_detail(QString &sex, QString &birthyear, QString &location_city,
		QString &work, LList<QString> *hobbies);

	user_detail & operator=(user_detail& detail);

	~user_detail();

	QString get_sex() const;

	void set_sex(QString sex);

	QString get_birthyear() const;

	void set_birthyear(QString birthyear);

	QString get_location_city() const;

	void set_location_city(QString &city);

	QString get_work() const;

	void set_work(QString &work);

	LList<QString>* get_hobbies_ptr();

	LList<QString> get_hobbies();

	void set_hobbies(LList<QString> *hobbies);
private:

	QString m_sex;
	QString m_birthyear;
	QString m_location;
	QString m_work;
	LList<QString> *m_hobbies = NULL;
};

//用户类，存储用户id，用户名，密码，好友列表，detail，用户ip
class user_info{

public:
	user_info(QString &user, QString &psw);

	user_info(QJsonDocument &jsonDocument);

	user_info(QVariantMap &userMap);

	QJsonDocument toJsonDocument();

	QVariantMap toVariantMap();

	user_info(const user_info &s);

	user_info& operator = (const user_info& s);

	user_info();

	~user_info();

	void set_user_id(int ID);

	int get_user_id() const;

	void set_username(QString &uname);

	QString get_username() const;

	void set_password(QString &psw);

	QString get_password() const;

	void set_friend_list(vector<int> f_list);

	vector<int> *get_friend_list_ptr();

	vector<int> get_friend_list_copy();

	void set_detail(user_detail *de);

	user_detail *get_detail() const;

	QString get_IP() const;

	void set_IP(QString &IP);

	void add_friend(int userid);

private:

	int user_id;
	QString username;
	QString password;
	vector<int> friend_list;
	user_detail *detail = NULL;

	QString m_IP;
};

//存储在内存中的用户简略信息，包括id，用户名，密码，ip
class user_memory{
public:
	user_memory();
	~user_memory();

	user_memory(const user_info &info);

	int get_user_id() const;

	void set_user_id(int id);

	QString get_username() const;

	void set_username(QString &username);

	QString get_password() const;

	void set_password(QString &password);

	QString get_IP() const;

	void set_IP(QString &IP);

private:
	int m_user_id;
	QString m_username;
	QString m_password;
	QString m_IP;
};

#endif //USER_INFO_H