#include <stdio.h>
#include <stdlib.h>

enum TipoDiabetes {DM1 = 1, DM2 = 2};

union Info {
    int Insulina;
    struct {
        int Aerobica;
        int Resistencia;
    } AtividadeFisica;
};

struct Registro {
    enum TipoDiabetes Tipo;
    union Info Info;
    int ID;
    int Glicose;
    int Carboidrato;
    int DataHora[2][3]; // Data ou hora e, dependendo da escolha, Dia/Mes/Ano ou Hora/Minuto
};

//Checar se a data e valida (Extremamente simplificado, talvez somente por enquanto.)
int DataHoraValida(int V[2][3]) {
    int dia = V[0][0], mes = V[0][1], ano = V[0][2]; int hora = V[1][0], minuto = V[1][1];
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1 || hora < 0 || hora > 23 || minuto < 0 || minuto > 59) return 0;
    return 1;
}

// Gerar ID para cada registro
int GerarID() {
    FILE* arq = fopen("registros.bin", "rb");
    if (!arq) return 1;

    struct Registro r;
    int UltimoID = 0;
    while (fread(&r, sizeof(struct Registro), 1, arq)) {
        if (r.ID > UltimoID) UltimoID = r.ID;
    }

    fclose(arq);
    return UltimoID + 1;
}

// Criar registros, pedir: Tipo de diabetes, Data e Hora, Glicose, Carboidrato, Insulina/Aeróbica e Resistência.
void CriarRegistro() {
    FILE* arq = fopen("registros.bin", "ab");
    struct Registro r;
    r.ID = GerarID();

    // Usuario seleciona o tipo da diabetes
    int tipo = 0;
    while (tipo != 1 && tipo != 2) {
        printf("Digite o tipo de diabetes (1- Tipo 1, 2- Tipo 2): ");
        scanf("%d", &tipo);
        if (tipo != 1 && tipo != 2) printf("Opcao invalida. Tente novamente.\n");
    }
    r.Tipo = tipo;

    // Usuario seleciona data e hora
    r.DataHora[0][0] = r.DataHora[0][1] = r.DataHora[0][2] = 0; r.DataHora[1][0] = r.DataHora[1][1] = 0;

    while (!DataHoraValida(r.DataHora)) {
        printf("Digite a data e a hora DD/MM/YYYY HH:MM: ");
        scanf("%d/%d/%d %d:%d", &r.DataHora[0][0], &r.DataHora[0][1], &r.DataHora[0][2],
              &r.DataHora[1][0], &r.DataHora[1][1]);
        if (!DataHoraValida(r.DataHora))
            printf("Data e/ou hora invalida. Tente novamente.\n");
    }

    // Usuario insere valores (dependente do tipo de DM)
    printf("Valor da glicose (mg/dL): ");
    scanf("%d", &r.Glicose);
    printf("Carboidrato consumido (g): ");
    scanf("%d", &r.Carboidrato);

    if (r.Tipo == DM1) {
        printf("Dose de insulina (unidades): ");
        scanf("%d", &r.Info.Insulina);
    } else {
        printf("Minutos de atividade aerobica: ");
        scanf("%d", &r.Info.AtividadeFisica.Aerobica);
        printf("Minutos de atividade de resistencia: ");
        scanf("%d", &r.Info.AtividadeFisica.Resistencia);
    }

    fwrite(&r, sizeof(struct Registro), 1, arq);
    fclose(arq);

    printf("\n==================================\n");
    printf("Registro #%d criado com sucesso!\n", r.ID);
    printf("====================================\n");
}

//Alterar registros, pedir: ID, Tipo de diabetes, Data e Hora, Glicose, Carboidrato, Insulina/Aeróbica e Resistência.

//Remover registros, pedir: ID.

//Buscar registros, pedir: ID ou Tipo de diabetes.
void BuscarRegistro() {
    FILE* arq = fopen("registros.bin", "rb");
    struct Registro r;

    int Opcao = 0;
    while (Opcao != 1 && Opcao != 2) {
        printf("Buscar por 1-ID ou 2-Tipo?\n");
        scanf("%d", &Opcao);
    }

    if (Opcao == 1) {
        int EscolhaID = 1;
        int Valido = 0;
        while (!Valido) {
            printf("Digite um ID: ");
            scanf("%d", &EscolhaID);
            fseek(arq, (EscolhaID - 1) * sizeof(struct Registro), SEEK_SET);

            if (fread(&r, sizeof(struct Registro), 1, arq) == 1) {
                printf("\nRegistro ID %d:\n", r.ID);
                printf("Data: %02d/%02d/%04d - %02d:%02d\n", r.DataHora[0][0], r.DataHora[0][1], r.DataHora[0][2], r.DataHora[1][0], r.DataHora[1][1]);
                printf("Glicose: %d mg/dL\n", r.Glicose);
                printf("Carboidrato consumido: %d g\n", r.Carboidrato);
                
                if (r.Tipo == DM1) {
                    printf("Dose de insulina: %d unidades\n", r.Info.Insulina);
                } else {
                    printf("Minutos de atividade aerobica: %d mins\n", r.Info.AtividadeFisica.Aerobica);
                    printf("Minutos de atividade de resistencia: %d mins\n", r.Info.AtividadeFisica.Resistencia);
                }
                Valido = 1;
            } else {
                printf("ID invalido. Tente novamente.\n");
            }
        }
    }

    else if (Opcao == 2) {
        int TipoSelecionado = 0;
        while (TipoSelecionado != 1 && TipoSelecionado != 2) {
            printf("Digite o tipo de diabetes para buscar (1- DM1, 2- DM2): ");
            scanf("%d", &TipoSelecionado);
        }

        if (TipoSelecionado == 1) {
            printf("\n=======================\n");
            printf("Registros do tipo DM1:\n");
            printf("=======================\n");
        } else {
            printf("\n=======================\n");
            printf("Registros do tipo DM2:\n");
            printf("=======================\n");
        }

        while (fread(&r, sizeof(struct Registro), 1, arq) == 1) {
            if (r.Tipo == TipoSelecionado) {
                printf("\nRegistro ID %d:\n", r.ID);
                printf("Data: %02d/%02d/%04d - %02d:%02d\n", r.DataHora[0][0], r.DataHora[0][1], r.DataHora[0][2], r.DataHora[1][0], r.DataHora[1][1]);
                printf("Glicose: %d mg/dL\n", r.Glicose);
                printf("Carboidrato consumido: %d g\n", r.Carboidrato);
                    
                if (r.Tipo == DM1) {
                    printf("Dose de insulina: %d unidades\n", r.Info.Insulina);
                } else {
                    printf("Minutos de atividade aerobica: %d mins\n", r.Info.AtividadeFisica.Aerobica);
                    printf("Minutos de atividade de resistencia: %d mins\n", r.Info.AtividadeFisica.Resistencia);
                }
            }
        }
    }
    fclose(arq);
}

//Funcao principal
int main() {
    int EscolhaUsuario = 0;
    while (EscolhaUsuario != 5) {
        printf("\n--------- MENU ---------\n");
        printf("1- Adicionar registro\n");
        printf("2- Alterar registro\n");
        printf("3- Remover registro\n");
        printf("4- Buscar registro\n");
        printf("5- Sair\n");
        printf("--------- MENU ---------\n");
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
}