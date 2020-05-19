#pragma once
#ifndef MAPCART_H
#define MAPCART_H

struct PixelList		// структура, кот. описывает элемент списка связанной области
{
	Itype x, y;					// координаты пикселя
	Itype color;				// цвет пикселя
};

void ReadColorMap(char * );							// прочитаиь карту из файла

void CreatePlist(void);								// создать из карты списки связных областей
void RegionSize(void);								// количество пикселей одного цвета
void PixelAdd(Itype, Itype, Itype, Itype);			// добавление пикселя в список Plist
void PixelCheck(Itype, Itype, Itype, Itype);		// проверка соседних пикселей
Dtype Distance2(Itype, Itype, Itype, Itype);		// определяет расстояние между двумя пикселями

Itype  IsLine(Itype, Dtype *);							// является ли связанная область отрезком
Itype  IsRectangle(Itype, Dtype *, Dtype *, Itype *);	// является ли связанная область прямоугольником
Itype  IsEllips(Itype, Itype *);						// является ли связанная область эллипсом


#endif 