#include <stdio.h>
#include <string.h>

int FCPP_Autenticar() {
    FILE *Arquivo;
    char CPP_Usuario_Digitado[20], CPP_Senha_Digitada[20];
    char CPP_Usuario[20], CPP_Senha[20];
    int CPP_Role;
    int CPP_Autenticado = 0;

    //ADMIN = 2, USER = 1

    Arquivo = fopen("usuarios.txt", "r");

    if (Arquivo == NULL) {
        printf("Arquivo de usuarios nao encontrado, criando arquivo padrao...\n");
        Arquivo = fopen("usuarios.txt", "w");

        if (Arquivo == NULL) {
            printf("Erro ao criar o Arquivo.");
            return 0;
        }

        fprintf(Arquivo, "admin;12345;2\n"); //
        fprintf(Arquivo, "user;54321;1\n");   // eu descobri o bug era erro do meu jit, e tambem os numeros 1 e 2
        fclose(Arquivo);


        Arquivo = fopen("usuarios.txt", "r");
        if (Arquivo == NULL) {
            printf("Erro ao abrir o Arquivo apos criar.");
            return 0;
        }
    }

    printf("Digitar o usuario: ");
    scanf("%s", CPP_Usuario_Digitado);
    printf("Digitar a senha: ");
    scanf("%s", CPP_Senha_Digitada);

    while (fscanf(Arquivo, "%19[^;];%19[^;];%d\n", CPP_Usuario, CPP_Senha, &CPP_Role) == 3) {
        if (strcmp(CPP_Usuario, CPP_Usuario_Digitado) == 0 && strcmp(CPP_Senha, CPP_Senha_Digitada) == 0) {
            CPP_Autenticado = 1;
            break;
        }
    }
    fclose(Arquivo);

    if (CPP_Autenticado) {
        printf("Login bem-sucedido!\n");
        return CPP_Role;
    } else {
        printf("Usuario ou senha incorretos.\n");
        return 0;
    }
}

void FCPP_Cadastrar_Produto() {
    FILE *Arquivo;
    char  CPP_Produto[20];
    float CPP_Preco;
    int CPP_Codigo;
    int CPP_Quantidade;

    Arquivo = fopen("produtos.txt", "a");
    if (Arquivo == NULL) {
        printf("Erro ao abrir o Arquivo.");
        return;
    }

    printf("Digite o produto: ");
    scanf("%s", CPP_Produto);

    printf("Digite o preco: ");
    scanf("%f", &CPP_Preco);

    printf("Digite o codigo: ");
    scanf("%d", &CPP_Codigo);

    printf("Digite a quantidade: ");
    scanf("%d", &CPP_Quantidade);

    fprintf(Arquivo, "%s;%.2f;%d;%d\n", CPP_Produto, CPP_Preco, CPP_Codigo, CPP_Quantidade);
    fclose(Arquivo);

    printf("Produto cadastrado com sucesso!\n");
}

void FCPP_Ler_Produtos() {
    FILE *Arquivo;
    char  CPP_Produto[20];
    float CPP_Preco;
    int CPP_Codigo;
    int CPP_Quantidade;

    Arquivo = fopen("produtos.txt", "r");
    if (Arquivo == NULL) {
        printf("Erro ao abrir o Arquivo 'produtos.txt'.\n");
        return;
    }

    printf("\n=== LISTA DE PRODUTOS ===\n");
    // Lê 4 campos
    while (fscanf(Arquivo, "%19[^;];%f;%d;%d\n", CPP_Produto, &CPP_Preco, &CPP_Codigo, &CPP_Quantidade) == 4) {
        printf("Produto: %s\n", CPP_Produto);
        printf("Preco: %.2f\n", CPP_Preco);
        printf("Quantidade: %d\n", CPP_Quantidade);
        printf("Codigo: %d\n", CPP_Codigo);
        printf("--------------------------\n");
    }

    fclose(Arquivo);
}

void FCPP_Atualizar_Produto() {
    FILE *Arquivo;
    FILE *Arquivo_Temporario;
    char  CPP_Produto[20], CPP_Produto_Novo[20];
    float CPP_Preco, CPP_Preco_Novo;
    int CPP_Codigo, CPP_Codigo_Novo;
    int CPP_Codigo_Atualizar;
    int CPP_Encontrado = 0;
    int CPP_Quantidade, CPP_Quantidade_Novo;
    int CPP_Opcao;

    Arquivo = fopen("produtos.txt", "r");
    if (Arquivo == NULL) {
        printf("Erro ao abrir o Arquivo.");
        return;
    }

    Arquivo_Temporario = fopen("produtos_temp.txt", "w");
    if (Arquivo_Temporario == NULL) {
        printf("Erro ao abrir o Arquivo temporario.");
        fclose(Arquivo);
        return;
    }

    printf("Digite o codigo do produto que deseja atualizar: ");
    scanf("%d", &CPP_Codigo_Atualizar);

    while (fscanf(Arquivo, "%19[^;];%f;%d;%d\n", CPP_Produto, &CPP_Preco, &CPP_Codigo, &CPP_Quantidade) == 4) {
        if (CPP_Codigo == CPP_Codigo_Atualizar) {
            CPP_Encontrado = 1;

            printf("Produto encontrado: %s\n", CPP_Produto);
            printf("O que voce deseja atualizar?\n");
            printf("1. Nome\n2. Preco\n3. Quantidade\n4. Codigo\n");
            printf("Opcao: ");
            scanf("%d", &CPP_Opcao);

            switch (CPP_Opcao) {
                case 1:
                    printf("Digite o novo nome: ");
                    scanf("%s", CPP_Produto_Novo);
                    fprintf(Arquivo_Temporario, "%s;%.2f;%d;%d\n", CPP_Produto_Novo, CPP_Preco, CPP_Codigo, CPP_Quantidade);
                    break;
                case 2:
                    printf("Digite o novo preco: ");
                    // *** CORREÇÃO AQUI: Era %s, mudei para %f ***
                    scanf("%f", &CPP_Preco_Novo);
                    fprintf(Arquivo_Temporario, "%s;%.2f;%d;%d\n", CPP_Produto, CPP_Preco_Novo, CPP_Codigo, CPP_Quantidade);
                    break;
                case 3:
                    printf("Digite a nova quantidade: ");
                    scanf("%d", &CPP_Quantidade_Novo);
                    fprintf(Arquivo_Temporario, "%s;%.2f;%d;%d\n", CPP_Produto, CPP_Preco, CPP_Codigo, CPP_Quantidade_Novo);
                    break;
                case 4:
                    printf("Digite o codigo novo: ");
                    scanf("%d", &CPP_Codigo_Novo);
                    fprintf(Arquivo_Temporario, "%s;%.2f;%d;%d\n", CPP_Produto, CPP_Preco, CPP_Codigo_Novo, CPP_Quantidade);
                    break;
                default:
                    printf("Opcao invalida. Mantendo dados originais.\n");
                    fprintf(Arquivo_Temporario, "%s;%.2f;%d;%d\n", CPP_Produto, CPP_Preco, CPP_Codigo, CPP_Quantidade);
                    break;
            }
        } else {
            fprintf(Arquivo_Temporario, "%s;%.2f;%d;%d\n", CPP_Produto, CPP_Preco, CPP_Codigo, CPP_Quantidade);
        }
    }

    fclose(Arquivo);
    fclose(Arquivo_Temporario);

    if (CPP_Encontrado) {
        remove("produtos.txt");
        rename("produtos_temp.txt", "produtos.txt");
        printf("Produto atualizado com sucesso!\n");
    } else {
        remove("produtos_temp.txt");
        printf("Produto com codigo %d nao encontrado.\n", CPP_Codigo_Atualizar);
    }
}

void FCPP_Excluir_Produto() {
    FILE *Arquivo;
    FILE *Arquivo_Temporario;
    int CPP_Codigo;
    int CPP_Codigo_Deletar;
    int CPP_Encontrado = 0;
    char  CPP_Produto[20];
    float CPP_Preco;
    int CPP_Quantidade;

    Arquivo = fopen("produtos.txt", "r");
    if (Arquivo == NULL) {
        printf("Erro ao abrir o Arquivo.");
        return;
    }

    Arquivo_Temporario = fopen("produtos_temp.txt", "w");
    if (Arquivo_Temporario == NULL) {
        printf("Erro ao abrir o Arquivo temporario.");
        fclose(Arquivo);
        return;
    }

    printf("Digite o codigo que quer excluir: ");
    scanf("%d", &CPP_Codigo_Deletar);

    while (fscanf(Arquivo, "%19[^;];%f;%d;%d\n", CPP_Produto, &CPP_Preco, &CPP_Codigo, &CPP_Quantidade) == 4) {
        if (CPP_Codigo_Deletar == CPP_Codigo) {
            CPP_Encontrado = 1;
            printf("Produto '%s' Deletado.\n", CPP_Produto);
        } else {
            fprintf(Arquivo_Temporario, "%s;%.2f;%d;%d\n", CPP_Produto, CPP_Preco, CPP_Codigo, CPP_Quantidade);
        }

        //Tive que tira o Fclose dentro do loop que tava dando erro
    }

    // Ai coloquei aqui embaixo
    fclose(Arquivo);
    fclose(Arquivo_Temporario);

    if (CPP_Encontrado) {
        remove("produtos.txt");
        rename("produtos_temp.txt", "produtos.txt");
    } else {
        remove("produtos_temp.txt");
        printf("Produto com codigo %d nao encontrado.\n", CPP_Codigo_Deletar);
    }
}

int main(void) {
    int CPP_Nivel_acesso = FCPP_Autenticar();
    int opcao;

    // aqui fiz denovo o menu só para ve se ta funcionando ai só botei o ler mesmo
    switch (CPP_Nivel_acesso) {

        // --- MENU USER (NÍVEL 1) ---
        case 1:
            printf("\nUSER Test\n");
            do {
                printf("\n1. Ler\n");
                printf("2. Sair\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        FCPP_Ler_Produtos();
                        break;
                    case 2:
                        printf("Saindo do sistema...\n");
                        break;
                    default:
                        printf("Opcao invalida!\n");
                        break;
                }
            } while (opcao != 2); // aqui só pra ve se o sair vai funcionar mesmo

            break;

        case 2:
            printf("\nADMIN\n");
            do {
                printf("\nCRUD\n");
                printf("1. Cadastrar\n");
                printf("2. Ler Produtos\n");
                printf("3. Atualizar\n");
                printf("4. Excluir\n");
                printf("5. Sair\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        FCPP_Cadastrar_Produto();
                        break;
                    case 2:
                        FCPP_Ler_Produtos();
                        break;
                    case 3:
                        FCPP_Atualizar_Produto();
                        break;
                    case 4:
                        FCPP_Excluir_Produto();
                        break;
                    case 5:
                        printf("Saindo do sistema...\n");
                        break;
                    default:
                        printf("Opcao invalida! Tente novamente.\n");
                        break;
                }
            } while (opcao != 5);

            break;

        default:
            printf("Falha no login. Programa encerrado.\n");
            break;
    } //no outro codigo falto esse falha no login tava dando erro toda hora tambem por causa disso

    return 0;
}