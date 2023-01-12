#include <QApplication>
#include "ImageGrid.h"
#include "operatii.h"

/* Shortcuts:

Scroll wheel - zoom in/out

Left button drag - deplasare in imagine cand aceasta este mai mare decat fereastra

Ctrl+A - activeaza / dezactiveaza ajustarea automata a dimensiunii imaginii 
		 pe care se afla cursorul mouse-ului

Shift+A - activeaza / dezactiveaza ajustarea automata a dimensiunii 
		  tuturor imaginilor

Ctrl+R - reseteaza imaginea curenta la dimensiunile sale initiale

Shift+R - reseteaza toate imaginile la dimensiunile lor initiale

*/

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ImageGrid *grid = new ImageGrid("Prelucrarea imaginilor");

	///CITIRE POZA ORIGINALA
	QString imageDir = "Images/";
	QString imageFile(imageDir + "nadim_reye1.bmp");
	grid->addImage(imageFile, 0, 0);
	int w, h;
	unsigned char* img = Tools::readImageGray8(imageFile, w, h);
	
	///CITIRE A DOUA POZA EU
	QString imageFile2(imageDir + "nadim_reye2.bmp");
	grid->addImage(imageFile2, 0, 1);
	int w2, h2;
	unsigned char* img2 = Tools::readImageGray8(imageFile2, w2, h2);

	///CITIRE POZA OCHI MAMA

	QString imageFile3(imageDir + "mama_reye1.bmp");
	grid->addImage(imageFile3, 0, 2);
	int w3, h3;
	unsigned char* img3 = Tools::readImageGray8(imageFile3, w3, h3);
	


	
	///Afisare 
	
	unsigned char* prod = adjustContrastImage(img, w, h);
	prod = produs(prod, w3, h3, 7);
	prod = binarizareImage2(prod, w3, h3);
	unsigned char* prodd = produs(img, w3, h3, 5);
	unsigned char* proddd = produs(img, w3, h3, 5);
	prodd = binarizarePupila(prodd, w, h);
	prod = SegmentareIris(prod, prodd, w, h);
	grid->addImage(prod, w, h, 1, 0, "segmentare-eu");
	unsigned char* segmentarecolor = SegmentareColor(img, prod, w, h);
	grid->addImage(segmentarecolor, w, h, 2, 0, "segmentare-eu");




	unsigned char* prod2 = adjustContrastImage(img2, w, h);
	prod2 = produs(prod2, w3, h3, 7);
	prod2 = binarizareImage2(prod2, w3, h3);
	unsigned char* prodd2 = produs(img2, w3, h3, 5);
	unsigned char* proddd2 = produs(img2, w3, h3, 5);
	prodd2 = binarizarePupila(prodd2, w, h);
	prod2 = SegmentareIris(prod2, prodd2, w, h);
	grid->addImage(prod2, w, h, 1, 1, "segmentare-eu2");
	unsigned char* segmentarecolor2 = SegmentareColor(img2, prod2, w, h);
	grid->addImage(segmentarecolor2, w, h, 2, 1, "segmentare-eu2");

	
	unsigned char* prod3 = adjustContrastImage(img3, w, h);
	prod3 = produs(prod3, w3, h3, 7);
	prod3 = binarizareImage2(prod3, w3, h3);
	unsigned char* prodd3 = produs(img3, w3, h3, 5);
	unsigned char* proddd3 = produs(img3, w3, h3, 5);
	prodd3 = binarizarePupila(prodd3, w, h);
	prod3 = SegmentareIris(prod3, prodd3, w, h);
	grid->addImage(prod3, w, h, 1, 2, "segmentare-mama");
	unsigned char* segmentarecolor3 = SegmentareColor(img3, prod3, w, h);
	grid->addImage(segmentarecolor3, w, h, 2, 2, "segmentare-mama");

	///TESTARE
	compareColors(img, img2,prod,prod2,proddd,proddd2, w, h);
	compareColors(img, img3,prod,prod3,proddd,proddd3, w, h);



	grid->show();
	
	return a.exec();
}

