'''
Función Media_player
Contiene los comandos necesarios para le control de reproducción de música
Reproducción de música mediante libreria pygame mixer
Lectura de archivos mediante librería os
25/05/2021
v1.0
Creado por:
Bruno Sánchez García
Carlos Antonio Buendía Lopez

'''
#Se importan las librerias necearias 
import pygame
import os
import random
#Se define la función Media_player que recibe 3 argumentos Media_player(<tipo de comando>,<comando>,<información en caso de requerirla>)
def Media_player(c_type, command, info):
#La función emplea las variables globales "songs" que es la lista de reproducción y "song" que es un iterador del número de lista de la canción.
    global slist, song, mainlist, playlists, current_lst
#El tipo de comando "init" es para inicializar el reproductor (Siempre se debe utilizar una vez al inicio del código) al usar este tipo de cmando, los otros 2 argumentos sería None   
    if c_type == "init":
        slist = []
        playlists = []
        song = 0
        current_lst = 0
        for fileName in os.listdir(r'Songs/'):
            slist.append(fileName)
        slist = sorted(slist, key=str.lower)
        mainlist = slist
        print(slist)
        for lst in os.listdir(r'Lists/'):
            playlists.append(lst[0:-4])
        playlists = sorted(playlists, key=str.lower)
        playlists.insert(0,"mainlist")
        print(playlists)
        pygame.mixer.init()
        pygame.mixer.music.load('Songs/'+slist[song])
# El tipo de comando "control" sirve para gestionar la reporducción con comandos: play, pausa(ps), stop(stp), volumen (vup,vdwn), rewind(rew), siguiente/anterior(nxt,prv)
#Este tipo de comando no equiere tercer argumento (colocar None)
    if c_type == "control":
        #Comandos stop, pausa  y play
        if command == "stp":
            pygame.mixer.music.stop()
        elif command == "ps":
            pygame.mixer.music.pause()
        elif command == "play":
            if pygame.mixer.music.get_busy():
                pygame.mixer.music.unpause()
            else:
                pygame.mixer.music.play()
        #Comandos volumen arriba, volumen abajo y rewind
        elif command =="vup":
            if pygame.mixer.music.get_volume() == 1.0:
                pygame.mixer.music.set_volume(1.0)
            else:
                pygame.mixer.music.set_volume(pygame.mixer.music.get_volume()+0.01)
        elif command =="vdwn":
            if pygame.mixer.music.get_volume() == 0.0:
                pygame.mixer.music.set_volume(0.0)
            else:
                pygame.mixer.music.set_volume(pygame.mixer.music.get_volume()-0.01)
        elif command == "rew":
            pygame.mixer.music.rewind()
        #Siguiente canción
        elif command =="nxt":
            if song == len(slist)-1:
                song = 0
            else:
                song += 1
            pygame.mixer.music.load('Songs/'+slist[song])
            pygame.mixer.music.play()
        #Canción anterior   
        elif command =="prv":
            if song == 0:
                song = len(slist)-1
            else:
                song -=1
            pygame.mixer.music.load('Songs/'+slist[song])
            pygame.mixer.music.play()
            
        #Canción aleatoria
        elif command == "random":
            slist = mainlist
            random.shuffle(slist)
            print(slist)
            song = 0
            current_lst = 0
            pygame.mixer.music.stop()
            pygame.mixer.music.load('Songs/'+slist[song])
            pygame.mixer.music.play()
        #Obtener canción actual
        elif command == "gs":
            return mainlist.index(slist[song])
        #Obtener lista actual
        elif command == "gl":
            return current_lst
            
            
            
            
#El tipo de comando list sirve para realizar operaciones relacionadas con la gestion de listas de reproducción
    if c_type == "list":
        #Editar/crear lista
        if command == "edlst":
            with open("Lists/"+info+".txt", "w") as file:
                file.write(info+' ')
            playlists = []
            for lst in os.listdir(r'Lists/'):
                playlists.append(lst[0:-4])
            playlists = sorted(playlists, key=str.lower)
            playlists.insert(0,"mainlist")
            current_lst = playlists.index(info)
            print(playlists)
            print(current_lst)
            
        #Eliminar lista      
        if command == "dellst":
            if os.path.exists("Lists/"+info+".txt"):
                os.remove("Lists/"+info+".txt")
            playlists = []
            for lst in os.listdir(r'Lists/'):
                playlists.append(lst[0:-4])
            playlists = sorted(playlists, key=str.lower)
            playlists.insert(0,"mainlist")
            current_lst = 0
            print(playlists)
        #Añadir canción a la lista  
        if command == "add2lst":
            txtdata = []
            with open("Lists/"+info[0]+".txt","r") as file:
                for i in file:
                    txtdata.append(i[0:-1]) 
            with open("Lists/"+info[0]+".txt", "w") as file:
                for i in txtdata:
                    if i != info[1]:
                        file.write(i+"\n")
                file.write(info[1]+"\n")
        #Remover canción de la lista       
        if command == "rmvlst":
            txtdata = []
            with open("Lists/"+info[0]+".txt","r") as file:
                for i in file:
                    txtdata.append(i[0:-1]) 
            with open("Lists/"+info[0]+".txt", "w") as file:
                for i in txtdata:
                    if i != info[1]:
                        file.write(i+"\n")
        #Reproducir una canción
        if command == "psong":
            if info in slist:
                pass
            else:
                slist = mainlist
                current_lst = 0
            print(slist)
            song = slist.index(info)
            pygame.mixer.music.stop()
            pygame.mixer.music.load('Songs/'+info)
            pygame.mixer.music.play()
            
        #Reproducir una lista Media_player("list","plist",indice de lista)
        if command == "plist":
            if info == "Relax":
                info = playlists.index("Relax")
            if info == "Joy":
                info = playlists.index("Joy")
            try:
                current_lst = info
                info = playlists[info]
                slist = []
                song = 0
                with open("Lists/"+info+".txt","r") as file:
                    for i in file:
                        if i[0:-1] != info:
                            slist.append(i[0:-1])
                print(slist)
                pygame.mixer.music.stop()
                pygame.mixer.music.load('Songs/'+slist[song])
                pygame.mixer.music.play()
            except:
                slist = mainlist
                current_lst = 0
                slist = mainlist
                song = 0
                pygame.mixer.music.stop()
                pygame.mixer.music.load('Songs/'+slist[song])
                pygame.mixer.music.play()
    return None


            


