#pragma once
using namespace std;

unsigned char* negateImage(unsigned char* img, int w, int h)
{
	unsigned char* result = new unsigned char[w * h];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			result[y * w + x] = 255 - img[y * w + x];
	return result;
}

unsigned char* binarizareImage(unsigned char* img, int w, int h)
{
	unsigned char* result = new unsigned char[w * h];
	int a = 65;
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			result[y * w + x] =img[y * w + x];
	for (int y = 110; y < h-110; y++)
		for (int x = 190; x < w-190; x++)
			if (img[y * w + x] < a)
				result[y * w + x] = 0;
			else
				result[y * w + x] = 255;

	return result;
}


unsigned char* adjustBrightnessImage(unsigned char* img, int w, int h, int brightnessLvl)
{
	unsigned char* result = new unsigned char[w * h];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
		{
			if (brightnessLvl >= 0)
			{
				if (img[y * w + x] + brightnessLvl <= 255)
					result[y * w + x] = img[y * w + x] + brightnessLvl;
				else
					result[y * w + x] = 255;
			}
			else
			{
				if (img[y * w + x] + brightnessLvl >= 0)
					result[y * w + x] = img[y * w + x] + brightnessLvl;
				else
					result[y * w + x] = 0;
			}
		}
	return result;
}

unsigned char* adjustContrastImage(unsigned char* img, int w, int h)
{
	float a, b, sa, sb;
	a = 100;
	b = 150;
	sa = 70;
	sb = 200;
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

///PIMP


void compareColors(unsigned char* img, unsigned char* img2, int w, int h, int w2, int h2)
{
	double percentageColours = 0.0;
	double percentageTotalColours = 0.0;
	double percentageDimensiune = 0.0;
	int iris1Dim = 0, iris2Dim = 0;
	int sum=0, sum2=0;
	unsigned char* result = new unsigned char[w * h];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			result[y * w + x] = img[y * w + x];
	unsigned char* result2 = new unsigned char[w2 * h2];
	for (int y = 0; y < h2; y++)
		for (int x = 0; x < w2; x++)
			result2[y * w2 + x] = img2[y * w2 + x];

	int vfrecv[256], vfrecv2[256];
	///initializare vector frecv
	for (int i = 0; i < 256; i++)
	{
		vfrecv[i] = 0;
		vfrecv2[i] = 0;
	}
	///culorile prea albe devin alb si cele prea negre devin negru
	for (int y = 110; y < h - 110; y++)
		for (int x = 190; x < w - 190; x++)
		{
			if (result[y * w + x] < 50)
				result[y * w + x] = 0;

			if (result[y * w + x] > 125)
				result[y * w + x] = 255;
		}
	for (int y = 110; y < h2 - 110; y++)
		for (int x = 190; x < w2 - 190; x++)
		{
			if (result2[y * w2 + x] < 50)
				result2[y * w2 + x] = 0;

			if (result2[y * w2 + x] > 125)
				result2[y * w2 + x] = 255;
		}
	//numarare pixeli
	//numara doar centrul pozei care contine irisul
	for (int y = 110; y < h - 110; y++)
		for (int x = 190; x < w-190; x++)
		{
			vfrecv[result[y * w + x]]++;
		}
	for (int y = 110; y < h2-110; y++)
		for (int x = 190; x < w2-190; x++)
		{
			vfrecv2[result2[y * w2 + x]]++;
		}
		

	/// initializare variabila procentaj
	for (int i = 5; i < 246; i++)
	{
		if (vfrecv[i] != 0)
		{
			percentageColours = (vfrecv2[i] * 100.0) / vfrecv[i];
			///cout << percentageColours << endl;
			break;
		
		}	
	}

	//suma pixeli si procentaj
	for (int i = 5; i < 246; i++)
	{
		///CAZUL CU 0!!!!!
		if (vfrecv[i] != 0)
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
			//cout << percentageColours << "%" << endl;
		}	
		else if (vfrecv2[i] != 0 && vfrecv[i]==0)
		{
			percentageColours-=(int)percentageColours/2;
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

	///Dimensiune iris
	for (int y = 0; y < h ; y++)
		for (int x = 0; x < w ; x++)
		{
			if (result[y * w + x] < 50)
				result[y * w + x] = 0;

			if (result[y * w + x] > 125)
				result[y * w + x] = 255;
		}
	for (int y = 0; y < h2; y++)
		for (int x = 0; x < w2; x++)
		{
			if (result2[y * w2 + x] < 50)
				result2[y * w2 + x] = 0;

			if (result2[y * w2 + x] > 125)
				result2[y * w2 + x] = 255;
		}
	for (int x = 320; x < w; x++)
	{
		if (result[240 * w + x] == 255)
			break;
		iris1Dim++;
	}
	for (int x = 320; x < w2; x++)
	{
		if (result2[240 * w2 + x] == 255)
			break;
		iris2Dim++;
	}
	if (iris1Dim > iris2Dim)
	{
		percentageDimensiune = (iris2Dim * 100.0) / iris1Dim;
	}
	else
	{
		percentageDimensiune = (iris1Dim * 100.0) / iris2Dim;
	}


	/// Afisare


	cout << "Dimensiune iris1 respectiv iris2 : " << iris1Dim << " | " << iris2Dim << endl;
	cout <<"Numar total pixeli iris poza1 respectiv poza 2 : " << sum << " | " << sum2 << endl;
	cout << "Procentaj asemanare culori: " << percentageColours << "%" << endl;
	cout << "Procent asemanare numar total de pixeli din iris: " << percentageTotalColours << "%" << endl;
	cout << "Procentaj Dimensiune iris : " << percentageDimensiune << "%" << endl;
	
	if (percentageColours >= 90.0 && percentageDimensiune >= 90.0 && percentageTotalColours >= 90.0)
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
/*	for (int y = 110; y < h - 110; y++)
		for (int x = 190; x < w - 190; x++)
		{
			if (result2[y * w + x] < 50)
				result2[y * w + x] = 0;

			if (result2[y * w + x] > 205)
				result2[y * w + x] = 255;
		}
		*/

	return result;
}



