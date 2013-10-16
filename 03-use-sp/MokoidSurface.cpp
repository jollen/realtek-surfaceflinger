/*
**
** Copyright 2013, Moko365 Inc.
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#define LOG_TAG "MokoidSurface"

#include <utils/Log.h>
#include <utils/misc.h>

#include <ui/SurfaceComposerClient.h>
#include <ui/Region.h>
#include <ui/Rect.h>

#include "MokoidSurface.h"

using namespace android;

/*
 * Lock screen will get draw buffer. 
 */
void MokoidSurface::lockScreen(void)
{
	Surface::SurfaceInfo info;

	surfaceflinger_surface->lock(&info);

    drawBuffer = (char *)info.bits;
}

char *MokoidSurface::getBuffer(void)
{
    return drawBuffer;
}

void MokoidSurface::unlockScreen(void)
{
	surfaceflinger_surface->unlockAndPost();
}

int MokoidSurface::getFormat(int depth)
{
	int fmt;

	switch (depth) {
	case 16:
		fmt = PIXEL_FORMAT_RGB_565;
		break;
	case 32:
		fmt = PIXEL_FORMAT_RGBA_8888;
		break;
	default:
		fmt = PIXEL_FORMAT_UNKNOWN;
		break;
	}

	return fmt;
}

MokoidSurface::~MokoidSurface()
{
}

MokoidSurface::MokoidSurface() :
    surfaceflinger_surface(NULL),
	surfaceflinger_client(NULL)
{
}

int MokoidSurface::clientInit(int x, int y, int w, int h, int *stride)
{
	int depth = 32;
	int fmt;

	surfaceflinger_client = new SurfaceComposerClient;
	if (surfaceflinger_client == NULL) {
		LOGE("failed to create client\n");
		return 0;
	}

	fmt = getFormat(depth);
	if (fmt == PIXEL_FORMAT_UNKNOWN) {
		LOGE("failed to find a format for depth %d\n", depth);
		return 0;
	}

	surfaceflinger_surface = surfaceflinger_client->createSurface(getpid(), 0, w, h, fmt, 0);
	if (surfaceflinger_surface == NULL) {
		LOGE("failed to create surface\n");
		return 0;
	}

	surfaceflinger_client->openTransaction();
	surfaceflinger_surface->setPosition(x, y);
	surfaceflinger_surface->setLayer(INT_MAX);
	surfaceflinger_client->closeTransaction();

	if (stride)
		*stride = w * depth / 8;

	return 1;
}
