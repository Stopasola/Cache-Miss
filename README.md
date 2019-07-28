# Cache-Miss
Introdução e Objetivo:

Algumas aplicações desenvolvidas exigem muitos recursos computacionais para prover
soluções rápidas e precisas, como, no caso da multiplicação de matrizes com números
ponto flutuante. Uma das formas mais fáceis de otimizar esse processo é fazendo um
melhor uso da memória cache, que é uma memória rápida localizada no processador,
facilitando o acesso aos dados armazenados, estando estes de forma sequencial.
O objetivo desta prática foi implementar um algoritmo que multiplica 2 matrizes de tamanho
lxc que permita a demonstração desse efeito positivo ou negativo da memória cache com
relação a forma de acesso aos dados do programa.

Desenvolvimento:

A resolução do problema se deu da seguinte forma. Primeiramente as matrizes foram
alocadas na memória de forma dinâmica e uma função de preenchimento adicionou valores
aleatórios em formato ponto flutuante as duas matrizes.
A multiplicação das matrizes de forma convencional (linha por coluna) é executada quando
o comando “-o” é utilizado na execução do programa. As duas matrizes de tamanho lxc são
passadas por parâmetro para a função “Mult_Matriz” que realiza o cálculo e retorna uma
nova matriz com os valores resultantes.
Pensando na otimização da memória cache nessa operação, ao ser passado o comando “-t”
o programa realiza a transposição da segunda matriz e chama a função
“Mult_Matriz_Transposta” que realiza o calcula das matrizes no formato linha por linha e
retorna uma nova matriz com os valores resultantes.
A melhoria na utilização dessa técnica de multiplicação de linha por linha se dá a partir do
fato de que os dados são carregado para a memória cache de forma sequencial, ou seja,
todos os valores das linhas serão utilizados no cálculo antes que o processador precise da
próxima linha da matriz, o que não ocorre no processo de multiplicação convencional, visto
que a operação é feita no formato linha por coluna.
