# Manual de Usuário Glucontrol

Bem-vindo ao manual de usuário do **Glucontrol**!. Por favor, leia atentamente este documento antes de utilizar o software para entender seu funcionamento ideal.

Este programa possui o intuito de auxiliar pessoas portadoras de diabates, tipo 1 ou tipo 2, no gerenciamento de informações importantes para o controle da doença. Sua função principal é o controle glicemico, apresentando um histórico primordial para que o usuário possa repensar seus hábitos e de facilitar uma consulta médica.

## Uso do programa

O aplicativo se baseia na criação de registros através de um menu via terminal que armazena as seguintes informações:

- Aferições de glicemia
- Quantidade de carboidratos consumidos
- Doses de insulina aplicada
- Data e Horário
- Tempo de atividades físicas aeróbicas e de resistência

Ao inicializar, é mostrado o seguinte menu: 

![Menu de opções do programa](/imagens/menu.png "Menu em um terminal linux")

É a partir dele que todas as funções do programa serão utilizadas, você deve digitar o número respectivo de cada uma para usá-la. Por exemplo: para `Adicionar registro` digite `1`.

> [!WARNING]
> Neste caso, se for digitado outro número, o programa indicará o erro e solicitará novamente, porém, **digitar outros caracteres diferentes do solicitados pode, em qualquer momento, causar um mau funcionamento**. Nesses casos é recomendado o reinicio do software para retornar à normalidade.

## Adicionar registro

Este é o passo inicial para a utilização efetiva do programa. Ao escolher esta opção, você deve responder às perguntas com os dados que queira registrar. A primeira pergunta será o tipo de diabates, você deve digitar `1` ou `2`. Caso seja do tipo 1, as perguntas são:

-  Data e Hora
-  Valor da glicose em mg/dL
-  Carboidrato consumido em gramas
-  Unidades de dose de insulina tomadas

![Exemplo de criação de um registro tipo 1](/imagens/Escolha1.png "Exemplo de criação de um registro de diabetes tipo 1")

E caso seja do tipo 2, as perguntas são:

-  Data e Hora
-  Valor da glicose em mg/dL
-  Carboidrato consumido em gramas
-  Minutos de atividade aeróbica
-  Minutos de atividade de resistência

![Exemplo de criação de um registro tipo 2](/imagens/Escolha1_Registro2.png "Exemplo de criação de um registro de diabetes tipo 2")

Em *Data e Hora*, sua resposta deve ser escrita no formato (DD/MM/YYYY HH:MM). Nas outras perguntas, não digite outros valores que não sejam números inteiros, caso contrário será solicitado os dados novamente no formato correto.

Caso o registro seja adicionado com sucesso, aparecerá uma mensagem escrita `Registro #n criado com sucesso!`, sendo `n` o `ID` do registro, que funciona como identificador para a utilização de outras funções.

Nesse momento, é criado um arquivo binário `registros.bin` — no mesmo local onde está armazenado o programa — que armazena todos os registros criados. É recomendado que o usuário não apague este arquivo, pois todos os registros serão apagados permanentemente. Ela também usa uma função auxiliar que cria um ID para cada uso da função e mostrando-o.

## Alterar Registro

Nesta seção o usuário poderá realizar alterações dos registros feitos anteriormente. Primeiro deve-se identificar qual registro queira alterar através de seu ID dito no momento de sua criação, caso não seja encontrado, a mensagem `Registro #n não foi encontrado. Tente novamente mais tarde.` aparecerá, sendo `n` o `ID` digitado, retornando ao menu inicial. Entretanto, se ele for localizado, o programa exibirá seus dados e solicitará os novos para que seja feita a alteração.

![Exemplo de alterar registro](/imagens/Escolha2_ID.png "Exemplo de alteração do registro #1")

Caso haja sucesso, a mensagem `Registro #n alterado com sucesso!` será exibida.
