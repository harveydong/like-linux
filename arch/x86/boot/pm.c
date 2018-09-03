#include <asm/header_32.h>
#include <asm/segment.h>
#include <asm/types.h>

static void realmode_switch_hook(void)
{
	if(boot_params.hdr.realmode_swtch){
		asm volatile("lcallw *%0"::"m"(boot_params.hdr.realmode_swtch):"eax","ebx","ecx","edx");
	
	}else{

		asm volatile("cli");
		outb(0x08,0x70);
		io_delay();
	}

}

static void reset_coprocessor(void)
{
	outb(0,0xf0);
	io_delay();
	outb(0,0xf1);
	io_delay();
}

static void mask_all_interrupts(void)
{
	outb(0xff,0xa1);
	io_delay();
	outb(0xfb,0x21);
	io_delay();

}

struct gdt_ptr{
	u16 len;
	u32 ptr;

}__attribute__((packed));


static void setup_idt(void)
{
	static const struct gdt_ptr null_idt = {0,0};
	asm volatile("lidtl %0"::"m"(null_idt));
}


static void setup_gdt(void)
{
	static const u64 boot_gdt[] __attribute__((aligned(16))) = {
		[GDT_ENTRY_BOOT_CS] = GDT_ENTRY(0xc09b,0,0xfffff),
		[GDT_ENTRY_BOOT_DS] = GDT_ENTRY(0xc093,0,0xfffff),
		[GDT_ENTRY_BOOT_TSS] = GDT_ENTRY(0x0089,4096,103),
	};

	static struct gdt_ptr gdt;
	gdt.len = sizeof(boot_gdt) - 1;
	gdt.ptr = (u32)&boot_gdt + (ds() << 4);
	
	asm volatile("lgdtl %0"::"m"(gdt));
}
void go_to_protected_mode(void)
{
	realmode_switch_hook();

	if(enable_a20()){
		my_puts("A20 gate not responding,unable to boo...\n");
		die();
	}
	my_puts("I am pm now\n");
	while(1);	
	printf("code32_start addr: 0x%x\n",boot_params.hdr.code32_start);	
	reset_coprocessor();
	mask_all_interrupts();
	
	setup_idt();
	setup_gdt();

	protected_mode_jump(boot_params.hdr.code32_start,(u32)&boot_params+(ds() << 4));
}
