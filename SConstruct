VariantDir('build', 'src')
env = Environment()
env['CCFLAGS'] = '-g'
env.ParseConfig('pkg-config --cflags --libs allegro-5.0 allegro_image-5.0')
env.Program(target='sh2015', source=Glob('build/*.cpp'))
