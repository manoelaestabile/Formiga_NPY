# Embarcados - Formiga Robótica
Projeto de formiga robótica para disciplina Sistemas Embarcados (EESC-USP).Alunos envolvidos: Manoela Rodrigues, Marcela Honma, Victor Moreira.

## Introdução
O projeto da Formiga Robótica tem como objetivo implementar uma lógica de movimentos do robô proposto a partir do uso de sistemas embarcados. Para isso, foi desenvolvido o código para descrever a caminhada da formiga, além da comunicação entre toradex e Mbed pelo protocolo CAN.

## Desenvolvimento
A formiga robótica possui 2 servos motores em cada uma de suas 6 patas. Para implementar a lógica da caminhada da formiga robótica, elaboramos um diagrama geral da rotina do robô. Com as pernas enumeradas de 1 a 6, foram definidas os possíveis comandos (frente, trás, direita e esquerda) e sua respectiva sequência de movimentos. Além disso, como o movimento é incremental, caso queira interromper algum movimento, o programa permite que as pernas da formiga voltem ao solo para repouso. O diagrama encontra-se logo abaixo.

![image](https://user-images.githubusercontent.com/82612592/127589260-1ed236b8-fc52-4524-ab71-36cfe67e2d29.png)

Como cada placa toradex suporta até 6 conexões e a formiga robótica é composta por 12 servos motores, foram utilizamos 2 Mbeds, na qual uma faz o controle dos 6 motores presentes das pernas ímpares e a outra faz o controle dos motores presentes das pernas pares. O grupo optou por desenvolver as instruções nas próprias Mbeds. Assim, a toradex tem apenas o papel de ler o comando vindo do computador e comunicar para a Mbed correspondente por meio do protocolo CAN.

Para que haja comunicação entre o computador do laboratório e a toradex, é necessário seguir alguns passos, como foi realizado em aula. Primeiro, é feito a conexão remota pelo _Anydesk_. Com o _SDK (Software Development Kit)_ instalado, executamos uma série de instruções no diretório home para exportar as variáveis e então realizar o _Cross Compiling_. Para enviar ao _target_, que nesse caso é a Toradex, identificamos o seu IP e aplicamos no outro terminal o protocolo _SSH (Security Shell)_, que permite conexões criptografadas entre cliente e servidor.Assim, é possível executar o código na toradex.

Para desenvolver o código, foi necessário definir os servos de elevação e rotação de cada perna e descrever cada conjunto de ações para cada comando de movimento. Basicamente, para o comando de mover para frente, o primeiro passo é mover simulataneamente as pernas 1,3 e 5, que consiste em: elevar a perna; rotacionar; descer e continuar rotacionando até voltar ao solo; recuar para posição inicial e zerar todos os contadores. Em seguida, para continuar o comando, pode realizar a sequência das pernas 2,4 e 6 e assim sucessivamente. Já para girar para a esquerda, a sequência de movimentos para as duas primeiras pernas são iguais, porém a última perna realiza a sequência de mover para a esquerda, que consiste em: elevar a perna; rotacionar; continuar rotacionando e descer e rotacionar até a posição inicial. 




Introduçao
Logica da caminhada da formiga (aquele diagrama esquematico que temos + logica do codigo do ph)
Pc-toradex 
Toradex-mbed (can)
Funçao de cada componente (o que vai acontecer na toradex e nas mbeds - codigo do ph)
Testes (feitos, nao feitos, deveriam ser feitos)
Conclusão pra ficar bonito
