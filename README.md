# Embarcados - Formiga Robótica
Projeto de formiga robótica para disciplina Sistemas Embarcados (EESC-USP). Alunos envolvidos: Manoela Rodrigues, Marcela Honma, Victor Moreira.

teste teste teste (o relatório deveria ser aqui?)
Conteúdo do relatório e do projeto de forma geral: ccomunicação usuário/pc - toradex, comunicação toradex-mbed, testes de recebimento de mensagem e execução de comando, código com padrão de movimento das pernas da formiga

![image](https://user-images.githubusercontent.com/82612592/127589260-1ed236b8-fc52-4524-ab71-36cfe67e2d29.png)

Imagem teste

## Tópico 2

# Comunicação entre Computador e Toradex
Para que haja comunicação entre o computador do laboratório e a toradex, é necessário seguir alguns passos, como foi realizado em aula. Primeiro, é feito a conexão remota pelo _Anydesk_. Com o _SDK (Software Development Kit)_ instalado, executamos uma série de instruções no diretório _home_ para exportar as variáveis e então realizar o _Cross Compiling_ a partir do comando _> ${CC} -Wall hello.c -o helloARM_. Para enviar ao _target_, que nesse caso é a Toradex, identificamos o seu IP e utilizamos o comando _> scp helloARM root@172.17.2.XXX:/home/root_. Por fim, aplicamos no outro terminal o protocolo _SSH (Security Shell)_, que permite conexões criptografadas entre cliente e servidor.Assim, para executar o código na toradex, utilizamos os comandos _> ssh root@172.168.2.XXX_,  _>>ls -1_ e _>> ./helloARM_.
