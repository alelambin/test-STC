# linux_kernel_module

> 2.1. Разработать модуль ядра Linux, который реализует драйвер символьного устройства my_dummy_device. При подключении и отключении устройства драйвер должен выводить сообщения в dmesg. Драйвера должны быть совместимы с ядром ОС Ubuntu 18.04.

Для сборки программы необходимо в директории `/source` воспользоваться утилитой `make`. Исполняемый файл &ndash; `my_dummy_driver.ko`. 

Загрузка драйвера осуществляется командой `make load`, выгрузка &ndash; `make unload`.

Пример использования:

![Image alt](https://github.com/alelambin/test-STC/raw/main/linux_kernel_module/resource/image.jpg) 