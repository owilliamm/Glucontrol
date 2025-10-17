#include <stdio.h>

// Informações a serem armazenadas
enum TipoRegistro {ENTRADA, SAIDA, MANUTENCAO};

union Dados {
    struct {
        char nomePeca[30];
        int quantidade;
        char fornecedor[20];
    } entrada;

    struct {
        char nomePeca[30];
        int quantidade;
        int IDVeiculo;
    } saida;

    struct {
        char nomePeca[30];
        int quantidade;
        char status[20];
    } manutencao;
};

struct Registro {
    int ID;
    enum TipoRegistro tipo;
    union Dados Dados;
    int DataHora[2][3]; // Data ou hora e, dependendo da escolha, Dia/Mês/Ano ou Hora/Minuto
    int removido;
};

//Checar se a data é válida (Extremamente simplificado, talvez somente por enquanto.)
int DataHoraValida(int V[2][3]) {
    int dia = V[0][0];
    int mes = V[0][1];
    int ano = V[0][2];
    int hora = V[1][0];
    int minuto = V[1][1];
    
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1 || hora < 0 || hora > 23 || minuto < 0 || minuto > 59) return 0;
    return 1;
}

//Gerar a identificação para um registro
int GerarID() {
    FILE* arq = fopen("registros.bin", "rb");
    if (!arq) return 1;

    struct Registro r;
    int UltimoID = 0;
    while (fread(&r, sizeof(struct Registro), 1, arq)) {
        if (r.ID > UltimoID) UltimoID = r.ID;
    }

    fclose(arq);
    return UltimoID+1;
}

//Criar registros
void CriarRegistro() {
    FILE* arq = fopen("registros.bin", "ab");

    struct Registro r;
    r.ID = GerarID();
    r.DataHora[0][0] = 0;
    r.DataHora[0][1] = 0;
    r.DataHora[0][2] = 0;
    r.DataHora[1][0] = 0;
    r.DataHora[1][1] = 0;
    r.removido = 0;

    while (DataHoraValida(r.DataHora) == 0) {
        printf("Digite a data e a hora DD/MM/YYYY HH:MM: ");
        scanf("%d/%d/%d %d:%d", &r.DataHora[0][0], &r.DataHora[0][1], &r.DataHora[0][2], &r.DataHora[1][0], &r.DataHora[1][1]);
        if (DataHoraValida(r.DataHora) == 0) {
            printf("Data e/ou hora invalida. Tente novamente.\n");
        }
    }

    int Opcao = 0;
    while (Opcao != 4) {
        printf("Tipo de registro:\n"); 
        printf("1-Entrada, 2-Saida, 3-Manutencao, 4-Sair e salvar\n");
        scanf("%d", &Opcao);

        if (Opcao == 1) {
            r.tipo = ENTRADA;
            getchar();

            printf("Nome da peça: "); fgets(r.Dados.entrada.nomePeca, 30, stdin);
            r.Dados.entrada.nomePeca[strcspn(r.Dados.entrada.nomePeca,"\n")] = 0;

            printf("Quantidade: "); scanf("%d",&r.Dados.entrada.quantidade);
            getchar();

            printf("Fornecedor: "); fgets(r.Dados.entrada.fornecedor, 20, stdin);
            r.Dados.entrada.fornecedor[strcspn(r.Dados.entrada.fornecedor,"\n")] = 0;
        }
        else if (Opcao == 2) {
            r.tipo = SAIDA;
            getchar();

            printf("Nome da peça: "); fgets(r.Dados.saida.nomePeca, 30, stdin);
            r.Dados.saida.nomePeca[strcspn(r.Dados.saida.nomePeca,"\n")] = 0;

            printf("Quantidade: "); scanf("%d",&r.Dados.saida.quantidade);

            printf("ID do veículo: "); scanf("%d",&r.Dados.saida.IDVeiculo);
        }
        else if (Opcao == 3) {
            r.tipo = MANUTENCAO;
            getchar();

            printf("Nome da peça: "); fgets(r.Dados.manutencao.nomePeca, 30, stdin);
            r.Dados.manutencao.nomePeca[strcspn(r.Dados.manutencao.nomePeca,"\n")] = 0;

            printf("Quantidade: "); scanf("%d",&r.Dados.manutencao.quantidade);
            getchar();

            printf("Status (reparo/substituida/devolvida): "); fgets(r.Dados.manutencao.status, 20, stdin);
            r.Dados.manutencao.status[strcspn(r.Dados.manutencao.status,"\n")] = 0;
        }
    }

    fwrite(&r, sizeof(struct Registro), 1, arq);
    fclose(arq);

    printf("\n==================================");
    printf("\nConcluido novo registro com identificacao #%d\n", r.ID);
    printf("==================================\n");
}

//Buscar registros
void BuscarRegistro() {
    FILE* arq = fopen("registros.bin", "rb");
    if(!arq){ printf("Nenhum registro encontrado.\n"); return; }
    struct Registro r;

    int Opcao = 0;
    while (Opcao != 1 && Opcao != 2) {
        printf("Buscar por 1-ID ou 2-Tipo?\n");
        scanf("%d", &Opcao);
    }

    if (Opcao == 1) {
        int EscolhaID = 1;
        int Valido = 0;
        while (Valido == 0) {
            printf("Digite um ID: ");
            scanf("%d", &EscolhaID);
            fseek(arq, (EscolhaID-1)*sizeof(struct Registro), SEEK_SET);
            if (fread(&r, sizeof(struct Registro), 1, arq) == 1 && r.removido==0) {
                r.ID = EscolhaID;
                printf("\nRegistro ID %d:\n", r.ID);
                printf("Data: %02d/%02d/%04d - %02d:%02d\n", r.DataHora[0][0], r.DataHora[0][1], r.DataHora[0][2], r.DataHora[1][0], r.DataHora[1][1]);
                if(r.tipo==ENTRADA){
                    printf("Entrada - Peça: %s | Qtde: %d | Fornecedor: %s\n", r.Dados.entrada.nomePeca, r.Dados.entrada.quantidade, r.Dados.entrada.fornecedor);
                } else if(r.tipo==SAIDA){
                    printf("Saida - Peça: %s | Qtde: %d | Veículo ID: %d\n", r.Dados.saida.nomePeca, r.Dados.saida.quantidade, r.Dados.saida.IDVeiculo);
                } else {
                    printf("Manutencao - Peça: %s | Qtde: %d | Status: %s\n", r.Dados.manutencao.nomePeca, r.Dados.manutencao.quantidade, r.Dados.manutencao.status);
                }
                Valido = 1;
                break;
            } else {
                printf("ID invalido. Tente novamente.\n");
            }
        }
    } else if (Opcao == 2) {
        int EscolhaTipo;
        printf("1-Entrada, 2-Saida, 3-Manutencao\n");
        while (EscolhaTipo != 1 && EscolhaTipo != 2 && EscolhaTipo != 3) {
            scanf("%d", &EscolhaTipo);
            if (EscolhaTipo != 1 && EscolhaTipo != 2 && EscolhaTipo != 3) {
                printf("Opcao invalida. Tente novamente.\n");
            }
        }
        // Lógica para buscar por tipo pode ser implementada aqui
    }

    fclose(arq);
}

//Função principal
int main() {
    int EscolhaUsuario = 0;

    while (EscolhaUsuario != 5) {
        printf("\n--------- MENU ---------\n");
        printf("1- Adicionar registro\n");
        printf("2- Alterar registro\n");
        printf("3- Remover registro\n");
        printf("4- Buscar registro\n");
        printf("5- Sair\n");
        printf("--------- MENU ---------\n\n");
        printf("Escolha: "); scanf("%d", &EscolhaUsuario);

        if (EscolhaUsuario == 1) {
            CriarRegistro();
        }
        else if (EscolhaUsuario == 2) {
            //AlterarRegistro();
        }
        else if (EscolhaUsuario == 3) {
            //RemoverRegistro();
        }
        else if (EscolhaUsuario == 4) {
            BuscarRegistro();
        }
    }

    return 0;
}