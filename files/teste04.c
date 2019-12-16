#include <stdio.h>
#include <stdlib.h>

int main (){
	float cos, x, n, term, eps, alt;
	// compute the cosine of x to within tolerance eps
	// use an alternating series
	x = 3.14159;
	eps = 0.1;
	n = 1;
	cos = 1;
	term = 1;
	alt = -1;
	while(term > eps){
		term = term * x * x / n / (n+1);
		cos = cos + alt * term;
		alt = -alt;
		n = n + 2;
	}
	if(x<10){
		x = x + 10;
	}else{
		x = 1;
	}
	for(i=0;i<10;i+1){
		x = 2;
		x += 1;
		x++;
	}
	do{
		x += 2;
	}while(x < 4);
	
	
	switch(xd){
		case 1:{ cont += 1; break;}
		case 2:{ cont += 2; break;}if
		default:{ cont = 0;}
	}
	
	break;
	
	cont = "teste xd";
	cont = 'x';
	
	printf,("flavio xd %d",123);
	
	return 0;
}

void testexd(int cont){
	int a;
	a = 2;
}