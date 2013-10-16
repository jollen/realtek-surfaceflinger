#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <utils/IPCThreadState.h>
#include <utils/ProcessState.h>
#include <utils/IServiceManager.h>
#include <utils/Log.h>

#include "MokoidSurface.h"

using namespace android;

#define RGBA8888(r, g, b, a)	\
	((((r) & 0xff) <<  0) |	\
	 (((g) & 0xff) <<  8) |	\
	 (((b) & 0xff) << 16) |	\
	 (((a) & 0xff) << 24))

static void draw(char *buf, int w, int h, int stride)
{
	int x, y;

	for (y = 0; y < h; y++) {
		char *row = buf + stride * y;

		for (x = 0; x < w; x++) {
			int r, g, b, a;

			r = (x + y) * 255 / (w + h);
			g = x * 255 / w;
			b = y * 255 / h;
			a = 100 + y * 155 / h;

			/* premultiplied */
			r = r * a / 255;
			g = g * a / 255;
			b = b * a / 255;

			((uint32_t *) row)[x] = RGBA8888(r, g, b, a);
		}
	}
}

static void demo(int x, int y, int w, int h)
{
	char *buf;
	int stride;

    MokoidSurface *surface = new MokoidSurface();

	if (!surface->clientInit(x, y, w, h, &stride)) {
		LOGI("failed to initialize a surface\n");
		return;
	} 
	surface->lockScreen();
    buf = surface->getBuffer();
	draw(buf, w, h, stride);
	surface->unlockScreen();
}

int main(int argc, char **argv)
{
    //sp<ProcessState> proc(ProcessState::self());
    LOGI("MokoidSurface is started.");

	demo(10, 10, 200, 300);
    sleep(5);

	demo(20, 20, 250, 300);
    sleep(5);

    //ProcessState::self()->startThreadPool();
    //IPCThreadState::self()->joinThreadPool();

	return 0;
}
