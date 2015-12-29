#include "musicblock.h"

YJ_Music_Block::YJ_Music_Block(QWidget *parent /* = 0 */)
:QWidget(parent)
{
	ui.setupUi(this);
	yj_init_ui();
	yj_init_player();
	yj_init_connections();
	yj_init_network();
	ui.vol_slider->setValue(50);
}

YJ_Music_Block::~YJ_Music_Block()
{

}

void YJ_Music_Block::yj_init_ui()
{
	ui.lrc_button->setFocusPolicy(Qt::NoFocus);
	ui.lrc_button->setFlat(true); 
	ui.lrc_button->setAttribute(Qt::WA_TranslucentBackground);

	QIcon icon_last_button;
	icon_last_button.addFile(":/YouJoin/Resources/back.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.last_button->setIcon(icon_last_button);
	ui.last_button->setFlat(true);
	ui.last_button->setFocusPolicy(Qt::NoFocus);
	ui.last_button->setIconSize(QSize(23, 29));
	//ui.last_button->setGeometry(QRect(0, (132 + 58 * 0), 200, 58));

	QIcon icon_next_button;
	icon_next_button.addFile(":/YouJoin/Resources/next.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.next_button->setIcon(icon_next_button);
	ui.next_button->setFlat(true);
	ui.next_button->setFocusPolicy(Qt::NoFocus);
	ui.next_button->setIconSize(QSize(23, 29));

	QIcon icon_play_button;
	icon_play_button.addFile(":/YouJoin/Resources/play.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.play_button->setIcon(icon_play_button);
	ui.play_button->setFlat(true);
	ui.play_button->setFocusPolicy(Qt::NoFocus);
	ui.play_button->setIconSize(QSize(23, 29));

	QIcon icon_share_button;
	icon_share_button.addFile(":/YouJoin/Resources/share.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.share_button->setIcon(icon_share_button);
	ui.share_button->setFlat(true);
	ui.share_button->setFocusPolicy(Qt::NoFocus);
	ui.share_button->setIconSize(QSize(21, 21));

	QIcon icon_add_button;
	icon_add_button.addFile(":/YouJoin/Resources/add.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.add_button->setIcon(icon_add_button);
	ui.add_button->setFlat(true);
	ui.add_button->setFocusPolicy(Qt::NoFocus);
	ui.add_button->setIconSize(QSize(21, 22));

	QIcon icon_bigger_button;
	icon_bigger_button.addFile(":/YouJoin/Resources/bigger.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.bigger_button->setIcon(icon_bigger_button);
	ui.bigger_button->setFlat(true);
	ui.bigger_button->setFocusPolicy(Qt::NoFocus);
	ui.bigger_button->setIconSize(QSize(21, 17));

	QIcon icon_pause_button;
	icon_pause_button.addFile(":/YouJoin/Resources/pause.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.pause_button->setIcon(icon_pause_button);
	ui.pause_button->setFlat(true);
	ui.pause_button->setFocusPolicy(Qt::NoFocus);
	ui.pause_button->setIconSize(QSize(23, 29));

	ui.album_pic_label->setPixmap(QPixmap(":/YouJoin/Resources/defaultalbumpic.jpg"));
	

	ui.play_slider->setStyleSheet("QSlider::groove:horizontal{border:0px;height:2px;}"
		"QSlider::sub-page:horizontal{background:#c9371e;}"
		"QSlider::add-page:horizontal{background:lightgray;} "
		"QSlider::handle:horizontal{background:white;width:10px;border:#51b5fb 10px;border-radius:1px;margin:-1px 0px -1px 0px;}");

	ui.vol_slider->setStyleSheet("QSlider::groove:horizontal{border:0px;height:2px;}"
		"QSlider::sub-page:horizontal{background:#ffffff;}"
		"QSlider::add-page:horizontal{background:lightgray;} "
		"QSlider::handle:horizontal{background:white;width:10px;border:#51b5fb 10px;border-radius:2px;margin:-2px 0px -2px 0px;}");

	if (ui.playlist_table->columnCount() < 1)
		ui.playlist_table->setColumnCount(2);
	QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
	ui.playlist_table->setHorizontalHeaderItem(0, __qtablewidgetitem);


	//设置列宽
	ui.playlist_table->setColumnWidth(0, 245);
	ui.playlist_table->setColumnWidth(1, 100);

	//禁止编辑单元格内容
	ui.playlist_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//选中一行
	ui.playlist_table->setSelectionBehavior(QAbstractItemView::SelectRows);
	//去掉水平滚动条
	ui.playlist_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//垂直滚动条按项移动
	ui.playlist_table->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
	//去除水平表头
	ui.playlist_table->horizontalHeader()->setFixedHeight(0);
	//去除垂直表头
	ui.playlist_table->verticalHeader()->setFixedWidth(0);
	//设置无边框
	ui.playlist_table->setFrameShape(QFrame::NoFrame);
	//设置不显示格子线
	ui.playlist_table->setShowGrid(false);
	//设置右键菜单
	ui.playlist_table->setContextMenuPolicy(Qt::CustomContextMenu);

	//设置背景颜色
	QPalette pal;
	pal.setBrush(QPalette::Base, QBrush(QColor(0, 0, 0, 50)));
	ui.playlist_table->setPalette(pal);

	//设置竖直滚动条样式
	ui.playlist_table->setStyleSheet(
		"QScrollBar{ width: 5px;background-color: rgb(255, 255, 255);}"
		"QScrollBar::handle{background:rgb(61, 11, 5); border:2px solid transparent; border-radius:3px;}"
		"QScrollBar::handle:hover{background:rgb(42, 9, 9);border:3px solid transparent; border-radius:3px;}"
		"QScrollBar::sub-line{background:transparent;}"
		"QScrollBar::add-line{background:transparent;}"
		"QTableWidget::item:selected { background-color: rgb(97, 17, 7) }");
	//半透明
	ui.playlist_table->setAttribute(Qt::WA_TranslucentBackground);
	ui.playlist_table->verticalHeader()->setDefaultSectionSize(50);
	ui.playlist_table->setTextElideMode(Qt::ElideNone);

	ui.playlist_table->setItemDelegate(new NoFocusDelegate());


	ui.song_label->setWordWrap(true);
	ui.song_label->setFont(QFont(QString::fromLocal8Bit("微软雅黑"), 13));
	ui.song_label->setStyleSheet("color:lightgray;");

	ui.singer_label->setWordWrap(true);
	ui.singer_label->setFont(QFont(QString::fromLocal8Bit("微软雅黑"), 13));
	ui.singer_label->setStyleSheet("color:lightgray;");

	ui.album_label->setWordWrap(true);
	ui.album_label->setFont(QFont(QString::fromLocal8Bit("微软雅黑"), 13));
	ui.album_label->setStyleSheet("color:lightgray;");

	ui.curr_time_label->setWordWrap(true);
	ui.curr_time_label->setFont(QFont(QString::fromLocal8Bit("微软雅黑"), 11));
	ui.curr_time_label->setStyleSheet("color:lightgray;");

	ui.total_time_label->setWordWrap(true);
	ui.total_time_label->setFont(QFont(QString::fromLocal8Bit("微软雅黑"), 7));
	ui.total_time_label->setStyleSheet("color:lightgray;");

	ui.pause_button->setVisible(false);

	lrc_block = new YJ_Lrc_Block(this);
	lrc_block->setGeometry(QRect(50, 90, 380, 370));

	lrc_block->setVisible(false);
}

void YJ_Music_Block::yj_init_connections()
{
	connect(ui.playlist_table, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(yj_playlist_table_item_double_clicked(int, int)));
	connect(music_player, SIGNAL(positionChanged(qint64)), this, SLOT(yj_update_play_positioin(qint64)));
	connect(music_player, SIGNAL(durationChanged(qint64)), this, SLOT(yj_update_duration(qint64)));
	connect(music_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(yj_update_play_state(QMediaPlayer::State)));
	connect(music_player, SIGNAL(metaDataChanged()), this, SLOT(yj_update_metadata()));
	connect(ui.play_slider, SIGNAL(valueChanged(int)), this, SLOT(yj_set_play_position(int)));
	connect(ui.vol_slider, SIGNAL(valueChanged(int)), music_player, SLOT(setVolume(int)));
	connect(ui.last_button, SIGNAL(clicked()), this, SLOT(yj_back_button_clicked()));
	connect(ui.next_button, SIGNAL(clicked()), this, SLOT(yj_next_button_clicked()));
	connect(ui.add_button, SIGNAL(clicked()), this, SLOT(yj_add_button_clicked()));
	connect(ui.bigger_button, SIGNAL(clicked()), this, SLOT(yj_bigger_button_clicked()));
	connect(ui.pause_button, SIGNAL(clicked()), this, SLOT(yj_pause_button_clicked()));
	connect(ui.play_button, SIGNAL(clicked()), this, SLOT(yj_play_button_clicked()));
	connect(ui.lrc_button, SIGNAL(clicked()), this, SLOT(yj_lrc_button_clicked()));
}

void YJ_Music_Block::yj_init_player()
{
	music_player = new QMediaPlayer(this);
	music_list = new QMediaPlaylist(this);

	music_player->setPlaylist(music_list);
	music_list->setPlaybackMode(QMediaPlaylist::Loop);
}

void YJ_Music_Block::yj_init_network()
{
	networker = NetWorker::instance();
	receive_state = RECEIVE_INFO;
	show_state = SHOW_PIC;

	//connect(ui.get_pic_lrc_button, &QPushButton::clicked, [=]() {yj_fetch_data();});

	connect(networker, &NetWorker::finished, [=](QNetworkReply *reply) {
		switch (receive_state){
		case RECEIVE_INFO:
			yj_rece_info(reply);
			yj_fetch_data();
			break;
		case RECEIVE_LINK:
			yj_rece_link(reply);
			yj_fetch_data();
			break;
		case RECEIVE_PIC:
			yj_rece_pic(reply);
			yj_fetch_data();
			break;
		case RECEIVE_LRC:
			yj_rece_lrc(reply);
			receive_state = RECEIVE_INFO;
			break;
		default:

			break;
		}

	});
}

void YJ_Music_Block::yj_open_songs()
{
	QStringList fileList = QFileDialog::getOpenFileNames(this, QString::fromLocal8Bit("添加音乐"), QString(), QString("MP3 (*.mp3)"));
	yj_add_songs(fileList);
}

void YJ_Music_Block::yj_add_songs(QStringList list)
{
	foreach(QString fileName, list)
	{
		if (play_list.contains(fileName))
			continue;
		play_list.append(fileName);

		music_list->addMedia(QUrl::fromLocalFile(fileName));
		ui.playlist_table->insertRow(ui.playlist_table->rowCount());

		for (int i = 0; i < ui.playlist_table->columnCount(); i++){
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setFont(QFont(QString::fromLocal8Bit("微软雅黑"), 11));
			item->setTextColor(QColor(194, 196, 208));
			
			ui.playlist_table->setItem(ui.playlist_table->rowCount() - 1, i, item);

		}
		ui.playlist_table->item(ui.playlist_table->rowCount() - 1, 0)->setText(QFileInfo(fileName).baseName());

	}
	yj_set_playlist_table_background();

	emit YJ_Music_List_Changed();
}

void YJ_Music_Block::yj_set_playlist_table_background()
{
	for (int i = 0; i < ui.playlist_table->rowCount(); i++){
		if (i % 2 == 0){
			for (int j = 0; j < ui.playlist_table->columnCount(); j++){
				QTableWidgetItem *item = ui.playlist_table->item(i, j);
				if (item){
					const QColor color = QColor(0, 0, 0, 50);
					item->setBackgroundColor(color);
				}
			}
		}
	}
}

void YJ_Music_Block::yj_clear_playlist()
{
	music_player->stop();
	play_list.clear();
	music_list->clear();
	while (ui.playlist_table->rowCount())
		ui.playlist_table->removeRow(0);

	ui.total_time_label->setText(tr("00:00"));
	ui.song_label->setText(tr("Name "));
	ui.singer_label->setText(tr("Musician"));
	ui.album_label->setText(tr("Album"));
}

void YJ_Music_Block::yj_delete_curr_music()
{
	play_list.removeAt(curr_index);
	ui.playlist_table->removeRow(curr_index);
	music_list->removeMedia(curr_index);
}

void YJ_Music_Block::yj_playlist_table_item_double_clicked(int row, int)
{
	QFile file(play_list.at(row));
	if (!file.open(QIODevice::ReadOnly)) {
		ui.playlist_table->item(row, 1)->setText(QString::fromLocal8Bit("失效"));
		return;
	}
	file.close();
	music_list->setCurrentIndex(row);

	music_player->play();
}

void YJ_Music_Block::yj_update_duration(qint64 duration)
{
	ui.play_slider->setRange(0, duration);
	ui.play_slider->setEnabled(duration > 0);
	ui.play_slider->setPageStep(duration / 10);
}

void YJ_Music_Block::yj_update_metadata()
{
	curr_index = music_list->currentIndex();
	playing_file = play_list.at(curr_index);

	song_name.clear();
	song_artist.clear();

	song_name = music_player->metaData(QMediaMetaData::Title).toString();
	ui.song_label->setText(song_name);

	song_artist = music_player->metaData(QMediaMetaData::Author).toString();
	ui.singer_label->setText(song_artist);

	ui.album_label->setText(music_player->metaData(QMediaMetaData::AlbumTitle).toString());

	ui.album_pic_label->setPixmap(QPixmap(":/YouJoin/Resources/defaultalbumpic.jpg"));

	if (song_name != ""){
		receive_state = RECEIVE_INFO;
		yj_fetch_data();
	}
	
	if (ui.song_label->text() == "")
		ui.song_label->setText(QString::fromLocal8Bit("未知歌曲"));
	if (ui.singer_label->text() == "")
		ui.singer_label->setText(QString::fromLocal8Bit("未知音乐家"));
	if (ui.album_label->text() == "")
		ui.album_label->setText(QString::fromLocal8Bit("未知专辑"));

	if (ui.playlist_table->rowCount() == 0){
		ui.total_time_label->setText(tr("00:00"));
		ui.song_label->setText(tr("Name "));
		ui.singer_label->setText(tr("Musician"));
		ui.album_label->setText(tr("Album"));
	}
}

void YJ_Music_Block::yj_update_play_state(QMediaPlayer::State state)
{
	if (state == QMediaPlayer::PlayingState) {
		ui.play_button->setVisible(false);
		ui.pause_button->setVisible(true);

	}
	else {
		ui.play_button->setVisible(true);
		ui.pause_button->setVisible(false);
	}

	if (state != QMediaPlayer::StoppedState){
		playing_file = play_list.at(music_list->currentIndex());
		//resolve_lrc(playingfile);
	}
}

void YJ_Music_Block::yj_set_play_position(int position)
{
	if (qAbs(music_player->position() - position) > 99)
		music_player->setPosition(position);
}

void YJ_Music_Block::yj_update_play_positioin(qint64 position)
{
	ui.play_slider->setValue(position);

	//获取该音频文件的总时长参数，单位为毫秒
	qint64 total_time_value = music_player->duration();

	//这3个参数分别代表了时，分，秒；60000毫秒为1分钟，所以分钟第二个参数是先除6000,第3个参数是直接除1s
	QTime total_time(0, (total_time_value / 60000) % 60, (total_time_value / 1000) % 60);

	//传进来的time参数代表了当前的时间
	QTime current_time(0, (position / 60000) % 60, (position / 1000) % 60);
	ui.curr_time_label->setText(current_time.toString(tr("mm:ss")));
	ui.total_time_label->setText(total_time.toString(tr("mm:ss")));
}

void YJ_Music_Block::yj_next_button_clicked()
{
	music_list->setCurrentIndex(music_list->nextIndex());
	music_player->play();
}

void YJ_Music_Block::yj_back_button_clicked()
{
	music_list->setCurrentIndex(music_list->previousIndex());
	music_player->play();
}

void YJ_Music_Block::yj_play_button_clicked()
{
	if (music_player->state() == QMediaPlayer::PausedState){
		music_player->play();
	}
}

void YJ_Music_Block::yj_pause_button_clicked()
{
	if (music_player->state() == QMediaPlayer::PlayingState){
		music_player->pause();
	}
}

void YJ_Music_Block::yj_share_button_clicked()
{

}

void YJ_Music_Block::yj_add_button_clicked()
{
	QStringList fileList = QFileDialog::getOpenFileNames(this, QString::fromLocal8Bit("添加音乐"), QString(), QString("MP3 (*.mp3)"));
	yj_add_songs(fileList);
}

void YJ_Music_Block::yj_bigger_button_clicked()
{

}

void YJ_Music_Block::yj_lrc_button_clicked()
{
	if (show_state == SHOW_PIC){
		show_state = SHOW_LRC;
		ui.album_pic_label->setVisible(false);
		lrc_block->setVisible(true);
		yj_resolve_lrc(playing_file);

		}
		else if (show_state == SHOW_LRC){
		show_state = SHOW_PIC;
		lrc_block->setVisible(false);
		ui.album_pic_label->setVisible(true);


		}
	
}

void YJ_Music_Block::yj_fetch_data()
{
	QString query = QUrl::toPercentEncoding(song_name + " " + song_artist);
	switch (receive_state){
	case RECEIVE_INFO:
		networker->get(
			QString("http://tingapi.ting.baidu.com/v1/restserver/ting?from=webapp_music&method=baidu.ting.search.catalogSug&format=json&callback=&query=" +
			query +
			"&_=1413017198449")
			);
		break;
	case RECEIVE_LINK:
		networker->get(QString("http://ting.baidu.com/data/music/links?songIds=" + song_id));
		break;
	case RECEIVE_PIC:
		networker->get(pic_url);
		break;
	case RECEIVE_LRC:
		lrc_url = QString("http://qukufile2.qianqian.com") + lrc_url;
		networker->get(lrc_url);
		break;
	default:
		break;
	}
}

void YJ_Music_Block::yj_rece_info(QNetworkReply *reply)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (!(jsonDocument.isNull() || jsonDocument.isEmpty()) && jsonDocument.isObject()) {
			QVariantMap data = jsonDocument.toVariant().toMap();

			song_info song;
			song.set_order(data[QLatin1String("order")].toString());
			song.set_error_code(data[QLatin1String("error_code")].toString());

			QVariantList result_list = data[QLatin1String("song")].toList();
			QVariantList album_list = data[QLatin1String("album")].toList();

			QList<song_result *> results;
			foreach(QVariant s, result_list){
				QVariantMap sm = s.toMap();
				song_result *result = new song_result;
				result->set_songid(sm[QLatin1String("songid")].toString());
				result->set_songname(sm[QLatin1String("songname")].toString());
				result->set_has_mv(sm[QLatin1String("has_mv")].toInt());
				result->set_yyr_artist(sm[QLatin1String("yyr_artist")].toInt());
				result->set_artistname(sm[QLatin1String("artistname")].toString());
				results.append(result);
			}

			song.set_song_results(results);

			QList<album_info *> album_infos;
			foreach(QVariant a, album_list){
				QVariantMap ai = a.toMap();
				album_info *info = new album_info;
				info->set_albumid(ai[QLatin1String("albumid")].toString());
				info->set_albumname(ai[QLatin1String("albumname")].toString());
				info->set_artistname(ai[QLatin1String("artistname")].toString());
				info->set_artistpic(ai[QLatin1String("artistpic")].toString());
				album_infos.append(info);
			}

			song.set_album_infos(album_infos);

			if (results.count() > 0){
				song_result *temp = new song_result;
				temp = results[0];
				/*album_info *album_temp = album_infos[0];

				if (ui.song_label->text() == QString::fromLocal8Bit("未知歌曲")){
				ui.song_label->setText(temp->get_songname());
				ui.singer_label->setText(temp->get_artistname());
				ui.album_label->setText(album_temp->get_albumname());
				}*/

				song_id = temp->get_songid();
			}
			receive_state = RECEIVE_LINK;

		}
	}
	reply->deleteLater();
}

void YJ_Music_Block::yj_rece_link(QNetworkReply *reply)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (!(jsonDocument.isNull() || jsonDocument.isEmpty()) && jsonDocument.isObject()) {
			QVariantMap data = jsonDocument.toVariant().toMap();

			song_link link;
			link.set_errorcode(data[QLatin1String("errorCode")].toString());

			QVariantMap song_data_map = data[QLatin1String("data")].toMap();

			song_data sdata;
			sdata.set_xcode(song_data_map[QLatin1String("xcode")].toString());

			QVariantList slist = song_data_map[QLatin1String("songList")].toList();
			QList<song_list *> slists;
			foreach(QVariant s, slist){
				QVariantMap sl = s.toMap();
				song_list *list = new song_list;
				list->set_songpic_radio(sl[QLatin1String("songPicRadio")].toString());
				list->set_lrclink(sl[QLatin1String("lrcLink")].toString());
				slists.append(list);
			}
			sdata.set_song_lists(slists);
			link.set_song_data(sdata);


			song_data temp2 = link.get_song_data();
			QList<song_list *> temp3 = temp2.get_song_lists();
			if (temp3.count() > 0){
				song_list *templist = temp3[0];

				pic_url = templist->get_songpic_radio();
				lrc_url = templist->get_lrclick();
			}
			receive_state = RECEIVE_PIC;
		}
	}
	reply->deleteLater();
}

void YJ_Music_Block::yj_rece_lrc(QNetworkReply *reply)
{
	if (reply->error() == QNetworkReply::NoError){
		QByteArray data = reply->readAll();

		QString strfile;
		strfile = QCoreApplication::applicationDirPath();

		QUrl url(strfile);
		QFileInfo fileInfo(url.path());
		QString fileName = fileInfo.fileName();
		//fileName = song_id + ".lrc";
		QString temp = playing_file;
		fileName = temp.remove(temp.right(3)) + "lrc";

		QFile *file = new QFile(fileName);
		if (!file->open(QIODevice::WriteOnly)) {
			delete file;
			file = 0;
			return;
		}

		QDataStream out(file);
		out << data;
		file->close();
		delete file;
		file = 0;

		
	}
	reply->deleteLater();
}

void YJ_Music_Block::yj_rece_pic(QNetworkReply *reply)
{
	if (reply->error() == QNetworkReply::NoError)
	{
		QByteArray data = reply->readAll();
		QPixmap currentPicture;

		if (currentPicture.loadFromData(data)){
			ui.album_pic_label->setPixmap(currentPicture);
		}

		receive_state = RECEIVE_LRC;
	}
	reply->deleteLater();
}

void YJ_Music_Block::yj_resolve_lrc(const QString &source_file_name)
{
	lrc_map.clear();
	if (source_file_name.isEmpty())
		return;
	QString file_name = source_file_name;
	QString lrc_file_name = file_name.remove(file_name.right(3)) + "lrc";//把音频文件的后缀改成lrc后缀
	
	// 打开歌词文件
	QFile file(lrc_file_name);
	if (!file.open(QIODevice::ReadOnly)) {
		//lrc->setText(mediaplayer->metaData(QMediaMetaData::Title).toString());
		return;
	}

	QByteArray temp = file.readAll();

	QString all_text;
	for (int i = 0; i < temp.size(); i++){
		if (temp.at(i) != 0) all_text.append(temp.at(i));
	}



	lrc_block->YJ_set_text(all_text);

	file.close();
	// 将歌词按行分解为歌词列表
	QStringList lines = all_text.split("\n");

	//这个是时间标签的格式[00:05.54]
	//正则表达式d{2}表示匹配2个数字
	QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");
	foreach(QString oneline, lines) {
		QString temp = oneline;
		temp.replace(rx, "");//用空字符串替换正则表达式中所匹配的地方,这样就获得了歌词文本
		// 然后依次获取当前行中的所有时间标签，并分别与歌词文本存入QMap中
		//indexIn()为返回第一个匹配的位置，如果返回为-1，则表示没有匹配成功
		//正常情况下pos后面应该对应的是歌词文件
		int pos = rx.indexIn(oneline, 0);
		while (pos != -1) { //表示匹配成功
			QString cap = rx.cap(0);//返回第0个表达式匹配的内容
			// 将时间标签转换为时间数值，以毫秒为单位
			QRegExp regexp;
			regexp.setPattern("\\d{2}(?=:)");
			regexp.indexIn(cap);
			int minute = regexp.cap(0).toInt();
			regexp.setPattern("\\d{2}(?=\\.)");
			regexp.indexIn(cap);
			int second = regexp.cap(0).toInt();
			regexp.setPattern("\\d{2}(?=\\])");
			regexp.indexIn(cap);
			int millisecond = regexp.cap(0).toInt();
			qint64 totalTime = minute * 60000 + second * 1000 + millisecond * 10;
			// 插入到lrc_map中
			lrc_map.insert(totalTime, temp);
			pos += rx.matchedLength();
			pos = rx.indexIn(oneline, pos);//匹配全部
		}
	}
	// 如果lrc_map为空
	if (lrc_map.isEmpty()) {
		//lrc->setText(mediaplayer->metaData(QMediaMetaData::Title).toString());
		return;
	}
}

QStringList YJ_Music_Block::YJ_Get_Music_List()
{
	return play_list;
}