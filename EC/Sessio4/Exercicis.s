4.3:	cfixa:		cflotant:
0.0	0x00000000	0x00000000
-0.0	0x80000000	0x80000000
12.75	0x0000CC00	0x01CC0000

4.4: Contesta:

	1) Quina condici� ha de complir el valor inicial de cfixa perqu� es produeixi p�rdua de precisi� en la conversi� que proposa aquesta pr�ctica?
		La precisi� es t� en la part decimal. Com que el registre de la coma fixa t� destinats 30 bits per a la representaci� del nombre decimal, en canvi, la coma flotant cont�
		nom�s 23 bits. Per tal que es produeixi un error de precisi�, �s necessari que, entre els dos bits entre els m�s llunyans que estan inicialitzats a 1, hi hagi com a m�nim
		23 bits.
		
	2) Indica un valor de cfiza per al qual es produiria p�rdua de precisi� al convertir-lo, i el corresponent valor en coma flotant:
		cfixa: 0x1000CC11	cflotant: 0x47800660
		
	3) En quina setn�ncia concreta del programa en alt nivell es pot produir la p�rdua de precisi�?
		La sent�ncia d'alinear i eliminar el bit ocult.
		
	4) Quins dels 4 modes d'arrodoniment que coneixes est� portant a la pr�ctica d'aquest programa de conversi�?
		El m�tode d'arrodoniment �s el truncament.
	
	
	5) El format de coma fixa explicat en aquesta pr�ctica permet codificar un rang de valors bastant limitat. Indica un n�mero positiu que estigui DINS el rang
	del format de coma flotant de simple precisi� (en decimal) per� que estigui FORA del rang del format de coma fixa. Indica tamb� quin �s el MENOR
	n�mero pot�ncia de 2 que compleixi aquesta condici�.
		El rang de la coma fixa �s: 	[2^(-12), 2^(19)]	(positius)
		El rang de la coma flotant �s :	[2^(-23), 2^(129)]	(positius)
		
		Aleshores, el nombre positiu dins del rang del format de la coma flotant i fora del ranfo del format de la coma fixa �s 2^(120), la menor pot�ncia ser� 2^(-13)