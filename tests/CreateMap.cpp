//#include <iostream>
//#include <fstream>

//#include <stdio.h>
#include "Common.h"

//using namespace std;

void DrowLine(Itype **, Itype , Itype, Itype , Itype, Itype, Itype, Itype);
void DrowRectangle(Itype **, Itype , Itype, Itype , Itype, Itype, Itype, Itype);
void DrowElips(Itype **, Itype, Itype, Itype, Itype, Itype, Itype, Itype);

//
// ������� ����� �������� Xsize � Ysize, ���������� �� ��� ����� � ������
// ncol - ����������� ��������� ���������� ������ �� �����
// ��������� ����� � ����� filename
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
	
	Map = (Itype**)calloc(Ysize, sizeof(Itype*));		//  ������ � �������
			

	if (Map == nullptr)
	{
		printf ( "CreateMap - Map can't be allocated.\n") ;
		exit(-1);
	}

	for (row = 0; row < Ysize; row++)
	{
		Map[row] = (Itype*)calloc(Ysize, sizeof(Itype));			//  ������� � �������
		if (Map[row] == nullptr)
		{
			printf( "CreateMap - Map %i can't be allocated.\n", row);
			exit(-1);
		}

		memset(Map[row], 0, Xsize * sizeof(Itype));
	}


	// ���������� �����
	// ���������� ������ �� ����� Map
	// ������ ����� ������������� ���� �� ������ � ������ ���� ��������

	// !!! ������������� ����� ������ �� ������� ����� !!! ������ �� ����� ����������
	// ������������ ����� �����  - 9 ! ��������������� � Test_MapCart
	// 0 - ���� ���� �����. ��������������� �������������

	DrowLine(Map, Xsize, Ysize, 15, 60, 75, 59, 5);			// ������� (Map, Xsize, Ysize,x0, y0, x1, y1, color) 
	DrowLine(Map, Xsize, Ysize, 35, 70, 75, 83, 2);			// ������� (Map, Xsize, Ysize,x0, y0, x1, y1, color) 
	DrowElips(Map, Xsize, Ysize, 21, 44, 12, 18, 7);		// ������  (Map, Xsize, Ysize,x0, y0, A, B, color) 
	DrowLine(Map, Xsize, Ysize, 55, 57, 88, 89, 2);			// ������� (Map, Xsize, Ysize,x0, y0, x1, y1, color) 
	DrowRectangle(Map, Xsize, Ysize, 2, 4, 30, 15, 1);		// ������������� (Map, Xsize, Ysize,x0, y0, x1, y1, color) 

//	DrowLine(Map, Xsize, Ysize, 3, 6, 3, 6, 5);				// ������ �������������

	DrowRectangle(Map, Xsize, Ysize, 64, 38, 86, 54, 2);	// ������������� (Map, Xsize, Ysize,x0, y0, x1, y1, color) 
	DrowElips(Map, Xsize, Ysize, 52, 25, 22, 8, 4);			// ������  (Map, Xsize, Ysize,x0, y0, A, B, color)
	DrowLine(Map, Xsize, Ysize, 63, 17, 91, 4, 3);			// ������� (Map, Xsize, Ysize,x0, y0, x1, y1, color) 

	// ������ �����
	
	// ������� ����� � ���������� ������

	sw = fwrite( &Xsize, sizeof(Itype), 1, fr);
	sw = fwrite( &Ysize, sizeof(Itype), 1, fr);
	sw = fwrite( &ncol, sizeof(Itype), 1, fr);

	// �����
	for (row = 0; row < Ysize; row++)
	{
		
		sw=fwrite(Map[row], sizeof(Itype), Xsize, fr);		// ������ ����� � ���� .dat

		for (col = 0; col < Xsize; col++)			// ����� �� �����
			printf("%i", Map[row][col]);
		printf("\n");
	}

	// ����������� ������ �� �����
	for (row = 0; row < Ysize; row++)
	{
		free( Map[row]);
	}
	
	free( Map);

	fclose(fr);

	return;
}
//
// �������� � Map ������� �� �������� ������ ����� color
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

	// ���������� ���������� max min y, ��� �� �� �������� �� ���� ��� ����������
	if (d1 > 0) { max_y = y1; min_y = y0; }
	else		{ max_y = y0; min_y = y1; }
	if (d2 > 0) { max_x = x1; min_x = x0; }
	else		{ max_x = x0; min_x = x1; }

	// ������ ������
	if (d2 == 0.0)			// ������������ ������
	{
		col = x0;
		for (row = min_y; row <= max_y; row++)
		{
			Map[row][col] = color;
		}
	}
	else
	{
		if (d1 == 0)		// �������������� ������
		{
			row = y0;
			for (col = min_x; col <=max_x; col++)
			{
				Map[row][col] = color;
			}
		}
		else				// ��������� ������
		{
			a = (double)d1 / (double)d2;
			b = (double)y1 - a * (double)x1;

			s = (double)min_x;
			f = (double)max_x;
			del = 1.0 / (dm );	// ������ ��� ����� ���������
			
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
// �������� � Map ������������� // �������� ���� 
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
		DrowLine(Map, Xsize, Ysize, x0, row, x1, row, color);		// ������������ ������������� ��� ��������� �������������� �������� 
	}

	return;
}


//
// �������� � Map ����� 
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


	// �������� ������� ������
	m = A;
	if (m < B) m = B;

	d = M_PI / (double)(12 * m);  // ��� ��������� ���� ��� ���������� ������

	Alfa = 0.0;
	while (Alfa <= M_PI * 2.0)
	{
		x1 = (double)A * cos(Alfa);
		y1 = (double)B * sin(Alfa);
		x1 += x0;
		y1 += y0;
			
		Alfa += d;

		Map[y1][x1] = color;

		DrowLine(Map, Xsize, Ysize, x0, y0, x1, y1, color);		// ������������ ����� ��� ��������� �������� �� ������ � �������

	}

	return;
}
