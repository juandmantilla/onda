#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*Codigo creado para resolver la ecuacion de onda.
Se toma como condicion inicial una curva gaussiana, con puntos fijos en los extremos (0.0 y 1.0)*/

int main (){
  int i, j, k;
  int n_points, tiempo;
  float dx, dt, c, r;
  float *x, *old, *new, *current;
  FILE *in;

  /*Se inicializa la lista de datos*/
  in = fopen("data.dat","w");
  x = malloc(n_points*sizeof(float));
  old = malloc(n_points*sizeof(float));
  new = malloc(n_points*sizeof(float));
  current = malloc(n_points*sizeof(float));

  n_points = 1000;
  
  for (i=0;i<n_points+1;i++){
    x[i]=(float)i/(n_points);
  }
  /*Se crean los diferenciales que determinaran la solucion.*/

  dx = x[1]-x[0];
  dt = 0.0005;
  c = 1.0;
  tiempo = 2000;
  r = c*(dt/dx);

  /*Se crea el estado inicial*/

  current[0] = 0.0;
  current[n_points-1] = 0.0;

  new[0] = 0.0;
  new[n_points-1] = 0.0;

  for (i=1;i<n_points-1;i++){
    current[i] = exp(-1*pow((x[i]-0.3),2)/0.01);
  }

/*Se imprimen los puntos en x.*/

for(i=0;i<n_points;i++){
    fprintf(in,"%f\t", x[i]);
    if(i == n_points-1){
      fprintf(in,"\n");
    }
  }

  /*Se imprime el estado inicial.*/

for(i=0;i<n_points;i++){
    fprintf(in,"%f\t", current[i]);
    if(i == n_points-1){
      fprintf(in,"\n");
    }
  }

  /*Se crea un loop que realice la solucion. Los datos seran enviados a un archivo llamada data.dat.*/

  for(i=0;i<tiempo;i++){
    if(i==0){
      for(j=1;j<n_points;j++){
	new[j] = current[j] + (pow(r,2)/2.0) * (current[j+1]-2.0*current[j]+current[j-1]); 
      }
      for(k=0;k<n_points;k++){
	fprintf(in,"%f\t", new[k]);
	if(k == n_points-1){
	  fprintf(in,"\n");
	}
      }
      for (k=0;k<n_points;k++){
	old[k] = current[k];
	current[k] = new[k];
      }  
    }
    else{
      for(j=1;j<n_points;j++){
	new[j] = (2.0*(1.0-pow(r,2)))*current[j] - old[j] + pow(r,2)*(current[j+1] + current[j-1]);
      }
      for(k=0;k<n_points;k++){
	fprintf(in,"%f\t", new[k]);
	if(k == n_points-1){
	  fprintf(in,"\n");
	}
      }
      for (k=0;k<n_points;k++){
	old[k] = current[k];
	current[k] = new[k];
      } 
    }
  }

  fclose(in);

  return 0;
}
