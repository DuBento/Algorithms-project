## Horas : 10h

#REFS
- https://stackoverflow.com/questions/2128728/allocate-matrix-in-c


# Processo


1. Ler input (vetor com clientes, outro com lojas **separados** ou então uma matriz, em que cada entrada é uma loja, um cidadão, ambos (*vertice preto*) ou uma esquina vazia)
    - ignorar o segundo supermercado ou segundo cidadão na mesma esquina
    - se houver erros no mooshak, verificar casos em que há um supermercado e cidadão na mesma esquina
2. Para cada tipo de vértices, criar arestas, percorrer estrela *: 
    - clientes, adicionar arestas para esquinas vazias e para supermercados 
    - esquinas vazias, outras esquinas vazias e supermecados 
    - supermercados, nada 
        - ter cuidado com limites da matriz (1, m e n)
3. Encontrar um caminho de aumento
    - vetor que guarda o caminho [s, A, B, t]
    - vetor visited
    - fazer DFS, que faz return quando chega a t
    - so visitar se nao estiver ja fluxo a percorrer (ver cor basicamente)
    - sempre que concluimos um vértice na DFS retirar do vetor
    - se o vetor for vazio, fim do algoritmo
    - guardar o fluxo que passa por cada aresta, porque, nos casos em que já há fluxo a percorrer o vértice:
        - se a aresta que queremos percorrer tem fluxo 0, estaríamos a passar mais fluxo por esse vértice, logo ABORT
        - se a aresta tem fluxo 1, então vamos estar a retirar o fluxo dessa aresta por isso podemos manter
4. Atualizar as arestas do caminho de aumento
    - para cada vértice do vetor, trocar hereditariedade do vi+1
      - Vi.parent = Vi+1 (atencao ao t)
      - Vi.child = Vi-1 (atencao ao s)
5. incrementar em 1 maxFlow
 
 
\*\
|\
-c-\
|
 
 O(E.|C|)


 ```
struct vértices{
    tipo {shop, cliente, vazia}

}

 ja temos a matriz M preenchida

 for i
    for j
        if M(i,j) == cliente 
            calcula_arestas_C(); addListAdj(M(i,j), M(i-1,j))
        else if M(i,j) == shop
            calcula_arestas_S();
        else if

 ``` 
 
 - Supermercado e cliente na mesma esquina:
   - Logo no processamento do input, se forem o mesmo ponto **RES++**, apaga ambos e add *vertice preto*.