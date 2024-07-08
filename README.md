# lala

## Decisões de design, limitações, defeitos e divergências

Discutir objetos globais, vantagem do linker vs ponteiros

burst, pseudo-dispositivo, clock

Namespace de macros do preprocessor é poluído.

A especificação pede para causar preempção num processo assim que surgir outro
com prioridade superior ao atual, porém nesta implementação isso não ocorre.

Okay. Antes nós só pegávamos `next` quando a CPU estava ociosa. Agora,
devemos checar também quando novos processos entram pro PSJF. Na verdade,
sempre que um IO completar, talvez deva reconsiderar qual executar!
Então um processo _sempre_ pode mudar.

E aí, o _quantum_ varia. PSJF não precisa de quantum! Porque quanto mais o processo
mais curto executar, mais curto ainda será! SLK. Mas como fica o burst??
Tipo, o `next` controla??

Mas pro MFP, quantum começa em --, pois só o next decrementa daí!
E a próxima execução do `next` checa o quantum. Ou a prioridade!

Porque antes do `next` "chegam" processos novos e desbloqueados!

E tem a competição do PID. """""""""""""filas""""""""""""" meu ovo.

Quantos tiros no pé vamos nos dar?

Tipo a porra do `empty`.

E aqui temos a PORRA da contradição da especificação do trabalho.
No final, fala que deve preservar FIFO, ou seja, a fila se comportar como FILA
Mas antes, fica falando de preferir PID menor e escolher menor prioridade.
E aí?

Interpretação. Mantém FIFO. Substitui só se prioridade menor. Mas `push` insere EM ORDEM
por causa da regra do PID só para os AO MESMO tempo NAQUELE ciclo de clock. BULLSHIT é claro.

Podia montar uma única chamada `push` que recebe uma lista encadeada inteira

E o PSJFC? SLK

uuuuuuuhhhhrr

push(`*`, int `n_new`, `n_wait`, `n_`

E NA VERDADE, preempção ao FIM do burst. mas que é ao mesmo tempo que ANTES do próximo??
Tudo igual.

Marcar no push um true, e no next um false, entre true e false ordenar tudo.

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
