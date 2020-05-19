#pragma once
#ifndef MAPCART_H
#define MAPCART_H

struct PixelList		// ���������, ���. ��������� ������� ������ ��������� �������
{
	Itype x, y;					// ���������� �������
	Itype color;				// ���� �������
};

void ReadColorMap(char * );							// ��������� ����� �� �����

void CreatePlist(void);								// ������� �� ����� ������ ������� ��������
void RegionSize(void);								// ���������� �������� ������ �����
void PixelAdd(Itype, Itype, Itype, Itype);			// ���������� ������� � ������ Plist
void PixelCheck(Itype, Itype, Itype, Itype);		// �������� �������� ��������
Dtype Distance2(Itype, Itype, Itype, Itype);		// ���������� ���������� ����� ����� ���������

Itype  IsLine(Itype, Dtype *);							// �������� �� ��������� ������� ��������
Itype  IsRectangle(Itype, Dtype *, Dtype *, Itype *);	// �������� �� ��������� ������� ���������������
Itype  IsEllips(Itype, Itype *);						// �������� �� ��������� ������� ��������


#endif 