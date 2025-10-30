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