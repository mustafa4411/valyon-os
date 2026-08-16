#define MULTIBOOT_MAGIC 0x1BADB002
#define MULTIBOOT_FLAGS 0x00000000
#define MULTIBOOT_CHECKSUM (-(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS))

__attribute__((section(".multiboot"))) __attribute__((used))
int multiboot_header[] = {
    MULTIBOOT_MAGIC,
    MULTIBOOT_FLAGS,
    MULTIBOOT_CHECKSUM
};

#define VGA ((unsigned short*)0xB8000)
static int x=0,y=0;

void cls(){for(int i=0;i<2000;i++)VGA[i]=0x0F20;x=0;y=0;}
void pc(char c){if(c=='\n'){x=0;y++;return;}VGA[y*80+x]=(0x0F<<8)|c;if(++x>=80){x=0;y++;}}
void ps(const char*s){for(int i=0;s[i];i++)pc(s[i]);}

void kernel_main(){
    cls();
    ps("ValyonOS\n");
    ps("--------\n");
    ps("Kernel loaded.\n");
    ps("\nWelcome to ValyonOS.\n");
    while(1){}
}
