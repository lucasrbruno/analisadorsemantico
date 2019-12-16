# analisadorsemantico

Analisador semântico feito em C baseado no código do João Vítor Gonçalves, que fez o analisador léxico e semântico presente no código.

Basicamente ele só detecta variável usada mas não declarada, variável declarada mais de uma vez e faz uma verificação de tipos "ingênua" em expressões (verifica se todas as variáveis da parte da direita são iguais à variável resultado, da esquerda.

Instruções:

- Compilar: Comando "make" em algum terminal, na pasta raiz do projeto.
  
- Flags de execução:
	-a: Nome do arquivo. (Flag obrigatória)
	-s: Ativar exibição da Árvore Sintática. (Opcional)
  
- Executar: ./tp1 -a (diretorio_do_arquivo)		(Árvore sintática omitida)
			./tp1 -a (diretorio_do_arquivo) -s  (Árvore sintática visível)
      
- Exemplo: ./tp1 -a files/teste01.c -s

Há 4 arquivos de testes na pasta 'files'.

Não foi possível implementar a verificação de tipos em formato de árvore, detecção de código morto, verificação de tipo de retorno de função e não há geração de código.
