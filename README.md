# Embarcados - Formiga Robótica
Escola de Engenharia de São Carlos - Universidade São Paulo <br />
Projeto de formiga robótica para disciplina Sistemas Embarcados (EESC-USP). <br />
Professores: Glauco Caurin e Daniel Varela.

Alunos:  <br />
Manoela Estabile Rodrigues (10308843)<br />
Marcela Sanae Honma (10309503) <br />
Victor Moreira Santos (10274008) <br />


## 1. Introdução
O projeto da Formiga Robótica tem como objetivo implementar uma lógica de movimentos do robô proposto a partir do uso de sistemas embarcados. Para isso, foi desenvolvido o projeto que contempla a lógica de caminhada da formiga, bem como a comunicação entre o usuário e o robô. O controle da formiga foi feito através de uma Toradex Colibri VF50 e duas Mbeds LPC1768.

## 2. Desenvolvimento

## 2.1. Rotina de movimentação
A formiga robótica possui 2 servos motores (um para rotação e outro para elevação) em cada uma de suas 6 patas. Para implementar a lógica da caminhada da formiga robótica, elaboramos um diagrama geral da rotina do robô. Com as pernas enumeradas de 1 a 6, foram definidas os possíveis comandos (frente, trás, direita e esquerda) e sua respectiva sequência de movimentos. Além disso, o acionamento dos motores é incremental e, por isso, é possível mudar a direção da trajetória do robô ou migrar para posição de repouso caso haja uma falha na comunicação. O diagrama da rotina de movimentação encontra-se logo abaixo.

![image](https://github.com/manoelaestabile/embarcados_formiga/blob/main/Diagrama%20de%20blocos%20-%20formiga.png?raw=true)

Para desenvolver o código, foi necessário definir os servos de elevação e rotação de cada perna e descrever cada conjunto de ações para cada comando de movimento. Basicamente, para o comando de mover para frente, o primeiro passo é mover simulataneamente as pernas 1,3 e 5, que consiste em: elevar a perna; rotacionar; descer e continuar rotacionando até voltar ao solo; recuar para posição inicial e zerar todos os contadores. Em seguida, para continuar o comando, pode realizar a sequência das pernas 2,4 e 6 e assim sucessivamente. Já para girar para a esquerda, a sequência de movimentos para as duas primeiras pernas são iguais, porém a última perna realiza a sequência de mover para a esquerda, que consiste em: elevar a perna; rotacionar; continuar rotacionando e descer e rotacionar até a posição inicial. Os ângulos dos motores enquanto a formiga marcha para frente podem ser observados na imagem abaixo.

![untitled](https://user-images.githubusercontent.com/88212397/127944036-dbb27514-52ff-44ce-baac-e4f7ee99fcea.jpg)

## 2.2. Componentes de controle e comunicação 

O controle da formiga robótica foi feito por 

![image](https://github.com/manoelaestabile/embarcados_formiga/blob/main/Fluxo%20de%20comunica%C3%A7%C3%A3o%20-%20formiga.png)


Como cada placa toradex suporta até 6 conexões e a formiga robótica é composta por 12 servos motores, foram utilizamos 2 Mbeds, na qual uma faz o controle dos 6 motores presentes das pernas ímpares e a outra faz o controle dos motores presentes das pernas pares. O grupo optou por desenvolver as instruções nas próprias Mbeds. Assim, a toradex tem apenas o papel de ler o comando vindo do computador e comunicar para a Mbed correspondente por meio do protocolo CAN.

Para que haja comunicação entre o computador do laboratório e a toradex, é necessário seguir alguns passos, como foi realizado em aula. Primeiro, é feito a conexão remota pelo _Anydesk_. Com o _SDK (Software Development Kit)_ instalado, executamos uma série de instruções no diretório home para exportar as variáveis e então realizar o _Cross Compiling_. Para enviar ao _target_, que nesse caso é a Toradex, identificamos o seu IP e aplicamos no outro terminal o protocolo _SSH (Security Shell)_, que permite conexões criptografadas entre cliente e servidor.Assim, é possível executar o código na toradex.






Introduçao
Logica da caminhada da formiga (aquele diagrama esquematico que temos + logica do codigo do ph)
Pc-toradex 
Toradex-mbed (can)
Funçao de cada componente (o que vai acontecer na toradex e nas mbeds - codigo do ph)
Testes (feitos, nao feitos, deveriam ser feitos)
Conclusão pra ficar bonito
