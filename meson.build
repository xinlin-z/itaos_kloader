project('kloader', 'c')

add_project_arguments('-m32', '-ffreestanding', '-nostdlib', language : 'c')

linker_file = 'llscript.ld'
linker_file_str = '@0@/@1@'.format(meson.current_source_dir(), linker_file)
add_project_link_arguments('-Wl,-T,'+linker_file_str, '-Wl,-m,elf_i386', '-ffreestanding', '-nostdlib', language : 'c')

src_files = ['mbrblock.S', 'gdt.c']
include_dir = include_directories('.')

executable('kloader', src_files, include_directories : include_dir)
