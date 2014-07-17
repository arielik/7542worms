#include "Sprite.h"


Sprite::Sprite()
	:imageId(""), width(0), height(0), rows(0),
	currentFrame(0), currentRow(0), repeat(true)
{

}

Sprite::Sprite(std::string imageId, int width, int height, int rows, bool repeat)
					:imageId(imageId), width(width), height(height), rows(rows)
					 ,currentFrame(0), currentRow(0), repeat(repeat)
{
}

Sprite::Sprite(const Sprite & sprite)
	:imageId(sprite.imageId), width(sprite.width), 
	 height(sprite.height), rows(sprite.rows), 
	 currentFrame(sprite.currentFrame), currentRow(sprite.currentRow), repeat(sprite.repeat)
		
{
}


Sprite::~Sprite(void)
{
}


void Sprite::clean()
{
	this->currentFrame=0;
	this->currentRow=0;
	//this->sleepFrame=0;
}
	
void Sprite::update() 
{
	if (repeat) {
		this->currentRow++;
		if (this->currentRow >= this->rows) 
		{
			this->currentRow = 0;
		}
	} else {
		this->currentRow++;
		if (this->currentRow >= this->rows) 
		{
			this->currentRow = this->rows - 1;
		}
	}

}

bool Sprite::isLastFrame()
{
	return (this->currentRow == this->rows - 1);
}