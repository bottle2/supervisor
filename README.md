# lala

## Decisões de design, limitações, defeitos e divergências

Discutir objetos globais, vantagem do linker vs ponteiros

burst, pseudo-dispositivo, clock

Namespace de macros do preprocessor é poluído.

## Contratos

Não classificado:

- Menor PID ganha

### Contrato: alimentação de dados

- [X] Ler linhas
- [X] Ler PID, garantido ser único
- [X] Ler tempo de chegada, igual ou maior que zero
- [X] Ler tempo de burst, maior que zero
- [X] Ler prioridade, entre 0 e 7 (inclusive)
- [X] Adicionar processos por ordem de chegada

### Contrato: ciclo de vida

- [ ] Configurar escalonador desejado
- [ ] Término de simulação

### Contrato: processos

- [ ] Escolha de processo a executar no momento
- [ ] API para manusear listas encadeadas
- [ ] Tentar solicitar IO
- [ ] Devolver ao escalonador processos cuja IO completou
- [ ] XXX quantum

### Contrato: política de Múltiplas Filas com Prioridades (FMP)

- [ ] 

### Contrato: política de Shortest Job First preemptivo (SJF)

- [ ] 

### Contrato: opções de linha de comando

- [X] Tratar opção -v de verbosidade
- [X] Tratar opção -F de escalonamento FMP
- [X] Tratar opção -S de escalonamento SJF
- [X] Obedecer às [convenções POSIX 2017 de utiliários](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap12.html)

### Contrato: estatísticas

- [ ] Número de processos executados
- [ ] Tempo total decorrido
- [ ] Tempo total por processo (*throughput*)
- [ ] Tempo total que cada processo ficou em cada estado: _ready_, _wait_ e _running_
- [ ] Processos com maior e menor tempo no sistema
- [ ] Atualizar as estatísticas ao completar processo
- [X] Impressão formatada de estatísticas na saída padrão

### Contrato: saída verbosa

- [ ] 

### Contrato: outros

- [X] Localização apropriada
- [ ] Organização do código
