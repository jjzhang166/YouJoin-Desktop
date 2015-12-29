#include "userinfo.h"

user_detail::user_detail()
{
	m_sex = "ÄÐ";
	m_location = "";
	m_birthyear = "1970";
	m_work = "";
	m_hobbies = new LList<QString>();
}

user_detail::~user_detail()
{

}

user_detail::user_detail(QVariantMap detailMap)
{
	if (detailMap.size() < 5) return;

	m_sex = detailMap[QLatin1Literal("sex")].toString();
	m_birthyear = detailMap[QLatin1Literal("birth")].toString();
	m_location = detailMap[QLatin1Literal("location")].toString();
	m_work = detailMap[QLatin1Literal("work")].toString();

	m_hobbies = new LList<QString>();

	QVariantList hobbiesList = detailMap[QLatin1Literal("hobbies")].toList();
	for (int i = 0; i < hobbiesList.size(); i++){
		m_hobbies->append(hobbiesList[i].toString());
	}
}

QVariantMap user_detail::toVariantMap()
{
	QVariantMap map;
	map.clear();
	map.insert("sex", m_sex);
	map.insert("birth", m_birthyear);
	map.insert("work", m_work);
	map.insert("location", m_location);

	QVariantList hobbiesList;
	for (m_hobbies->moveToStart(); m_hobbies->currPos() < m_hobbies->length();
		m_hobbies->next()){
		hobbiesList.append(m_hobbies->getValue());
	}
	map.insert("hobbies", hobbiesList);

	return map;
}

user_detail::user_detail(QString &sex, QString &birthyear, QString &location_city,
	QString &work, LList<QString> *hobbies)
{
	m_sex = sex;
	m_birthyear = birthyear;
	m_location = location_city;
	m_work = work;
	set_hobbies(hobbies);
	m_hobbies = new LList<QString>();
}

user_detail & user_detail::operator = (user_detail& detail)
{
	m_sex = detail.get_sex();
	m_birthyear = detail.get_birthyear();
	m_location = detail.get_location_city();
	m_work = detail.get_work();
	set_hobbies(detail.get_hobbies_ptr());
	return *this;
}

QString user_detail::get_sex() const
{
	return m_sex;
}

void user_detail::set_sex(QString sex)
{
	m_sex = sex;
}

QString user_detail::get_birthyear() const
{
	return m_birthyear;
}

void user_detail::set_birthyear(QString birthyear)
{
	m_birthyear = birthyear;
}

QString user_detail::get_location_city() const
{
	return m_location;
}

void user_detail::set_location_city(QString &city)
{
	m_location = city;
}

QString user_detail::get_work() const
{
	return m_work;
}

void user_detail::set_work(QString &work)
{
	m_work = work;
}

LList<QString>* user_detail::get_hobbies_ptr()
{
	return m_hobbies;
}

LList<QString> user_detail::get_hobbies()
{
	return *m_hobbies;
}

void user_detail::set_hobbies(LList<QString> *hobbies)
{
	if (m_hobbies != NULL){
		delete m_hobbies;
	}
	m_hobbies = new LList<QString>();
	//m_hobbies.append("");
	//if (hobbies->length() < 2) return;
	for (hobbies->moveToStart(); hobbies->currPos() < hobbies->length(); hobbies->next()){
		if (hobbies->getable())
			m_hobbies->append(hobbies->getValue());
	}
}

//////////////////////////////////////////////////////////////////////////

user_info::user_info(QString &user, QString &psw)
{
	username = user;
	password = psw;
	if (detail == NULL) detail = new user_detail();
	user_id = 0;
	//friend_list.push_back(0);
}

user_info::user_info(QJsonDocument &jsonDocument)
{

	if (!jsonDocument.isArray()) {
		user_id = 0;
		username = "";
		password = "";
		//friend_list.push_back(0);
		if (detail == NULL) detail = new user_detail();

		return;
	}

	QVariantList result = jsonDocument.toVariant().toList();
	if (result.size() < 1) {
		user_id = 0;
		username = "";
		password = "";
		//friend_list.push_back(0);
		detail = new user_detail();

		return;
	}
	QVariantMap map = result[0].toMap();

	user_id = map[QLatin1Literal("userid")].toInt();
	username = map[QLatin1Literal("username")].toString();
	password = map[QLatin1Literal("password")].toString();

	QVariantList friendlist = map[QLatin1Literal("friendlist")].toList();
	for (int i = 0; i < friendlist.size(); i++){
		friend_list.push_back(friendlist[i].toInt());
	}

	if (detail != NULL) delete detail;
	detail = new user_detail(map[QLatin1Literal("detail")].toMap());
}

user_info::user_info(QVariantMap &userMap)
{
	if (userMap.size() < 1){
		user_id = 0;
		username = "";
		password = "";
		//friend_list.push_back(0);
		if (detail == NULL) detail = new user_detail();
		return;
	}

	user_id = userMap[QLatin1Literal("userid")].toInt();
	username = userMap[QLatin1Literal("username")].toString();
	password = userMap[QLatin1Literal("password")].toString();

	QVariantList friendlist = userMap[QLatin1Literal("friendlist")].toList();
	for (int i = 0; i < friendlist.size(); i++){
		friend_list.push_back(friendlist[i].toInt());
	}

	if (detail != NULL) delete detail;
	detail = new user_detail(userMap[QLatin1Literal("detail")].toMap());
}

QVariantMap user_info::toVariantMap()
{
	QVariantMap info_map;
	info_map.clear();
	info_map.insert("userid", get_user_id());
	info_map.insert("username", get_username());
	info_map.insert("password", get_password());

	QVariantList friendlist;
	if (friend_list.size() > 1){
		for (int i = 0; i < friend_list.size(); i++){
			friendlist.append(friend_list.at(i));
		}
		// 		for (friend_list.moveToStart(); friend_list.currPos() < friend_list.length(); friend_list.next()){
		// 			friendlist.append(friend_list.getValue());
		// 		}
	}
	info_map.insert("friendlist", friendlist);

	QVariantMap detailMap;
	if (detail != NULL) {
		detailMap = detail->toVariantMap();
	}
	info_map.insert("detail", detailMap);

	return info_map;
}

QJsonDocument user_info::toJsonDocument()
{
	QVariantList info_list;
	info_list << this->toVariantMap();

	QJsonDocument jsonDocument = QJsonDocument::fromVariant(info_list);
	return jsonDocument;
}

user_info::user_info(const user_info &s)
{
	user_id = s.user_id;
	username = s.username;
	password = s.password;
	if (detail == NULL) detail = new user_detail();
	set_detail(s.get_detail());
	set_friend_list(s.friend_list);
}

user_info& user_info::operator = (const user_info& s)
{
	user_id = s.user_id;
	QString tempusername = s.username;
	QString temppass = s.password;

	set_username(tempusername);
	username = tempusername;
	password = temppass;
	set_detail(s.get_detail());
	set_friend_list(s.friend_list);
	return *this;
}

user_info::user_info()
{
	if (detail == NULL) detail = new user_detail();
	username = "error";
	password = "";
	user_id = 0;
	//friend_list.push_back(0);

}
user_info::~user_info()
{
	if (detail != NULL) {
		delete detail;
		detail = NULL;
	}
}

void user_info::set_user_id(int ID)
{
	user_id = ID;

}

int user_info::get_user_id() const
{
	return user_id;
}

void user_info::set_username(QString &uname)
{
	username = uname;
}

QString user_info::get_username() const
{
	return username;
}

void user_info::set_password(QString &psw)
{
	password = psw;
}

QString user_info::get_password() const
{
	return password;
}

void user_info::set_friend_list(vector<int> f_list)
{
	friend_list.clear();
	for (int i = 0; i < f_list.size(); i++){
		friend_list.push_back(f_list.at(i));
	}

	// 	for (f_list.moveToStart(); f_list.currPos() < f_list.length(); f_list.next()){
	// 		int a = f_list.getValue();
	// 		friend_list.append(a);
	// 	}
}

vector<int> *user_info::get_friend_list_ptr()
{
	return &friend_list;
}

vector<int> user_info::get_friend_list_copy()
{
	return friend_list;
}

void user_info::set_detail(user_detail *de)
{

	detail->set_birthyear(de->get_birthyear());
	detail->set_hobbies(de->get_hobbies_ptr());
	detail->set_location_city(de->get_location_city());
	detail->set_sex(de->get_sex());
	detail->set_work(de->get_work());
}

user_detail *user_info::get_detail() const
{
	return detail;
}

QString user_info::get_IP() const
{
	return m_IP;
}

void user_info::set_IP(QString &IP)
{
	m_IP = IP;
}

void user_info::add_friend(int userid)
{
	if (userid <= 10000000) return;
	friend_list.push_back(userid);
}

//////////////////////////////////////////////////////////////////////////

user_memory::user_memory(){}
user_memory::~user_memory(){}

user_memory::user_memory(const user_info &info)
{
	m_user_id = info.get_user_id();
	m_username = info.get_username();
	m_password = info.get_password();
	m_IP = info.get_IP();
}

int user_memory::get_user_id() const
{
	return m_user_id;
}
void user_memory::set_user_id(int id)
{
	m_user_id = id;
}

QString user_memory::get_username() const
{
	return m_username;
}

void user_memory::set_username(QString &username)
{
	m_username = username;
}

QString user_memory::get_password() const
{
	return m_password;
}

void user_memory::set_password(QString &password)
{
	m_password = password;
}

QString user_memory::get_IP() const
{
	return m_IP;
}

void user_memory::set_IP(QString &IP)
{
	m_IP = IP;
}

