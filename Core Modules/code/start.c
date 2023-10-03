/*
* start.c - Пример модуля, исходный текст которого размещен в нескольких
файлах
*/
#include <linux/kernel.h> /* Все-таки мы пишем код ядра! */
#include <linux/module.h> /* Необходим для любого модуля ядра */

MODULE_LICENSE("GPL");

int init_module(void)
{
	printk("Hello, world - this is the kernel speaking\n");
	return 0;
}
