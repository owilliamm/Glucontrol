# Sistema Glucontrol
## Objetivos
- Criar registros para facilitar pacientes no controle da Diabetes
- Facilitar o monitoramento dos dados do paciente aos médicos responsáveis

## Guia da Aplicação
Através do menu, o usuário pode escolher uma entre cinco opções:
- Adicionar Registro
- Alterar Registro
- Remover Registro
- Buscar Registro
- Sair da aplicação


![imagem](menu.png)

### Adicionar Registro
A função `CriarRegistro()` adiciona um registro e é a função mais importante do projeto. Sem ela não se pode alterar, remover ou buscar um registro. \
Nela selecionamos o **tipo de diabetes**, **data e hora** do registro e **outras informações adicionais** que dependem do tipo selecionado.

Se o paciente for do **Tipo 1**:
- 
