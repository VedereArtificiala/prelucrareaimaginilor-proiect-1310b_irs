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

	/* generam o fereastra care va contine una sau mai multe imagini
	   plasate sub forma unei matrici 2D */
	ImageGrid *grid = new ImageGrid("Prelucrarea imaginilor");

	QString imageDir = "Images/";
	QString imageFile(imageDir + "nadim_reye1.bmp");

	/*adaugam prima imagine, cea initiala, citita din fisier,
	in pozitia stanga-sus (linia 0, coloana 0)*/
	grid->addImage(imageFile, 0, 0);

	/* extragem imformatiile necesare din imagine:
	dimensiunile ei si un sir de octeti care contine valorile
	intensitatilor pentru fiecare pixel */
	int w, h;
	unsigned char* img = Tools::readImageGray8(imageFile, w, h);
	///PIMP
	QString imageFile2(imageDir + "nadim_reye2.bmp");
	grid->addImage(imageFile2, 1, 0);
	int w2, h2;
	unsigned char* img2 = Tools::readImageGray8(imageFile2, w2, h2);

	compareColors(img, img2, w, h, w2, h2);

	QString imageFile3(imageDir + "mama_reye1.bmp");
	grid->addImage(imageFile3, 1, 1);
	int w3, h3;
	unsigned char* img3 = Tools::readImageGray8(imageFile3, w3, h3);
	compareColors(img, img3, w, h, w3, h3);
	////PIMP
	// exemplu de operatie: negativarea unei imagini 

	/*parcurgem imaginea pixel cu pixel si determinam valoarea complementara
	pentru fiecare intensitate

	se recomanda ca acest gen de operatie sa se implementeze intr-o functie
	separata sau intr-o alta clasa
	*/

	unsigned char* negated = negateImagee(img, w, h);
	unsigned char* negated3 = negateImagee(img3, w3, h3);
	unsigned char* prod = produs(img3, w3, h3,7);

	/* afisam imaginea astfel obtinuta la dreapta celei initiale;
	parametrii cu valorile 0, 1 semnifica prima linie, respectiv
	a doua coloana a imageGrid-ului
	*/
	grid->addImage(negated, w, h, 0, 1, "Negativ");
	grid->addImage(negated3, w, h, 0, 2, "Negativ_mama");
	grid->addImage(prod, w, h, 1, 2, "zgomot");
	///grid->addImage(contrast, w, h, 0, 2, "Contrast");

	grid->show();
	
	return a.exec();
}

