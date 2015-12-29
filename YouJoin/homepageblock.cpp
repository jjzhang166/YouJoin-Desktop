#include "homepageblock.h"

YJ_Homepage_Block::YJ_Homepage_Block(QWidget *parent /* = 0 */)
: QWidget(parent)
{
	yj_init_ui();
}

YJ_Homepage_Block::~YJ_Homepage_Block()
{

}

void YJ_Homepage_Block::yj_init_ui()
{
	
	
	weather_block = new YJ_Weather_Block(this);

}