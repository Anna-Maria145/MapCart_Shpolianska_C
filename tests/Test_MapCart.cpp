# include "..\\headers\Common.h"
# include "..\\headers\MapCart.h"

void CreateMap(char *, Itype, Itype, Itype);

extern  PixelList ** Plist;					// ������ ��������� ��������� ������� (��� ������� � ����� ������)
extern  Itype PlCount, PlCurs;				// PlCount - ���-�� ��������� � Plist, PlCurs - ������� ��������� � Plist
extern	Itype RCount;						// ���������� ��������� ��������
extern	Itype Xsize, Ysize, ncol;			// Map size Xsize x Ysize, ncol ���������� ������ �� �����
extern	Itype **Map;						// �����
extern	Itype *P_Reg;						// P_Reg[i] ��������� �� ������ c�������� ������� � Plist
extern	Itype K_Reg;						// ���������� c�������� �������� � P_Reg


int main()
{
	FILE *fileres;
	errno_t err;
		
	char * FPath;
	char filename[256], file_res[256];

	Itype row, col, checked;
	Itype i, k, KL, rP, rSq, kr;
	Itype l_col, kl, m_col, i_col, kp, ke;
	Itype El[4];
	Dtype Len, P, Sq, maxP, maxSq, maxLen, S_ellips;

	 Xsize = 100, Ysize = 100;					// ������� �����
	 ncol = 10;								// ���������� ������ �� �����

	
	FPath = _getcwd(NULL, 0);						// ���� �� ����������
	strcpy_s(filename, FPath);
	strcpy_s(file_res, FPath);
	free(FPath);

	strcat_s(filename, "\\MapCart_test_map.dat");		// ��� ����� �����
	strcat_s(file_res, "\\MapCart_test_res.txt");		// ��� ����� ����������
			
	CreateMap(filename, Xsize, Ysize, ncol);

	ReadColorMap(filename);								// ������ �����

	KL = 0;

	for (row = 0; row < Ysize; row++)
	{
		for (col = 0; col < Xsize; col++)
			if (Map[row][col] != 0) KL++;		// ���������� ����������� �������� �� �����
	}

	Plist = (PixelList**)calloc(KL + 1, sizeof(PixelList*)); 		// ����� ������ �� ������ �������� �������� ��� ���������� ������� ��������


	if (Plist == nullptr)
	{
		printf("Plist can't be allocated.\n");
		exit(-1);
	}

	for (i = 0; i < KL; i++)
	{
		Plist[i] = (PixelList*)calloc( 1, sizeof(PixelList));
		if (Plist[i] == nullptr)
		{
			printf("Plist %i can't be allocated.\n", i);
			exit(-1);
		}
	}


	P_Reg = (Itype*)calloc(KL + 1, sizeof(Itype)); 				// ������ ������� �������� � Plist

	if (P_Reg == nullptr)
	{
		printf_s("P_Reg can't be allocated.\n");
		exit(-1);
	}

	CreatePlist();				//������� ������ ��������� ��������

	printf_s("\n");

	RegionSize();				//���������� ������� ��������� ��������

	err = fopen_s(&fileres, file_res, "wt");				// ������� ���� ��� ������ �����������
	if (err != 0)
	{
		printf_s("Test_CreateMap - Unable to open file %s",file_res);
		exit(-1);
	}

	for (row = 0; row < Ysize; row++)
	{
		for (col = 0; col < Xsize; col++)			// ������ ����� � ����
			fprintf_s(fileres, "%i",Map[row][col]);
		fprintf_s(fileres, "\n");
	}


	// ��������� ��������� �������� ��� ����������� �������������

	// ��������
	maxLen = 30.0;		
	l_col = 2;				// ���� �������
	kl = 0;					// ���-�� �������� L>maxLen & color=l_col

	// ���������������
	maxP = 0.0;				// ��������
	maxSq = 0.0;			// �������
	kr = 0;					// ���-��
	rP = -1;
	rSq = -1;

	// ��������
	ke = 0;					// ���-��
	S_ellips = 25.0;		// �������


	m_col = 1;				// ���� ����. �������
	kp = 0;					// ���-�� �� ��������

	for (i = 0; i < K_Reg; i++)					// ���� �� ��������
	{
		printf("\n Region %i \n", i);

		fprintf(fileres, "\n Region %i \n", i);


		checked = 0;								// ������� �� ���������

		i_col = Plist[P_Reg[i]]->color;		// ���� �������

		if (i_col == m_col) kp += (P_Reg[i + 1] - P_Reg[i]);		// ��������� ���������� �������� ����� m_col

		k = IsLine(i, &Len);					// �������� �� ������� ��������
		if (k > 0)
		{
			checked = 1;
			printf(" Is a Line. Len= %.2f\n", Len);
			fprintf_s(fileres, " Is a Line. Len= %.2f\n", Len);

			if (Len > maxLen && i_col == l_col) kl++;

			continue;
		}
	
		k = IsRectangle(i, &P, &Sq, El);		// �������� �� ������� ���������������
		if (k > 0)
		{
			checked = 2;
			kr++;
			if (P > maxP) { maxP = P; rP = i; }
			if (Sq > maxSq) { maxSq = Sq; rSq = i; }

			printf_s(" Is a Rectangle. P=%.2f Sq=%.2f \n", P, Sq);
			printf_s("x0=%i   y0=%i\n", El[0], El[1]);
			printf_s("x1=%i   y1=%i\n", El[2], El[3]);

			fprintf_s(fileres," Is a Rectangle. P=%.2f Sq=%.2f \n", P, Sq);
			fprintf_s(fileres, "x0=%i   y0=%i\n", El[0], El[1]);
			fprintf_s(fileres, "x1=%i   y1=%i\n", El[2], El[3]);

			continue;
		}

		k = IsEllips(i, El);					// �������� �� ������� ��������
		if (k > 0)
		{
			checked = 3;
			if (M_PI* El[2] * El[3] > S_ellips) { ke++; }

			printf_s(" Is an Ellips \n");
			printf_s("x0=%i   y0=%i\n", El[0], El[1]);
			printf_s("A=%i    B=%i\n", El[2], El[3]);

			fprintf_s(fileres, " Is an Ellips \n");
			fprintf_s(fileres, "x0=%i   y0=%i\n", El[0], El[1]);
			fprintf_s(fileres, "A=%i    B=%i\n", El[2], El[3]);

			continue;
		}

		if (checked == 0)
		{
			printf(" Is not Recognized \n");
			fprintf(fileres, " Is not Recognized \n");
		}
	}

	printf_s("\n Number of Regions is %i\n", K_Reg);
	printf_s("\n Number of Rectangle is %i\n", kr);
	printf_s("Region %i is a Rectangle whith max P=%.2f \n",rP , maxP);
	printf_s("Region %i is a Rectangle whith max Sq=%.2f\n", rSq, maxSq);
	printf_s("\n Number of Lines whith Len > %.2f of color %i  is  %i\n", maxLen, l_col, kl);
	printf_s("\n Number of Elips whith Sq > %.2f is  %i\n", S_ellips, ke);
	printf_s("\n Number of Pixels of color  %i is  %i\n", m_col, kp);
	
	fprintf_s(fileres, "\n Number of Regions is %i\n", K_Reg);
	fprintf_s(fileres, "\n Number of Rectangle is %i\n", kr);
	fprintf_s(fileres, "Region %i is a Rectangle whith max P=%.2f \n", rP, maxP);
	fprintf_s(fileres, "Region %i is a Rectangle whith max Sq=%.2f\n", rSq, maxSq);
	fprintf_s(fileres, "\n Number of Lines whith Len > %.2f of color %i  is  %i\n", maxLen, l_col, kl);
	fprintf_s(fileres, "\n Number of Elips whith Sq > %.2f is  %i\n", S_ellips, ke);
	fprintf_s(fileres, "\n Number of Pixels of color  %i is  %i\n", m_col, kp);

	for (i = 0; i < KL; i++)	free(Plist[i]);
		
	for (Itype row = 0; row < Ysize; row++) free(Map[row]);
	
	free (Plist);
	free (Map);
	free (P_Reg);
	
	fclose(fileres);
		
}

