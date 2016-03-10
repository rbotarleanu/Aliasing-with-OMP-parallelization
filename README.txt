Botarleanu Robert-Mihai
Grupa: 331CB
Tema 1 APD

I. Super Sampling Anti Aliasing
	a) Descrierea structurii programului si a algoritmului folosit
	Pentru a rezolva aceasta cerinta am optat sa folosesc o structura de date
pentru imaginile pnm/pgm cu urmatoarele campuri: grayscale(care indica daca
imaginea este bw sau color, folosit atat pentru a determina numarul de pixeli
intr-o linie cat si pentru a determina numarul magic P5/P6 la afisare.), 
width, height, maxvalue, byte_array(care contine matricea de bytes ce descriu
maparea culorilor pixelilor), byte_count(numarul total de pixeli in matricea
de culori: width * height * numcolors) si bytes_in_row(care va avea o valoare
egala fie cu width fie cu width * 3 pentru imagini colore si reprezinta numarul
de bytes ce se pot gasi pe o linie a matricei).
	Functia "read_input" va citi informatiile din fisierul trimis ca parametru 
si va atribui informatiile in structura imaginii. Astfel, se compara daca 
numarul magic citit este P5 sau P6 pentru a seta tipul imaginii(daca este sau
nu grayscale), width, height si maxvalue. Dupa citirea acestora, se calculeaza
numarul total de pixeli din matrice, dintr-o linie a matricei si se aloca 
spatiul necesar inainte de a citi, linie cu linie, matricea de pixeli.
	Functia "writeData" va afisa mai intai numarul magic P5/P6(in functie de
variabila grayscale a incapului imagine), apoi width, height, maxvalue si, in
final, matricea de bytes care reprezinta culorile pixelilor din imagine.
	Functia "resize" va calcula width, height, bytes_in_row si byte_count in
functie de factorul de scalare pentru imaginea rezultanta si va seta variabilele 
grayscale, maxval vor ramane neschimbate fata de imaginea originala. De 
asemenea, se va aloca matricea de pixeli pentru imaginea rezultanta. In final,
in functie de factorul de scalare se va apela una din doua functii pentru 
construirea matricei de pixeli cu factor de scalare par sau 3:
	- construct_byte_array_even: va calcula mediile aritmetice pentru submatrice
de dimensiuni resize_factor * (resize_factor * numcolors), acest lucru se va 
intampla atata timp cat mai sunt suficiente valori pentru a construi o submatri-
ce completa(ignorand astfel in unele situatii ultima linie si/sau ultima 
coloana). Media aritmetica se face prin calculul initial al unei sume(sau a 
trei sume in cazul imaginilor color) formata din valorile culorilor pixelilor
din submatricea curenta si impartirea ulterioara la resize_factor ^ 2(numarul
de pixeli ai matricei curente). Rezultatul va mapa un singur pixel in matricea
rezultanta, corespunzator liniei si coloanei curente a pixelului de pe pozitia
(0,0) relativa la submaticea curenta, impartit la factorul de redimensionare.
	- construct_byte_array_3: va calcula valaorea culorii fiecarui pixel folo-
sind kernel-ul Gaussian de dimensiune 3x3. Acest lucru se face prin insumarea 
produselor dintre fiecare submatrice de dimensiune 3x3 si elementul corespunza-
tor din kernel-ul gaussian, impartind ulterior la 16. In cazul imaginilor color,
sunt calculate 3 sume separate pentru valorile r,g,b ale culorii pixelului. 
	
	b) Argumentare pornire de thread-uri pentru paralelizare si rezultatele 
	testelor de scalabilitate
	Pentru a imbunatati viteza de executie a programului, am ales sa paralelizez
calculul valorii pixelului din matricea rezultanta in functie de un numar mai 
mare de pixeli din matricea originala pentru fiecare linie.
	Astfel, datorita independentei calculelor pentru fiecare submatrice de 
dimensiune resize_factor * resize_factor, am ales ca submatricele de pe fiecare
linie sa fie procesate de catre un thread, permitand astfel pentru un numar mai
mare de thread-uri sa se poata calcula mai multe linii simultan micsorand 
semnificativ timpul de executie total al programului.
	Rezultele testelor de scalabilitate facute pe cluster, pentru o imagine
de dimensiune 17384 x 5558 pixels, atat in format pnm(color) si pgm(grayscale) 
sunt urmatoarele(extrase din 10 iteratii):

**********BW Scale 2***********
1 Thread
1.096320
2 Threads
0.592463
4 Threads
0.306725
8 Threads
0.154146
**********BW Scale 8***********
1 Thread
0.684928
2 Threads
0.353111
4 Threads
0.175343
8 Threads
0.089278
**********BW Scale 3***********
1 Thread
1.030496
2 Threads
0.523338
4 Threads
0.266490
8 Threads
0.138238
**********Color Scale 2***********
1 Thread
1.815575
2 Threads
0.949436
4 Threads
0.485363
8 Threads
0.257338
********Color Scale 8********
1 Thread
1.185656
2 Threads
0.609946
4 Threads
0.308176
8 Threads
0.152094
*************Color Scale 3*********
1 Thread
1.803321
2 Threads
1.015275
4 Threads
0.466498
8 Threads
0.243054

	Dupa cum se observa, dubland numarul de thread-uri pornind de la 1 thread
pana la 8 thread-uri va imbunatati semnificativ timpul de executie al programu-
lui pentru toti factorii de scalare pari sau 3 testati.
	A fost aleasa o imagine cu o rezolutie mai mare pentru a evidentia cat mai 
bine efectul pe care pornirea de mai multe thread-uri o are asupra executiei 
programului.
	

II. Micro Renderer
	a) Descrierea structurii programului si a algoritmului folosit
	Pentru a rezolva aceasta cerinta am optat sa folosesc o structura de date
pentru imaginile pnm/pgm cu urmatoarele campuri: width, height, maxval si 
byte_array. Deoarece imaginea va fi mereu in format grayscale dimensiunea
matricei de pixeli va fi width * height, iar numarul magic va fi mereu acelasi.
	Functia "initialize" va crea o imagine cu dimensiune resolution * resolution
si va aloca matricea de bytes corespunzatoare pentru o imagine grayscale.
	Functia "writeData" va scrie in fisierul dat ca parametru o imagine .pgm,
cu dimensiunile setate la initialize si va scrie matricea de bytes care 
corespund culorilor pixelilor din imaginea alb-negru.
	Functia "render" va parcurge toti cei width * height bytes ce vor determina,
culoarea pixelilor din imagine si va determina pentru fiecare daca este la o 
distanta mai mica de 3m de dreapta descrisa in enunt(prin apelul functiei 
pixel_is_within_3m(i, j) care calculeaza distanta fata de dreapta si returneaza
1 daca aceasta este mai mica de 3). In cazul afirmativ, culoarea pixelului este
setata ca fiind negru(byte-ul ia valoarea 0), altfel va fi alb(byte-ul ia 
valoarea maxima: 255).
	
	b) Argumentare pornire de thread-uri pentru paralelizare si rezultatele 
	testelor de scalabilitate
	Pentru a imbunatati timpul de executie, am ales sa paralelizez analiza
distantei pixelilor de pe fiecare linie. Astfel, pentru un numar de thread-uri
mai mare decat 1, mai multe linii vor fi parcurse simultan de un numar de 
thread-uri.
	Acest lucru este posibil datorita independentei pixelilor(culoarea care este
determinata pentru fiecare nu depinde de vruen alt pixel din imagine, ci doar
de pozitia sa relativa in plan).

	Rezultatele testelor de scalabilitate pentru o resolutie de 8000x8000 si 
de 10000x10000. Au fost alese rezolutii mai mari pentru a evidentia cat mai bine
efectul pe care pornirea de mai multe thread-uri o are asupra executiei 
programului.
	Rezultatele sunt urmatoarele(extrase din 10 iteratii):

*************Resolution 8000*********
1 Thread
3.573849
2 Threads
1.808884
4 Threads
0.911789
8 Threads
0.450748
*************Resolution 10000*********
1 Thread
5.586272
2 Threads
2.823425
4 Threads
1.417046
8 Threads
0.703739

	Dupa cum se observa, prin dublarea numarului de thread-uri de la 1 thread
pana la 8, se imbunatateste semnificativ timpul de executie al programului.


	Metodologia de testare si descrierea sistemelor pe care am efectuat testele	
	In scopul obtinerii unor date cat mai conclusive, am ales sa folosesc o 
imagine de rezolutie foarte mare la primul exercitiu si rezolutii de 8000 si
10000 la al doilea. 
	Am testat fiecare caz prezentat in tema pentru primul exercitiu, verificand
atat pentru imagine color si grayscale factori de scalare de 2, 3 si 8 pentru
un numar de 1, 2, 4 si 8 thread-uri. Aceste teste au fost realizate intr-un
numar de 10 iteratii pe cluster-ul facultatii, pe coada ibm-nehalem, iar datele
prezentate anterior au fost extrase din cele 10 iteratii. La fiecare iteratie,
s-a putut vedea clar scalabilitatea celor doua programe prin cresterea numarului
de thread-uri.
	Sistemul pe care s-au realizat testele este coada ibm-nehalem.q din cadrul
cluster-ului facultatii. Este un sistem distribuit, ce contine un numar de
noduri. Script-ul de testare a fost alocat drept un job si nu a fost partajat.
