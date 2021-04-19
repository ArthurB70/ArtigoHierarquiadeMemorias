#include <stdio.h>
#include <stdlib.h>
#include <time.h>
char *retorno;
char* decToHexa(int n)
{
    if(n == 0){
      retorno[0] = '0';
      return retorno;
    }
    char *hexaDeciNum = (char*)calloc(100, sizeof(char)); 
    int i = 0;
    while (n != 0) {
        int temp = 0;
        temp = n % 16;
        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else {
            hexaDeciNum[i] = temp + 55;
            i++;
        }
        n = n / 16;
    }
  
    for (int j = i - 1, k = 0; j >= 0; j--, k++){
      retorno[k] = hexaDeciNum[j];
    }
    free(hexaDeciNum);
    return retorno;
}
int main(void) {
  
  int quantidade_enderecos = 0, quantidade_consultas = 0, blocos = 0;

  printf("\tGerador de Traces\n");
  printf("\nInforme a quantidade de enderecos: ");
  scanf("%d",&quantidade_enderecos);
  printf("\nInforme a quantidade de consultas: ");
  scanf("%d",&quantidade_consultas);
  printf("\nInforme a quantidade de instrucoes sequenciais (aleatoria = 1): ");
  scanf("%d",&blocos);

  char *nome_trace = "trace.txt";    
  FILE *file_aux = fopen("arq_aux.txt","w+");
  FILE *file = fopen(nome_trace, "w");
  if(file && file_aux){
    for(int i = 0; i < quantidade_enderecos; i++){
      retorno = (char*)calloc(100,sizeof(char));
      if(i == quantidade_enderecos-1){
        fprintf(file_aux, "%s", decToHexa(i));
      }
      else{
        fprintf(file_aux, "%s\n", decToHexa(i));
      }
      fprintf(file, "1 %s    \n", decToHexa(i));
      free(retorno);
    }
    srand(time(NULL));
    for(int j = 0; j<quantidade_consultas;j++) {
      rewind(file_aux);
      int ind_rand = (rand() % quantidade_enderecos);
      char *buffer;
      int buff;
      buffer = (char*)calloc(100, sizeof(char));
      for(int i =0; i<ind_rand; i++){
        fscanf(file_aux, "%s",buffer);
      }
      free(buffer);
      for(int k = 0; k<blocos;k++){
        buffer = (char*)calloc(100, sizeof(char));
        if(feof(file_aux)){
          rewind(file_aux);
        }        
        fscanf(file_aux, "%s",buffer); 
        fprintf(file, "2 %s    \n",buffer);
        free(buffer);        
      }
      j += blocos - 1;
    }
    printf("\nArquivo %s criado com sucesso!", nome_trace);
  }
  else{
    printf("\nErro ao abrir o arquivo!");
  }
  fclose(file);
  fclose(file_aux);
  return 0;
}
