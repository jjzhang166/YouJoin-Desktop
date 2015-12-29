//音乐模块，实现音乐播放功能

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

//网络音乐信息，专辑图片，歌词获取状态
enum { RECEIVE_INFO, RECEIVE_LINK, RECEIVE_PIC, RECEIVE_LRC };

//专辑图片，歌词显示状态
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

	//双击播放列表中的歌曲，开始播放
	void yj_playlist_table_item_double_clicked(int, int);

	//更新音乐元信息
	void yj_update_metadata();

	//更新进度条 
	void yj_update_duration(qint64 duration);

	//更新播放状态
	void yj_update_play_state(QMediaPlayer::State state);
	
	//更新播放进度
	void yj_set_play_position(int position);

	//更新歌词、时间显示
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

	//初始化UI界面
	void yj_init_ui();

	//初始化播放模块
	void yj_init_player();

	//初始化信号-槽连接
	void yj_init_connections();

	//初始化网络模块
	void yj_init_network();

	//打开本地歌曲
	void yj_open_songs();

	//设置播放列表背景色
	void yj_set_playlist_table_background();

	//添加歌曲到播放列表
	void yj_add_songs(QStringList list);

	//清空播放列表
	void yj_clear_playlist();
	
	//删除选定曲目
	void yj_delete_curr_music();

	//获取网络数据
	void yj_fetch_data();

	//接收专辑图片
	void yj_rece_pic(QNetworkReply *reply);

	//接收歌曲信息
	void yj_rece_info(QNetworkReply *reply);

	//接收网络歌词
	void yj_rece_lrc(QNetworkReply *reply);

	//接收歌词地址
	void yj_rece_link(QNetworkReply *reply);

	//解析歌词文件
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