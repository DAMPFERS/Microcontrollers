"Для отладки используйте launch.json:

DE
VSCode: Используйте расширение Cortex-Debug:

Настройте файл launch.json:
json
Копировать код
{
  "version": "0.2.0",
  "configurations": [
    {
      "type": "cortex-debug",
      "request": "launch",
      "servertype": "openocd",
      "cwd": "${workspaceRoot}",
      "executable": "./firmware.elf",
      "device": "STM32F103C8",
      "configFiles": [
        "interface/stlink.cfg",
        "target/stm32f1x.cfg"
      ]
    }
  ]
}
Теперь вы можете использовать отладчик прямо из VSCode."



# Настройка

1. В CubeIDE создается проект.
2. Копируются папки: Core, Drivers, файл линковки ххх.ld
3. В мейк файле указываются директории с заголовками и исп-ые файлы
4. В файле конфигурации указываются теже пути 



# Работа с программатором
Переход в режим загрузщика: BOOT0 -> 1, BOOT0 -> 0 (and restaurt)
cmd:
    STM32_Programmer_CLI -c port=SWD   -> проверить наличие подключения к программатору ST-Link

Если хотите полностью очистить память устройства:
    STM32_Programmer_CLI -c port=SWD -e all



Чтобы увидеть текущие настройки памяти (включая уровень защиты RDP), выполните следующую команду:
    STM32_Programmer_CLI -c port=SWD -rdu


Проверка текущих опций загрузки:
    STM32_Programmer_CLI -c port=SWD -ob displ


cброс защиты от чтения (RDP):
    STM32_Programmer_CLI -c port=SWD -ob RDP=0xAA

    0xAA – отключение защиты.
    0xBB – включение уровня 1 защиты.

    После успешного подключения сбросьте конфигурацию защиты и переключите BOOT0 обратно на GND.



st-info (в Linux или WSL): Установите пакет:
    sudo apt install stlink-tools
    st-info --probe   -> Проверьте подключение

Перезагрузка контроллера:
    STM32_Programmer_CLI -c port=SWD -rst

Загрузка прошивки с помощью STM32CubeProgrammer:
    ELF:
     STM32_Programmer_CLI -c port=SWD -w firmware.elf   
    -c port=SWD: Устанавливает интерфейс для подключения.
    mode=UR: Обновление в режиме сброса.
    -d firmware.elf: Путь к прошивке (в формате ELF, HEX или BIN).

    BIN:
    STM32_Programmer_CLI -c port=SWD -w firmware.bin 0x08000000


С помощью st-flash (в Linux/WSL): Если у вас есть .bin файл:
    st-flash write firmware.bin 0x8000000
    Адрес 0x8000000 — это стандартный стартовый адрес флэш-памяти STM32.


Интеграция в Makefile
Добавьте правило flash в Makefile для автоматизации:

makefile:
    ROGRAMMER = "C:/ST/STM32CubeCLT_1.16.0/STM32CubeProgrammer/bin/STM32_Programmer_CLI.exe"
    flash: $(TARGET).elf
	$(PROGRAMMER) -c port=SWD -w $(TARGET).elf

Теперь можно запускать прошивку просто командой:
    make flash

    
