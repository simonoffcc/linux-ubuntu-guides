### *Задание*

1. *Установите (распакуйте) инструментальные средства LMbench 3 или Phoronix Test Suite.*
2. *Запустите все контрольные задачи для оценки производительности системы. (Для этого к головном каталоге можно выполнить команду: `make results see`)*
3. *В отчёте представьте проделанные действия, решения возможных проблем, снятые метрики с домашней или лабораторной вычислительной системы с их описанием, а также состав оцениваемой вычислительной системы, имеющий значение для выполненных контрольных задач (например, процессор, память, ядро, дистрибутив Linux).*

---

## Шаг 1. Установка утилиты Phoronix Test Suite

1. Установка побочных утилит
    
    `sudo apt install php7.4-gd curl git sqlite3 bzip2 php-cli php-xml`
    
2. Скачивание тестирующей утилиты из гита
    
    `git clone https://github.com/phoronix-test-suite/phoronix-test-suite`
    
3. Инсталляция утилиты
    
    `cd phoronix-test-suite && sudo ./install-sh`
    
    *Должно быть такое*:
    
    ```nasm
    -e 
    Phoronix Test Suite Installation Completed
    
    Executable File: /usr/bin/phoronix-test-suite
    Documentation: /usr/share/doc/phoronix-test-suite/
    Phoronix Test Suite Files: /usr/share/phoronix-test-suite/
    ```
    

---

## Полезные команды PTS

- `phoronix-test-suite help` – покажет все доступные команды.
- `phoronix-test-suite list-all-tests` – поможет увидеть все доступные тесты для текущей машины.
- `phoronix-test-suite list-all-tests | grep Processor` — видим все тесты для процессора.
- `phoronix-test-suite list-installed-tests` – тесты, которые установлены на машине.
- `phoronix-test-suite list-recommended-tests` – список рекомендованных тестов для вашей ОС.
- `phoronix-test-suite info <name_test>` — позволит посмотреть техническую информацию о тесте.
- `phoronix-test-suite benchmark <test1> <test2> <test3>` — позволит установить (если необходимо) и запустить подряд тесты test1, test2, test3.
- `phoronix-test-suite system-info` - выводит информацию о железе и о системе машины (будет нужно для отчёта)

---

## Шаг 2. **Тестирование**

1. `phoronix-test-suite` - простой текстовый интерактивный интерфейс для Phoronix Test Suite.
    
    ### **Тесты в составе Suite (2)**
    
    1:  pts/audio-encoding
    
    2:  pts/av1
    
    3:  pts/bioinformatics
    
    4:  pts/browsers
    
    5:  pts/cad
    
    6:  pts/chess
    
    7:  pts/compilation
    
    8:  pts/compression
    
    9:  pts/cpu
    
    10: pts/cpu-massive
    
    11: pts/creator
    
    12: pts/cryptocurrency
    
    13: pts/cryptography
    
    14: pts/database
    
    15: pts/desktop-graphics
    
    16: pts/disk
    
    17: pts/electronic-design
    
    18: pts/encoding
    
    19: pts/finance
    
    20: pts/game-dev
    
    21: pts/hpc
    
    22: pts/imaging
    
    23: pts/internet-speed
    
    24: pts/java
    
    25: pts/java-opengl
    
    26: pts/kernel
    
    27: pts/linear-algebra
    
    28: pts/machine-learning
    
    29: pts/memory
    
    30: pts/molecular-dynamics
    
    31: pts/mpi
    
    32: pts/network
    
    33: pts/nvidia-gpu-compute
    
    34: pts/ocr
    
    35: pts/oneapi
    
    36: pts/opencl
    
    37: pts/opengl-demos
    
    38: pts/productivity
    
    39: pts/programmer
    
    40: pts/python
    
    41: pts/quantum-mechanics
    
    42: pts/raytracing
    
    43: pts/renderers
    
    44: pts/scientific-computing
    
    45: pts/sdr
    
    46: pts/server
    
    47: pts/server-cpu-tests
    
    48: pts/speech
    
    49: pts/steam
    
    50: pts/telephony
    
    51: pts/texture-compression
    
    52: pts/unigine
    
    53: pts/video-encoding
    
    54: pts/vulkan-compute
    
    55: pts/vulkan-rt
    
    56: pts/workstation
    
    57: pts/system
    
    58: pts/processor
    
    59: pts/disk
    
    60: pts/graphics
    
    61: pts/memory
    
    62: pts/network
    
    63: pts/os
    
    64: pts/other
    

<aside>
❗ Попробовал выполнить тест 9 (pts/cpu) из набора suite. Зависимостей для установки теста на 11939mb, и у меня просто не хватило места.

В Ubuntu есть очень полезная встроенная программа с граф. интерфейсом (Disk Usage Analyzer), которая помогает посмотреть насколько диск заполняется в реальном времени. Используйте её, когда устанавливаете тесты.

Если у вас такая же проблема и диск переполнился, то командой `phoronix-test-suite remove-installed-test <имя теста>` можно все тесты удалить.

</aside>

---

**Категории с примерами тестов, которые нужно сделать по требованиям лабы:**

- [x]  .

← рекомендуемые (уже мной) тесты 

- Процессор
    - [x]  [Swet](https://openbenchmarking.org/test/pts/swet)
    - [x]  [x264](https://openbenchmarking.org/test/pts/x264) (`phoronix-test-suite list-recommended-tests`)
    - [ ]  [7-Zip Compression](https://openbenchmarking.org/test/pts/compress-7zip) (`phoronix-test-suite list-recommended-tests`)
    - [ ]  [OpenSSL](https://openbenchmarking.org/test/pts/openssl) (`phoronix-test-suite list-recommended-tests`)
    - [ ]  [C-Ray](http://openbenchmarking.org/test/pts/c-ray)
- Оперативная память
    - [x]  [Stream](https://openbenchmarking.org/test/pts/stream) (`phoronix-test-suite list-recommended-tests`)
    - [ ]  [RAMspeed SMP](https://openbenchmarking.org/test/pts/ramspeed) (хороший тест, но слишком много результатов (диаграмм), которые нужно уметь объяснять)
    - [ ]  [Intel Memory Latency Checker](https://openbenchmarking.org/test/pts/intel-mlc) (`phoronix-test-suite list-recommended-tests`)
    - [ ]  [t-test1](https://openbenchmarking.org/test/pts/t-test1)
- Сеть
    - [ ]  [Ethr](https://openbenchmarking.org/test/pts/ethr) (`phoronix-test-suite list-recommended-tests`) - для всех тестов 4 Hours, 19 Minutes
    - [ ]  [Loopback TCP Network Performance](https://openbenchmarking.org/test/pts/network-loopback) (pts/network-loopback)
    - [ ]  [iPerf](https://openbenchmarking.org/test/pts/iperf)
    - [x]  [Aircrack-ng](https://openbenchmarking.org/test/pts/aircrack-ng)
- Диск
    - [x]  [Unpacking The Linux Kernel](https://openbenchmarking.org/test/pts/unpack-linux) (`phoronix-test-suite list-recommended-tests`) (pts/unpack-linux)
    - [ ]  [Flexible IO Tester](https://openbenchmarking.org/test/pts/fio) (pts/fio)
    - [ ]  [Compile Bench](https://openbenchmarking.org/test/pts/compilebench)
    - [ ]  [Dbench](http://openbenchmarking.org/test/pts/dbench)

---

- Прочие тесты (*не трогаем*)
    - Ядро
        - [Unpacking The Linux Kernel](https://openbenchmarking.org/test/pts/unpack-linux)
        - [Timed Linux Kernel Compilation](https://openbenchmarking.org/test/pts/build-linux-kernel) *(привет из 6-ой лабы (: )*
    - Подсистема ввода-вывода
    - Видеокарта

---

## Шаг 3. Запись результатов (для отчёта)

### Запись результатов через консоль (муторный способ)

После выполнения тестов PTS выводит информацию о проведенном 
измерении в консоль и/или в файл. Результаты тестирования сохраняются в 
каталог: `~/.phoronix-test-suite/test-results`

- Чтобы увидеть сохраненные тесты:
    
    `phoronix-test-suite list-results`
    
- Чтобы подробно ознакомится с результатами теста
    
    `phoronix-test-suite show-result < имя теста >`, например
    
    `phoronix-test-suite show-result hmmer-test-result`
    

### Запись результатов с помощью [OpenBenchmarking.org](http://OpenBenchmarking.org) (хороший способ)

1. Регаемся через обычный браузер на сайте [openbechmarking.org](https://openbenchmarking.org/).
2. Авторизуемся в своём аккаунте через консоль используя команду `phoronix-test-suite openbenchmarking-login`.
3. После каждого бенчмарка отвечаем на вопросы о сохранении тестов на сайте.
4. Смотрим красивые диаграммы в своём аккаунте.

---

## Как работают конкретные тесты?

*(текст сгенерирован с помощью ChatGPT-3, [ChatGPT Mar 23 Version](https://help.openai.com/en/articles/6825453-chatgpt-release-notes))*

### Swet (processor)

*Бенчмарк "SWET" в Phoronix Test Suite (PTS) - это бенчмарк процессора, который расшифровывается как "Single-Threaded Web Engine Test" (Тест однопоточного веб-движка). Он предназначен для измерения производительности процессора при выполнении однопоточной нагрузки веб-движка.*

Бенчмарк SWET работает путем моделирования нагрузки веб-браузинга, которая включает в себя последовательную загрузку и рендеринг набора веб-страниц, каждая из которых содержит смесь HTML, CSS и JavaScript. Бенчмарк измеряет время, необходимое для загрузки и рендеринга каждой страницы, а также общее время, необходимое для выполнения всей рабочей нагрузки.

Во время тестирования Phoronix Test Suite запускает экземпляр браузера Firefox и прогоняет через него заранее определенный набор веб-страниц. Бенчмарк повторяет этот процесс несколько раз, чтобы обеспечить стабильность результатов, а затем подсчитывает общий балл, основанный на общем времени, затраченном на выполнение нагрузки.

---

И так, поехали. Процесс отображения страниц можно разбить на следующие основные этапы:

1. Начало разбора HTML
2. Получение внешних ресурсов
3. Разбор CSS и создание CSSOM
4. Выполнение JavaScript
5. Объединение DOM и CSSOM, для построения дерево рендеринга
6. Расчет макета и отрисовка результата

### x264

*Бенчмарк "x264" в Phoronix Test Suite (PTS) - это бенчмарк CPU, измеряющий производительность процессора при кодировании видео с помощью видеокодека x264.*

Бенчмарк x264 работает с использованием видеокодека x264 для сжатия видеофайла с помощью набора предварительно заданных параметров кодирования. Бенчмарк измеряет время, необходимое для завершения процесса кодирования, а также результирующее качество закодированного видео.

Во время тестирования Phoronix Test Suite запускает экземпляр кодера x264 и передает ему предварительно заданный видеофайл и параметры кодирования. Затем кодер сжимает видеофайл, используя заданные параметры, а бенчмарк измеряет время, необходимое для завершения кодирования. Бенчмарк может повторить этот процесс несколько раз, чтобы обеспечить стабильность результатов.

После завершения процесса кодирования бенчмарк измеряет качество полученного видео с помощью набора заранее определенных метрик, таких как пиковое отношение сигнал/шум (PSNR) и индекс структурного сходства (SSIM). Эти метрики дают количественную оценку качества видео, которую можно использовать для сравнения производительности различных процессоров.

### Stream (RAM)

*Бенчмарк "Stream" в Phoronix Test Suite (PTS) - это бенчмарк памяти, который измеряет пропускную способность подсистемы оперативной памяти компьютера.*

Бенчмарк Stream работает путем выполнения набора тестов доступа к памяти, которые включают чтение и запись больших объемов данных из памяти и в память. Бенчмарк измеряет скорость, с которой система может передавать данные между процессором и оперативной памятью, а также задержку доступа к памяти.

В ходе тестирования Phoronix Test Suite выделяет большой блок памяти и выполняет серию тестов, включающих чтение и запись в различные части блока. Тесты направлены на максимальное увеличение пропускной способности памяти путем выполнения последовательных и случайных обращений к памяти, а также операций чтения и записи.

Бенчмарк измеряет время, необходимое для выполнения каждого теста, и рассчитывает набор показателей производительности на основе полученных результатов. Эти показатели включают пропускную способность памяти, которая представляет собой скорость передачи данных между ЦП и оперативной памятью, и задержку памяти, которая представляет собой время, необходимое ЦП для доступа к данным в памяти.

Результаты всех тестов бенчмарка Stream сообщаются в единицах мегабайт в секунду (МБ/с).

### Copy

*Тест "Copy" в бенчмарке Stream для Phoronix Test Suite (PTS) - это бенчмарк памяти, измеряющий скорость копирования данных из одной области памяти в другую.*

Во время теста Copy создается большой блок памяти и копируется содержимое одной части блока в другую. Эта операция повторяется несколько раз, причем разные части блока копируются в разные места. Тест предназначен для измерения максимальной скорости, с которой данные могут быть скопированы в подсистеме памяти без участия ЦП или операций ввода-вывода.

### Scale

*Тест "Scale" в бенчмарке Stream для Phoronix Test Suite (PTS) - это бенчмарк памяти, который измеряет скорость масштабирования данных, или умножения на постоянный коэффициент, в подсистеме памяти.*

Во время теста Scale бенчмарк создает большой блок памяти и умножает содержимое блока на постоянный коэффициент. Эта операция повторяется несколько раз, причем коэффициент и размер блока увеличиваются на каждой итерации. Тест предназначен для измерения максимальной скорости, с которой данные могут быть масштабированы в подсистеме памяти, без участия ЦП или операций ввода-вывода.

### Triad

Тест "Triad" в бенчмарке Stream для Phoronix Test Suite (PTS) - это бенчмарк памяти, который измеряет скорость доступа к данным и манипулирования ими в подсистеме памяти.

Во время теста Triad программа создает три больших блока памяти и выполняет следующую операцию над каждым блоком: `C = A + B * scalar`, где `A`, `B` и `C` - блоки памяти, а `scalar` - постоянное значение. Эта операция повторяется несколько раз, причем значение скаляра и размер блока увеличиваются на каждой итерации. Тест предназначен для измерения максимальной скорости, с которой данные могут быть доступны, обработаны и записаны обратно в память в подсистеме памяти.

### Add

Тест "Add" в бенчмарке Stream для Phoronix Test Suite (PTS) - это бенчмарк памяти, который измеряет скорость доступа к данным и манипулирования ими в подсистеме памяти.

Во время теста Add программа создает два больших блока памяти и выполняет следующую операцию над каждым элементом блоков: `C[i] = A[i] + B[i]`, где `A`, `B` и `C` - блоки памяти, а `i` - индекс элемента. Эта операция повторяется несколько раз, причем размер блока увеличивается на каждой итерации. Тест предназначен для измерения максимальной скорости, с которой данные могут быть доступны, манипулированы и записаны обратно в память в подсистеме памяти.

### Aircrack-ng

*Бенчмарк "Aircrack-ng" в Phoronix Test Suite (PTS) - это сетевой бенчмарк, который измеряет производительность адаптера беспроводной сети компьютера при взломе паролей сети Wi-Fi.*

Бенчмарк Aircrack-ng работает с использованием программного пакета Aircrack-ng для выполнения набора тестов на взлом паролей на заранее определенном наборе захватов сети Wi-Fi. Тест измеряет время, необходимое для взлома каждого пароля, а также общее время, необходимое для взлома всех паролей в наборе.

В ходе тестирования Phoronix Test Suite использует заранее определенный набор захватов сетей Wi-Fi, полученных из реальных сетей Wi-Fi. Каждый захват содержит зашифрованный сетевой трафик, который был захвачен с помощью адаптера беспроводной сети. Затем бенчмарк использует программный пакет Aircrack-ng для проведения словарной атаки на каждый захват, пытаясь взломать пароль с помощью заранее определенного набора паролей.

### Unpacking The Linux Kernel

*Бенчмарк "Unpacking The Linux Kernel" в Phoronix Test Suite (PTS) - это дисковый бенчмарк, измеряющий производительность подсистемы хранения данных компьютера при распаковке сжатого архива исходного кода ядра Linux.*

Бенчмарк Unpacking The Linux Kernel работает путем загрузки заранее определенного сжатого архива исходного кода ядра Linux, а затем измеряет время, необходимое для распаковки архива в целевой каталог на устройстве хранения данных.

Во время тестирования Phoronix Test Suite загружает сжатый архив исходного кода ядра Linux, а затем с помощью команды `tar` распаковывает архив в целевой каталог на устройстве хранения данных. Бенчмарк измеряет время, необходимое для завершения процесса извлечения, а также скорость чтения и записи на диск во время этого процесса.