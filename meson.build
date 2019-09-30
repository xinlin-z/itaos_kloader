project('kloader', 'c')

#Config data processing
conf_data = configuration_data()
conf_data.set('EMBED_IMG_LBA', get_option('EMBED_IMG_LBA'))

configure_file(output : 'buildvar.h', configuration : conf_data)
configure_file(input : 'diskembed.sh.in', output : 'diskembed.sh', configuration : conf_data)

#Arguments used in both the linking process and compilation
common_args=['-m32','-ffreestanding','-nostdlib','-fno-PIE', '-fno-asynchronous-unwind-tables' , '-mno-avx', '-mno-sse', '-mno-mmx']

#String manipulation to get the linker file
linker_file = 'llscript.ld'
linker_file_str = '@0@/@1@'.format(meson.current_source_dir(), linker_file)

add_project_arguments(common_args ,language : 'c')
add_project_link_arguments('-Wl,-T,'+linker_file_str, '-Wl,-m,elf_i386', '-Wl,--omagic', common_args, language : 'c')

src_files = [
  'gdt.c',
  'kload_main.c',
  'klstart.S',
  'mbrblock.S',
  'memutils.c',
  'terminal_driver.c',
  'a20gate.c',
  'rmsr.c',
  'idt.c',
  'rmsr_impl.S',
  'printf.c',
  'convert.c'
]

kloader_include_dir = include_directories('include')
kloader_exe = executable('kloader', src_files, include_directories : kloader_include_dir)

#Custom target generation of embed.img and mbr.img

prog_objcopy = find_program('objcopy')

embed_img = custom_target('embed', input : kloader_exe, output : 'embed.img',
  command : [prog_objcopy, '@INPUT@', '-O', 'binary', '--remove-section=.mbr_block', '@OUTPUT@'], build_by_default : true)

mbr_img = custom_target('mbr', input : kloader_exe, output : 'mbr.img',
  command : [prog_objcopy, '@INPUT@', '-O', 'binary', '--only-section=.mbr_block', '@OUTPUT@'], build_by_default : true)


meson.add_install_script(meson.current_build_dir()+'/diskembed.sh')
