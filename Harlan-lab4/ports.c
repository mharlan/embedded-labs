#include "ports.h"
#include "uart.h"

#include <zneo.h>
#include <string.h>

void ports_print_config(const char *port)
{
	uart_printf("\n");
	if(strcmp(port, "A") == 0) {
		uart_printf("PAIN:\t0x%.2X\n", PAIN);
		uart_printf("PAOUT:\t0x%.2X\n", PAOUT);
		uart_printf("PADD:\t0x%.2X\n", PADD);
		uart_printf("PAHDE:\t0x%.2X\n", PAHDE);
		uart_printf("PAAFH:\t0x%.2X\n", PAAFH);
		uart_printf("PAAFL:\t0x%.2X\n", PAAFL);
		uart_printf("PAOC:\t0x%.2X\n", PAOC);
		uart_printf("PAPUE:\t0x%.2X\n", PAPUE);
		uart_printf("PASMRE:\t0x%.2X\n", PASMRE);
		uart_printf("PAIMUX1:0x%.2X\n", PAIMUX1);
		uart_printf("PAIMUX:\t0x%.2X\n", PAIMUX);
		uart_printf("PAIEDGE:0x%.2X\n", PAIEDGE);
	}
	else if(strcmp(port, "B") == 0) {
		uart_printf("PBIN:\t0x%.2X\n", PBIN);
		uart_printf("PBOUT:\t0x%.2X\n", PBOUT);
		uart_printf("PBDD:\t0x%.2X\n", PBDD);
		uart_printf("PBHDE:\t0x%.2X\n", PBHDE);
		uart_printf("PBAFL:\t0x%.2X\n", PBAFL);
		uart_printf("PBOC:\t0x%.2X\n", PBOC);
		uart_printf("PBPUE:\t0x%.2X\n", PBPUE);
		uart_printf("PBSMRE:\t0x%.2X\n", PBSMRE);
	}
	else if(strcmp(port, "C") == 0) {
		uart_printf("PCIN:\t0x%.2X\n", PCIN);
		uart_printf("PCOUT:\t0x%.2X\n", PCOUT);
		uart_printf("PCDD:\t0x%.2X\n", PCDD);
		uart_printf("PCHDE:\t0x%.2X\n", PCHDE);
		uart_printf("PCAFH:\t0x%.2X\n", PCAFH);
		uart_printf("PCAFL:\t0x%.2X\n", PCAFL);
		uart_printf("PCOC:\t0x%.2X\n", PCOC);
		uart_printf("PCPUE:\t0x%.2X\n", PCPUE);
		uart_printf("PCSMRE:\t0x%.2X\n", PCSMRE);
		uart_printf("PCIMUX:\t0x%.2X\n", PCIMUX);	
	}
	else if(strcmp(port, "D") == 0) {
		uart_printf("PDIN:\t0x%.2X\n", PDIN);
		uart_printf("PDOUT:\t0x%.2X\n", PDOUT);
		uart_printf("PDDD:\t0x%.2X\n", PDDD);
		uart_printf("PDHDE:\t0x%.2X\n", PDHDE);
		uart_printf("PDAFH:\t0x%.2X\n", PDAFH);
		uart_printf("PDAFL:\t0x%.2X\n", PDAFL);
		uart_printf("PDOC:\t0x%.2X\n", PDOC);
		uart_printf("PDPUE:\t0x%.2X\n", PDPUE);
		uart_printf("PDSMRE:\t0x%.2X\n", PDSMRE);
	}
	else if(strcmp(port, "E") == 0) {
		uart_printf("PEIN:\t0x%.2X\n", PEIN);
		uart_printf("PEOUT:\t0x%.2X\n", PEOUT);
		uart_printf("PEDD:\t0x%.2X\n", PEDD);
		uart_printf("PEHDE:\t0x%.2X\n", PEHDE);
		uart_printf("PEOC:\t0x%.2X\n", PEOC);
		uart_printf("PEPUE:\t0x%.2X\n", PEPUE);
		uart_printf("PESMRE:\t0x%.2X\n", PESMRE);
	}
	else if(strcmp(port, "F") == 0) {
		uart_printf("PFIN:\t0x%.2X\n", PFIN);
		uart_printf("PFOUT:\t0x%.2X\n", PFOUT);
		uart_printf("PFDD:\t0x%.2X\n", PFDD);
		uart_printf("PFHDE:\t0x%.2X\n", PFHDE);
		uart_printf("PFAFL:\t0x%.2X\n", PFAFL);
		uart_printf("PFOC:\t0x%.2X\n", PFOC);
		uart_printf("PFPUE:\t0x%.2X\n", PFPUE);
		uart_printf("PFSMRE:\t0x%.2X\n", PFSMRE);
	}
	else if(strcmp(port, "G") == 0) {
		uart_printf("PGIN:\t0x%.2X\n", PGIN);
		uart_printf("PGOUT:\t0x%.2X\n", PGOUT);
		uart_printf("PGDD:\t0x%.2X\n", PGDD);
		uart_printf("PGHDE:\t0x%.2X\n", PGHDE);
		uart_printf("PGAFL:\t0x%.2X\n", PGAFL);
		uart_printf("PGOC:\t0x%.2X\n", PGOC);
		uart_printf("PGPUE:\t0x%.2X\n", PGPUE);
		uart_printf("PGSMRE:\t0x%.2X\n", PGSMRE);
	}
	else if(strcmp(port, "H") == 0) {
		uart_printf("PHIN:\t0x%.2X\n", PHIN);
		uart_printf("PHOUT:\t0x%.2X\n", PHOUT);
		uart_printf("PHDD:\t0x%.2X\n", PHDD);
		uart_printf("PHHDE:\t0x%.2X\n", PHHDE);
		uart_printf("PHAFH:\t0x%.2X\n", PHAFH);
		uart_printf("PHAFL:\t0x%.2X\n", PHAFL);
		uart_printf("PHOC:\t0x%.2X\n", PHOC);
		uart_printf("PHPUE:\t0x%.2X\n", PHPUE);
		uart_printf("PHSMRE:\t0x%.2X\n", PHSMRE);
	}
	else if(strcmp(port, "J") == 0) {
		uart_printf("Port J is unavailabe.\n");
		/*
		uart_printf("PJIN:\t0x%.2X\n", PJIN);
		uart_printf("PJOUT:\t0x%.2X\n", PJOUT);
		uart_printf("PJDD:\t0x%.2X\n", PJDD);
		uart_printf("PJHDE:\t0x%.2X\n", PJHDE);
		uart_printf("PJOC:\t0x%.2X\n", PJOC);
		uart_printf("PJPUE:\t0x%.2X\n", PJPUE);
		uart_printf("PJSMRE:\t0x%.2X\n", PJSMRE);
		*/	
	}
	else if(strcmp(port, "K") == 0) {
		uart_printf("Port K is unavailabe.\n");
		/*
		uart_printf("PKIN:\t0x%.2X\n", PKIN);
		uart_printf("PKOUT:\t0x%.2X\n", PKOUT);
		uart_printf("PKDD:\t0x%.2X\n", PKDD);
		uart_printf("PKHDE:\t0x%.2X\n", PKHDE);
		uart_printf("PKAFL:\t0x%.2X\n", PKAFL);
		uart_printf("PKOC:\t0x%.2X\n", PKOC);
		uart_printf("PKPUE:\t0x%.2X\n", PKPUE);
		uart_printf("PKSMRE:\t0x%.2X\n", PKSMRE);
		*/
	}
	else {
		uart_printf("Select a port A-K.\n");
	}
}
