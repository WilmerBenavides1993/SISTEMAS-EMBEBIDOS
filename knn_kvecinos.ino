#include "matriz_entrenamiento.h"
float datos_prueba[5] = {5 ,2 ,3.5 ,1,2};

int respuesta;
void setup() {
  Serial.begin(9600);
}

void loop() {
  respuesta = knn(3, 3, 5, 120);
  Serial.println(respuesta);
  delay(500);
  if (respuesta ==1){
    Serial.println("Iris-setosa");
  }
    if (respuesta ==2){
    Serial.println("Iris-versicolor");
  }
    else{
    Serial.println("Iris-virginica");
  }
  
}

int knn (int k, int etiquetas, int tam_col, int tam_fil) {
  int col;
  int fil;
  int i = 0;
  int j;
  float aux;
  int etiqueta;
  float aux_eti;
  float sumatoria = 0; // sumatoria de la elevación al cuadrado de cada col
  float distancia = 0; // raiz de sumatoria

  /*matriz de k-vecinos
    |1|2|3| -> numero de vecinos
    |2|1|1| -> asginacion del vecino por etiqueta
    |0.1|0.2|0.3| -> distancia
  */
  float matriz_k [3][k];

  /* etiquetas
    |1|2|3| -> etiquetas que existe dentro de la base de datos
    |2|1|0| -> conteo de etiquetas dentro de los k-vecinos
  */
  int matriz_etiq[2][etiquetas];
  // asignar numero de vecinos y enceramos asignación de etiqueta

  for (; i < k; i++) {
    matriz_k[0][i] = i + 1.0;
    matriz_k[1][i] = 0;
    matriz_k[2][i] = 3000.0 + i;
    /*
      |1|2|3|
      |0|0|0|
      |3000|3001|3002|
    */
  }
  // asignar etiquetas y enceramos su contador
  for (i = 0; i < etiquetas; i++) {
    matriz_etiq[0][i] = i + 1;
    matriz_etiq[1][i] = 0;
    Serial.print(matriz_etiq[0][i] = i + 1);
    Serial.print("|");
    /*
      |1|2|3|
      |0|0|0|
    */
  }
Serial.println(' ');
  /*PASOS PARA K-NN
     Leer cada fila de la matriz de entrenamiento
     distancia entre la fila de la matriz con la nueva instancia (vector de prueba)
     ordenar la matriz matriz_k (determinar los k vecinos de menor distancia)
     contar las etiquetas en la matriz_k y asignar en matriz etiquetas
     eligo al mayor número de matriz etiquetas
     retorno la etiqueta resultante

  */

  for (fil = 0; fil < tam_fil; fil++) {
    for (col = 0; col < tam_col - 1; col++) { // menos 1 por ultima columna es etiqueta
      sumatoria = sumatoria + pow(matriz[fil][col] - datos_prueba[col], 2);
    }
    distancia = sqrt(sumatoria);
    // comparación de nuevo dato con solo la distacia mayor almacenada en matriz_k
    if (distancia < matriz_k[2][k - 1]) {
      matriz_k[2][k - 1] = distancia;
      matriz_k[1][k - 1] = matriz[fil][tam_col - 1];
      //ordenar por metodo burbuja
      for (i = 0; i < k; i++) {
        for (j = i + 1; j < k; j++) {
          if (matriz_k[2][i] > matriz_k[2][j]) {
            //distancia
            aux = matriz_k[2][i];
            matriz_k[2][i] = matriz_k[2][j];
            matriz_k[2][j] = aux;
            // etiqueta
            aux_eti = matriz_k[1][i];
            matriz_k[1][i] = matriz_k[1][j];
            matriz_k[1][j] = aux_eti;
           // Serial.println(aux);
           // delay(200);
          } //end if
        } //end for
      }
      //fin ordenamiento
    }
    //fin condicion de numero menor
    sumatoria = 0;
  }

  // fin de lectura de matriz
  for (i = 0; i < etiquetas; i++) { //  donde se almacena el contador
    for (j = 0; j < k; j++) {
      if (matriz_etiq[0][i] == matriz_k[1][j]) {
        matriz_etiq[1][i]++;

      }
    }
  }
  // buscar la etiqueta con mayor numero de vecinos 
  
  for (i = 0; i < etiquetas-1; i++) {// comparar la posisicion
    if (matriz_etiq[1][i]<matriz_etiq[1][i+1] ){
      etiqueta=matriz_etiq[0][i+1];
    }else 
    etiqueta=matriz_etiq[0][i];
    
  }
  return etiqueta;
  Serial.print(etiqueta);
  // contar por columna, cuantos vecinos hay por etiqueta

}
