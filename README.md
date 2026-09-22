# Gaia — Sistema de Irrigação Automática (ESP32-C6)

> Sistema IoT de irrigação automática baseado em ESP32-C6, com leitura de umidade do solo e ventilação para circulação de ar da planta.

[![Platform](https://img.shields.io/badge/platform-ESP32--C6-blue)](https://www.espressif.com/en/products/socs/esp32-c6)
[![Framework](https://img.shields.io/badge/framework-Arduino-00979D)](https://www.arduino.cc/)
[![Build](https://img.shields.io/badge/build-PlatformIO-orange)](https://platformio.org/)
[![Status](https://img.shields.io/badge/status-em%20desenvolvimento-yellow)](#roadmap)
[![License](https://img.shields.io/badge/license-MIT-green)](#licença)

---

## 📖 Sobre o projeto

**Gaia** é um sistema de automação para cuidado de plantas, com foco em manter o solo na umidade ideal sem intervenção manual. A proposta é ler a umidade do solo continuamente e, a partir de um limiar configurável, acionar a irrigação — além de manter uma **ventoinha** ativa para circulação de ar ao redor da planta, ajudando a evitar acúmulo de umidade excessiva no ambiente e problemas como fungos e mofo.

> ⚠️ **Estágio atual:** projeto em desenvolvimento inicial (protótipo). A base do firmware em PlatformIO já está configurada; a lógica de leitura do sensor, o acionamento da irrigação e da ventoinha ainda estão sendo implementados.

---

## ✨ Funcionalidades

- [ ] Leitura de umidade do solo via sensor capacitivo/resistivo
- [ ] Irrigação automática por limiar de umidade configurável
- [ ] Ventoinha para circulação de ar ao redor da planta
- [ ] Conectividade WiFi / monitoramento remoto
- [ ] Histórico de leituras e acionamentos
- [ ] Configuração de parâmetros (limiares, horários) via app/dashboard

---

## 🔧 Hardware

### Microcontrolador

- **Placa:** ESP32-C6 (DevKitC-1)
- **Framework:** Arduino (via PlatformIO)
- **Plataforma de build:** [pioarduino/platform-espressif32](https://github.com/pioarduino/platform-espressif32)

### Componentes previstos

| Componente | Função |
|---|---|
| Sensor de umidade do solo | Determina quando a irrigação deve ser acionada |
| Bomba d'água / válvula (relé) | Aciona a irrigação |
| Ventoinha (fan) | Circulação de ar / ventilação da planta |

> 💡 Os pinos de conexão e o esquema elétrico completo serão documentados assim que a montagem for finalizada — veja [`docs/`](./docs) ou o roadmap abaixo.

---

## 📁 Estrutura do projeto

```
Gaia/
├── .vscode/        # Configurações do editor (PlatformIO/VS Code)
├── include/        # Headers (.h) do projeto
├── lib/            # Bibliotecas privadas/locais do projeto
├── src/            # Código-fonte principal (firmware)
├── test/           # Testes automatizados (PlatformIO Unit Testing)
├── platformio.ini  # Configuração de build, board e dependências
└── README.md
```

---

## 🚀 Como rodar o projeto

### Pré-requisitos

- [PlatformIO](https://platformio.org/install) (extensão para VS Code ou CLI)
- Placa ESP32-C6 DevKitC-1 conectada via USB
- Driver serial da placa instalado, se necessário

### Clonando o repositório

```bash
git clone https://github.com/newsantoryu/Gaia.git
cd Gaia
```

### Compilando e enviando o firmware

Com a extensão do PlatformIO no VS Code, basta abrir a pasta do projeto e usar os botões **Build** e **Upload**.

Ou, via linha de comando:

```bash
# Compilar o firmware
pio run

# Enviar (upload) para a placa
pio run --target upload

# Monitorar a saída serial
pio device monitor
```

### Parâmetros de conexão

| Parâmetro | Valor |
|---|---|
| Board | `esp32-c6-devkitc-1` |
| Baud rate (monitor) | 115200 |
| USB CDC on boot | Habilitado (`ARDUINO_USB_CDC_ON_BOOT=1`) |

---

## 🗺️ Roadmap

- [ ] Definir e integrar sensor de umidade do solo
- [ ] Implementar lógica de acionamento da irrigação (limiar configurável)
- [ ] Implementar controle da ventoinha
- [ ] Adicionar conectividade WiFi
- [ ] Criar dashboard/app de monitoramento remoto
- [ ] Documentar esquema elétrico e diagrama de ligação
- [ ] Adicionar testes automatizados no diretório `test/`

---

## 🤝 Contribuindo

Contribuições são bem-vindas! Sinta-se à vontade para abrir uma [issue](https://github.com/newsantoryu/Gaia/issues) ou enviar um pull request.

1. Faça um fork do projeto
2. Crie uma branch para sua feature (`git checkout -b feature/nova-feature`)
3. Commit suas mudanças (`git commit -m 'feat: adiciona nova feature'`)
4. Push para a branch (`git push origin feature/nova-feature`)
5. Abra um Pull Request

---

## ⚠️ Aviso

Este projeto envolve o controle de bomba/válvula d'água próximo a componentes eletrônicos. Observe boas práticas de isolamento elétrico e proteção contra umidade na montagem final.

---

## 📄 Licença

Distribuído sob a licença MIT. Veja `LICENSE` para mais informações.

---

## 👤 Autor

**newsantoryu**
GitHub: [@newsantoryu](https://github.com/newsantoryu)
