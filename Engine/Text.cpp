#include "Text.h"

Text::Text(std::string textToRender, float rhsSize, float rhsXOffSet, float rhsYOffSet, int rhsLayer)
{
	text = textToRender;
	size = rhsSize;
	xOffSet = rhsXOffSet;
	yOffSet = rhsYOffSet;
	layer = rhsLayer;
}
