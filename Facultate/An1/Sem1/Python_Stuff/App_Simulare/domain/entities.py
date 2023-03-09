#modulul pentru tipurile de date picturi

class pictura:
    #clasa de tip pictura care contine ID, NUME, NUME AUTOR, AN
    def __init__(self, id, nume, nume_autor, an):
        #initializarea obiectului
        self.__id=id
        self.__nume=nume
        self.__nume_autor=nume_autor
        self.__an=an
    
    def get_id(self):
        #getter pentru id
        return self.__id

    def get_nume(self):
        #getter pentru nume
        return self.__nume

    def get_nume_autor(self):
        #getter pentru nume autor
        return self.__nume_autor
    
    def get_an(self):
        #getter pentru an
        return self.__an
    
    def set_id(self, value):
        #setter pentru id
        self.__id=value
    
    def set_nume(self, value):
        #setter pentru nume
        self.__nume=value
    
    def set_nume_autor(self, value):
        #setter pentru nume autor
        self.__nume_autor=value
    
    def set_an(self, value):
        #setter pentru an
        self.__an=value
    
    def __eq__(self, other):
        if self.__id==other.get_id():
            return True
        return False

    