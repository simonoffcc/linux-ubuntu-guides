# Ход работы

1. `cd /usr/src/` - рекомендую размещать папку с ядром тут, ибо там лежат папки всех ядер. Я распаковал просто в домашней папке :)
    
    `wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.2.1.tar.xz`
    
2. `tar xvf linux-6.2.1.tar.xz`
3. `sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison`
    - [Назначение этих пакетов](https://github.com/simonoffcc/linux-ubuntu-guides/raw/main/images/1_packages.png)
    - [Выучить назначения каждого из пакетов Linux для сборки ядра - Flashcards](https://quizlet.com/_cypy9k?x=1jqt&i=4b79qc)

4. `cd linux-6.2.1`
5. `sudo cp -v /boot/config-$(uname -r) .config`
6. `make menuconfig`
7. `sudo nano .config`
    - для быстрого поиска в файле используем “ctrl + w”
    
    ```bash
    CONFIG_SYSTEM_TRUSTED_KEYS=""       # находим эти поля и ставим пустые кавычки
    CONFIG_SYSTEM_REVOCATION_KEYS=""
    ```
    
    - сохраняем файл
8. `make` (по умолчанию 1 поток)
    
    или
    
    `make -jN` (где N - количество потоков, которое будет задействовано при сборке)

9. `sudo make modules_install`
10. `sudo make install`
11. `sudo update-initramfs -c -k 6.2.1`
12. `sudo update-grub2`
13. `sudo reboot`
14. `uname -r`

---

# Выяснение информации об аппаратной платформе для выполнения отчёта

`sudo lshw -short` - **список железных компонентов**

`lscpu` - **информации о процессорных мощностях**

`lspci` - **список PCI**

`lsscsi` - **список SCSI устройств**

`df` - **информация о пространстве файловой системы**

### Файлы /proc

В директории **/proc** существует целое множество файлов, 
содержимое которых расскажет множество интересной и полезной информации о
 компонентах. Например, информация о CPU и памяти:

- cpu информация
    
    `cat /proc/cpuinfo`
    
- информация о памяти
`cat /proc/meminfo`
- информация об операционной системе
    
    `cat /proc/version`
    

---

## Циклическая сборка ядра

`make clean` - очистить каталог от всех файлов полученных в результате компиляции

`nano kernelCyclicBuild.sh`

```bash
#!/bin/bash

cd linux-6.2.1
make clean > /dev/null
for ((i = 0; i < 10; i++ ))
do
{ time make -j$i > /dev/null ; } 2>&1 | grep real
make clean > /dev/null
done
```

❔ [Что такое `..2>&1 | grep real` ? - StackOverflow](https://stackoverflow.com/questions/17257724/grep-time-command-output)

  - По дефолту, утилита `time` выводит инфу в поток ошибок, то есть в 2. Поэтому необходимо перенаправить поток ошибок в поток вывода, то есть в 1. В свою очередь `grep real` означает вывод только строки *real* (кроме *user* и *sys*) - общего времени от начала выполнения процесса и до его завершения.

`chmod +x kernelCyclicBuild.sh`

`./kernelCyclicBuild.sh`

> #### Interesting observation

  - В зелёном квадратике - результаты, которые были получены на ноуте, питаемым от сети

  - В красном - по идее, испорченные значения, которые были собраны чисто на батарее не в режиме максимальной производительности. 

  - Желательно, для точных результатов следует собрать ядро ещё раз по циклу, но можно начиная с 5 потоков.

![funfact](https://github.com/simonoffcc/linux-ubuntu-guides/raw/main/images/2_3_Screenshot.png)

  1. 76 + 57
  2. 68
  3. 68
  4. 68
  5. 68

---

## Индивидуальное задание № 4 - Ускорение сборки ядра за счёт использования каналов

> Цель работы – ускорение сборки ядра за счёт использования каналов.

### Задание

- собрать ядро без использования символьной информации без использования каналов вместо временных файлов (см. опцию pipe в GCC)
- собрать ядро без использования символьной информации с использованием каналов вместо временных файлов
- определить ускорение времени сборки за счёт использования каналов

---

❔ [Что такое *символьная информация* - StackOverflow](https://ru.stackoverflow.com/questions/1383146/%D0%A1%D0%B8%D0%BC%D0%B2%D0%BE%D0%BB%D1%8C%D0%BD%D0%B0%D1%8F-%D0%B8%D0%BD%D1%84%D0%BE%D1%80%D0%BC%D0%B0%D1%86%D0%B8%D1%8F-%D0%BF%D1%80%D0%B8-%D1%81%D0%B1%D0%BE%D1%80%D0%BA%D0%B5-%D1%8F%D0%B4%D1%80%D0%B0-linux)?

  - Чтобы отключить её при сборке ядра, в файле `.config` нужно закомментировать строчку с переменной `CONFIG_DEBUG_INFO`

  - Чтобы наоборот включить, нужно в том же файле `.config` прописать строчку `CONFIG_DEBUG_INFO=y`

  - По сути дела, это же можно сделать красивее в `menuconfig`, но это уже другая история

---

[Распараллеливание процессов](https://habr.com/ru/company/xakep/blog/210480/)

  - Чтобы выиграть еще немного времени, можно добавить ключ '-pipe' к GCC. С этим ключом передача данных между разными стадиями компиляции происходит через каналы обмена (pipes), а не через временные файлы, что немного (совсем немного) ускоряет процесс.

---

### Ход работы

1. `sudo nano .config`
    
    ~~`CONFIG_DEBUG_INFO`~~ → `#CONFIG_DEBUG_INFO`
    
    `time make -j6` - сборка с 6-ю потоками, т.к. выводы из основной проделанной лабораторной работы показали, что для сборки ядра это кол-во потоков является наиболее эффективным.
    
    **Результат:** `87m38,402s` - 5258 секунд
   
    - ![begin](https://github.com/simonoffcc/linux-ubuntu-guides/raw/main/images/4_Untitled.png)

    - ![end](https://github.com/simonoffcc/linux-ubuntu-guides/raw/main/images/5_Untitled.png)
    
3. Повтор действий
    
    **Результат:** 82m17,982s - 4998 секунд

   - ![result2](https://github.com/simonoffcc/linux-ubuntu-guides/raw/main/images/6_Untitled.png)
    
5. Прирост - всего 1% (0,9505515405)

**Результат неудовлетворительный.**

---

## Полезные материалы

- [Об утилите `make`](https://www.opennet.ru/docs/RUS/gnumake/#Make)

- [Просто о make - Habr](https://habr.com/ru/post/211751/)

- [Флаг оптимизации `-pipe`](https://wiki.gentoo.org/wiki/GCC_optimization/ru#-pipe)

- [Синтаксис использования флагов оптимизации](https://stackoverflow.com/questions/23407635/append-compile-flags-to-cflags-and-cxxflags-while-configuration-make)

- [Реальный пример GCC оптимизации](http://computerlib.narod.ru/html/gcc.htm)

---

### 2 попытка

`time make -j$(nproc) CFLAGS="-pipe -O2 -fomit-frame-pointer"`

- ![secondTry](https://github.com/simonoffcc/linux-ubuntu-guides/raw/main/images/7_Untitled.png)

**Фэйл.**

---

### 3 попытка

`time make -j4 CFLAGS="-pipe"`

- ![thirdTry](https://github.com/simonoffcc/linux-ubuntu-guides/raw/main/images/8_Untitled.png)

**Фэйл.**

---

### 4 попытка (подсказка добрых людей с беседы потока)

- ![syntax](https://github.com/simonoffcc/linux-ubuntu-guides/raw/main/images/9_Untitled.png)

- ![explain](https://github.com/simonoffcc/linux-ubuntu-guides/raw/main/images/10_Untitled.png)

`time make -j4 "CFLAGS_KERNEL=-pipe"`

- ![finalResult!](https://github.com/simonoffcc/linux-ubuntu-guides/raw/main/images/10_Untitled.png)

**Результат:** 73m4,368s - 4384 секунд

Разница = 874 секунд

→ **Прирост скорости сборки: 16%**

---

### Бонус

`time make -j$(nproc) FEATURES="-ccache"` - данная команда выполняет сборку проекта с использованием максимально возможного количества ядер процессора, активируя опцию -ccache для кэширования компиляции, и затем измеряет время, необходимое для выполнения этой операции.

---

#### Автор

[Ваня Симоненко](https://t.me/simonoffcc), весна, 2023
