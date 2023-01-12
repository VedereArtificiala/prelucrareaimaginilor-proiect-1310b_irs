#pragma once
using namespace std;



///PIMP

unsigned char* SegmentareColor(unsigned char* img, unsigned char* img2, int w, int h)
{
	unsigned char* result = new unsigned char[w * h];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			if (img2[y * w + x] == 0)
				result[y * w + x] = img[y * w + x];
			else
				result[y * w + x] = 255;

	return result;
}




unsigned char* adjustContrastImage(unsigned char* img, int w, int h)
{
	float a, b, sa, sb;
	a = 40;
	b = 70;
	sa = 40;
	sb = 60;
	unsigned char* result = new unsigned char[w * h];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			if (img[y * w + x] < a)
			{
				result[y * w + x] = img[y * w + x] * (sa / a);
			}
			else if (img[y * w + x] >= a && img[y * w + x] <= b)
			{
				result[y * w + x] = ((sb - sa) / (b - a)) * (img[y * w + x] - a) + sa;
			}
			else
			{
				result[y * w + x] = ((255 - sb) / (255 - b)) * (img[y * w + x] - b) + sb;
			}
	return result;
}



unsigned char* binarizarePupila(unsigned char* img, int w, int h)
{
	///vector ce contine pozitiile cele mai din dreapta ale primilor pixeli negrii
	int* extreme;
	extreme = new int [h];
	for (int i = 0; i < h; i++)
		extreme[i] = 0;
	unsigned char* result = new unsigned char[w * h];
	int a = 40;
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			result[y * w + x] = img[y * w + x];
	
	//Binarizare imagine astfel incat ramane doar PUPILA
	for (int y = 0; y < h ; y++)
		for (int x = 0; x < w ; x++)
			if (y > 130 && y < (h - 130) && x>210 && x < (w - 210))
			{
				if (img[y * w + x] < a)
					result[y * w + x] = 0;
				else
					result[y * w + x] = 255;
			}
			else
				result[y * w + x] = 255;
	
	
	///umplere pupila cu negru (SCAPAM DE REFLEXIA DIN PUPILA!!)
	int ok = 0;
	for (int y = 0; y < h; y++)
		for (int x = w-1; x >=0; x--)
		{
			if (result[y * w + x] == 0)
			{
				extreme[y] = x;
				ok = 1;
			}
			if (ok)
			{
				ok = 0;
				break;
			}
		}
	ok = 0;
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
		{
			if (extreme[y] == 0)
				break;
			if (result[y * w + x] == 0)
			{
				for (int i = x; i < extreme[y]; i++)
				{
					result[y * w + i] = 0;
				}
				ok = 1;
			}
			if (ok)
			{
				ok = 0;
				break;
			}
		}
			
	return result;
}




unsigned char* binarizareImage2(unsigned char* img, int w, int h)
{
	unsigned char* result = new unsigned char[w * h];
	int a = 53;
	//int aa = 180;
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			result[y * w + x] = img[y * w + x];
	for (int y = 0; y < h ; y++)
		for (int x = 0; x < w ; x++)
			if (y>110 && y<(h-110) && x>190 && x<(w-190))
			{
				if (img[y * w + x] < a)
					result[y * w + x] = 0;
				else
					result[y * w + x] = 255;
			}
			else
				result[y * w + x] = 255;

				

	return result;
}


unsigned char* SegmentareIris(unsigned char* img, unsigned char* img2, int w, int h)
{
	unsigned char* result = new unsigned char[w * h];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			result[y * w + x] = img[y * w + x];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
		{
			if (img[y * w + x] == 0 && img2[y * w + x] == 0)
			{
				result[y * w + x] = 255;
			}
		}
	return result;
}



unsigned char* produs(unsigned char* img, int w, int h, int dimensiune_masca)
{
	unsigned char* result = new unsigned char[w * h];
	double* masca = new double[dimensiune_masca * dimensiune_masca];
	for (int y = 0; y < dimensiune_masca; y++)
		for (int x = 0; x < dimensiune_masca; x++)
		{
			masca[y * dimensiune_masca + x] = 1.0 / (dimensiune_masca * dimensiune_masca);
		}
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			result[y * w + x] = img[y * w + x];
	for (int y = dimensiune_masca / 2; y < h - (dimensiune_masca / 2); y++)
		for (int x = dimensiune_masca / 2; x < w - (dimensiune_masca / 2); x++)
			result[y * w + x] = 0;


	for (int y = dimensiune_masca / 2; y < h - (dimensiune_masca / 2); y++)
		for (int x = dimensiune_masca / 2; x < w - (dimensiune_masca / 2); x++)
			for (int i = 0; i < dimensiune_masca; i++)
				for (int j = 0; j < dimensiune_masca; j++)
				{
					result[y * w + x] += img[(y + i - dimensiune_masca / 2) * w + (x + j - dimensiune_masca / 2)] * masca[i * dimensiune_masca + j];

				}



	return result;
}



void compareColors(unsigned char* img, unsigned char* img2, unsigned char* seg1, unsigned char* seg2, unsigned char* masca1, unsigned char* masca2, int w, int h)
{
	double percentageColours = 0.0;
	double percentageColours2 = 0.0;
	double percentageTotalColours = 0.0;
	double percentageDimensiune = 0.0;
	int iris1Dim = 0, iris2Dim = 0;
	int sum=0, sum2=0;
	unsigned char* result = new unsigned char[w * h];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			result[y * w + x] = img[y * w + x];
	unsigned char* result2 = new unsigned char[w * h];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			result2[y * w + x] = img2[y * w + x];

	int vfrecv1[256], vfrecv22[256],vfrecv[256], vfrecv2[256];
	///initializare vector frecv
	for (int i = 0; i < 256; i++)
	{
		vfrecv[i] = 0;
		vfrecv2[i] = 0;
		vfrecv1[i] = 0;
		vfrecv22[i] = 0;
	}
	
	//numarare pixeli
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			if(seg1[y * w + x]==0)
			{
				vfrecv[masca1[y * w + x]]++;
			}
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			if (seg2[y * w + x] == 0)
			{
				vfrecv2[masca2[y * w + x]]++;
			}
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			if (seg1[y * w + x] == 0)
			{
				vfrecv1[result[y * w + x]]++;
			}
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			if (seg2[y * w + x] == 0)
			{
				vfrecv22[result2[y * w + x]]++;
			}

	/// initializare variabila procentaj

	percentageColours = 100;


	//suma pixeli si procentaj
	for (int i = 30; i < 220; i++)
	{
		///CAZUL CU 0!!!!!
		if (vfrecv[i] != 0 && vfrecv2[i] !=0)
		{
			if (((vfrecv2[i] * 100.0) / vfrecv[i]) > 100)
			{
				percentageColours = percentageColours + (vfrecv[i] * 100.0) / vfrecv2[i];
				percentageColours = percentageColours / 2;
			}
			else
			{
				percentageColours = (percentageColours + (vfrecv2[i] * 100.0) / vfrecv[i]) / 2;
			}
		}	
		sum += vfrecv[i];
		sum2 += vfrecv2[i];
	}
	if (sum > sum2)
	{
		percentageTotalColours = (sum2 * 100.0) / sum;
	}
	else
	{
		percentageTotalColours = (sum * 100.0) / sum2;
	}



	for (int i = 30; i < 220; i++)
	{
		///CAZUL CU 0!!!!!
		if (vfrecv1[i] != 0 && vfrecv22[i] != 0)
		{
			if (((vfrecv22[i] * 100.0) / vfrecv1[i]) > 100)
			{
				percentageColours2 = percentageColours2 + (vfrecv1[i] * 100.0) / vfrecv22[i];
				percentageColours2 = percentageColours2/ 2;
			}
			else
			{
				percentageColours2 = (percentageColours2 + (vfrecv22[i] * 100.0) / vfrecv1[i]) / 2;
			}
		}

	}


	/// Afisare


	cout <<"Numar total pixeli iris poza1 respectiv poza 2 : " << sum << " | " << sum2 << endl;
	cout << "Procentaj asemanare culori: " << percentageColours << "%" << endl;
	cout << "Procentaj asemanare culori2: " << percentageColours2 << "%" << endl;
	cout << "Procent asemanare numar total de pixeli din iris: " << percentageTotalColours << "%" << endl;
	
	if (percentageColours2 >= 50.0 && percentageColours >= 50.0 &&  percentageTotalColours >= 90.0)
	{
		cout << "ACELASI IRIS!" << endl;
	}
	else
	{
		cout << "NU ESTE ACELASI IRIS!" << endl;
	}

	cout << '\t' << "//////////////////////////////////////////////////////////////////////" << endl;
}

unsigned char* negateImagee(unsigned char* img, int w, int h)
{
	///functie testare
	unsigned char* result = new unsigned char[w * h];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			result[y * w + x] =img[y * w + x];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			if(x==w/2 && y<110 || x == w / 2 && y > h-110 || y==h/2 && x<190 || y == h / 2 && x > w-190)
			result[y * w + x] = 0;
	for (int y = 110; y < h - 110; y++)
		for (int x = 190; x < w - 190; x++)
		{
			if (result[y * w + x] < 50)
				result[y * w + x] = 0;

			if (result[y * w + x] > 125)
				result[y * w + x] = 255;
		}

	return result;
}



