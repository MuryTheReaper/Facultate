#modulul cu operatiile de baza
from domain.entities import pictura

class repo_pictura:
    #operatiile pentru picturi
    def __init__(self, filepath):
        #initializarea repoului
        self.__file=filepath
        self.__storage=[]
        self.__load_file()
    
    def __load_file(self):
        #operatia de incarcare date din fisier in memorie
        with open(self.__file,'r') as f:
            for line in f:
                line=line.split(';')
                id=int(line[0])
                nume=line[1]
                nume_autor=line[2]
                an=int(line[3])
                p=pictura(id,nume,nume_autor,an)
                self.__storage.append(p)
    
    def get_all_pictura(self):
        #operatia care returneaza toata picturile retinute in memorie
        return self.__storage
    
    




        
