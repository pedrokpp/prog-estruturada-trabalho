# Trabalho Programação Estruturada
Trabalho Computacional: implementação de números inteiros gigantes (isto é, valores maiores que o limite do int de C), positivos e negativos, usando listas encadeadas.

Operações válidas: soma (+), subtração (-), multiplicação (*)

## Descompactar e compilar
```
# Download wget
wget https://github.com/pedrokpp/prog-estruturada-trabalho/archive/refs/tags/ENTREGA.zip

# Download curl
curl -L https://github.com/pedrokpp/prog-estruturada-trabalho/archive/refs/tags/ENTREGA.zip -o prog-estruturada-trabalho-ENTREGA.zip

# Descompactar
unzip prog-estruturada-trabalho-ENTREGA.zip

# Apagar o arquivo zip
rm -rf prog-estruturada-trabalho-ENTREGA.zip

# Mudar diretório atual
cd prog-estruturada-trabalho-ENTREGA

# Compilar com -lm para inserir library de math
gcc -lm -o big_int big_int.c

# Executar binário gerado
./big_int 
```

### Grupo: Pedro Kozlowski e Felipe Belletti
