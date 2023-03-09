#
from services.services import NoSirFoundError


class console:
    def __init__(self,serv):
        self.__serv_pictura=serv
    
    def __get_all_nume_sort_an(self):
        try:
            sir=input("Introduceti sirul: ")
            l=self.__serv_pictura.get_all_nume_sort_an(sir)
            for el in l:
                print(el.get_id(),",",el.get_nume(),",",el.get_nume_autor(),",",el.get_an())
        except NoSirFoundError:
            print("Nu s-a gasit nimic de afisat")
    
    def __get_cel_mai_recent(self):
        l=self.__serv_pictura.get_cel_mai_recent()
        for el in l:
            print(el[0],":",el[1])
    
    def show_ui(self):
        #consola
        while True:
            print("Cerinta 1, apasati 1 ")
            print("Cerinta 2, apasati 2 ")
            print("Exit, apasati 0")
            n=input("Comanda: ")
            print()
            if n=="1":
                self.__get_all_nume_sort_an()
            elif n=="2":
                self.__get_cel_mai_recent()
            elif n=="0":
                return
            else: print("Comanda invalida")
