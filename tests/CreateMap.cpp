#include "Common.h"



void DrowLine(Itype **, Itype , Itype, Itype , Itype, Itype, Itype, Itype);
void DrowRectangle(Itype **, Itype , Itype, Itype , Itype, Itype, Itype, Itype);
void DrowElips(Itype **, Itype, Itype, Itype, Itype, Itype, Itype, Itype);

//
// создать карту размером Xsize х Ysize, изобразить на ней линии и фигуры
// ncol - максимально возможное количество цветов на карте
// сохранить карту в файле filename
//
void CreateMap(char *filename, Itype Xsize, Itype Ysize, Itype ncol)
{
	errno_t err;
	size_t sw;
	char *buf;
	
	Itype row, col;
	Itype **Map;		

	FILE *fr;

	err = fopen_s(&fr, filename, "wb");
	if (err !=0 )
	{
		printf( "CreateMap - Unable to open file %s",filename);
		exit(-1);
	}
	
	Map = (Itype**)calloc(Ysize, sizeof(Itype*));		//  строки в массиве
			

	if (Map == nullptr)
	{
		printf ( "CreateMap - Map can't be allocated.\n") ;
		exit(-1);
	}

	for (row = 0; row < Ysize; row++)
	{
		Map[row] = (Itype*)calloc(Ysize, sizeof(Itype));			//  столбцы в массиве
		if (Map[row] == nullptr)
		{
			printf( "CreateMap - Map %i can't be allocated.\n", row);
			exit(-1);
		}

		memset(Map[row], 0, Xsize * sizeof(Itype));
	}


	// заполнение карты
	// нарисовать фигуры на карте Map
	// фигуры могут накладываться одна на другую и терять свои свойства

	// !!! НЕДОПУСКАЕТСЯ ВЫХОД ФИГУРЫ ЗА ГРАНИЦЫ КАРТЫ !!! фигура не будет отображена
	// Максимальный номер цвкта  - 9 ! Устанавливается в Test_MapCart
	// 0 - цвет фона карты. Устанавливается автоматически

	DrowLine(Map, Xsize, Ysize, 15, 60, 75, 59, 5);			// отрезок (Map, Xsize, Ysize,x0, y0, x1, y1, color) 
	DrowLine(Map, Xsize, Ysize, 35, 70, 75, 83, 2);			// отрезок (Map, Xsize, Ysize,x0, y0, x1, y1, color) 
	DrowElips(Map, Xsize, Ysize, 21, 44, 12, 18, 7);		// эллипс  (Map, Xsize, Ysize,x0, y0, A, B, color) 
	DrowLine(Map, Xsize, Ysize, 55, 57, 88, 89, 2);			// отрезок (Map, Xsize, Ysize,x0, y0, x1, y1, color) 
	DrowRectangle(Map, Xsize, Ysize, 2, 4, 30, 15, 1);		// прямоугольник (Map, Xsize, Ysize,x0, y0, x1, y1, color) 

//	DrowLine(Map, Xsize, Ysize, 3, 6, 3, 6, 5);				// портим прямоугольник

	DrowRectangle(Map, Xsize, Ysize, 64, 38, 86, 54, 2);	// прямоугольник (Map, Xsize, Ysize,x0, y0, x1, y1, color) 
	DrowElips(Map, Xsize, Ysize, 52, 25, 22, 8, 4);			// эллипс  (Map, Xsize, Ysize,x0, y0, A, B, color)
	DrowLine(Map, Xsize, Ysize, 63, 17, 91, 4, 3);			// отрезок (Map, Xsize, Ysize,x0, y0, x1, y1, color) 

	// запись файла
	
	// размеры карты и количество цветов

	sw = fwrite( &Xsize, sizeof(Itype), 1, fr);
	sw = fwrite( &Ysize, sizeof(Itype), 1, fr);
	sw = fwrite( &ncol, sizeof(Itype), 1, fr);

	// карта
	for (row = 0; row < Ysize; row++)
	{
		
		sw=fwrite(Map[row], sizeof(Itype), Xsize, fr);		// запись карты в файл .dat

		for (col = 0; col < Xsize; col++)			// вывод на экран
			printf("%i", Map[row][col]);
		printf("\n");
	}

	// освобождаем память на карту
	for (row = 0; row < Ysize; row++)
	{
		free( Map[row]);
	}
	
	free( Map);

	fclose(fr);

	return;
}
//
// записать в Map отрезок по конечным точкам цвета color
//
void DrowLine(Itype **Map, Itype Xsize, Itype Ysize, Itype x0, Itype y0, Itype x1, Itype y1, Itype color)
{

	Itype row, col, d1, d2, dm;
	Itype max_x, min_x, max_y, min_y;
	
	double a, b , s , f, del;

	if ((x0 >= Xsize || x1 >= Xsize || x0 < 0 || x1 < 0) ||
		(y0 >= Ysize || y1 >= Ysize || y0 < 0 || y1 < 0))
	{
		printf(" DrowLine: wrong parameters\n");
		return;
	}

	d1 = y1 - y0;
	d2 = x1 - x0;
	dm = abs(d1);
	if (abs(d2) > abs(d1)) dm = abs(d2);

	// определяем наибольшее max min y, что бы не выходить за него при округлении
	if (d1 > 0) { max_y = y1; min_y = y0; }
	else		{ max_y = y0; min_y = y1; }
	if (d2 > 0) { max_x = x1; min_x = x0; }
	else		{ max_x = x0; min_x = x1; }

	// строим прямую
	if (d2 == 0.0)			// вертикальная прямая
	{
		col = x0;
		for (row = min_y; row <= max_y; row++)
		{
			Map[row][col] = color;
		}
	}
	else
	{
		if (d1 == 0)		// горизонтальная прямая
		{
			row = y0;
			for (col = min_x; col <=max_x; col++)
			{
				Map[row][col] = color;
			}
		}
		else				// наклонная прямая
		{
			a = (double)d1 / (double)d2;
			b = (double)y1 - a * (double)x1;

			s = (double)min_x;
			f = (double)max_x;
			del = 1.0 / (dm );	// дробим шаг между строчками
			
			while ( s < f )
			{
				row = round(a*s + b);
				col = round(s);
				Map[row][col] = color;
				s += del;
			}
		}
	}
	
	return;
}

//
// записать в Map прямоугольник // сторонам поля 
//
void DrowRectangle(Itype **Map, Itype Xsize, Itype Ysize, Itype x0, Itype y0, Itype x1, Itype y1, Itype color)
{

	Itype row;
	Itype d1, max_y, min_y;

	if ((x0 >= Xsize || x1 >= Xsize || x0 < 0 || x1 < 0) ||
		(y0 >= Ysize || y1 >= Ysize || y0 < 0 || y1 < 0))
	{
		printf(" DrowRectangle: wrong parameters\n");
		return;
	}

	d1 = y1 - y0;
	if (d1 > 0) { max_y = y1; min_y = y0; }
	else { max_y = y0; min_y = y1; }

	printf ("Rectangle parameters. Color= [%i]", color );
	printf ( "x0=%i   y0=[%i] \n", x0,  y0 );
	printf ("x1=%i   y1=[%i] \n", x1, y1);

	for (row = min_y; row <= max_y; row++)
	{
		DrowLine(Map, Xsize, Ysize, x0, row, x1, row, color);		// зарисовываем прямоугольник как множество горизонтальных отрезков 
	}

	return;
}


//
// записать в Map элипс 
//
void DrowElips(Itype **Map, Itype Xsize, Itype Ysize, Itype x0, Itype y0, Itype A, Itype B, Itype color)
{

	Itype  x1, y1, m;
	double d, Alfa;

	if ((x0+A >= Xsize || x0-A < 0 || A < 0) ||
		(y0+B >= Ysize || y0-B < 0 || B < 0))
	{
		printf( " DrowElips: wrong parameters\n");
		return;
	}


	// выбираем больший радиус
	m = A;
	if (m < B) m = B;

	d = M_PI / (double)(12 * m);  // шаг изменения угла при построении элипса

	Alfa = 0.0;
	while (Alfa <= M_PI * 2.0)
	{
		x1 = (double)A * cos(Alfa);
		y1 = (double)B * sin(Alfa);
		x1 += x0;
		y1 += y0;
			
		Alfa += d;

		Map[y1][x1] = color;

		DrowLine(Map, Xsize, Ysize, x0, y0, x1, y1, color);		// зарисовываем элипс как множество отрезков от центра к границе

	}

	return;
}
