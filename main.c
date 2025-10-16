// armazenar informações sobre glicose, carboidrato, insulina aplicada e a data do registro.

// O sistema deve permitir que os usuários...
//     criem novos registros;
//     editem registros existentes;
//     busquem registros por ID único ou palavras chave.

// O sistema deve armazenar as informações dos registros em um arquivo.
// O sistema deve recuperar as informações do arquivo e exibi-las para o usuário.
// O sistema deve ter uma interface de usuário através do terminal.

#include <stdio.h>

// Informações a serem armazenadas.
enum TipoRegistro {
    Glicose,
    Carboidrato,
    Insulina,
};

union Dados {
    int Glicose;        // mg/DL
    int Carboidrato;    // gramas
    int Insulina;       // unidades
};

struct Registro {
    enum TipoRegistro Tipo;
    union Dados Valor;
    int ID;
    int Hora, Minuto;
    int Dia, Mes, Ano;
};

//Gerar a identificação para um registro
int GerarID() {
    FILE* arq;
    arq = fopen("registros.txt", "rb");

    if (!arq) return 1;

    struct Registro r;
    int UltimoID = 0;
    while (fread(&r, sizeof(struct Registro), 1, arq)) {
        if (r.ID > UltimoID) UltimoID = r.ID;
    }

    fclose(arq);
    return UltimoID+1;
}

//Criar registros, pedir: Tipo, Valor, Data, Hora.
void CriarRegistro() {
    FILE* arq;
    arq = fopen("registros.txt", "ab");

    int Opcao;

    struct Registro r;
    r.ID = GerarID();

    r.Dia = r.Mes = r.Ano = -1;
    r.Hora = r.Minuto = -1;

    while (r.Dia < 1 || r.Dia > 30 || r.Mes < 1 || r.Mes > 12) {
        printf("Digite o dia, mes e ano. DD/MM/YYYY: ");
        scanf("%d/%d/%d", &r.Dia, &r.Mes, &r.Ano);
        if (r.Dia < 1 || r.Dia > 30 || r.Mes < 1 || r.Mes > 12) {
            printf("Data invalida. Tente novamente.\n");
        }
    }

    while (r.Hora < 0 || r.Hora > 24 || r.Minuto < 0 || r.Minuto > 60) {
        printf("Digite o horario. HR:MN: ");
        scanf("%d:%d", &r.Hora, &r.Minuto);
        if (r.Hora < 0 || r.Hora > 24 || r.Minuto < 0 || r.Minuto > 60) {
            printf("Horario invalido. Tente novamente.\n");
        }
    }

    printf("Tipo de dado que deseja armazenar:\n"); 
    printf("1-Glicose, 2-Carboidrato, 3-Insulina\n");
    scanf("%d", &Opcao);

    if (Opcao == 1) {
        printf("Valor da glicose (mg/dL): ");
        scanf("%d", &r.Valor.Glicose);
    }
    else if (Opcao == 2) {
        printf("Carboidrato consumido (g): ");
        scanf("%d", &r.Valor.Carboidrato);
    }
    else if (Opcao == 3) {
        printf("Dose da insulina (unidade): ");
        scanf("%d", &r.Valor.Insulina);
    }

    fwrite(&r, sizeof(struct Registro), 1, arq);
    fclose(arq);

    printf("\n==================================");
    printf("\nConcluido novo registro com identificacao #%d\n", r.ID);
    printf("==================================\n");
}

//Editar registros, pedir: ID, Tipo, Valor, Data, Hora.
//Remover registros, pedir: ID
//Buscar registros, pedir: ID ou Tipo.


//Função principal
int main() {
    int EscolhaUsuario;

    while (EscolhaUsuario != 4) {
        printf("\n--------- MENU ---------\n");
        printf("1- Adicionar registro\n");
        printf("2- Alterar registro\n");
        printf("3- Buscar registro\n");
        printf("4- Remover registro\n");
        printf("5- Sair\n");
        printf("--------- MENU ---------\n\n");
        printf("Escolha: "); scanf("%d", &EscolhaUsuario);

        if (EscolhaUsuario == 1) {
            CriarRegistro();
        }
        else if (EscolhaUsuario == 2) {
            //AlterarRegistro(arquivo);
        }
        else if (EscolhaUsuario == 3) {
            //BuscarRegistro(arquivo);
        }
        else if (EscolhaUsuario == 4) {
            //RemoverRegistro(arquivo);
        }
        else if (EscolhaUsuario == 5) {
            //Sair;
        }
        
    }

}
