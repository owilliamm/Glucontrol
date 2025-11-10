# Manual de Usuário Glucontrol

<img src="/imagens/logoglucontrol.jpeg" alt="Logo Glucontrol" width="30%" height="30%">

Bem-vindo ao manual de usuário do **Glucontrol**! Por favor, leia atentamente este documento antes de utilizar o software para entender seu funcionamento ideal.

Este programa possui o intuito de auxiliar pessoas portadoras de diabetes, tipo 1 ou tipo 2, no gerenciamento de informações importantes para o controle da doença. Sua função principal é o controle glicêmico, apresentando um histórico essencial para que o usuário possa repensar seus hábitos e para facilitar uma consulta médica.


## Uso do programa


O aplicativo se baseia na criação de registros através de um menu via terminal que armazena as seguintes informações:

- Aferições de glicemia
- Quantidade de carboidratos consumidos
- Doses de insulina aplicada
- Data e Horário
- Tempo de atividades físicas aeróbicas e de resistência

Ao inicializar, é mostrado o seguinte menu: 

![Menu de opções do programa](/imagens/menufinal.jpg "Menu em um terminal linux")

É a partir dele que todas as funções do programa serão utilizadas, você deve digitar o respectivo número de cada uma para usá-la. Por exemplo: para `Adicionar registro` digite `1`.

> [!WARNING]
> Caso seja inserido outro número diferente das opções disponíveis no menu, o programa indicará o erro e solicitará uma entrada novamente, porém, **digitar letras ou outros caracteres onde números são solicitados pode, em qualquer função, causar um comportamento inesperado como repetição infinitas de frases**. Nesse caso, reinicie o software para retornar à normalidade.


## Adicionar registro

Este é o passo inicial para a utilização efetiva do programa. Ao escolher esta opção, você deve responder às perguntas com os dados que queira registrar. A primeira pergunta será o tipo de diabetes, você deve digitar `1` ou `2`. Caso seja do tipo 1, as perguntas são:

-  Data e Hora
-  Valor da glicose em mg/dL
-  Carboidrato consumido em gramas
-  Unidades de dose de insulina tomadas

<img src="/imagens/Escolha1.png" alt="Exemplo de criação de um registro de diabetes tipo 1" width="75%" height="75%">


E caso seja do tipo 2, as perguntas são:

-  Data e Hora
-  Valor da glicose em mg/dL
-  Carboidrato consumido em gramas
-  Minutos de atividade aeróbica
-  Minutos de atividade de resistência

<img src="/imagens/Escolha1_Registro2.png" alt="Exemplo de criação de um registro de diabetes tipo 2" width="75%" height="75%">

Em *Data e Hora*, sua resposta deve ser escrita no formato (DD/MM/YYYY HH:MM). Em outras perguntas, não digite outros valores que não sejam números inteiros, caso contrário, será solicitado os dados novamente no formato correto.

Caso o registro seja adicionado com sucesso, aparecerá uma mensagem escrita `Registro #n criado com sucesso!`, sendo `n` o `ID` do registro, que funciona como identificador único para a utilização de outras funções (como alterar, remover ou buscar).

Nesse momento, é criado um arquivo binário `registros.bin` — no mesmo local onde está localizado o programa — que salvará seus dados.

> [!CAUTION]
> É recomendado que o usuário **não apague ou mova este arquivo**, pois todo seu histórico será apagado e/ou inutilizável. O `ID` que aparece na mensagem de sucesso é o número que você usará no futuro para alterar, remover ou buscar este registro.


## Alterar registro

Nesta seção o usuário poderá realizar alterações dos registros feitos anteriormente. Primeiro deve-se identificar qual registro queira alterar através de seu `ID` dito no momento de sua criação, caso não seja encontrado, a mensagem `Registro #n não foi encontrado. Tente novamente mais tarde.` aparecerá, sendo `n` o `ID` digitado, retornando ao menu inicial. Entretanto, se ele for localizado, o programa exibirá seus dados e solicitará os novos para que seja feita a alteração.

<img src="/imagens/Escolha2_ID.png" alt="Exemplo de alteração do registro #1" width="75%" height="75%">

![Exemplo de alterar registro não encontrado](/imagens/Escolha2_NA.jpg "Exemplo de não localizar registro para alterar")

Caso haja sucesso, a mensagem `Registro #n alterado com sucesso!` será exibida.


## Remover registro


Se por alguma hipótese o aplicativo não funcionar corretamente e criar um registro defeituoso, ou por simples vontade do usuário, é possível apagar uma ocorrência no arquivo binário através desta função. Após digitar o número `3` no menu, insira qual o `ID` do registro que deverá ser apagado. Se ele existir, será exibido a mensagem `Registro #n apagado com sucesso!`, se não, `Registro #n não encontrado`.

![Exemplo de apagar registro](/imagens/Escolha3.png "Exemplo de remoção do registro #2")

Para apagar o registro, o programa realiza os seguintes passos:

1. Cria um arquivo temporário `temp.bin`.
2. Copia para ele todas as informações do arquivo original **exceto a que será removido**.
3. Apaga o antigo registro e, por fim, renomeia o arquivo temporário para `registros.bin`, finalizando o processo.


## Buscar registro


É primordial a ação de visualizar o que foi anteriormente armazenado no arquivo binário — já que não é possível interagir com ele fora do programa — e com isso tomar melhores decisões para o controle da doença. Esta função permite a plena visualização de todos os registros desejados através de uma busca por dois métodos:

1. Busca por ID

Basta digitar o `ID` que deseja observar, caso não exista, a mensagem `ID inválido. Tente novamente.` será exibida e você deve colocar novamente o `ID` desejado. Para retornar ao menu, digite `-1`.

![Exemplo de busca por ID](/imagens/Escolha4.png "Exemplo de busca por ID (1)")

![Exemplo de busca por ID](/imagens/Escolha4_ID2.png "Exemplo de busca por ID (2)")

2. Busca por tipo

Assim que escolher este método, você deve, em seguida, decidir qual tipo de diabetes deseja verificar. Ao encontrar registros do tipo selecionado, o programa exibirá todas as respectivas informações presentes no arquivo. Se não houver dados a mostrar, a mensagem `Não foram encontrados registros` aparecerá.

<img src="/imagens/Escolha4_tipo1.jpg" alt="Exemplo de busca por tipo (1)" width="75%" height="75%">

<img src="/imagens/Escolha4_tipo2.png" alt="Exemplo de busca por tipo (2)" width="75%" height="75%">

<img src="/imagens/Escolha4_sem_registro.png" alt="Exemplo de busca por tipo (Nenhum registro deste tipo encontrado)" width="75%" height="75%">


## Sair


Por fim, para encerrar o programa, digite `5` no menu inicial e a mensagem `Saiu com sucesso` será exibida e o terminal poderá ser usado normalmente.


## Q&A

**P:** É possível recuperar um registro apagado?
**R:** Não, a função `Remover registro` é permanente.

**P:** Eu posso buscar um registro pela data ou por outro valor?
**R:** Não, somente é possível realizar a buscar pelo `ID` ou pelo tipo de diabetes.

**P:** Se o arquivo `temp.bin` se manter na minha máquina, eu posso apagá-lo?
**R:** Sim, o programa provavelmente cometeu um erro ao apagar um registro, porém certifique-se de que o Glucontrol esteja funcionando corretamente e faça um backup antes de tomar qualquer ação.

## Fim

Obrigado por ler! Esperamos que você faça bom proveito do nosso sistema.
