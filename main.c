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
        printf("Erro ao abrir o Arquivo, criando usuário");
        Arquivo = fopen("usuarios.txt", "w");
    }
    if (Arquivo == NULL) {
        printf("Erro ao criar o Arquivo,");
        return 0;
    }

    fprintf(Arquivo, "admin;12345;1;1");
    fclose(Arquivo);

    Arquivo = fopen("usuarios.txt", "r");
    if (Arquivo == NULL) {
        printf("Erro ao abrir o Arquivo.");
        return 0;
    }

    printf("Digitar o usuário");
    scanf("%s", CPP_Usuario_Digitado);
    printf("Digitar a senha");
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
        printf("Usuário ou senha incorretos.\n");
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

    printf("Digite o preço: ");
    scanf("%f", &CPP_Preco);

    printf("Digite o código: ");
    scanf("%d", &CPP_Codigo);   


    printf("Digite a quantidade: ");
    scanf("%d", &CPP_Quantidade);

    fprintf(Arquivo, "%s;%.2f;%d;%d\n", CPP_Produto, CPP_Preco, CPP_Codigo, CPP_Quantidade);  // Incluí o código também
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
        printf("Erro ao abrir o Arquivo.");
        return;
    }

    while (fscanf(Arquivo, "%19[^;];%f;%d;%d\n", CPP_Produto, &CPP_Preco, &CPP_Codigo, &CPP_Quantidade) == 4) {
        printf("Produto: %s\n", CPP_Produto);
        printf("Preço: %.2f\n", CPP_Preco);
        printf("Quantidade: %d\n", CPP_Quantidade);
        printf("Código: %d\n", CPP_Codigo);
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
        printf("Erro ao abrir o Arquivo temporário.");
        fclose(Arquivo);
        return;
    }

    printf("Digite o códiog do produto que deseja atualizar: ");
    scanf("%d", &CPP_Codigo_Atualizar);

    while (fscanf(Arquivo, "%19[^;];%f;%d;%d\n", CPP_Produto, &CPP_Preco, &CPP_Codigo, &CPP_Quantidade) == 4) {
        if (CPP_Codigo == CPP_Codigo_Atualizar) {
            CPP_Encontrado = 1;

            printf("Produto encontrado");
            printf("o que vc dejeja atualizar");
            scanf("%d", &CPP_Opcao);

            switch (CPP_Opcao) {
                case 1:
                    printf("Digite o novo produto: ");
                    scanf("%s", CPP_Produto_Novo);
                    fprintf(Arquivo_Temporario, "%s;%.2f;%d;%d\n", CPP_Produto_Novo, CPP_Preco, CPP_Codigo, CPP_Quantidade);
                    break;
                case 2:
                    printf("Digite o novo preço: ");
                    scanf("%s", CPP_Preco_Novo);
                    fprintf(Arquivo_Temporario, "%s;%.2f;%d;%d\n", CPP_Produto, CPP_Preco_Novo, CPP_Codigo, CPP_Quantidade);
                    break;
                case 3:
                    printf("Digite a nova quantidade: ");
                    scanf("%d", &CPP_Quantidade_Novo);
                    fprintf(Arquivo_Temporario, "%s;%.2f;%d;%d\n", CPP_Produto, CPP_Preco, CPP_Codigo, CPP_Quantidade_Novo);
                    break;
                case 4:
                    printf("Digite o código novo");
                    scanf("%d", &CPP_Codigo_Novo);
                    fprintf(Arquivo_Temporario, "%s;%.2f;%d;%d\n", CPP_Produto, CPP_Preco, CPP_Codigo_Novo, CPP_Quantidade);
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
    } else {
        remove("produtos_temp.txt");
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
        printf("Erro ao abrir o Arquivo temporário.");
        fclose(Arquivo);
        return;
    }

    printf("Digite o código que quer excluir: ");
    scanf("%d", &CPP_Codigo_Deletar);

    while (fscanf(Arquivo, "%19[^;];%f;%d;%d\n", CPP_Produto, &CPP_Preco, &CPP_Codigo, &CPP_Quantidade) == 4) {
        if (CPP_Codigo_Deletar == CPP_Codigo) {
            CPP_Encontrado = 1;
            printf("Produto Deletado");
        } else {
            fprintf(Arquivo_Temporario, "%s;%.2f;%d;%d\n", CPP_Produto, CPP_Preco, CPP_Codigo, CPP_Quantidade);
        }

        fclose(Arquivo);
        fclose(Arquivo_Temporario);
    }

    if (CPP_Encontrado) {
        remove("produtos.txt");
        rename("produtos_temp.txt", "produtos.txt");
    } else {
        remove("produtos_temp.txt");
    }


}

int main(void) {
    int CPP_Nivel_acesso = FCPP_Autenticar();

    switch (CPP_Nivel_acesso) {
        case 1:
            printf("Bem vindo USER");
        case 2:
            printf("Bem vindo ADMIN");
            break;
        default:
            break;
    }

    return 0;
}