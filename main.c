extern void main(){
    char *vga = (char*)0xb8000;
    vga[0] = 'Q';      // Character
    vga[1] = 0x07;     // Attribute byte (light gray on black)
    return;
}