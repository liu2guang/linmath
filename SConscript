import os
from building import * 
import rtconfig

# get current dir path
cwd = GetCurrentDir()

# init src and inc vars
src = []
inc = []

inc = inc + [cwd]
src = src + Glob('*.c')

LOCAL_CCFLAGS = ''
if rtconfig.CROSS_TOOL == 'keil':
    LOCAL_CCFLAGS = ' --diag_suppress=167 --diag_suppress=1035'

# add group to IDE project
objs = DefineGroup('linmath-1.0.0', src, depend = ['PKG_USING_LINMATH'], CPPPATH = inc, LOCAL_CCFLAGS = LOCAL_CCFLAGS)

# traversal subscript
list = os.listdir(cwd)
if GetDepend('PKG_USING_LINMATH'):
    for d in list:
        path = os.path.join(cwd, d)
        if os.path.isfile(os.path.join(path, 'SConscript')):
            objs = objs + SConscript(os.path.join(d, 'SConscript'))

Return('objs') 
