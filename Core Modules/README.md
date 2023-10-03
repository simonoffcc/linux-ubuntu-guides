## Что из себя представляет лаба?

О том, что из себя представляет лаба достаточно хорошо написано в ней самой. Здесь просто я уточню пару моментов, которые явно там не описаны: моменты в которых я сам затупил и долго думал о том, что действительно нужно делать.

### **Подготовительные действия**

- Создать где угодно папку, где вы будете хранить все создаваемые файлы (исходные коды модулей, написанные на языке C). Я например создал папку в домашней директории с названием **lab7**.
- В этой папке нужно будет поочерёдно создавать (если вы хотите реально понять лабу) или же сразу создать 7 файлов-примеров с кодом модулей (весь код есть в лабе, но и тут я его частично тоже продублировал, однако **рекомендую** копировать весь код из лабораторной, потому что тут могут быть опечатки)
    
    <aside>
    💡 `MODULE_LICENSE("GPL");` - важно добавлять в исходный код любого модуля. Иначе будут ошибки
    
    </aside>
    
- В этой же папке необходимо создать **Makefile** (его полный код в самом конце этой статьи), в котором, грубо говоря, храниться инфа о сборке

### Пример 1, 2 (и основные принципы сборки, установки и деинсталяции модулей)

---

`make -C /usr/src/linux-6.2.1 M=$PWD modules` - **сборка модуля**

<aside>
💡 Здесь, конечно же, необходимо поменять название папки <linux-6.2.1> на текущую версию вашего ядра. Это команда читает правила, написанные в **Makefile**, и собирает модули. После сборки в той же самой папке **lab7** создаются файлы с теми же самыми названиями файлов, которые мы сохраняли с расширением `.c`, но только с другими расширениями.

</aside>

---

<aside>
💡 Мы устанавливаем модуль командой `insmod`. Важно, что загружаем мы файл с расширением `.ko`.

</aside>

`sudo insmod ./hello-1.ko` - **загрузка только что собранного модуля**

`sort /proc/modules` - проверить наличие только что загруженного модуля (`sort` просто выводит в алфавитном порядке, можно использовать `cat`)

`sudo rmmod hello-1` - **удаление модуля** (здесь пишем просто название файла, без всяких расширений)

`cat /var/log/kern.log` - **посмотреть вывод модуля ядра** (должно быть сообщение при инициализации - “<1>Hello world 1” и сообщение при выгрузке - “Goodbye world 1”)

> Поменяв код файла *hello-1.c* строчку `return 0` на `return 1` в функции инициализации ядра, при загрузке модуля в лог-файле выводиться строчка `</TASK>`
> 

### Пример 3, 4

`sudo insmod ./hello-1.ko`

`sudo insmod ./hello-2.ko`

### Пример 5

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

static int hello3_data __initdata = 3;
static int __init hello_3_init(void)
{
	printk(KERN_ALERT "Hello, world %d\n", hello3_data);
	return 0;
}
static void __exit hello_3_exit(void)
{
	printk(KERN_ALERT "Goodbye, world 3\n");
}

module_init(hello_3_init);
module_exit(hello_3_exit);
```

`sudo insmod ./hello-3.ko`

### Пример 6

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define DRIVER_AUTHOR "Peter Jay Salzman <p@dirac.org>"
#define DRIVER_DESC "A sample driver"

static int __init init_hello_4(void)
{
	printk(KERN_ALERT "Hello, world 4\n");
	return 0;
}

static void __exit cleanup_hello_4(void)
{
	printk(KERN_ALERT "Goodbye, world 44);
module_exit(cleanup_hello_4);
/*
* Вы можете передавать в макросы строки, как это показано ниже:
*/
/*
* Запретить вывод предупреждения о "загрязнении" ядра, объявив код под GPL.
*/
MODULE_LICENSE("GPL");
/*
* или определения:
*/
MODULE_AUTHOR(DRIVER_AUTHOR); /* Автор модуля */
MODULE_DESCRIPTION(DRIVER_DESC); /* Назначение модуля */
/*
* Этот модуль использует устройство /dev/testdevice. В будущих версиях ядра
* макрос MODULE_SUPPORTED_DEVICE может быть использован
* для автоматической настройки модуля, но пока
* он служит исключительно в описательных целях.
*/
//MODULE_SUPPORTED_DEVICE("testdevice"); - ошибка
```

- **ОШИБКА**
    
    /home/simon/lab7/hello-4.c:38:25: error: expected declaration specifiers or ‘...’ before string constant
    
    38 | MODULE_SUPPORTED_DEVICE("testdevice");
    
    ![Ошибка в коде](https://github.com/simonoffcc/linux-ubuntu-guides/raw/main/images/code_error.png)
    
- **РЕШЕНИЕ**
    
    Просто комментим строчку `MODULE_SUPPORTED_DEVICE(”testdevice”)`
    

### Пример 7

hello-5.c

```c
/*
* hello-5.c - Пример передачи модулю аргументов командной строки.
*/
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Peter Jay Salzman");

static short int myshort = 1;
static int myint = 420;
static long int mylong = 9999;
static char *mystring = "blah";
/*
* module_param(foo, int, 0000)
* Первый параметр -- имя переменной,
* Второй -- тип,
* Последний -- биты прав доступа
* для того, чтобы выставить в sysfs (если ненулевое значение) на более поздней
стадии.
*/
module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "A short integer");
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An integer");
module_param(mylong, long, S_IRUSR);
MODULE_PARM_DESC(mylong, "A long integer");
module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "A character string");
static int __init hello_5_init(void)
{
	printk(KERN_ALERT "Hello, world 5\n=============\n");
	printk(KERN_ALERT "myshort is a short integer: %hd\n", myshort);
	printk(KERN_ALERT "myint is an integer: %d\n", myint);
	printk(KERN_ALERT "mylong is a long integer: %ld\n", mylong);
	printk(KERN_ALERT "mystring is a string: %s\n", mystring);
	return 0;
}
static void __exit hello_5_exit(void)
{
	printk(KERN_ALERT "Goodbye, world 5\n");
}
module_init(hello_5_init);
module_exit(hello_5_exit);
```

`sudo insmod ./hello-5.ko mystring="bebop" myshort=255` - загрузка модуля с параметрами

```nasm
Apr 13 11:13:01 simon-VirtualBox kernel: [  490.600299] Hello, world 5
Apr 13 11:13:01 simon-VirtualBox kernel: [  490.600299] =============
Apr 13 11:13:01 simon-VirtualBox kernel: [  490.600308] myshort is a short integer: 25
Apr 13 11:13:01 simon-VirtualBox kernel: [  490.600311] myint is an integer: 420
Apr 13 11:13:01 simon-VirtualBox kernel: [  490.600313] mylong is a long integer: 9999
Apr 13 11:13:01 simon-VirtualBox kernel: [  490.600314] mystring is a string: bebop
```

`sudo rmmod hello-5`

```nasm
Apr 13 11:14:12 simon-VirtualBox kernel: [  561.742233] Goodbye, world 5
```

`sudo insmod ./hello-5.ko mystring="supercalifragilisticexpialidocious" myint=100`

```nasm
Apr 13 11:15:26 simon-VirtualBox kernel: [  635.966278] Hello, world 5
Apr 13 11:15:26 simon-VirtualBox kernel: [  635.966278] =============
Apr 13 11:15:26 simon-VirtualBox kernel: [  635.966285] myshort is a short integer: 1
Apr 13 11:15:26 simon-VirtualBox kernel: [  635.966287] myint is an integer: 100
Apr 13 11:15:26 simon-VirtualBox kernel: [  635.966289] mylong is a long integer: 9999
Apr 13 11:15:26 simon-VirtualBox kernel: [  635.966290] mystring is a string: supercalifragilisticexpialidocious
```

`sudo rmmod hello-5`

```nasm
Apr 13 11:16:22 simon-VirtualBox kernel: [  692.014171] Goodbye, world 5
```

`sudo insmod ./hello-5.ko mylong=hello`

```nasm
insmod: ERROR: could not insert module ./hello-5.ko: Invalid parameters
```

```nasm
Apr 13 11:17:09 simon-VirtualBox kernel: [  739.029503] hello_5: `hello' invalid for parameter `mylong'
```

### Пример 8, 9

start.c stop.c → startstop.ko

<aside>
💡 Тут два файла конвертируются в один (правило для этого действия можно увидеть в Makefile)

</aside>

---

### Makefile

```makefile
obj-m += hello-1.o
obj-m += hello-2.o
obj-m += hello-3.o
obj-m += hello-4.o
obj-m += hello-5.o
obj-m += startstop.o
startstop-objs := start.o stop.o
```

### Установка всех модулей (→ смотрим log)

`sudo insmod ./hello-1.ko`

`sudo insmod ./hello-2.ko`

`sudo insmod ./hello-3.ko`

`sudo insmod ./hello-4.ko`

`sudo insmod ./hello-5.ko` или `sudo insmod ./hello-5.ko mystring="bebop" myshort=255`

`sudo insmod ./startstop.ko`

### Удаление всех модулей (→ смотрим log)

`sudo rmmod hello-1`

`sudo rmmod hello-2`

`sudo rmmod hello-3`

`sudo rmmod hello-4`

`sudo rmmod hello-5`

`sudo rmmod startstop`

---

### Как отслеживать лог-файл в реальном времени?

<aside>
💡 Это скорее всего у вас спросят, и вот решение:

`tail -f /var/log/kern.log`

*(у меня спросили только это)*

</aside>

<aside>
💡 Также возможен вопрос: **Чем отличается `modprobe` от `insmod` ?**

**Ответ:** `modprobe`, как и `insmod`, загружает модуль в ядро. Она отличается тем, что просматривает модуль, который необходимо загрузить, ссылается ли он на любые символы, которые в настоящее время не определены в ядре.

`insmod` - ему должен быть указан путь к этому самому модулю

`modprobe` - это умная команда, которая анализирует файл *modules.dep*, чтобы сначала загрузить зависимости, прежде чем загрузить данный модуль.

</aside>

`sudo dmesg`
