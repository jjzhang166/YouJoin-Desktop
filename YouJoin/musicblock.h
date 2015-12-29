//����ģ�飬ʵ�����ֲ��Ź���

#ifndef MUSIC_BLOCK_H
#define MUSIC_BLOCK_H

#include "ui_musicblock.h"

#include <QtWidgets/QWidget>
#include <QPainter>
#include <QIcon>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <QString>
#include <QMediaMetaData>
#include <QTime>
#include <QPalette>

#include "network.h"
#include "songinfo.h"
#include "lrcblock.h"
#include <QJsonDocument>
#include <QTextCodec>
#include <QFileInfo>

#include "nofocusdelegate.h"

//����������Ϣ��ר��ͼƬ����ʻ�ȡ״̬
enum { RECEIVE_INFO, RECEIVE_LINK, RECEIVE_PIC, RECEIVE_LRC };

//ר��ͼƬ�������ʾ״̬
enum { SHOW_PIC, SHOW_LRC };

class YJ_Music_Block : public QWidget{

	Q_OBJECT

public :

	YJ_Music_Block(QWidget *parent = 0);
	~YJ_Music_Block();

	QStringList YJ_Get_Music_List();

signals:

	void YJ_Music_List_Changed();

private slots:

	//˫�������б��еĸ�������ʼ����
	void yj_playlist_table_item_double_clicked(int, int);

	//��������Ԫ��Ϣ
	void yj_update_metadata();

	//���½����� 
	void yj_update_duration(qint64 duration);

	//���²���״̬
	void yj_update_play_state(QMediaPlayer::State state);
	
	//���²��Ž���
	void yj_set_play_position(int position);

	//���¸�ʡ�ʱ����ʾ
	void yj_update_play_positioin(qint64 position);


	void yj_next_button_clicked();
	void yj_back_button_clicked();
	void yj_play_button_clicked();
	void yj_share_button_clicked();
	void yj_add_button_clicked();
	void yj_bigger_button_clicked();
	void yj_pause_button_clicked();
	void yj_lrc_button_clicked();

private:

	//��ʼ��UI����
	void yj_init_ui();

	//��ʼ������ģ��
	void yj_init_player();

	//��ʼ���ź�-������
	void yj_init_connections();

	//��ʼ������ģ��
	void yj_init_network();

	//�򿪱��ظ���
	void yj_open_songs();

	//���ò����б���ɫ
	void yj_set_playlist_table_background();

	//��Ӹ����������б�
	void yj_add_songs(QStringList list);

	//��ղ����б�
	void yj_clear_playlist();
	
	//ɾ��ѡ����Ŀ
	void yj_delete_curr_music();

	//��ȡ��������
	void yj_fetch_data();

	//����ר��ͼƬ
	void yj_rece_pic(QNetworkReply *reply);

	//���ո�����Ϣ
	void yj_rece_info(QNetworkReply *reply);

	//����������
	void yj_rece_lrc(QNetworkReply *reply);

	//���ո�ʵ�ַ
	void yj_rece_link(QNetworkReply *reply);

	//��������ļ�
	void yj_resolve_lrc(const QString &source_file_name);


	Ui::MusicBlock ui;

	QMediaPlayer *music_player;
	QMediaPlaylist *music_list;
	QStringList play_list;
	QString playing_file;
	QMap<qint64, QString> lrc_map;
	YJ_Lrc_Block *lrc_block;
	int curr_index;

	NetWorker *networker;
	QString song_name;
	QString song_artist;
	QString song_id;
	QString pic_url;
	QString lrc_url;
	int receive_state;
	int show_state;

	
};

#endif //MUSIC_BLOCK_H