#coding=cp936

import os
from os.path import join,abspath,split,splitext,basename

def RemoveTree(path):
    if len(abspath(path)) < 40:
        return
    for root, dirs, files in os.walk(path, topdown=False):
        for name in files:
            os.remove(join(root,name))
        for name in dirs:
            os.rmdir(join(root,name))
    os.rmdir(path)

def CleanSolution(path,slnname):
    ClnFileExt = ['.ncb','.aps','.user','.ilk','.pdb']
    ClnFolder  = ['debug','release']
    if not os.path.exists(join(path,slnname+".sln")):
        return
    for name in os.listdir(path):
        if (os.path.isfile(join(path,name)) and \
                splitext(name)[0] == slnname and \
                splitext(name)[1] in ClnFileExt):
            os.remove(join(path,name))
    for folder in ClnFolder:
        if os.path.exists(join(path,folder)):
            for file in os.listdir(join(path,folder)):
                if splitext(file)[1] in ClnFileExt:
                    os.remove(join(path,folder,file))
    if not os.path.exists(join(path,slnname)):
        return
    for name in os.listdir(join(path,slnname)):
        if (os.path.isfile(join(path,slnname,name)) and \
                splitext(name)[1] in ClnFileExt):
            os.remove(join(path,slnname,name))
    for folder in ClnFolder:
        if os.path.exists(join(path,slnname,folder)):
            RemoveTree(join(path,slnname,folder))

def RemoveSlns(path):
    for root, dirs, files in os.walk(path):
        for name in files:  
            if splitext(name)[1] == '.sln':
                #print "Cleaning",join(root,splitext(name)[0]),"..."
                print ("Cleaning", root, "...")
                dirs[:] = []
                CleanSolution(root,splitext(name)[0])

if __name__ == '__main__':
    RemoveSlns('.')
    os.system("pause")

    
