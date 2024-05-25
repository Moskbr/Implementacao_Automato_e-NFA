
# Implementação de um Automato e-NFA

**Funcionamento:** Foi criado uma matriz transições (int**) representando a função transição
da qual tem suas dimensões [quantidade de estados][quantidade de letras do alfabeto] e, separadamente
temos os vetores "bool ehFinal[quantidade de estados]" e "char alfabeto[quantidade de letras]".
Os estados são na verdade os índices dos vetores, e os campos da matriz armazenam inteiros representando
também os estados, respeitando sua fórmula transição[Estado][Letra] = Estado.

**Erro conhecido:** código não aceita mais de
uma transição saindo de um determinado estado, a não ser que sejam transições vazias.

*in development*
