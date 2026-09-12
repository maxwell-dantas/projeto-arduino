# JARVIS - Robô com Arduino

Robô móvel desenvolvido em C++ para Arduino, com quatro motores DC, duas
pontes H e sensor ultrassônico HC-SR04. O robô movimenta-se continuamente para
a frente e executa uma rotina de desvio quando identifica um obstáculo a até
30 cm.

> **Versão principal:** [`jarvis/jarvis_v4.ino`](./jarvis/jarvis_v4.ino)

## Funcionalidades

- Movimento contínuo para frente.
- Movimento temporizado para frente e para trás.
- Giro para a direita e para a esquerda.
- Giro no sentido horário sobre o próprio eixo.
- Medição de distância com o HC-SR04.
- Parada automática diante de obstáculos.
- Rotina de desvio: recua por 800 ms e gira por 700 ms.

## Hardware

- Arduino Mega (a versão atual utiliza os pinos digitais 31 a 53).
- Quatro motores DC e chassi compatível.
- Duas pontes H para acionamento dos motores.
- Sensor ultrassônico HC-SR04.
- Fonte ou bateria adequada para os motores.
- Fios, conectores e demais elementos de montagem.

As pontes H e o Arduino devem compartilhar o GND. A alimentação dos motores
deve ser dimensionada para a corrente dos quatro motores e não deve ser
retirada diretamente do pino de 5 V do Arduino.

## Pinagem

### Pontes H e motores

| Ponte H | Função | Pino Arduino |
| --- | --- | ---: |
| A | Motor dianteiro - IN1 | 31 |
| A | Motor dianteiro - IN2 | 33 |
| A | Motor traseiro - IN3 | 35 |
| A | Motor traseiro - IN4 | 37 |
| A | Enable motor dianteiro (ENA) | 10 |
| A | Enable motor traseiro (ENB) | 9 |
| B | Motor traseiro - IN1 | 47 |
| B | Motor traseiro - IN2 | 49 |
| B | Motor dianteiro - IN3 | 51 |
| B | Motor dianteiro - IN4 | 53 |
| B | Enable motor traseiro (ENA) | 3 |
| B | Enable motor dianteiro (ENB) | 2 |

Os pinos `EN` recebem sinais PWM para controlar a velocidade. A versão atual
usa os valores `255`, `235`, `245` e `245`, respectivamente, para os quatro
canais de acionamento.

### Sensor HC-SR04

| Sinal | Pino Arduino |
| --- | ---: |
| `TRIG` | 22 |
| `ECHO` | 24 |

Conecte também `VCC` do sensor ao 5 V e `GND` ao GND. Se for utilizada uma
placa diferente do Arduino Mega, verifique se todos os pinos definidos no
código existem e se os pinos de enable suportam PWM.

## Como executar

1. Instale a [Arduino IDE](https://www.arduino.cc/en/software).
2. Abra o arquivo `jarvis/jarvis_v4.ino`.
3. Selecione a placa e a porta correspondentes ao Arduino.
4. Revise a pinagem e a alimentação antes de energizar os motores.
5. Compile e carregue o sketch na placa.
6. Abra o Monitor Serial em `9600 baud` para acompanhar as distâncias.

Não é necessário instalar bibliotecas externas: o sketch utiliza apenas
recursos nativos da plataforma Arduino.

## Lógica de funcionamento

Em cada ciclo, o programa envia um pulso de 10 microssegundos ao `TRIG` e
calcula a distância a partir do tempo de retorno no `ECHO`.

- **Distância maior que 30 cm (ou nenhuma detecção válida):** o robô continua
  avançando.
- **Distância entre 1 e 30 cm:** o robô para, espera 300 ms, recua por 800 ms e
  realiza um giro horário por 700 ms.
- Após a manobra, a leitura é repetida e o comportamento é escolhido
  novamente.

## API de movimentos

A estrutura `Movimentos`, definida em `jarvis_v4.ino`, disponibiliza:

| Método | Comportamento |
| --- | --- |
| `andarFrente(tempo)` | Avança pelo tempo informado em milissegundos e para. |
| `andarTras(tempo)` | Recua pelo tempo informado em milissegundos e para. |
| `girarDireitaFrente(tempo)` | Aciona o conjunto do lado B para virar à direita. |
| `girarEsquerdaFrente(tempo)` | Aciona o conjunto do lado A para virar à esquerda. |
| `giroPerfeitoHorario(tempo)` | Gira sobre o próprio eixo no sentido horário. |
| `moverFrenteContinuo()` | Mantém os quatro motores acionados para frente. |
| `pararRobo()` | Desliga os motores. |

Os tempos e o limite de distância podem ser ajustados diretamente no arquivo
`jarvis_v4.ino`, considerando o peso do chassi, a tensão da bateria e o espaço
disponível para a manobra.

## Estrutura do projeto

```text
.
├── jarvis/
│   ├── jarvis_v1.ino
│   ├── jarvis_v2.ino
│   ├── jarvis_v3.ino
│   └── jarvis_v4.ino   # versão atual
├── artigo/
│   └── modelo_artigo_IEEEtran.tex
├── LICENSE
└── README.md
```

As versões anteriores são mantidas para histórico. Para novas montagens e
testes, utilize o `jarvis_v4.ino`.

## Licença

Este projeto é distribuído sob a [licença MIT](./LICENSE).