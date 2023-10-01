/*
* hello-4.c - Демонстрация описания модуля.
*/
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
printk(KERN_ALERT "Goodbye, world 4\n");
}
module_init(init_hello_4);
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
//MODULE_SUPPORTED_DEVICE("testdevice");
