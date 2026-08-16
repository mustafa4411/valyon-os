#define MULTIBOOT_MAGIC 0x1BADB002
#define MULTIBOOT_FLAGS 0x00000000
#define MULTIBOOT_CHECKSUM (-(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS))

__attribute__((section(".multiboot"))) __attribute__((used))
int multiboot_header[] = {MULTIBOOT_MAGIC, MULTIBOOT_FLAGS, MULTIBOOT_CHECKSUM};

#define VGA ((unsigned short*)0xB8000)
static int x=0,y=0;

void cls(){for(int i=0;i<2000;i++)VGA[i]=0x0F20;x=0;y=0;}
void pc(char c){if(c=='\n'){x=0;y++;return;}VGA[y*80+x]=(0x0F<<8)|c;if(++x>=80){x=0;y++;}}
void ps(const char*s){for(int i=0;s[i];i++)pc(s[i]);}

// English US layout
static char keys_en[] = {
    0,0,'1','2','3','4','5','6','7','8','9','0','-','=',0,
    0,'q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,'\\','z','x','c','v','b','n','m',',','.','/',0,
    '*',0,' '
};

// Turkish Q layout
static char keys_tr[] = {
    0,0,'1','2','3','4','5','6','7','8','9','0','-','=',0,
    0,'q','w','e','r','t','y','u','i','o','p','g','u','\n',
    0,'a','s','d','f','g','h','j','k','l','s','i','"',
    0,',','z','x','c','v','b','n','m','o','c','.',0,
    '*',0,' '
};

// 0 = English, 1 = Turkish
static int layout = 0;

static inline unsigned char inb(unsigned short port){
    unsigned char val;
    __asm__ volatile("inb %1, %0" : "=a"(val) : "Nd"(port));
    return val;
}

char get_key(){
    unsigned char scan;
    while(1){
        if(inb(0x64) & 1){
            scan = inb(0x60);
            // F1 = switch to English
            if(scan == 0x3B){ layout=0; ps("[EN] "); continue; }
            // F2 = switch to Turkish
            if(scan == 0x3C){ layout=1; ps("[TR] "); continue; }
            char *keys = layout ? keys_tr : keys_en;
            if(scan < 58 && keys[scan])
                return keys[scan];
        }
    }
}

void kernel_main(){
    cls();
    ps("ValyonOS\n");
    ps("--------\n");
    ps("Keyboard: F1=English F2=Turkish\n\n");
    ps("> ");

    while(1){
        char c = get_key();
        pc(c);
        if(c == '\n') ps("> ");
    }
}
