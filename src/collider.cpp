#include <collider.h>


bool checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2) {
	Vec2 center1 = pos1 ;
	Vec2 center2 = pos2;
	Vec2 dist = center1 - center2;
	float distLenght = dist.lenght();
	if (distLenght < (radius1 + radius2))
		return true;
	else
		return false;

}

bool checkCircleRect(const Vec2& circlePos, float circleRadius, const Vec2& rectPos, const Vec2& rectSize) {
	float closestX = std::clamp(circlePos.x, rectPos.x, (rectPos.x + rectSize.x)); 
	float closestY = std::clamp(circlePos.y, rectPos.y, (rectPos.y + rectSize.y));
	Vec2 closestPoint = Vec2(closestX, closestY);
	Vec2 dist = circlePos - closestPoint;
	float distLenght = dist.lenght();
	if (distLenght < circleRadius)
		return true;
	else
		return false;
}

bool checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1, const Vec2& rectPos2, const Vec2& rectSize2) { //box then mouse
	float xPrim2 = rectPos2.x + rectSize2.x;
	float yPrim2 = rectPos2.y + rectSize2.y;
	float xPrim1 = rectPos1.x + rectSize1.x;
	float yPrim1 = rectPos1.y + rectSize1.y;
	float x1 = rectPos1.x;
	float y1 = rectPos1.y;
	float x2 = rectPos2.x;
	float y2 = rectPos2.y;

	if (((x2 < xPrim1)&&((x2 > x1)||(xPrim2 > x1)))&&((y2 < yPrim1)&&((y2 > y1)||(yPrim2 > y1)))) 
		return true;
	else 
		return false;
	
}

bool checkPixelsPixels(const Vec2& pixelsPos1, const Vec2& pixelsSize1, const std::vector<unsigned char> pixels1, const Vec2& pixelsPos2, const Vec2& pixelsSize2, const std::vector<unsigned char> pixels2) {

		
	//FIND OVERLAP AREA
	Vec2 LR1 = Vec2(pixelsPos1.x, pixelsPos1.y);
	Vec2 BR1 = Vec2(pixelsPos1.x + pixelsSize1.x, pixelsPos1.y + pixelsSize1.y);

	Vec2 LR2 = Vec2(pixelsPos2.x, pixelsPos2.y);
	Vec2 BR2 = Vec2(pixelsPos2.x + pixelsSize2.x, pixelsPos2.y + pixelsSize2.y);

	Vec2 leftTopOverlap = Vec2(0,0);
	Vec2 rightBotOverlap = Vec2(0,0);

	if (LR2.x > LR1.x)
		leftTopOverlap.x = LR2.x;
	else
		leftTopOverlap.x = LR1.x;

	if (LR2.y > LR1.y)
		leftTopOverlap.y = LR2.y;
	else
		leftTopOverlap.y = LR1.y;

	if (BR2.x < BR1.x)
		rightBotOverlap.x = BR2.x;
	else
		rightBotOverlap.x = BR1.x;

	if (BR2.y < BR1.y)
		rightBotOverlap.y = BR2.y;
	else
		rightBotOverlap.y = BR1.y;

	/*std::cout << "BeePos : LR(" << LR1.x <<" , "<< LR1.y<<") "<< " BR: (" << BR1.x << " , " << BR1.y << ")" << " MousePos: LR(" << LR2.x<<", "<<LR2.y << ") BR: (" << BR2.x << " , " << BR2.y << ")" << " OVERLAP: ("<< leftTopOverlap.x<<", "<<
		leftTopOverlap.y<< ")  ("<<rightBotOverlap.x<<", "<< rightBotOverlap.y<< ")"<<std::endl;*/

	for (int j = leftTopOverlap.y; j < rightBotOverlap.y; j++) {
		for (int i = leftTopOverlap.x; i < rightBotOverlap.x; i++) {
			Vec2 pointBuff1 = Vec2(i, j) - pixelsPos1;
			Vec2 pointBuff2 = Vec2(i, j) - pixelsPos2;

			int posBuff1 = pointBuff1.y * pixelsSize1.x + pointBuff1.x;
			int posBuff2 = pointBuff2.y * pixelsSize2.x + pointBuff2.x;

			int alphaPos1 = posBuff1 * 4 + 3;
			int alphaPos2 = posBuff2 * 4 + 3;

			int alphaValue1 = pixels1[alphaPos1];
			int alphaValue2 = pixels2[alphaPos2];

			if ((alphaValue1 >= 128) && (alphaValue2 >= 128)) {
				//std::cout << "Collision : R1(" << pointBuff1.x << " , " << pointBuff1.y << ") " << " R2: (" << pointBuff2.x << " , " << pointBuff2.y << ")" << std::endl;
				return true;
			}			
			
		}
	}
	return false;
}

bool checkPixelsRect(const Vec2& pixelsPos1, const Vec2& pixelsSize1, const std::vector<unsigned char> pixels1, const Vec2& rectPos, const Vec2& rectSize){


	//FIND OVERLAP AREA
	Vec2 LR1 = Vec2(pixelsPos1.x, pixelsPos1.y);
	Vec2 BR1 = Vec2(pixelsPos1.x + pixelsSize1.x, pixelsPos1.y + pixelsSize1.y);

	Vec2 LR2 = Vec2(rectPos.x, rectPos.y);
	Vec2 BR2 = Vec2(rectPos.x + rectSize.x, rectPos.y + rectSize.y);

	Vec2 leftTopOverlap = Vec2(0, 0);
	Vec2 rightBotOverlap = Vec2(0, 0);

	if (LR2.x > LR1.x)
		leftTopOverlap.x = LR2.x;
	else
		leftTopOverlap.x = LR1.x;

	if (LR2.y > LR1.y)
		leftTopOverlap.y = LR2.y;
	else
		leftTopOverlap.y = LR1.y;

	if (BR2.x < BR1.x)
		rightBotOverlap.x = BR2.x;
	else
		rightBotOverlap.x = BR1.x;

	if (BR2.y < BR1.y)
		rightBotOverlap.y = BR2.y;
	else
		rightBotOverlap.y = BR1.y;

	for (int j = leftTopOverlap.y; j < rightBotOverlap.y; j++) {
		for (int i = leftTopOverlap.x; i < rightBotOverlap.x; i++) {
			Vec2 pointBuff1 = Vec2(i, j) - pixelsPos1;
			int posBuff1 = pointBuff1.y * pixelsSize1.x + pointBuff1.x;
			
			int alphaPos1 = posBuff1 * 4 + 3;
		
			int alphaValue1 = pixels1[alphaPos1];
		
			if ((alphaValue1 >= 128)) {
				return true;
			}

		}
	}
	return false;
}

bool checkCirclePixels(const Vec2& circlePos, float circleRadius, const Vec2& pixelsPos, const Vec2& pixelsSize, const std::vector<unsigned char> pixels) {
	
	//FIND OVERLAP AREA
	Vec2 LR1 = Vec2(pixelsPos.x, pixelsPos.y);
	Vec2 BR1 = Vec2(pixelsPos.x + pixelsSize.x, pixelsPos.y + pixelsSize.y);

	Vec2 LR2 = Vec2(circlePos.x - circleRadius, circlePos.y - circleRadius);
	Vec2 BR2 = Vec2(circlePos.x + circleRadius, circlePos.y + circleRadius);

	Vec2 leftTopOverlap = Vec2(0, 0);
	Vec2 rightBotOverlap = Vec2(0, 0);

	if (LR2.x > LR1.x)
		leftTopOverlap.x = LR2.x;
	else
		leftTopOverlap.x = LR1.x;

	if (LR2.y > LR1.y)
		leftTopOverlap.y = LR2.y;
	else
		leftTopOverlap.y = LR1.y;

	if (BR2.x < BR1.x)
		rightBotOverlap.x = BR2.x;
	else
		rightBotOverlap.x = BR1.x;

	if (BR2.y < BR1.y)
		rightBotOverlap.y = BR2.y;
	else
		rightBotOverlap.y = BR1.y;

	for (int j = leftTopOverlap.y; j < rightBotOverlap.y; j++) {
		for (int i = leftTopOverlap.x; i < rightBotOverlap.x; i++) {
			Vec2 pointBuff1 = Vec2(i, j) - pixelsPos;
			int posBuff1 = pointBuff1.y * pixelsSize.x + pointBuff1.x;

			int alphaPos1 = posBuff1 * 4 + 3;

			int alphaValue1 = pixels[alphaPos1];

			if ((alphaValue1 >= 128)) {
				Vec2 dist = circlePos - Vec2(i, j);
				float distLenght = dist.lenght();
				if (distLenght < circleRadius)
					return true;
			}

		}
	}
	return false;


}