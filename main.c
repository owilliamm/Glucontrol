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
        printf("Digite o tipo de diabetes (1 - Tipo 1, 2 - Tipo 2): ");
        scanf("%d", &tipo);
        if (tipo != 1 && tipo != 2) printf("Opcao invalida. Tente novamente.\n");
    }
    r.Tipo = tipo;

    // Usuario seleciona data e hora
    r.DataHora[0][0] = r.DataHora[0][1] = r.DataHora[0][2] = 0; r.DataHora[1][0] = r.DataHora[1][1] = 0;

    while (!DataHoraValida(r.DataHora)) {
        printf("Digite a data e a hora (DD/MM/YYYY HH:MM): ");
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


void AlterarRegistro(){
    int ID_Alt;
    struct Registro r;
    int achei = 0; //se achar o registro, muda pra 1

    FILE *arq = fopen("registros.bin","rb+"); //rb+ pq ele vai ler e escrever por causa das alteracoes

    if (!arq) { //arquivo nao existe ou tem erro
        printf("Tivemos um problema com o arquivo. Tente novamente mais tarde. \n");
        return; //finaliza a funcao
    }

    printf("ID para alterar: ");
    scanf("%d", &ID_Alt);

    while(fread(&r,sizeof(struct Registro), 1, arq) == 1) {
        if (r.ID == ID_Alt) {
            achei = 1;
        

        //Mostrar dados para o user
        printf("\n---- REGISTRO ENCONTRADO ----\n");
        printf("ID: %d\n", r.ID);
        if (r.Tipo == DM1) {
            printf("Tipo de Diabetes: 1\n");
            printf("Dose de insulina: %d unidades\n", r.Info.Insulina);
        } else {
            printf("Tipo de Diabetes: 2\n");
            printf("Minutos de atividade aerobica: %d min\n", r.Info.AtividadeFisica.Aerobica);
            printf("Minutos de atividade de resistencia: %d min\n", r.Info.AtividadeFisica.Resistencia);
            
        }   

        printf("Data: %02d/%02d/%04d - %02d:%02d\n", r.DataHora[0][0], r.DataHora[0][1], r.DataHora[0][2], r.DataHora[1][0], r.DataHora[1][1]);
        printf("Glicose: %d mg/dL\n", r.Glicose);
        printf("Carboidrato consumido: %d g\n", r.Carboidrato);
        printf("===============\n\n");

        fseek(arq, -sizeof(struct Registro), SEEK_CUR);

        printf("----- ALTERACAO DOS DADOS -----\n");
        int DataHoraAlt[2][3] = {{0, 0, 0}, {0, 0}};
        while (!DataHoraValida(DataHoraAlt)) {
            
            printf("Digite a nova data e hora (DD/MM/YYYY HH:MM): ");
            scanf("%d/%d/%d %d:%d", &DataHoraAlt[0][0], &DataHoraAlt[0][1], &DataHoraAlt[0][2], &DataHoraAlt[1][0], &DataHoraAlt[1][1]);
            if (!DataHoraValida(DataHoraAlt)) {
                printf("Data e/ou hora invalida. Tente novamente mais tarde.\n");
            }
        }

        // passar a datahora inserida pro registro
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                r.DataHora[i][j] = DataHoraAlt[i][j];
            }
        }

        printf("Novo valor da glicose (mg/dL): ");
        scanf("%d", &r.Glicose);
        printf("Novo carboidrato consumido (g): ");
        scanf("%d", &r.Carboidrato);

        if (r.Tipo == DM1) {
            printf("Tipo de Diabetes: 1\n");

            printf("Nova dose de insulina (unidades): ");
            scanf("%d", &r.Info.Insulina);

        } else {
            printf("Tipo de Diabetes: 2\n");

            printf("Minutos de atividade aerobica: ");
            scanf("%d", &r.Info.AtividadeFisica.Aerobica);

            printf("Minutos de atividade de resistencia: ");
            scanf("%d", &r.Info.AtividadeFisica.Resistencia);
            
        }

        fwrite(&r, sizeof(struct Registro), 1, arq);

        printf("\n==================================\n");
        printf("Registro #%d alterado com sucesso!\n", r.ID);
        printf("====================================\n");

        break;

        }
    }  

    if (!achei) { //se nao for achado
        printf("Registro #%d nao foi encontrado. Tente novamente mais tarde.\n", ID_Alt);
    }

    fclose(arq);
}


void RemoverRegistro(){

    //Copiar os registros para um ID temporário (exceto o que é pra remover) e renomear no final
    struct Registro r;

    FILE *arq = fopen("registros.bin", "rb");
    FILE *arq_tmp = fopen("temp.bin","wb");

    if(!arq){printf("Erro em encontrar aquivo original para remover o registro");fclose(arq);}
    if(!arq_tmp){printf("Erro em remover o registro");fclose(arq_tmp);}

    int id_remover;
    printf("Qual o registro deseja remover? ");
    scanf("%d",&id_remover);

    short int encontrado = 0;

    while(fread(&r, sizeof(struct Registro), 1, arq) == 1){

        if (r.ID == id_remover){encontrado = 1;}
        else {fwrite(&r, sizeof(struct Registro), 1, arq_tmp);} //copiar os outros registros

    }

    fclose(arq); fclose(arq_tmp);

    if (encontrado == 1){

        remove("registros.bin");
        rename("temp.bin","registros.bin");
        printf("\n==================================\n");
        printf("Registro #%d apagado com sucesso!\n", id_remover);
        printf("====================================\n");
    }

    if (encontrado == 0){

        remove("temp.bin");
        printf("\n==================================\n");
        printf("Registro #%d não encontrado\n", id_remover);
        printf("====================================\n");

    }
}

void BuscarRegistro() {
    FILE* arq = fopen("registros.bin", "rb");
    struct Registro r;

    int Opcao = 0;
    while (Opcao != 1 && Opcao != 2) {
        printf("Buscar por 1 - ID ou 2 - Tipo? ");
        scanf("%d", &Opcao);
    }

    if (Opcao == 1) {
        int EscolhaID = 1;
        int Valido = 0;
        while (!Valido) {
            printf("\nDigite um ID (-1 para voltar ao MENU): ");
            scanf("%d", &EscolhaID);
            if (EscolhaID == -1){break;} //caso não tenha registro pra buscar, digitar -1 volta para o menu
            fseek(arq, (EscolhaID - 1) * sizeof(struct Registro), SEEK_SET);

            if (fread(&r, sizeof(struct Registro), 1, arq) == 1) {
                printf("\nRegistro ID %d:\n", r.ID);
                printf("Data: %02d/%02d/%04d - %02d:%02d\n", r.DataHora[0][0], r.DataHora[0][1], r.DataHora[0][2], r.DataHora[1][0], r.DataHora[1][1]);
                printf("Glicose: %d mg/dL\n", r.Glicose);
                printf("Carboidrato consumido: %d g\n", r.Carboidrato);
                
                if (r.Tipo == DM1) {
                    printf("Dose de insulina: %d unidades\n", r.Info.Insulina);
                } else {
                    printf("Minutos de atividade aerobica: %d min\n", r.Info.AtividadeFisica.Aerobica);
                    printf("Minutos de atividade de resistencia: %d min\n", r.Info.AtividadeFisica.Resistencia);
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
            printf("Digite o tipo de diabetes para buscar (1 - DM1, 2 - DM2): ");
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
                    printf("Minutos de atividade aerobica: %d min\n", r.Info.AtividadeFisica.Aerobica);
                    printf("Minutos de atividade de resistencia: %d min\n", r.Info.AtividadeFisica.Resistencia);
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
            AlterarRegistro();
        }
        else if (EscolhaUsuario == 3) {
            RemoverRegistro();
        }
        else if (EscolhaUsuario == 4) {
            BuscarRegistro();
        }
        else if (EscolhaUsuario == 5){
           printf("Saiu com sucesso.\n");
        }
        else {
            printf("Numero invalido. Tente novamente.\n");
        }
    }
}
