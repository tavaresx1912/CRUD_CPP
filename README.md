Projeto simples em C que implementa operações básicas de CRUD para produtos (criar, ler, atualizar, excluir) e um mecanismo simples de autenticação por usuário.

Descrição
- Código em `main.c` que usa arquivos de texto (`produtos.txt` e `usuarios.txt`) para persistência.
- Feito para compilação com CMake/CLion ou manualmente via ferramentas de linha de comando.

Pré-requisitos
- Um compilador C (GCC, Clang ou MSVC).
- CMake (versão 3.x ou superior).
- Windows (instruções abaixo para linha de comando `cmd.exe`) ou CLion.

Como compilar (linha de comando - Windows `cmd.exe`)
1. Abra um terminal `cmd.exe` na raiz do projeto (`C:\Users\tavs1\CLionProjects\CRUD_CPP`).
2. Crie diretório de build e entre nele:

   mkdir build && cd build
3. Gere os arquivos de build com CMake e compile:

   cmake ..
   cmake --build . --config Debug

4. O executável estará em `build` (ou `cmake-build-debug` se você usar o CLion). No CLion o build é feito automaticamente.

Como executar
- Pelo terminal, a partir da pasta de build:

  CRUD_CPP.exe

- O programa pedirá usuário e senha. O arquivo `usuarios.txt` é criado automaticamente com um usuário padrão na primeira execução.

Observações sobre autenticação e arquivos
- O projeto cria e utiliza os arquivos `usuarios.txt` e `produtos.txt` na raiz do diretório de execução.
- Por segurança, o `.gitignore` deste repositório ignora esses arquivos para evitar subir credenciais/dados de produtos acidentalmente.

Estrutura do projeto
- `main.c` - fonte principal com as funções de autenticação e CRUD.
- `CMakeLists.txt` - configuração do CMake.
- `produtos.txt`, `usuarios.txt` - arquivos de dados (gerados em tempo de execução).

Melhorias sugeridas
- Validar entradas do usuário para evitar leitura/scanf insegura.
- Usar estruturas e modularizar o código em vários arquivos .c/.h.
- Implementar hashing de senhas em vez de texto simples.

Contribuição
- Sinta-se à vontade para abrir issues e pull requests. Mantenha mudanças pequenas e documentadas.

Licença
- Adicione uma licença se quiser tornar o repositório público (por exemplo MIT).