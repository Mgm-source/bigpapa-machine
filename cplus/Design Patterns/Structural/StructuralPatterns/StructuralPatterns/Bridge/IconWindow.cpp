#include "IconWindow.h"

void IconWindow::DrawContents() {
	WindowImp* imp = getWindowImp();
	if (imp == nullptr) 
	{
		imp->deviceBitMap();
	}
}
