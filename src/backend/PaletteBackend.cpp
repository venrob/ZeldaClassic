#include "PaletteBackend.h"
#include "GraphicsBackend.h"
#include "Backend.h"
#include "../zc_alleg.h"
#include <cassert>

PaletteBackend::PaletteBackend()
{
	copyPalette(black_palette, pal_);
	buildPixelMaps();
}

PaletteBackend::~PaletteBackend() {}

void PaletteBackend::applyPaletteToScreen()
{
	set_palette(pal_);
	buildPixelMaps();
}

void PaletteBackend::copyPalette(PALETTE src, PALETTE dest)
{
	memcpy(dest, src, sizeof(PALETTE));
}

void PaletteBackend::setPalette(PALETTE newpal)
{
	copyPalette(newpal, pal_);
	buildPixelMaps();
}

void PaletteBackend::getPalette(PALETTE targetpal)
{
	copyPalette(pal_, targetpal);
}

void PaletteBackend::setPaletteEntry(int entry, RGB color)
{
	if (entry >= 0 && entry <= 255)
		pal_[entry] = color;
	buildPixelMaps();
}

void PaletteBackend::getPaletteEntry(int entry, RGB &color)
{
	if (entry >= 0 && entry <= 255)
		color = pal_[entry];
}

void PaletteBackend::setPaletteRange(PALETTE newpal, int first, int last)
{
	if (first >= 0 && first <= last && last <= 255)
	{
		memcpy(pal_ + first, newpal + first, (last - first + 1) * sizeof(RGB));
	}
	buildPixelMaps();
}

void PaletteBackend::interpolatePalettes(PALETTE first, PALETTE second, int interpValue, int rangeFirst, int rangeSecond, PALETTE result)
{
	if (rangeFirst >= 0 && rangeFirst <= rangeSecond && rangeSecond <= 255)
	{
		for (int i = rangeFirst; i <= rangeSecond; i++)
		{
			result[i].r = (first[i].r * (64 - interpValue) + second[i].r * interpValue) / 64;
			result[i].g = (first[i].g * (64 - interpValue) + second[i].g * interpValue) / 64;
			result[i].b = (first[i].b * (64 - interpValue) + second[i].b * interpValue) / 64;
		}
	}
	buildPixelMaps();
}

int PaletteBackend::virtualColorOfEntry(int entry)
{
	return entry;
}

void PaletteBackend::selectPalette()
{
	select_palette(pal_);
}

void PaletteBackend::buildPixelMaps()
{
	//Just fill each array and then run glPixelMapfv on them. No alpha channel support just yet.
	for (int i = 0; i < 256; i++)
	{
		I_to_R[i] = (float)pal_[i].r / 255.0f;
		I_to_G[i] = (float)pal_[i].g / 255.0f;
		I_to_B[i] = (float)pal_[i].b / 255.0f;
		I_to_A[i] = 1.0f;
	}
	glPixelMapfv(GL_PIXEL_MAP_I_TO_R, 256, I_to_R);
	glPixelMapfv(GL_PIXEL_MAP_I_TO_G, 256, I_to_G);
	glPixelMapfv(GL_PIXEL_MAP_I_TO_B, 256, I_to_B);
	glPixelMapfv(GL_PIXEL_MAP_I_TO_A, 256, I_to_A);

}