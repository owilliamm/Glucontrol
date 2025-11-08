//Tipo enumerado para representar o tipo de diabetes, onde DM1=1 e DM2=2
enum TipoDiabetes {DM1 = 1, DM2 = 2};

//Uma union que armazena OU insulina OU atividades físicas (ocupa o espaço da memória da struct interna)
union Info {
    int Insulina;        //Quantidade de insulina usada (somente para DM1)
    struct {             //Estrutura para caso em que o usuário seja DM2
        int Aerobica;    //Minutos de atividade aeróbica
        int Resistencia; //Minutos de atividade de resistência
    } AtividadeFisica;
};

// Estrutura principal que representa um registro do paciente
struct Registro {
    enum TipoDiabetes Tipo; //Armazena o tipo de diabetes (DM1 ou DM2)
    union Info Info;        //    =    Insulina (DM1) OU dados de atividade física (DM2)
    int ID;                 //    =    Identificador do registro
    int Glicose;            //    =    Valor da glicemia medida
    int Carboidrato;        //    =    Quantidade de carboidratos consumidos
    int DataHora[2][3];     //    =    Matriz bidimensional para armazenar data e hora, DataHora[0]=[Dia, Mes, Ano], DataHora[1]=[Hora, Minuto]
};
