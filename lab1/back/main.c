#include "head.h"

int main(void)
{
printf("dchsif");
	CPU cpu = get_cpu();
	printf("%s %u %u %u %u %u %u %u", cpu.name, cpu.user, cpu.nice, \
		   cpu.system, cpu.idle, cpu.iowait, cpu.irq, cpu.softirq);
    return 0;
}
